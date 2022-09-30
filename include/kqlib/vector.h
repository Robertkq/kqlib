#ifndef KQVECTOR_
#define KQVECTOR_

//#include <iostream>

#include "other.h"

namespace kq
{
	template<typename T, bool constant>
	struct v_iterator
	{
	public:
		using value_type = T;
		using pointer = value_type*;
		using reference = typename std::conditional<constant, const value_type&, value_type&>::type;
		using difference_type = size_t;
		using iterator_category = std::random_access_iterator_tag;
		
		v_iterator() : m_ptr(nullptr) {}
		v_iterator(const v_iterator& other) : m_ptr(other.m_ptr) {}
		v_iterator(v_iterator&& other) noexcept : m_ptr(other.m_ptr) { other.m_ptr = nullptr; }
		v_iterator(pointer ptr) : m_ptr(ptr) {}

		v_iterator& operator=(const v_iterator& other);
		v_iterator& operator=(v_iterator&& other) noexcept;

		bool operator==(const v_iterator& rhs) const { return m_ptr == rhs.m_ptr; }
#if !_HAS_CXX_20_KQ
		bool operator!=(const v_iterator& rhs) const { return m_ptr != rhs.m_ptr; }
		bool operator<(const v_iterator& rhs) const { return m_ptr < rhs.m_ptr; }
		bool operator>(const v_iterator& rhs) const { return m_ptr > rhs.m_ptr; }
		bool operator<=(const v_iterator& rhs) const { return m_ptr <= rhs.m_ptr; }
		bool operator>=(const v_iterator& rhs) const { return m_ptr >= rhs.m_ptr; }
#elif
		bool operator<=>(const v_iterator& rhs) const;
#endif

		v_iterator operator++(int) { pointer Tmp = m_ptr; ++m_ptr; return Tmp; }
		v_iterator& operator++() { ++m_ptr; return *this; }
		v_iterator operator--(int) { pointer Tmp = m_ptr; --m_ptr; return Tmp; }
		v_iterator& operator--() { --m_ptr; return *this; }
		v_iterator operator+(int rhs) const { return m_ptr + rhs; }
		v_iterator operator-(int rhs) const { return m_ptr - rhs; }
		v_iterator& operator+=(int rhs) { m_ptr += rhs; return *this; }
		v_iterator& operator-=(int rhs) { m_ptr -= rhs; return *this; }
		friend v_iterator operator+(difference_type lhs, const v_iterator& rhs) { return rhs.m_ptr + lhs; }
		difference_type operator-(const v_iterator& rhs) const { return abs(m_ptr - rhs.m_ptr); }

		pointer ptr() const { return m_ptr; }

		reference operator*() const { return *m_ptr; }
		pointer operator->() const { return m_ptr; }

	private:
		pointer m_ptr;
	};

	template<typename T, bool constant>
	typename v_iterator<T, constant>& v_iterator<T, constant>::operator=(const v_iterator& other)
	{
		if (this != &other)
		{
			m_ptr = other.m_ptr;
		}
		return *this;
	}

	template<typename T, bool constant>
	typename v_iterator<T, constant>& v_iterator<T, constant>::operator=(v_iterator&& other) noexcept
	{ 
		if (this != &other)
		{
			m_ptr = other.m_ptr;
			other.m_ptr = nullptr;
		}
		return *this; 
	}

#if _HAS_CXX_20_KQ
	template<typename T, bool constant>
	int v_iterator<T, constant>::operator<=>(const v_iterator& rhs) const
	{
		if (m_ptr == rhs.m_ptr)
			return 0;
		if (m_ptr < rhs.m_ptr)
			return -1;
		return 1;
	}
#endif

	template<typename T, bool constant>
	struct v_reverse_iterator
	{
	public:
		using value_type = T;
		using pointer = value_type*;
		using reference = typename std::conditional<constant, const value_type&, value_type&>::type;
		using difference_type = size_t;
		using iterator_category = std::random_access_iterator_tag;

