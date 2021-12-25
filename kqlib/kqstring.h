#ifndef kqstring_
#define kqstring_

#include "kqother.h"
#include <iostream>

namespace kq
{
    // Forward declarations

    template<typename T>
    struct basic_string;

    // Template Aliases

    using string = basic_string<char>;

    using wstring = basic_string<wchar_t>;

    // String non-member functions

    size_t strlen(const char* source)
    {
        size_t count{ 0 };
        while (*(source++) != '\0')
        {
            ++count;
        }
        return count;
    }

    template<typename T, bool constant>
    struct str_iterator
    {
    public:
        using value_type = T;
        using pointer_type = value_type*;
        using reference_type = typename std::conditional<constant, const value_type&, value_type&>::type;

        str_iterator() : kq_ptr() {}
        str_iterator(const str_iterator& other) : kq_ptr(other.kq_ptr) {}
        str_iterator(str_iterator&& other) : kq_ptr(other.kq_ptr) noexcept { other.kq_ptr = nullptr; }
        str_iterator(pointer_type ptr) : kq_ptr(ptr) {}
        ~str_iterator() {}

        str_iterator& operator=(const str_iterator& other) { kq_ptr = other.kq_ptr; return *this; }
        str_iterator& operator=(str_iterator&& other) noexcept { kq_ptr = other.kq_ptr; other.kq_ptr = nullptr;  return *this; }

        bool operator==(const str_iterator& rhs) const { return kq_ptr == rhs.kq_ptr; }
        bool operator!=(const str_iterator& rhs) const { return kq_ptr != rhs.kq_ptr; }
        bool operator<(const str_iterator& rhs) const { return kq_ptr < rhs.kq_ptr; }
        bool operator>(const str_iterator& rhs) const { return kq_ptr > rhs.kq_ptr; }
        bool operator <=(const str_iterator& rhs) const { return kq_ptr <= rhs.kq_ptr; }
        bool operator >=(const str_iterator& rhs) const { return kq_ptr = > rhs.kq_ptr; }

        str_iterator operator++(int) { pointer_type = kq_ptr; ++kq_ptr; }
    private:
        pointer_type kq_ptr;
    };

    template<typename T, bool constant>
    struct str_reverse_iterator
    {
    public:
        using value_type = T;
        using pointer_type = value_type*;
        using reference_type = typename std::conditional<constant, const value_type&, value_type&>::type;

        str_reverse_iterator() : kq_ptr() {}
        str_reverse_iterator(const str_reverse_iterator& other) : kq_ptr(other.kq_ptr) {}
        str_reverse_iterator(str_reverse_iterator&& other) : kq_ptr(other.kq_ptr) noexcept { other.kq_ptr = nullptr; }
        str_reverse_iterator(pointer_type ptr) : kq_ptr(ptr) {}
        ~str_reverse_iterator() {}

        str_reverse_iterator& operator=(const str_reverse_iterator& other) { kq_ptr = other.kq_ptr; return *this; }
        str_reverse_iterator& operator=(str_reverse_iterator&& other) noexcept { kq_ptr = other.kq_ptr; other.kq_ptr = nullptr;  return *this; }

        bool operator==(const str_reverse_iterator& rhs) const { return kq_ptr == rhs.kq_ptr; }
        bool operator!=(const str_reverse_iterator& rhs) const { return kq_ptr != rhs.kq_ptr; }
        bool operator<(const str_reverse_iterator& rhs) const { return kq_ptr < rhs.kq_ptr; }
        bool operator>(const str_reverse_iterator& rhs) const { return kq_ptr > rhs.kq_ptr; }
        bool operator <=(const str_reverse_iterator& rhs) const { return kq_ptr <= rhs.kq_ptr; }
        bool operator >=(const str_reverse_iterator& rhs) const { return kq_ptr = > rhs.kq_ptr; }


    private:
        pointer_type kq_ptr;
    };

    // basic_string

    template<typename T>
    struct basic_string
    {
    public:
        using value_type = T; // char type
        using pointer_type = value_type*;
        using reference_type = value_type&;
    public:
        basic_string();
        basic_string(const char* str);
        basic_string(const char* str, size_t amount);
        basic_string(const basic_string<T>&);
        basic_string(basic_string<T>&&) noexcept;
        ~basic_string();

