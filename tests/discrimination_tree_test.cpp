#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#if __has_include(<doctest/doctest.h>)
#include <doctest/doctest.h>
#elif __has_include(<doctest.h>)
#include <doctest.h>
#else
#error "doctest header not found"
#endif

#include "discrimination_tree.hpp"
#include "terms.hpp"
#include "unification.hpp"
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

DiscrKey appKey(const std::string &n, int arity)
{
    return DiscrKey{DiscrKeyKind::App, FunctionSymbol{arity, n}};
}
} // namespace

TEST_CASE("linearize produces preorder tokens")
{
    Term t = F("f", {F("g", {Const("a")}), V("X")});
    auto tokens = linearize(t);

    REQUIRE(tokens.size() == 4);
    CHECK(tokens[0] == appKey("f", 2));
    CHECK(tokens[1] == appKey("g", 1));
    CHECK(tokens[2] == appKey("a", 0));
    CHECK(tokens[3].kind == DiscrKeyKind::Star);
}

TEST_CASE("skipSubtree skips exactly one subtree at each position")
{
    Term t = F("f", {F("g", {Const("a")}), V("X")});
    auto tokens = linearize(t);

    CHECK(skipSubtree(tokens, 0) == 4); // whole term
    CHECK(skipSubtree(tokens, 1) == 3); // g(a)
    CHECK(skipSubtree(tokens, 2) == 3); // a
    CHECK(skipSubtree(tokens, 3) == 4); // X
}

TEST_CASE("query variable matches an indexed compound subtree")
{
    DiscriminationTree<int> index;
    index.insert(F("f", {F("g", {Const("a")}), V("X")}), 0);

    auto candidates = index.candidates(F("f", {V("Y"), Const("b")}));
    CHECK(candidates.size() == 1);
}

TEST_CASE("discrimination tree candidates are a superset of the truly unifiable terms")
{
    std::vector<Term> indexed = {
        F("f", {Const("a"), Const("b")}),
        F("f", {V("X"), Const("b")}),
        F("f", {Const("a"), V("Y")}),
        F("g", {Const("a")}),
        V("Z"),
        F("f", {Const("c"), Const("d"), Const("e")}),
        F("f", {F("g", {Const("a")}), V("X")}),
    };

    DiscriminationTree<int> index;
    for (std::size_t i = 0; i < indexed.size(); ++i)
        index.insert(indexed[i], static_cast<int>(i));

    std::vector<Term> queries = {
        F("f", {Const("a"), Const("b")}),
        F("f", {Const("a"), Const("z")}),
        F("f", {V("W"), V("V")}),
        F("g", {Const("a")}),
        Const("q"),
        F("f", {Const("c"), Const("d"), Const("e")}),
        F("f", {V("W"), Const("b")}),
    };

    for (const auto &query : queries)
    {
        std::set<int> trueMatches;
        for (std::size_t i = 0; i < indexed.size(); ++i)
            if (mgu(indexed[i], query))
                trueMatches.insert(static_cast<int>(i));

        auto candidates = index.candidates(query);
        std::set<int> candidateSet(candidates.begin(), candidates.end());

        for (int m : trueMatches)
            CHECK(candidateSet.count(m) == 1);
    }
}
