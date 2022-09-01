#ifndef test
#define test

namespace kq
{

	namespace details
	{
		//Tag dispatch for equal_compare_impl functions to return TRUE if lhs == rhs
		struct eql_no_operator {};
		struct eql_not_equal : eql_no_operator {};
		struct eql_equal : eql_not_equal {};
		struct eql_operator_tag : eql_equal {};


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
		struct not_eql_not_equal : not_eql_equal {};
		struct not_eql_operator_tag : not_eql_not_equal {};

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
		struct less_no_operator {};
		struct less_has_greater_or_equal : less_no_operator {};
		struct less_has_smaller_or_equal : less_has_greater_or_equal {};
		struct less_has_greater : less_has_smaller_or_equal {};
		struct less_has_greater_or_equal_NE : less_has_greater {};
		struct less_has_greater_or_equal_E : less_has_greater_or_equal_NE {};
		struct less_has_smaller_or_equal_NE : less_has_greater_or_equal_NE {};
		struct less_has_smaller_or_equal_E : less_has_smaller_or_equal_NE {};
		struct less_has_greater_NE : less_has_smaller_or_equal_E {};
		struct less_has_greater_E : less_has_greater_NE {};
		struct less_has_smaller : less_has_greater_E {};
		struct less_operator_tag : less_has_smaller {};


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
			-> decltype(lhs > rhs&& lhs != rhs)
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
		struct grt_no_operator {};
		struct grt_has_smaller_or_equal : grt_no_operator {};
		struct grt_has_greater_or_equal : grt_has_smaller_or_equal {};
		struct grt_has_smaller : grt_has_greater_or_equal {};
		struct grt_has_smaller_or_equal_NE : grt_has_greater_or_equal {};
		struct grt_has_smaller_or_equal_E : grt_has_smaller_or_equal_NE {};
		struct grt_has_greater_or_equal_NE : grt_has_smaller_or_equal_E {};
		struct grt_has_greater_or_equal_E : grt_has_greater_or_equal_NE {};
		struct grt_has_smaller_NE : grt_has_greater_or_equal_E {};
		struct grt_has_smaller_E : grt_has_smaller_NE {};
		struct grt_has_greater : grt_has_smaller_E {};
		struct grt_operator_tag : grt_has_greater {};


		template<typename T>
		auto grt_compare_impl(const T& lhs, const T& rhs, grt_has_greater)
			-> decltype(lhs > rhs)
		{
			//std::cout << "min_element() lhs > rhs\n";
			return (lhs > rhs);
		}
		template<typename T>
		auto grt_compare_impl(const T& lhs, const T& rhs, grt_has_smaller_E)
			-> decltype(lhs < rhs&& lhs == rhs)
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

}

#endif