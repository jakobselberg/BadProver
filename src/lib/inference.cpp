#include "inference.hpp"
#include "ordering.hpp"
#include "unification.hpp"
#include "util.hpp"
#include <array>

namespace
{
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

        auto sigma = mgu(sourceTerm, *maybeSubterm);
        if (!sigma)
            continue;

        // check ordering side-conditions
        if (!kboGreater(applySubstitution(*sigma, sourceTerm),
                        applySubstitution(*sigma, replacement)))
            continue;

        Clause sigmaD = applySubstitution(*sigma, D);
        if (!isMaximalLiteral(sigmaD.literals, applySubstitution(*sigma, dLit)))
            continue;

        Clause sigmaC = applySubstitution(*sigma, D);
        if (!isMaximalLiteral(sigmaC.literals, applySubstitution(*sigma, cLit)))
            continue;

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
    std::vector<Clause> results;
    for (const auto &dLit : D.literals)
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

                performSuperpositionStep(D, C, dLit, cLit, t, cLit.left, tPrime, results);
                performSuperpositionStep(D, C, dLit, cLit, t, cLit.right, tPrime, results);
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
        for (std::size_t j = i + 1; j < eqLits.size(); ++j)
        {
            if (i == j)
            {
                continue; // Skip the same literal
            }
            const Literal &l1 = eqLits[i];
            const Literal &l2 = eqLits[j];

            const std::array<std::pair<Term, Term>, 4> unifyPairs = {{
                {l1.left, l2.left},
                {l1.left, l2.right},
                {l1.right, l2.left},
                {l1.right, l2.right},
            }};

            const std::array<std::pair<Term, Term>, 4> remainingPairs = {{
                {l1.right, l2.right},
                {l1.right, l2.left},
                {l1.left, l2.right},
                {l1.left, l2.left},
            }};

            const std::array<bool, 4> l2LeftActive = {true, false, true, false};

            for (std::size_t k = 0; k < 4; ++k)
            {
                auto sigma = mgu(unifyPairs[k].first, unifyPairs[k].second);
                if (!sigma)
                    continue;

                // orientation
                const Term &l2Big = l2LeftActive[k] ? l2.left : l2.right;
                const Term &l2Small = l2LeftActive[k] ? l2.right : l2.left;

                auto cmp = kboCompare(applySubstitution(*sigma, l2Big),
                                      applySubstitution(*sigma, l2Small));
                if (cmp == Comparison::Less || cmp == Comparison::Equal)
                    continue;

                // maximality of equality
                Clause sigmaC = applySubstitution(*sigma, C);
                if (!isMaximalLiteral(sigmaC.literals, applySubstitution(*sigma, l2)))
                    continue;

                Clause base{-1, C.literals};
                base.literals.erase(l1);
                base = applySubstitution(*sigma, base);

                Term leftRem = applySubstitution(*sigma, remainingPairs[k].first);
                Term rightRem = applySubstitution(*sigma, remainingPairs[k].second);
                base.literals.insert(makeLiteral(std::move(leftRem), std::move(rightRem), false));

                addClauseIfUseful(results, std::move(base));
            }
        }
    }
    return results;
}
