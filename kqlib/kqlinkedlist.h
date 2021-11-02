#ifndef kqlinkedlist_
#define kqlinkedlist_

#include "kqother.h"

namespace kq 
{
	template<typename T>
	struct linkedlist_element;

	template<typename T, bool constant>
	struct ll_iterator
	{
	public:
		using value_type = T;
		using pointer_type = value_type*;
		using difference_type = int;
		using reference_type = typename std::conditional<constant, const value_type&, value_type&>::type;
		using element = linkedlist_element<value_type>;
		using iterator_category = std::bidirectional_iterator_tag;

		ll_iterator() : kq_ptr() {}
		ll_iterator(const ll_iterator& other) : kq_ptr(other.kq_ptr) {}
		ll_iterator(ll_iterator&& other) noexcept : kq_ptr(other.kq_ptr) { other.kq_ptr = nullptr; }
		ll_iterator(element* llelement) : kq_ptr(llelement) {}

		ll_iterator& operator=(const ll_iterator& other) { kq_ptr = other.kq_ptr; return *this; }
		ll_iterator& operator=(ll_iterator&& other) noexcept { kq_ptr = other.kq_ptr; other.kq_ptr = nullptr; return *this; }

		bool operator==(const ll_iterator& other) const { return kq_ptr == other.kq_ptr; }
		bool operator!=(const ll_iterator& other) const { return !(*this == other); }

		ll_iterator& operator++() { kq_ptr = kq_ptr->next; return *this; }
		ll_iterator operator++(int) { element Tmp = *this; kq_ptr = kq_ptr->next; return Tmp; }
		ll_iterator& operator--() { kq_ptr = kq_ptr->prev; return *this; }
		ll_iterator operator--(int) { element Tmp = *this;  kq_ptr = kq_ptr->prev;  return Tmp; }

		element* ptr() const { return kq_ptr; }
		element* next() const { return kq_ptr->next; }
		element* prev() const { return kq_ptr->prev; }

		reference_type operator*() const { return kq_ptr->value; }
		pointer_type operator->() const { return &(kq_ptr->value); }

	private:
		element* kq_ptr;
	};

	template<typename T, bool constant>
	struct ll_reverse_iterator
	{
	public:
		using value_type = T;
		using pointer_type = value_type*;
		using reference_type = typename std::conditional<constant, const value_type&, value_type&>::type;
		using difference_type = int;
		using element = linkedlist_element<value_type>;
		using iterator_category = std::bidirectional_iterator_tag;

		ll_reverse_iterator() : kq_ptr() {}
		ll_reverse_iterator(const ll_reverse_iterator& other) : kq_ptr(other.kq_ptr) {}
		ll_reverse_iterator(ll_reverse_iterator&& other) noexcept : kq_ptr(other.kq_ptr) { other.kq_ptr = nullptr; }
		ll_reverse_iterator(element* llelement) : kq_ptr(llelement) {}

		ll_reverse_iterator& operator=(const ll_reverse_iterator& other) { kq_ptr = other.kq_ptr; }
		ll_reverse_iterator& operator=(ll_reverse_iterator&& other) noexcept { kq_ptr = other.kq_ptr; other.kq_ptr = nullptr; }

		bool operator==(const ll_reverse_iterator& other) const { return kq_ptr == other.kq_ptr; }
		bool operator!=(const ll_reverse_iterator& other) const { return !(*this == other); }

		ll_reverse_iterator& operator++() { kq_ptr = kq_ptr->prev; return *this; }
		ll_reverse_iterator operator++(int) { element Tmp = *this; kq_ptr = kq_ptr->prev; return Tmp; }
		ll_reverse_iterator& operator--() { kq_ptr = kq_ptr->next; return *this; }
		ll_reverse_iterator operator--(int) { element Tmp = *this; kq_ptr = kq_ptr->next; return Tmp; }

		element* ptr() const { return kq_ptr; }
		element* next() const { return kq_ptr->next; }
		element* prev() const { return kq_ptr->prev; }

		reference_type operator*() const { return kq_ptr->value; }
		pointer_type operator->() const	{ return &(kq_ptr->value); }

