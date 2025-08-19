#include "container.hpp"
#include <algorithm>

namespace auxtypes
{
    template <typename K, typename V, std::size_t N>
    void StaticMap<K, V, N>::insert(const K& key, const V& value)
    {
        if (count >= N) throw std::out_of_range("StaticMap full!");
        storage[count++] = {key, value};
    }

    template <typename K, typename V, std::size_t N>
    void StaticMap<K, V, N>::remove(const K& key)
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

    template <typename K, typename V, std::size_t N>
    V& StaticMap<K, V, N>::at(const K& key)
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

    template <typename K, typename V, std::size_t N>
    const V& StaticMap<K, V, N>::at(const K& key) const
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

    template <typename K, typename V, std::size_t N>
    std::size_t StaticMap<K, V, N>::size() const
    {
        return count;
    }
}