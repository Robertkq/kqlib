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

    using string = typename basic_string<char>;

    using wstring = typename basic_string<wchar_t>;

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

        size_t size() { return kq_size; }
        size_t capacity() { return kq_cap; }

        reference_type push_back(const reference_type&);

        bool isEmpty() const { return kq_size == 0; }
        void clear();
        void reserve(size_t);
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

    // friend functions
    std::ostream& operator<<(std::ostream& os, const string& value)
    {
        os << (value.kq_data);
        return os;
    }

    template<typename T>
    void basic_string<T>::realloc(size_t newCapacity)
    {
        if (newCapacity < 2)
        {
            newCapacity = 2;
        }

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