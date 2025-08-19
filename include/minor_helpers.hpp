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
        OptionalRef(std::nullptr_t) noexcept;
        OptionalRef(T& ref) noexcept;

        // copy

        OptionalRef(const OptionalRef&) noexcept = default;
        OptionalRef& operator=(const OptionalRef&) noexcept = default;

        // move

        OptionalRef(OptionalRef&&) noexcept = default;
        OptionalRef& operator=(OptionalRef&&) noexcept = default;

        OptionalRef& operator=(T& ref) noexcept;

        bool hasValue() const noexcept;
        explicit operator bool() const noexcept;

        T& value();
        const T& value() const;

        T& operator*();
        const T& operator*() const;

        T* operator->();
        const T* operator->() const;

        void reset() noexcept;
    };
}

#endif /* AB8295EA_ADE3_4BA3_ABB7_1189C7B69EE4 */
