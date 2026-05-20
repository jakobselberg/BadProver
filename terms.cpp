#include "terms.hpp"

Term makeApp(FunctionSymbol symbol, std::vector<Term> arguments)
{
    return std::make_shared<const FunctionApplication>(
        FunctionApplication{std::move(symbol), std::move(arguments)});
};

std::set<Variable> FreeVariables(const Term &t)
{
    if (auto v = std::get_if<Variable>(&t))
        return {*v};
    const auto &f = *std::get<std::shared_ptr<const FunctionApplication>>(t);
    std::set<Variable> result;
    for (const auto &arg : f.arguments)
    {
        auto sub = FreeVariables(arg);
        result.merge(sub);
    }
    return result;
};
