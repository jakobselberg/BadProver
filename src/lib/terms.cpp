#include "terms.hpp"

bool FunctionApplicationRef::operator==(const FunctionApplicationRef &other) const
{
    if (ptr == other.ptr)
        return true;
    if (!ptr || !other.ptr)
        return false;
    return *ptr == *other.ptr;
}

std::strong_ordering FunctionApplicationRef::operator<=>(const FunctionApplicationRef &other) const
{
    if (ptr == other.ptr)
        return std::strong_ordering::equal;
    if (!ptr)
        return std::strong_ordering::less;
    if (!other.ptr)
        return std::strong_ordering::greater;
    return *ptr <=> *other.ptr;
}

Term makeFunctionApplication(FunctionSymbol symbol, std::vector<Term> arguments)
{
    return FunctionApplicationRef{std::make_shared<const FunctionApplication>(
        FunctionApplication{std::move(symbol), std::move(arguments)})};
};

std::set<Variable> GetFreeVariables(const Term &t)
{
    if (auto v = std::get_if<Variable>(&t))
        return {*v};
    const auto &f = *std::get<FunctionApplicationRef>(t);
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
    const auto &f = *std::get<FunctionApplicationRef>(t);
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
    Substitution result = second;
    for (const auto &[x, t] : first)
    {
        Term t2 = applySubstitution(second, t);
        // drop trivial identity bindings
        if (auto *v = std::get_if<Variable>(&t2); v && *v == x)
            result.erase(x);
        else
            result[x] = std::move(t2);
    }
    return result;
};
