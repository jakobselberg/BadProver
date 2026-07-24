#pragma once
#include "terms.hpp"
#include <compare>
#include <map>
#include <memory>
#include <vector>

enum class DiscrKeyKind
{
    Star,
    App,
};

struct DiscrKey
{
    DiscrKeyKind kind;
    FunctionSymbol symbol;

    std::strong_ordering operator<=>(const DiscrKey &other) const
    {
        if (auto byKind = kind <=> other.kind; byKind != 0)
            return byKind;
        if (kind == DiscrKeyKind::App)
            return symbol <=> other.symbol;
        return std::strong_ordering::equal;
    }
    bool operator==(const DiscrKey &other) const
    {
        if (kind != other.kind)
            return false;
        if (kind == DiscrKeyKind::App)
            return symbol == other.symbol;
        return true;
    }
};

std::vector<DiscrKey> linearize(const Term &t);
std::size_t skipSubtree(const std::vector<DiscrKey> &tokens, std::size_t pos);

template <class Entry> class DiscriminationTree
{
  public:
    void insert(const Term &t, Entry entry)
    {
        auto tokens = linearize(t);
        Node *cur = &root_;
        for (const auto &tok : tokens)
        {
            auto &child = cur->children[tok];
            if (!child)
                child = std::make_unique<Node>();
            cur = child.get();
        }
        cur->entries.push_back(std::move(entry));
    }

    std::vector<Entry> candidates(const Term &query) const
    {
        std::vector<Entry> result;
        auto tokens = linearize(query);
        collect(&root_, tokens, 0, result);
        return result;
    }

    // one-directional: entries whose indexed term t satisfies sigma(t) = query
    // for some sigma, i.e. candidates for matchTerm(t, query)
    std::vector<Entry> matchCandidates(const Term &query) const
    {
        std::vector<Entry> result;
        auto tokens = linearize(query);
        collectGeneralisations(&root_, tokens, 0, result);
        return result;
    }

  private:
    struct Node
    {
        std::vector<Entry> entries;
        std::map<DiscrKey, std::unique_ptr<Node>> children;
    };

    static void skipInTrie(const Node *node, std::vector<const Node *> &out)
    {
        std::vector<std::pair<const Node *, std::size_t>> frontier = {{node, 1}};
        while (!frontier.empty())
        {
            auto [pos, toSkip] = frontier.back();
            frontier.pop_back();
            for (const auto &[key, child] : pos->children)
            {
                std::size_t next = key.kind == DiscrKeyKind::Star
                                       ? toSkip - 1
                                       : toSkip + static_cast<std::size_t>(key.symbol.arity) - 1;
                if (next == 0)
                    out.push_back(child.get());
                else
                    frontier.push_back({child.get(), next});
            }
        }
    }

    static void collect(const Node *node, const std::vector<DiscrKey> &tokens, std::size_t pos,
                        std::vector<Entry> &out)
    {
        if (pos == tokens.size())
        {
            out.insert(out.end(), node->entries.begin(), node->entries.end());
            return;
        }

        const DiscrKey &tok = tokens[pos];
        if (tok.kind == DiscrKeyKind::Star)
        {
            std::vector<const Node *> dests;
            skipInTrie(node, dests);
            for (const Node *dest : dests)
                collect(dest, tokens, pos + 1, out);
            return;
        }

        auto appIt = node->children.find(tok);
        if (appIt != node->children.end())
            collect(appIt->second.get(), tokens, pos + 1, out);

        auto starIt = node->children.find(DiscrKey{DiscrKeyKind::Star, {}});
        if (starIt != node->children.end())
            collect(starIt->second.get(), tokens, skipSubtree(tokens, pos), out);
    }

    static void collectGeneralisations(const Node *node, const std::vector<DiscrKey> &tokens,
                                       std::size_t pos, std::vector<Entry> &out)
    {
        if (pos == tokens.size())
        {
            out.insert(out.end(), node->entries.begin(), node->entries.end());
            return;
        }

        const DiscrKey &tok = tokens[pos];
        if (tok.kind == DiscrKeyKind::Star)
        {
            auto starIt = node->children.find(DiscrKey{DiscrKeyKind::Star, {}});
            if (starIt != node->children.end())
                collectGeneralisations(starIt->second.get(), tokens, pos + 1, out);
            return;
        }

        auto appIt = node->children.find(tok);
        if (appIt != node->children.end())
            collectGeneralisations(appIt->second.get(), tokens, pos + 1, out);

        auto starIt = node->children.find(DiscrKey{DiscrKeyKind::Star, {}});
        if (starIt != node->children.end())
            collectGeneralisations(starIt->second.get(), tokens, skipSubtree(tokens, pos), out);
    }

    Node root_;
};
