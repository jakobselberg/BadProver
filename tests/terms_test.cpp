#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include <doctest/doctest.h>

#include "terms.hpp"
#include "unification.hpp"

TEST_CASE("FreeVariables finds variables")
{
    Variable x{"x"};
    Variable y{"y"};

    FunctionSymbol f{2, "f"};

    Term tx = x;
    Term ty = y;

    Term app = makeFunctionApplication(f, {tx, ty});

    auto fv = GetFreeVariables(app);

    CHECK(fv.size() == 2);
    CHECK(fv.contains(x));
    CHECK(fv.contains(y));
}

TEST_CASE("rejects Boolean terms in individual contexts")
{
    Term boolean = makeFunctionApplication(FunctionSymbol{0, "$true", TermType::Boolean}, {});
    Term individual = makeFunctionApplication(FunctionSymbol{1, "f"}, {Variable{"X"}});

    CHECK_THROWS_AS(makeFunctionApplication(FunctionSymbol{1, "g"}, {boolean}),
                    std::invalid_argument);
    CHECK_FALSE(setSubtermAt(individual, {0}, boolean).has_value());
    CHECK_FALSE(mgu(Variable{"X"}, boolean).has_value());
}

TEST_CASE("substitution cannot assign a Boolean term to a variable")
{
    Term boolean = makeFunctionApplication(FunctionSymbol{0, "$true", TermType::Boolean}, {});
    Substitution substitution{{Variable{"X"}, boolean}};
    CHECK_THROWS_AS(applySubstitution(substitution, Variable{"X"}), std::invalid_argument);
    CHECK_THROWS_AS(composeSubstitutions(substitution, {}), std::invalid_argument);
}
