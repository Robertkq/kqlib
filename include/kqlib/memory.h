#ifndef KQMEMORY_
#define KQMEMORY_

#include "other.h"
#include <mutex>

namespace kq
{

    template<typename T>
    struct default_deleter
    {
        default_deleter() = default;

        template<typename U, typename std::enable_if<std::is_convertible<U*, T*>::value, int>::type = 0>
        default_deleter(const default_deleter<U>& other) {}

        void operator()(T* ptr) const noexcept
        {
            delete ptr;
        }
    };

    template<typename T> // default deletor for array types
    struct default_deleter<T[]>
    {
        default_deleter() = default;

        template<typename U, typename std::enable_if<std::is_convertible<U (*)[], T(*)[]>::value, int>::type = 0>
        default_deleter(const default_deleter<U>& other) {}

        void operator()(T* ptr) const noexcept
        {
            delete[] ptr;
        }
    };


    template<typename T, typename Dx = default_deleter<T>>
    struct unique_ptr
    {
    public:
        
        using value_type = typename std::remove_all_extents<T>::type;
        using pointer = value_type*;
        using deleter_type = Dx;

        unique_ptr();
        unique_ptr(const unique_ptr&) = delete;
        unique_ptr(pointer ptr);
        template<typename T2, typename Dx2, typename std::enable_if<(std::is_convertible_v<T2*, T*>, std::is_constructible_v<Dx, Dx2>), int>::type = 0>
        unique_ptr(unique_ptr<T2, Dx2>&& other) noexcept;
        ~unique_ptr();

        unique_ptr& operator=(const unique_ptr&) = delete;
        unique_ptr& operator=(pointer ptr);
        template<typename T2, typename Dx2, typename std::enable_if<(std::is_convertible_v<T2*, T*>, std::is_assignable_v<Dx&, Dx2>), int>::type = 0>
        unique_ptr& operator=(unique_ptr<T2, Dx2>&& other) noexcept;

        void reset(pointer ptr = nullptr);
        pointer release();
        explicit operator bool() const { return m_pointer != nullptr; }

        pointer get() const { return m_pointer; }
        deleter_type& get_deleter() { return m_deleter; }
        const deleter_type& get_deleter() const { return m_deleter; }      

        // Used typename U to make those function non-dependent so they dont instanciate with unique_ptr<T>
        template<typename U = T, typename std::enable_if<!std::is_array_v<U>, int>::type = 0>
        value_type& operator*() const { return *m_pointer; }
        template<typename U = T, typename std::enable_if<!std::is_array_v<U>, int>::type = 0>
        pointer operator->() const { return m_pointer; }

        template<typename U = T, typename std::enable_if<std::is_array_v<U>, int>::type = 0>
        value_type& operator[](size_t index) const { return m_pointer[index]; }

    private:
        pointer m_pointer;
        deleter_type m_deleter;   
    }; // unique_ptr

    template<typename T, typename Dx>
    unique_ptr<T, Dx>::unique_ptr()
        : m_pointer(nullptr), m_deleter()
    {}

    template<typename T, typename Dx>
    unique_ptr<T, Dx>::unique_ptr(pointer ptr)
        : m_pointer(ptr), m_deleter()
    {}

    template<typename T, typename Dx>
    template<typename T2, typename Dx2, typename std::enable_if <(std::is_convertible_v<T2*, T*>, std::is_constructible_v<Dx, Dx2>), int>::type>
    unique_ptr<T, Dx>::unique_ptr(unique_ptr<T2, Dx2>&& other) noexcept
        : m_pointer(other.release()), m_deleter(other.get_deleter())
    {}

    template<typename T, typename Dx>
    unique_ptr<T, Dx>::~unique_ptr()
    {
        reset();
    }

    template<typename T, typename Dx>
    unique_ptr<T, Dx>& unique_ptr<T, Dx>::operator=(pointer ptr)
    {
        reset(ptr);
        return *this;
    }

    template<typename T, typename Dx>
    template<typename T2, typename Dx2, typename std::enable_if<(std::is_convertible_v<T2*, T*>, std::is_assignable_v<Dx&, Dx2>), int>::type>
    unique_ptr<T, Dx>& unique_ptr<T, Dx>::operator=(unique_ptr<T2, Dx2>&& other) noexcept
    {
        reset(other.release());
        m_deleter = std::move(other.get_deleter());
        return *this;
    }

    template<typename T, typename Dx>
    void unique_ptr<T, Dx>::reset(pointer ptr)
    {
        m_deleter(m_pointer);
        m_pointer = ptr;
    }

    template<typename T, typename Dx>
    typename unique_ptr<T, Dx>::pointer unique_ptr<T, Dx>::release()
    {
        auto ret = m_pointer;
        m_pointer = nullptr;
        return ret;
    }

    
    template<typename T, typename... Args, typename std::enable_if<!std::is_array_v<T>, int>::type = 0>
    unique_ptr<T> make_unique(Args&&... args)
    {
        return unique_ptr<T>(new T(std::forward<Args>(args)...));
    }

    template<typename T, typename std::enable_if<std::is_array_v<T>, int>::type = 0>
    unique_ptr<T> make_unique(size_t count)
    {
        return unique_ptr<T>(new typename unique_ptr<T>::value_type[count]);
    }

    struct ref_count { // handles reference counting for shared_ptr
    public:
        ref_count();
        ref_count(const ref_count&) = delete;
        ref_count(ref_count&& other) noexcept;
    private:

        std::mutex m_mutex;
        size_t m_uses;
        // size_t m_weaks; //FIXME: should look into implementing this 
    };

    ref_count::ref_count()
        : m_mutex(), m_uses()
    {}

    ref_count::ref_count(ref_count&& other) noexcept
        : m_mutex(), m_uses()
    {
        std::unique_lock(other.m_mutex);
        m_uses = other.m_uses;
        other.m_uses = 0;
    }

    template<typename T, typename Dx>
    struct shared_ptr
    {
    public:
        using value_type = T;
        using pointer = value_type*;
        using deleter_type = Dx;

        shared_ptr();

    private:
        pointer m_pointer;
        ref_count* m_refc;
        deleter_type m_deleter;
    };
    
}

#endif