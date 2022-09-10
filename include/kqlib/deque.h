#ifndef KQDEQUE_
#define KQDEQUE_

#include "other.h"

namespace kq
{
	template<typename T, bool constant>
	struct dq_iterator
	{
	public:
		using value_type = T;
		using pointer = value_type*;
		using difference_type = size_t;
		using reference = typename std::conditional<constant, const value_type&, value_type&>::type;
		using iterator_category = std::random_access_iterator_tag;

		dq_iterator() : m_ptr() {}
		dq_iterator(const dq_iterator& other) : m_ptr(other.m_ptr) {}
		dq_iterator(dq_iterator&& other) noexcept : m_ptr(other.m_ptr) { other.m_ptr = nullptr; }
		dq_iterator(pointer ptr_) : m_ptr(ptr_) {};
		
		dq_iterator& operator=(const dq_iterator& other);
		dq_iterator& operator=(dq_iterator&& other) noexcept;

		bool operator==(const dq_iterator& other) const { return m_ptr == other.m_ptr; }
		bool operator!=(const dq_iterator& other) const { return m_ptr != other.m_ptr; }
		bool operator>(const dq_iterator& other) const { return m_ptr > other.m_ptr; }
		bool operator<(const dq_iterator& other) const { return m_ptr < other.m_ptr; }
		bool operator>=(const dq_iterator& other) const { return m_ptr >= other.m_ptr; }
		bool operator<=(const dq_iterator& other) const { return m_ptr <= other.m_ptr; }

		dq_iterator operator++(int) { auto Tmp = *this; ++m_ptr; return Tmp; }
		dq_iterator& operator++() { ++m_ptr; return *this; }
		dq_iterator operator--(int) { auto Tmp = *this; --m_ptr; return Tmp; }
		dq_iterator& operator--() { --m_ptr; return *this; }
		dq_iterator operator+(int rhs) const { return m_ptr + rhs; }
		dq_iterator operator-(int rhs) const { return m_ptr - rhs; }
		dq_iterator& operator+=(int rhs) { m_ptr += rhs; return *this; }
		dq_iterator& operator-=(int rhs) { m_ptr -= rhs; return *this; }
		size_t operator-(const dq_iterator& rhs) const { return abs(m_ptr - rhs.m_ptr); }
		friend dq_iterator operator+(int lhs, const dq_iterator& rhs) { return rhs.m_ptr + lhs; }

		pointer ptr() const { return m_ptr; }

		reference operator*() { return *m_ptr; }
		pointer operator->() const { return m_ptr; }

	private:
		pointer m_ptr;
	};

	template<typename T, bool constant>
	dq_iterator<T, constant>& dq_iterator<T, constant>::operator=(const dq_iterator& other) 
	{
		if (this != &other)
		{
			m_ptr = other.m_ptr;
		}
		return *this; 
	}

	template<typename T, bool constant>
	dq_iterator<T, constant>& dq_iterator<T, constant>::operator=(dq_iterator&& other) noexcept 
	{
		if (this != &other)
		{
			m_ptr = other.m_ptr;
			other.m_ptr = nullptr;
		}
		return *this;
	}

	template<typename T, bool constant>
	struct dq_reverse_iterator
	{
	public:
		using value_type = T;
		using pointer = value_type*;
		using difference_type = size_t;
		using reference = typename std::conditional<constant, const value_type&, value_type&>::type;
		using iterator_category = std::random_access_iterator_tag;

		dq_reverse_iterator() : m_ptr() {}
		dq_reverse_iterator(const dq_reverse_iterator& other) : m_ptr(other.m_ptr) {}
		dq_reverse_iterator(dq_reverse_iterator&& other) noexcept : m_ptr(other.m_ptr) { other.m_ptr = nullptr; }
		dq_reverse_iterator(pointer ptr_) : m_ptr(ptr_) {};

		dq_reverse_iterator& operator=(const dq_reverse_iterator& other);
		dq_reverse_iterator& operator=(dq_reverse_iterator&& other) noexcept;

