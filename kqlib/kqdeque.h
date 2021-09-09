#ifndef kqdeque_
#define kqdeque_

#include "kqother.h"

namespace kq
{
	template<typename T, bool constant>
	struct dq_iterator
	{
	public:
		using value_type = T;
		using pointer_type = T*;
		using reference_type = typename std::conditional<constant, const value_type&, value_type&>::type;
		using iterator_category = std::random_access_iterator_tag;

		dq_iterator() : kq_ptr() {}
		dq_iterator(const dq_iterator& other) : kq_ptr(other.kq_ptr) {}
		dq_iterator(dq_iterator&& other) noexcept : kq_ptr(other.kq_ptr) { other.kq_ptr = nullptr; }
		dq_iterator(pointer_type ptr_) : kq_ptr(ptr_) {};
		
		dq_iterator& operator=(const dq_iterator& other) { kq_ptr = other.kq_ptr; return *this; }
		dq_iterator& operator=(dq_iterator&& other) noexcept { kq_ptr = other.kq_ptr; other.kq_ptr = nullptr; return *this; }

		bool operator==(const dq_iterator& other) const { return kq_ptr == other.kq_ptr; }
		bool operator!=(const dq_iterator& other) const { return !(*this == other.kq_ptr); }
		bool operator>(const dq_iterator& other) const { return kq_ptr > other.kq_ptr; }
		bool operator<(const dq_iterator& other) const { return kq_ptr < other.kq_ptr; }
		bool operator>=(const dq_iterator& other) const { return kq_ptr >= other.kq_ptr; }
		bool operator<=(const dq_iterator& other) const { return kq_ptr <= other.kq_ptr; }

		dq_iterator operator++(int) { auto Tmp = *this; ++kq_ptr; return Tmp; }
		dq_iterator& operator++() { ++kq_ptr; return *this; }
		dq_iterator operator--(int) { auto Tmp = *this; --kq_ptr; return Tmp; }
		dq_iterator& operator--() { --kq_ptr; return *this; }
		dq_iterator operator+(int rhs) const { return kq_ptr + rhs; }
		dq_iterator operator-(int rhs) const { return kq_ptr - rhs; }
		dq_iterator& operator+=(int rhs) { kq_ptr += rhs; return *this; }
		dq_iterator& operator-=(int rhs) { kq_ptr -= rhs; return *this; }
		size_t operator-(const dq_iterator& rhs) const { return abs(kq_ptr - rhs.kq_ptr); }
		friend dq_iterator operator+(int lhs, const dq_iterator& rhs) { return rhs.kq_ptr + lhs; }

		reference_type operator*() { return *kq_ptr; }
		pointer_type operator->() const { return kq_ptr; }

	private:
		pointer_type kq_ptr;
	};

	template<typename T, bool constant>
	struct dq_reverse_iterator
	{
	public:
		using value_type = T;
		using pointer_type = T*;
		using reference_type = typename std::conditional<constant, const value_type&, value_type&>::type;
		using iterator_category = std::random_access_iterator_tag;

		dq_reverse_iterator() : kq_ptr() {}
		dq_reverse_iterator(const dq_reverse_iterator& other) : kq_ptr(other.kq_ptr) {}
		dq_reverse_iterator(dq_reverse_iterator&& other) noexcept : kq_ptr(other.kq_ptr) { other.kq_ptr = nullptr; }
		dq_reverse_iterator(pointer_type ptr_) : kq_ptr(ptr_) {};

		dq_reverse_iterator& operator=(const dq_reverse_iterator& other) { kq_ptr = other.kq_ptr; return *this; }
		dq_reverse_iterator& operator=(dq_reverse_iterator&& other) noexcept { kq_ptr = other.kq_ptr; other.kq_ptr = nullptr; return *this; }

		bool operator==(const dq_reverse_iterator& other) const { return kq_ptr == other.kq_ptr; }
		bool operator!=(const dq_reverse_iterator& other) const { return !(*this == other.kq_ptr); }
		bool operator>(const dq_reverse_iterator& other) const { return kq_ptr < other.kq_ptr; }
		bool operator<(const dq_reverse_iterator& other) const { return kq_ptr > other.kq_ptr; }
		bool operator>=(const dq_reverse_iterator& other) const { return kq_ptr <= other.kq_ptr; }
		bool operator<=(const dq_reverse_iterator& other) const { return kq_ptr >= other.kq_ptr; }

