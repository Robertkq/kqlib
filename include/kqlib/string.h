#ifndef KQSTRING_
#define KQSTRING_

#include <locale>

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

    inline size_t strlen(const char* source)
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
        using pointer = value_type*;
        using reference = typename std::conditional<constant, const value_type&, value_type&>::type;
        using difference_type = size_t;
        using iterator_category = std::random_access_iterator_tag;


        str_iterator() : m_ptr() {}
        str_iterator(const str_iterator& other) : m_ptr(other.m_ptr) {}
        str_iterator(str_iterator&& other) noexcept : m_ptr(other.m_ptr) { other.m_ptr = nullptr; }
        str_iterator(pointer ptr) : m_ptr(ptr) {}
        ~str_iterator() {}

        str_iterator& operator=(const str_iterator& other);
        str_iterator& operator=(str_iterator&& other) noexcept;

        bool operator==(const str_iterator& rhs) const { return m_ptr == rhs.m_ptr; }
        bool operator!=(const str_iterator& rhs) const { return m_ptr != rhs.m_ptr; }
        bool operator<(const str_iterator& rhs) const { return m_ptr < rhs.m_ptr; }
        bool operator>(const str_iterator& rhs) const { return m_ptr > rhs.m_ptr; }
        bool operator<=(const str_iterator& rhs) const { return m_ptr <= rhs.m_ptr; }
        bool operator>=(const str_iterator& rhs) const { return m_ptr >= rhs.m_ptr; }

        str_iterator operator++(int) { pointer Tmp = m_ptr; ++m_ptr; return Tmp; }
        str_iterator& operator++() { ++m_ptr; return *this; }
        str_iterator operator--(int) { pointer Tmp = m_ptr; --m_ptr; return Tmp; }
        str_iterator& operator--() { --m_ptr; return *this; }
        str_iterator operator+(int rhs) const { return m_ptr + rhs; }
        str_iterator operator-(int rhs) const { return m_ptr - rhs; }
        str_iterator& operator+=(int rhs) { m_ptr += rhs; return *this; }
        str_iterator& operator-=(int rhs) { m_ptr -= rhs; return *this; }

        friend str_iterator operator+(int lhs, const str_iterator& rhs) { return rhs.m_ptr + lhs; }
        difference_type operator-(const str_iterator& rhs) const { return abs(m_ptr - rhs.m_ptr); }

        pointer ptr() const { return m_ptr; }

        reference operator*() const { return *m_ptr; }
        pointer operator->() const { return m_ptr; }
    private:
        pointer m_ptr;
    };
    
    template<typename T, bool constant>
    str_iterator<T, constant>& str_iterator<T, constant>::operator=(const str_iterator& other) 
    {
        if (this != &other)
        {
            m_ptr = other.m_ptr;
        }
        return *this;
    }

    template<typename T, bool constant>
    str_iterator<T, constant>& str_iterator<T, constant>::operator=(str_iterator&& other) noexcept
    { 
        if (this != &other)
        {
            m_ptr = other.m_ptr;
            other.m_ptr = nullptr;
        }
        return *this; 
    }

    template<typename T, bool constant>
    struct str_reverse_iterator
    {
    public:
        using value_type = T;
        using pointer = value_type*;
        using reference = typename std::conditional<constant, const value_type&, value_type&>::type;
        using difference_type = size_t;
        using iterator_category = std::random_access_iterator_tag;

        str_reverse_iterator() : m_ptr() {}
        str_reverse_iterator(const str_reverse_iterator& other) : m_ptr(other.m_ptr) {}
        str_reverse_iterator(str_reverse_iterator&& other) noexcept : m_ptr(other.m_ptr) { other.m_ptr = nullptr; }
        str_reverse_iterator(pointer ptr) : m_ptr(ptr) {}
        ~str_reverse_iterator() {}

        str_reverse_iterator& operator=(const str_reverse_iterator& other);
        str_reverse_iterator& operator=(str_reverse_iterator&& other) noexcept;

        bool operator==(const str_reverse_iterator& rhs) const { return m_ptr == rhs.m_ptr; }
        bool operator!=(const str_reverse_iterator& rhs) const { return m_ptr != rhs.m_ptr; }
        bool operator<(const str_reverse_iterator& rhs) const { return m_ptr < rhs.m_ptr; }
        bool operator>(const str_reverse_iterator& rhs) const { return m_ptr > rhs.m_ptr; }
        bool operator <=(const str_reverse_iterator& rhs) const { return m_ptr <= rhs.m_ptr; }
        bool operator >=(const str_reverse_iterator& rhs) const { return m_ptr >= rhs.m_ptr; }

        str_reverse_iterator operator++(int) { pointer Tmp = m_ptr; --m_ptr; return Tmp; }
        str_reverse_iterator& operator++() { --m_ptr; return *this; }
        str_reverse_iterator operator--(int) { pointer Tmp = m_ptr; ++m_ptr; return Tmp; }
        str_reverse_iterator& operator--() { ++m_ptr; return *this; }
        str_reverse_iterator operator+(int rhs) const { return m_ptr - rhs; }
        str_reverse_iterator operator-(int rhs) const { return m_ptr + rhs; }
        str_reverse_iterator& operator+=(int rhs) { m_ptr -= rhs; return *this; }
        str_reverse_iterator& operator-=(int rhs) { m_ptr += rhs; return *this; }

        friend str_reverse_iterator operator+(int lhs, const str_reverse_iterator& rhs) { return rhs.m_ptr + lhs; }
        difference_type operator-(const str_reverse_iterator& rhs) const { return abs(m_ptr - rhs.m_ptr); }

        pointer ptr() const { return m_ptr; }

        reference operator*() const { return *m_ptr; }
        pointer operator->() const { return m_ptr; }


    private:
        pointer m_ptr;
    };

    template<typename T, bool constant>
    str_reverse_iterator<T, constant>& str_reverse_iterator<T, constant>::operator=(const str_reverse_iterator& other)
    {
        if (this != &other)
        {
            m_ptr = other.m_ptr;
        }
        return *this;
    }

    template<typename T, bool constant>
    str_reverse_iterator<T, constant>& str_reverse_iterator<T, constant>::operator=(str_reverse_iterator&& other) noexcept
    {
        if (this != &other)
        {
            m_ptr = other.m_ptr;
            other.m_ptr = nullptr;
        }
        return *this;
    }

    template<typename T>
    struct basic_string
    {
    public:
        using value_type = T; // char type
        using pointer = value_type*;
        using reference = value_type&;
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
        bool operator!=(const basic_string<T>& rhs) const { return !(*this == rhs); }
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

        size_t size() const     { return m_size; }
        size_t length() const   { return m_size; }
        size_t capacity() const { return m_cap; }
        pointer data()     { return m_data; }
        const pointer data() const { return m_data; }
        pointer c_str()            { return m_data; }
        const pointer c_str() const{ return m_data; }

        iterator begin()    { return m_data; }
        iterator end()      { return (m_data + m_size); }
        const_iterator begin() const    { return m_data; }
        const_iterator end() const      { return (m_data + m_size); }
        const_iterator cbegin() const   { return m_data; }
        const_iterator cend() const { return (m_data + m_size); }
        reverse_iterator rbegin()   { return (m_data + m_size - 1); }
        reverse_iterator rend()     { return m_data - 1; }
        const_reverse_iterator rbegin() const   { return (m_data + m_size - 1); }
        const_reverse_iterator rend() const     { return (m_data - 1); }
        const_reverse_iterator crbegin() const  { return (m_data + m_size - 1); }
        const_reverse_iterator crend() const    { return m_data - 1; }

        bool empty() const { return m_size == 0; }

        reference push_back(value_type);
        reference insert(iterator, value_type);
        //FIXME: add insert(size_t index, value_type val)
        // add insert(size_t index = 0, const char* ptr)

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

        value_type& operator[](size_t index) { return m_data[index]; }
        const value_type& operator[](size_t index) const { return m_data[index]; }
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
        pointer m_data;
        size_t m_size;
        size_t m_cap;

    };

    template<typename T>
    basic_string<T>::basic_string() : m_data(nullptr), m_size(0), m_cap(0) {}

    template<typename T>
    basic_string<T>::basic_string(const char* ptr) : basic_string(ptr, strlen(ptr)) {};

    template<typename T>
    basic_string<T>::basic_string(const char* str, size_t amount)
        : m_data(new T[amount + 1]), m_size(amount), m_cap(m_size + 1)
    {
        for (size_t i = 0; i < amount; ++i)
        {
            *(m_data + i) = *(str++);
        }
        *(m_data + m_size) = '\0';
    }

    template<typename T>
    basic_string<T>::basic_string(size_t size, value_type ch)
        : m_data(new value_type[size+1]), m_size(size), m_cap(size+1)
    {
        for (size_t i = 0; i < size; ++i)
        {
            *(m_data + i) = ch;
        }
        *(m_data + m_size) = '\0';
    }

    template<typename T>
    template<typename iterType, typename std::enable_if<is_iterator<iterType>::value, int>::type>
    basic_string<T>::basic_string(iterType begin, iterType end)
        : m_data(nullptr), m_size(0), m_cap(0)
    {
        for (; begin != end; ++begin)
        {
            push_back(*begin);
        }
    }

    template<typename T>
    basic_string<T>::basic_string(const basic_string<T>& str, size_t pos, size_t len)
        : m_data(nullptr), m_size(0), m_cap(0)
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
        : m_data(new T[other.m_size + 1]), m_size(other.m_size), m_cap(m_size + 1)
    {
        for (size_t i = 0; i < m_cap; ++i)
        {
            *(m_data + i) = *(other.m_data + i);
        }
  
    }

    template<typename T>
    basic_string<T>::basic_string(basic_string<T>&& other) noexcept
        : m_data(other.m_data), m_size(other.m_size), m_cap(other.m_cap)
    {
        other.m_data = nullptr;
        other.m_size = 0;
        other.m_cap = 0;
    }

    template<typename T>
    basic_string<T>::~basic_string()
    {
        if (m_data)
        {
            destroy();
            delete[] m_data;
        }
    }

    template<typename T>
    basic_string<T>& basic_string<T>::operator=(const basic_string<T>& other)
    {
        // perhaps we could make this more efficient to not allocate if we already have enough capacity ?
        if (this != &other)
        {
            clear();
            m_data = new value_type[other.m_size + 1];
            m_size = other.m_size;
            m_cap = m_size + 1;
            for (size_t i = 0; i < m_cap; ++i)
            {
                *(m_data + i) = *(other.m_data + i);
            }
        }
        return *this;
    }

    template<typename T>
    basic_string<T>& basic_string<T>::operator=(basic_string<T>&& other) noexcept
    {
        if (this != &other)
        {
            clear();
            m_data = other.m_data;
            m_size = other.m_size;
            m_cap = other.m_cap;
            other.m_data = nullptr;
            other.m_size = 0;
            other.m_cap = 0;
        }
        return *this;
    }

    template<typename T>
    basic_string<T>& basic_string<T>::operator=(const char* str)
    {
        if (strlen(str) + 1 > m_cap)
        {
            reserve(strlen(str) + 1);
        }
        m_size = strlen(str);
        for (size_t i = 0; i < m_size; ++i)
        {
            *(m_data + i) = *(str++);
        }
        m_data[m_size] = '\0';
        return *this;
    }

    template<typename T>
    bool basic_string<T>::operator==(const basic_string<T>& rhs) const
    {
        if (m_size != rhs.m_size)
        {
            return false;
        }
        else
        {
            for (size_t i = 0; i < m_size; ++i)
            {
                if (*(m_data + i) != *(rhs.m_data + i))
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
        size_t size = m_size < rhs.m_size ? m_size : rhs.m_size;
        for (size_t i = 0; i < size; i++)
        {
            if ((*this)[i] != rhs[i])
            {
                return (*this)[i] > rhs[i];
            }
        }
        if (m_size == rhs.m_size)
        {
            return false;
        }
        else if (m_size > size)
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
        size_t size = m_size < rhs.m_size ? m_size : rhs.m_size;
        for (size_t i = 0; i < size; i++)
        {
            if ((*this)[i] != rhs[i])
            {
                return (*this)[i] < rhs[i];
            }
        }
        if (m_size == rhs.m_size)
        {
            return false;
        }
        else if (m_size > size)
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
        size_t size = m_size < rhs.m_size ? m_size : rhs.m_size;
        for (size_t i = 0; i < size; i++)
        {
            if ((*this)[i] != rhs[i])
            {
                return (*this)[i] >= rhs[i];
            }
        }
        if (m_size >= rhs.m_size)
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
        size_t size = m_size < rhs.m_size ? m_size : rhs.m_size;
        for (size_t i = 0; i < size; i++)
        {
            if ((*this)[i] != rhs[i])
            {
                return (*this)[i] <= rhs[i];
            }
        }
        if (m_size >= rhs.m_size)
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
        aux.m_data = new value_type[m_size + 2];
        for (size_t i = 0; i < m_size; ++i)
        {
            aux[i] = (*this)[i];
        }
        aux[m_size] = ch;
        aux[m_size + 1] = '\0';
        aux.m_size = m_size + 1;
        aux.m_cap = aux.m_size + 1;
        return aux;
    }

    template<typename T>
    basic_string<T> basic_string<T>::operator+(const char* ptr) const
    {
        basic_string<T> aux;
        aux.m_data = new value_type[m_size + strlen(ptr) + 1];
        for (size_t i = 0; i < m_size; ++i)
        {
            aux[i] = (*this)[i];
        }
        for (size_t i = 0; ptr[i] != 0; ++i)
        {
            aux[m_size + i] = ptr[i];
        }
        aux.m_size = m_size + strlen(ptr);
        aux[aux.m_size] = '\0';
        aux.m_cap = aux.m_size + 1;
        return aux;
    }

    template<typename T>
    basic_string<T> basic_string<T>::operator+(const basic_string<T>& other) const
    {
        basic_string<T> aux;
        aux.m_data = new value_type[m_size + other.m_size + 1];
        // aux m_size = m_size + other.m_size
        for (size_t i = 0; i < m_size; ++i)
        {
            aux[i] = (*this)[i];
        }
        for (size_t i = 0; i < other.m_size; ++i)
        {
            aux[m_size + i] = other[i];
        }
        aux.m_size = m_size + other.m_size;
        aux[aux.m_size] = '\0';
        aux.m_cap = aux.m_size + 1;
        return aux;
    }

    template<typename T>
    basic_string<T>& basic_string<T>::operator+=(value_type ch)
    {
        basic_string<T> aux;
        aux.m_data = new value_type[m_size + 2];
        for (size_t i = 0; i < m_size; ++i)
        {
            aux[i] = (*this)[i];
        }
        aux[m_size] = ch;
        aux[m_size + 1] = '\0';
        aux.m_size = m_size + 1;
        aux.m_cap = aux.m_size + 1;
        *this = std::move(aux);
        return *this;
    }

    template<typename T>
    basic_string<T>& basic_string<T>::operator+=(const char* ptr)
    {
        basic_string<T> aux;
        aux.m_data = new value_type[m_size + strlen(ptr) + 1];
        for (size_t i = 0; i < m_size; ++i)
        {
            aux[i] = (*this)[i];
        }
        for (size_t i = 0; i < strlen(ptr); ++i)
        {
            aux[m_size + i] = ptr[i];
        }
        aux.m_size = m_size + strlen(ptr);
        aux[aux.m_size] = '\0';
        aux.m_cap = aux.m_size + 1;
        *this = std::move(aux);
        return *this;
    }

    template<typename T>
    basic_string<T>& basic_string<T>::operator+=(const basic_string<T>& other)
    {
        basic_string<T> aux;
        aux.m_data = new value_type[m_size + other.m_size + 1];
        for (size_t i = 0; i < m_size; ++i)
        {
            aux[i] = (*this)[i];
        }
        for (size_t i = 0; i < other.m_size; ++i)
        {
            aux[m_size + i] = other[i];
        }
        aux.m_size = m_size + other.m_size;
        aux[aux.m_size] = '\0';
        aux.m_cap = aux.m_size + 1;
        *this = std::move(aux);
        return *this;
    }


    template<typename T>
    void basic_string<T>::reserve(size_t newCapacity)
    {
        if (newCapacity > m_cap)
        {
            realloc(newCapacity);
        }
    }

    template<typename T>
    typename basic_string<T>::reference basic_string<T>::push_back(value_type elementToAdd)
    {
        // Don't do `m_cap - 1` because cap might be 0
        if (m_size + 1 >= m_cap)
        {
            // std::cout << "Realloc\n";
            realloc(m_cap + m_cap / 2);
        }
        *(m_data + m_size++) = elementToAdd;
        *(m_data + m_size) = '\0';
        return m_data[m_size - 1];
    }
    
    template<typename T>
    typename basic_string<T>::reference basic_string<T>::insert(iterator position, value_type elementToAdd)
    {
        // Note: iterator position will be invalid if we reallocate
        if ((position > begin() && position < end()) || position == begin())
        {
            size_t safePosition = abs(position - begin());
            if (m_size+1 >= m_cap)
            {
                realloc(m_cap + m_cap / 2);
            }
            ++m_size;
            for (iterator it = end() - 1; it >= begin() + safePosition; --it)
            {
                *(it + 1) = *it;
            }
            *(begin() + safePosition) = elementToAdd;
            return *(begin() + safePosition);
        }
        else if (position == end())
        {
            push_back(elementToAdd);
        }
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
        if (m_size > 0)
        {
            --m_size;
            (m_data + m_size)->~T();
        }
    }

    template<typename T>
    void basic_string<T>::erase(iterator pos)
    {
        if (m_size > 0)
        {
            if (pos >= begin() && pos < end())
            {
                (pos.ptr())->~T();
                for (; pos != end(); ++pos)
                {
                    *pos = *(pos + 1);
                    // again, not using std::move, because && will be 8 bytes, which should usually be > T
                }
                --m_size;
                m_data[m_size] = '\0';
            }
        }
    }

    template<typename T>
    void basic_string<T>::erase(const basic_string<T>& toRemove)
    {
        if (m_size >= toRemove.size())
        {
            for (auto it = begin(); it != end() - toRemove.size() + 1; ++it)
            {
                auto copyIt = it;
                bool found = true;
                for (auto it2 = toRemove.begin(); it2 != toRemove.end(); ++it2)
                {
                    if ( *it2 != *(copyIt++) )
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
                    m_size -= toRemove.size();
                    m_data[m_size] = '\0';
                    return;
                }
            }
        }
    }

    template<typename T>
    void basic_string<T>::clear()
    {
        if (m_data != nullptr)
        {
            destroy();
            delete[] m_data;
            m_data = nullptr;
            m_size = 0;
            m_cap = 0;
        }
    }

    template<typename T>
    void basic_string<T>::resize(size_t count)
    {
        if (count < m_size)
        {
            while (m_size > count)
            {
                pop_back();
            }
        }
        else if (count > m_size)
        {
            if (count > m_cap)
            {
                reserve(count);
            }
            while (m_size < count)
            {
                push_back(T());
            }
        }
    }

    template<typename T>
    void basic_string<T>::resize(size_t count, value_type value)
        // not taking const& as param because value_type should be < 8 bytes
    {
        if (count < m_size)
        {
            while (m_size > count)
            {
                pop_back();
            }
        }
        else if (count > m_size)
        {
            if (count > m_cap)
            {
                reserve(count);
            }
            while (m_size < count)
            {
                push_back(value);
            }
        }
    }

    template<typename T>
    void basic_string<T>::shrink_to_fit()
    {
        if (m_size + 1 != m_cap)
        {
            realloc(m_size + 1);
        }
    }

    template<typename T>
    void basic_string<T>::swap(basic_string<T>& other)
    {
        kq::swap(m_data, other.m_data);
        kq::swap(m_size, other.m_size);
        kq::swap(m_cap, other.m_cap);
    }

    template<typename T>
    basic_string<T> basic_string<T>::substr(size_t pos, size_t count) const
    {
        return kq::basic_string<T>(*this, pos, count);
    }

    template<typename T>
    size_t basic_string<T>::find(value_type ch, size_t pos) const
    {
        for (size_t i = pos; i < m_size; ++i)
        {
            if (*(m_data + i) == ch)
            {
                return i;
            }
        }
        return m_size;
    }

    template<typename T>
    size_t basic_string<T>::find(const char* ptr, size_t pos) const
    {
        for (size_t i = pos; i < m_size; ++i)
        {
            size_t j = 0;
            for (; ptr[j] != 0; ++j)
            {
                if (ptr[j] != *(m_data + i + j))
                {
                    break;
                }
            }
            if (ptr[j] == 0)
            {
                return i;
            }
        }
        return m_size;
    }

    template<typename T>
    size_t basic_string<T>::find(const basic_string<T>& str, size_t pos) const
    {
        for (size_t i = pos; i < m_size; ++i)
        {
            if (substr(i, str.size()) == str)
            {
                return i;
            }
        }
        return m_size;
    }

    template<typename T>
    typename basic_string<T>::value_type& basic_string<T>::front()
    {
        if (m_size == 0)
        {
            throw std::out_of_range("front(), called on empty string");
        }
        return *m_data;
    }

    template<typename T>
    const typename basic_string<T>::value_type& basic_string<T>::front() const
    {
        if (m_size == 0)
        {
            throw std::out_of_range("front(), called on empty string");
        }
        return *m_data;
    }

    template<typename T>
    typename basic_string<T>::value_type& basic_string<T>::back()
    {
        if (m_size == 0)
        {
            throw std::out_of_range("back(), called on empty string");
        }
        return *(m_data + m_size - 1);
    }

    template<typename T>
    const typename basic_string<T>::value_type& basic_string<T>::back() const
    {
        if (m_size == 0)
        {
            throw std::out_of_range("back(), called on empty string");
        }
        return *(m_data + m_size - 1);
    }

    template<typename T>
    typename basic_string<T>::value_type& basic_string<T>::at(size_t index)
    {
        if (index >= m_size || m_size == 0)
        {
            throw std::out_of_range("at(), trying to access element out of range on string");
        }
        return m_data[index];
    }

    template<typename T>
    const typename basic_string<T>::value_type& basic_string<T>::at(size_t index) const
    {
        if (index >= m_size || m_size == 0)
        {
            throw std::out_of_range("at(), trying to access element out of range on string");
        }
        return m_data[index];
    }

    template<typename CharT, typename Traits>
    std::basic_ostream<CharT, Traits>& operator<<(std::basic_ostream<CharT, Traits>& os, const kq::basic_string<CharT>& str)
    {
        if(str.m_data)
        os << (str.m_data);
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
        while (ch != delim)
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


        pointer newBlock = new value_type[newCapacity];

        if (m_data && newBlock)
        {
            for (size_t i = 0; i < m_size; ++i)
            {
                *(newBlock + i) = std::move(*(m_data + i));
            }
        }
        newBlock[m_size] = '\0';

        destroy();
        delete[] m_data;
        m_data = newBlock;
        m_cap = newCapacity;
        
    }

    template<typename T>
    void basic_string<T>::destroy()
    {
        if (m_data)
        {
            for (size_t i = 0; i < m_size; ++i)
            {
                (m_data + i)->~value_type();
            }
        }
    }

    
}

#endif