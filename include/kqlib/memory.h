#ifndef KQMEMORY_
#define KQMEMORY_

#include "other.h"

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
        unique_ptr(pointer ptr);
        template<typename T2, typename Dx2, typename std::enable_if<(std::is_convertible<T2*, T*>::type, std::is_assignable<Dx, Dx2>::type), int>::type = 0>
        unique_ptr(unique_ptr<T2, Dx2>&& other);
        ~unique_ptr();

        unique_ptr& operator=(const unique_ptr&) = delete;
        unique_ptr& operator=(unique_ptr&&) noexcept;
        unique_ptr& operator=(pointer ptr);
        template<typename T2, typename Dx2, typename std::enable_if<(std::is_convertible<T2*, T*>::type, std::is_assignable<Dx, Dx2>::type), int>::type = 0>
        unique_ptr& operator=(unique_ptr<T2, Dx2>&& other);

        void reset();
        pointer release();

    private:

        T* m_pointer;
        DX m_deleter;
    }; // unique_ptr

    template<typename T, typename Dx>
    unique_ptr<T, Dx>::unique_ptr()
        : m_pointer(nullptr), m_deleter()
    {}

    template<typename T, typename Dx>
    unique_ptr<T, Dx>::unique_ptr(unique_ptr&& other) noexcept
        : m_pointer(other.release()), m_deleter(other.m_deleter)
    {}

    template<typename T, typename Dx>
    unique_ptr<T, Dx>::unique_ptr(pointer ptr)
        : m_pointer(ptr), m_deleter()
    {}

    template<typename T, typename Dx>
    template<typename T2, typename Dx2, typename std::enable_if<(std::is_convertible<T2*, T*>::type, std::is_assignable<Dx, Dx2>::type), int>::type>
    unique_ptr<T, Dx>::unique_ptr(unique_ptr<T2, Dx2>&& other)
    {

    }

    template<typename T, typename Dx>
    unique_ptr<T, Dx>::~unique_ptr()
    {
        reset();
    }


    template<typename T, typename Dx>
    unique_ptr<T, Dx>& unique_ptr<T, Dx>::operator=(unique_ptr&&) noexcept
    {

    }

    template<typename T, typename Dx>
    unique_ptr<T, Dx>& unique_ptr<T, Dx>::operator=(pointer ptr)
    {

    }

    template<typename T, typename Dx>
    template<typename T2, typename Dx2, typename std::enable_if<(std::is_convertible<T2*, T*>::type, std::is_assignable<Dx, Dx2>::type), int>::type>
    unique_ptr<T, Dx>& unique_ptr<T, Dx>::operator=(unique_ptr<T2, Dx2>&& other)
    {

    }

    template<typename T, typename Dx>
    void unique_ptr<T, Dx>::reset()
    {
        m_deleter(m_pointer);
        m_pointer = nullptr;
    }

    template<typename T, typename Dx>
    typename unique_ptr<T, Dx>::pointer unique_ptr<T, Dx>::release()
    {
        auto ret = m_pointer;
        m_pointer = nullptr;
        return ret;
    }
}

#endif