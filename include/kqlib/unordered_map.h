#ifndef KQUNORDERED_MAP_
#define KQUNORDERED_MAP_

#include "other.h"
#include "vector.h"
#include "single_list.h"
#include "pair.h"

//#include <iostream>

namespace kq
{
   
    template<typename Key, typename T>
    struct bucket
    {
    public:
        using key_type = Key;
        using mapped_type = T;
        using value_type = kq::pair<key_type, mapped_type>;

        bucket() : prev_nonempty(nullptr), m_data(), next_nonempty() {}
        bucket(const bucket& other) : prev_nonempty(other.prev_nonempty), m_data(other.m_data), next_nonempty(other.next_nonempty) {}
        bucket(bucket&& other) noexcept : prev_nonempty(other.prev_nonempty), m_data(std::move(other.m_data)), next_nonempty(other.next_nonempty) {}

        bucket& operator=(const bucket& other);
        bucket& operator=(bucket&& other) noexcept;

        typename single_list<value_type>::iterator begin() { return m_data.begin(); }
        typename single_list<value_type>::iterator end() { return m_data.end(); }
        typename single_list<value_type>::const_iterator begin() const { return m_data.cbegin(); }
        typename single_list<value_type>::const_iterator end() const { return m_data.cend(); }
        typename single_list<value_type>::const_iterator cbegin() const { return m_data.cbegin(); }
        typename single_list<value_type>::const_iterator cend() const { return m_data.cend(); }

        size_t size() const { return m_data.size(); }

        value_type& push_back(const value_type& value) { return m_data.push_back(value); }
        template<typename... Args>
        value_type& emplace_back(Args&&... args) { return m_data.emplace_back(std::forward<Args>(args)...); }

        void pop_back() { m_data.pop_back(); }
        void pop_front() { m_data.pop_front(); }
        void erase(typename single_list<value_type>::iterator pos) { m_data.erase(pos); }
        void clear() { m_data.clear(); }

        bool empty() { return m_data.empty(); }

        typename kq::vector<bucket<Key, T>>::iterator prev_nonempty;
        single_list<value_type> m_data;
        typename kq::vector<bucket<Key, T>>::iterator next_nonempty;

    };

    template<typename Key, typename T>
    typename bucket<Key, T>::bucket& bucket<Key, T>::operator=(const bucket& other)
    {
        if (this != &other)
        {
            m_data = other.m_data;
            prev_nonempty = other.prev_nonempty;
            next_nonempty = other.next_nonempty;
        }
        return *this;
    }

    template<typename Key, typename T>
    typename bucket<Key, T>::bucket& bucket<Key, T>::operator=(bucket&& other) noexcept
    {
        if (this != &other)
        {
            m_data = std::move(other.m_data);
            prev_nonempty = other.prev_nonempty;
            next_nonempty = other.next_nonempty;
        }
        return *this;
    }

    template<typename Key, typename T, bool constant>
    struct um_iterator
    {
    public:
        using key_type = Key;
        using mapped_type = T;
        using value_type = kq::pair<Key, T>;
        using pointer = value_type*;
        using reference = typename std::conditional<constant, const value_type&, value_type&>::type;
        using iterator_category = std::forward_iterator_tag;
        

        um_iterator() : m_outer(), m_inner() {}
        um_iterator(const um_iterator& other) : m_outer(other.m_outer), m_inner(other.m_inner) {}
        um_iterator(um_iterator&& other) noexcept : m_outer(other.m_outer), m_inner(other.m_inner) {}
        um_iterator(typename vector<bucket<key_type, mapped_type>>::iterator outer) : m_outer(outer), m_inner(m_outer->begin()) {}
        um_iterator(typename vector<bucket<key_type, mapped_type>>::iterator outer, typename single_list<value_type>::iterator inner) : m_outer(outer), m_inner(inner) {}

        um_iterator& operator=(const um_iterator& other);
        um_iterator& operator=(um_iterator&& other) noexcept;

        bool operator==(const um_iterator& other) const;
        bool operator!=(const um_iterator& other) const;
        bool operator<(const um_iterator& rhs) const;
        bool operator>(const um_iterator& rhs) const;
        bool operator<=(const um_iterator& rhs) const;
        bool operator>=(const um_iterator& rhs) const;

        um_iterator& operator++();
        um_iterator& operator++(int);

        bucket<key_type, mapped_type>* outer_ptr() const { return m_outer.ptr(); }
        value_type* inner_ptr() const { return m_inner.ptr(); }

