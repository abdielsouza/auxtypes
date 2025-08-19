#ifndef C4938C27_6ADA_4693_A8AD_9BF179FB69AE
#define C4938C27_6ADA_4693_A8AD_9BF179FB69AE

#pragma once

#include <type_traits>
#include <stdexcept>

namespace auxtypes
{
    /**
     * This type was made for protecting pointer values from any troubles
     * relative to "null" values. In other words, accepts a pointer type
     * and behaves as a pointer, asserting the internal pointer to never
     * be null.
     * @tparam T the pointer type (MUST BE A POINTER TYPE, PLEASE).
     */
    template <typename T>
    class NotNull
    {
        static_assert(std::is_pointer_v<T>, "Template type must be a pointer!");

        T ptr;

    public:
        explicit NotNull(T p) : ptr(p)
        {
            if (!p) throw std::invalid_argument("pointer cannot be null!");
        }

        T get() const { return ptr; }
        T operator->() const { return ptr; }
        decltype(auto) operator*() const { return *ptr; }
    };
}

#endif /* C4938C27_6ADA_4693_A8AD_9BF179FB69AE */
