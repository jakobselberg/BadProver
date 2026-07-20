#include "cnf.hpp"
#include <vector>

void removeFalseLiterals(Clause &c);
Clause demodulate(Clause, const std::vector<Clause> &);