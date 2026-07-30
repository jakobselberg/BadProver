#pragma once
#include "config.hpp"
#include "discrimination_tree.hpp"
#include "linear_index.hpp"
#include "terms.hpp"
#include <cstddef>
#include <variant>
#include <vector>

// backs subtermIndex/eqLiteralIndex candidate lookup for superposition; picks its
// implementation at construction time based on superposition_indexing
class SuperpositionIndex
{
  public:
    SuperpositionIndex() : SuperpositionIndex(get_config_superposition_indexing()) {}
    explicit SuperpositionIndex(bool useDiscriminationTree);

    void insert(const Term &t, std::size_t entry);
    std::vector<std::size_t> candidates(const Term &query) const;

  private:
    std::variant<LinearIndex<Term, std::size_t>, DiscriminationTree<std::size_t>> impl_;
};
