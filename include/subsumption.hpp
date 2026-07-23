#pragma once
#include "cnf.hpp"
#include "feature_vector.hpp"
#include <cstddef>

using SubsumptionIndex = FeatureVectorIndex<std::size_t>;

bool subsumes(const Clause &A, const Clause &C);