	private:
		element* kq_ptr;
	};
	
	template<typename T>
	struct linkedlist_element
	{
	public:
		using value_type = T;
		using pointer_type = value_type*;
		using reference_type = value_type&;

		linkedlist_element() : value(), next(nullptr), prev(nullptr) {}
		linkedlist_element(const linkedlist_element& other) : value(other.value), next(other.next), prev(other.prev) {}
		linkedlist_element(linkedlist_element&& other) noexcept : value(std::move(other.value)), next(other.next), prev(other.prev) {}
		linkedlist_element(const value_type& elementToAdd) : value(elementToAdd), next(nullptr), prev(nullptr) {}
		template<typename... Args>
		linkedlist_element(Args&&... args) : value(std::forward<Args>(args)...), next(nullptr), prev(nullptr) {}
		~linkedlist_element() {}

		linkedlist_element& operator=(const linkedlist_element& other) { value = other.value; next = other.next; prev = other.prev; return *this; }
		linkedlist_element& operator=(linkedlist_element&& other) noexcept { value = std::move(other.value); next = other.next; prev = other.prev; return *this; }

		value_type value;
		linkedlist_element* next;
		linkedlist_element* prev;
	};

	template<typename T>
	struct list
	{
	public:
		using value_type = T;
		using pointer_type = value_type*;
		using reference_type = value_type&;
		using element = linkedlist_element<value_type>;
		using iterator = ll_iterator<value_type, false>;
		using const_iterator = ll_iterator<value_type, true>;
		using reverse_iterator = ll_reverse_iterator<value_type, false>;
		using const_reverse_iterator = ll_reverse_iterator<value_type, true>;

		list();
		list(const list&);
		list(list&&) noexcept;
		list(size_t);
		list(size_t, const value_type&);
		template<typename iterType, typename std::enable_if<is_iterator<iterType>, int>::type = 0>
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

		size_t size() const { return kq_size; }

		iterator begin() { return kq_data->next; }
		iterator end() { return kq_data; }
		const_iterator begin() const { return kq_data->next; }
		const_iterator end() const { return kq_data; }
		const_iterator cbegin() const { return kq_data->next; }
		const_iterator cend() const { return kq_data; }
		reverse_iterator rbegin() { return kq_data->prev; }
		reverse_iterator rend() { return kq_data; }
		const_reverse_iterator rbegin() const { return kq_data->prev; }
		const_reverse_iterator rend() const { return kq_data; }
		const_reverse_iterator crbegin() const { return kq_data->prev; }
		const_reverse_iterator crend() const { return kq_data; }

		
		bool is_empty() const { return kq_size == 0; }
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
		auto assign(iterType, iterType)->typename std::enable_if<is_iterator<iterType>, void>::type;
		template<typename ilT>
		void assign(const std::initializer_list<ilT>&);

		void pop_back();
		void pop_front();
		void clear();
		void erase(iterator);
		void swap(list&);

		value_type& front();
		const value_type& front() const;
		value_type& back();
		const value_type& back() const;
	private:
		element* kq_data;
		size_t kq_size;
	};

	template<typename T>
	list<T>::list() 
		: kq_data((element*)::operator new(sizeof(element))), kq_size(0) 
	{ 
		kq_data->prev = kq_data;
		kq_data->next = kq_data; 
	}

	template<typename T>
	list<T>::list(const list& other) 
		: kq_data((pointer_type)::operator new(sizeof(element))), kq_size(0)
	{
		for (auto& element : other)
		{
			push_back(element);
		}
	}

	template<typename T>
	list<T>::list(list&& other) noexcept 
		: kq_data(other.kq_data), kq_size(other.kq_size)
	{
		other.kq_data = ::operator new(sizeof(element));
		other.kq_data->prev = kq_data;
		other.kq_data->next = kq_data;
		other.kq_size = 0;
	}

	template<typename T>
	list<T>::list(size_t size)
		: kq_data((element*)::operator new(sizeof(element))), kq_size(0)
	{
		kq_data->prev = kq_data;
		kq_data->next = kq_data;
		while (size > 0)
		{
			push_back(value_type());
			--size;
		}
	}

