#include "discrimination_tree.hpp"

namespace
{
void linearizeInto(const Term &t, std::vector<DiscrKey> &out)
{
    if (std::holds_alternative<Variable>(t))
    {
        out.push_back(DiscrKey{DiscrKeyKind::Star, {}});
        return;
    }
    const auto &f = *std::get<FunctionApplicationRef>(t);
    out.push_back(DiscrKey{DiscrKeyKind::App, f.symbol});
    for (const auto &arg : f.arguments)
        linearizeInto(arg, out);
}
} // namespace

std::vector<DiscrKey> linearize(const Term &t)
{
    std::vector<DiscrKey> out;
    linearizeInto(t, out);
    return out;
}

std::size_t skipSubtree(const std::vector<DiscrKey> &tokens, std::size_t pos)
{
    if (tokens[pos].kind == DiscrKeyKind::Star)
        return pos + 1;

    std::size_t toSkip = static_cast<std::size_t>(tokens[pos].symbol.arity);
    ++pos;
    while (toSkip != 0)
    {
        if (tokens[pos].kind == DiscrKeyKind::Star)
            --toSkip;
        else
            toSkip = toSkip + static_cast<std::size_t>(tokens[pos].symbol.arity) - 1;
        ++pos;
    }
    return pos;
}
