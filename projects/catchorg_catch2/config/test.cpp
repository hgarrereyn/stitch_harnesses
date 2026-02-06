#include <catch2/catch_test_macros.hpp>

// Simple function to test
static int add(int a, int b) { return a + b; }

TEST_CASE("Addition works", "[basic]") {
    REQUIRE(add(1, 1) == 2);
    REQUIRE(add(-3, 5) == 2);
}

// Catch2Main provides main() when linked with Catch2Main library.
