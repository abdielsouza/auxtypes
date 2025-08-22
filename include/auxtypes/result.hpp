#ifndef F49B0839_215C_4714_8ECB_0B4DA7F28259
#define F49B0839_215C_4714_8ECB_0B4DA7F28259

#pragma once

#include <variant>

namespace auxtypes
{
    /**
     * Represents a returned type by Result in any case. It's a generic container for it.
     * @warning Internal use!
     */
    template <typename T>
    class ResultCaseValue
    {
    public:
        T value;

        constexpr explicit ResultCaseValue(T value) : value(std::move(value)) {}

        constexpr T&& take()
        {
            return std::move(value);
        }
    };

    /**
     * Represents a returned type by Result in case of success.
     * @warning Internal use!
     */
    template <typename T>
    using Ok = ResultCaseValue<T>;

    /**
     * Represents a returned type by Result in case of failure.
     * @warning Internal use!
     */
    template <typename T>
    using Err = ResultCaseValue<T>;

    /**
     * Represents any action result. If the action is successful,
     * returns a value of the first type. If not, returns a value
     * of the second type.
     */
    template <typename OkT, typename ErrT>
    class Result
    {
    public:
        using Variant_t = std::variant<Ok<OkT>, Err<ErrT>>;

        constexpr Result(Ok<OkT> value) : variant(std::move(value)) {}
        constexpr Result(Err<ErrT> value) : variant(std::move(value)) {}

        constexpr bool isOk()
        {
            return std::holds_alternative<Ok<OkT>>(variant);
        }

        constexpr bool isErr()
        {
            return std::holds_alternative<Err<ErrT>>(variant);
        }

        constexpr OkT getOk()
        {
            return std::get<Ok<OkT>>(variant).value;
        }

        constexpr ErrT getErr()
        {
            return std::get<Err<ErrT>>(variant).value;
        }

        constexpr OkT takeOk()
        {
            return std::get<Ok<OkT>>(variant).take();
        }

        constexpr ErrT takeErr()
        {
            return std::get<Err<ErrT>>(variant).take();
        }


    private:
        Variant_t variant;
    };
}

#endif /* F49B0839_215C_4714_8ECB_0B4DA7F28259 */
