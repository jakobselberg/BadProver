#include "simplification.hpp"
#include "ordering.hpp"
#include "tptp_parser.hpp"
#include "unification.hpp"
#include "util.hpp"

namespace
{
static std::optional<Clause> tryDemodulateOnce(const Clause &C,
                                               const std::set<Variable> &clauseVars,
                                               const Literal &lit, int side, const Position &pos,
                                               const Term &target, const Term &sub,
                                               const RewriteRule &rule)
{
    auto sigma = mgu(rule.lhs, sub);
    if (!sigma)
        return std::nullopt;

    bool bindsClauseVar = false;
    for (const auto &[v, unused] : *sigma)
        if (clauseVars.count(v))
        {
            bindsClauseVar = true;
            break;
        }
    if (bindsClauseVar)
        return std::nullopt;
    if (!kboGreater(applySubstitution(*sigma, rule.lhs), applySubstitution(*sigma, rule.rhs)))
        return std::nullopt;

    Term sigmaRhs = applySubstitution(*sigma, rule.rhs);
    if (!pos.empty() && sigmaRhs == tptpTrue())
        return std::nullopt;

    auto newTerm = setSubtermAt(target, pos, sigmaRhs);
    if (!newTerm)
        return std::nullopt;

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
