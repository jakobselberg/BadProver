#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#if __has_include(<doctest/doctest.h>)
#include <doctest/doctest.h>
#elif __has_include(<doctest.h>)
#include <doctest.h>
#else
#error "doctest header not found"
#endif

#include "feature_vector.hpp"
#include "subsumption.hpp"
#include "terms.hpp"
#include <set>

namespace
{
Term V(const std::string &n)
{
    return Variable{n};
}

Term Const(const std::string &n)
{
    return makeFunctionApplication(FunctionSymbol{0, n}, {});
}

Term F(const std::string &n, std::vector<Term> args)
{
    int arity = static_cast<int>(args.size());
    return makeFunctionApplication(FunctionSymbol{arity, n}, std::move(args));
}

Literal eq(Term l, Term r, bool pos = true)
{
    return Literal{std::move(l), std::move(r), pos};
}
} // namespace

TEST_CASE("computeFeatureVector counts literals and overflows past 6 tracked symbols")
{
    Term big = F("f0", {Const("f1"), Const("f2"), Const("f3"), Const("f4"), Const("f5"),
                        Const("f6"), Const("f7"), Const("f8")});
    Clause c{1, std::set<Literal>{eq(big, Const("k"), true)}};

    SymbolIndex symbols;
    FeatureVector fv = computeFeatureVector(c, symbols);

    CHECK(fv[0] == 1); // positive literal count
    CHECK(fv[1] == 0); // negative literal count
    CHECK(fv[2] == 4); // catch-all: f6, f7, f8, k
    CHECK(fv[3] == 1); // f0
    CHECK(fv[4] == 1); // f1
    CHECK(fv[5] == 1); // f2
    CHECK(fv[6] == 1); // f3
    CHECK(fv[7] == 1); // f4
    CHECK(fv[8] == 1); // f5
    for (std::size_t i = 9; i < FEATURE_VECTOR_SIZE; ++i)
        CHECK(fv[i] == 0);
}

TEST_CASE("feature vector index candidates are a superset of the truly subsuming clauses")
{
    std::vector<Clause> indexed = {
        Clause{1, std::set<Literal>{eq(F("p", {V("X")}), Const("t"), true)}},
        Clause{2, std::set<Literal>{eq(F("p", {Const("a")}), Const("t"), true)}},
        Clause{3, std::set<Literal>{eq(F("p", {V("X")}), Const("t"), true),
                                    eq(F("q", {V("X")}), Const("t"), true)}},
        Clause{4, std::set<Literal>{eq(F("p", {Const("a")}), Const("t"), false)}},
    };

    SubsumptionIndex index;
    for (std::size_t i = 0; i < indexed.size(); ++i)
        index.insert(indexed[i], i);

    std::vector<Clause> queries = {
        Clause{10, std::set<Literal>{eq(F("p", {Const("a")}), Const("t"), true)}},
        Clause{11, std::set<Literal>{eq(F("p", {Const("a")}), Const("t"), true),
                                     eq(F("q", {Const("a")}), Const("t"), true)}},
        Clause{12, std::set<Literal>{eq(F("p", {Const("a")}), Const("t"), false)}},
    };

    for (const auto &query : queries)
    {
        std::set<std::size_t> trueMatches;
        for (std::size_t i = 0; i < indexed.size(); ++i)
            if (subsumes(indexed[i], query))
                trueMatches.insert(i);

        auto candidates = index.candidates(query);
        std::set<std::size_t> candidateSet(candidates.begin(), candidates.end());

        for (std::size_t m : trueMatches)
            CHECK(candidateSet.count(m) == 1);
    }
}