        const typename vector<bucket<key_type, mapped_type>>::iterator& get_outer() const { return m_outer; }
        const typename single_list<value_type>::iterator& get_inner() const { return m_inner; }

        reference operator*() const { return *m_inner; }
        pointer operator->() const { return m_inner.ptr(); }

    private:
        typename vector<bucket<key_type, mapped_type>>::iterator m_outer;
        typename single_list<value_type>::iterator m_inner;
    };

    template<typename Key, typename T, bool constant>
    um_iterator<Key, T, constant>& um_iterator<Key, T, constant>::operator=(const um_iterator& other)
    {
        if (this != &other)
        {
            m_outer = other.m_outer;
            m_inner = other.m_inner;
        }
        return *this;
    }

    template<typename Key, typename T, bool constant>
    um_iterator<Key, T, constant>& um_iterator<Key, T, constant>::operator=(um_iterator&& other) noexcept
    {
        if (this != &other)
        {
            m_outer = other.m_outer;
            m_inner = other.m_inner;
            other.m_outer = nullptr;
            other.m_inner = nullptr;
        }
        return *this;
    }

    template<typename Key, typename T, bool constant>
    bool um_iterator<Key, T, constant>::operator==(const um_iterator& other) const
    {
        if (m_outer == other.m_outer)
            if (m_inner == nullptr || other.m_inner == nullptr)
                return true;
            else return m_inner == other.m_inner;
        return false;
    }

    template<typename Key, typename T, bool constant>
    bool um_iterator<Key, T, constant>::operator!=(const um_iterator& other) const
    {
        if (m_outer == other.m_outer)
            if (m_inner == nullptr || other.m_inner == nullptr)
                return false;
            else return m_inner != other.m_inner;
        return true;
    }

    template<typename Key, typename T, bool constant>
    bool um_iterator<Key, T, constant>::operator<(const um_iterator& rhs) const
    {
        return m_outer < rhs.m_outer;
    }

    template<typename Key, typename T, bool constant>
    bool um_iterator<Key, T, constant>::operator>(const um_iterator& rhs) const
    {
        return m_outer > rhs.m_outer;
    }

    template<typename Key, typename T, bool constant>
    bool um_iterator<Key, T, constant>::operator<=(const um_iterator& rhs) const
    {
        return m_outer <= rhs.m_outer;
    }

    template<typename Key, typename T, bool constant>
    bool um_iterator<Key, T, constant>::operator>=(const um_iterator& rhs) const
    {
        return m_outer >= rhs.m_outer;
    }

    template<typename Key, typename T, bool constant>
    typename um_iterator<Key, T, constant>::um_iterator& um_iterator<Key, T, constant>::operator++()
    {
        ++m_inner;
        if (m_outer->end() == m_inner)
        {
            m_outer = m_outer->next_nonempty;
            m_inner = m_outer->begin();
               
        }
        return *this;
    }

    template<typename Key, typename T, bool constant>
    typename um_iterator<Key, T, constant>::um_iterator& um_iterator<Key, T, constant>::operator++(int)
    {
        auto Tmp = *this;
        ++m_inner;
        if (m_outer->end() == m_inner)
        {
            m_outer = m_outer->next_nonempty;
            m_inner = m_outer->begin();
        }
        return Tmp;
    }

    template<typename Key, typename T, typename Hasher = std::hash<Key>>
    struct unordered_map
    {
    public:

        using key_type = Key;
        using mapped_type = T;
        using value_type = kq::pair<key_type, mapped_type>;
        
        using reference = value_type&;
        using pointer = value_type*;

        using iterator = um_iterator<key_type, mapped_type, false>;
        using const_iterator = um_iterator<key_type, mapped_type, true>;


        unordered_map();
        unordered_map(const unordered_map& other);
        unordered_map(unordered_map&& other) noexcept;
        unordered_map(size_t bucket_count);
        template<typename iterType, typename std::enable_if<is_iterator<iterType>::value, int>::type = 0>
        unordered_map(iterType first, iterType last);
        unordered_map(const std::initializer_list<value_type>& ilist);

        unordered_map& operator=(const unordered_map& other);
        unordered_map& operator=(unordered_map&& other) noexcept;

        unordered_map& operator=(const std::initializer_list<value_type>& il);

