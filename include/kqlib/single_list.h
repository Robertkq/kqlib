#ifndef kqsingle_list_
#define kqsingle_list_

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

        sl_iterator() : kq_ptr()                                        {}
        sl_iterator(const sl_iterator& other) : kq_ptr(other.kq_ptr)    {}
        sl_iterator(sl_iterator&& other) : kq_ptr(other.kq_ptr)         { other.kq_ptr = nullptr; }
        sl_iterator(element* ptr) : kq_ptr(ptr)                         {}

        sl_iterator& operator=(const sl_iterator& other)                { kq_ptr = other.kq_ptr; }
        sl_iterator& operator=(sl_iterator&& other)                     { kq_ptr = other.kq_ptr; other.kq_ptr = nullptr; }

        bool operator!=(const sl_iterator& other) const                 { return kq_ptr != other.kq_ptr; }
        bool operator==(const sl_iterator& other) const                 { return kq_ptr == other.kq_ptr; }

        sl_iterator& operator++()                                       { kq_ptr = kq_ptr->next; return *this; }
        sl_iterator& operator++(int)                                    { element* tmp = kq_ptr; ++kq_ptr; return tmp; }

        reference operator*() const                                     { return kq_ptr->value; }
        pointer operator->() const                                      { return &(kq_ptr->value); }

    private:
        element* kq_ptr;
    };

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

        iterator begin() const { return kq_ptr; }
        iterator end() const { return nullptr; }

        single_list() : kq_ptr(nullptr), kq_size(0) {}
            

        ~single_list();

        void push_back(const value_type& value);
        template<typename... Args>
        void emplace_back(Args&&... args);

        void pop_back();
        void pop_front();

    private:
        element* kq_ptr;
        size_t kq_size;
    };

    template<typename T>
    single_list<T>::~single_list()
    {
        element* current = kq_ptr;
        element* next;
        for (int i = 0; i < kq_size; ++i)
        {
            next = current->next;
            delete current;
            current = next;
        }
    }

    template<typename T>
    void single_list<T>::push_back(const value_type& value)
    {
        if (kq_size == 0)
        {
            kq_ptr = new element(value);
            ++kq_size;
        }
        else
        {
            element* last = kq_ptr;
            while (last->next != nullptr)
            {
                last = last->next;
            }
            last->next = new element(value);
            ++kq_size;
        }
    }

    template<typename T>
    template<typename... Args>
    void single_list<T>::emplace_back(Args&&... args)
    {
        if (kq_size == 0)
        {
            kq_ptr = new element(std::forward<Args>(args)...);
            ++kq_size;
        }
        else
        {
            element* last = kq_ptr;
            while (last->next != nullptr)
            {
                last = last->next;
            }
            last->next = new element(std::forward<Args>(args)...);
            ++kq_size;
        }
    }

    template<typename T>
    void single_list<T>::pop_back()
    {
        if (kq_size != 0)
        {
            if (kq_size == 1)
            {
                delete kq_ptr;
                --kq_size;
            }
            else
            {
                element* prev = kq_ptr;
                element* last = kq_ptr->next;
                while (last->next != nullptr)
                {
                    prev = last;
                    last = last->next;
                }
                delete last;
                prev->next = nullptr;
                --kq_size;

            }
        }
    }

    template<typename T>
    void single_list<T>::pop_front()
    {
        if (kq_size != 0)
        {
            element* dell = kq_ptr;
            kq_ptr = kq_ptr->next;
            delete dell;
            --kq_size;
        }
    }

} // namespace kq

#endif