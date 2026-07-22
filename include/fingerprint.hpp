#pragma once
#include "terms.hpp"
#include <compare>

enum class FeatureKind
{
    Symbol,
    Star,
    AncestorVar,
    Below
};

struct Feature
{
    FeatureKind kind;
    FunctionSymbol symbol; // for the kind == FeatureKind::Symbol cases

    std::strong_ordering operator<=>(const Feature &other) const
    {
        if (auto byKind = kind <=> other.kind; byKind != 0)
            return byKind;
        if (kind == FeatureKind::Symbol)
            return symbol <=> other.symbol;
        return std::strong_ordering::equal;
    }
    bool operator==(const Feature &other) const
    {
        if (kind != other.kind)
            return false;
        if (kind == FeatureKind::Symbol)
            return symbol == other.symbol;
        return true;
    }
};

using Fingerprint = std::vector<Feature>;

// set of sample positions used to compute all fingerprints
const std::vector<Position> &fingerprintSamplePositions();

Fingerprint computeFingerprint(const Term &t);

// overapproximation of unifiable features, (=not allowed to return false for unifiable ones)
bool featuresCompatible(const Feature &a, const Feature &b);
bool fingerprintsCompatible(const Fingerprint &indexed, const Fingerprint &query);

template <class Entry> class FingerprintIndex
{
  public:
    void insert(const Term &t, Entry entry)
    {
        Fingerprint fp = computeFingerprint(t);
        Node *cur = &root_;
        for (const auto &feat : fp)
        {
            auto &child = cur->children[feat];
            if (!child)
                child = std::make_unique<Node>();
            cur = child.get();
        }
        cur->entries.push_back(std::move(entry));
    }
    std::vector<Entry> candidates(const Term &query) const
    {
        std::vector<Entry> result;
        Fingerprint qfp = computeFingerprint(query);
        collect(&root_, qfp, 0, result);
        return result;
    }

  private:
    struct Node
    {
        std::vector<Entry> entries;
        std::map<Feature, std::unique_ptr<Node>> children;
    };

    static void collect(const Node *node, const Fingerprint &qfp, std::size_t depth,
                        std::vector<Entry> &out)
    {
        if (depth == qfp.size())
        {
            out.insert(out.end(), node->entries.begin(), node->entries.end());
            return;
        }
        for (const auto &[feat, child] : node->children)
            if (featuresCompatible(feat, qfp[depth]))
                collect(child.get(), qfp, depth + 1, out);
    }

    Node root_;
};
