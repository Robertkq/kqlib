#ifndef KQALGORITHM_
#define KQALGORITHM_

#include "other.h"

namespace kq
{

	namespace details
	{
		//Tag dispatch for equal_compare_impl functions to return TRUE if lhs == rhs
		struct eql_no_operator{};
		struct eql_not_equal : eql_no_operator{};
		struct eql_equal : eql_not_equal{};
		struct eql_operator_tag : eql_equal{};


		template<typename T>
		auto equal_compare_impl(const T& lhs, const T& rhs, eql_equal)
			-> decltype(lhs == rhs)
		{
			return lhs == rhs;
		}
		template<typename T>
		auto equal_compare_impl(const T& lhs, const T& rhs, eql_not_equal)
			-> decltype(lhs != rhs)
		{
			return !(lhs != rhs);
		}
		template<typename T>
		auto equal_compare_impl(const T& lhs, const T& rhs, eql_no_operator)
			-> bool = delete;

		struct sort_partition_eql_no_operator {};
		struct sort_partition_eql_not_equal : sort_partition_eql_no_operator {};
		struct sort_partition_eql_equal : sort_partition_eql_not_equal {};
		struct sort_partition_eql_operator_tag : sort_partition_eql_equal {};


		template<typename T>
		auto sort_partition_equal_compare_impl(const T& lhs, const T& rhs, sort_partition_eql_equal)
			-> decltype(lhs == rhs)
		{
			return lhs == rhs;
		}
		template<typename T>
		auto sort_partition_equal_compare_impl(const T& lhs, const T& rhs, sort_partition_eql_not_equal)
			-> decltype(lhs == rhs)
		{
			return !(lhs != rhs);
		}
		template<typename T>
		auto sort_partition_equal_compare_impl(const T& lhs, const T& rhs, sort_partition_eql_no_operator)
		{
			return false; // so that we will not swap in the if statement of sort_partition
		}

		struct not_eql_no_operator {};
		struct not_eql_equal : not_eql_no_operator {};
		struct not_eql_not_equal : not_eql_equal{};
		struct not_eql_operator_tag : not_eql_not_equal{};

		template<typename T>
		auto not_equal_compare_impl(const T& lhs, const T& rhs, not_eql_not_equal)
			-> decltype(lhs != rhs)
		{
			return lhs != rhs;
		}

		template<typename T>
		auto not_equal_compare_impl(const T& lhs, const T& rhs, not_eql_equal)
			-> decltype(lhs == rhs)
		{
			return !(lhs == rhs);
		}

		template<typename T>
		auto not_equal_compare_impl(const T& lhs, const T& rhs, not_eql_no_operator)
			-> bool = delete;

		//Tag dispatch for less_compare_impl fucntions to return TRUE if lhs < rhs or in bad cases lhs <= rhs
		struct less_no_operator{};
		struct less_has_greater_or_equal : less_no_operator {};
		struct less_has_smaller_or_equal : less_has_greater_or_equal{};
		struct less_has_greater : less_has_smaller_or_equal{};
		struct less_has_greater_or_equal_NE : less_has_greater{};
		struct less_has_greater_or_equal_E : less_has_greater_or_equal_NE{};
		struct less_has_smaller_or_equal_NE : less_has_greater_or_equal_NE{};
		struct less_has_smaller_or_equal_E : less_has_smaller_or_equal_NE{};
		struct less_has_greater_NE : less_has_smaller_or_equal_E{};
		struct less_has_greater_E : less_has_greater_NE{};
		struct less_has_smaller : less_has_greater_E{};
		struct less_operator_tag : less_has_smaller{};


		template<typename T>
		auto less_compare_impl(const T& lhs, const T& rhs, less_has_smaller)
			-> decltype(lhs < rhs)
		{
			return (lhs < rhs);
		}

