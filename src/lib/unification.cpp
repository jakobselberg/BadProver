// unification.cpp
#include "unification.hpp"

namespace
{
bool occursIn(const Variable &x, const Term &t)
{
    if (auto *v = std::get_if<Variable>(&t))
        return *v == x;
    const auto &f = *std::get<FunctionApplicationRef>(t);
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

        // Variables are individuals.  Therefore no unifier may relate an
        // individual term and a Boolean predicate term.
        if (termType(s) != termType(t))
            return std::nullopt;

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

        const auto &f = *std::get<FunctionApplicationRef>(s);
        const auto &g = *std::get<FunctionApplicationRef>(t);
        if (f.symbol != g.symbol)
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

std::optional<Substitution> matchTerm(const Term &pattern, const Term &target, Substitution start)
{
    Substitution sigma = std::move(start);
    std::vector<std::pair<Term, Term>> worklist{{pattern, target}};
    while (!worklist.empty())
    {
        auto [p, t] = std::move(worklist.back());
        worklist.pop_back();

        if (termType(p) != termType(t))
            return std::nullopt;

        if (const auto *pv = std::get_if<Variable>(&p))
        {
            auto it = sigma.find(*pv);
            if (it != sigma.end())
            {
                if (it->second != t)
                    return std::nullopt;
            }
            else
            {
                sigma[*pv] = t;
            }
            continue;
        }

        if (std::holds_alternative<Variable>(t))
            return std::nullopt;

        const auto &pf = *std::get<FunctionApplicationRef>(p);
        const auto &tf = *std::get<FunctionApplicationRef>(t);
        if (pf.symbol != tf.symbol)
            return std::nullopt;

        for (std::size_t i = 0; i < pf.arguments.size(); ++i)
            worklist.emplace_back(pf.arguments[i], tf.arguments[i]);
    }
    return sigma;
}
