#include "ordering.hpp"
#include <map>
#include <variant>
#include <vector>

namespace
{
int termWeight(const Term &t)
{
    if (std::holds_alternative<Variable>(t))
        return 1;
    const auto &app = *std::get<FunctionApplicationRef>(t);
    int w = 1;
    for (const auto &arg : app.arguments)
        w += termWeight(arg);
    return w;
}

void collectVariableCounts(const Term &t, std::map<Variable, int> &counts)
{
    if (const auto *v = std::get_if<Variable>(&t))
    {
        counts[*v] += 1;
        return;
    }
    const auto &app = *std::get<FunctionApplicationRef>(t);
    for (const auto &arg : app.arguments)
        collectVariableCounts(arg, counts);
};

// does 'super' contains at least as many occurences of every variable as 'sub'?
bool variablesDominate(const std::map<Variable, int> &super, const std::map<Variable, int> &sub)
{
    for (const auto &[v, n] : sub)
    {
        auto it = super.find(v);
        const int have = (it == super.end()) ? 0 : it->second;
        if (have < n)
            return false;
    }
    return true;
}

int comparePrecedence(const FunctionSymbol &f, const FunctionSymbol &g)
{
    if (f.arity != g.arity)
        return f.arity < g.arity ? -1 : 1;
    if (f.name != g.name)
        return f.name < g.name ? -1 : 1;
    return 0;
}

Comparison kboCompare(const Term &s, const Term &t)
{
    std::map<Variable, int> sCounts;
    std::map<Variable, int> tCounts;
    collectVariableCounts(s, sCounts);
    collectVariableCounts(t, tCounts);

    const bool sDominates = variablesDominate(sCounts, tCounts);
    const bool tDominates = variablesDominate(tCounts, sCounts);

    const int ws = termWeight(s);
    const int wt = termWeight(t);

    if (ws > wt)
        return sDominates ? Comparison::Greater : Comparison::Incomparable;
    if (ws < wt)
        return tDominates ? Comparison::Less : Comparison::Incomparable;

    // equal weight

    const bool sVar = std::holds_alternative<Variable>(s);
    const bool tVar = std::holds_alternative<Variable>(t);
    if (sVar || tVar)
    {
        if (sVar && tVar)
            return std::get<Variable>(s) == std::get<Variable>(t) ? Comparison::Equal
                                                                  : Comparison::Incomparable;
        return Comparison::Incomparable;
    }

    const auto &fs = *std::get<FunctionApplicationRef>(s);
    const auto &ft = *std::get<FunctionApplicationRef>(t);

    const int prec = comparePrecedence(fs.symbol, ft.symbol);
    if (prec > 0)
        return sDominates ? Comparison::Greater : Comparison::Incomparable;
    if (prec < 0)
        return tDominates ? Comparison::Less : Comparison::Incomparable;

    // same function symbol
    for (std::size_t i = 0; i < fs.arguments.size(); i++)
    {
        const Comparison c = kboCompare(fs.arguments[i], ft.arguments[i]);
        if (c == Comparison::Equal)
            continue;
        if (c == Comparison::Greater)
            return sDominates ? Comparison::Greater : Comparison::Incomparable;
        if (c == Comparison::Less)
            return tDominates ? Comparison::Less : Comparison::Incomparable;
        return Comparison::Incomparable;
    }
    return Comparison::Equal;
};

} // namespace