		dq_reverse_iterator operator++(int) { auto Tmp = *this; --kq_ptr; return Tmp; }
		dq_reverse_iterator& operator++() { --kq_ptr; return *this; }
		dq_reverse_iterator operator--(int) { auto Tmp = *this; ++kq_ptr; return Tmp; }
		dq_reverse_iterator& operator--() { ++kq_ptr; return *this; }
		dq_reverse_iterator operator+(int rhs) const { return kq_ptr - rhs; }
		dq_reverse_iterator operator-(int rhs) const { return kq_ptr + rhs; }
		dq_reverse_iterator& operator+=(int rhs) { kq_ptr -= rhs; return *this; }
		dq_reverse_iterator& operator-=(int rhs) { kq_ptr += rhs; return *this; }
		size_t operator-(const dq_reverse_iterator& rhs) const { return abs(kq_ptr - rhs.kq_ptr); }
		friend dq_reverse_iterator operator+(int lhs, const dq_reverse_iterator& rhs) { return rhs.kq_ptr - lhs; }

		reference_type operator*() const { return *kq_ptr; }
		pointer_type operator->() const { return kq_ptr; }

	private:
		pointer_type kq_ptr;
	};


	template<typename T>
	struct deque
	{
	public:
		using value_type = T;
		using pointer_type = T*;
		using reference_type = T&;
		using iterator = dq_iterator<value_type, false>;
		using const_iterator = dq_iterator<value_type, true>;
		using reverse_iterator = dq_reverse_iterator<value_type, false>;
		using const_reverse_iterator = dq_reverse_iterator<value_type, true>;

		deque();
		deque(const deque&);
		deque(deque&&);
		deque(size_t);
		deque(size_t, const value_type&);
		template<typename iterType, std::enable_if_t<is_iterator<iterType>, int> = 0>
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

		size_t size() const { return kq_size; }
		size_t cap() const { return kq_cap; }
		pointer_type data() const { return kq_data; }
		size_t margin() const { return kq_margin; }

		iterator begin() { return kq_data + kq_margin; }
		iterator end() { return kq_data + kq_margin + kq_size; }
		const_iterator begin() const { return kq_data + kq_margin; }
		const_iterator end() const { return kq_data + kq_margin + kq_size; }
		const_iterator cbegin() const { return kq_data + kq_margin; }
		const_iterator cend() const { return kq_data + kq_margin + kq_size; }
		reverse_iterator rbegin() { return kq_data + kq_margin + kq_size - 1; }
		reverse_iterator rend() { return kq_data - 1; }
		const_reverse_iterator rbegin() const { return kq_data + kq_margin + kq_size - 1; }
		const_reverse_iterator rend() const { return kq_data - 1; }
		const_reverse_iterator crbegin() const { return kq_data + kq_margin + kq_size - 1; }
		const_reverse_iterator crend() const { return kq_data - 1; }

		
		bool is_empty() const { return kq_size == 0; }
		value_type& push_back(const value_type&);
		value_type& push_front(const value_type&);
		template<typename... Args>
		value_type& emplace_back(Args&&... args);
		template<typename... Args>
		value_type& emplace_front(Args&&... args);

		void assign(size_t, const value_type&);
		template<typename iterType>
		auto assign(iterType, iterType)->std::enable_if_t<is_iterator<iterType>, void>;
		template<typename ilT>
		void assign(const std::initializer_list<ilT>&);

		void pop_back();
		void pop_front();
		void clear();

		void reserve(size_t);
		void shrinkToFit() { realloc_exactly(kq_size); }
		void swap(deque&);

		value_type& front();
		const value_type& front() const;
		value_type& back();
		const value_type& back() const;

		value_type& operator[](size_t index) { return *(kq_data + kq_margin + index); }
		const value_type& operator[](size_t index) const { return *(kq_data + kq_margin + index); }
		value_type& at(size_t);
		const value_type& at(size_t) const;

	private:
		pointer_type kq_data;
		size_t kq_size;
		size_t kq_cap;
		size_t kq_margin;

		void realloc(size_t);
		void realloc_exactly(size_t);
		void destroy();
	};

	template<typename T>
	deque<T>::deque() 
		: kq_data(nullptr), kq_size(0), kq_cap(0), kq_margin(0) 
	{}

	template<typename T>
	deque<T>::deque(const deque& other)
		: kq_data(nullptr), kq_size(0), kq_cap(0), kq_margin(0)
	{
		assign(other.begin(), other.end());
	}

