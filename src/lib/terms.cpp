#include "terms.hpp"

#include <stdexcept>

namespace
{
void validateSubstitution(const Substitution &substitution)
{
    for (const auto &[variable, term] : substitution)
    {
        (void)variable;
        if (termType(term) != TermType::Individual)
            throw std::invalid_argument("a variable cannot be substituted by a Boolean term");
    }
}
} // namespace

bool FunctionApplicationRef::operator==(const FunctionApplicationRef &other) const
{
    if (ptr == other.ptr)
        return true;
    if (!ptr || !other.ptr)
        return false;
    return *ptr == *other.ptr;
}

std::strong_ordering FunctionApplicationRef::operator<=>(const FunctionApplicationRef &other) const
{
    if (ptr == other.ptr)
        return std::strong_ordering::equal;
    if (!ptr)
        return std::strong_ordering::less;
    if (!other.ptr)
        return std::strong_ordering::greater;
    return *ptr <=> *other.ptr;
}

Term makeFunctionApplication(FunctionSymbol symbol, std::vector<Term> arguments)
{
    if (symbol.arity != static_cast<int>(arguments.size()))
        throw std::invalid_argument("function application has the wrong number of arguments");
    for (const Term &argument : arguments)
    {
        if (termType(argument) != TermType::Individual)
            throw std::invalid_argument("a function or predicate argument must have individual type");
    }
    return FunctionApplicationRef{std::make_shared<const FunctionApplication>(
        FunctionApplication{std::move(symbol), std::move(arguments)})};
};

std::set<Variable> GetFreeVariables(const Term &t)
{
    if (auto v = std::get_if<Variable>(&t))
        return {*v};
    const auto &f = *std::get<FunctionApplicationRef>(t);
    std::set<Variable> result;
    for (const auto &arg : f.arguments)
    {
        auto sub = GetFreeVariables(arg);
        result.merge(sub);
    }
    return result;
};

namespace
{
// assumes substitution has already been validated by the public entry point
Term applySubstitutionUnchecked(const Substitution &substitution, const Term &t)
{
    if (auto v = std::get_if<Variable>(&t))
    {
        auto substitutionIterator = substitution.find(*v);
        if (substitutionIterator != substitution.end())
        {
            return substitutionIterator->second;
        }
        return t;
    }
    const auto &f = *std::get<FunctionApplicationRef>(t);
    std::vector<Term> substitutedArguments;
    substitutedArguments.reserve(f.arguments.size());
    bool changed = false;
    for (const auto &arg : f.arguments)
    {
        Term substituted = applySubstitutionUnchecked(substitution, arg);
        if (!(substituted == arg))
            changed = true;
        substitutedArguments.push_back(std::move(substituted));
    }
    // nothing below this node changed: share the original instead of rebuilding it
    if (!changed)
        return t;

    return makeFunctionApplication(f.symbol, std::move(substitutedArguments));
}
} // namespace

Term applySubstitution(const Substitution &substitution, const Term &t)
{
    validateSubstitution(substitution);
    return applySubstitutionUnchecked(substitution, t);
};

Substitution composeSubstitutions(const Substitution &first, const Substitution &second)
{
    validateSubstitution(first);
    validateSubstitution(second);
    Substitution result = second;
    for (const auto &[x, t] : first)
    {
        Term t2 = applySubstitutionUnchecked(second, t);
        // drop trivial identity bindings
        if (auto *v = std::get_if<Variable>(&t2); v && *v == x)
            result.erase(x);
        else
            result[x] = std::move(t2);
    }
    return result;
}

TermType termType(const Term &t)
{
    if (std::holds_alternative<Variable>(t))
        return TermType::Individual;
    return std::get<FunctionApplicationRef>(t)->symbol.resultType;
}

std::optional<Term> getSubtermAt(const Term &t, const Position &pos)
{
    if (pos.empty())
        return t;

    if (std::get_if<Variable>(&t))
        return std::nullopt;

    const auto &f = *std::get<FunctionApplicationRef>(t);
    int idx = pos[0];
    if (idx < 0 || idx >= static_cast<int>(f.arguments.size()))
        return std::nullopt;

    Position tail(pos.begin() + 1, pos.end());
    return getSubtermAt(f.arguments[static_cast<std::size_t>(idx)], tail);
}

std::optional<Term> setSubtermAt(const Term &t, const Position &pos, const Term &replacement)
{
    if (pos.empty())
    {
        if (termType(t) != termType(replacement))
            return std::nullopt;
        return replacement;
    }

    if (std::get_if<Variable>(&t))
        return std::nullopt;

    const auto &f = *std::get<FunctionApplicationRef>(t);
    int idx = pos[0];
    if (idx < 0 || idx >= static_cast<int>(f.arguments.size()))
        return std::nullopt;

    Position tail(pos.begin() + 1, pos.end());
    auto subterm = setSubtermAt(f.arguments[static_cast<std::size_t>(idx)], tail, replacement);
    if (!subterm)
        return std::nullopt;

    std::vector<Term> newArgs = f.arguments;
    newArgs[static_cast<std::size_t>(idx)] = *subterm;
    return makeFunctionApplication(f.symbol, std::move(newArgs));
}

static void allSubtermPositionsImpl(const Term &t, Position prefix, std::vector<Position> &acc)
{
    acc.push_back(prefix);
    if (std::get_if<Variable>(&t))
        return;

    const auto &f = *std::get<FunctionApplicationRef>(t);
    for (std::size_t i = 0; i < f.arguments.size(); ++i)
    {
        Position childPrefix = prefix;
        childPrefix.push_back(static_cast<int>(i));
        allSubtermPositionsImpl(f.arguments[i], std::move(childPrefix), acc);
    }
}

std::vector<Position> allSubtermPositions(const Term &t)
{
    std::vector<Position> result;
    allSubtermPositionsImpl(t, {}, result);
    return result;
}

static void allSubtermsWithPositionsImpl(const Term &t, Position prefix,
                                         std::vector<std::pair<Position, Term>> &acc)
{
    // pre-order, matching allSubtermPositions: parent before children
    Position ownPrefix = prefix;
    acc.emplace_back(std::move(ownPrefix), t);
    if (std::get_if<Variable>(&t))
        return;

    const auto &f = *std::get<FunctionApplicationRef>(t);
    for (std::size_t i = 0; i < f.arguments.size(); ++i)
    {
        Position childPrefix = prefix;
        childPrefix.push_back(static_cast<int>(i));
        allSubtermsWithPositionsImpl(f.arguments[i], std::move(childPrefix), acc);
    }
}

std::vector<std::pair<Position, Term>> allSubtermsWithPositions(const Term &t)
{
    std::vector<std::pair<Position, Term>> result;
    allSubtermsWithPositionsImpl(t, {}, result);
    return result;
}

int termWeight(const Term &t)
{
    if (std::holds_alternative<Variable>(t))
        return 1;
    const auto &f = *std::get<FunctionApplicationRef>(t);
    int w = 1;
    for (const auto &arg : f.arguments)
        w += termWeight(arg);
    return w;
}
