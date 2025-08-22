#include "auxtypes/result.hpp"
#include <string>
#include <iostream>
#include <cassert>

int main()
{
    auto accept_even = [](int number) -> auxtypes::Result<int, std::string> {
        if (!(number % 2 == 0)) {
            return auxtypes::Err<std::string>("number is not even!");
        }

        return auxtypes::Ok<int>(number);
    };

    auto expect_ok = accept_even(2);
    assert((expect_ok.isOk() && !expect_ok.isErr()) && "'Ok' result expected!");

    std::cout << expect_ok.takeOk() << "\n";

    auto expect_err = accept_even(1);
    assert((expect_ok.isErr() && !expect_ok.isOk()) && "'Err' result expected!");

    std::cout << expect_err.takeErr() << "\n";

    std::cout << "test for Result was successful!\n";

    return 0;
}