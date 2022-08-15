#ifndef KQUNORDERED_MAP_
#define KQUNORDERED_MAP_

#include "other.h"
#include "vector.h"
#include "single_list.h"

namespace kq
{
   
    template<typename Key, typename T>
    struct bucket
    {
    public:
        using key_type = Key;
        using mapped_type = T;
        using value_type = std::pair<key_type, mapped_type>;

        bucket() : prev_nonempty(nullptr), kq_data(), next_nonempty() {}
        bucket(const bucket& other) : prev_nonempty(other.prev_nonempty), kq_data(other.kq_data), next_nonempty(other.next_nonempty) {}
        bucket(bucket&& other) noexcept : prev_nonempty(other.prev_nonempty), kq_data(std::move(other.kq_data)), next_nonempty(other.next_nonempty) {}

        bucket& operator=(const bucket& other);
        bucket& operator=(bucket&& other) noexcept;

        typename single_list<value_type>::iterator begin() { return kq_data.begin(); }
        typename single_list<value_type>::iterator end() { return kq_data.end(); }
        typename single_list<value_type>::const_iterator begin() const { return kq_data.cbegin(); }
        typename single_list<value_type>::const_iterator end() const { return kq_data.cend(); }
        typename single_list<value_type>::const_iterator cbegin() const { return kq_data.cbegin(); }
        typename single_list<value_type>::const_iterator cend() const { return kq_data.cend(); }

        size_t size() const { return kq_data.size(); }

        value_type& push_back(const value_type& value) { return kq_data.push_back(value); }
        template<typename... Args>
        value_type& emplace_back(Args&&... args) { return kq_data.emplace_back(std::forward<Args>(args)...); }

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
    typename bucket<Key, T>::bucket& bucket<Key, T>::operator=(const bucket& other)
    {
        kq_data = other.kq_data;
        prev_nonempty = other.prev_nonempty;
        next_nonempty = other.next_nonempty;
        return *this;
    }

    template<typename Key, typename T>
    typename bucket<Key, T>::bucket& bucket<Key, T>::operator=(bucket&& other) noexcept
    {
        kq_data = std::move(other.kq_data);
        prev_nonempty = other.prev_nonempty;
        next_nonempty = other.next_nonempty;
        return *this;
    }

    template<typename Key, typename T, bool constant>
    struct um_iterator
    {
    public:
        using key_type = Key;
        using mapped_type = T;
        using value_type = std::pair<Key, T>;
        using reference = typename std::conditional<constant, const value_type&, value_type&>::type;
        using pointer = value_type*;

        um_iterator() : kq_outer(), kq_inner() {}
        um_iterator(typename vector<bucket<key_type, mapped_type>>::iterator outer) : kq_outer(outer), kq_inner(kq_outer->begin()) {}

        bool operator==(const um_iterator& other) const;
        bool operator!=(const um_iterator& other) const;
        bool operator<(const um_iterator& rhs) const;
        bool operator>(const um_iterator& rhs) const;
        bool operator<=(const um_iterator& rhs) const;
        bool operator>=(const um_iterator& rhs) const;

        um_iterator& operator++();
        um_iterator& operator++(int);

        // for debug purposes only
        bucket<key_type, mapped_type>* outer_ptr() { return kq_outer.ptr(); }

        reference operator*() const { return *kq_inner; }
        pointer operator->() const { return kq_inner.ptr(); }

    private:
        typename vector<bucket<key_type, mapped_type>>::iterator kq_outer;
        typename single_list<std::pair<key_type, mapped_type>>::iterator kq_inner;
    };

    template<typename Key, typename T, bool constant>
    bool um_iterator<Key, T, constant>::operator==(const um_iterator& other) const
    {
        if (kq_outer == other.kq_outer)
            return kq_inner == other.kq_inner;
        return false;
    }

