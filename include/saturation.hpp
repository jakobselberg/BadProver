#pragma once
#include "cnf.hpp"
#include "discrimination_tree.hpp"
#include "inference.hpp"
#include "simplification.hpp"
#include "subsumption.hpp"
#include "util.hpp"
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
    DiscriminationTree<std::size_t> subtermIndex;
    DiscriminationTree<std::size_t> eqLiteralIndex;
};

// models a contradiction
bool isEmptyClause(const Clause &c);

SaturationResult saturate(ProofState &state, int max_iteration = 10000);