	template<typename T>
	list<T>::list(size_t size, const value_type& objectToFill)
		: kq_data((element*)::operator new(sizeof(element))), kq_size(0)
	{
		kq_data->next = kq_data;
		kq_data->prev = kq_data;
		assign(size, objectToFill);
	}

	template<typename T>
	template<typename iterType, typename std::enable_if<is_iterator<iterType>, int>::type>
	list<T>::list(iterType first, iterType last)
		: kq_data((element*)::operator new(sizeof(element))), kq_size(0)
	{
		kq_data->next = kq_data;
		kq_data->prev = kq_data;
		assign(first, last);
	}

	template<typename T>
	template<typename ilT>
	list<T>::list(const std::initializer_list<ilT>& ilist)
		: kq_data((element*)::operator new(sizeof(element))), kq_size(0)
	{
		kq_data->next = kq_data;
		kq_data->prev = kq_data;
		assign(ilist);
	}

	template<typename T>
	list<T>::~list()
	{
		clear();
		::operator delete(kq_data);
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
			delete kq_data;
			kq_data = other.kq_data;
			kq_size = other.kq_size;
			other.kq_data = (element*)::operator new (sizeof(element));
			other.kq_data->next = other.kq_data;
			other.kq_data->prev = other.kq_data;
			other.kq_size = 0;
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
		if (kq_size != other.kq_size)
		{
			return false;
		}
		else
		{
			element* A = kq_data->next;
			element* B = other.kq_data->next;
			for (size_t i = 0; i < kq_size; ++i)
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
		if (kq_data == 0)
		{
			kq_data->next = new element(elementToAdd); 
			kq_data->prev = kq_data->next;
			kq_data->next->prev = kq_data;
			kq_data->next->next = kq_data;
			++kq_size;
			return kq_data->next->value;
		}
		else
		{
			element* keep = kq_data->prev;
			keep->next = new element(elementToAdd);
			keep->next->next = kq_data;
			kq_data->prev = keep->next;
			keep->next->prev = keep;
			++kq_size;
			return keep->next->value;
		}
	}

	template<typename T>
	typename list<T>::value_type& list<T>::push_front(const typename list<T>::value_type& elementToAdd)
	{
		if (kq_size == 0)
		{
			kq_data->next = new element(elementToAdd);
			kq_data->prev = kq_data->next;
			kq_data->next->prev = kq_data;
			kq_data->next->next = kq_data;
			++kq_size;
			return kq_data->next->value;
		}
		else
		{
			element* keep = kq_data->next;
			keep->prev = new element(elementToAdd);
			kq_data->next = keep->prev;
			keep->prev->next = keep;
			keep->prev->prev = kq_data;
			++kq_size;
			return keep->prev->value;
		}
	}

	template<typename T>
	template<typename... Args>
	typename list<T>::value_type& list<T>::emplace_back(Args&&... args)
	{
		if (kq_data == 0)
		{
			kq_data->next = new element(std::forward<Args>(args)...);
			kq_data->prev = kq_data->next;
			kq_data->next->prev = kq_data;
			kq_data->next->next = kq_data;
			++kq_size;
			return kq_data->next->value;
		}
		else
		{
			element* keep = kq_data->prev;
			keep->next = new element(std::forward<Args>(args)...);
			keep->next->next = kq_data;
			kq_data->prev = keep->next;
			keep->next->prev = keep;
			++kq_size;
			return keep->next->value;
		}
	}

	template<typename T>
	template<typename... Args>
	typename list<T>::value_type& list<T>::emplace_front(Args&&... args)
	{
		if (kq_size == 0)
		{
			kq_data->next = new element(std::forward<Args>(args)...);
			kq_data->prev = kq_data->next;
			kq_data->next->prev = kq_data;
			kq_data->next->next = kq_data;
			++kq_size;
			return kq_data->next->value;
		}
		else
		{
			element* keep = kq_data->next;
			keep->prev = new element(std::forward<Args>(args)...);
			kq_data->next = keep->prev;
			keep->prev->next = keep;
			keep->prev->prev = kq_data;
			++kq_size;
			return keep->prev->value;
		}
	}

	template<typename T>
	typename list<T>::value_type& list<T>::insert(iterator position, const value_type& elementToAdd)
	{
		if (position.ptr() != kq_data)
		{
			if (position.next() == kq_data)
			{
				return push_back(elementToAdd);
			}
			else if (position.prev() == kq_data)
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
				++kq_size;
			}
		}
	}

