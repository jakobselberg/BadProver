#include "cnf.hpp"

#include <stdexcept>

Signature::Signature()
{
    // $true is the Boolean value used to reify predicate literals.
    symbols_.emplace("$true", Entry{SymbolKind::Predicate, 0});
}

std::optional<SymbolKind> Signature::lookup(const std::string &name) const
{
    auto it = symbols_.find(name);
    if (it == symbols_.end())
        return std::nullopt;
    return it->second.kind;
}

std::vector<Signature::SymbolDeclaration> Signature::declarations() const
{
    std::vector<SymbolDeclaration> result;
    result.reserve(symbols_.size());
    for (const auto &[name, entry] : symbols_)
        result.push_back(SymbolDeclaration{name, entry.kind, entry.arity});
    return result;
}

Term Signature::applyFunction(std::string name, std::vector<Term> arguments)
{
    return apply(SymbolKind::Function, std::move(name), std::move(arguments));
}

Term Signature::applyPredicate(std::string name, std::vector<Term> arguments)
{
    return apply(SymbolKind::Predicate, std::move(name), std::move(arguments));
}

Term Signature::apply(SymbolKind kind, std::string name, std::vector<Term> arguments)
{
    const int arity = static_cast<int>(arguments.size());
    for (const Term &argument : arguments)
    {
        if (termType(argument) != TermType::Individual)
            throw std::invalid_argument("a symbol argument must have individual type");
    }

    auto [it, inserted] = symbols_.emplace(name, Entry{kind, arity});
    if (!inserted && (it->second.kind != kind || it->second.arity != arity))
        throw std::invalid_argument("inconsistent use of symbol '" + name + "'");

    TermType resultType = kind == SymbolKind::Function ? TermType::Individual : TermType::Boolean;
    return makeFunctionApplication(FunctionSymbol{arity, std::move(name), resultType},
                                   std::move(arguments));
}

// Literals
Literal makeLiteral(Term left, Term right, bool positive)
{
    return Literal{std::move(left), std::move(right), positive};
}

Literal negateLiteral(const Literal &lit)
{
    return Literal{lit.left, lit.right, !lit.positive};
}

bool isTautology(const Clause &c)
{
    for (const auto &lit : c.literals)
    {
        if (c.literals.contains(negateLiteral(lit)))
            return true;
        if (lit.positive && lit.left == lit.right)
            return true;
    }
    return false;
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
    return Clause{id, std::move(lits)};
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
    Clause result{c.id, {}};
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
