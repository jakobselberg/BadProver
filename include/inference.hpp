#pragma once
#include "cnf.hpp"
#include <vector>

std::vector<Clause> superposition(const Clause &D, const Clause &C);
std::vector<Clause> equalityResolution(const Clause &C);
std::vector<Clause> equalityFactoring(const Clause &C);

Clause demodulate(Clause C, const std::vector<Clause> &active);