        basic_string<T>& operator=(const basic_string<T>&);
        basic_string<T>& operator=(basic_string<T>&&) noexcept;

        basic_string<T>& operator=(const char*);

        size_t size() const     { return kq_size; }
        size_t length() const   { return kq_size; }
        size_t capacity() const { return kq_cap; }
        pointer_type data()     { return kq_data; }
        const pointer_type data() const { return kq_data; }

        bool is_empty() const { return kq_size == 0; }

        reference_type push_back(const value_type&);
        
        void pop_back();
        //void erase(iterator); // ADDME
        void clear(); 

        void resize(size_t); // ADDME
        void resize(size_t, value_type); // ADDME

        void reserve(size_t);
        void shrink_to_fit();
        void swap(basic_string<T>&); // ADDME

        value_type& front();
        const value_type& front() const;
        value_type& back();
        const value_type& back() const;
        
    public:
        // friend functions
        friend std::ostream& operator<<(std::ostream& os, const string& value);

    private:
        void realloc(size_t);
        void destroy();
    private:
        pointer_type kq_data;
        size_t kq_size;
        size_t kq_cap;

    };

    template<typename T>
    basic_string<T>::basic_string() : kq_data(nullptr), kq_size(0), kq_cap(0) {}

    template<typename T>
    basic_string<T>::basic_string(const char* ptr) : basic_string(ptr, strlen(ptr)) {};

    template<typename T>
    basic_string<T>::basic_string(const char* str, size_t amount)
        : kq_data(new T[amount + 1]), kq_size(amount), kq_cap(kq_size + 1)
    {
        for (size_t i = 0; i < amount; ++i)
        {
            *(kq_data + i) = *(str++);
        }
        *(kq_data + kq_size) = '\0';
    }

    template<typename T>
    basic_string<T>::basic_string(const basic_string<T>& other)
        : kq_data(new T[other.kq_size + 1]), kq_size(other.kq_size), kq_cap(kq_size + 1)
    {
        for (size_t i = 0; i < kq_cap; ++i)
        {
            *(kq_data + i) = *(other.kq_data + i);
        }
  
    }

    template<typename T>
    basic_string<T>::basic_string(basic_string<T>&& other) noexcept
        : kq_data(other.kq_data), kq_size(other.kq_size), kq_cap(other.kq_cap)
    {
        other.kq_data = nullptr;
        other.kq_size = 0;
        other.kq_cap = 0;
    }

    template<typename T>
    basic_string<T>::~basic_string()
    {
        if (kq_data)
        {
            destroy();
            delete[] kq_data;
        }
    }

    template<typename T>
    basic_string<T>& basic_string<T>::operator=(const basic_string<T>& other)
    {
        // perhaps we could make this more efficient to not allocate if we already have enough capacity ?
        clear();
        kq_data = new value_type[other.kq_size + 1];
        kq_size = other.kq_size;
        kq_cap = kq_size + 1;
        for (size_t i = 0; i < kq_cap; ++i)
        {
            *(kq_data + i) = *(other.kq_data + i);
        }
        return *this;
    }

    template<typename T>
    basic_string<T>& basic_string<T>::operator=(basic_string<T>&& other) noexcept
    {
        clear();
        kq_data = other.kq_data;
        kq_size = other.kq_size;
        kq_cap = other.kq_cap;
        other.kq_data = nullptr;
        other.kq_size = 0;
        other.kq_cap = 0;
        
        return *this;
    }

    template<typename T>
    basic_string<T>& basic_string<T>::operator=(const char* str)
    {
        // perhaps we could make this more efficient to not allocate if we already have enough capacity ?
        clear();
        kq_size = strlen(str);
        kq_cap = kq_size + 1;
        kq_data = new value_type[kq_cap];
        for (size_t i = 0; i < kq_size; ++i)
        {
            *(kq_data + i) = *(str++);
        }
        kq_data[kq_size] = '\0';
        return *this;
    }

