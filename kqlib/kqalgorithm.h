#ifndef kqalgorithm_
#define kqalgorithm_

#include "kqother.h"

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
			-> decltype(lhs == rhs)
		{
			return !(lhs != rhs);
		}
		template<typename T>
		auto equal_compare_impl(const T& lhs, const T& rhs, eql_no_operator)
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
			//std::cout << "max_element() lhs < rhs\n";
			return (lhs < rhs);
		}
		template<typename T>
		auto less_compare_impl(const T& lhs, const T& rhs, less_has_greater_E)
			-> decltype(lhs > rhs&& lhs == rhs)
		{
			//std::cout << "max_element() lhs > rhs && lhs == rhs\n";
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
			//std::cout << "max_element() lhs > rhs && lhs != rhs\n";
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
			//std::cout << "max_element() lhs <= rhs && lhs == rhs\n";
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
			//std::cout << "max_element() lhs <= rhs && lhs != rhs\n";
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
			//std::cout << "max_element() lhs >= rhs && lhs == rhs\n";
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
			//std::cout << "max_element() lhs >= rhs && lhs != rhs\n";
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
			//std::cout << "max_element() lhs > rhs\n";
			return !(lhs > rhs);
		}
		template<typename T>
		auto less_compare_impl(const T& lhs, const T& rhs, less_has_smaller_or_equal)
			-> decltype(lhs <= rhs)
		{
			//std::cout << "max_element() lhs <= rhs\n";
			return lhs <= rhs;
		}
		template<typename T>
		auto less_compare_impl(const T& lhs, const T& rhs, less_has_greater_or_equal)
			-> decltype(lhs >= rhs)
		{
			//std::cout << "max_element() lhs >= rhs\n";
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

	template<typename iterType, typename T>
	constexpr iterType find(iterType first, iterType last, const T& value)
	{
		for (; first != last; ++first)
		{
			if (details::equal_compare_impl(*first, value, details::eql_operator_tag{}))
			{
				return first;
			}
		}
		return last;
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
			//std::cout << "\n=== sort_partition(" << *first << ", " << *last << ")\n";
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
			//std::cout << "comp(" << *first << ", " << *pivot << ")\n";
			if (comp(*first, *pivot))
			{
				++smaller;
				//std::cout << "Swap between " << *smaller << " & " << *first << "\n";
				if (!(equal_compare_impl(*smaller, *first, details::eql_operator_tag{})))
				{
					swap(*smaller, *first);
				}

			}
		}
		++smaller;
		//std::cout << "Last Swap between " << *smaller << " & " << *first << "\n";
		if (!(equal_compare_impl(*smaller, *pivot, details::eql_operator_tag{})))
		{
			swap(*smaller, *pivot);
		}
		return smaller;
	}

}
#endif
