#ifndef KQLINKEDLIST_
#define KQLINKEDLIST_

#include "other.h"

namespace kq 
{
	template<typename T>
	struct ll_element;

	template<typename T, bool constant>
	struct ll_iterator
	{
	public:
		using value_type = T;
		using pointer = value_type*;
		using difference_type = size_t;
		using reference = typename std::conditional<constant, const value_type&, value_type&>::type;
		using element = ll_element<value_type>;
		using iterator_category = std::bidirectional_iterator_tag;

		ll_iterator() : m_ptr() {}
		ll_iterator(const ll_iterator& other) : m_ptr(other.m_ptr) {}
		ll_iterator(ll_iterator&& other) noexcept : m_ptr(other.m_ptr) { other.m_ptr = nullptr; }
		ll_iterator(element* llelement) : m_ptr(llelement) {}

		ll_iterator& operator=(const ll_iterator& other);
		ll_iterator& operator=(ll_iterator&& other) noexcept;

		bool operator==(const ll_iterator& other) const { return m_ptr == other.m_ptr; }
		bool operator!=(const ll_iterator& other) const { return m_ptr != other.m_ptr; }

		ll_iterator& operator++() { m_ptr = m_ptr->next; return *this; }
		ll_iterator operator++(int) { element Tmp = *this; m_ptr = m_ptr->next; return Tmp; }
		ll_iterator& operator--() { m_ptr = m_ptr->prev; return *this; }
		ll_iterator operator--(int) { element Tmp = *this;  m_ptr = m_ptr->prev;  return Tmp; }

		element* ptr() const { return m_ptr; }
		element* next() const { return m_ptr->next; }
		element* prev() const { return m_ptr->prev; }

		reference operator*() const { return m_ptr->value; }
		pointer operator->() const { return &(m_ptr->value); }

	private:
		element* m_ptr;
	};

	template<typename T, bool constant>
	ll_iterator<T, constant>& ll_iterator<T, constant>::operator=(const ll_iterator& other)
	{
		if (this != &other)
		{
			m_ptr = other.m_ptr;
		}
		return *this;
	}

	template<typename T, bool constant>
	ll_iterator<T, constant>& ll_iterator<T, constant>::operator=(ll_iterator&& other) noexcept 
	{
		if (this != &other)
		{
			m_ptr = other.m_ptr;
			other.m_ptr = nullptr;
		}
		return *this; 
	}

	template<typename T, bool constant>
	struct ll_reverse_iterator
	{
	public:
		using value_type = T;
		using pointer = value_type*;
		using reference = typename std::conditional<constant, const value_type&, value_type&>::type;
		using difference_type = size_t;
		using element = ll_element<value_type>;
		using iterator_category = std::bidirectional_iterator_tag;

		ll_reverse_iterator() : m_ptr() {}
		ll_reverse_iterator(const ll_reverse_iterator& other) : m_ptr(other.m_ptr) {}
		ll_reverse_iterator(ll_reverse_iterator&& other) noexcept : m_ptr(other.m_ptr) { other.m_ptr = nullptr; }
		ll_reverse_iterator(element* llelement) : m_ptr(llelement) {}

		ll_reverse_iterator& operator=(const ll_reverse_iterator& other);
		ll_reverse_iterator& operator=(ll_reverse_iterator&& other) noexcept;

		bool operator==(const ll_reverse_iterator& other) const { return m_ptr == other.m_ptr; }
		bool operator!=(const ll_reverse_iterator& other) const { return m_ptr != other.m_ptr; }

		ll_reverse_iterator& operator++() { m_ptr = m_ptr->prev; return *this; }
		ll_reverse_iterator operator++(int) { element Tmp = *this; m_ptr = m_ptr->prev; return Tmp; }
		ll_reverse_iterator& operator--() { m_ptr = m_ptr->next; return *this; }
		ll_reverse_iterator operator--(int) { element Tmp = *this; m_ptr = m_ptr->next; return Tmp; }

