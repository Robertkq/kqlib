#ifndef kqunordered_map_
#define kqunordered_map_

#include "other.h"
#include "vector.h"
#include "single_list.h"
#include <vector>

namespace kq
{
   
    template<typename Key, typename T>
    struct bucket
    {
    public:
        using key_type = Key;
        using mapped_type = T;
        using value_type = std::pair<key_type, mapped_type>;

        void push_back(const value_type& value) { kq_data.push_back(value); }
        template<typename... Args>
        void emplace_back(Args&&... args) { kq_data.emplace_back(std::forward<Args>(args)...); }

        void pop_back() { kq_data.pop_back(); }
        void pop_front() { kq_data.pop_front(); }
        void erase(typename single_list<value_type>::iterator pos) { kq_data.erase(pos); }
        void clear() { kq_data.clear(); }

        bool empty() { return kq_data.empty(); }

        typename kq::vector<bucket<Key, T>>::iterator prev_nonempty;
        single_list<value_type> kq_data;
        typename kq::vector<bucket<Key, T>>::iterator next_nonempty;

    };

    template<typename Key, typename T, typename Hasher = std::hash<Key>>
    struct unordered_map
    {
    public:

        using key_type = Key;
        using mapped_type = T;
        using value_type = std::pair<key_type, mapped_type>;
        
        using reference = value_type&;
        using pointer = value_type*;


        unordered_map();
        unordered_map(const unordered_map& other); // FIXME: implement
        unordered_map(unordered_map&& other); // FIXME: implement

        unordered_map& operator=(const unordered_map& other); // FIXME: implement
        unordered_map& operator=(unordered_map&& other); // FIXME: implement

        void insert(const value_type& pair) 
        {
            if (contains(pair.first) == 0)
            {
                if (load_factor() >= 0.9f)
                {
                    rehash(kq_bucket_size * 2);
                }
                size_t bucket_index = kq_hasher(pair.first) % kq_bucket_size;
                kq_data[bucket_index].push_back(pair);
                ++kq_size;
            }
        };

        //FIXME: add const method
        value_type& at(const key_type& key)
        {
            size_t bucket_to_search = kq_hasher(key);
            for (auto& pair : kq_data[bucket_to_serach])
            {
                if (pair.first == key)
                    return pair;
            }
            throw std::out_of_range("element with key not found");
        }

        bool contains(const key_type& key) const
        {
            size_t bucket_to_search = kq_hasher(key);
            for (const auto& pair : kq_data[bucket_to_serach])
            {
                if (pair.first == key)
                    return true;
            }
            return false;
        }

        float load_factor() const { return static_cast<float>(kq_size) / static_cast<float>(kq_bucket_size); }

        void rehash(size_t buckets) 
        {
            size_t old_bucket_size = kq_bucket_size;
            kq_bucket_size = buckets;
            kq_data.resize(buckets);

            print();

            for (size_t old_bucket_index = 0; old_bucket_index < old_bucket_size; ++old_bucket_index)
            {
                if (kq_data[old_bucket_index].empty() == 0)
                {
                    for (typename single_list<value_type>::iterator it = kq_data[old_bucket_index].kq_data.begin();
                        it != kq_data[old_bucket_index].kq_data.end(); ++it)
                    {
                        std::cout << "Checking " << it->first;
                        if (kq_hasher(it->first) != old_bucket_index)
                        {
                            std::cout  << " has a different bucket index value now, CHECK\n";
                        }
                        else std::cout  << " doesnt have a different bucket value\n";
                    }
                }
            }

        }

        void print()
        {
            uint32_t bid = 0;
            for (auto& bucket : kq_data)
            {
                if (bucket.empty() == 0)
                {
                    std::cout << "Bucket " << bid << "\n";
                    for (auto& pair : bucket.kq_data)
                    {
                        std::cout << pair.first << " " << pair.second << '\n';
                    }
                }
                ++bid;
            }
            std::cout << '\n';
        }

    private:
        Hasher kq_hasher;
        vector<bucket<key_type, mapped_type>> kq_data;
        size_t kq_size;
        size_t kq_bucket_size;
        
    };

    template<typename Key, typename T, typename Hasher>
    unordered_map<Key, T, Hasher>::unordered_map()
        : kq_data(), kq_size(0), kq_bucket_size(8)
    {
        kq_data.resize(8);
    }



} // namespace kq

#endif