		template<typename T>
		auto less_compare_impl(const T& lhs, const T& rhs, less_has_greater_E)
			-> decltype(lhs > rhs&& lhs == rhs)
		{
			if (lhs == rhs)
			{
				return false;
			}
			return !(lhs > rhs);
		}
		template<typename T>
		auto less_compare_impl(const T& lhs, const T& rhs, less_has_greater_NE)
			-> decltype(lhs > rhs && lhs != rhs)
		{
			if (lhs != rhs)
			{
				return !(lhs > rhs);
			}
			return false;
		}
		template<typename T>
		auto less_compare_impl(const T& lhs, const T& rhs, less_has_smaller_or_equal_E)
			->decltype(lhs <= rhs && lhs == rhs)
		{
			if (lhs == rhs)
			{
				return false;
			}
			return lhs <= rhs;
		}
		template<typename T>
		auto less_compare_impl(const T& lhs, const T& rhs, less_has_smaller_or_equal_NE)
			->decltype(lhs <= rhs && lhs != rhs)
		{
			if (lhs != rhs)
			{
				return lhs <= rhs;
			}
			return false;
		}
		template<typename T>
		auto less_compare_impl(const T& lhs, const T& rhs, less_has_greater_or_equal_E)
			->decltype(lhs >= rhs && lhs == rhs)
		{
			if (lhs == rhs)
			{
				return false;
			}
			return !(lhs >= rhs);
		}
		template<typename T>
		auto less_compare_impl(const T& lhs, const T& rhs, less_has_greater_or_equal_NE)
			->decltype(lhs >= rhs && lhs != rhs)
		{
			if (lhs != rhs)
			{
				return !(lhs >= rhs);
			}
			return false;
		}
		template<typename T>
		auto less_compare_impl(const T& lhs, const T& rhs, less_has_greater)
			-> decltype(lhs > rhs)
		{
			return !(lhs > rhs);
		}
		template<typename T>
		auto less_compare_impl(const T& lhs, const T& rhs, less_has_smaller_or_equal)
			-> decltype(lhs <= rhs)
		{
			return lhs <= rhs;
		}
		template<typename T>
		auto less_compare_impl(const T& lhs, const T& rhs, less_has_greater_or_equal)
			-> decltype(lhs >= rhs)
		{
			return !(lhs >= rhs);
		}
		template<typename T>
		auto less_compare_impl(const T& lhs, const T& rhs, less_no_operator)
			-> bool = delete;
		

		//Tag dispatch for grt_compare_impl fucntions to return TRUE if lhs > rhs or in bad cases lhs >= rhs
		struct grt_no_operator{};
		struct grt_has_smaller_or_equal : grt_no_operator{};
		struct grt_has_greater_or_equal : grt_has_smaller_or_equal{};
		struct grt_has_smaller : grt_has_greater_or_equal{};
		struct grt_has_smaller_or_equal_NE : grt_has_greater_or_equal{};
		struct grt_has_smaller_or_equal_E : grt_has_smaller_or_equal_NE{};
		struct grt_has_greater_or_equal_NE : grt_has_smaller_or_equal_E{};
		struct grt_has_greater_or_equal_E : grt_has_greater_or_equal_NE{};
		struct grt_has_smaller_NE : grt_has_greater_or_equal_E{};
		struct grt_has_smaller_E : grt_has_smaller_NE{};
		struct grt_has_greater : grt_has_smaller_E{};
		struct grt_operator_tag : grt_has_greater{};


