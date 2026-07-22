#include "fingerprint.hpp"

#include <variant>

namespace
{
Feature featureAt(const Term &t, const Position &pos)
{
    const Term *cur = &t;
    for (int idx : pos)
    {
        if (std::holds_alternative<Variable>(*cur))
            return Feature{FeatureKind::AncestorVar, {}};

        const auto &f = *std::get<FunctionApplicationRef>(*cur);
        if (idx < 0 || idx >= static_cast<int>(f.arguments.size()))
            return Feature{FeatureKind::Below, {}};

        cur = &f.arguments[static_cast<std::size_t>(idx)];
    }

    if (std::holds_alternative<Variable>(*cur))
        return Feature{FeatureKind::Star, {}};
    return Feature{FeatureKind::Symbol, std::get<FunctionApplicationRef>(*cur)->symbol};
}

} // namespace

const std::vector<Position> &fingerprintSamplePositions()
{
    // right now using root, all first three args, and their first 2 children
    static const std::vector<Position> positions = {
        {},                                             // root
        {0},    {1},    {2},                            // first 3 root args
        {0, 0}, {0, 1}, {1, 0}, {1, 1}, {2, 0}, {2, 1}, // their first 2 children
    };
    return positions;
}

Fingerprint computeFingerprint(const Term &t)
{
    const auto &positions = fingerprintSamplePositions();
    Fingerprint fp;
    fp.reserve(positions.size());
    for (const auto &pos : positions)
        fp.push_back(featureAt(t, pos));
    return fp;
}

bool featuresCompatible(const Feature &a, const Feature &b)
{
    if (a.kind == FeatureKind::Symbol && b.kind == FeatureKind::Symbol)
        return a.symbol == b.symbol;
    if (a.kind == FeatureKind::Below &&
        (b.kind == FeatureKind::Symbol || b.kind == FeatureKind::Star))
        return false;
    if (b.kind == FeatureKind::Below &&
        (a.kind == FeatureKind::Symbol || a.kind == FeatureKind::Star))
        return false;
    return true;
}

bool fingerPrintsCompatible(const Fingerprint &indexed, const Fingerprint &query)
{
    if (indexed.size() != query.size())
        return false;
    for (std::size_t i = 0; i < indexed.size(); ++i)
        if (!featuresCompatible(indexed[i], query[i]))
            return false;
    return true;
}
