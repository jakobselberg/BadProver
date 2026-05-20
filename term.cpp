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
    if (auto v = std::get_if<Variable>(&t))
        return {*v};
    const auto &f = *std::get<std::unique_ptr<FunctionApplication>>(t);
    std::set<Variable> result;
    for (const auto &arg : f.arguments)
    {
        auto sub = FreeVariables(arg);
        result.merge(sub);
    }
    return result;
}