		bool operator==(const dq_reverse_iterator& other) const { return m_ptr == other.m_ptr; }
		bool operator!=(const dq_reverse_iterator& other) const { return m_ptr != other.m_ptr; }
		bool operator>(const dq_reverse_iterator& other) const { return m_ptr < other.m_ptr; }
		bool operator<(const dq_reverse_iterator& other) const { return m_ptr > other.m_ptr; }
		bool operator>=(const dq_reverse_iterator& other) const { return m_ptr <= other.m_ptr; }
		bool operator<=(const dq_reverse_iterator& other) const { return m_ptr >= other.m_ptr; }

		dq_reverse_iterator operator++(int) { auto Tmp = *this; --m_ptr; return Tmp; }
		dq_reverse_iterator& operator++() { --m_ptr; return *this; }
		dq_reverse_iterator operator--(int) { auto Tmp = *this; ++m_ptr; return Tmp; }
		dq_reverse_iterator& operator--() { ++m_ptr; return *this; }
		dq_reverse_iterator operator+(int rhs) const { return m_ptr - rhs; }
		dq_reverse_iterator operator-(int rhs) const { return m_ptr + rhs; }
		dq_reverse_iterator& operator+=(int rhs) { m_ptr -= rhs; return *this; }
		dq_reverse_iterator& operator-=(int rhs) { m_ptr += rhs; return *this; }
		size_t operator-(const dq_reverse_iterator& rhs) const { return abs(m_ptr - rhs.m_ptr); }
		friend dq_reverse_iterator operator+(int lhs, const dq_reverse_iterator& rhs) { return rhs.m_ptr - lhs; }

		pointer ptr() const { return m_ptr; }

		reference operator*() const { return *m_ptr; }
		pointer operator->() const { return m_ptr; }

	private:
		pointer m_ptr;
	};

	template<typename T, bool constant>
	dq_reverse_iterator<T, constant>& dq_reverse_iterator<T, constant>::operator=(const dq_reverse_iterator& other)
	{
		if (this != &other)
		{
			m_ptr = other.m_ptr;
		}
		return *this;
	}

	template<typename T, bool constant>
	dq_reverse_iterator<T, constant>& dq_reverse_iterator<T, constant>::operator=(dq_reverse_iterator&& other) noexcept
	{
		if (this != &other)
		{
			m_ptr = other.m_ptr;
			other.m_ptr = nullptr;
		}
		return *this;
	}


	template<typename T>
	struct deque
	{
	public:
		using value_type = T;
		using pointer = T*;
		using reference = T&;
		using iterator = dq_iterator<value_type, false>;
		using const_iterator = dq_iterator<value_type, true>;
		using reverse_iterator = dq_reverse_iterator<value_type, false>;
		using const_reverse_iterator = dq_reverse_iterator<value_type, true>;

		deque();
		deque(const deque&);
		deque(deque&&) noexcept;
		deque(size_t);
		deque(size_t, const value_type&);
		template<typename iterType, typename std::enable_if<is_iterator<iterType>::value, int>::type = 0>
		deque(iterType, iterType);
		template<typename ilT>
		deque(const std::initializer_list<ilT>&);
		~deque();

		deque& operator=(const deque&);
		deque& operator=(deque&&) noexcept;

		template<typename ilT>
		deque& operator=(const std::initializer_list<ilT>&);

		bool operator==(const deque&) const;
		bool operator!=(const deque& other) const { return !(*this == other); }

		size_t size() const { return m_size; }
		size_t capacity() const { return m_cap; }
		pointer data() const { return m_data; }
		size_t margin() const { return m_margin; }

		iterator begin() { return m_data + m_margin; }
		iterator end() { return m_data + m_margin + m_size; }
		const_iterator begin() const { return m_data + m_margin; }
		const_iterator end() const { return m_data + m_margin + m_size; }
		const_iterator cbegin() const { return m_data + m_margin; }
		const_iterator cend() const { return m_data + m_margin + m_size; }
		reverse_iterator rbegin() { return m_data + m_margin + m_size - 1; }
		reverse_iterator rend() { return m_data - 1; }
		const_reverse_iterator rbegin() const { return m_data + m_margin + m_size - 1; }
		const_reverse_iterator rend() const { return m_data - 1; }
		const_reverse_iterator crbegin() const { return m_data + m_margin + m_size - 1; }
		const_reverse_iterator crend() const { return m_data - 1; }


