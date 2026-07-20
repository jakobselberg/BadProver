#include "saturation.hpp"
#include "selection.hpp"
#include "simplification.hpp"
#include "subsumption.hpp"
#include <functional>
#include <variant>

bool isEmptyClause(const Clause &c)
{
    return c.literals.empty();
}

namespace
{

static Clause canonicalize(const Clause &c)
{
    std::map<std::string, std::string> mapping;
    int count = 0;

    std::function<Term(const Term &)> canonTerm = [&](const Term &t) -> Term {
        if (auto *v = std::get_if<Variable>(&t))
        {
            auto &mapped = mapping[v->name];
            if (mapped.empty())
                mapped = "_c" + std::to_string(count++);
            return Variable{mapped};
        }
        const auto &f = *std::get<FunctionApplicationRef>(t);
        std::vector<Term> args;
        for (const auto &arg : f.arguments)
        {
            args.push_back(canonTerm(arg));
        }
        return makeFunctionApplication(f.symbol, std::move(args));
    };

    Clause result{c.id, {}};
    for (const auto &lit : c.literals)
        result.literals.insert(Literal{canonTerm(lit.left), canonTerm(lit.right), lit.positive});
    return result;
}

} // namespace

SaturationResult saturate(ProofState &state, int max_iteration)
{

    for (const auto &c : state.passive)
        state.seen.insert(c.literals);

    for (int iteration = 0; iteration < max_iteration; ++iteration)
    {
        if (state.passive.empty())
        {
            return SaturationResult::Saturated;
        }

        std::size_t idx = selectGivenIndex(state.passive);
        Clause given = state.passive[idx];
        state.passive[idx] = state.passive.back();
        state.passive.pop_back();
        state.active.push_back(given);

        std::vector<Clause> generated;

        auto equalityResolutionResult = equalityResolution(given);
        generated.insert(generated.end(), equalityResolutionResult.begin(),
                         equalityResolutionResult.end());

        auto equalityFactoringResult = equalityFactoring(given);
        generated.insert(generated.end(), equalityFactoringResult.begin(),
                         equalityFactoringResult.end());

        for (const auto &c : state.active)
        {
            auto s1 = superposition(given, c);
            generated.insert(generated.end(), s1.begin(), s1.end());
            auto s2 = superposition(c, given);
            generated.insert(generated.end(), s2.begin(), s2.end());
        }

        for (auto &conclusion : generated)
        {
            conclusion.id = state.next_id++;
            removeFalseLiterals(conclusion);
            conclusion = demodulate(conclusion, state.active);
            removeFalseLiterals(conclusion);
            bool subsumed = false;
            for (const auto &lit : conclusion.literals)
                if (lit.positive && lit.left == lit.right)
                    goto next_conclusion;

            if (isEmptyClause(conclusion))
            {
                return SaturationResult::Unsatisfiable;
            }

            for (const auto &active : state.active)
                if (subsumes(active, conclusion))
                {
                    subsumed = true;
                    break;
                }
            if (subsumed)
                continue;

            if (state.seen.insert(canonicalize(conclusion).literals).second)
                state.passive.push_back(conclusion);
        next_conclusion:;
        }
    }

    // neither saturation nor empty clause reached within iteration budget
    return SaturationResult::Unknown;
}