		template<typename T>
		auto grt_compare_impl(const T& lhs, const T& rhs, grt_has_greater)
			-> decltype(lhs > rhs)
		{
			//std::cout << "min_element() lhs > rhs\n";
			return (lhs > rhs);
		}
		template<typename T>
		auto grt_compare_impl(const T& lhs, const T& rhs, grt_has_smaller_E)
			-> decltype(lhs < rhs && lhs == rhs)
		{
			//std::cout << "min_element() lhs < rhs && lhs == rhs\n";
			if (lhs == rhs)
			{
				return false;
			}
			return !(lhs < rhs);
		}
		template<typename T>
		auto grt_compare_impl(const T& lhs, const T& rhs, grt_has_smaller_NE)
			-> decltype(lhs < rhs&& lhs != rhs)
		{
			//std::cout << "min_element() lhs < rhs && lhs != rhs\n";
			if (lhs != rhs)
			{
				return !(lhs < rhs);
			}
			return false;
		}
		template<typename T>
		auto grt_compare_impl(const T& lhs, const T& rhs, grt_has_greater_or_equal_E)
			->decltype(lhs >= rhs && lhs == rhs)
		{
			//std::cout << "min_element() lhs >= rhs && lhs == rhs\n";
			if (lhs == rhs)
			{
				return false;
			}
			return lhs >= rhs;
		}
		template<typename T>
		auto grt_compare_impl(const T& lhs, const T& rhs, grt_has_greater_or_equal_NE)
			->decltype(lhs >= rhs && lhs != rhs)
		{
			//std::cout << "min_element() lhs >= rhs && lhs != rhs\n";
			if (lhs != rhs)
			{
				return lhs >= rhs;
			}
			return false;
		}
		template<typename T>
		auto grt_compare_impl(const T& lhs, const T& rhs, grt_has_smaller_or_equal_E)
			->decltype(lhs <= rhs && lhs == rhs)
		{
			//std::cout << "min_element() lhs <= rhs && lhs == rhs\n";
			if (lhs == rhs)
			{
				return false;
			}
			return !(lhs <= rhs);
		}
		template<typename T>
		auto grt_compare_impl(const T& lhs, const T& rhs, grt_has_smaller_or_equal_NE)
			->decltype(lhs <= rhs && lhs != rhs)
		{
			//std::cout << "min_element() lhs <= rhs && lhs != rhs\n";
			if (lhs != rhs)
			{
				return !(lhs <= rhs);
			}
			return false;
		}
		template<typename T>
		auto grt_compare_impl(const T& lhs, const T& rhs, grt_has_smaller)
			-> decltype(lhs < rhs)
		{
			//std::cout << "min_element() lhs < rhs\n";
			return !(lhs < rhs);
		}
		template<typename T>
		auto grt_compare_impl(const T& lhs, const T& rhs, grt_has_greater_or_equal)
			-> decltype(lhs >= rhs)
		{
			//std::cout << "min_element() lhs >= rhs\n";
			return lhs >= rhs;
		}
		template<typename T>
		auto grt_compare_impl(const T& lhs, const T& rhs, grt_has_smaller_or_equal)
			-> decltype(lhs <= rhs)
		{
			//std::cout << "min_element() lhs <= rhs\n";
			return !(lhs <= rhs);
		}
		template<typename T>
		auto grt_compare_impl(const T& lhs, const T& rhs, grt_no_operator)
			-> bool = delete;
	}

	template<typename T>
	struct equal_to
	{
		bool operator()(const T& lhs, const T& rhs) const
		{
			return details::equal_compare_impl(lhs, rhs, details::eql_operator_tag{});
		}
	};

	template<typename T>
	struct sort_partition_equal_to
	{
		bool operator()(const T& lhs, const T& rhs) const
		{
			return details::sort_partition_equal_compare_impl(lhs, rhs, details::sort_partition_eql_operator_tag{});
		}
	};

	template<typename T>
	struct not_equal_to
	{
		bool operator()(const T& lhs, const T& rhs) const
		{
			return details::not_equal_compare_impl(lhs, rhs, details::not_eql_operator_tag);
		}
	};

	template<typename T>
	struct less
	{
		bool operator()(const T& lhs, const T& rhs) const
		{
			return details::less_compare_impl(lhs, rhs, details::less_operator_tag{});
		}
	};

	template<typename T>
	struct greater
	{
		bool operator()(const T& lhs, const T& rhs) const
		{
			return details::grt_compare_impl(lhs, rhs, details::grt_operator_tag{});
		}
	};

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