	template<typename T>
	deque<T>::deque(deque&& other)
		: kq_data(other.kq_data), kq_size(other.kq_size), kq_cap(other.kq_cap), kq_margin(other.kq_margin)
	{
		other.kq_data = nullptr;
		other.kq_size = 0;
		other.kq_cap = 0;
		other.kq_margin = 0;
	}

	template<typename T>
	deque<T>::deque(size_t size)																		// kq_cap / 2 - 1
		: kq_data((pointer_type)::operator new[](sizeof(value_type)* size)), kq_size(size), kq_cap(size), kq_margin(0)
	{}

	template<typename T>
	deque<T>::deque(size_t size, const value_type& objectToFill) 
		: kq_data(nullptr), kq_size(0), kq_cap(0), kq_margin(0)
	{
		assign(size, objectToFill);
	}

	template<typename T>
	template<typename iterType, std::enable_if_t<is_iterator<iterType>, int>>
	deque<T>::deque(iterType first, iterType last)
		: kq_data(nullptr), kq_size(0), kq_cap(0), kq_margin(0)
	{
		assign(first, last);
	}

	template<typename T>
	template<typename ilT>
	deque<T>::deque(const std::initializer_list<ilT>& ilist)
		: kq_data(nullptr), kq_size(0), kq_cap(0), kq_margin(0)
	{
		assign(ilist);
	}

	template<typename T>
	deque<T>::~deque()
	{
		destroy(); delete[] kq_data;
	}

	template<typename T>
	typename deque<T>::deque& deque<T>::operator=(const deque& other)
	{
		clear();
		assign(other.begin(), other.end());
		return *this;
	}

