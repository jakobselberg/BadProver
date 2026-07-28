#pragma once
#include <utility>
#include <vector>

// baseline index that does no filtering at all: every insert is a candidate for every query
template <class Key, class Entry> class LinearIndex
{
  public:
    void insert(const Key &, Entry entry) { entries_.push_back(std::move(entry)); }

    std::vector<Entry> candidates(const Key &) const { return entries_; }
    std::vector<Entry> matchCandidates(const Key &) const { return entries_; }

  private:
    std::vector<Entry> entries_;
};
