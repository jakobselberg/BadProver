#pragma once
#include "terms.hpp"
#include <optional>
#include <utility> // for std::pair
#include <vector>

std::optional<Substitution> mgu(std::vector<std::pair<Term, Term>> equations);
std::optional<Substitution> mgu(const Term &t, const Term &u);

// one-directional: extends `start` to sigma s.t. sigma(pattern) = target, substituting
// only pattern's variables; target is never substituted into
std::optional<Substitution> matchTerm(const Term &pattern, const Term &target,
                                      Substitution start = {});