	template<typename T>
	typename deque<T>::deque& deque<T>::operator=(deque&& other) noexcept
	{
		clear();
		kq_data = other.kq_data;
		kq_size = other.kq_size;
		kq_cap = other.kq_cap;
		kq_margin = other.kq_margin;
		other.kq_data = nullptr;
		other.kq_size = 0;
		other.kq_cap = 0;
		other.kq_margin = 0;
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
		if (kq_size != other.kq_size)
		{
			return false;
		}
		else
		{
			for(size_t i = 0; i < kq_size; ++i)
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
		if (kq_size >= kq_cap - kq_margin)
		{
			realloc(kq_cap * 2);
		}
		new (kq_data + kq_margin + kq_size) value_type(std::move(toAdd));
		return (*this)[kq_size++];
	}

	template<typename T>
	typename deque<T>::value_type& deque<T>::push_front(const typename deque<T>::value_type& toAdd)
	{
		if (kq_margin == 0)
		{
			realloc(kq_cap * 2);
		}
		++kq_size;
		new (kq_data + --kq_margin) value_type(std::move(toAdd));
		return *(kq_data + kq_margin);
	}

	template<typename T>
	template<typename... Args>
	typename deque<T>::value_type& deque<T>::emplace_back(Args&&... args)
	{
		if (kq_size >= kq_cap - kq_margin)
		{
			realloc(kq_cap * 2);
		}
		new (kq_data + kq_margin + kq_size) value_type(std::forward<Args>(args)...);
		return (*this)[kq_size++];
	}
	template<typename T>
	template<typename... Args>
	typename deque<T>::value_type& deque<T>::emplace_front(Args&&... args)
	{
		if (kq_margin == 0)
		{
			realloc(kq_cap * 2);
		}
		++kq_size;
		new (kq_data + --kq_margin) value_type(std::forward<Args>(args)...);
		return *(kq_data + kq_margin);
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
	auto deque<T>::assign(iterType first, iterType last)->std::enable_if_t<is_iterator<iterType>, void>
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
		for (auto& element : ilist)
		{
			push_back(element);
		}
	}

	template<typename T>
	void deque<T>::pop_back()
	{
		(kq_data + kq_margin + --kq_size)->~value_type();
		if (kq_size < kq_cap - kq_size)
		{
			realloc(kq_cap / 2);
		}

	}

	template<typename T>
	void deque<T>::pop_front()
	{
		(kq_data + kq_margin)->~value_type();
		--kq_size;
		++kq_margin;
		if (kq_margin >= kq_cap / 2)
		{
			realloc(kq_cap / 2);
		}
	}

	template<typename T>
	void deque<T>::clear()
	{
		if (kq_data != nullptr)
		{
			destroy();
			delete[] kq_data;
			kq_data = nullptr;
			kq_size = 0;
			kq_margin = 0;
			kq_cap = 0;
		}
	}

	template<typename T>
	void deque<T>::reserve(size_t size)
	{
		if (size > kq_cap)
		{
			if (size % 2 == 0)
			{
				realloc(size);
			}
			else
			{
				realloc(size + 1);
			}
		}
	}

	template<typename T>
	void deque<T>::swap(deque& other)
	{
		kq::swap(kq_data, other.kq_data);
		kq::swap(kq_size, other.kq_size);
		kq::swap(kq_cap, other.kq_cap);
		kq::swap(kq_margin, other.kq_margin);
	}

	template<typename T>
	typename deque<T>::value_type& deque<T>::front() 
	{
			if (kq_size == 0)
			{
				throw std::out_of_range("front(), called on empty deque");
			}
			return *(kq_data + kq_margin);
	}

	template<typename T>
	const typename deque<T>::value_type& deque<T>::front() const 
	{
			if (kq_size == 0)
			{
				throw std::out_of_range("front(), called on empty deque");
			}
			return *(kq_data + kq_margin);
	}

	template<typename T>
	typename deque<T>::value_type& deque<T>::back() 
	{
			if (kq_size == 0)
			{
				throw std::out_of_range("back(), called on empty deque");
			}
			return *(kq_data + kq_margin + kq_size - 1);
	}

	template<typename T>
	const typename deque<T>::value_type& deque<T>::back() const 
	{ 
			if (kq_size == 0)
			{
				throw std::out_of_range("back(), called on empty deque");
			}
			return *(kq_data + kq_margin + kq_size - 1);
	}

	template<typename T>
	typename deque<T>::value_type& deque<T>::at(size_t index)
	{
			// kq_margin + index > kq_cap
			if (index >= kq_size)
			{
				throw std::out_of_range("at(), trying to acces elements out of range on deque");
			}
			return *(kq_data + kq_margin + index);
	}

	template<typename T>
	const typename deque<T>::value_type& deque<T>::at(size_t index) const
	{
			// kq_margin + index > kq_cap
			if (index >= kq_size)
			{
				throw std::out_of_range("at(), trying to acces elements out of range on deque");
			}
			return *(kq_data + kq_margin + index);
	}

	template<typename T>
	void deque<T>::realloc(size_t newCap)
	{
		//std::cout << "realloc";
		if (newCap < 2)
		{
			newCap = 2;
		}
		pointer_type newBlock = (pointer_type)::operator new[](sizeof(value_type)*newCap);
		size_t equalSides = 0;
		size_t newMargin = 0;
		if (newCap > kq_cap)
		{
			newMargin = newCap / 4;
			if (kq_cap - kq_size > 2)
			{
				equalSides = (kq_cap - kq_size) / 2;
			}
		}
		else
		{
			newMargin = 0;
			equalSides = 0;
		}
		
		if (newBlock != nullptr && kq_data != nullptr)
		{
			for (size_t i = 0; i < kq_size; ++i)
			{
				new (newBlock + newMargin + i + equalSides) value_type(std::move((*this)[i]));
			}
		}

		if (newCap < 2)
		{
			kq_margin = 1;
		}
		else
		{
			kq_margin = newMargin + equalSides;
		}

		destroy();
		delete[] kq_data;
		kq_cap = newCap;
		kq_data = newBlock;
		
		//std::cout << "Details from realloc: cap = " << kq_cap << " margin = " << kq_margin << " size = " << kq_size << "\n";
	}

	template<typename T>
	void deque<T>::realloc_exactly(size_t newCap)
	{
		if (newCap % 2 == 1)
		{
			++newCap;
		}
		pointer_type newBlock = (pointer_type)::operator new[](sizeof(value_type)* newCap);

		if (kq_data != nullptr && newBlock != nullptr)
		{
			for (size_t i = 0; i < kq_size; ++i)
			{
				new(newBlock + i) value_type(std::move(*this)[i]);
			}
		}
		destroy();
		delete[] kq_data;
		kq_data = newBlock;
		kq_cap = newCap;
		kq_margin = 0; 
	}

	template<typename T>
	void deque<T>::destroy()
	{
		if (kq_data != nullptr)
		{
			for (size_t i = 0; i < kq_size; i++)
			{
				(kq_data + kq_margin + i)->~value_type();
			}
		}
	}
}



#endif