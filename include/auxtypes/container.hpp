#ifndef F44E96E9_F6ED_4101_8E04_042D0B88081B
#define F44E96E9_F6ED_4101_8E04_042D0B88081B

#pragma once

#include <array>
#include <vector>
#include <stdexcept>
#include <utility>
#include <initializer_list>
#include <string>
#include <cstring>

namespace auxtypes
{
    /**
     * Container for vectors that expect a little number of elements.
     * It uses a stack storage (`std::array`) when the number of elements
     * is less than `N` and swaps to a heap storage (`std::vector`) when it
     * is greater than `N`.
     */
    template <typename T, std::size_t N>
    class SmallVector
    {
        std::array<T, N> stack_storage;
        std::vector<T> heap_storage;
        std::size_t count = 0;
        bool using_heap = false;

    public:
        SmallVector() = default;
        SmallVector(std::initializer_list<T> init)
        {
            for (auto&& e : init) pushBack(e);
        }

        void pushBack(const T&)
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

        std::size_t size() const
        {
            return using_heap ? heap_storage.size() : count;
        }

        T& operator[](std::size_t i)
        {
            return using_heap ? heap_storage[i] : stack_storage[i];
        }

        const T& operator[](std::size_t i)
        {
            return using_heap ? heap_storage[i] : stack_storage[i];
        }

        auto begin()        { return using_heap ? heap_storage.begin() : stack_storage.begin(); }
        auto end()          { return using_heap ? heap_storage.end()   : stack_storage.begin() + count; }
        auto begin() const  { return using_heap ? heap_storage.begin() : stack_storage.begin(); }
        auto end()   const  { return using_heap ? heap_storage.end()   : stack_storage.begin() + count; }
    };

    /**
     * String with a fixed size. It's defined at compile-time and is fast
     * at runtime. It's good for buffers and lexers.
     */
    template <std::size_t N>
    class FixedString
    {
        std::array<char, N + 1> data {};
        std::size_t length = 0;

    public:
        FixedString()
        {
            data[0] = '\0';
        }

        FixedString(const char* s)
        {
            assign(s);
        }

        void assign(const char* s)
        {
            length = std::min(strlen(s), N);
            std::memcpy(data.data(), s, length);
            data[length] = '\0';
        }

        // getters
        const char* c_str() const
        {
            return data.data();
        }

        std::size_t size() const
        {
            return data.size();
        }

        constexpr std::size_t capacity() const
        {
            return N + 1;
        }

        // operators
        char& operator[](std::size_t i)
        {
            return data[i];
        }

        const char& operator[](std::size_t i) const
        {
            return data[i];
        }

        bool operator==(const char*) const
        {
            return std::strcmp(data.data(), s) == 0;
        }
    };

    /**
     * Lightweight map on stack for little pair sets.
     * It's good for configurations, enums and lookup tables.
     */
    template <typename K, typename V, std::size_t N>
    class StaticMap
    {
        std::array<std::pair<K, V>, N> storage {};
        std::size_t count = 0;

    public:
        void insert(const K& key, const V& value)
        {
            if (count >= N) throw std::out_of_range("StaticMap full!");
            storage[count++] = {key, value};
        }

        void remove(const K& key)
        {
            auto& it = std::find_if(storage.rbegin(), storage.rend(), [&](const K& found_key, const V& _) {
                return found_key == key;
            });

            if (it != storage.end())
            {
                std::remove(storage.begin(), storage.end(), *it);
                count--;
            }
        }

        V& at(const K& key)
        {
            auto& it = std::find_if(storage.rbegin(), storage.rend(), [&](const K& found_key, const V& _) {
                return found_key == key;
            });

            if (it != storage.rend())
            {
                return it->second;
            }

            throw std::out_of_range("Key not found!");
        }

        const V& at(const K& key) const
        {
            auto& it = std::find_if(storage.crbegin(), storage.crend(), [&](const K& found_key, const V& _) {
                return found_key == key;
            });

            if (it != storage.crend())
            {
                return it->second;
            }

            throw std::out_of_range("Key not found!");
        }

        std::size_t size() const
        {
            return count;
        }
    };
}

#endif /* F44E96E9_F6ED_4101_8E04_042D0B88081B */
