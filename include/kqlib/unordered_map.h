#ifndef kqunordered_map_
#define kqunordered_map_

#include "other.h"
#include "vector.h"

namespace kq
{
    template<typename T>
    struct sl_element
    {
    public:
        using value_type = T;

        sl_element()
            : value(), next(nullptr) {}

        template<typename... Args>
        sl_element(Args&&... args)
            : value(std::forward<Args>(args)...), next(nullptr) {}

    public:
        value_type value;
        sl_element* next;
    };

    template<typename T>
    struct sl_iterator
    {
        using value_type = T;
        using element = sl_element<value_type>;

        sl_iterator(element* ptr) : kq_ptr(ptr) {}

        bool operator!=(const sl_iterator& other) const { return kq_ptr != other.kq_ptr; }
        bool operator==(const sl_iterator& other) const { return kq_ptr == other.kq_ptr; }

        sl_iterator& operator++() { kq_ptr = kq_ptr->next; return *this; }

        value_type& operator*() { return kq_ptr->value; }

    private:
        element* kq_ptr;
    };

    template<typename T>
    struct single_list
    {
    public:
        using value_type = T;
        using reference = value_type&;
        using pointer = value_type*;
        using element = sl_element<value_type>;

        using iterator = sl_iterator<value_type>;

        iterator begin() const { return kq_ptr; }
        iterator end() const { return nullptr; }

        single_list()
            : kq_ptr(nullptr), kq_size(0) {}

        void push_back(const value_type& value)
        {
            if (kq_size == 0)
            {
                kq_ptr = new element(value);
                ++kq_size;
            }
            else
            {
                element* last = kq_ptr;
                while (last->next != nullptr)
                {
                    last = last->next;
                }
                last->next = new element(value);
                ++kq_size;
            }
        }

        template<typename... Args>
        void emplace_back(Args&&... args)
        {

        }

        void pop_back()
        {

        }

        void pop_front()
        {

        }

    private:
        element* kq_ptr;
        size_t kq_size;
    };


    template<typename Key, typename T>
    struct unordered_map
    {
    public:

        using key_type = Key;
        using mapped_type = T;
        using value_type = kq::pair<key_type, mapped_type>;
        using reference = value_type&;
        using pointer = value_type*;


        unordered_map();
        unordered_map(const unordered_map& other); // FIXME: implement
        unordered_map(unordered_map&& other); // FIXME: implement

        unordered_map& operator=(const unordered_map& other); // FIXME: implement
        unordered_map& operator=(unordered_map&& other); // FIXME: implement

    private:
        vector<single_list<value_type>> kq_data;
        size_t kq_size;
        size_t kq_cap;
    };

    template<typename Key, typename T>
    unordered_map<Key, T>::unordered_map()
        : kq_data(), kq_size(0), kq_cap(0)
    {}



} // namespace kq

#endif