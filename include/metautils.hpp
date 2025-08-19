#ifndef E351D8C7_E7CD_48E9_990F_7FF2B60600B7
#define E351D8C7_E7CD_48E9_990F_7FF2B60600B7

#pragma once

#include <cstdint>

namespace auxtypes
{
    template<typename... Ts>
    struct Overloaded : Ts...
    {
        using Ts::operator()...;
    };

    template <typename... Ts>
    Overloaded(Ts...) -> Overloaded<Ts...>;

    /**
     * A type list that can be manipulated at compile-time.
     */
    template <typename... Ts>
    struct TypeList {};

    template <std::size_t N, typename List>
    struct TypeAt {};

    template <std::size_t N, typename Head, typename... Tail>
    struct TypeAt<N, TypeList<Head, Tail...>> : TypeAt<N - 1, TypeList<Tail...>> {};

    template <typename Head, typename... Tail>
    struct TypeAt<0, TypeList<Head, Tail...>>
    {
        using Type = Head;
    };

    template <std::size_t N, typename List>
    using TypeAt_t = typename TypeAt<N, List>::Type;

    /**
     * With type T, find its index in a TypeList.
     */
    template <typename T, typename List>
    struct IndexOf;

    template <typename T, typename... Tail>
    struct IndexOf<T, TypeList<T, Tail...>> {
        static constexpr std::size_t value = 0;
    };

    template <typename T, typename Head, typename... Tail>
    struct IndexOf<T, TypeList<Head, Tail...>> {
        static constexpr std::size_t value = 1 + IndexOf<T, TypeList<Tail...>>::value;
    };

    /**
     * Checks if a type is instance of a specific template.
     */
    template <typename T, template <typename...> class Template>
    struct IsSpecOf : std::false_type { };

    template <template <typename...> class Template, typename... Args>
    struct IsSpecOf<Template<Args...>, Template> : std::true_type { };

    template <typename T, template <typename...> class Template>
    constexpr bool IsSpecOf_v = IsSpecOf<T, Template>::value;
}

#endif /* E351D8C7_E7CD_48E9_990F_7FF2B60600B7 */
