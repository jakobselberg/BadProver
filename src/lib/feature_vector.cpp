#include "feature_vector.hpp"

namespace
{
constexpr int CPLUS = 0;
constexpr int CMINUS = 1;
constexpr int CPLUS_CATCHALL = 2;
constexpr int CPLUS_FUNC_START = 3;
constexpr int CPLUS_FUNC_SIZE = 6;
constexpr int CMINUS_CATCHALL = 9;
constexpr int CMINUS_FUNC_START = 10;
constexpr int CMINUS_FUNC_SIZE = 6;

void countSymbols(const Term &t, SymbolIndex &symbols, FeatureVector &fv, int catchallIdx,
                  int funcStart, int funcSize)
{
    if (std::holds_alternative<Variable>(t))
        return;
    const auto &f = *std::get<FunctionApplicationRef>(t);
    int idx = symbols.indexOf(f.symbol);
    if (idx < funcSize)
        fv[static_cast<std::size_t>(funcStart + idx)] += 1;
    else
        fv[static_cast<std::size_t>(catchallIdx)] += 1;
    for (const auto &arg : f.arguments)
        countSymbols(arg, symbols, fv, catchallIdx, funcStart, funcSize);
}
} // namespace

FeatureVector computeFeatureVector(const Clause &c, SymbolIndex &symbols)
{
    FeatureVector fv{};
    for (const auto &lit : c.literals)
    {
        if (lit.positive)
        {
            fv[CPLUS] += 1;
            countSymbols(lit.left, symbols, fv, CPLUS_CATCHALL, CPLUS_FUNC_START, CPLUS_FUNC_SIZE);
            countSymbols(lit.right, symbols, fv, CPLUS_CATCHALL, CPLUS_FUNC_START, CPLUS_FUNC_SIZE);
        }
        else
        {
            fv[CMINUS] += 1;
            countSymbols(lit.left, symbols, fv, CMINUS_CATCHALL, CMINUS_FUNC_START,
                        CMINUS_FUNC_SIZE);
            countSymbols(lit.right, symbols, fv, CMINUS_CATCHALL, CMINUS_FUNC_START,
                        CMINUS_FUNC_SIZE);
        }
    }
    return fv;
}
