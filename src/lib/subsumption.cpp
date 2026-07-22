#include "subsumption.hpp"
#include "cnf.hpp"

namespace
{
static std::optional<Substitution> matchTerm(const Term &pattern, const Term &subject,
                                             Substitution sigma)
{
    if (auto *v = std::get_if<Variable>(&pattern))
    {
        auto it = sigma.find(*v);
        if (it != sigma.end())
            return it->second == subject ? std::make_optional(sigma) : std::nullopt;
        sigma[*v] = subject;
        return sigma;
    }
    if (std::get_if<Variable>(&subject))
        return std::nullopt;
    const auto &f = *std::get<FunctionApplicationRef>(pattern);
    const auto &g = *std::get<FunctionApplicationRef>(subject);
    if (f.symbol != g.symbol)
        return std::nullopt;
    for (size_t i = 0; i < f.arguments.size(); i++)
    {
        auto r = matchTerm(f.arguments[i], g.arguments[i], sigma);
        if (!r)
            return std::nullopt;
        sigma = std::move(*r);
    }
    return sigma;
}

static bool subsumesHelper(const std::vector<Literal> &aLits, std::size_t idx,
                           const std::vector<Literal> &cLits, std::vector<bool> &used,
                           Substitution sigma)
{
    if (idx == aLits.size())
        return true;
    const Literal &aLit = aLits[idx];
    for (std::size_t j = 0; j < static_cast<std::size_t>(cLits.size()); j++)
    {
        if (used[j] || cLits[j].positive != aLit.positive)
            continue;
        for (int swap = 0; swap < 2; swap++)
        {
            const Term &pl = swap ? aLit.right : aLit.left;
            const Term &pr = swap ? aLit.left : aLit.right;
            auto s = matchTerm(pl, cLits[j].left, sigma);
            if (!s)
                continue;
            s = matchTerm(pr, cLits[j].right, *s);
            if (!s)
                continue;
            used[j] = true;
            if (subsumesHelper(aLits, idx + 1, cLits, used, *s))
                return true;
            used[j] = false;
        }
    }
    return false;
}

} // namespace

bool subsumes(const Clause &A, const Clause &C)
{
    if (A.literals.size() > C.literals.size())
        return false;
    std::vector<Literal> aLits(A.literals.begin(), A.literals.end());
    std::vector<Literal> cLits(C.literals.begin(), C.literals.end());
    std::vector<bool> used(cLits.size(), false);
    return subsumesHelper(aLits, 0, cLits, used, {});
}
