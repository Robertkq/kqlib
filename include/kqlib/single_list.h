#ifndef KQSINGLE_LIST_
#define KQSINGLE_LIST_

#include "other.h"

//#include <iostream>

namespace kq {

    template<typename T>
    struct sl_element
    {
    public:
        using value_type = T;

        sl_element() : value(), next(nullptr) {}
        sl_element(const sl_element& other) : value(other.value), next(other.next) {}
        sl_element(sl_element&& other) noexcept : value(std::move(other.value)), next(other.next) {}
        template<typename... Args>
        sl_element(Args&&... args) : value(std::forward<Args>(args)...), next(nullptr) {}
        ~sl_element() {}

        sl_element& operator=(const sl_element& other) { value = other.value; next = other.next; return *this; }
        sl_element& operator=(sl_element&& other) noexcept { value = std::move(other.value); next = other.next; return *this; }

    public:
        value_type value;
        sl_element* next;
    };

    template<typename T, bool constant>
    struct sl_iterator
    {
        using value_type = T;
        using pointer = value_type*;
        using reference = typename std::conditional<constant, const value_type&, value_type&>::type;
        using element = sl_element<value_type>;
        using iterator_category = std::forward_iterator_tag;

        sl_iterator() : m_ptr()                                        {}
        sl_iterator(const sl_iterator& other) : m_ptr(other.m_ptr)    {}
        sl_iterator(sl_iterator&& other) : m_ptr(other.m_ptr)         { other.m_ptr = nullptr; }
        sl_iterator(element* ptr) : m_ptr(ptr)                         {}

        sl_iterator& operator=(const sl_iterator& other);
        sl_iterator& operator=(sl_iterator&& other) noexcept;

        bool operator!=(const sl_iterator& other) const                 { return m_ptr != other.m_ptr; }
        bool operator==(const sl_iterator& other) const                 { return m_ptr == other.m_ptr; }

        sl_iterator& operator++()                                       { m_ptr = m_ptr->next; return *this; }
        sl_iterator operator++(int)                                    { element* tmp = m_ptr; m_ptr = m_ptr->next; return tmp; }

        element* el_ptr() const                                            { return m_ptr; }
        element* el_next() const                                           { return m_ptr->next; }
        pointer ptr() const                                             { return &(m_ptr->value); }

        reference operator*() const                                     { return m_ptr->value; }
        pointer operator->() const                                      { return &(m_ptr->value); }

    private:
        element* m_ptr;
    };

    template<typename T, bool constant>
    sl_iterator<T, constant>& sl_iterator<T, constant>::operator=(const sl_iterator& other)
    {
        if (this != &other)
        {
            m_ptr = other.m_ptr;
        }
        return *this;
    }

    template<typename T, bool constant>
    sl_iterator<T, constant>& sl_iterator<T, constant>::operator=(sl_iterator&& other) noexcept
    { 
        if (this != &other)
        {
            m_ptr = other.m_ptr;
            other.m_ptr = nullptr;
        }
        return *this; 
    }

    template<typename T>
    struct single_list
    {
    public:
        using value_type = T;
        using reference = value_type&;
        using pointer = value_type*;
        using element = sl_element<value_type>;

        using iterator = sl_iterator<value_type, false>;
        using const_iterator = sl_iterator<value_type, true>;

        iterator begin() { return m_ptr; }
        iterator end() { return nullptr; }
        const_iterator begin() const { return m_ptr; }
        const_iterator end() const { return nullptr; }
        const_iterator cbegin() const { return m_ptr; }
        const_iterator cend() const { return nullptr; }

        single_list() : m_ptr(nullptr), m_size(0) {}
        single_list(const single_list& other);
        single_list(single_list&& other) noexcept;
        template<typename ilT>
        single_list(const std::initializer_list<ilT>& il);
        ~single_list();

        single_list& operator=(const single_list& other);
        single_list& operator=(single_list&& other) noexcept;

        bool empty() const { return m_size == 0; }
        size_t size() const { return m_size; }

        value_type& push_back(const value_type& value);
        template<typename... Args>
        value_type& emplace_back(Args&&... args);

        void pop_back();
        void pop_front();
        void erase(iterator pos);
        void clear();

    private:
        element* m_ptr;
        size_t m_size;
    };