        iterator begin()    { return m_first_nonempty; }
        iterator end()  { return { m_data.end(), nullptr }; }
        const_iterator begin() const { return m_first_nonempty; }
        const_iterator end() const { return { m_data.end(), nullptr}; }
        const_iterator cbegin() const { return m_first_nonempty; }
        const_iterator cend() const { return { m_data.end(), nullptr }; }

        size_t size() const { return m_size; }
        bool empty() const { return m_size == 0; }
        float load_factor() const { return static_cast<float>(m_size) / static_cast<float>(m_bucket_size); }
        size_t bucket_count() const { return m_bucket_size; }


        mapped_type& insert(const value_type& pair);
        template<typename... Args>
        mapped_type& emplace(Args&&... args);
        
        void erase(iterator pos);
        void erase(const key_type& key);
        void clear();
        
        mapped_type& operator[](const key_type& key);
        const mapped_type& operator[](const key_type& key) const;
        mapped_type& at(const key_type& key);
        const mapped_type& at(const key_type& key) const;

        bool contains(const key_type& key) const;
        void reserve(size_t buckets);
        void swap(unordered_map& other);

    private:
            void remove_iterator_bucket(typename vector<bucket<key_type, mapped_type>>::iterator it);
            // Function takes care of setting up iterators for amortized O(1) iteration time
            void re_iterator_bucket();
            void add_iterator_bucket(typename vector<bucket<key_type, mapped_type>>::iterator it);

            bool validIterator(iterator it);

            void rehash(size_t buckets);

    private:
        
        vector<bucket<key_type, mapped_type>> m_data;
        size_t m_size;
        size_t m_bucket_size;
        Hasher m_hasher;
        typename vector<bucket<key_type, mapped_type>>::iterator m_first_nonempty;
        typename vector<bucket<key_type, mapped_type>>::iterator m_last_nonempty;
    };

    template<typename Key, typename T, typename Hasher>
    unordered_map<Key, T, Hasher>::unordered_map()
        : m_data(8), m_size(0), m_bucket_size(8),
        m_hasher(), m_first_nonempty(m_data.end()), m_last_nonempty(m_data.end())
    {}

    template<typename Key, typename T, typename Hasher>
    unordered_map<Key, T, Hasher>::unordered_map(const unordered_map& other)
        : m_data(other.m_data), m_size(other.m_size), m_bucket_size(other.m_bucket_size),
        m_hasher(), m_first_nonempty(), m_last_nonempty()
    {
        re_iterator_bucket();
    }

    template<typename Key, typename T, typename Hasher>
    unordered_map<Key, T, Hasher>::unordered_map(unordered_map&& other) noexcept
        : m_data(std::move(other.m_data)), m_size(other.m_size), m_bucket_size(other.m_bucket_size),
        m_hasher(), m_first_nonempty(other.m_first_nonempty), m_last_nonempty(other.m_last_nonempty)
    {
        other.clear();
    }

    template<typename Key, typename T, typename Hasher>
    unordered_map<Key, T, Hasher>::unordered_map(size_t bucket_count)
        : m_data(bucket_count), m_size(0), m_bucket_size(bucket_count),
        m_hasher(), m_first_nonempty(m_data.end()), m_last_nonempty(m_data.end())
    {}
    
    template<typename Key, typename T, typename Hasher>
    template<typename iterType, typename std::enable_if<is_iterator<iterType>::value, int>::type>
    unordered_map<Key, T, Hasher>::unordered_map(iterType first, iterType last)
        : unordered_map()
    {
        for (; first != last; ++first)
            insert(*first);
    }

    template<typename Key, typename T, typename Hasher>
    unordered_map<Key, T, Hasher>::unordered_map(const std::initializer_list<value_type>& ilist)
        : m_data(ilist.size() * 2), m_size(0), m_bucket_size(ilist.size() * 2),
        m_hasher(), m_first_nonempty(m_data.end()), m_last_nonempty(m_data.end())
    {
        for (auto it = ilist.begin(); it != ilist.end(); ++it)
            insert(*it);
    }

    template<typename Key, typename T, typename Hasher>
    unordered_map<Key, T, Hasher>& unordered_map<Key, T, Hasher>::operator=(const unordered_map& other)
    {
        if (this != &other)
        {
            clear();
            m_data = other.m_data;
            m_size = other.m_size;
            m_bucket_size = other.m_bucket_size;
            re_iterator_bucket();
        }
        return *this;
    }

