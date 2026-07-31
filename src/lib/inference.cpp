#include "inference.hpp"
#include "ordering.hpp"
#include "unification.hpp"
#include <array>

namespace
{

// Renames c's variables to names not used anywhere in `forbidden` (which must
// include c's own variables), so the result shares no variable with any clause
// `forbidden` was built from. Deterministic: depends only on the inputs.
static Clause standardizeApart(const Clause &c, const std::set<Variable> &forbidden)
{
    Substitution renaming;
    int next = 0;
    for (const auto &v : FreeVariables(c))
    {
        Variable fresh;
        do
        {
            fresh = Variable{"_v" + std::to_string(next++)};
        } while (forbidden.count(fresh));
        renaming[v] = fresh;
    }
    return applySubstitution(renaming, c);
}

static void addClauseIfUseful(std::vector<Clause> &results, Clause clause)
{
    if (!isTautology(clause))
        results.push_back(std::move(clause));
}

// Only negative literals are ever selected. Any deterministic choice preserves
// completeness (ordered superposition with selection, see e.g. [Wal23] "Selection
// Functions"). Selecting in a clause makes it unusable as a superposition equation
// source (D), so to never give up D-usability we'd otherwise have, only select in
// clauses with no positive literal at all -- those could never serve as D anyway.
static std::optional<Literal> selectLiteral(const Clause &c)
{
    for (const auto &lit : c.literals)
        if (lit.positive)
            return std::nullopt;
    for (const auto &lit : c.literals)
        return lit;
    return std::nullopt;
}

static void performSuperpositionStep(const Clause &D, const Clause &C, const Literal &dLit,
                                     const Literal &cLit, const Term &sourceTerm,
                                     const Term &targetTerm, bool targetIsLeft,
                                     const Term &replacement, bool nothingSelectedInC,
                                     std::vector<Clause> &results)
{
    for (const auto &[pos, subterm] : allSubtermsWithPositions(targetTerm))
    {
        auto sigma = mgu(sourceTerm, subterm);
        if (!sigma)
            continue;

        // check ordering side-conditions: reject only a forbidden *smaller* orientation;
        // an incomparable orientation (e.g. terms sharing no variables) remains eligible
        if (kboCompare(applySubstitution(*sigma, sourceTerm),
                       applySubstitution(*sigma, replacement)) == Comparison::Less)
            continue;

        Clause sigmaD = applySubstitution(*sigma, D);
        if (!isMaximalLiteral(sigmaD.literals, applySubstitution(*sigma, dLit)))
            continue;

        Clause sigmaC = applySubstitution(*sigma, C);
        if (nothingSelectedInC &&
            !isMaximalLiteral(sigmaC.literals, applySubstitution(*sigma, cLit)))
            continue;

        Clause cCopy{-1, C.literals};
        cCopy.literals.erase(cLit);

        Literal replacedLiteral = cLit;

        // equality literal: replace the proper side
        if (targetIsLeft)
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

        Clause merged{-1, std::move(cCopy.literals)};
        merged.literals.merge(dCopy.literals);
        addClauseIfUseful(results, std::move(merged));
    }
}

} // namespace

std::vector<Clause> superposition(const Clause &D, const Clause &C)
{
    std::set<Variable> forbidden = FreeVariables(D);
    for (const auto &v : FreeVariables(C))
        forbidden.insert(v);
    Clause dRenamed = standardizeApart(D, forbidden);

    // D's literal must be positive, and only negative literals are ever selected, so D
    // is only usable here when nothing in it is selected at all.
    if (selectLiteral(dRenamed))
        return {};

    std::optional<Literal> selectedC = selectLiteral(C);
    bool nothingSelectedInC = !selectedC.has_value();

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
                if (selectedC && cLit != *selectedC)
                    continue;

                performSuperpositionStep(dRenamed, C, dLit, cLit, t, cLit.left, /*targetIsLeft=*/true,
                                         tPrime, nothingSelectedInC, results);
                performSuperpositionStep(dRenamed, C, dLit, cLit, t, cLit.right,
                                         /*targetIsLeft=*/false, tPrime, nothingSelectedInC, results);
            }
        }
    }
    return results;
}

std::vector<Clause> equalityResolution(const Clause &C)
{
    std::vector<Clause> results;
    std::optional<Literal> selected = selectLiteral(C);
    for (const auto &lit : C.literals)
    {
        if (lit.positive)
            continue;
        if (selected && lit != *selected)
            continue;

        auto sigma = mgu(lit.left, lit.right);
        if (!sigma)
            continue;

        if (!selected)
        {
            Clause sigmaC = applySubstitution(*sigma, C);
            if (!isMaximalLiteral(sigmaC.literals, applySubstitution(*sigma, lit)))
                continue;
        }

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
    // factoring only ever fires on positive literals, so it's void whenever C has a
    // selected (necessarily negative) literal
    if (selectLiteral(C))
        return results;

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