		element* ptr() const { return m_ptr; }
		element* next() const { return m_ptr->next; }
		element* prev() const { return m_ptr->prev; }

		reference operator*() const { return m_ptr->value; }
		pointer operator->() const	{ return &(m_ptr->value); }

	private:
		element* m_ptr;
	};

	template<typename T, bool constant>
	ll_reverse_iterator<T, constant>& ll_reverse_iterator<T, constant>::operator=(const ll_reverse_iterator& other)
	{
		if (this != &other)
		{
			m_ptr = other.m_ptr;
		}
		return *this;
	}

	template<typename T, bool constant>
	ll_reverse_iterator<T, constant>& ll_reverse_iterator<T, constant>::operator=(ll_reverse_iterator&& other) noexcept
	{
		if (this != &other)
		{
			m_ptr = other.m_ptr;
			other.m_ptr = nullptr;
		}
		return *this;
	}
	
	template<typename T>
	struct ll_element
	{
	public:
		using value_type = T;
		using pointer = value_type*;
		using reference = value_type&;

		ll_element() : value(), next(nullptr), prev(nullptr) {}
		ll_element(const ll_element& other) : value(other.value), next(other.next), prev(other.prev) {}
		ll_element(ll_element&& other) noexcept : value(std::move(other.value)), next(other.next), prev(other.prev) {}
		ll_element(const value_type& elementToAdd) : value(elementToAdd), next(nullptr), prev(nullptr) {}
		template<typename... Args>
		ll_element(Args&&... args) : value(std::forward<Args>(args)...), next(nullptr), prev(nullptr) {}
		~ll_element() {}

		ll_element& operator=(const ll_element& other) { value = other.value; next = other.next; prev = other.prev; return *this; }
		ll_element& operator=(ll_element&& other) noexcept { value = std::move(other.value); next = other.next; prev = other.prev; return *this; }

		value_type value;
		ll_element* next;
		ll_element* prev;
	};

	template<typename T>
	struct list
	{
	public:
		using value_type = T;
		using pointer = value_type*;
		using reference = value_type&;
		using element = ll_element<value_type>;
		using iterator = ll_iterator<value_type, false>;
		using const_iterator = ll_iterator<value_type, true>;
		using reverse_iterator = ll_reverse_iterator<value_type, false>;
		using const_reverse_iterator = ll_reverse_iterator<value_type, true>;

		list();
		list(const list&);
		list(list&&) noexcept;
		list(size_t);
		list(size_t, const value_type&);
		template<typename iterType, typename std::enable_if<is_iterator<iterType>::value, int>::type = 0>
		list(iterType, iterType);
		template<typename ilT>
		list(const std::initializer_list<ilT>&);
		~list();

		list& operator=(const list&);
		list& operator=(list&&) noexcept;

		template<typename ilT>
		list& operator=(const std::initializer_list<ilT>&);

		bool operator==(const list&) const;
		bool operator!=(const list& other) const { return !(*this == other); }

		size_t size() const { return m_size; }

		iterator begin() { return m_data->next; }
		iterator end() { return m_data; }
		const_iterator begin() const { return m_data->next; }
		const_iterator end() const { return m_data; }
		const_iterator cbegin() const { return m_data->next; }
		const_iterator cend() const { return m_data; }
		reverse_iterator rbegin() { return m_data->prev; }
		reverse_iterator rend() { return m_data; }
		const_reverse_iterator rbegin() const { return m_data->prev; }
		const_reverse_iterator rend() const { return m_data; }
		const_reverse_iterator crbegin() const { return m_data->prev; }
		const_reverse_iterator crend() const { return m_data; }

		
		bool empty() const { return m_size == 0; }

		value_type& push_back(const value_type&);
		value_type& push_front(const value_type&);
		template<typename... Args>
		value_type& emplace_back(Args&&... args);
		template<typename... Args>
		value_type& emplace_front(Args&&... args);
		value_type& insert(iterator, const value_type&);
		template<typename... Args>
		value_type& emplace(iterator, Args&&... args);

