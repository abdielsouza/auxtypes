#include "auxtypes/container.hpp"
#include <cassert>

void test_small_vector()
{
    auxtypes::SmallVector<int, 5> my_vec;
    
    for (int i = 0; i < 9; i++)
    {
        my_vec.pushBack(i + 1);
    }
}

void test_fixed_string()
{

    auxtypes::FixedString<5> myFixedString = "hello";
    assert(myFixedString.capacity() == myFixedString.size() + 1 && "fixed string capacity must be the size plus one.");
}

int main()
{
    test_small_vector();

    return 0;
}