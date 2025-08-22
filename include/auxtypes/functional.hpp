#ifndef A0D10025_8D77_4304_B1B8_2F57C59E970E
#define A0D10025_8D77_4304_B1B8_2F57C59E970E

#pragma once

#include <utility>
#include <cstddef>
#include <type_traits>
#include <functional>
#include <optional>

namespace auxtypes
{
    template <typename>
    class FunctionRef;

    /**
     * It's similar to `std::function`, but it doesn't allocate anything in the heap
     * and hasn't ownership. It's a non-owning view about a function, good for
     * code that receive temporary callbacks.
     */
    template <typename Ret, typename... Args>
    class FunctionRef<Ret(Args...)>
    {
        void* object;
        Ret (*stub)(void*, Args...);

    public:
        constexpr FunctionRef(std::nullptr_t = nullptr) noexcept : object(nullptr), stub(nullptr) {}
        constexpr FunctionRef(Ret (*func)(Args...)) noexcept
        : object(reinterpret_cast<void*>(func))
        {
            stub = [](void* obj, Args... args) -> Ret {
                auto f = reinterpret_cast<Ret(*)(Args...)>(obj);
                return f(std::forward<Args>(args)...);
            };
        }
        
        template <typename F>
        constexpr FunctionRef(F& f) noexcept : object(static_cast<void*>(std::addressof(f)))
        {
            stub = [](void* obj, Args... args) -> Ret {
                return (*reinterpret_cast<F*>(obj))(std::forward<Args>(args)...);
            };
        }

        template <typename F>
        constexpr FunctionRef(F&& f) noexcept
        {
            using Decayed = std::decay_t<F>;
            static_assert(!std::is_same_v<Decayed, FunctionRef>, "Cannot be directly constructible from 'FunctionRef'.");

            object = reinterpret_cast<void*>(&f);
            stub = [](void* obj, Args... args) -> Ret {
                return (*reinterpret_cast<Decayed*>(obj))(std::forward<Args>(args)...);
            };
        }

        constexpr Ret operator()(Args... args) {
            return stub(object, std::forward<Args>(args)...);
        }

        constexpr explicit operator bool() noexcept {
            return stub != nullptr;
        }
    };

    /**
     * Support for function composition, just like in functional languages.
     * This wrapper turn functions into pipeable components that can be chained.
     */
    template <typename F>
    class Pipeable
    {
        F func;

    public:
        constexpr explicit Pipeable(F&& f) noexcept(std::is_nothrow_move_constructible_v<F>)
        : func(std::move(f)) {}

        template <typename... Args>
        constexpr decltype(auto) operator()(Args&&... args)
        {
            return func(std::forward<Args>(args)...);
        }

        template <typename T>
        friend constexpr decltype(auto) operator | (T&& value, const Pipeable& pipe)
        {
            return pipe.func(std::forward<T>(value));
        }

        friend constexpr auto operator | (const Pipeable& lhs, const Pipeable& rhs)
        {
            return Pipeable([=](auto&& x) {
                return rhs(lhs(x));
            });
        }
    };

    /// Helper for automatic deduction in `Pipeable`.
    template <typename F>
    constexpr auto makePipeable(F&& f) {
        return Pipeable<std::decay_t<F>>(std::forward<F>(f));
    }

    template <typename F>
    Pipeable(F) -> Pipeable<F>;

    /**
     * Encapsulates an operation that will be only executed when called.
     */
    template <typename T>
    class Lazy
    {
    public:
        using Func = std::function<T()>;

        Lazy(Func&& func) : func(std::move(func)) {}

        const T& value()
        {
            if (!cached)
            {
                cached = func();
            }

            return *cached;
        }

    private:
        Func func;
        std::optional<T> cached;
    };
}

#endif /* A0D10025_8D77_4304_B1B8_2F57C59E970E */
