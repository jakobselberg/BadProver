#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include <doctest/doctest.h>

#include "terms.hpp"

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
