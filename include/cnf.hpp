#pragma once
#include "terms.hpp"

#include <optional>
#include <stdexcept>
#include <utility>

enum class SymbolKind
{
    Function,
    Predicate,
};

// Records the symbols occurring in one problem.  Functions return
// individuals, predicates return booleans, and every argument must be an
// individual.  A name may not be used as both kinds of symbol (or at two
// arities).
class Signature
{
  public:
    struct SymbolDeclaration
    {
        std::string name;
        SymbolKind kind;
        int arity;
    };

    Signature();

    std::optional<SymbolKind> lookup(const std::string &name) const;
    std::vector<SymbolDeclaration> declarations() const;
    Term applyFunction(std::string name, std::vector<Term> arguments);
    Term applyPredicate(std::string name, std::vector<Term> arguments);

  private:
    struct Entry
    {
        SymbolKind kind;
        int arity;
    };
    std::map<std::string, Entry> symbols_;

    Term apply(SymbolKind kind, std::string name, std::vector<Term> arguments);
};

struct Literal
{
    Term left;
    Term right;
    bool positive = true;

    Literal(Term left, Term right, bool positive = true)
        : left(std::move(left)), right(std::move(right)), positive(positive)
    {
        if (termType(this->left) != termType(this->right))
            throw std::invalid_argument("both sides of an equality must have the same type");
    }

    // Lexicographic ordering for use in sets
    auto operator<=>(const Literal &other) const = default;
    bool operator==(const Literal &other) const = default;
};

struct Clause
{
    int id;
    std::set<Literal> literals;
};

Literal makeLiteral(Term left, Term right, bool positive);
Literal negateLiteral(const Literal &lit);
// A clause containing a reflexive equality (s = s) or complementary literals (p and ~p)
bool isTautology(const Clause &c);
// Apply substitution to a literal
Literal applySubstitution(const Substitution &substitution, const Literal &lit);
// Get all free variables in a literal
std::set<Variable> FreeVariables(const Literal &lit);

Clause makeClause(int id, std::set<Literal> lits);
void addLiteralToClause(Clause &c, const Literal &lit);
void removeLiteralFromClause(Clause &c, const Literal &lit);
// Apply substitution to a clause
Clause applySubstitution(const Substitution &substitution, const Clause &c);
// Get all free variables in a clause
std::set<Variable> FreeVariables(const Clause &c);
