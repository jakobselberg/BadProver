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

using Substitution = std::map<Variable, Term>;

Term substitute(const Substitution &substitution, const Term &t)
{
}