	template<typename T>
	template<typename... Args>
	typename list<T>::value_type& list<T>::emplace(iterator position, Args&&... args)
	{
		if (position.ptr() != kq_data)
		{
			if (position.next() == kq_data)
			{
				return emplace_back(std::forward<Args>(args)...);
			}
			else if (position.prev() == kq_data)
			{
				return emplace_front(std::forward<Args>(args)...);
			}
			else
			{
				element* newElement = new element(std::forward<Args>(args)...);
				newElement->next = position.ptr();
				newElement->prev = position.prev();
				position.prev()->next = newElement;
				++kq_size;
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
	auto list<T>::assign(iterType first, iterType last)
		->typename std::enable_if<is_iterator<iterType>, void>::type
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
		if (kq_size > 1)
		{
			element* remove = kq_data->prev;
			kq_data->prev->prev->next = kq_data;
			kq_data->prev = kq_data->prev->prev;
			delete remove;
			--kq_size;
		}
		else if (kq_size == 1)
		{
			delete kq_data->next;
			kq_data->next = kq_data;
			kq_data->prev = kq_data;
			kq_size = 0;
		}
		else {}
	}

	template<typename T>
	void list<T>::pop_front()
	{
		if (kq_size > 1)
		{
			element* remove = kq_data->next;
			kq_data->next->next->prev = kq_data;
			kq_data->next = kq_data->next->next;
			delete remove;
			--kq_size;
		}
		else if (kq_size == 1)
		{
			delete kq_data->next;
			kq_data->next = kq_data;
			kq_data->prev = kq_data;
			kq_size = 0;
		}
		else {}
	}

	template<typename T>
	void list<T>::clear()
	{
		
		if (kq_size > 1)
		{
			element* current = kq_data->next;
			while (current != kq_data)
			{
				element* next = current->next;
				delete current;
				current = next;
			}
			kq_size = 0;
			kq_data->next = kq_data;
			kq_data->prev = kq_data;
		}
		else if (kq_size == 1)
		{
			delete kq_data->next;
			kq_data->next = kq_data;
			kq_data->prev = kq_data;
		}
	}

	template<typename T>
	void list<T>::erase(iterator position)
	{
		if (position.ptr() != kq_data)
		{
			if (position.next() == kq_data)
			{
				pop_back();
			}
			else if (position.prev() == kq_data)
			{
				pop_front();
			}
			else
			{
				position.prev()->next = position.next();
				position.next()->prev = position.prev();
				delete position.ptr();
				--kq_size;
			}
		}
		
	}

	template<typename T>
	void list<T>::swap(list& other)
	{
		kq::swap(kq_data, other.kq_data);
		kq::swap(kq_size, other.kq_size);
	}

	template<typename T>
	typename list<T>::value_type& list<T>::front() 
	{ 
			if (kq_size == 0)
			{
				throw std::out_of_range("front(), called on empty list");
			}	
			return kq_data->next->value;
	}

	template<typename T>
	const typename list<T>::value_type& list<T>::front() const 
	{
			if (kq_size == 0)
			{
				throw std::out_of_range("front(), called on empty list");
			}
			return kq_data->next->value;
	}

	template<typename T>
	typename list<T>::value_type& list<T>::back() 
	{
			if (kq_size == 0)
			{
				throw std::out_of_range("back(), called on empty list");
			}
			return kq_data->prev->value;
	}

	template<typename T>
	const typename list<T>::value_type& list<T>::back() const 
	{
			if (kq_size == 0)
			{
				throw std::out_of_range("back(), called on empty list");
			}
			return kq_data->prev->value;
	}

}

#endif