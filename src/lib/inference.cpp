#include "inference.hpp"
#include "ordering.hpp"
#include "tptp_parser.hpp"
#include "unification.hpp"
#include "util.hpp"
#include <array>

namespace
{

static int gFreshVarCounter = 0;

static Clause standardizeApart(const Clause &c)
{
    std::set<Variable> vars = FreeVariables(c);
    Substitution renaming;
    for (const auto &v : vars)
        renaming[v] = Variable{"_v" + std::to_string(gFreshVarCounter++)};
    return applySubstitution(renaming, c);
}

static Literal invertLiteral(const Literal &lit)
{
    return Literal{lit.left, lit.right, !lit.positive};
}

static bool isTautology(const Clause &c)
{
    for (const auto &lit : c.literals)
    {
        if (c.literals.contains(invertLiteral(lit)))
            return true;
        if (lit.positive && lit.left == lit.right)
            return true;
    }
    return false;
}

static void addClauseIfUseful(std::vector<Clause> &results, Clause clause)
{
    if (!isTautology(clause))
        results.push_back(std::move(clause));
}

static void performSuperpositionStep(const Clause &D, const Clause &C, const Literal &dLit,
                                     const Literal &cLit, const Term &sourceTerm,
                                     const Term &targetTerm, const Term &replacement,
                                     std::vector<Clause> &results)
{
    for (const auto &pos : allSubtermPositions(targetTerm))
    {
        auto maybeSubterm = getSubtermAt(targetTerm, pos);
        if (!maybeSubterm)
            continue;

        if (!pos.empty() && replacement == tptpTrue())
            continue;
        auto sigma = mgu(sourceTerm, *maybeSubterm);
        if (!sigma)
            continue;

        // check ordering side-conditions
        if (!kboGreater(applySubstitution(*sigma, sourceTerm),
                        applySubstitution(*sigma, replacement)))
            continue;

        Clause sigmaD = applySubstitution(*sigma, D);
        std::set<Literal> posSigmaD;
        for (const auto &l : sigmaD.literals)
            if (l.positive)
                posSigmaD.insert(l);
        if (!isMaximalLiteral(posSigmaD, applySubstitution(*sigma, dLit)))
            continue;

        if (cLit.positive)
        {
            Clause sigmaC = applySubstitution(*sigma, C);
            if (!isMaximalLiteral(sigmaC.literals, applySubstitution(*sigma, cLit)))
                continue;
        }
        Clause cCopy{-1, C.literals};
        cCopy.literals.erase(cLit);

        Literal replacedLiteral = cLit;

        // equality literal: replace the proper side
        if (targetTerm == cLit.left)
        {
            auto newLeft = setSubtermAt(cLit.left, pos, replacement);
            if (!newLeft)
                continue;
            replacedLiteral.left = *newLeft;
        }
        else
        {
            auto newRight = setSubtermAt(cLit.right, pos, replacement);
            if (!newRight)
                continue;
            replacedLiteral.right = *newRight;
        }

        cCopy.literals.insert(replacedLiteral);
        cCopy = applySubstitution(*sigma, cCopy);

        Clause dCopy{-1, D.literals};
        dCopy.literals.erase(dLit);
        dCopy = applySubstitution(*sigma, dCopy);

        Clause merged{-1, {}};
        merged.literals = cCopy.literals;
        merged.literals.merge(dCopy.literals);
        addClauseIfUseful(results, std::move(merged));
    }
}

} // namespace

std::vector<Clause> superposition(const Clause &D, const Clause &C)
{

    Clause dRenamed = standardizeApart(D);

    std::vector<Clause> results;
    for (const auto &dLit : dRenamed.literals)
    {
        if (!dLit.positive)
            continue;

        const std::array<std::pair<Term, Term>, 2> orientations = {{
            {dLit.left, dLit.right},
            {dLit.right, dLit.left},
        }};

        for (const auto &[t, tPrime] : orientations)
        {
            for (const auto &cLit : C.literals)
            {

                performSuperpositionStep(dRenamed, C, dLit, cLit, t, cLit.left, tPrime, results);
                performSuperpositionStep(dRenamed, C, dLit, cLit, t, cLit.right, tPrime, results);
            }
        }
    }
    return results;
}

std::vector<Clause> equalityResolution(const Clause &C)
{
    std::vector<Clause> results;
    for (const auto &lit : C.literals)
    {
        if (lit.positive)
            continue;

        auto sigma = mgu(lit.left, lit.right);
        if (!sigma)
            continue;

        Clause resolvent{-1, C.literals};
        resolvent.literals.erase(lit);
        resolvent = applySubstitution(*sigma, resolvent);
        addClauseIfUseful(results, std::move(resolvent));
    }
    return results;
}

std::vector<Clause> equalityFactoring(const Clause &C)
{
    std::vector<Clause> results;
    std::vector<Literal> eqLits;
    for (const auto &lit : C.literals)
    {
        if (lit.positive)
            eqLits.push_back(lit);
    }

    for (std::size_t i = 0; i < eqLits.size(); ++i)
    {
        for (std::size_t j = 0; j < eqLits.size(); ++j)
        {
            if (i == j)
                continue;

            const Literal &first = eqLits[i];
            const Literal &second = eqLits[j];

            // Ordered equality factoring:
            //
            //   C | s = t | u = v
            // ---------------------  sigma = mgu(s, u), t sigma is NOT < s sigma
            // C sigma | s sigma = t sigma | t sigma != v sigma
            //
            // The first equality is the maximal, oriented equality: s is the
            // (weakly) larger side, not t.  Either side of the second
            // equality may be the side unified with s.
            const std::array<std::pair<Term, Term>, 2> firstOrientations = {{
                {first.left, first.right},
                {first.right, first.left},
            }};
            const std::array<std::pair<Term, Term>, 2> secondOrientations = {{
                {second.left, second.right},
                {second.right, second.left},
            }};

            for (const auto &[s, t] : firstOrientations)
            {
                for (const auto &[u, v] : secondOrientations)
                {
                    auto sigma = mgu(s, u);
                    if (!sigma)
                        continue;

                    if (kboCompare(applySubstitution(*sigma, s), applySubstitution(*sigma, t)) ==
                        Comparison::Less)
                        continue;

                    Clause sigmaC = applySubstitution(*sigma, C);
                    if (!isMaximalLiteral(sigmaC.literals, applySubstitution(*sigma, first)))
                        continue;

                    Clause conclusion{-1, C.literals};
                    conclusion.literals.erase(second);
                    conclusion = applySubstitution(*sigma, conclusion);

                    Term remainingFirst = applySubstitution(*sigma, t);
                    Term remainingSecond = applySubstitution(*sigma, v);
                    conclusion.literals.insert(
                        makeLiteral(std::move(remainingFirst), std::move(remainingSecond), false));
                    addClauseIfUseful(results, std::move(conclusion));
                }
            }
        }
    }
    return results;
}
