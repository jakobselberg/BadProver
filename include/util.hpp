#pragma once
#include "cnf.hpp"

std::string printTerm(const Term &t);
std::string printLiteral(const Literal &lit);
std::string printClause(const Clause &clause);
void printC(const Clause &clause);

std::string load_file_from_path(const std::string &path);

// These are NON-STANDARD, but consistent with the cadical solver, so we use them as well!
const int EXIT_UNKNOWN = 0;
const int EXIT_SAT = 10;
const int EXIT_UNSAT = 20;