    template<typename Key, typename T, bool constant>
    bool um_iterator<Key, T, constant>::operator!=(const um_iterator& other) const
    {
        if (kq_outer == other.kq_outer)
            return kq_inner != other.kq_inner;
        return true;
    }

    template<typename Key, typename T, bool constant>
    bool um_iterator<Key, T, constant>::operator<(const um_iterator& rhs) const
    {
        return kq_outer < rhs.kq_outer;
    }

    template<typename Key, typename T, bool constant>
    bool um_iterator<Key, T, constant>::operator>(const um_iterator& rhs) const
    {
        return kq_outer > rhs.kq_outer;
    }

    template<typename Key, typename T, bool constant>
    bool um_iterator<Key, T, constant>::operator<=(const um_iterator& rhs) const
    {
        return kq_outer <= rhs.kq_outer;
    }

    template<typename Key, typename T, bool constant>
    bool um_iterator<Key, T, constant>::operator>=(const um_iterator& rhs) const
    {
        return kq_outer >= rhs.kq_outer;
    }

    template<typename Key, typename T, bool constant>
    typename um_iterator<Key, T, constant>::um_iterator& um_iterator<Key, T, constant>::operator++()
    {
        ++kq_inner;
        if (kq_outer->end() == kq_inner)
        {
            kq_outer = kq_outer->next_nonempty;
            kq_inner = kq_outer->begin();
        }
        return *this;
    }

    template<typename Key, typename T, bool constant>
    typename um_iterator<Key, T, constant>::um_iterator& um_iterator<Key, T, constant>::operator++(int)
    {
        auto Tmp = *this;
        ++kq_inner;
        if (kq_outer->end() == kq_inner)
        {
            kq_outer = kq_outer->next_nonempty;
            kq_inner = kq_outer->begin();
        }
        return Tmp;
    }

    template<typename Key, typename T, typename Hasher = std::hash<Key>>
    struct unordered_map
    {
    public:

        using key_type = Key;
        using mapped_type = T;
        using value_type = std::pair<key_type, mapped_type>;
        
        using reference = value_type&;
        using pointer = value_type*;

        using iterator = um_iterator<key_type, mapped_type, false>;
        using const_iterator = um_iterator<key_type, mapped_type, true>;


        unordered_map();
        unordered_map(const unordered_map& other);
        unordered_map(unordered_map&& other);

        unordered_map& operator=(const unordered_map& other);
        unordered_map& operator=(unordered_map&& other) noexcept;

        iterator begin()    { return kq_first_nonempty; }
        iterator end()  { return kq_data.end(); }
        const_iterator begin() const { return kq_first_nonempty; }
        const_iterator end() const { return kq_data.end(); }
        const_iterator cbegin() const { return kq_first_nonempty; }
        const_iterator cend() const { return kq_data.end(); }

        size_t size() const { return kq_size; }
        bool empty() const { return kq_size == 0; }
        float load_factor() const { return static_cast<float>(kq_size) / static_cast<float>(kq_bucket_size); }


        mapped_type& insert(const value_type& pair);
        template<typename... Args>
        mapped_type& emplace(Args&&... args);
        
        void erase(iterator pos);
        void clear();
        
        mapped_type& operator[](const key_type& key);
        const mapped_type& operator[](const key_type& key) const;
        mapped_type& at(const key_type& key);
        const mapped_type& at(const key_type& key) const;

        bool contains(const key_type& key) const;

    private:
            void remove_iterator_bucket(typename vector<bucket<key_type, mapped_type>>::iterator it);
            // Function takes care of setting up iterators for amortized O(1) iteration time
            void re_iterator_bucket();
            void add_iterator_bucket(typename vector<bucket<key_type, mapped_type>>::iterator it);

            void rehash(size_t buckets);

    private:
        
        vector<bucket<key_type, mapped_type>> kq_data;
        size_t kq_size;
        size_t kq_bucket_size;
        Hasher kq_hasher;
        typename vector<bucket<key_type, mapped_type>>::iterator kq_first_nonempty;
        typename vector<bucket<key_type, mapped_type>>::iterator kq_last_nonempty;
    };

