#include "container.hpp"

namespace auxtypes
{
    template <std::size_t N>
    FixedString<N>::FixedString()
    {
        data[0] = '\0';
    }

    template <std::size_t N>
    FixedString<N>::FixedString(const char* s)
    {
        assign(s);
    }

    template <std::size_t N>
    void FixedString<N>::assign(const char* s)
    {
        length = std::min(strlen(s), N);
        std::memcpy(data.data(), s, length);
        data[length] = '\0';
    }

    template <std::size_t N>
    const char* FixedString<N>::c_str() const
    {
        return data;
    }

    template <std::size_t N>
    char& FixedString<N>::operator[](std::size_t i)
    {
        return data[i];
    }

    template <std::size_t N>
    const char& FixedString<N>::operator[](std::size_t i) const
    {
        return data[i];
    }

    template <std::size_t N>
    bool FixedString<N>::operator==(const char* s) const
    {
        return std::strcmp(data.data(), s) == 0;
    }
}