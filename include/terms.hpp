#pragma once
#include <map>
#include <memory>
#include <set>
#include <string>
#include <variant>
#include <vector>

struct Variable
{
    std::string name;
    auto operator<=>(const Variable &) const = default;
    bool operator==(const Variable &) const = default;
};

struct FunctionApplication;
using Term = std::variant<Variable, std::shared_ptr<const FunctionApplication>>;

struct FunctionSymbol
{
    int arity;
    std::string name;
};
struct FunctionApplication
{
    FunctionSymbol symbol;
    std::vector<Term> arguments;
};

Term makeFunctionApplication(FunctionSymbol symbol, std::vector<Term> arguments);

using Substitution = std::map<Variable, Term>;
Term applySubstitution(const Substitution &substitution, const Term &t);

std::set<Variable> GetFreeVariables(const Term &t);

Substitution composeSubstitutions(const Substitution &first, const Substitution &second);
