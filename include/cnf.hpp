#include "terms.hpp"

struct Literal
{
    Term left;
    Term right;
    bool positive = true;

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