		v_reverse_iterator() : m_ptr(nullptr) {}
		v_reverse_iterator(const v_reverse_iterator& other) : m_ptr(other.m_ptr) {}
		v_reverse_iterator(v_reverse_iterator&& other) noexcept : m_ptr(other.m_ptr) { other.m_ptr = nullptr; }
		v_reverse_iterator(pointer ptr) : m_ptr(ptr) {}

		v_reverse_iterator& operator=(const v_reverse_iterator& other);
		v_reverse_iterator& operator=(v_reverse_iterator&& other) noexcept;

		bool operator==(const v_reverse_iterator& other) const { return m_ptr == other.m_ptr; }
#if !_HAS_CXX_20_KQ
		bool operator!=(const v_reverse_iterator& other) const { return m_ptr != other.m_ptr; }
		bool operator<(const v_reverse_iterator& rhs) const { return m_ptr > rhs.m_ptr; }
		bool operator>(const v_reverse_iterator& rhs) const { return m_ptr < m_ptr; }
		bool operator<=(const v_reverse_iterator& rhs) const { return m_ptr >= rhs.m_ptr; }
		bool operator>=(const v_reverse_iterator& rhs) const { return m_ptr <= rhs.m_ptr; }
#elif 
		int operator<=>(const v_reverse_iterator& rhs) const;
#endif

		v_reverse_iterator operator++(int) { pointer Tmp = m_ptr; --m_ptr; return Tmp; }
		v_reverse_iterator& operator++() { --m_ptr; return *this; }
		v_reverse_iterator operator--(int) { pointer Tmp = m_ptr; ++m_ptr; return Tmp; }
		v_reverse_iterator& operator--() { ++m_ptr; return *this; }
		v_reverse_iterator operator+(int rhs) const { return m_ptr - rhs; }
		v_reverse_iterator operator-(int rhs) const { return m_ptr + rhs; }
		v_reverse_iterator& operator+=(int rhs)	{ m_ptr -= rhs; return *this; }
		v_reverse_iterator& operator-=(int rhs)	{ m_ptr += rhs; return *this; }
		friend v_reverse_iterator operator+(int lhs, const v_reverse_iterator& rhs) { return rhs.m_ptr - lhs; }
		difference_type operator-(const v_reverse_iterator& rhs)	const { return abs(m_ptr - rhs.m_ptr); }

		pointer ptr() const { return m_ptr; }

		reference operator*() const { return *m_ptr; }
		pointer operator->() const { return m_ptr; }

		

	private:
		pointer m_ptr;
	};

	template<typename T, bool constant>
	typename v_reverse_iterator<T, constant>& v_reverse_iterator<T, constant>::operator=(const v_reverse_iterator& other)
	{
		if (this != &other)
		{
			m_ptr = other.m_ptr;
		}
		return *this;
	}

	template<typename T, bool constant>
	typename v_reverse_iterator<T, constant>& v_reverse_iterator<T, constant>::operator=(v_reverse_iterator&& other) noexcept
	{
		if (this != &other)
		{
			m_ptr = other.m_ptr;
			other.m_ptr = nullptr;
		}
		return *this;
	}

#if _HAS_CXX_20_KQ
	template<typename T, bool constant>
	int v_reverse_iterator<T, constant>::<T, constant>::operator<=>(const v_reverse_iterator& rhs) const
	{
		if (m_ptr == rhs.m_ptr)
			return 0;
		if (m_ptr < rhs.m_ptr)
			return 1;
		return -1;
	}
#endif

	template<typename T>
	struct vector
	{
	public:
		
		using value_type = T;
		using reference = value_type&;
		using pointer = value_type*;
		using iterator = v_iterator<value_type, false>;
		using const_iterator = v_iterator<value_type, true>;
		using reverse_iterator = v_reverse_iterator<value_type, false>;
		using const_reverse_iterator = v_reverse_iterator<value_type, true>;

