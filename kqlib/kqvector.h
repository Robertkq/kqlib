#ifndef kqvector_
#define kqvector_

#include <iostream>
#include "kqother.h"

namespace kq
{
	template<typename T, bool constant>
	struct v_iterator
	{
	public:
		using value_type = T;
		using pointer_type = value_type*;
		using reference_type = typename std::conditional<constant, const value_type&, value_type&>::type;
		using difference_type = int;
		using iterator_category = std::random_access_iterator_tag;
		
		v_iterator() : kq_ptr(nullptr) {}
		v_iterator(const v_iterator& other) : kq_ptr(other.kq_ptr) {}
		v_iterator(v_iterator&& other) noexcept : kq_ptr(other.kq_ptr) { other.kq_ptr = nullptr; }
		v_iterator(pointer_type ptr) : kq_ptr(ptr) {}

		v_iterator& operator=(const v_iterator& other) { kq_ptr = other.kq_ptr; return *this; }
		v_iterator& operator=(v_iterator&& other) noexcept { kq_ptr = other.kq_ptr; other.kq_ptr = nullptr; return *this; }

		bool operator==(const v_iterator& rhs) const { return kq_ptr == rhs.kq_ptr; }
		bool operator!=(const v_iterator& rhs) const { return !(kq_ptr == rhs.kq_ptr); }
		bool operator<(const v_iterator& rhs) const { return kq_ptr < rhs.kq_ptr; }
		bool operator>(const v_iterator& rhs) const { return kq_ptr > rhs.kq_ptr; }
		bool operator<=(const v_iterator& rhs) const { return kq_ptr <= rhs.kq_ptr; }
		bool operator>=(const v_iterator& rhs) const { return kq_ptr >= rhs.kq_ptr; }

		v_iterator operator++(difference_type) { pointer_type Tmp = kq_ptr; kq_ptr++; return Tmp; }
		v_iterator& operator++() { kq_ptr++; return *this; }
		v_iterator operator--(difference_type) { pointer_type Tmp = kq_ptr; kq_ptr--; return Tmp; }
		v_iterator& operator--() { kq_ptr--; return *this; }
		v_iterator operator+(difference_type rhs) const { return kq_ptr + rhs; }
		v_iterator operator-(difference_type rhs) const { return kq_ptr - rhs; }
		v_iterator& operator+=(difference_type rhs) { kq_ptr += rhs; return *this; }
		v_iterator& operator-=(difference_type rhs) { kq_ptr -= rhs; return *this; }
		friend v_iterator operator+(difference_type lhs, const v_iterator& rhs) { return rhs.kq_ptr + lhs; }
		size_t operator-(const v_iterator& rhs) const { return abs(kq_ptr - rhs.kq_ptr); }

		pointer_type ptr() const { return kq_ptr; }

		reference_type operator*() const { return *kq_ptr; }
		pointer_type operator->() const { return kq_ptr; }

	private:
		pointer_type kq_ptr;
	};

	template<typename T, bool constant>
	struct v_reverse_iterator
	{
	public:
		using value_type = T;
		using pointer_type = value_type*;
		using reference_type = typename std::conditional<constant, const value_type&, value_type&>::type;
		using difference_type = int;
		using iterator_category = std::random_access_iterator_tag;

		v_reverse_iterator() : kq_ptr(nullptr) {}
		v_reverse_iterator(const v_reverse_iterator& other) : kq_ptr(other.kq_ptr) {}
		v_reverse_iterator(v_reverse_iterator&& other) noexcept : kq_ptr(other.kq_ptr) { other.kq_ptr = nullptr; }
		v_reverse_iterator(pointer_type ptr) : kq_ptr(ptr) {}

		v_reverse_iterator& operator=(const v_reverse_iterator& other) { kq_ptr = other.kq_ptr; return *this; }
		v_reverse_iterator& operator=(v_reverse_iterator&& other) noexcept { kq_ptr = other.kq_ptr; other.kq_ptr = nullptr; return *this; }

		bool operator==(const v_reverse_iterator& other) const { return kq_ptr == other.kq_ptr; }
		bool operator!=(const v_reverse_iterator& other) const { return !(kq_ptr == other.kq_ptr); }
		bool operator<(const v_reverse_iterator& rhs) const { return kq_ptr > rhs.kq_ptr; }
		bool operator>(const v_reverse_iterator& rhs) const { return kq_ptr < kq_ptr; }
		bool operator<=(const v_reverse_iterator& rhs) const { return kq_ptr >= rhs.kq_ptr; }
		bool operator>=(const v_reverse_iterator& rhs) const { return kq_ptr <= rhs.kq_ptr; }

