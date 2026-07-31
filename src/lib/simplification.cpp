#include "simplification.hpp"
#include "ordering.hpp"
#include "unification.hpp"
#include <map>

namespace
{

static std::optional<Term> tryApplyRule(const Term &sub, const RewriteRule &rule)
{
    auto sigma = matchTerm(rule.lhs, sub);
    if (!sigma)
        return std::nullopt;
    if (!kboGreater(applySubstitution(*sigma, rule.lhs), applySubstitution(*sigma, rule.rhs)))
        return std::nullopt;

    return applySubstitution(*sigma, rule.rhs);
}

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

std::optional<Clause> tryDemodulateOnce(const Clause &C, const DemodulationIndex &index,
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

                if (std::holds_alternative<Variable>(*sub))
                    continue;

                auto [cacheIt, inserted] = cache.try_emplace(*sub);
                std::optional<Term> &replacement = cacheIt->second;
                if (inserted)
                {
                    for (const auto &rule : index.matchCandidates(*sub))
                    {
                        replacement = tryApplyRule(*sub, rule);
                        if (replacement)
                            break;
                    }
                }

                if (!replacement)
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

DemodulationIndex::DemodulationIndex(DemodulationIndexKind kind)
{
    switch (kind)
    {
    case DemodulationIndexKind::None:
        impl_ = LinearIndex<Term, RewriteRule>{};
        break;
    case DemodulationIndexKind::Fingerprint:
        impl_ = FingerprintIndex<RewriteRule>{};
        break;
    case DemodulationIndexKind::DiscriminationTree:
        impl_ = DiscriminationTree<RewriteRule>{};
        break;
    }
}

void DemodulationIndex::insert(const Term &t, RewriteRule rule)
{
    std::visit([&](auto &idx) { idx.insert(t, std::move(rule)); }, impl_);
}

std::vector<RewriteRule> DemodulationIndex::matchCandidates(const Term &query) const
{
    return std::visit([&](const auto &idx) { return idx.matchCandidates(query); }, impl_);
}

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
    // cached across the whole fixpoint loop
    std::map<Term, std::optional<Term>> cache;
    bool changed = true;
    while (changed)
    {
        changed = false;
        if (auto result = tryDemodulateOnce(C, index, cache))
        {
            C = std::move(*result);
            changed = true;
        }
    }
    return C;
}
