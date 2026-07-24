#include "simplification.hpp"
#include "ordering.hpp"
#include "tptp_parser.hpp"
#include "unification.hpp"
#include "util.hpp"
#include <map>

namespace
{
// Position-independent: does `rule` rewrite `sub` at all, and to what? The
// caller is responsible for the position-specific "don't rewrite a nested
// occurrence to $true" check, since the same term value can legally occur
// both as a whole literal side and nested elsewhere - that can't be baked
// into a cache keyed by term value alone.
static std::optional<Term> tryApplyRule(const std::set<Variable> &clauseVars, const Term &sub,
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

    return applySubstitution(*sigma, rule.rhs);
}

// `bindsClauseVar` above guarantees sigma's domain is always disjoint from
// clauseVars once accepted, so - unlike the substitution used to compute
// `replacement` - nothing else in the clause needs any substitution applied
// to it; the other literals are carried over unchanged.
static Clause buildRewrittenClause(const Clause &C, const Literal &lit, int side,
                                   const Term &newTerm)
{
    Literal newLit = lit;
    if (side == 0)
        newLit.left = newTerm;
    else
        newLit.right = newTerm;

    Clause result = {C.id, {}};
    for (const auto &other : C.literals)
        result.literals.insert(other == lit ? newLit : other);
    return result;
}

std::optional<Clause> tryDemodulateOnce(const Clause &C, const std::set<Variable> &clauseVars,
                                        const DemodulationIndex &index,
                                        std::map<Term, std::optional<Term>> &cache)
{
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
                // rewriting at a variable position can never satisfy bindsClauseVar below,
                // since sub is always one of C's own free variables here - skip the index
                // query entirely rather than pay for it and reject it every time
                if (std::holds_alternative<Variable>(*sub))
                    continue;

                auto [cacheIt, inserted] = cache.try_emplace(*sub);
                std::optional<Term> &replacement = cacheIt->second;
                if (inserted)
                {
                    for (const auto &rule : index.candidates(*sub))
                    {
                        replacement = tryApplyRule(clauseVars, *sub, rule);
                        if (replacement)
                            break;
                    }
                }

                if (!replacement)
                    continue;
                if (!pos.empty() && *replacement == tptpTrue())
                    continue;

                auto newTerm = setSubtermAt(target, pos, *replacement);
                if (!newTerm)
                    continue;

                return buildRewrittenClause(C, lit, side, *newTerm);
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

Clause demodulate(Clause C, const DemodulationIndex &index)
{
    // Cached across the whole fixpoint: once a subterm is confirmed
    // rewritable (or confirmed not) it's the same answer on every later
    // pass, since the index itself never changes mid-call and a subterm's
    // own free variables - the only thing the answer depends on beyond the
    // index - are fixed as long as that occurrence still exists in C.
    std::map<Term, std::optional<Term>> cache;
    bool changed = true;
    while (changed)
    {
        changed = false;
        std::set<Variable> clauseVars = FreeVariables(C);
        if (auto result = tryDemodulateOnce(C, clauseVars, index, cache))
        {
            C = std::move(*result);
            changed = true;
        }
    }
    return C;
}