		vector();
		vector(const vector<T>& other);
		vector(vector<T>&& other) noexcept;
		vector(size_t);
		vector(size_t, const value_type&);
		template<typename iterType, typename std::enable_if<is_iterator<iterType>::value, int>::type = 0>
		vector(iterType, iterType);
		template<typename ilT>
		vector(const std::initializer_list<ilT>&);
		~vector();

		vector& operator=(const vector<T>& other);
		vector& operator=(vector<T>&& other) noexcept;

		template<typename ilT>
		vector& operator=(const std::initializer_list<ilT>& ilist);

		size_t size() const					{ return m_size; }
		size_t capacity() const				{ return m_cap; }
		pointer data()					{ return m_data; } 
		const pointer data() const		{ return m_data; }

		iterator begin()					{ return m_data; }
		iterator end()						{ return (m_data + m_size); }
		const_iterator begin() const		{ return m_data; }
		const_iterator end() const			{ return (m_data + m_size); }
		const_iterator cbegin() const		{ return m_data; }
		const_iterator cend() const			{ return (m_data + m_size); }
		reverse_iterator rbegin()			{ return (m_data + m_size - 1); }
		reverse_iterator rend()				{ return m_data - 1; }
		const_reverse_iterator rbegin() const	{ return (m_data + m_size - 1); }
		const_reverse_iterator rend() const		{ return (m_data - 1); }
		const_reverse_iterator crbegin() const	{ return (m_data + m_size - 1); }
		const_reverse_iterator crend() const	{ return m_data - 1; }

		bool empty()	const { return m_size == 0; }

		value_type& push_back(const value_type&);
		template<typename... Args>
		value_type& emplace_back(Args&&... args);
		value_type& insert(iterator, const value_type&);
		template<typename... Args>
		value_type& emplace(iterator position, Args&&... args);

		void assign(size_t, const value_type&);
		template<typename iterType>
		typename std::enable_if<is_iterator<iterType>::value, void>::type
			assign(iterType first, iterType last);
		template<typename ilT>
		void assign(const std::initializer_list<ilT>&);

		void pop_back();
		void erase(iterator);
		void clear();

		void resize(size_t);
		void resize(size_t, const value_type&);

		void shrink_to_fit()					{ if (m_size != m_cap) { realloc(m_size); } }
		void reserve(size_t capToReserve)	{ if (capToReserve > m_cap) { realloc(capToReserve); } }
		void swap(vector<T>&);

		value_type& front();
		const value_type& front() const;
		value_type& back();
		const value_type& back() const;

		value_type& operator[](size_t index) { return *(m_data + index); }
		const value_type& operator[](size_t index) const { return *(m_data + index); }
		value_type& at(size_t);
		const value_type& at(size_t) const;

	private:
		value_type* m_data;
		size_t m_size;
		size_t m_cap;

		void realloc(size_t);
		void destroy();

	};
	/*
	* @brief This is the default constructor for vector
	*/
	template<typename T>
	vector<T>::vector() : m_data(nullptr), m_size(0), m_cap(0) {}

	template<typename T>
	vector<T>::vector(const vector& other)
		: m_data((pointer)::operator new[](sizeof(value_type)* other.m_cap)), m_size(other.m_size), m_cap(other.m_cap)
	{
		for (size_t i = 0; i < m_size; ++i)
		{
			new (m_data + i) value_type(*(other.m_data + i));
		}
	}

	template<typename T>
	vector<T>::vector(vector&& other) noexcept
		: m_data(other.m_data), m_size(other.m_size), m_cap(other.m_cap)
	{
		other.m_data = nullptr;
		other.m_size = 0;
		other.m_cap = 0;
	}

	template<typename T>
	vector<T>::vector(size_t size) : m_data((pointer)::operator new[](sizeof(value_type)* size)), m_size(size), m_cap(size) 
	{
		for (size_t i = 0; i < m_size; ++i)
		{
			new (m_data + i) value_type();
		}
	}

