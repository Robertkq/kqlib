#ifndef kqstring_
#define kqstring_

namespace kq
{
    // T - char type
    template<typename T>
    struct basic_string
    {
        basic_string() : kq_data(nullptr), kq_size(0), kq_cap(0) {}
        basic_string(const basic_string& <T>);
        basic_string(basic_string<T>&&);
        ~basic_string();

    private:
        pointer_type kq_data;
        size_t kq_size;
        size_t kq_cap;
    };

    template<typename T>
    basic_string<T>::basic_string() : kq_data(nullptr), kq_size(0), kq_cap(0) {}

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
}

#endif