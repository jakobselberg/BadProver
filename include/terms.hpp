#pragma once
#include <compare>
#include <map>
#include <memory>
#include <optional>
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

struct FunctionSymbol
{
    int arity;
    std::string name;
    auto operator<=>(const FunctionSymbol &) const = default;
    bool operator==(const FunctionSymbol &) const = default;
};

struct FunctionApplication;

// A wrapper around the underlying FunctionApplication,
// that allows us to implement structural equality comparison between Terms
struct FunctionApplicationRef
{
    std::shared_ptr<const FunctionApplication> ptr;

    const FunctionApplication &operator*() const
    {
        return *ptr;
    }
    const FunctionApplication *operator->() const
    {
        return ptr.get();
    }

    bool operator==(const FunctionApplicationRef &other) const;
    std::strong_ordering operator<=>(const FunctionApplicationRef &other) const;
};

using Term = std::variant<Variable, FunctionApplicationRef>;

struct FunctionApplication
{
    FunctionSymbol symbol;
    std::vector<Term> arguments;
    auto operator<=>(const FunctionApplication &) const = default;
    bool operator==(const FunctionApplication &) const = default;
};

Term makeFunctionApplication(FunctionSymbol symbol, std::vector<Term> arguments);

using Substitution = std::map<Variable, Term>;
using Position = std::vector<int>;

std::optional<Term> getSubtermAt(const Term &t, const Position &pos);
std::optional<Term> setSubtermAt(const Term &t, const Position &pos, const Term &replacement);
std::vector<Position> allSubtermPositions(const Term &t);

Term applySubstitution(const Substitution &substitution, const Term &t);

std::set<Variable> GetFreeVariables(const Term &t);

Substitution composeSubstitutions(const Substitution &first, const Substitution &second);
