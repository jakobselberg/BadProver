#include <string>
#include <variant>
#include <vector>
#include <memory>
#include <set>

struct Variable
{
    std::string name;
    auto operator<=>(const Variable &) const = default;
    bool operator==(const Variable &) const = default;
};

struct FunctionApplication;

using Term = std::variant<Variable, std::unique_ptr<FunctionApplication>>;

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

std::set<Variable> FreeVariables(const Term &t)
{
}