#include "saturation.hpp"
#include <variant>

bool isEmptyClause(const Clause &c)
{
    return c.literals.empty();
}

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