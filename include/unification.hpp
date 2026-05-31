#pragma once
#include "terms.hpp"
#include <optional>
#include <utility> // for std::pair
#include <vector>

std::optional<Substitution> mgu(std::vector<std::pair<Term, Term>> equations);
std::optional<Substitution> mgu(const Term &t, const Term &u);
