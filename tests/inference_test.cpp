#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#if __has_include(<doctest/doctest.h>)
#include <doctest/doctest.h>
#elif __has_include(<doctest.h>)
#include <doctest.h>
#else
#error "doctest header not found"
#endif

#include "cnf.hpp"
#include "inference.hpp"
#include "terms.hpp"
#include "tptp_parser.hpp"
#include "util.hpp"

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

Literal pred(const std::string &name, std::vector<Term> args, bool positive)
{
    int arity = static_cast<int>(args.size());
    return Literal{makeFunctionApplication(FunctionSymbol{arity, name}, std::move(args)),
                   tptpTrue(), positive};
}

} // namespace

TEST_CASE("term subterm positions")
{
    Term t = F("f", {Const("a"), F("g", {V("X")})});
    auto positions = allSubtermPositions(t);
    CHECK(positions.size() == 4);
    CHECK(getSubtermAt(t, {}) == t);
    CHECK(getSubtermAt(t, {0}) == Const("a"));
    CHECK(getSubtermAt(t, {1}) == F("g", {V("X")}));
    CHECK(getSubtermAt(t, {1, 0}) == V("X"));

    auto replaced = setSubtermAt(t, {1, 0}, Const("b"));
    REQUIRE(replaced);
    CHECK(*replaced == F("f", {Const("a"), F("g", {Const("b")})}));
}

TEST_CASE("superposition on a single equality")
{
    Clause D{1, std::set<Literal>{eq(F("f", {Const("a")}), Const("b"), true)}};
    Clause C{2, std::set<Literal>{pred("p", {F("f", {Const("a")})}, true)}};

    auto results = superposition(D, C);
    /*printC(C);
    printC(D);
    for (const auto &cl : results)
    {
        printC(cl);
    }*/
    REQUIRE(results.size() == 1);
    Clause expected{-1, std::set<Literal>{pred("p", {Const("b")}, true)}};
    CHECK(results[0].literals == expected.literals);
}

TEST_CASE("equality resolution")
{
    Clause clauseC{1, std::set<Literal>{eq(V("X"), Const("a"), false), pred("p", {V("X")}, true)}};
    auto results = equalityResolution(clauseC);
    /*printC(clauseC);
    for (const auto &cl : results)
    {
        printC(cl);
    }*/
    REQUIRE(results.size() == 1);
    Clause expected{-1, std::set<Literal>{pred("p", {Const("a")}, true)}};
    CHECK(results[0].literals == expected.literals);
}

// of limited usefullnes witjout ordering
TEST_CASE("equality factoring")
{
    Clause clauseC{1,
                   std::set<Literal>{eq(V("X"), Const("a"), true), eq(V("X"), Const("b"), true)}};
    // printC(clauseC);
    auto results = equalityFactoring(clauseC);
    /*for (const auto &cl : results)
    {
        printC(cl);
    }*/
    REQUIRE(results.size() >= 1);
    CHECK(std::any_of(results.begin(), results.end(), [&](const Clause &cl) {
        return cl.literals.contains(eq(Const("a"), Const("b"), false));
    }));
}
