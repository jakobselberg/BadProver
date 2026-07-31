#pragma once
#include "cnf.hpp"

int clauseWeight(const Clause &);
// weights must be precomputed for every entry of passive, in the same order
std::size_t selectGivenIndex(const std::vector<Clause> &passive, const std::vector<int> &weights,
                             bool preferAge);
