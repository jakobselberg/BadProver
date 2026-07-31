#include "config.hpp"
#include "saturation.hpp"
#include "selection.hpp"
#include "simplification.hpp"
#include "subsumption.hpp"
#include <unordered_set>

bool isEmptyClause(const Clause &c)
{
    return c.literals.empty();
}

namespace
{

// make the ids of all variables in a given clause c unique within the current process
// to avoid accidental name collisions between variables
Clause canonicalize(const Clause &c)
{
    Substitution renaming;
    for (const auto &v : FreeVariables(c))
        renaming[v] = Variable{"_c" + std::to_string(renaming.size())};
    return applySubstitution(renaming, c);
}

} // namespace

SaturationResult saturate(ProofState &state, int max_iteration)
{

    for (const auto &c : state.passive)
        state.seen.insert(c.literals);

    // kept in lockstep with state.passive so selectGivenIndex never recomputes a weight
    std::vector<int> passiveWeights;
    passiveWeights.reserve(state.passive.size());
    for (const auto &c : state.passive)
        passiveWeights.push_back(clauseWeight(c));

    for (int iteration = 0; iteration < max_iteration; ++iteration)
    {
        if (state.passive.empty())
        {
            return SaturationResult::Saturated;
        }

        std::size_t idx = selectGivenIndex(state.passive, passiveWeights, iteration % 11 == 10);

        state.active.push_back(std::move(state.passive[idx]));
        state.passive[idx] = std::move(state.passive.back());
        state.passive.pop_back();
        passiveWeights[idx] = passiveWeights.back();
        passiveWeights.pop_back();

        std::size_t activeIdx = state.active.size() - 1;
        const Clause &given = state.active[activeIdx];
        if (get_config_subsumption())
            state.subsumptionIndex.insert(given, activeIdx);

        if (given.literals.size() == 1)
        {
            const Literal &rule = *given.literals.begin();
            if (rule.positive)
            {
                state.demodulationIndex.insert(rule.left, RewriteRule{rule.left, rule.right});
                state.demodulationIndex.insert(rule.right, RewriteRule{rule.right, rule.left});
            }
        }

        for (const auto &lit : given.literals)
        {
            for (const Term &side : {lit.left, lit.right})
                for (const auto &entry : allSubtermsWithPositions(side))
                    state.subtermIndex.insert(entry.second, activeIdx);
            if (lit.positive)
            {
                state.eqLiteralIndex.insert(lit.left, activeIdx);
                state.eqLiteralIndex.insert(lit.right, activeIdx);
            }
        }

        std::vector<Clause> generated;

        auto equalityResolutionResult = equalityResolution(given);
        generated.insert(generated.end(), equalityResolutionResult.begin(),
                         equalityResolutionResult.end());

        auto equalityFactoringResult = equalityFactoring(given);
        generated.insert(generated.end(), equalityFactoringResult.begin(),
                         equalityFactoringResult.end());

        std::unordered_set<std::size_t> asD;
        for (const auto &lit : given.literals)
        {
            if (!lit.positive)
                continue;
            for (const Term &side : {lit.left, lit.right})
                for (std::size_t c : state.subtermIndex.candidates(side))
                    asD.insert(c);
        }
        for (std::size_t c : asD)
        {
            auto s1 = superposition(given, state.active[c]);
            generated.insert(generated.end(), s1.begin(), s1.end());
        }

        std::unordered_set<std::size_t> asC;
        for (const auto &lit : given.literals)
            for (const Term &side : {lit.left, lit.right})
                for (const auto &entry : allSubtermsWithPositions(side))
                    for (std::size_t c : state.eqLiteralIndex.candidates(entry.second))
                        asC.insert(c);
        for (std::size_t c : asC)
        {
            auto s2 = superposition(state.active[c], given);
            generated.insert(generated.end(), s2.begin(), s2.end());
        }

        for (auto &conclusion : generated)
        {
            conclusion.id = state.next_id++;
            removeFalseLiterals(conclusion);
            conclusion = demodulate(conclusion, state.demodulationIndex);
            removeFalseLiterals(conclusion);

            // demodulation can introduce a tautology that wasn't there at generation time
            if (isTautology(conclusion))
                continue;

            if (isEmptyClause(conclusion))
            {
                return SaturationResult::Unsatisfiable;
            }

            if (get_config_subsumption())
            {
                std::vector<Literal> conclusionLits(conclusion.literals.begin(),
                                                     conclusion.literals.end());
                bool subsumed = false;
                for (std::size_t candidateIdx : state.subsumptionIndex.candidates(conclusion))
                    if (subsumes(state.active[candidateIdx], conclusionLits))
                    {
                        subsumed = true;
                        break;
                    }
                if (subsumed)
                    continue;
            }

            if (state.seen.insert(canonicalize(conclusion).literals).second)
            {
                passiveWeights.push_back(clauseWeight(conclusion));
                state.passive.push_back(std::move(conclusion));
            }
        }
    }

    // neither saturation nor empty clause reached within iteration budget
    return SaturationResult::Unknown;
}
