#ifndef kqstring_
#define kqstring_

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
    public:
        basic_string();
        basic_string(const char* str);
        basic_string(const char* str, size_t amount);
        basic_string(const basic_string<T>&);
        basic_string(basic_string<T>&&);
        ~basic_string();
    public:
        // friend functions
        friend std::ostream& operator<<(std::ostream& os, const basic_string<char>& value);

    private:
   
    private:
        pointer_type kq_data;
        size_t kq_size;
        size_t kq_cap;

    };

    template<typename T>
    basic_string<T>::basic_string() : kq_data(nullptr), kq_size(0), kq_cap(0) {}

    template<typename T>
    basic_string<T>::basic_string(const char* ptr) : basic_string(ptr, strlen(ptr));

    template<typename T>
    basic_string<T>::basic_string(const char* str, size_t amount)
        : kq_data(new T[amount]), kq_size(amount), kq_cap(kq_size)
    {
        for (size_t i = 0; i < amount; ++i)
        {
            *(kq_data + i) = *(str++);
        }
    }

    template<typename T>
    basic_string<T>::basic_string(const basic_string<T>& other)
        : kq_data(new T[other.kq_size]), kq_size(other.kq_size), kq_cap(kq_size)
    {
        for (size_t i = 0; i < kq_size; ++i)
        {
            *(kq_data + i) = *(other.kq_data + i);
        }
    }

    template<typename T>
    basic_string<T>::basic_string(basic_string<T>&& other)
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
            delete[] kq_data;
        }
    }

    std::ostream& operator<<(std::ostream& os, const basic_string<char>& value)
    {
        os << value.kq_data;
        return os;
    }

    
}

#endif