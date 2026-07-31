#include "selection.hpp"
#include "terms.hpp"

int clauseWeight(const Clause &c)
{
    int total = 0;
    for (const auto &lit : c.literals)
    {
        total += termWeight(lit.left) + termWeight(lit.right);
    }
    return total;
}

std::size_t selectGivenIndex(const std::vector<Clause> &passive, const std::vector<int> &weights,
                             bool preferAge)
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
        for (std::size_t i = 1; i < passive.size(); ++i)
        {
            if (weights[i] < weights[best] ||
                (weights[i] == weights[best] && passive[i].id < passive[best].id))
            {
                best = i;
            }
        }
    }

    return best;
}