    template<typename T>
    void basic_string<T>::reserve(size_t newCapacity)
    {
        if (newCapacity > kq_cap)
        {
            realloc(newCapacity);
        }
    }

    template<typename T>
    typename basic_string<T>::reference_type basic_string<T>::push_back(const value_type& elementToAdd)
    {
        // Don't do `kq_cap - 1` because cap might be 0
        if (kq_size + 1 >= kq_cap)
        {
            std::cout << "Realloc\n";
            realloc(kq_cap + kq_cap / 2);
        }
        *(kq_data + kq_size++) = elementToAdd;
        *(kq_data + kq_size) = '\0';
        return kq_data[kq_size - 1];
    }

    template<typename T>
    void basic_string<T>::pop_back()
    {
        if (kq_size > 1)
        {
            --kq_size;
            (kq_data + kq_size)->~T();
            if (kq_size < kq_cap / 2)
            {
                realloc(kq_cap - kq_cap / 2);
            }
        }
        else if (kq_size == 1)
        {
            --kq_size;
            (kq_data + kq_size)->~T();
            delete[] kq_data;
            kq_data = nullptr;
            kq_size = 0;
            kq_cap = 0;
        }
    }

    template<typename T>
    void basic_string<T>::clear()
    {
        if (kq_data)
        {
            destroy();
            delete[] kq_data;
            kq_data = nullptr;
            kq_size = 0;
            kq_cap = 0;
        }
    }

    template<typename T>
    void basic_string<T>::resize(size_t count)
    {
        if (count < kq_size)
        {
            kq_size = count;
        }
        else if (count > kq_size)
        {
            if (count > kq_cap)
            {
                reserve(count);
            }
            kq_size = count;
        }
    }

    template<typename T>
    void basic_string<T>::resize(size_t count, value_type value)
    {
        if (count < kq_size)
        {
            while (!(kq_size != count))
            {
                pop_back();
            }
        }
        else if (count > kq_size)
        {
            while (count > 0)
            {
                push_back(value);
                --count;
            }

        }
    }

    template<typename T>
    void basic_string<T>::shrink_to_fit()
    {
        if (kq_size + 1 != kq_cap)
        {
            realloc(kq_size + 1);
        }
    }

    template<typename T>
    typename basic_string<T>::value_type& basic_string<T>::front()
    {
        if (kq_size > 0)
        {
            return *kq_data;
        }
        throw std::out_of_range("front(), called on empty string");
    }

    template<typename T>
    typename const basic_string<T>::value_type& basic_string<T>::front() const
    {
        if (kq_size > 0)
        {
            return *kq_data;
        }
        throw std::out_of_range("front(), called on empty string");
    }

    template<typename T>
    typename basic_string<T>::value_type& basic_string<T>::back()
    {
        if (kq_size > 0)
        {
            return *(kq_data + kq_size - 1);
        }
        throw std::out_of_range("back(), called on empty string");
    }

    template<typename T>
    typename const basic_string<T>::value_type& basic_string<T>::back() const
    {
        if (kq_size > 0)
        {
            return *(kq_data + kq_size - 1);
        }
        throw std::out_of_range("back(), called on empty string");
    }

    // friend functions
    std::ostream& operator<<(std::ostream& os, const string& value)
    {
        os << (value.kq_data);
        return os;
    }

    template<typename T>
    void basic_string<T>::realloc(size_t newCapacity)
    {
        // Notes:
        // newCapacity will contain the +1 for the '\0'


        pointer_type newBlock = new value_type[newCapacity];

        if (kq_data && newBlock)
        {
            for (size_t i = 0; i < kq_size; ++i)
            {
                *(newBlock + i) = std::move(*(kq_data + i));
            }
        }
        newBlock[kq_size] = '\0';

        destroy();
        delete[] kq_data;
        kq_data = newBlock;
        kq_cap = newCapacity;
        
    }

    template<typename T>
    void basic_string<T>::destroy()
    {
        if (kq_data)
        {
            for (size_t i = 0; i < kq_size; ++i)
            {
                (kq_data + i)->~value_type();
            }
        }
    }

    
}

#endif