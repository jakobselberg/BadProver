#include "superposition_index.hpp"

SuperpositionIndex::SuperpositionIndex(bool useDiscriminationTree)
{
    if (useDiscriminationTree)
        impl_ = DiscriminationTree<std::size_t>{};
    else
        impl_ = LinearIndex<Term, std::size_t>{};
}

void SuperpositionIndex::insert(const Term &t, std::size_t entry)
{
    std::visit([&](auto &idx) { idx.insert(t, entry); }, impl_);
}

std::vector<std::size_t> SuperpositionIndex::candidates(const Term &query) const
{
    return std::visit([&](const auto &idx) { return idx.candidates(query); }, impl_);
}
