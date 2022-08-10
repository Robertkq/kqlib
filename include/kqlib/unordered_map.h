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

        typename single_list<value_type>::iterator begin() { return kq_data.begin(); }
        typename single_list<value_type>::iterator end() { return kq_data.end(); }
        typename single_list<value_type>::const_iterator begin() const { return kq_data.cbegin(); }
        typename single_list<value_type>::const_iterator end() const { return kq_data.cend(); }
        typename single_list<value_type>::const_iterator cbegin() const { return kq_data.cbegin(); }
        typename single_list<value_type>::const_iterator cend() const { return kq_data.cend(); }

        size_t size() const { return kq_data.size(); }

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

    template<typename Key, typename T>
    struct um_iterator
    {
    public:
        using key_type = Key;
        using mapped_type = T;

        um_iterator() : kq_outer(), kq_inner() {}
        um_iterator(typename vector<bucket<key_type, mapped_type>>::iterator outer) : kq_outer(outer), kq_inner(kq_outer->begin())
        {
            std::cout << "it made: " << kq_outer.ptr() << '\n';
        }

        bool operator==(const um_iterator& other)
        {
            if (kq_outer == other.kq_outer)
                return kq_inner == other.kq_inner;
            return false;
        }

        bool operator!=(const um_iterator& other) { return !(*this == other); }

        um_iterator& operator++()
        {
            std::cout << "here";
            if (kq_outer->end() == kq_inner)
            {
                ++kq_outer;
                kq_inner = kq_outer->begin();
            }
            else ++kq_inner;
            return *this;
        }

        

        std::pair<key_type, mapped_type>& operator*() { std::cout << kq_inner.ptr() << '\n'; return *kq_inner; }

    private:
        typename vector<bucket<key_type, mapped_type>>::iterator kq_outer;
        typename single_list<std::pair<key_type, mapped_type>>::iterator kq_inner;
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

        using iterator = um_iterator<key_type, mapped_type>;


        unordered_map();
        unordered_map(const unordered_map& other); // FIXME: implement
        unordered_map(unordered_map&& other); // FIXME: implement

        unordered_map& operator=(const unordered_map& other); // FIXME: implement
        unordered_map& operator=(unordered_map&& other); // FIXME: implement

        void insert(const value_type& pair) 
        {  
            if (contains(pair.first) == 0)
            {
                std::cout << pair.first << '\n';
                if (load_factor() >= 0.9f)
                {
                    
                    rehash(kq_bucket_size * 2);
                }
                size_t bucket_index = kq_hasher(pair.first) % kq_bucket_size;
                kq_data[bucket_index].push_back(pair);
                ++kq_size;
                // if bucket was empty, add to iterator list
            }
        };

        iterator begin()    { return kq_first_nonempty; }
        iterator end()      { return kq_last_empty; }

        //FIXME: add const method
        value_type& at(const key_type& key)
        {
            size_t bucket_to_search = kq_hasher(key) % kq_bucket_size;
            for (auto& pair : kq_data[bucket_to_search])
            {
                if (pair.first == key)
                    return pair;
            }
            throw std::out_of_range("element with key not found");
        }

        bool contains(const key_type& key) const
        {
            size_t bucket_to_search = kq_hasher(key) % kq_bucket_size;
            for (const auto& pair : kq_data[bucket_to_search])
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
                        
                        size_t new_bucket_location = kq_hasher(it->first) % kq_bucket_size;
                        if (new_bucket_location != old_bucket_index)
                        {
                            auto Tmp = std::move(*it);
                            kq_data[old_bucket_index].erase(it);
                            kq_data[new_bucket_location].emplace_back(std::move(Tmp));
                        }
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
                    std::cout << "Bucket " << bid << ": " << &bucket << "\n";
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
        
        vector<bucket<key_type, mapped_type>> kq_data;
        size_t kq_size;
        size_t kq_bucket_size;
        Hasher kq_hasher;
        typename vector<bucket<key_type, mapped_type>>::iterator kq_first_nonempty;
        typename vector<bucket<key_type, mapped_type>>::iterator kq_last_empty;
    };

    template<typename Key, typename T, typename Hasher>
    unordered_map<Key, T, Hasher>::unordered_map()
        : kq_data(), kq_size(0), kq_bucket_size(8), 
        kq_hasher(), kq_first_nonempty(nullptr), kq_last_empty(nullptr)
                                            // copy constructor to make sure they have the same address
    {
        // FIXME: fix vector's constructor with size OR LOOK AT IT SMTH WRONG WITH IT
        kq_data.resize(8);
    }



} // namespace kq

#endif