	template<typename T>
	vector<T>::vector(size_t size, const value_type& objectToFill)
		: m_data(nullptr), m_size(0), m_cap(0)
	{
		assign(size, objectToFill);
	}

	template<typename T>
	template<typename iterType, typename std::enable_if<is_iterator<iterType>::value, int>::type>
	vector<T>::vector(iterType first, iterType last)
		: m_data(nullptr), m_size(0), m_cap(0)
	{
		assign(first, last);
	}

	template<typename T>
	template<typename ilT>
	vector<T>::vector(const std::initializer_list<ilT>& ilist)
		: m_data(nullptr), m_size(0), m_cap(0)
	{
		assign(ilist);
	}

	template<typename T>
	vector<T>::~vector()
	{
		destroy();
		::operator delete[](m_data);
	}

	template<typename T>
	typename vector<T>& vector<T>::operator=(const vector& other)
	{
		if (this != &other)
		{
			clear();
			m_data = (pointer)::operator new[](sizeof(value_type)* other.m_cap);
			m_size = other.m_size;
			m_cap = other.m_cap;
			for (size_t i = 0; i < m_size; i++)
			{
				new (m_data + i) value_type(*(other.m_data + i));
			}
		}
		return *this;
	}

	template<typename T>
	typename vector<T>& vector<T>::operator=(vector&& other) noexcept
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
	template<typename ilT>
	typename vector<T>& vector<T>::operator=(const std::initializer_list<ilT>& ilist)
	{
		clear();
		assign(ilist);
		return *this;
	}

	template<typename T>
	typename vector<T>::value_type& vector<T>::push_back(const value_type& value)
	{
		if (m_size >= m_cap)
		{
			realloc(m_cap + m_cap / 2);
		}
		new (m_data + m_size) value_type(value);
		m_size++;
		return *(m_data + m_size - 1);
	}

	template<typename T>
	template<typename... Args>
	typename vector<T>::value_type& vector<T>::emplace_back(Args&&... args)
	{
		if (m_size >= m_cap)
		{
			realloc(m_cap + m_cap / 2);
		}
		new (m_data + m_size) value_type(std::forward<Args>(args)...);
		m_size++;
		return *(m_data + m_size - 1);
	}

