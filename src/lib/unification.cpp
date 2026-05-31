// unification.cpp
#include "unification.hpp"

namespace
{
bool occursIn(const Variable &x, const Term &t)
{
    if (auto *v = std::get_if<Variable>(&t))
        return *v == x;
    const auto &f = *std::get<std::shared_ptr<const FunctionApplication>>(t);
    for (const auto &arg : f.arguments)
        if (occursIn(x, arg))
            return true;
    return false;
}
} // namespace

std::optional<Substitution> mgu(std::vector<std::pair<Term, Term>> equations)
{
    Substitution sigma;
    while (!equations.empty())
    {
        auto [s, t] = std::move(equations.back());
        equations.pop_back();

        const auto *sv = std::get_if<Variable>(&s);
        const auto *tv = std::get_if<Variable>(&t);

        if (sv && tv && *sv == *tv)
            continue; // delete

        if (sv)
        { // eliminate
            if (occursIn(*sv, t))
                return std::nullopt;
            Substitution single{{*sv, t}};
            for (auto &[a, b] : equations)
            {
                a = applySubstitution(single, a);
                b = applySubstitution(single, b);
            }
            for (auto &[k, v] : sigma)
                v = applySubstitution(single, v);
            sigma[*sv] = std::move(t);
            continue;
        }

        if (tv)
        { // orient
            equations.emplace_back(std::move(t), std::move(s));
            continue;
        }

        const auto &f = *std::get<std::shared_ptr<const FunctionApplication>>(s);
        const auto &g = *std::get<std::shared_ptr<const FunctionApplication>>(t);
        if (f.symbol.name != g.symbol.name || f.symbol.arity != g.symbol.arity)
            return std::nullopt; // clash

        for (std::size_t i = 0; i < f.arguments.size(); ++i)
            equations.emplace_back(f.arguments[i], g.arguments[i]);
    }
    return sigma;
}

std::optional<Substitution> mgu(const Term &t, const Term &u)
{
    return mgu(std::vector<std::pair<Term, Term>>{{t, u}});
}
