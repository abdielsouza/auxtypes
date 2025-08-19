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
        SmallVector(std::initializer_list<T>);

        void pushBack(const T&);
        void pushBack(T&&);
        std::size_t size() const;

        T& operator[](std::size_t);
        const T& operator[](std::size_t) const;

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
        FixedString();
        FixedString(const char*);

        void assign(const char*);

        // getters
        const char* c_str() const;
        std::size_t size() const;
        constexpr std::size_t capacity() const;

        // operators
        char& operator[](std::size_t i);
        const char& operator[](std::size_t i) const;
        bool operator==(const char*) const;
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
        void insert(const K& key, const V& value);
        void remove(const K& key);
        V& at(const K& key);
        const V& at(const K& key) const;
        std::size_t size() const; 
    };
}

#endif /* F44E96E9_F6ED_4101_8E04_042D0B88081B */