		void assign(size_t, const value_type&);
		template<typename iterType>
		typename std::enable_if<is_iterator<iterType>::value, void>::type assign(iterType, iterType);
		template<typename ilT>
		void assign(const std::initializer_list<ilT>&);

		void pop_back();
		void pop_front();
		void clear();

		void resize(size_t);
		void resize(size_t, const value_type&);

		void erase(iterator);
		void swap(list&);

		value_type& front();
		const value_type& front() const;
		value_type& back();
		const value_type& back() const;
	private:
		element* m_data;
		size_t m_size;
	};

	template<typename T>
	list<T>::list() 
		: m_data((element*)::operator new(sizeof(element))), m_size(0) 
	{ 
		m_data->prev = m_data;
		m_data->next = m_data; 
	}

	template<typename T>
	list<T>::list(const list& other) 
		: m_data((element*)::operator new(sizeof(element))), m_size(0)
	{
		m_data->prev = m_data;
		m_data->next = m_data;
		for (auto& element : other)
		{
			push_back(element);
		}
	}

	template<typename T>
	list<T>::list(list&& other) noexcept 
		: m_data(other.m_data), m_size(other.m_size)
	{
		other.m_data = (element*)::operator new(sizeof(element));
		other.m_data->prev = m_data;
		other.m_data->next = m_data;
		other.m_size = 0;
	}

	template<typename T>
	list<T>::list(size_t size)
		: m_data((element*)::operator new(sizeof(element))), m_size(0)
	{
		m_data->prev = m_data;
		m_data->next = m_data;
		while (size > 0)
		{
			push_back(value_type());
			--size;
		}
	}

	template<typename T>
	list<T>::list(size_t size, const value_type& objectToFill)
		: m_data((element*)::operator new(sizeof(element))), m_size(0)
	{
		m_data->next = m_data;
		m_data->prev = m_data;
		assign(size, objectToFill);
	}

	template<typename T>
	template<typename iterType, typename std::enable_if<is_iterator<iterType>::value, int>::type>
	list<T>::list(iterType first, iterType last)
		: m_data((element*)::operator new(sizeof(element))), m_size(0)
	{
		m_data->next = m_data;
		m_data->prev = m_data;
		assign(first, last);
	}

	template<typename T>
	template<typename ilT>
	list<T>::list(const std::initializer_list<ilT>& ilist)
		: m_data((element*)::operator new(sizeof(element))), m_size(0)
	{
		m_data->next = m_data;
		m_data->prev = m_data;
		assign(ilist);
	}

	template<typename T>
	list<T>::~list()
	{
		clear();
		::operator delete(m_data);
	}

	template<typename T>
	typename list<T>::list& list<T>::operator=(const list& other)
	{
		if (this != &other)
		{
			clear();
			for (const_iterator it = other.cbegin(); it != other.cend(); ++it)
			{
				push_back(*it);
			}
		}
		return *this;
	}

	template<typename T>
	typename list<T>::list& list<T>::operator=(list && other) noexcept
	{
		if (this != &other)
		{
			clear();
			delete m_data;
			m_data = other.m_data;
			m_size = other.m_size;
			other.m_data = (element*)::operator new (sizeof(element));
			other.m_data->next = other.m_data;
			other.m_data->prev = other.m_data;
			other.m_size = 0;
		}
		return *this;
	}

	template<typename T>
	template<typename ilT>
	typename list<T>::list& list<T>::operator=(const std::initializer_list<ilT>& ilist)
	{
		clear();
		assign(ilist);
		return *this;
	}

	template<typename T>
	bool list<T>::operator==(const list& other) const
	{
		if (m_size != other.m_size)
		{
			return false;
		}
		else
		{
			element* A = m_data->next;
			element* B = other.m_data->next;
			for (size_t i = 0; i < m_size; ++i)
			{
				if (A->value != B->value)
				{
					return false;
				}
				A = A->next;
				B = B->next;
			}
			return true;
		}
	}

