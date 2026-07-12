#pragma once
#include "cnf.hpp"

std::string printTerm(const Term &t);
std::string printLiteral(const Literal &lit);
std::string printClause(const Clause &clause);
void printC(const Clause &clause);