    template<typename T>
    single_list<T>::single_list(const single_list& other) 
        : m_ptr(nullptr), m_size(0)
    {
        //FIXME: this method is pretty lazy.. 
        for (auto it = other.cbegin(); it != other.cend(); ++it)
        {
            push_back(*it);
        }
    }

    template<typename T>
    single_list<T>::single_list(single_list&& other) noexcept
        : m_ptr(other.m_ptr), m_size(other.m_size)
    {
        other.m_ptr = nullptr;
        other.m_size = 0;
    }

    template<typename T>
    template<typename ilT>
    single_list<T>::single_list(const std::initializer_list<ilT>& il)
        : m_ptr(nullptr), m_size(0)
    {
        for (auto it = il.begin(); it != il.end(); ++it)
        {
            push_back(*it);
        }
    }

    template<typename T>
    single_list<T>::~single_list()
    {
        element* current = m_ptr;
        element* next;
        for (int i = 0; i < m_size; ++i)
        {
            next = current->next;
            delete current;
            current = next;
        }
    }

    template<typename T>
    single_list<T>& single_list<T>::operator=(const single_list& other)
    {
        if (this != &other)
        {
            clear();
            for (auto it = other.begin(); it != other.end(); ++it)
            {
                push_back(*it);
            }
        }
        return *this;
    }

    template<typename T>
    single_list<T>& single_list<T>::operator=(single_list&& other) noexcept
    {
        if (this != &other)
        {
            clear();
            m_ptr = other.m_ptr;
            m_size = other.m_size;
            other.m_ptr = nullptr;
            other.m_size = 0;
        }
        return *this;
    }

    template<typename T>
    typename single_list<T>::value_type& single_list<T>::push_back(const value_type& value)
    {
        if (m_size == 0)
        {
            m_ptr = new element(value);
            m_ptr->next = nullptr;
            ++m_size;
            return m_ptr->value;
        }
        else
        {
            element* last = m_ptr;
            while (last->next != nullptr)
            {
                last = last->next;
            }
            last->next = new element(value);
            last->next->next = nullptr;
            ++m_size;
            return last->next->value;
        }
    }

    template<typename T>
    template<typename... Args>
    typename single_list<T>::value_type& single_list<T>::emplace_back(Args&&... args)
    {
        if (m_size == 0)
        {
            m_ptr = new element(std::forward<Args>(args)...);
            m_ptr->next = nullptr;
            ++m_size;
            return m_ptr->value;
        }
        else
        {
            element* last = m_ptr;
            while (last->next != nullptr)
            {
                last = last->next;
            }
            last->next = new element(std::forward<Args>(args)...);
            last->next->next = nullptr;
            ++m_size;
            return last->next->value;
        }
    }

    template<typename T>
    void single_list<T>::pop_back()
    {
        if (m_size != 0)
        {
            if (m_size == 1)
            {
                delete m_ptr;
                --m_size;
                m_ptr = nullptr;
            }
            else
            {
                element* prev = m_ptr;
                element* last = m_ptr->next;
                while (last->next != nullptr)
                {
                    prev = last;
                    last = last->next;
                }
                delete last;
                prev->next = nullptr;
                --m_size;

            }
        }
    }

    template<typename T>
    void single_list<T>::pop_front()
    {
        if (m_size != 0)
        {
            element* dell = m_ptr;
            m_ptr = m_ptr->next;
            delete dell;
            --m_size;
        }
    }

    template<typename T>
    void single_list<T>::erase(iterator pos)
    {
        if (m_size != 0)
        {
            // check to see if iterator is from this list
            iterator it = begin();
            if (pos == it) { pop_front(); }
            else
            {
                iterator prev = it;
                for (++it; it != end(); ++it)
                {
                    if (it == pos)
                    {
                        if (it.el_next() == nullptr) { pop_back(); }
                        else
                        {
                            prev.el_ptr()->next = it.el_next();
                            delete it.el_ptr();
                            --m_size;
                            return;
                        }
                    }
                    prev = it;
                }
            }
        }
    }
    
    template<typename T>
    void single_list<T>::clear()
    {
        if (m_size != 0)
        {
            element* current;
            while (m_ptr != nullptr)
            {
                current = m_ptr;
                m_ptr = m_ptr->next;
                delete current;
            }
        }
    }

} // namespace kq

#endif