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
