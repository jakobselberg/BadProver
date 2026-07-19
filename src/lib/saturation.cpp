#include "saturation.hpp"
#include <variant>

bool isEmptyClause(const Clause &c)
{
    return c.literals.empty();
}

namespace
{

static void removeFalseLiterals(Clause &c)
{
    std::set<Literal> kept;
    for (const auto &lit : c.literals)
        if (lit.positive || lit.left != lit.right)
            kept.insert(lit);
    c.literals = std::move(kept);
}

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

std::size_t selectGivenIndex(const std::vector<Clause> &passive)
{
    std::size_t best = 0;
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
    return best;
}

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
        for (auto cl : state.active)
        {
            printC(cl);
        }

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
            if (isEmptyClause(conclusion))
            {
                return SaturationResult::Unsatisfiable;
            }
            if (state.seen.insert(conclusion.literals).second)
                state.passive.push_back(conclusion);
        }
    }

    // neither saturation nor empty clause reached within iteration budget
    return SaturationResult::Unknown;
}
