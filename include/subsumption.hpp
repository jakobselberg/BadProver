#pragma once
#include "cnf.hpp"
#include "config.hpp"
#include "feature_vector.hpp"
#include "linear_index.hpp"
#include <cstddef>
#include <variant>

// picks its backing implementation at construction time based on feature_vector_indexing,
// so the saturation loop doesn't need to know which one is active
class SubsumptionIndex
{
  public:
    SubsumptionIndex() : SubsumptionIndex(get_config_feature_vector_indexing()) {}
    explicit SubsumptionIndex(bool useFeatureVectorIndex);

    void insert(const Clause &c, std::size_t entry);
    std::vector<std::size_t> candidates(const Clause &c) const;

  private:
    std::variant<LinearIndex<Clause, std::size_t>, FeatureVectorIndex<std::size_t>> impl_;
};

bool subsumes(const Clause &A, const Clause &C);
