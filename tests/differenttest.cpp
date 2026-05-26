#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include <doctest/doctest.h>

#include "terms.hpp"

TEST_CASE("FreeVariables works")
{
    Variable x{"x"};

    auto fv = FreeVariables(Term{x});

    CHECK(fv.contains(x));
}
