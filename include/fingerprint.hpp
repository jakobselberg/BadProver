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

bool featuresCompatible(const Feature &a, const Feature &b);
bool fingerprintsCompatible(const Fingerprint &indexed, const Fingerprint &query);
