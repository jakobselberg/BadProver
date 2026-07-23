#pragma once
#include "cnf.hpp"
#include "discrimination_tree.hpp"
#include <vector>

struct RewriteRule
{
    Term lhs;
    Term rhs;
};

using DemodulationIndex = DiscriminationTree<RewriteRule>;

void removeFalseLiterals(Clause &c);
Clause demodulate(Clause, const DemodulationIndex &);