		bool empty() const { return m_size == 0; }

		value_type& push_back(const value_type&);
		value_type& push_front(const value_type&);
		template<typename... Args>
		value_type& emplace_back(Args&&... args);
		template<typename... Args>
		value_type& emplace_front(Args&&... args);
		value_type& insert(iterator position, const value_type&);
		template<typename... Args>
		value_type& emplace(iterator position, Args&&... args);

		void assign(size_t, const value_type&);
		template<typename iterType>
		typename std::enable_if<is_iterator<iterType>::value, void>::type
			assign(iterType, iterType);
		template<typename ilT>
		void assign(const std::initializer_list<ilT>&);

		void pop_back();
		void pop_front();
		void erase(iterator position);
		void clear();

		void reserve(size_t);
		void shrink_to_fit() { realloc_exactly(m_size); }
		void swap(deque&);

		value_type& front();
		const value_type& front() const;
		value_type& back();
		const value_type& back() const;

		value_type& operator[](size_t index) { return *(m_data + m_margin + index); }
		const value_type& operator[](size_t index) const { return *(m_data + m_margin + index); }
		value_type& at(size_t);
		const value_type& at(size_t) const;

	private:
		pointer m_data;
		size_t m_size;
		size_t m_cap;
		size_t m_margin;

		void realloc(size_t);
		void realloc_exactly(size_t);
		void destroy();
	};

	template<typename T>
	deque<T>::deque()
		: m_data(nullptr), m_size(0), m_cap(0), m_margin(0)
	{}

	template<typename T>
	deque<T>::deque(const deque& other)
		: m_data(nullptr), m_size(0), m_cap(0), m_margin(0)
	{
		assign(other.begin(), other.end());
	}

	template<typename T>
	deque<T>::deque(deque&& other) noexcept
		: m_data(other.m_data), m_size(other.m_size), m_cap(other.m_cap), m_margin(other.m_margin)
	{
		other.m_data = nullptr;
		other.m_size = 0;
		other.m_cap = 0;
		other.m_margin = 0;
	}

	template<typename T>
	deque<T>::deque(size_t size)																		// m_cap / 2 - 1
		: m_data((pointer)::operator new[](sizeof(value_type)* size)), m_size(size), m_cap(size), m_margin(0)
	{
		for (size_t i = 0; i < m_size; ++i)
			new (m_data + i) value_type();
	}

	template<typename T>
	deque<T>::deque(size_t size, const value_type& objectToFill)
		: m_data(nullptr), m_size(0), m_cap(0), m_margin(0)
	{
		assign(size, objectToFill);
	}

	template<typename T>
	template<typename iterType, typename std::enable_if<is_iterator<iterType>::value, int>::type>
	deque<T>::deque(iterType first, iterType last)
		: m_data(nullptr), m_size(0), m_cap(0), m_margin(0)
	{
		assign(first, last);
	}

	template<typename T>
	template<typename ilT>
	deque<T>::deque(const std::initializer_list<ilT>& ilist)
		: m_data(nullptr), m_size(0), m_cap(0), m_margin(0)
	{
		assign(ilist);
	}

	template<typename T>
	deque<T>::~deque()
	{
		destroy(); delete[] m_data;
	}

	template<typename T>
	typename deque<T>::deque& deque<T>::operator=(const deque& other)
	{
		if (this != &other)
		{
			clear();
			assign(other.begin(), other.end());
		}
		return *this;
	}

	template<typename T>
	typename deque<T>::deque& deque<T>::operator=(deque&& other) noexcept
	{
		if (this != &other)
		{
			clear();
			m_data = other.m_data;
			m_size = other.m_size;
			m_cap = other.m_cap;
			m_margin = other.m_margin;
			other.m_data = nullptr;
			other.m_size = 0;
			other.m_cap = 0;
			other.m_margin = 0;
		}
		return *this;
	}

	template<typename T>
	template<typename ilT>
	typename deque<T>::deque& deque<T>::operator=(const std::initializer_list<ilT>& ilist)
	{
		clear();
		assign(ilist);
		return *this;
	}

	template<typename T>
	bool deque<T>::operator==(const deque& other) const
	{
		if (m_size != other.m_size)
		{
			return false;
		}
		else
		{
			for (size_t i = 0; i < m_size; ++i)
			{
				if ((*this)[i] != other[i])
				{
					return false;
				}
			}
			return true;
		}
	}

