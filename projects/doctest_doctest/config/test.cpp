#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include <doctest/doctest.h>

// A simple function to test
static int add(int a, int b) { return a + b; }

TEST_CASE("addition works") {
    CHECK(add(2, 2) == 4);
    CHECK(add(-1, 1) == 0);
}