    template<typename Key, typename T, typename Hasher>
    unordered_map<Key, T, Hasher>& unordered_map<Key, T, Hasher>::operator=(unordered_map&& other) noexcept
    {
        if (this != &other)
        {
            clear();
            m_first_nonempty = other.m_first_nonempty;
            m_last_nonempty = other.m_last_nonempty;
            m_data = std::move(other.m_data);
            m_size = other.m_size;
            m_bucket_size = other.m_bucket_size;
            // m_hasher is probably the same since Key is the same


            other.m_data.resize(8);
            other.m_bucket_size = 8;
            other.m_size = 0;
            other.m_first_nonempty = other.m_last_nonempty;
        }

        return *this;
    }

    template<typename Key, typename T, typename Hasher>
    unordered_map<Key, T, Hasher>& unordered_map<Key, T, Hasher>::operator=(const std::initializer_list<value_type>& il)
    {
        clear();
        reserve(il.size());
        for (auto it = il.begin(); it != il.end(); ++it)
            insert(*it);
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
                rehash(m_bucket_size * 2);
            }
            size_t bucket_index = m_hasher(pair.first) % m_bucket_size;
            value_type& ref = m_data[bucket_index].push_back(pair);
            ++m_size;
            // if bucket was empty, add to iterator list
            if (m_data[bucket_index].size() == 1)
            {
                add_iterator_bucket(m_data.begin() + bucket_index);
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
                rehash(m_bucket_size * 2);
            }
            size_t bucket_index = m_hasher(pair.first) % m_bucket_size;
            value_type& ref = m_data[bucket_index].emplace_back(std::move(pair));
            ++m_size;
            // if bucket was empty, add to iterator list
            if (m_data[bucket_index].size() == 1)
            {
                add_iterator_bucket(m_data.begin() + bucket_index);
            }
            return ref.second;
        }
        return (*this)[pair.first];
    }

    template<typename Key, typename T, typename Hasher>
    void unordered_map<Key, T, Hasher>::erase(iterator pos)
    {
        if (validIterator(pos) && m_size != 0)
        {
            bucket<key_type, mapped_type>& bucket = *(pos.get_outer());
            bucket.erase(pos.get_inner());
            if (bucket.empty() == true)
            {
                remove_iterator_bucket(pos.get_outer());
            }
            --m_size;
        }
    }

    template<typename Key, typename T, typename Hasher>
    void unordered_map<Key, T, Hasher>::erase(const key_type& key)
    {
        if (m_size != 0 && contains(key) == true)
        {
            size_t bucket = m_hasher(key) % m_bucket_size;
            for (auto it = m_data[bucket].begin(); it != m_data[bucket].end(); ++it)
            {
                if (it->first == key)
                {
                    m_data[bucket].erase(it);
                    if (m_data[bucket].empty() == true)
                    {
                        remove_iterator_bucket(m_data.begin() + bucket);
                    }
                    --m_size;
                    return;
                }
            }
        }
    }

    template<typename Key, typename T, typename Hasher>
    void unordered_map<Key, T, Hasher>::clear()
    {
        m_data.clear();
        m_size = 0;
        m_bucket_size = 8;
        m_data.resize(8);
        m_first_nonempty = m_data.end();
        m_last_nonempty = m_data.end();
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
            size_t bucket_to_search = m_hasher(key) % m_bucket_size;
            for (auto& pair : m_data[bucket_to_search])
            {
                //if (pair.first == key)
                if (equal_to<key_type>{}(pair.first, key))
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
            size_t bucket_to_search = m_hasher(key) % m_bucket_size;
            for (auto& pair : m_data[bucket_to_search])
            {
                //if (pair.first == key)
                if (equal_to<key_type>{}(pair.first, key))
                    return pair.second;
            }
        }
    }

    template<typename Key, typename T, typename Hasher>
    typename unordered_map<Key, T, Hasher>::mapped_type& unordered_map<Key, T, Hasher>::at(const key_type& key)
    {
        size_t bucket_to_search = m_hasher(key) % m_bucket_size;
        for (auto& pair : m_data[bucket_to_search])
        {
            //if (pair.first == key)
            if (equal_to<key_type>{}(pair.first, key))
                return pair.second;
        }
        throw std::out_of_range("element with key not found");
    }

    template<typename Key, typename T, typename Hasher>
    const typename unordered_map<Key, T, Hasher>::mapped_type& unordered_map<Key, T, Hasher>::at(const key_type& key) const
    {
        size_t bucket_to_search = m_hasher(key) % m_bucket_size;
        for (auto& pair : m_data[bucket_to_search])
        {
            //if (pair.first == key)
            if (equal_to<key_type>{}(pair.first, key))
                return pair.second;
        }
        throw std::out_of_range("element with key not found");
    }

    template<typename Key, typename T, typename Hasher>
    bool unordered_map<Key, T, Hasher>::contains(const key_type& key) const
    {
        size_t bucket_to_search = m_hasher(key) % m_bucket_size;
        for (const auto& pair : m_data[bucket_to_search])
        {
            //if (pair.first == key)
            if (equal_to<key_type>{}(pair.first, key))
                return true;
        }
        return false;
    }

    template<typename Key, typename T, typename Hasher>
    void unordered_map<Key, T, Hasher>::reserve(size_t buckets)
    {
        if (m_bucket_size < buckets)
        {
            rehash(buckets);
        }
    }

    template<typename Key, typename T, typename Hasher>
    void unordered_map<Key, T, Hasher>::swap(unordered_map& other)
    {
        m_data.swap(other.m_data);
        kq::swap(m_size, other.m_size);
        kq::swap(m_bucket_size, other.m_bucket_size);
        kq::swap(m_first_nonempty, other.m_first_nonempty);
        kq::swap(m_last_nonempty, other.m_last_nonempty);
    }

    template<typename Key, typename T, typename Hasher>
    void unordered_map<Key, T, Hasher>::remove_iterator_bucket(typename vector<bucket<key_type, mapped_type>>::iterator it)
    {
        if (it == m_first_nonempty)
        {
            //std::cout << "Removed first bucket\n";
            m_first_nonempty = it->next_nonempty;
        }
        else if (it == m_last_nonempty)
        {
            //std::cout << "Removed last bucket\n";
            m_last_nonempty = it->prev_nonempty;
            m_last_nonempty->next_nonempty = m_data.end();

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
        m_first_nonempty = m_data.end();
        m_last_nonempty = m_data.end();
        for (auto it = m_data.begin(); it != m_data.end(); ++it)
        {
            if (it->empty() == false)
                add_iterator_bucket(it);
        }
    }
    template<typename Key, typename T, typename Hasher>
    bool unordered_map<Key, T, Hasher>::validIterator(iterator it)
    {
        // Can't do it >= begin().
        // begin() returns the first sequentually nonempty bucket, which is not garanteed to be the first nonempty bucket in memory.
        return (it >= iterator{m_data.begin(), nullptr} && it < iterator{m_data.end(), nullptr});
    }

    template<typename Key, typename T, typename Hasher>
    void unordered_map<Key, T, Hasher>::add_iterator_bucket(typename vector<bucket<key_type, mapped_type>>::iterator it)
    {
        if (m_first_nonempty == m_data.end())
        {
            //std::cout << "First bucket added to list\n";
            m_first_nonempty = it;
            m_last_nonempty = it;
            it->prev_nonempty = nullptr;
            it->next_nonempty = m_data.end();
        }
        else
        {
            //std::cout << "More bucket added to list\n";             
            m_last_nonempty->next_nonempty = it;
            it->prev_nonempty = m_last_nonempty;
            m_last_nonempty = it;
            it->next_nonempty = m_data.end();
        }
    }

    template<typename Key, typename T, typename Hasher>
    void unordered_map<Key, T, Hasher>::rehash(size_t buckets)
    {
        //std::cout << "REHASHING\n";
        size_t old_bucket_size = m_bucket_size;
        m_bucket_size = buckets;

        vector<bucket<key_type, mapped_type>> new_data(buckets);

        //std::cout << "STARTED LOOPING\n";
        for (size_t old_bucket_index = 0; old_bucket_index < old_bucket_size; ++old_bucket_index)
        {

            if (m_data[old_bucket_index].empty() == 0)
            {
                for (typename single_list<value_type>::iterator it = m_data[old_bucket_index].m_data.begin();
                    it != m_data[old_bucket_index].m_data.end(); ++it)
                {
                    //std::cout << it->first << '\n';
                    size_t new_bucket_location = m_hasher(it->first) % m_bucket_size;
                    new_data[new_bucket_location].emplace_back(std::move(*it));
                }
            }
        }

        

        m_data = std::move(new_data);



        //std::cout << "DONE LOOPING\n";
        re_iterator_bucket();
    }



} // namespace kq

#endif