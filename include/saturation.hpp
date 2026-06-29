#pragma once
#include "cnf.hpp"
#include "inference.hpp"
#include <cstddef> // for std::size_t

enum class SaturationResult
{
    Unsatisfiable,
    Saturated,
    Unknown
};

struct ProofState
{
    std::vector<Clause> active;
    std::vector<Clause> passive;
    int next_id;
};

// models a contradiction
bool isEmptyClause(const Clause &c);

int clauseWeight(const Clause &c);

std::size_t selectGivenIndex(const std::vector<Clause> &passive);

SaturationResult saturate(ProofState &state, int max_iteration = 10000);
