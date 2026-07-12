#include "util.hpp"
#include <fstream>
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

std::string load_file_from_path(const std::string &path)
{
    std::ifstream input_file_stream(path);
    if (input_file_stream.fail())
    {
        throw std::runtime_error("Could not open file: " + path);
    }

    std::ostringstream content_stream;
    content_stream << input_file_stream.rdbuf();
    input_file_stream.close();
    return content_stream.str();
}
