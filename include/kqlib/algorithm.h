#ifndef KQALGORITHM_
#define KQALGORITHM_

#include "other.h"

namespace kq
{

	

	template<typename iterType>
	constexpr void reverse(iterType first, iterType last)
	{
		for (; first != last; ++first)
		{
			if (--last != first)
			{
				swap(*first, *last);
			}
			else
			{
				return;
			}
		}
	}

	template<typename iterType, typename T>
	constexpr iterType find(iterType first, iterType last, const T& value)
	{
		for (; first != last; ++first)
		{
			if (equal_to<typename iterType::value_type>{}(*first, value))
			{
				return first;
			}
		}
		return last;
	}

	template<typename iterType, typename UnaryPredicate>
	constexpr iterType find_if(iterType first, iterType last, UnaryPredicate p)
	{
		for (; first != last; ++first)
		{
			if (p(*first))
			{
				return first;
			}
		}
		return last;
	}

	template<typename iterType, typename UnaryPredicate>
	constexpr iterType find_if_not(iterType first, iterType last, UnaryPredicate q)
	{
		for (; first != last; ++first)
		{
			if (!q(*first))
			{
				return first;
			}
		}
		return last;
	}

	template<typename iterType, typename T>
	constexpr size_t count(iterType first, iterType last, const T& value)
	{
		size_t ret = 0;
		for (; first != last; ++first)
		{
			if (equal_to<typename iterType::value_type>{}(*first, value))
			{
				// Notee: *first and value must be of the same type,
				++ret;
			}
		}
		return ret;
	}

	template<typename iterType, typename UnaryPredicate>
	constexpr size_t count_if(iterType first, iterType last, UnaryPredicate p)
	{
		size_t ret = 0;
		for (; first != last; ++first)
		{
			if (p(*first))
			{
				++ret;
			}
		}
		return ret;
	}

	template<typename iterType, typename UnaryPredicate>
	constexpr size_t count_if_not(iterType first, iterType last, UnaryPredicate q)
	{
		size_t ret = 0;
		for (; first != last; ++first)
		{
			if (!q(*first))
			{
				++ret;
			}
		}
		return ret;
	}

	template<typename iterType, typename Compare = greater<typename iterType::value_type>>
	constexpr iterType max_element(iterType first, iterType last, Compare comp = greater<typename iterType::value_type>{})
	{
		if (first == last) { return last; }
		iterType max = first;
		++first;
		for (; first != last; ++first)
		{
			if (comp(*first, *max))
			{
				max = first;
			}
		}
		return max;
	}

	template<typename iterType, typename Compare = less<typename iterType::value_type>>
	constexpr iterType min_element(iterType first, iterType last, Compare comp = less<typename iterType::value_type>{})
	{
		if (first == last) { return last; }
		iterType min = first;
		++first;
		for (; first != last; ++first)
		{
			if (comp(*first, *min))
			{
				min = first;
			}
		}
		return min;
	}

	template<typename iterType, typename Compare = less<typename iterType::value_type>>
	void sort(iterType first, iterType last, Compare comp = less<typename iterType::value_type>{})
	{
		if (first == last)
		{
			return;
		}
		else
		{
			iterType p = sort_partition(first, last, comp);
			sort(first, p, comp);
			sort(++p, last, comp);
		}
	}

	template<typename iterType, typename Compare>
	iterType sort_partition(iterType first, iterType last, Compare comp)
	{
		
		--last;
		iterType pivot = last;
		iterType smaller = first;
		--smaller;
		for (; first != last; ++first)
		{
			if (comp(*first, *pivot))
			{
				++smaller;
				swap(*smaller, *first);
			}
			// Used to check `sort_partition_equal_to(*smaller, *first)` before swapping, it is most likely unefficient since comp should cover most general cases
		}
		++smaller;
		swap(*smaller, *pivot);
		return smaller;
	}

}
#endif
