#pragma once
#include "cnf.hpp"
#include "terms.hpp"
#include <set>

enum class Comparison
{
    Greater,
    Less,
    Equal,
    Incomparable
};

// Naive KBO: every function symbol and variable gets weight 1,
// symbols are compared by arity then name

Comparison kboCompare(const Term &s, const Term &t);
bool kboGreater(const Term &s, const Term &t);

// Multiset ordering based on KBO
Comparison compareLiterals(const Literal &a, const Literal &b);
bool isMaximalLiteral(const std::set<Literal> &lits, const Literal &lit);