	template<typename T>
	typename list<T>::value_type& list<T>::push_back(const typename list<T>::value_type& elementToAdd)
	{
		if (m_data == 0)
		{
			m_data->next = new element(elementToAdd); 
			m_data->prev = m_data->next;
			m_data->next->prev = m_data;
			m_data->next->next = m_data;
			++m_size;
			return m_data->next->value;
		}
		else
		{
			element* keep = m_data->prev;
			keep->next = new element(elementToAdd);
			keep->next->next = m_data;
			m_data->prev = keep->next;
			keep->next->prev = keep;
			++m_size;
			return keep->next->value;
		}
	}

	template<typename T>
	typename list<T>::value_type& list<T>::push_front(const typename list<T>::value_type& elementToAdd)
	{
		if (m_size == 0)
		{
			m_data->next = new element(elementToAdd);
			m_data->prev = m_data->next;
			m_data->next->prev = m_data;
			m_data->next->next = m_data;
			++m_size;
			return m_data->next->value;
		}
		else
		{
			element* keep = m_data->next;
			keep->prev = new element(elementToAdd);
			m_data->next = keep->prev;
			keep->prev->next = keep;
			keep->prev->prev = m_data;
			++m_size;
			return keep->prev->value;
		}
	}

	template<typename T>
	template<typename... Args>
	typename list<T>::value_type& list<T>::emplace_back(Args&&... args)
	{
		if (m_data == 0)
		{
			m_data->next = new element(std::forward<Args>(args)...);
			m_data->prev = m_data->next;
			m_data->next->prev = m_data;
			m_data->next->next = m_data;
			++m_size;
			return m_data->next->value;
		}
		else
		{
			element* keep = m_data->prev;
			keep->next = new element(std::forward<Args>(args)...);
			keep->next->next = m_data;
			m_data->prev = keep->next;
			keep->next->prev = keep;
			++m_size;
			return keep->next->value;
		}
	}

	template<typename T>
	template<typename... Args>
	typename list<T>::value_type& list<T>::emplace_front(Args&&... args)
	{
		if (m_size == 0)
		{
			m_data->next = new element(std::forward<Args>(args)...);
			m_data->prev = m_data->next;
			m_data->next->prev = m_data;
			m_data->next->next = m_data;
			++m_size;
			return m_data->next->value;
		}
		else
		{
			element* keep = m_data->next;
			keep->prev = new element(std::forward<Args>(args)...);
			m_data->next = keep->prev;
			keep->prev->next = keep;
			keep->prev->prev = m_data;
			++m_size;
			return keep->prev->value;
		}
	}

	template<typename T>
	typename list<T>::value_type& list<T>::insert(iterator position, const value_type& elementToAdd)
	{
		if (position.ptr() != m_data)
		{
			if (position.next() == m_data)
			{
				return push_back(elementToAdd);
			}
			else if (position.prev() == m_data)
			{
				return push_front(elementToAdd);
			}
			else
			{
				element* newElement = new element;
				newElement->value = elementToAdd;
				newElement->next = position.ptr();
				newElement->prev = position.prev();
				position.prev()->next = newElement;
				++m_size;
			}
		}
	}

	template<typename T>
	template<typename... Args>
	typename list<T>::value_type& list<T>::emplace(iterator position, Args&&... args)
	{
		if (position.ptr() != m_data)
		{
			if (position.next() == m_data)
			{
				return emplace_back(std::forward<Args>(args)...);
			}
			else if (position.prev() == m_data)
			{
				return emplace_front(std::forward<Args>(args)...);
			}
			else
			{
				element* newElement = new element(std::forward<Args>(args)...);
				newElement->next = position.ptr();
				newElement->prev = position.prev();
				position.prev()->next = newElement;
				++m_size;
			}
		}
	}

	template<typename T>
	void list<T>::assign(size_t count, const value_type& objectToFill)
	{
		clear();
		while (count > 0)
		{
			push_back(objectToFill);
			--count;
		}
	}

