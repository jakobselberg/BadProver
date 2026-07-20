#include "selection.hpp"

namespace
{

int termWeight(const Term &t)
{
    if (std::holds_alternative<Variable>(t))
    {
        return 1;
    }
    const auto &app = std::get<FunctionApplicationRef>(t);
    int w = 1;
    for (const auto &arg : app->arguments)
    {
        w += termWeight(arg);
    }
    return w;
}
} // namespace

int clauseWeight(const Clause &c)
{
    int total = 0;
    for (const auto &lit : c.literals)
    {
        total += termWeight(lit.left) + termWeight(lit.right);
    }
    return total;
}

std::size_t selectGivenIndex(const std::vector<Clause> &passive, bool preferAge)
{
    std::size_t best = 0;

    if (preferAge)
    {
        int best_id = passive[0].id;
        for (std::size_t i = 1; i < passive.size(); ++i)
        {
            if (passive[i].id < best_id)
            {
                best = i;
                best_id = passive[i].id;
            }
        }
    }
    else
    {
        int best_weight = clauseWeight(passive[0]);
        for (std::size_t i = 1; i < passive.size(); ++i)
        {
            int w = clauseWeight(passive[i]);
            if (w < best_weight || (w == best_weight && passive[i].id < passive[best].id))
            {
                best = i;
                best_weight = w;
            }
        }
    }

    return best;
}
