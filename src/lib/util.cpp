#include "util.hpp"
#include <iostream>
#include <sstream>

std::string printTerm(const Term &t)
{
    return std::visit(
        [](const auto &x) -> std::string {
            using T = std::decay_t<decltype(x)>;

            if constexpr (std::is_same_v<T, Variable>)
            {
                return x.name;
            }
            else // FunctionApplicationRef
            {
                std::ostringstream out;
                out << x->symbol.name;

                if (!x->arguments.empty())
                {
                    out << "(";
                    for (std::size_t i = 0; i < x->arguments.size(); ++i)
                    {
                        if (i != 0)
                            out << ", ";
                        out << printTerm(x->arguments[i]);
                    }
                    out << ")";
                }

                return out.str();
            }
        },
        t);
}

std::string printLiteral(const Literal &lit)
{
    std::ostringstream out;

    out << printTerm(lit.left);

    if (lit.positive)
        out << " = ";
    else
        out << " != ";

    out << printTerm(lit.right);

    return out.str();
}

std::string printClause(const Clause &clause)
{
    std::ostringstream out;

    out << "[" << clause.id << "] ";

    bool first = true;
    for (const auto &lit : clause.literals)
    {
        if (!first)
            out << " | ";

        out << printLiteral(lit);
        first = false;
    }

    if (first)
        out << "⊥"; // Empty clause

    return out.str();
}

void printC(const Clause &clause)
{
    std::cout << printClause(clause) << '\n';
}
