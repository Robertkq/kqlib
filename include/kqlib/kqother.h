#ifndef kqother_
#define kqother_

#include <initializer_list>
#include <utility>
#include <type_traits>
#include <iterator>
#include <stdexcept>

namespace kq
{

	template <class...> using void_t = void;

	template<typename container>
	struct reverseView;

	// FUNCTION HEADERS //////////////////////////////////////////////////////////////////////////////////////

	template<typename container>
	reverseView<container> reverseIter(container&);

	template<typename value_type>
	value_type abs(const value_type& number);

	template<typename T>
	void swap(T& first, T& second);

	template<typename iterType>
	iterType& next(iterType& iterator, size_t n);

	template<typename iterType>
	iterType& prev(iterType& iterator, size_t n);


	// FUNCTION IMPLEMENTATIONS //////////////////////////////////////////////////////////////////////////////////////
	template<typename container>
	struct reverseView
	{
	public:
		reverseView(container& _ref_) : ref(_ref_) {};
		typename container::reverse_iterator begin() { return ref.rbegin(); }
		typename container::reverse_iterator end() { return ref.rend(); }
	private:
		container& ref;
	};

	template<typename container>
	reverseView<container> reverseIter(container& _container)
	{
		return reverseView<container>(_container);
	}



	template<typename value_type>
	value_type abs(const value_type& number)
	{
		if (number < 0)
			return number * -1;
		return number;
	}

	template<typename T>
	void swap(T& first, T& second)
	{
		static_assert(
		(std::is_move_constructible<T>::value && std::is_move_assignable<T>::value) ||
		(std::is_move_constructible<T>::value && std::is_copy_assignable<T>::value) ||
		(std::is_copy_constructible<T>::value && std::is_move_assignable<T>::value) ||
		(std::is_copy_constructible<T>::value && std::is_copy_assignable<T>::value),
		"type T is not move/copy constructible and assignable");
		T aux(std::move(first));
		first = std::move(second);
		second = std::move(aux);
	}

	template<typename iterType>
	iterType& next(iterType& iterator, size_t n)
	{
		while (n > 0)
		{
			++iterator;
			--n;
		}
	}

	template<typename iterType>
	iterType& prev(iterType& iterator, size_t n)
	{
		while (n > 0)
		{
			--iterator;
			++n;
		}
	}


	// TYPE CHECKING //////////////////////////////////////////////////////////////////////////////////////

	template<typename iterType, typename = void>
	struct is_iterator
	{
		constexpr static bool value = false;
	};

	template<typename iterType>
	struct is_iterator<iterType, kq::void_t<typename iterType::iterator_category>>
	{
		constexpr static bool value = true;
	};


	// PROTOTYPES //////////////////////////////////////////////////////////////////////////////////////
	template<typename T>
	struct rangeView
	{
		using value_type = T;
		using pointer_type = value_type*;

		struct myType
		{
			myType(const value_type& transform) : actualValue(transform) {}
			myType operator++(int) { myType Tmp = actualValue; actualValue += incrementBy; return Tmp; }

			value_type actualValue;

		};

		rangeView(const value_type& _end_) : start(0), endv(_end_), incrementBy(1) {}
		rangeView(const value_type& _start_, const value_type& _end_) : start(_start_), endv(_end_), incrementBy(1) {}
		rangeView(const value_type& _start_, const value_type& _end_, const value_type& _incrementBy_)
			: start(_start_), endv(_end_), incrementBy(_incrementBy_) {}

		myType begin() { return start; }
		myType end() { return endv; }

		value_type start;
		value_type endv;
		value_type incrementBy;

	};
}
#endif
