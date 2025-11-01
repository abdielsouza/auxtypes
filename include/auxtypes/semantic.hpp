#ifndef C864D325_D531_4BD8_A35E_5DA3478B0813
#define C864D325_D531_4BD8_A35E_5DA3478B0813

#pragma once

#include <compare>
#include <functional>
#include <ostream>

namespace auxtypes
{
    template <typename T, typename Tag>
    class StrongType
    {
        T value;

    public:
        using ValueType = T;
        using TagType = Tag;

        constexpr explicit StrongType(const T& v) noexcept(std::is_nothrow_copy_constructible_v<T>) : value(v) {}
        constexpr explicit StrongType(T&& v) noexcept(std::is_nothrow_copy_constructible_v<T>) : value(std::move(v)) {}

        constexpr StrongType() = default;
        constexpr StrongType(const StrongType&) = default;
        constexpr StrongType(StrongType&&) noexcept = default;
        constexpr StrongType& operator=(const StrongType&) = default;
        constexpr StrongType& operator=(StrongType&&) noexcept = default;

        // Acesso explícito
        constexpr const T& get() const noexcept { return value; }
        constexpr T& get() noexcept { return value; }

        // Operadores de comparação (C++20)
        #if __cplusplus >= 202002L
        constexpr auto operator<=>(const StrongType&) const = default;

        // Operadores aritméticos opcionais
        constexpr StrongType operator+(const StrongType& other) const requires std::is_arithmetic_v<T>
        {
            return StrongType(value + other.value);
        }

        constexpr StrongType operator-(const StrongType& other) const requires std::is_arithmetic_v<T>
        {
            return StrongType(value - other.value);
        }

        constexpr StrongType& operator+=(const StrongType& other) requires std::is_arithmetic_v<T>
        {
            value += other.value;
            return *this;
        }

        constexpr StrongType& operator-=(const StrongType& other) requires std::is_arithmetic_v<T>
        {
            value -= other.value;
            return *this;
        }
        #else
        // Operadores aritméticos opcionais
        constexpr StrongType operator+(const StrongType& other) const
        {
            static_assert(std::is_arithmetic_v<T>);

            return StrongType(value + other.value);
        }

        constexpr StrongType operator-(const StrongType& other) const
        {
            static_assert(std::is_arithmetic_v<T>);
            
            return StrongType(value - other.value);
        }

        constexpr StrongType& operator+=(const StrongType& other)
        {
            static_assert(std::is_arithmetic_v<T>);

            value += other.value;
            return *this;
        }

        constexpr StrongType& operator-=(const StrongType& other)
        {
            static_assert(std::is_arithmetic_v<T>);

            value -= other.value;
            return *this;
        }
        #endif

        // Operador de streaming (para debug/log)
        friend std::ostream& operator<<(std::ostream& os, const StrongType& s)
        {
            return os << s.value;
        }

        // Hash para uso em std::unordered_map / std::unordered_set
        struct Hasher
        {
            std::size_t operator()(const StrongType& s) const noexcept
            {
                return std::hash<T>{}(s.get());
            }
        };
    };
}

#endif /* C864D325_D531_4BD8_A35E_5DA3478B0813 */
