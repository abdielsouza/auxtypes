#include <cassert>
#include <iostream>
#include "auxtypes/minor_helpers.hpp"

int main()
{
    // Test OptionalRef
    int x = 10;
    auxtypes::OptionalRef<int> opt(x);

    assert(opt.hasValue() && "'opt' has no value!");
    assert(*opt == 10 && "'opt' value is different from 'x' value!");

    *opt = 42;
    assert(x == 42 && "'x' value was not modified as expected!");

    opt.reset();
    assert(!opt.hasValue() && "'opt' still has value after reset!");

    std::cout << "\nTest for OptionalRef OK\n";

    return 0;
}