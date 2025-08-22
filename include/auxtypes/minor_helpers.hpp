#ifndef AB8295EA_ADE3_4BA3_ABB7_1189C7B69EE4
#define AB8295EA_ADE3_4BA3_ABB7_1189C7B69EE4

#pragma once

#include <utility>
#include <stdexcept>

namespace auxtypes
{
    /**
     * Used to create support for references as optional values,
     * since `std::optional` does not support any kind of references.
     */
    template <typename T>
    class OptionalRef
    {
        T* ptr = nullptr;

    public:
        // constructors

        OptionalRef() noexcept = default;
        OptionalRef(std::nullptr_t) noexcept : ptr(nullptr) {}
        OptionalRef(T& ref) noexcept : ptr(&ref) {}

        // copy

        OptionalRef(const OptionalRef&) noexcept = default;
        OptionalRef& operator=(const OptionalRef&) noexcept = default;

        // move

        OptionalRef(OptionalRef&&) noexcept = default;
        OptionalRef& operator=(OptionalRef&&) noexcept = default;

        OptionalRef& operator=(T& ref) noexcept
        {
            ptr = &ref;
            return *this;
        }

        bool hasValue() const noexcept
        {
            return ptr != nullptr;
        }

        explicit operator bool() const noexcept
        {
            return hasValue();
        }

        T& value()
        {
            if (!ptr) throw std::runtime_error("OptionalRef: no value");
            return *ptr;
        }

        const T& value() const
        {
            if (!ptr) throw std::runtime_error("OptionalRef: no value");
            return *ptr;
        }

        T& operator*()
        {
            return value();
        }

        const T& operator*() const
        {
            return value();
        }

        T* operator->()
        {
            return &value();
        }

        const T* operator->() const
        {
            return &value();
        }

        void reset() noexcept
        {
            ptr = nullptr;
        }
    };
}

#endif /* AB8295EA_ADE3_4BA3_ABB7_1189C7B69EE4 */
