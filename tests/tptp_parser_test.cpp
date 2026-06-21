#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#if __has_include(<doctest/doctest.h>)
#include <doctest/doctest.h>
#elif __has_include(<doctest.h>)
#include <doctest.h>
#else
#error "doctest header not found"
#endif

#include "cnf.hpp"
#include "terms.hpp"
#include "tptp_parser.hpp"

namespace
{

// small helpers
Term V(const std::string &n)
{
    return Variable{n};
}
Term C(const std::string &n)
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

// Reified-predicate literal: p(args) [!]= $true
Literal pred(const std::string &name, std::vector<Term> args, bool positive)
{
    int arity = static_cast<int>(args.size());
    return Literal{makeFunctionApplication(FunctionSymbol{arity, name}, std::move(args)),
                   tptpTrue(), positive};
}

} // namespace

TEST_CASE("parses a single positive predicate literal")
{
    auto cs = parseTPTPCNF("cnf(c1, axiom, p(X)).");
    REQUIRE(cs.size() == 1);
    CHECK(cs[0].id == 0);
    REQUIRE(cs[0].literals.size() == 1);

    Literal expected = pred("p", {V("X")}, true);
    CHECK(cs[0].literals.contains(expected));
}

TEST_CASE("parses a negated predicate literal")
{
    auto cs = parseTPTPCNF("cnf(c, axiom, ~q(a, Y)).");
    REQUIRE(cs.size() == 1);
    REQUIRE(cs[0].literals.size() == 1);

    Literal expected = pred("q", {C("a"), V("Y")}, false);
    CHECK(cs[0].literals.contains(expected));
}

TEST_CASE("parses equality and disequality literals")
{
    auto cs = parseTPTPCNF("cnf(c, axiom, a = b | f(X) != g(X)).");
    REQUIRE(cs.size() == 1);
    REQUIRE(cs[0].literals.size() == 2);

    CHECK(cs[0].literals.contains(eq(C("a"), C("b"), true)));
    CHECK(cs[0].literals.contains(eq(F("f", {V("X")}), F("g", {V("X")}), false)));
}

TEST_CASE("parses a multi-literal clause with mixed kinds and outer parentheses")
{
    auto cs = parseTPTPCNF("cnf(mixed, axiom, ( p(X) | ~q(X, f(Y)) | a = b )).");
    REQUIRE(cs.size() == 1);
    REQUIRE(cs[0].literals.size() == 3);

    CHECK(cs[0].literals.contains(pred("p", {V("X")}, true)));
    CHECK(cs[0].literals.contains(pred("q", {V("X"), F("f", {V("Y")})}, false)));
    CHECK(cs[0].literals.contains(eq(C("a"), C("b"), true)));
}

TEST_CASE("assigns sequential clause ids over multiple clauses")
{
    auto cs = parseTPTPCNF("cnf(c1, axiom, p(X)).\n"
                           "cnf(c2, negated_conjecture, ~p(a)).\n");
    REQUIRE(cs.size() == 2);
    CHECK(cs[0].id == 0);
    CHECK(cs[1].id == 1);
    CHECK(cs[0].literals.contains(pred("p", {V("X")}, true)));
    CHECK(cs[1].literals.contains(pred("p", {C("a")}, false)));
}

TEST_CASE("skips % line comments and /* block */ comments")
{
    const char *src = "% leading line comment\n"
                      "/* block\n"
                      "   comment */\n"
                      "cnf(c, axiom, % inline comment\n"
                      "  p(X) /* mid */ | q(Y)).\n"
                      "% trailing\n";
    auto cs = parseTPTPCNF(src);
    REQUIRE(cs.size() == 1);
    REQUIRE(cs[0].literals.size() == 2);
    CHECK(cs[0].literals.contains(pred("p", {V("X")}, true)));
    CHECK(cs[0].literals.contains(pred("q", {V("Y")}, true)));
}

TEST_CASE("tolerates whitespace and newlines between tokens")
{
    auto cs = parseTPTPCNF("  cnf  (\n  c\n  ,\n  axiom\n  ,\n  p ( X )\n  )  .\n");
    REQUIRE(cs.size() == 1);
    CHECK(cs[0].literals.contains(pred("p", {V("X")}, true)));
}

TEST_CASE("deduplicates structurally equal literals via std::set")
{
    auto cs = parseTPTPCNF("cnf(c, axiom, p(X) | p(X)).");
    REQUIRE(cs.size() == 1);
    CHECK(cs[0].literals.size() == 1);
}

TEST_CASE("accepts integer clause names")
{
    auto cs = parseTPTPCNF("cnf(42, axiom, p(a)).");
    REQUIRE(cs.size() == 1);
    CHECK(cs[0].literals.contains(pred("p", {C("a")}, true)));
}

TEST_CASE("rejects non-cnf languages")
{
    CHECK_THROWS_AS(parseTPTPCNF("fof(c, axiom, p(X))."), TPTPParseError);
    CHECK_THROWS_AS(parseTPTPCNF("tff(c, axiom, p(X))."), TPTPParseError);
}

TEST_CASE("rejects include directives")
{
    CHECK_THROWS_AS(parseTPTPCNF("include('foo.ax')."), TPTPParseError);
}

TEST_CASE("rejects missing terminator")
{
    CHECK_THROWS_AS(parseTPTPCNF("cnf(c, axiom, p(X))"), TPTPParseError);
}

TEST_CASE("rejects bare variable as literal")
{
    CHECK_THROWS_AS(parseTPTPCNF("cnf(c, axiom, X)."), TPTPParseError);
}

TEST_CASE("rejects negation of equality (use !=)")
{
    CHECK_THROWS_AS(parseTPTPCNF("cnf(c, axiom, ~ a = b)."), TPTPParseError);
}

TEST_CASE("rejects unterminated block comment")
{
    CHECK_THROWS_AS(parseTPTPCNF("/* never closed cnf(c, axiom, p(X))."), TPTPParseError);
}

TEST_CASE("parses empty input as zero clauses")
{
    auto cs = parseTPTPCNF("   \n  % only a comment\n  ");
    CHECK(cs.empty());
}

TEST_CASE("nested function applications round-trip")
{
    auto cs = parseTPTPCNF("cnf(c, axiom, f(g(X), h(a, Y)) = b).");
    REQUIRE(cs.size() == 1);
    REQUIRE(cs[0].literals.size() == 1);

    Term lhs = F("f", {F("g", {V("X")}), F("h", {C("a"), V("Y")})});
    CHECK(cs[0].literals.contains(eq(lhs, C("b"), true)));
}
