#ifndef KQMEMORY_
#define KQMEMORY_

namespace kq
{
    template<typename T>
    struct default_deleter
    {
        void operator()(T* ptr) const noexcept
        {
            delete ptr;
        }
    };

    template<typename T> // default deletor for array types
    struct default_deleter<T[]>
    {
        void operator()(T* ptr) const noexcept
        {
            delete[] ptr;
        }
    };

    template<typename T, typename Dx = default_deleter<T>>
    struct unique_ptr
    {
    public:

        using pointer = T*;
        using value_type = T;
        using deleter_type = Dx;

        unique_ptr();
        unique_ptr(const unique_ptr&) = delete;
        unique_ptr(unique_ptr&&) noexcept;
        ~unique_ptr();

        unique_ptr& operator=(const unique_ptr&) = delete;
        unique_ptr& operator=(unique_ptr&&) noexcept;

        unique_ptr& operator=(T* ptr);
        unique_ptr& operator

        void reset();

    private:

        T* m_pointer;
    };
}

#endif