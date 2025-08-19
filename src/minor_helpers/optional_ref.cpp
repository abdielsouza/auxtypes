#include "minor_helpers.hpp"

namespace auxtypes
{
    template <typename T>
    OptionalRef<T>::OptionalRef(std::nullptr_t) noexcept : ptr(nullptr) {}

    template <typename T>
    OptionalRef<T>::OptionalRef(T& ref) noexcept : ptr(&ref) {}

    template <typename T>
    OptionalRef<T>& OptionalRef<T>::operator=(T& ref) noexcept
    {
        ptr = &ref;
        return *this;
    }

    template <typename T>
    bool OptionalRef<T>::hasValue() const noexcept
    {
        return ptr != nullptr;
    }

    template <typename T>
    OptionalRef<T>::operator bool() const noexcept
    {
        return hasValue();
    }

    template <typename T>
    T& OptionalRef<T>::value()
    {
        if (!ptr) throw std::runtime_error("OptionalRef: no value");
        return *ptr;
    }

    template <typename T>
    const T& OptionalRef<T>::value() const
    {
        if (!ptr) throw std::runtime_error("OptionalRef: no value");
        return *ptr;
    }

    template <typename T>
    T& OptionalRef<T>::operator*()
    {
        return value();
    }

    template <typename T>
    const T& OptionalRef<T>::operator*() const
    {
        return value();
    }

    template <typename T>
    T* OptionalRef<T>::operator->()
    {
        return &value();
    }

    template <typename T>
    const T* OptionalRef<T>::operator->() const
    {
        return &value();
    }

    template <typename T>
    void OptionalRef<T>::reset() noexcept
    {
        ptr = nullptr;
    }
}