	template<typename T>
	typename vector<T>::value_type& vector<T>::insert(iterator position, const value_type& value)
	{
		// Note: iterator position will be invalid if we reallocate
		if (position >= begin() && position <= end())
		{
			size_t safePosition = abs(position - begin());
			if (m_size >= m_cap)
			{
				realloc(m_cap + m_cap / 2);
			}
			++m_size;
			for (iterator it = end() - 2; it >= begin() + safePosition; --it)
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
	typename vector<T>::value_type& vector<T>::emplace(iterator position, Args&&... args)
	{
		// Note: iterator position will be invalid if we reallocate
		if (position >= begin() && position <= end())
		{
			//value_type holder(std::forward<Args>(args)...);
			size_t safePosition = 0;
			safePosition = abs(position - begin());
			if (m_size >= m_cap)
			{
				realloc(m_cap + m_cap / 2);
			}
			++m_size;
			for (iterator it = end() - 2; it >= begin() + safePosition; --it)
			{
				*(it + 1) = std::move(*it);
			}
			new (begin().ptr() + safePosition) value_type(std::forward<Args>(args)...);
			return *(begin() + safePosition);
		}
		throw std::out_of_range("bad iterator");
	}
	template<typename T>
	void vector<T>::assign(size_t count, const value_type& objectToFill)
	{
		clear();
		reserve(count);
		while (count > 0)
		{
			push_back(objectToFill);
			--count;
		}
	}
	
	template<typename T>
	template<typename iterType>
	typename std::enable_if<is_iterator<iterType>::value, void>::type vector<T>::assign(iterType first, iterType last)
			
		{
			clear();
			if (first < last)
			{
				reserve(abs(last - first));
				for (; first != last; ++first)
				{
					push_back((*first));
				}
			}
		}

	template<typename T>
	template<typename ilT>
	void vector<T>::assign(const std::initializer_list<ilT>& ilist)
	{
		clear();
		reserve(ilist.size());
		for (typename std::initializer_list<ilT>::iterator it = ilist.begin();it != ilist.end(); ++it)
		{
			push_back(*it);
		}
	}

	template<typename T>
	void vector<T>::pop_back()
	{
		if (m_size > 0)
		{
			--m_size;
			(m_data + m_size)->~value_type();			
		}
	}

	template<typename T>
	void vector<T>::erase(iterator position)
	{
		if (m_size > 0)
		{
			if (position >= begin() && position < end())
			{
				(*position).~T();
				for (position; position != end() - 1; ++position)
				{
					*position = std::move(*(position + 1));
				}
				--m_size;
			}
		}
	}

	template<typename T>
	void vector<T>::clear()
	{
		
		if (m_data != nullptr)
		{
			destroy();
			::operator delete[](m_data);
			m_data = nullptr;
			m_size = 0;
			m_cap = 0;
		}
	}

	template<typename T>
	void vector<T>::resize(size_t count)
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
				emplace_back();
			}
		}
	}

	template<typename T>
	void vector<T>::resize(size_t count, const value_type& value)
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
	void vector<T>::swap(vector& other)
	{
		kq::swap(m_data, other.m_data);
		kq::swap(m_size, other.m_size);
		kq::swap(m_cap, other.m_cap);

	}

	template<typename T>
	typename vector<T>::value_type& vector<T>::front() 
	{
		if (m_size == 0)
		{
			throw std::out_of_range("front(), called on empty vector");
		}
		return *m_data;
	}

	template<typename T>
	const typename vector<T>::value_type& vector<T>::front() const 
	{
		if (m_size == 0)
		{
			throw std::out_of_range("front(), called on empty vector");
		}
		return *m_data;
	}

	template<typename T>
	typename vector<T>::value_type& vector<T>::back() 
	{
		if (m_size == 0)
		{
			throw std::out_of_range("back(), called on empty vector");
		}
		return *(m_data + m_size - 1);
	}

	template<typename T>
	const typename vector<T>::value_type& vector<T>::back() const 
	{
		if (m_size == 0)
		{
			throw std::out_of_range("back(), called on empty vector");
		}
		return *(m_data + m_size - 1);
	}

	template<typename T>
	typename vector<T>::value_type& vector<T>::at(size_t index)
	{
		if (index >= m_size || m_size == 0)
		{
			throw std::out_of_range("at(), trying to access elements out of range on vector");
		}
		return *(m_data + index);
	}

	template<typename T>
	const typename vector<T>::value_type& vector<T>::at(size_t index) const
	{
		if (index >= m_size || m_size == 0)
		{
			throw std::out_of_range("at(), trying to access elements out of range on vector");
		}
		return *(m_data + index);
	}

	template<typename T>
	void vector<T>::realloc(size_t newCap)
	{
		
		if (newCap < 2)
		{
			newCap = 2;
		}

		pointer newBlock = (pointer) ::operator new[](sizeof(value_type) * newCap);

		if (m_data != nullptr && newBlock != nullptr)
		{
			for (size_t i = 0; i < m_size; ++i)
			{
				new (newBlock + i) value_type(std::move(*(m_data + i)));
			}
		}

		destroy();
		::operator delete[](m_data);
		m_data = newBlock;
		m_cap = newCap;
	}

	template<typename T>
	void vector<T>::destroy()
	{
		if (m_data != nullptr)
		{
			for (size_t i = 0; i < m_size; ++i)
			{
				(m_data + i)->~value_type();
			}
		}

	}

}

#endif