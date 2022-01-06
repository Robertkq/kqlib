#ifndef kqstring_
#define kqstring_

#include <istream>
#include <ostream>

#include "other.h"



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
        using iterator_category = std::random_access_iterator_tag;

        str_iterator() : kq_ptr() {}
        str_iterator(const str_iterator& other) : kq_ptr(other.kq_ptr) {}
        str_iterator(str_iterator&& other) noexcept : kq_ptr(other.kq_ptr) { other.kq_ptr = nullptr; }
        str_iterator(pointer_type ptr) : kq_ptr(ptr) {}
        ~str_iterator() {}

        str_iterator& operator=(const str_iterator& other) { kq_ptr = other.kq_ptr; return *this; }
        str_iterator& operator=(str_iterator&& other) noexcept { kq_ptr = other.kq_ptr; other.kq_ptr = nullptr;  return *this; }

        bool operator==(const str_iterator& rhs) const { return kq_ptr == rhs.kq_ptr; }
        bool operator!=(const str_iterator& rhs) const { return kq_ptr != rhs.kq_ptr; }
        bool operator<(const str_iterator& rhs) const { return kq_ptr < rhs.kq_ptr; }
        bool operator>(const str_iterator& rhs) const { return kq_ptr > rhs.kq_ptr; }
        bool operator<=(const str_iterator& rhs) const { return kq_ptr <= rhs.kq_ptr; }
        bool operator>=(const str_iterator& rhs) const { return kq_ptr >= rhs.kq_ptr; }

        str_iterator operator++(int) { pointer_type Tmp = kq_ptr; ++kq_ptr; return Tmp; }
        str_iterator& operator++() { ++kq_ptr; return *this; }
        str_iterator operator--(int) { pointer_type Tmp = kq_ptr; --kq_ptr; return Tmp; }
        str_iterator& operator--() { --kq_ptr; return *this; }
        str_iterator operator+(int rhs) const { return kq_ptr + rhs; }
        str_iterator operator-(int rhs) const { return kq_ptr - rhs; }
        str_iterator& operator+=(int rhs) { kq_ptr += rhs; return *this; }
        str_iterator& operator-=(int rhs) { kq_ptr -= rhs; return *this; }

        friend str_iterator operator+(int lhs, const str_iterator& rhs) { return rhs.kq_ptr + lhs; }
        size_t operator-(const str_iterator& rhs) const { return abs(kq_ptr - rhs.kq_ptr); }

        pointer_type ptr() const { return kq_ptr; }

        reference_type operator*() const { return *kq_ptr; }
        pointer_type operator->() const { return kq_ptr; }
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
        using iterator_category = std::random_access_iterator_tag;

        str_reverse_iterator() : kq_ptr() {}
        str_reverse_iterator(const str_reverse_iterator& other) : kq_ptr(other.kq_ptr) {}
        str_reverse_iterator(str_reverse_iterator&& other) noexcept : kq_ptr(other.kq_ptr) { other.kq_ptr = nullptr; }
        str_reverse_iterator(pointer_type ptr) : kq_ptr(ptr) {}
        ~str_reverse_iterator() {}

        str_reverse_iterator& operator=(const str_reverse_iterator& other) { kq_ptr = other.kq_ptr; return *this; }
        str_reverse_iterator& operator=(str_reverse_iterator&& other) noexcept { kq_ptr = other.kq_ptr; other.kq_ptr = nullptr;  return *this; }

        bool operator==(const str_reverse_iterator& rhs) const { return kq_ptr == rhs.kq_ptr; }
        bool operator!=(const str_reverse_iterator& rhs) const { return kq_ptr != rhs.kq_ptr; }
        bool operator<(const str_reverse_iterator& rhs) const { return kq_ptr < rhs.kq_ptr; }
        bool operator>(const str_reverse_iterator& rhs) const { return kq_ptr > rhs.kq_ptr; }
        bool operator <=(const str_reverse_iterator& rhs) const { return kq_ptr <= rhs.kq_ptr; }
        bool operator >=(const str_reverse_iterator& rhs) const { return kq_ptr >= rhs.kq_ptr; }

        str_reverse_iterator operator++(int) { pointer_type Tmp = kq_ptr; --kq_ptr; return Tmp; }
        str_reverse_iterator& operator++() { --kq_ptr; return *this; }
        str_reverse_iterator operator--(int) { pointer_type Tmp = kq_ptr; ++kq_ptr; return Tmp; }
        str_reverse_iterator& operator--() { ++kq_ptr; return *this; }
        str_reverse_iterator operator+(int rhs) const { return kq_ptr - rhs; }
        str_reverse_iterator operator-(int rhs) const { return kq_ptr + rhs; }
        str_reverse_iterator& operator+=(int rhs) { kq_ptr -= rhs; return *this; }
        str_reverse_iterator& operator-=(int rhs) { kq_ptr += rhs; return *this; }

        friend str_reverse_iterator operator+(int lhs, const str_reverse_iterator& rhs) { return rhs.kq_ptr + lhs; }
        size_t operator-(const str_reverse_iterator& rhs) const { return abs(kq_ptr - rhs.kq_ptr); }

        pointer_type ptr() const { return kq_ptr; }

        reference_type operator*() const { return *kq_ptr; }
        pointer_type operator->() const { return kq_ptr; }


    private:
        pointer_type kq_ptr;
    };

    template<typename T>
    struct basic_string
    {
    public:
        using value_type = T; // char type
        using pointer_type = value_type*;
        using reference_type = value_type&;
        using iterator = str_iterator<value_type, false>;
        using const_iterator = str_iterator<value_type, true>;
        using reverse_iterator = str_reverse_iterator<value_type, false>;
        using const_reverse_iterator = str_reverse_iterator<value_type, true>;
    public:
        basic_string();
        basic_string(const char* str);
        basic_string(const char* str, size_t amount);
        basic_string(size_t, value_type);
        template<typename iterType, typename std::enable_if<is_iterator<iterType>::value, int>::type = 0>
        basic_string(iterType, iterType);
        basic_string(const basic_string<T>& str, size_t pos, size_t len = -1);
        basic_string(const basic_string<T>&);
        basic_string(basic_string<T>&&) noexcept;
        ~basic_string();

        basic_string<T>& operator=(const basic_string<T>&);
        basic_string<T>& operator=(basic_string<T>&&) noexcept;

        basic_string<T>& operator=(const char*);

        bool operator==(const basic_string<T>&) const;
        bool operator!=(const basic_string<T>& rhs) const { return (*this == rhs); }
        bool operator>(const basic_string<T>&) const;
        bool operator<(const basic_string<T>&) const;
        bool operator>=(const basic_string<T>&) const;
        bool operator<=(const basic_string<T>&) const;

        basic_string<T> operator+(value_type) const;
        basic_string<T> operator+(const char*) const;
        basic_string<T> operator+(const basic_string<T>&) const;

        basic_string<T>& operator+=(value_type);
        basic_string<T>& operator+=(const char*);
        basic_string<T>& operator+=(const basic_string<T>&);

        size_t size() const     { return kq_size; }
        size_t length() const   { return kq_size; }
        size_t capacity() const { return kq_cap; }
        pointer_type data()     { return kq_data; }
        const pointer_type data() const { return kq_data; }
        pointer_type c_str()            { return kq_data; }
        const pointer_type c_str() const{ return kq_data; }

        iterator begin()    { return kq_data; }
        iterator end()      { return (kq_data + kq_size); }
        const_iterator begin() const    { return kq_data; }
        const_iterator end() const      { return (kq_data + kq_size); }
        const_iterator cbegin() const   { return kq_data; }
        const_iterator cend() const { return (kq_data + kq_size); }
        reverse_iterator rbegin()   { return (kq_data + kq_size - 1); }
        reverse_iterator rend()     { return kq_data - 1; }
        const_reverse_iterator rbegin() const   { return (kq_data + kq_size - 1); }
        const_reverse_iterator rend() const     { return (kq_data - 1); }
        const_reverse_iterator crbegin() const  { return (kq_data + kq_size - 1); }
        const_reverse_iterator crend() const    { return kq_data - 1; }

        bool is_empty() const { return kq_size == 0; }

        reference_type push_back(const value_type&);

        void assign(size_t, value_type);
        void assign(const basic_string<T>&);
        void assign(basic_string<T>&& other);
        
        void pop_back();
        void erase(iterator);
        void erase(const basic_string<T>&);
        void clear(); 

        void resize(size_t);
        void resize(size_t, value_type);

        void reserve(size_t);
        void shrink_to_fit();
        void swap(basic_string<T>&);

        basic_string<T> substr(size_t, size_t) const;

        size_t find(value_type, size_t = 0) const;
        size_t find(const char*, size_t = 0) const;
        size_t find(const basic_string<T>&, size_t = 0) const;

        value_type& front();
        const value_type& front() const;
        value_type& back();
        const value_type& back() const;

        value_type& operator[](size_t index) { return kq_data[index]; }
        const value_type& operator[](size_t index) const { return kq_data[index]; }
        value_type& at(size_t);
        const value_type& at(size_t) const;
        
    public:
        // friend functions
        template<typename CharT, typename Traits>
        friend std::basic_ostream<CharT, Traits>& operator<<(std::basic_ostream<CharT, Traits>&, const kq::basic_string<CharT>&);

        template<typename CharT, typename Traits>
        friend std::basic_istream<CharT, Traits>& operator>>(std::basic_istream<CharT, Traits>&, kq::basic_string<CharT>&);

        template<typename CharT, typename Traits>
        friend std::basic_istream<CharT, Traits>& getline(std::basic_istream<CharT, Traits>&, basic_string<CharT>&, CharT = '\n');

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
    basic_string<T>::basic_string(size_t size, value_type ch)
        : kq_data(new value_type[size+1]), kq_size(size), kq_cap(size+1)
    {
        for (size_t i = 0; i < size; ++i)
        {
            *(kq_data + i) = ch;
        }
        *(kq_data + kq_size) = '\0';
    }

    template<typename T>
    template<typename iterType, typename std::enable_if<is_iterator<iterType>::value, int>::type>
    basic_string<T>::basic_string(iterType begin, iterType end)
        : kq_data(nullptr), kq_size(0), kq_cap(0)
    {
        for (; begin != end; ++begin)
        {
            push_back(*begin);
        }
    }

    template<typename T>
    basic_string<T>::basic_string(const basic_string<T>& str, size_t pos, size_t len)
        : kq_data(nullptr), kq_size(0), kq_cap(0)
    {
        if (pos < str.size())
        {
            if (pos + len < str.size())
            {
                reserve(str.size() - pos);
            }
            else if (pos + len >= str.size())
            {
                reserve(str.size() - pos);
            }
            while (len > 0 && str.size() - pos > 0)
            {
                push_back(str[pos]);
                --len;
                ++pos;
            }
        }
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
    bool basic_string<T>::operator==(const basic_string<T>& rhs) const
    {
        if (kq_size != rhs.kq_size)
        {
            return false;
        }
        else
        {
            for (size_t i = 0; i < kq_size; ++i)
            {
                if (*(kq_data + i) != *(rhs.kq_data + i))
                {
                    return false;
                }
            }
        }
        return true;
    }

    template<typename T>
    bool basic_string<T>::operator>(const basic_string<T>& rhs) const
    {
        size_t size = kq_size < rhs.kq_size ? kq_size : rhs.kq_size;
        for (size_t i = 0; i < size; i++)
        {
            if ((*this)[i] != rhs[i])
            {
                return (*this)[i] > rhs[i];
            }
        }
        if (kq_size == rhs.kq_size)
        {
            return false;
        }
        else if (kq_size > size)
        {
            return true;
        }
        else
        {
            return false;
        }
    }

    template<typename T>
    bool basic_string<T>::operator<(const basic_string<T>& rhs) const
    {
        size_t size = kq_size < rhs.kq_size ? kq_size : rhs.kq_size;
        for (size_t i = 0; i < size; i++)
        {
            if ((*this)[i] != rhs[i])
            {
                return (*this)[i] < rhs[i];
            }
        }
        if (kq_size == rhs.kq_size)
        {
            return false;
        }
        else if (kq_size > size)
        {
            return false;
        }
        else
        {
            return true;
        }
    }

    template<typename T>
    bool basic_string<T>::operator>=(const basic_string<T>& rhs) const
    {
        size_t size = kq_size < rhs.kq_size ? kq_size : rhs.kq_size;
        for (size_t i = 0; i < size; i++)
        {
            if ((*this)[i] != rhs[i])
            {
                return (*this)[i] >= rhs[i];
            }
        }
        if (kq_size >= rhs.kq_size)
        {
            return true;
        }
        else
        {
            return false;
        }
    }

    template<typename T>
    bool basic_string<T>::operator<=(const basic_string<T>& rhs) const
    {
        size_t size = kq_size < rhs.kq_size ? kq_size : rhs.kq_size;
        for (size_t i = 0; i < size; i++)
        {
            if ((*this)[i] != rhs[i])
            {
                return (*this)[i] <= rhs[i];
            }
        }
        if (kq_size >= rhs.kq_size)
        {
            return false;
        }
        else
        {
            return true;
        }
    }

    template<typename T>
    basic_string<T> basic_string<T>::operator+(value_type ch) const
    {
        basic_string<T> aux;
        aux.kq_data = new value_type[kq_size + 2];
        for (size_t i = 0; i < kq_size; ++i)
        {
            aux[i] = (*this)[i];
        }
        aux[kq_size] = ch;
        aux[kq_size + 1] = '\0';
        aux.kq_size = kq_size + 1;
        aux.kq_cap = aux.kq_size + 1;
        return aux;
    }

    template<typename T>
    basic_string<T> basic_string<T>::operator+(const char* ptr) const
    {
        basic_string<T> aux;
        aux.kq_data = new value_type[kq_size + strlen(ptr) + 1];
        for (size_t i = 0; i < kq_size; ++i)
        {
            aux[i] = (*this)[i];
        }
        for (size_t i = 0; ptr[i] != 0; ++i)
        {
            aux[kq_size + i] = ptr[i];
        }
        aux.kq_size = kq_size + strlen(ptr);
        aux[aux.kq_size] = '\0';
        aux.kq_cap = aux.kq_size + 1;
        return aux;
    }

    template<typename T>
    basic_string<T> basic_string<T>::operator+(const basic_string<T>& other) const
    {
        basic_string<T> aux;
        aux.kq_data = new value_type[kq_size + other.kq_size + 1];
        // aux kq_size = kq_size + other.kq_size
        for (size_t i = 0; i < kq_size; ++i)
        {
            aux[i] = (*this)[i];
        }
        for (size_t i = 0; i < other.kq_size; ++i)
        {
            aux[kq_size + i] = other[i];
        }
        aux.kq_size = kq_size + other.kq_size;
        aux[aux.kq_size] = '\0';
        aux.kq_cap = aux.kq_size + 1;
        return aux;
    }

    template<typename T>
    basic_string<T>& basic_string<T>::operator+=(value_type ch)
    {
        basic_string<T> aux;
        aux.kq_data = new value_type[kq_size + 2];
        for (size_t i = 0; i < kq_size; ++i)
        {
            aux[i] = (*this)[i];
        }
        aux[kq_size] = ch;
        aux[kq_size + 1] = '\0';
        aux.kq_size = kq_size + 1;
        aux.kq_cap = aux.kq_size + 1;
        *this = std::move(aux);
        return *this;
    }

    template<typename T>
    basic_string<T>& basic_string<T>::operator+=(const char* ptr)
    {
        basic_string<T> aux;
        aux.kq_data = new value_type[kq_size + strlen(ptr) + 1];
        for (size_t i = 0; i < kq_size; ++i)
        {
            aux[i] = (*this)[i];
        }
        for (size_t i = 0; i < strlen(ptr); ++i)
        {
            aux[kq_size + i] = ptr[i];
        }
        aux.kq_size = kq_size + strlen(ptr);
        aux[aux.kq_size] = '\0';
        aux.kq_cap = aux.kq_size + 1;
        *this = std::move(aux);
        return *this;
    }

    template<typename T>
    basic_string<T>& basic_string<T>::operator+=(const basic_string<T>& other)
    {
        basic_string<T> aux;
        aux.kq_data = new value_type[kq_size + other.kq_size + 1];
        for (size_t i = 0; i < kq_size; ++i)
        {
            aux[i] = (*this)[i];
        }
        for (size_t i = 0; i < other.kq_size; ++i)
        {
            aux[kq_size + i] = other[i];
        }
        aux.kq_size = kq_size + other.kq_size;
        aux[aux.kq_size] = '\0';
        aux.kq_cap = aux.kq_size + 1;
        *this = std::move(aux);
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
            // std::cout << "Realloc\n";
            realloc(kq_cap + kq_cap / 2);
        }
        *(kq_data + kq_size++) = elementToAdd;
        *(kq_data + kq_size) = '\0';
        return kq_data[kq_size - 1];
    }

    template<typename T>
    void basic_string<T>::assign(size_t count, value_type value)
    {
        clear();
        reserve(count);
        while (count > 0)
        {
            push_back(value);
            --count;
        }
    }

    template<typename T>
    void basic_string<T>::assign(const basic_string<T>& other)
    {
        *this = other;
    }

    template<typename T>
    void basic_string<T>::assign(basic_string<T>&& other)
    {
        *this = std::move(other);
    }

    template<typename T>
    void basic_string<T>::pop_back()
    {
        if (kq_size > 0)
        {
            --kq_size;
            (kq_data + kq_size)->~T();
        }
    }

    template<typename T>
    void basic_string<T>::erase(iterator pos)
    {
        if (kq_size > 0)
        {
            if (pos >= begin() && pos < end())
            {
                (pos.ptr())->~T();
                for (; pos != end(); ++pos)
                {
                    *pos = *(pos + 1);
                    // again, not using std::move, because && will be 8 bytes, which should usually be > T
                }
                --kq_size;
                kq_data[kq_size] = '\0';
            }
        }
    }

    template<typename T>
    void basic_string<T>::erase(const basic_string<T>& toRemove)
    {
        if (kq_size >= toRemove.size())
        {
            for (basic_string<T>::iterator it = begin(); it != end() - toRemove.size(); ++it)
            {
                auto copyIt = it;
                bool found = true;
                for (basic_string<T>::iterator it2 = toRemove.begin(); it2 != toRemove.end(); ++it2)
                {
                    if ( (*it2) != (*(copyIt++)) )
                    {
                        found = false;
                        break;
                    }
                }
                if (found == true)
                {
                    for (it; it != end() - toRemove.size() + 1; ++it)
                    {
                        it.ptr()->~T();
                        *it = *(it + toRemove.size());
                    }
                    kq_size -= toRemove.size();
                    kq_data[kq_size] = '\0';
                    return;
                }
            }
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
            while (kq_size > count)
            {
                pop_back();
            }
        }
        else if (count > kq_size)
        {
            if (count > kq_cap)
            {
                reserve(count);
            }
            while (kq_size < count)
            {
                push_back(T());
            }
        }
    }

    template<typename T>
    void basic_string<T>::resize(size_t count, value_type value)
        // not taking const& as param because value_type should be < 8 bytes
    {
        if (count < kq_size)
        {
            while (kq_size > count)
            {
                pop_back();
            }
        }
        else if (count > kq_size)
        {
            if (count > kq_cap)
            {
                reserve(count);
            }
            while (kq_size < count)
            {
                emplace_back(value);
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
    void basic_string<T>::swap(basic_string<T>& other)
    {
        swap(*this, other);
    }

    template<typename T>
    basic_string<T> basic_string<T>::substr(size_t pos, size_t count) const
    {
        return kq::basic_string<T>(*this, pos, count);
    }

    template<typename T>
    size_t basic_string<T>::find(value_type ch, size_t pos) const
    {
        for (size_t i = pos; i < kq_size; ++i)
        {
            if (*(kq_data + i) == ch)
            {
                return i;
            }
        }
        return kq_size;
    }

    template<typename T>
    size_t basic_string<T>::find(const char* ptr, size_t pos) const
    {
        for (size_t i = pos; i < kq_size; ++i)
        {
            size_t j;
            for (j = 0; ptr[j] != 0; ++j)
            {
                if (ptr[j++] != *(kq_data + i + j))
                {
                    break;
                }
            }
            if (ptr[j] == 0)
            {
                return i;
            }
        }
        return kq_size;
    }

    template<typename T>
    size_t basic_string<T>::find(const basic_string<T>& str, size_t pos) const
    {
        for (size_t i = pos; i < kq_size; ++i)
        {
            if (substr(i, str.size()) == str)
            {
                return i;
            }
        }
        return kq_size;
    }

    template<typename T>
    typename basic_string<T>::value_type& basic_string<T>::front()
    {
        if (kq_size == 0)
        {
            throw std::out_of_range("front(), called on empty string");
        }
        return *kq_data;
    }

    template<typename T>
    const typename basic_string<T>::value_type& basic_string<T>::front() const
    {
        if (kq_size == 0)
        {
            throw std::out_of_range("front(), called on empty string");
        }
        return *kq_data;
    }

    template<typename T>
    typename basic_string<T>::value_type& basic_string<T>::back()
    {
        if (kq_size == 0)
        {
            throw std::out_of_range("back(), called on empty string");
        }
        return *(kq_data + kq_size - 1);
    }

    template<typename T>
    const typename basic_string<T>::value_type& basic_string<T>::back() const
    {
        if (kq_size == 0)
        {
            throw std::out_of_range("back(), called on empty string");
        }
        return *(kq_data + kq_size - 1);
    }

    template<typename T>
    typename basic_string<T>::value_type& basic_string<T>::at(size_t index)
    {
        if (index >= kq_size || kq_size == 0)
        {
            throw std::out_of_range("at(), trying to access element out of range on string");
        }
        return kq_data[index];
    }

    template<typename T>
    const typename basic_string<T>::value_type& basic_string<T>::at(size_t index) const
    {
        if (index >= kq_size || kq_size == 0)
        {
            throw std::out_of_range("at(), trying to access element out of range on string");
        }
        return kq_data[index];
    }

    template<typename CharT, typename Traits>
    std::basic_ostream<CharT, Traits>& operator<<(std::basic_ostream<CharT, Traits>& os, const kq::basic_string<CharT>& str)
    {
        os << (str.kq_data);
        return os;
    }

    template<typename CharT, typename Traits>
    std::basic_istream<CharT, Traits>& operator>>(std::basic_istream<CharT, Traits>& is, kq::basic_string<CharT>& str)
    {
        str.clear();
        char ch;
        is.get(ch);
        while (!isspace(ch))
        {
            str.push_back(ch);
            is.get(ch);
        }
        str.shrink_to_fit();
        return is;
    }

    template<typename CharT, typename Traits>
    std::basic_istream<CharT, Traits>& getline(std::basic_istream<CharT, Traits>& is,
                                               basic_string<CharT>& str,
                                                CharT delim)
    {
        str.clear();
        char ch;
        is.get(ch);
        while ((!isspace(ch) || ch == ' ') && ch != delim)
        {
            str.push_back(ch);
            is.get(ch);
        }
        str.shrink_to_fit();
        return is;
    }

    template<typename T>
    void basic_string<T>::realloc(size_t newCapacity)
    {
        // Notes:
        // newCapacity will contain the +1 for the '\0'
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