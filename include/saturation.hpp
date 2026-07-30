#pragma once
#include "cnf.hpp"
#include "inference.hpp"
#include "simplification.hpp"
#include "subsumption.hpp"
#include "superposition_index.hpp"
#include "util.hpp"
#include <climits>
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
    std::set<std::set<Literal>> seen;
    DemodulationIndex demodulationIndex;
    SubsumptionIndex subsumptionIndex;
    SuperpositionIndex subtermIndex;
    SuperpositionIndex eqLiteralIndex;
};

// models a contradiction
bool isEmptyClause(const Clause &c);

SaturationResult saturate(ProofState &state, int max_iteration = INT_MAX);