    template<typename Key, typename T, typename Hasher>
    unordered_map<Key, T, Hasher>::unordered_map()
        : kq_data(8), kq_size(0), kq_bucket_size(8),
        kq_hasher(), kq_first_nonempty(), kq_last_nonempty()
    {
        kq_first_nonempty = kq_data.end();
        kq_last_nonempty  = kq_data.end();
    }

    template<typename Key, typename T, typename Hasher>
    unordered_map<Key, T, Hasher>::unordered_map(const unordered_map& other)
        : kq_data(other.kq_data), kq_size(other.kq_size), kq_bucket_size(other.kq_bucket_size),
        kq_hasher(), kq_first_nonempty(), kq_last_nonempty()
    {
        re_iterator_bucket();
    }

    template<typename Key, typename T, typename Hasher>
    unordered_map<Key, T, Hasher>::unordered_map(unordered_map&& other)
        : kq_data(std::move(other.kq_data)), kq_size(other.kq_size), kq_bucket_size(other.kq_bucket_size),
        kq_hasher(), kq_first_nonempty(other.kq_first_nonempty), kq_last_nonempty(other.kq_last_nonempty)
    {
        other.clear();
    }

    template<typename Key, typename T, typename Hasher>
    unordered_map<Key, T, Hasher>& unordered_map<Key, T, Hasher>::operator=(const unordered_map& other)
    {
        clear();
        kq_data         = other.kq_data;
        kq_size         = other.kq_size;
        kq_bucket_size  = other.kq_bucket_size;
        re_iterator_bucket();
        return *this;
    }

    template<typename Key, typename T, typename Hasher>
    unordered_map<Key, T, Hasher>& unordered_map<Key, T, Hasher>::operator=(unordered_map&& other) noexcept
    {
        clear();
        kq_first_nonempty   = other.kq_first_nonempty;
        kq_last_nonempty    = other.kq_last_nonempty;
        kq_data             = std::move(other.kq_data);
        kq_size             = other.kq_size;
        kq_bucket_size      = other.kq_bucket_size;
        // kq_hasher is probably the same since Key is the same
        

        other.kq_data.resize(8);
        other.kq_bucket_size    = 8;
        other.kq_size           = 0;
        other.kq_first_nonempty = other.kq_last_nonempty;

        return *this;
    }

    template<typename Key, typename T, typename Hasher>
    typename unordered_map<Key, T, Hasher>::mapped_type& unordered_map<Key, T, Hasher>::insert(const value_type& pair)
    {
        if (contains(pair.first) == 0)
        {
            //std::cout << pair.first << '\n';
            if (load_factor() >= 0.9f)
            {
                rehash(kq_bucket_size * 2);
            }
            size_t bucket_index = kq_hasher(pair.first) % kq_bucket_size;
            value_type& ref = kq_data[bucket_index].push_back(pair);
            ++kq_size;
            // if bucket was empty, add to iterator list
            if (kq_data[bucket_index].size() == 1)
            {
                add_iterator_bucket(kq_data.begin() + bucket_index);
            }
            return ref.second;
        }
        return (*this)[pair.first];
    }

    template<typename Key, typename T, typename Hasher>
    template<typename... Args>
    typename unordered_map<Key, T, Hasher>::mapped_type& unordered_map<Key, T, Hasher>::emplace(Args&&... args)
    {
        value_type pair{std::forward<Args>(args)...};
        if (contains(pair.first) == 0)
        {
            //std::cout << pair.first << '\n';
            if (load_factor() >= 0.9f)
            {
                rehash(kq_bucket_size * 2);
            }
            size_t bucket_index = kq_hasher(pair.first) % kq_bucket_size;
            value_type& ref = kq_data[bucket_index].emplace_back(std::move(pair));
            ++kq_size;
            // if bucket was empty, add to iterator list
            if (kq_data[bucket_index].size() == 1)
            {
                add_iterator_bucket(kq_data.begin() + bucket_index);
            }
            return ref.second;
        }
        return (*this)[pair.first];
    }

