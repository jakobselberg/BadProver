#include "inference.hpp"
#include "ordering.hpp"
#include "tptp_parser.hpp"
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
        if (!isMaximalLiteral(sigmaD.literals, applySubstitution(*sigma, dLit)))
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

static std::optional<Clause> tryDemodulateOnce(const Clause &C, const Term &lhs, const Term &rhs)
{
    std::set<Variable> clauseVars = FreeVariables(C);
    for (const auto &lit : C.literals)
    {
        for (int side = 0; side < 2; ++side)
        {
            const Term &target = (side == 0) ? lit.left : lit.right;
            for (const auto &pos : allSubtermPositions(target))
            {
                auto sub = getSubtermAt(target, pos);
                if (!sub)
                    continue;
                auto sigma = mgu(lhs, *sub);
                if (!sigma)
                    continue;
                bool bindsClauseVar = false;
                for (const auto &[v, unused] : *sigma)
                    if (clauseVars.count(v))
                    {
                        bindsClauseVar = true;
                        break;
                    }
                if (bindsClauseVar)
                    continue;
                if (!kboGreater(applySubstitution(*sigma, lhs), applySubstitution(*sigma, rhs)))
                    continue;
                Term sigmaRhs = applySubstitution(*sigma, rhs);
                if (!pos.empty() && sigmaRhs == tptpTrue())
                    continue;
                auto newTerm = setSubtermAt(target, pos, sigmaRhs);
                if (!newTerm)
                    continue;

                Literal newLit = lit;
                if (side == 0)
                    newLit.left = *newTerm;
                else
                    newLit.right = *newTerm;
                Clause result = {C.id, {}};
                for (const auto &other : C.literals)
                {
                    if (other == lit)
                        result.literals.insert(applySubstitution(*sigma, newLit));
                    else
                        result.literals.insert(applySubstitution(*sigma, other));
                }
                return result;
            }
        }
    }
    return std::nullopt;
}

} // namespace

Clause demodulate(Clause C, const std::vector<Clause> &active)
{
    bool changed = true;
    while (changed)
    {
        changed = false;
        for (const auto &d : active)
        {
            if (d.literals.size() != 1)
                continue;
            const Literal &rule = *d.literals.begin();
            if (!rule.positive)
                continue;

            for (const auto &[lhs, rhs] :
                 {std::pair{rule.left, rule.right}, std::pair{rule.right, rule.left}})
            {
                auto result = tryDemodulateOnce(C, lhs, rhs);
                if (result)
                {
                    C = std::move(*result);
                    changed = true;
                    break;
                }
            }
            if (changed)
                break;
        }
    }
    return C;
}

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
