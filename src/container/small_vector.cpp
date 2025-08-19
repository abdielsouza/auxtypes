#include "container.hpp"

namespace auxtypes
{
    template <typename T, std::size_t N>
    SmallVector<T, N>::SmallVector(std::initializer_list<T> init)
    {
        for (auto&& e : init) pushBack(e);
    }

    template <typename T, std::size_t N>
    void SmallVector<T, N>::pushBack(const T& value)
    {
        if (!using_heap && count < N)
        {
            stack_storage[count++] = std::move(value);
        }
        else
        {
            if (!using_heap)
            {
                heap_storage.reserve(N * 2);
                heap_storage.insert(
                    heap_storage.end(),
                    std::make_move_iterator(stack_storage.begin()),
                    std::make_move_iterator(stack_storage.begin() + count)
                );

                using_heap = true;
            }

            heap_storage.push_back(std::move(value));
        }
    }

    template <typename T, std::size_t N>
    std::size_t SmallVector<T, N>::size() const
    {
        return using_heap ? heap_storage.size() : count;
    }

    template <typename T, std::size_t N>
    T& SmallVector<T, N>::operator[](std::size_t i)
    {
        return using_heap ? heap_storage[i] : stack_storage[i];
    }

    template <typename T, std::size_t N>
    const T& SmallVector<T, N>::operator[](std::size_t i) const
    {
        return using_heap ? heap_storage[i] : stack_storage[i];
    }
}