	template<typename T>
	template<typename iterType>
	typename std::enable_if<is_iterator<iterType>::value, void>::type list<T>::assign(iterType first, iterType last)
	{
		clear();
		for (; first != last; ++first)
		{
			push_back(*first);
		}
	}

	template<typename T>
	template<typename ilT>
	void list<T>::assign(const std::initializer_list<ilT>& ilist)
	{
		clear();
		for (typename std::initializer_list<ilT>::iterator it = ilist.begin(); it != ilist.end(); ++it)
		{
			push_back(*it);
		}
	}

	template<typename T>
	void list<T>::pop_back()
	{
		if (m_size > 1)
		{
			element* remove = m_data->prev;
			m_data->prev->prev->next = m_data;
			m_data->prev = m_data->prev->prev;
			delete remove;
			--m_size;
		}
		else if (m_size == 1)
		{
			delete m_data->next;
			m_data->next = m_data;
			m_data->prev = m_data;
			m_size = 0;
		}
		else {}
	}

	template<typename T>
	void list<T>::pop_front()
	{
		if (m_size > 1)
		{
			element* remove = m_data->next;
			m_data->next->next->prev = m_data;
			m_data->next = m_data->next->next;
			delete remove;
			--m_size;
		}
		else if (m_size == 1)
		{
			delete m_data->next;
			m_data->next = m_data;
			m_data->prev = m_data;
			m_size = 0;
		}
		else {}
	}

	template<typename T>
	void list<T>::clear()
	{
		
		if (m_size > 1)
		{
			element* current = m_data->next;
			while (current != m_data)
			{
				element* next = current->next;
				delete current;
				current = next;
			}
			m_size = 0;
			m_data->next = m_data;
			m_data->prev = m_data;
		}
		else if (m_size == 1)
		{
			delete m_data->next;
			m_data->next = m_data;
			m_data->prev = m_data;
		}
	}

	template<typename T>
	void list<T>::resize(size_t count)
	{
		if (count < m_size)
		{
			count = m_size - count;
			while (count > 0)
			{
				pop_back();
				--count;
			}
		}
		else if (count > m_size)
		{
			count -= m_size;
			while (count > 0)
			{
				emplace_back();
				--count;
			}
		}
	}

	template<typename T>
	void list<T>::resize(size_t count, const value_type& value)
	{
		if (count < m_size)
		{
			count = m_size - count;
			while (count > 0)
			{
				pop_back();
				--count;
			}
		}
		else if (count > m_size)
		{
			count -= m_size;
			while (count > 0)
			{
				push_back(value);
				--count;
			}
		}
	}

	template<typename T>
	void list<T>::erase(iterator position)
	{
		if (position.ptr() != m_data)
		{
			if (position.next() == m_data)
			{
				pop_back();
			}
			else if (position.prev() == m_data)
			{
				pop_front();
			}
			else
			{
				position.prev()->next = position.next();
				position.next()->prev = position.prev();
				//position->~T(); Probably called by the delete below
				delete position.ptr();
				--m_size;
			}
		}
		
	}

	template<typename T>
	void list<T>::swap(list& other)
	{
		kq::swap(m_data, other.m_data);
		kq::swap(m_size, other.m_size);
	}

	template<typename T>
	typename list<T>::value_type& list<T>::front() 
	{ 
		if (m_size == 0)
		{
			throw std::out_of_range("front(), called on empty list");
		}	
		return m_data->next->value;
	}

	template<typename T>
	const typename list<T>::value_type& list<T>::front() const 
	{
		if (m_size == 0)
		{
			throw std::out_of_range("front(), called on empty list");
		}
		return m_data->next->value;
	}

	template<typename T>
	typename list<T>::value_type& list<T>::back() 
	{
		if (m_size == 0)
		{
			throw std::out_of_range("back(), called on empty list");
		}
		return m_data->prev->value;
	}

	template<typename T>
	const typename list<T>::value_type& list<T>::back() const 
	{
		if (m_size == 0)
		{
			throw std::out_of_range("back(), called on empty list");
		}
		return m_data->prev->value;
	}

}

#endif