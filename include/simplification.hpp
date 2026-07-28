#pragma once
#include "cnf.hpp"
#include "config.hpp"
#include "discrimination_tree.hpp"
#include "fingerprint.hpp"
#include "linear_index.hpp"
#include <variant>
#include <vector>

struct RewriteRule
{
    Term lhs;
    Term rhs;
};

// picks its backing implementation at construction time based on DemodulationIndexKind,
// so the saturation loop and demodulate() don't need to know which one is active
class DemodulationIndex
{
  public:
    DemodulationIndex() : DemodulationIndex(get_config_demodulation_index()) {}
    explicit DemodulationIndex(DemodulationIndexKind kind);

    void insert(const Term &t, RewriteRule rule);
    std::vector<RewriteRule> matchCandidates(const Term &query) const;

  private:
    std::variant<LinearIndex<Term, RewriteRule>, FingerprintIndex<RewriteRule>,
                DiscriminationTree<RewriteRule>>
        impl_;
};

void removeFalseLiterals(Clause &c);
Clause demodulate(Clause, const DemodulationIndex &);
