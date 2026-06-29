#pragma once
#include "cnf.hpp"
#include "inference.hpp"

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
