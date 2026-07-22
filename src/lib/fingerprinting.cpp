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
