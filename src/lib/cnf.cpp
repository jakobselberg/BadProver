#include "cnf.hpp"

// Literals
Literal makeLiteral(Term left, Term right, bool positive)
{
    return Literal{left, right, positive};
}

Literal negateLiteral(const Literal &lit)
{
    return Literal{lit.left, lit.right, !lit.positive};
}

Literal applySubstitution(const Substitution &substitution, const Literal &lit)
{
    return Literal{::applySubstitution(substitution, lit.left),
                   ::applySubstitution(substitution, lit.right), lit.positive};
}

std::set<Variable> FreeVariables(const Literal &lit)
{
    auto left_vars = GetFreeVariables(lit.left);
    auto right_vars = GetFreeVariables(lit.right);
    left_vars.merge(right_vars);
    return left_vars;
}

// Clauses
Clause makeClause(int id, std::set<Literal> lits)
{
    Clause c(id);
    c.literals = std::move(lits);
    return c;
}

void addLiteralToClause(Clause &c, const Literal &lit)
{
    c.literals.insert(lit);
}

void removeLiteralFromClause(Clause &c, const Literal &lit)
{
    c.literals.erase(lit);
}

Clause applySubstitution(const Substitution &substitution, const Clause &c)
{
    Clause result(c.id);
    for (const auto &lit : c.literals)
    {
        result.literals.insert(::applySubstitution(substitution, lit));
    }
    return result;
}

std::set<Variable> FreeVariables(const Clause &c)
{
    std::set<Variable> result;
    for (const auto &lit : c.literals)
    {
        auto lit_vars = FreeVariables(lit);
        result.merge(lit_vars);
    }
    return result;
}