		v_reverse_iterator operator++(difference_type) { pointer_type Tmp = kq_ptr; kq_ptr--; return Tmp; }
		v_reverse_iterator& operator++() { kq_ptr--; return *this; }
		v_reverse_iterator operator--(difference_type) { pointer_type Tmp = kq_ptr; kq_ptr++; return Tmp; }
		v_reverse_iterator& operator--() { kq_ptr++; return *this; }
		v_reverse_iterator operator+(difference_type rhs) const { return kq_ptr - rhs; }
		v_reverse_iterator operator-(difference_type rhs) const { return kq_ptr + rhs; }
		v_reverse_iterator& operator+=(difference_type rhs)	{ kq_ptr -= rhs; return *this; }
		v_reverse_iterator& operator-=(difference_type rhs)	{ kq_ptr += rhs; return *this; }
		friend v_reverse_iterator operator+(difference_type lhs, const v_reverse_iterator& rhs) { return rhs.kq_ptr - lhs; }
		size_t operator-(const v_reverse_iterator& rhs)	const { return abs(kq_ptr - rhs.kq_ptr); }

		pointer_type ptr() const { return kq_ptr; }

		reference_type operator*() const { return *kq_ptr; }
		pointer_type operator->() const { return kq_ptr; }

		

	private:
		pointer_type kq_ptr;
	};

	template<typename T>
	struct vector
	{
	public:
		
		using value_type = T;
		using reference_type = value_type&;
		using pointer_type = value_type*;
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

		bool operator==(const vector<T>& other) const;
		bool operator!=(const vector<T>& other) const { return !(*this == other); }

		size_t size() const					{ return kq_size; }
		size_t capacity() const				{ return kq_cap; }
		pointer_type data()					{ return kq_data; } 
		const pointer_type data() const		{ return kq_data; }

		iterator begin()					{ return kq_data; }
		iterator end()						{ return (kq_data + kq_size); }
		const_iterator being() const		{ return kq_data; }
		const_iterator end() const			{ return (kq_data + kq_size); }
		const_iterator cbegin() const		{ return kq_data; }
		const_iterator cend() const			{ return (kq_data + kq_size); }
		reverse_iterator rbegin()			{ return (kq_data + kq_size - 1); }
		reverse_iterator rend()				{ return kq_data - 1; }
		const_reverse_iterator rbegin() const	{ return (kq_data + kq_size - 1); }
		const_reverse_iterator rend() const		{ return (kq_data - 1); }
		const_reverse_iterator crbegin() const	{ return (kq_data + kq_size - 1); }
		const_reverse_iterator crend() const	{ return kq_data - 1; }

		bool is_empty()	const { return kq_size == 0; }

		value_type& push_back(const value_type&);
		template<typename... Args>
		value_type& emplace_back(Args&&... args);
		value_type& insert(iterator, const value_type&);
		template<typename... Args>
		value_type& emplace(iterator position, Args&&... args);

		void assign(size_t, const value_type&);
		template<typename iterType>
		auto assign(iterType first, iterType last)
			-> typename std::enable_if<is_iterator<iterType>::value, void>::type;
		template<typename ilT>
		void assign(const std::initializer_list<ilT>&);

		void pop_back();
		void erase(iterator);
		void clear();

		void resize(size_t);
		void resize(size_t, const value_type&);

		void shrinkToFit()					{ if (kq_size != kq_cap) { realloc(kq_size); } }
		void reserve(size_t capToReserve)	{ if (capToReserve > kq_cap) { realloc(capToReserve); } }
		void swap(vector<T>&);

		value_type& front();
		const value_type& front() const;
		value_type& back();
		const value_type& back() const;

		value_type& operator[](size_t index) { return *(kq_data + index); }
		const value_type& operator[](size_t index) const { return *(kq_data + index); }
		value_type& at(size_t);
		const value_type& at(size_t) const;

	private:
		value_type* kq_data;
		size_t kq_size;
		size_t kq_cap;

		void realloc(size_t);
		void destroy();

	};
	/*
	* @brief This is the default constructor for vector
	*/
	template<typename T>
	vector<T>::vector() : kq_data(nullptr), kq_size(0), kq_cap(0) {}

