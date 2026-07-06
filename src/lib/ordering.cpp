#include "ordering.hpp"

namespace
{
int termWeight(const Term &t)
{
    if (std::holds_alternative<Variable>(t))
        return 1;
    const auto &app = *std::get<FunctionApplicationRef>(t);
    int w = 1;
    for (const auto &arg : app.arguments)
        w += termWeight(arg);
    return w;
}
} // namespace
