#pragma once
#include "cnf.hpp"
#include <array>
#include <map>
#include <memory>
#include <vector>

constexpr std::size_t FEATURE_VECTOR_SIZE = 16;
using FeatureVector = std::array<int, FEATURE_VECTOR_SIZE>;

class SymbolIndex
{
  public:
    int indexOf(const FunctionSymbol &s)
    {
        auto [it, inserted] = map_.try_emplace(s, static_cast<int>(map_.size()));
        return it->second;
    }

  private:
    std::map<FunctionSymbol, int> map_;
};

FeatureVector computeFeatureVector(const Clause &c, SymbolIndex &symbols);

template <class Entry> class FeatureVectorIndex
{
  public:
    void insert(const Clause &c, Entry entry)
    {
        FeatureVector fv = computeFeatureVector(c, symbols_);
        Node *cur = &root_;
        for (int v : fv)
        {
            auto &child = cur->children[v];
            if (!child)
                child = std::make_unique<Node>();
            cur = child.get();
        }
        cur->entries.push_back(std::move(entry));
    }

    std::vector<Entry> candidates(const Clause &c) const
    {
        std::vector<Entry> result;
        FeatureVector fv = computeFeatureVector(c, symbols_);
        collect(&root_, fv, 0, result);
        return result;
    }

  private:
    struct Node
    {
        std::vector<Entry> entries;
        std::map<int, std::unique_ptr<Node>> children;
    };

    static void collect(const Node *node, const FeatureVector &fv, std::size_t depth,
                        std::vector<Entry> &out)
    {
        if (depth == fv.size())
        {
            out.insert(out.end(), node->entries.begin(), node->entries.end());
            return;
        }
        auto end = node->children.upper_bound(fv[depth]);
        for (auto it = node->children.begin(); it != end; ++it)
            collect(it->second.get(), fv, depth + 1, out);
    }

    Node root_;
    mutable SymbolIndex symbols_;
};