	template<typename T>
	vector<T>::vector(const vector& other)
		: kq_data((pointer_type)::operator new[](sizeof(value_type)* other.kq_cap)), kq_size(other.kq_size), kq_cap(other.kq_cap)
	{
		for (size_t i = 0; i < kq_size; ++i)
		{
			new (kq_data + i) value_type(*(other.kq_data + i));
		}
	}

	template<typename T>
	vector<T>::vector(vector&& other) noexcept
		: kq_data(other.kq_data), kq_size(other.kq_size), kq_cap(other.kq_cap)
	{
		other.kq_data = nullptr;
		other.kq_size = 0;
		other.kq_cap = 0;
	}

	template<typename T>
	vector<T>::vector(size_t size) : kq_data((pointer_type)::operator new[](sizeof(value_type)* size)), kq_size(size), kq_cap(size) {}

	template<typename T>
	vector<T>::vector(size_t size, const value_type& objectToFill)
		: kq_data(nullptr), kq_size(0), kq_cap(0)
	{
		assign(size, objectToFill);
	}

	template<typename T>
	template<typename iterType, typename std::enable_if<is_iterator<iterType>::value, int>::type>
	vector<T>::vector(iterType first, iterType last)
		: kq_data(nullptr), kq_size(0), kq_cap(0)
	{
		assign(first, last);
	}

	template<typename T>
	template<typename ilT>
	vector<T>::vector(const std::initializer_list<ilT>& ilist)
		: kq_data(nullptr), kq_size(0), kq_cap(0)
	{
		assign(ilist);
	}

	template<typename T>
	vector<T>::~vector()
	{
		destroy();
		::operator delete[](kq_data);
	}

	template<typename T>
	typename vector<T>::vector& vector<T>::operator=(const vector& other)
	{
		if (this != &other)
		{
			clear();
			kq_data = (pointer_type)::operator new[](sizeof(value_type)* other.kq_cap);
			kq_size = other.kq_size;
			kq_cap = other.kq_cap;
			for (size_t i = 0; i < kq_size; i++)
			{
				new (kq_data + i) value_type(*(other.kq_data + i));
			}
		}
		return *this;
	}

	template<typename T>
	typename vector<T>::vector& vector<T>::operator=(vector&& other) noexcept
	{
		if (this != &other)
		{
			clear();
			kq_data = other.kq_data;
			kq_size = other.kq_size;
			kq_cap = other.kq_cap;
			other.kq_data = nullptr;
			other.kq_size = 0;
			other.kq_cap = 0;
		}
		return *this;
	}

	template<typename T>
	template<typename ilT>
	typename vector<T>::vector& vector<T>::operator=(const std::initializer_list<ilT>& ilist)
	{
		clear();
		assign(ilist);
		return *this;
	}

	template<typename T>
	bool vector<T>::operator==(const vector& other) const
	{
		if (kq_size != other.kq_size)
		{
			return false;
		}
		for (size_t i = 0; i < kq_size; i++)
		{
			if (*(kq_data + i) != *(other.kq_data + i))
			{
				return false;
			}
		}
		return true;
	}

	template<typename T>
	typename vector<T>::value_type& vector<T>::push_back(const value_type& value)
	{
		if (kq_size >= kq_cap)
		{
			realloc(kq_cap + kq_cap / 2);
		}
		new (kq_data + kq_size) value_type(value);
		kq_size++;
		return *(kq_data + kq_size - 1);
	}

	template<typename T>
	template<typename... Args>
	typename vector<T>::value_type& vector<T>::emplace_back(Args&&... args)
	{
		if (kq_size >= kq_cap)
		{
			realloc(kq_cap + kq_cap / 2);
		}
		new (kq_data + kq_size) value_type(std::forward<Args>(args)...);
		kq_size++;
		return *(kq_data + kq_size - 1);
	}

	template<typename T>
	typename vector<T>::value_type& vector<T>::insert(iterator position, const value_type& value)
	{
		// Note: iterator position will be invalid if we reallocate
		if ((position > begin() && position < end()) || position == begin())
		{
			size_t safePosition = 0;
			if (kq_size >= kq_cap)
			{
				safePosition = abs(position - begin());
				realloc(kq_cap + kq_cap / 2);
			}
			++kq_size;
			for (iterator it = end() - 2; it >= begin() + safePosition; --it)
			{
				*(it + 1) = std::move(*it);
			}
			*(begin() + safePosition) = value;
			return *(begin() + safePosition);
		}

	}

