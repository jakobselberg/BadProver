#include "cnf.hpp"
#pragma once

int clauseWeight(const Clause &);
std::size_t selectGivenIndex(const std::vector<Clause> &, bool);