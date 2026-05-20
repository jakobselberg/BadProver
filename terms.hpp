#pragma once
#include <string>
#include <variant>
#include <vector>
#include <memory>
#include <set>
#include <map>

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

using Substitution = std::map<Variable, Term>;

std::set<Variable> FreeVariables(const Term &t);
Term makeApp(FunctionSymbol symbol, std::vector<Term> arguments);