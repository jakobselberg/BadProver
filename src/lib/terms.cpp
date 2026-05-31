#include "terms.hpp"

Term makeFunctionApplication(FunctionSymbol symbol, std::vector<Term> arguments)
{
    return std::make_shared<const FunctionApplication>(
        FunctionApplication{std::move(symbol), std::move(arguments)});
};

std::set<Variable> GetFreeVariables(const Term &t)
{
    if (auto v = std::get_if<Variable>(&t))
        return {*v};
    const auto &f = *std::get<std::shared_ptr<const FunctionApplication>>(t);
    std::set<Variable> result;
    for (const auto &arg : f.arguments)
    {
        auto sub = GetFreeVariables(arg);
        result.merge(sub);
    }
    return result;
};

Term applySubstitution(const Substitution &substitution, const Term &t)
{
    if (auto v = std::get_if<Variable>(&t))
    {
        auto substitutionIterator = substitution.find(*v);
        if (substitutionIterator != substitution.end())
        {
            return substitutionIterator->second;
        }
        return t;
    }
    const auto &f = *std::get<std::shared_ptr<const FunctionApplication>>(t);
    std::vector<Term> substitutedArguments;
    substitutedArguments.reserve(f.arguments.size());
    for (const auto &arg : f.arguments)
    {
        substitutedArguments.push_back(applySubstitution(substitution, arg));
    }

    return makeFunctionApplication(f.symbol, std::move(substitutedArguments));
};

Substitution composeSubstitutions(const Substitution &first, const Substitution &second)
{
    return first;
};
