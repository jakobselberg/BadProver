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

// The two sorts used by the untyped TPTP fragment.  Variables and ordinary
// function applications denote individuals; predicate applications denote
// booleans.
enum class TermType
{
    Individual,
    Boolean,
};

struct FunctionSymbol
{
    int arity;
    std::string name;
    TermType resultType = TermType::Individual;

    // A well-formed signature never assigns two result types to the same
    // symbol.  Keeping the sort out of structural identity preserves the
    // existing syntactic identity of terms while the Signature enforces that
    // invariant at construction time.
    auto operator<=>(const FunctionSymbol &other) const
    {
        if (auto byArity = arity <=> other.arity; byArity != 0)
            return byArity;
        return name <=> other.name;
    }
    bool operator==(const FunctionSymbol &other) const
    {
        return arity == other.arity && name == other.name;
    }
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
TermType termType(const Term &t);

using Substitution = std::map<Variable, Term>;
using Position = std::vector<int>;

std::optional<Term> getSubtermAt(const Term &t, const Position &pos);
std::optional<Term> setSubtermAt(const Term &t, const Position &pos, const Term &replacement);
std::vector<Position> allSubtermPositions(const Term &t);

Term applySubstitution(const Substitution &substitution, const Term &t);

std::set<Variable> GetFreeVariables(const Term &t);

Substitution composeSubstitutions(const Substitution &first, const Substitution &second);