    template<typename Key, typename T, typename Hasher>
    void unordered_map<Key, T, Hasher>::erase(iterator pos)
    {
        if (pos >= begin() && pos < end() && kq_size != 0)
        {
            bucket<key_type, mapped_type>& bucket = *(pos.outer_ptr);
            bucket.erase(*pos);
            --kq_size;
        }
    }

    template<typename Key, typename T, typename Hasher>
    void unordered_map<Key, T, Hasher>::clear()
    {
        kq_data.clear();
        kq_size = 0;
        kq_bucket_size = 8;
        kq_data.resize(8);
        kq_first_nonempty = kq_data.end();
        kq_last_nonempty = kq_data.end();
    }

    template<typename Key, typename T, typename Hasher>
    typename unordered_map<Key, T, Hasher>::mapped_type& unordered_map<Key, T, Hasher>::operator[](const key_type& key)
    {
        if (contains(key) == false)
        {
            //FIXME: I think the standard requires this to be emplace instead of insert
            return insert({ key, mapped_type{} });
        }
        else
        {
            size_t bucket_to_search = kq_hasher(key) % kq_bucket_size;
            for (auto& pair : kq_data[bucket_to_search])
            {
                if (pair.first == key)
                    return pair.second;
            }
        }
    }

    template<typename Key, typename T, typename Hasher>
    const typename unordered_map<Key, T, Hasher>::mapped_type& unordered_map<Key, T, Hasher>::operator[](const key_type& key) const
    {
        if (contains(key) == false)
        {
            //FIXME: I think the standard requires this to be emplace instead of insert
            return insert({ key, mapped_type{} });
        }
        else
        {
            size_t bucket_to_search = kq_hasher(key) % kq_bucket_size;
            for (auto& pair : kq_data[bucket_to_search])
            {
                if (pair.first == key)
                    return pair.second;
            }
        }
    }

    template<typename Key, typename T, typename Hasher>
    typename unordered_map<Key, T, Hasher>::mapped_type& unordered_map<Key, T, Hasher>::at(const key_type& key)
    {
        size_t bucket_to_search = kq_hasher(key) % kq_bucket_size;
        for (auto& pair : kq_data[bucket_to_search])
        {
            if (pair.first == key)
                return pair.second;
        }
        throw std::out_of_range("element with key not found");
    }

    template<typename Key, typename T, typename Hasher>
    const typename unordered_map<Key, T, Hasher>::mapped_type& unordered_map<Key, T, Hasher>::at(const key_type& key) const
    {
        size_t bucket_to_search = kq_hasher(key) % kq_bucket_size;
        for (auto& pair : kq_data[bucket_to_search])
        {
            if (pair.first == key)
                return pair.second;
        }
        throw std::out_of_range("element with key not found");
    }

    template<typename Key, typename T, typename Hasher>
    bool unordered_map<Key, T, Hasher>::contains(const key_type& key) const
    {
        size_t bucket_to_search = kq_hasher(key) % kq_bucket_size;
        for (const auto& pair : kq_data[bucket_to_search])
        {
            if (pair.first == key)
                return true;
        }
        return false;
    }

    template<typename Key, typename T, typename Hasher>
    void unordered_map<Key, T, Hasher>::remove_iterator_bucket(typename vector<bucket<key_type, mapped_type>>::iterator it)
    {
        if (it == kq_first_nonempty)
        {
            //std::cout << "Removed first bucket\n";
            kq_first_nonempty = it->next_nonempty;
        }
        else if (it == kq_last_nonempty)
        {
            //std::cout << "Removed last bucket\n";
            kq_last_nonempty = it->prev_nonempty;
            kq_last_nonempty->next_nonempty = kq_data.end();

        }
        else
        {
            //std::cout << "Removed not first bucket\n";
            it->prev_nonempty->next_nonempty = it->next_nonempty;
            it->next_nonempty->prev_nonempty = it->prev_nonempty;
        }
    }