	template<typename T>
	typename deque<T>::value_type& deque<T>::push_back(const typename deque<T>::value_type& toAdd)
	{
		if (m_size >= m_cap - m_margin)
		{
			realloc(m_cap * 2);
		}
		new (m_data + m_margin + m_size) value_type(toAdd);
		return (*this)[m_size++];
	}

	template<typename T>
	typename deque<T>::value_type& deque<T>::push_front(const typename deque<T>::value_type& toAdd)
	{
		//FIXME: idk, fix this
		if (m_margin == 0)
		{
			//std::cout << "realloc\n";
			realloc(m_cap * 2);
		}
		++m_size;
		new (m_data + --m_margin) value_type(toAdd);
		return *(m_data + m_margin);
	}

	template<typename T>
	template<typename... Args>
	typename deque<T>::value_type& deque<T>::emplace_back(Args&&... args)
	{
		if (m_size >= m_cap - m_margin)
		{
			realloc(m_cap * 2);
		}
		new (m_data + m_margin + m_size) value_type(std::forward<Args>(args)...);
		return (*this)[m_size++];
	}
	template<typename T>
	template<typename... Args>
	typename deque<T>::value_type& deque<T>::emplace_front(Args&&... args)
	{
		if (m_margin == 0)
		{
			realloc(m_cap * 2);
		}
		++m_size;
		new (m_data + --m_margin) value_type(std::forward<Args>(args)...);
		return *(m_data + m_margin);
	}

	template<typename T>
	typename deque<T>::value_type& deque<T>::insert(iterator position, const value_type& value)
	{
		if (position >= begin() && position <= end())
		{
			size_t safePosition = position - begin();

			// back							//front
			if ((m_size >= m_cap - m_margin) || m_margin == 0)
			{
				realloc(m_cap * 2);
			}
			++m_size;
			for (auto it = end() - 2; it >= begin() + safePosition; --it)
			{
				*(it + 1) = std::move(*it);
			}
			*(begin() + safePosition) = value;
			return *(begin() + safePosition);
		}
		throw std::out_of_range("bad iterator");
	}

	template<typename T>
	template<typename... Args>
	typename deque<T>::value_type& deque<T>::emplace(iterator position, Args&&... args)
	{
		if (position >= begin() && position <= end())
		{
			size_t safePosition = position - begin();

			// back							//front
			if ((m_size >= m_cap - m_margin) || m_margin == 0)
			{
				realloc(m_cap * 2);
			}
			++m_size;
			for (auto it = end() - 2; it >= begin() + safePosition; --it)
			{
				*(it + 1) = std::move(*it);
			}
			new (begin().ptr() + safePosition) value_type(std::forward<Args>(args)...);
			return *(begin() + safePosition);
		}
		throw std::out_of_range("bad iterator");
	}

	template<typename T>
	void deque<T>::assign(size_t count, const value_type& objectToFill)
	{
		clear();
		realloc_exactly(count);
		while (count > 0)
		{
			push_back(objectToFill);
			--count;
		}
	}
	template<typename T>
	template<typename iterType>
	typename std::enable_if<is_iterator<iterType>::value, void>::type deque<T>::assign(iterType first, iterType last)
	{
		clear();
		for (first; first != last; ++first)
		{
			push_back(*first);
		}
	}
	template<typename T>
	template<typename ilT>
	void deque<T>::assign(const std::initializer_list<ilT>& ilist)
	{
		clear();
		realloc_exactly(ilist.size());
		for (const auto& element : ilist)
		{
			push_back(element);
		}
	}

	template<typename T>
	void deque<T>::pop_back()
	{
		if (m_size > 0)
		{
			(m_data + m_margin + --m_size)->~value_type();
			--m_size;
		}
	}

	template<typename T>
	void deque<T>::pop_front()
	{
		if (m_size > 0)
		{
			(m_data + m_margin)->~value_type();
			--m_size;
			++m_margin;
		}
	}

	template<typename T>
	void deque<T>::erase(iterator position)
	{
		if (begin() <= position && position < end())
		{
			position.ptr()->~value_type();
			for (position; position != end() - 1; ++position)
			{
				*position = *(position + 1);
			}
			--m_size;
		}
	}

