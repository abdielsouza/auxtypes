#ifndef C864D325_D531_4BD8_A35E_5DA3478B0813
#define C864D325_D531_4BD8_A35E_5DA3478B0813

#pragma once

namespace auxtypes
{
    template <typename T, typename Tag>
    class StrongType
    {
        T value;

    public:
        constexpr explicit StrongType(T v) : value(v) {}
        constexpr operator T() const
        {
            return value;
        }
    };
}

#endif /* C864D325_D531_4BD8_A35E_5DA3478B0813 */