    // Function takes care of setting up iterators for amortized O(1) iteration time
    template<typename Key, typename T, typename Hasher>
    void unordered_map<Key, T, Hasher>::re_iterator_bucket()
    {
        kq_first_nonempty = kq_data.end();
        kq_last_nonempty = kq_data.end();
        for (auto it = kq_data.begin(); it != kq_data.end(); ++it)
        {
            if (it->empty() == false)
                add_iterator_bucket(it);
        }
    }

    template<typename Key, typename T, typename Hasher>
    void unordered_map<Key, T, Hasher>::add_iterator_bucket(typename vector<bucket<key_type, mapped_type>>::iterator it)
    {
        if (kq_first_nonempty == kq_data.end())
        {
            //std::cout << "First bucket added to list\n";
            kq_first_nonempty = it;
            kq_last_nonempty = it;
            it->prev_nonempty = nullptr;
            it->next_nonempty = kq_data.end();
        }
        else
        {
            //std::cout << "More bucket added to list\n";             
            kq_last_nonempty->next_nonempty = it;
            it->prev_nonempty = kq_last_nonempty;
            kq_last_nonempty = it;
            it->next_nonempty = kq_data.end();
        }
    }

    template<typename Key, typename T, typename Hasher>
    void unordered_map<Key, T, Hasher>::rehash(size_t buckets)
    {
        //std::cout << "REHASHING\n";
        size_t old_bucket_size = kq_bucket_size;
        kq_bucket_size = buckets;

        vector<bucket<key_type, mapped_type>> new_data(buckets);

        //std::cout << "STARTED LOOPING\n";
        for (size_t old_bucket_index = 0; old_bucket_index < old_bucket_size; ++old_bucket_index)
        {

            if (kq_data[old_bucket_index].empty() == 0)
            {
                for (typename single_list<value_type>::iterator it = kq_data[old_bucket_index].kq_data.begin();
                    it != kq_data[old_bucket_index].kq_data.end(); ++it)
                {
                    //std::cout << it->first << '\n';
                    size_t new_bucket_location = kq_hasher(it->first) % kq_bucket_size;
                    new_data[new_bucket_location].emplace_back(std::move(*it));
                }
            }
        }
        kq_data = std::move(new_data);



        //std::cout << "DONE LOOPING\n";
        re_iterator_bucket();
    }



} // namespace kq

#endif


/*
void rehash(size_t buckets)
        {
            std::cout << "REHASHING\n";
            size_t old_bucket_size = kq_bucket_size;
            kq_bucket_size = buckets;
            kq_data.resize(buckets);

            print();

            std::cout << "STARTED LOOPING\n";
            size_t bid = 0;
            size_t eid = 0;
            for (size_t old_bucket_index = 0; old_bucket_index < old_bucket_size; ++old_bucket_index)
            {

                if (kq_data[old_bucket_index].empty() == 0)
                {
                    for (typename single_list<value_type>::iterator it = kq_data[old_bucket_index].kq_data.begin();
                        it != kq_data[old_bucket_index].kq_data.end(); ++it)
                    {
                        std::cout << bid << "." << eid << '\n';
                        size_t new_bucket_location = kq_hasher(it->first) % kq_bucket_size;
                        if (new_bucket_location != old_bucket_index)
                        {
                            auto Tmp = std::move(*it);
                            kq_data[old_bucket_index].erase(it);

                            kq_data[new_bucket_location].emplace_back(std::move(Tmp));

                        }
                        ++eid;
                    }
                }
                ++bid;
                eid = 0;
            }
            std::cout << "DONE LOOPING\n";
            re_iterator_bucket();
            std::cout << "DONE REHASHING\n";
        }
*/