	template<typename T>
	void deque<T>::clear()
	{
		if (m_data != nullptr)
		{
			destroy();
			::operator delete[](m_data);
			m_data = nullptr;
			m_size = 0;
			m_margin = 0;
			m_cap = 0;
		}
	}

	template<typename T>
	void deque<T>::reserve(size_t newCap)
	{
		if (newCap > m_cap)
		{
			newCap = (newCap % 2 == 0) ? newCap : newCap + 1;
			realloc(newCap);
		}
	}

	template<typename T>
	void deque<T>::swap(deque& other)
	{
		kq::swap(m_data, other.m_data);
		kq::swap(m_size, other.m_size);
		kq::swap(m_cap, other.m_cap);
		kq::swap(m_margin, other.m_margin);
	}

	template<typename T>
	typename deque<T>::value_type& deque<T>::front()
	{
		if (m_size == 0)
		{
			throw std::out_of_range("front(), called on empty deque");
		}
		return *(m_data + m_margin);
	}

	template<typename T>
	const typename deque<T>::value_type& deque<T>::front() const
	{
		if (m_size == 0)
		{
			throw std::out_of_range("front(), called on empty deque");
		}
		return *(m_data + m_margin);
	}

	template<typename T>
	typename deque<T>::value_type& deque<T>::back()
	{
		if (m_size == 0)
		{
			throw std::out_of_range("back(), called on empty deque");
		}
		return *(m_data + m_margin + m_size - 1);
	}

	template<typename T>
	const typename deque<T>::value_type& deque<T>::back() const
	{
		if (m_size == 0)
		{
			throw std::out_of_range("back(), called on empty deque");
		}
		return *(m_data + m_margin + m_size - 1);
	}

	template<typename T>
	typename deque<T>::value_type& deque<T>::at(size_t index)
	{
		// m_margin + index > m_cap
		if (index >= m_size || m_size == 0)
		{
			throw std::out_of_range("at(), trying to acces elements out of range on deque");
		}
		return *(m_data + m_margin + index);
	}

	template<typename T>
	const typename deque<T>::value_type& deque<T>::at(size_t index) const
	{
		// m_margin + index > m_cap
		if (index >= m_size || m_size == 0)
		{
			throw std::out_of_range("at(), trying to acces elements out of range on deque");
		}
		return *(m_data + m_margin + index);
	}

	template<typename T>
	void deque<T>::realloc(size_t newCap)
	{
		//std::cout << "realloc";
		if (newCap < 10)
		{
			newCap = 10;
		}
		pointer newBlock = (pointer)::operator new[](sizeof(value_type)* newCap);

		size_t newMargin = newCap / 2 - m_size / 2;

		if (newBlock != nullptr && m_data != nullptr)
		{
			for (size_t i = 0; i < m_size; ++i)
			{
				new (newBlock + newMargin + i) value_type(std::move((*this)[i]));
			}
		}

		destroy();
		::operator delete[](m_data);
		m_data = newBlock;
		m_cap = newCap;
		m_margin = newMargin;

		//std::cout << "Details from realloc: cap = " << m_cap << " margin = " << m_margin << " size = " << m_size << "\n";
		//std::cout << "newMargin = " << newMargin << " equalSides = " << equalSides << '\n's
	}

	template<typename T>
	void deque<T>::realloc_exactly(size_t newCap)
	{
		if (newCap % 2 == 1)
		{
			++newCap;
		}
		pointer newBlock = (pointer)::operator new[](sizeof(value_type)* newCap);

		if (m_data != nullptr && newBlock != nullptr)
		{
			for (size_t i = 0; i < m_size; ++i)
			{
				new(newBlock + i) value_type(std::move(*this)[i]);
			}
		}
		destroy();
		delete[] m_data;
		m_data = newBlock;
		m_cap = newCap;
		m_margin = 0;
	}

	template<typename T>
	void deque<T>::destroy()
	{
		if (m_data != nullptr)
		{
			for (size_t i = 0; i < m_size; i++)
			{
				(m_data + m_margin + i)->~value_type();
			}
		}
	}
}



#endif