	template<typename T> template<typename... Args>
	typename vector<T>::value_type& vector<T>::emplace(iterator position, Args&&... args)
	{
		// Note: iterator position will be invalid if we reallocate
		if ((position > begin() && position < end()) || position == begin())
		{
			value_type holder(std::forward<Args>(args)...);
			size_t safePosition = 0;
			if (kq_size >= kq_cap)
			{
				safePosition = abs(position - begin());
				realloc(kq_cap + kq_cap / 2);
			}
			kq_size++;
			for (iterator it = end() - 2; it >= begin() + safePosition; --it)
			{
				*(it + 1) = std::move(*it);
			}
			*(begin() + safePosition) = std::move(holder);
			return *(begin() + safePosition);
		}

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
	auto vector<T>::assign(iterType first, iterType last)
			-> typename std::enable_if<is_iterator<iterType>::value, void>::type
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
		if (kq_size > 0)
		{
			--kq_size;
			(kq_data + kq_size)->~value_type();			
		}
	}

	template<typename T>
	void vector<T>::erase(iterator position)
	{
		if (kq_size > 0)
		{
			if (position >= begin() && position < end())
			{
				position->~T();
				for (position; position != end() - 1; ++position)
				{
					*position = std::move(*(position + 1));
				}
				--kq_size;
			}
		}
	}

	template<typename T>
	void vector<T>::clear()
	{
		
		if (kq_data != nullptr)
		{
			destroy();
			::operator delete[](kq_data);
			kq_data = nullptr;
			kq_size = 0;
			kq_cap = 0;
		}
	}

	template<typename T>
	void vector<T>::resize(size_t count)
	{
		if (count < kq_size)
		{
			kq_size = count;
		}
		else if (count > kq_size)
		{
			if (count > kq_cap)
			{
				reserve(count);
			}
			kq_size = count;
		}
	}

	template<typename T>
	void vector<T>::resize(size_t count, const value_type& value)
	{
		if (count < kq_size)
		{
			kq_size = count;
		}
		else if (count > kq_size)
		{
			if (count > kq_cap)
			{
				reserve(count);
			}
			count -= kq_size;
			while (count > 0)
			{
				push_back(value);
				--count;
			}
			
		}
	}

	template<typename T>
	void vector<T>::swap(vector& other)
	{
		kq::swap(kq_data, other.kq_data);
		kq::swap(kq_size, other.kq_size);
		kq::swap(kq_cap, other.kq_cap);

	}

	template<typename T>
	typename vector<T>::value_type& vector<T>::front() 
	{ 
	
			if (kq_size == 0)
			{
				throw std::out_of_range("front(), called on empty vector");
			}
			return *kq_data;
	}

	template<typename T>
	const typename vector<T>::value_type& vector<T>::front() const 
	{
			if (kq_size == 0)
			{
				throw std::out_of_range("front(), called on empty vector");
			}
			return *kq_data;
	}

	template<typename T>
	typename vector<T>::value_type& vector<T>::back() 
	{
			if (kq_size == 0)
			{
				throw std::out_of_range("back(), called on empty vector");
			}
			return *(kq_data + kq_size - 1);
	}

	template<typename T>
	const typename vector<T>::value_type& vector<T>::back() const 
	{
			if (kq_size == 0)
			{
				throw std::out_of_range("back(), called on empty vector");
			}
			return *(kq_data + kq_size - 1);
	}

	template<typename T>
	typename vector<T>::value_type& vector<T>::at(size_t index)
	{
			if (index >= kq_size)
				throw std::out_of_range("at(), trying to access elements out of range on vector");
			return *(kq_data + index);
	}

	template<typename T>
	const typename vector<T>::value_type& vector<T>::at(size_t index) const
	{
			if (index >= kq_size)
				throw std::out_of_range("at(), trying to access elements out of range on vector");
			return *(kq_data + index);
	}





	template<typename T>
	void vector<T>::realloc(size_t newCap)
	{
		
		if (newCap < 2)
		{
			newCap = 2;
		}

		pointer_type newBlock = (pointer_type) ::operator new[](sizeof(value_type) * newCap);

		if (kq_data != nullptr && newBlock != nullptr)
		{
			for (size_t i = 0; i < kq_size; ++i)
			{
				new (newBlock + i) value_type(std::move(*(kq_data + i)));
			}
		}

		destroy();
		::operator delete[](kq_data);
		kq_data = newBlock;
		kq_cap = newCap;
	}

	template<typename T>
	void vector<T>::destroy()
	{
		if (kq_data != nullptr)
		{
			for (size_t i = 0; i < kq_size; ++i)
			{
				(kq_data + i)->~value_type();
			}
		}

	}

}



#endif