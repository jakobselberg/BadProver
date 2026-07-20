#include "simplification.hpp"
#include "ordering.hpp"
#include "tptp_parser.hpp"
#include "unification.hpp"
#include "util.hpp"

namespace
{
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

void removeFalseLiterals(Clause &c)
{
    std::set<Literal> kept;
    for (const auto &lit : c.literals)
        if (lit.positive || lit.left != lit.right)
            kept.insert(lit);
    c.literals = std::move(kept);
}

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
