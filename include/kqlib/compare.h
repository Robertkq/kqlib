#ifndef KQCOMPARE_
#define KQCOMPARE_

namespace kq
{

	namespace details
	{
		//Tag dispatch for equal_compare_impl functions for returning lhs == rhs using best available operators
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

		//Tag dispatch for less_compare_impl functions for returning lhs != rhs using best available operators
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

		//Tag dispatch for less_compare_impl functions to return for returning lhs < rhs using best available operators
		struct less_no_operator {};
		struct less_greater_or_equal : less_no_operator {};
		struct less_smaller_or_equal : less_greater_or_equal {};
		struct less_greater : less_smaller_or_equal {};
		struct less_greater_or_equal_NE : less_greater {};
		struct less_greater_or_equal_E : less_greater_or_equal_NE {};
		struct less_smaller_or_equal_NE : less_greater_or_equal_E {};
		struct less_smaller_or_equal_E : less_smaller_or_equal_NE {};
		struct less_greater_NE : less_smaller_or_equal_E {};
		struct less_greater_E : less_greater_NE {};
		struct less_smaller : less_greater_E {};
		struct less_operator_tag : less_smaller {};


		template<typename T>
		auto less_compare_impl(const T& lhs, const T& rhs, less_smaller)
			-> decltype(lhs < rhs)
		{
			return (lhs < rhs);
		}

		template<typename T>
		auto less_compare_impl(const T& lhs, const T& rhs, less_greater_E)
			-> decltype(lhs > rhs && lhs == rhs)
		{
			if (lhs == rhs)
			{
				return false;
			}
			return !(lhs > rhs);
		}
		template<typename T>
		auto less_compare_impl(const T& lhs, const T& rhs, less_greater_NE)
			-> decltype(lhs > rhs&& lhs != rhs)
		{
			if (lhs != rhs)
			{
				return !(lhs > rhs);
			}
			return false;
		}
		template<typename T>
		auto less_compare_impl(const T& lhs, const T& rhs, less_smaller_or_equal_E)
			->decltype(lhs <= rhs && lhs == rhs)
		{
			if (lhs == rhs)
			{
				return false;
			}
			return lhs <= rhs;
		}
		template<typename T>
		auto less_compare_impl(const T& lhs, const T& rhs, less_smaller_or_equal_NE)
			->decltype(lhs <= rhs && lhs != rhs)
		{
			if (lhs != rhs)
			{
				return lhs <= rhs;
			}
			return false;
		}
		template<typename T>
		auto less_compare_impl(const T& lhs, const T& rhs, less_greater_or_equal_E)
			->decltype(lhs >= rhs && lhs == rhs)
		{
			if (lhs == rhs)
			{
				return false;
			}
			return !(lhs >= rhs);
		}
		template<typename T>
		auto less_compare_impl(const T& lhs, const T& rhs, less_greater_or_equal_NE)
			->decltype(lhs >= rhs && lhs != rhs)
		{
			if (lhs != rhs)
			{
				return !(lhs >= rhs);
			}
			return false;
		}
		template<typename T>
		auto less_compare_impl(const T& lhs, const T& rhs, less_greater)
			-> decltype(lhs > rhs)
		{
			return !(lhs > rhs);
		}
		template<typename T>
		auto less_compare_impl(const T& lhs, const T& rhs, less_smaller_or_equal)
			-> decltype(lhs <= rhs)
		{
			return lhs <= rhs;
		}
		template<typename T>
		auto less_compare_impl(const T& lhs, const T& rhs, less_greater_or_equal)
			-> decltype(lhs >= rhs)
		{
			return !(lhs >= rhs);
		}
		template<typename T>
		auto less_compare_impl(const T& lhs, const T& rhs, less_no_operator)
			-> bool = delete;


		//Tag dispatch for grt_compare_impl functions for returning lhs > rhs using best available operators
		struct grt_no_operator {};
		struct grt_smaller_or_equal : grt_no_operator {};
		struct grt_greater_or_equal : grt_smaller_or_equal {};
		struct grt_smaller : grt_greater_or_equal {};
		struct grt_smaller_or_equal_NE : grt_smaller {};
		struct grt_smaller_or_equal_E : grt_smaller_or_equal_NE {};
		struct grt_greater_or_equal_NE : grt_smaller_or_equal_E {};
		struct grt_greater_or_equal_E : grt_greater_or_equal_NE {};
		struct grt_smaller_NE : grt_greater_or_equal_E {};
		struct grt_smaller_E : grt_smaller_NE {};
		struct grt_greater : grt_smaller_E {};
		struct grt_operator_tag : grt_greater {};


		template<typename T>
		auto grt_compare_impl(const T& lhs, const T& rhs, grt_greater)
			-> decltype(lhs > rhs)
		{
			//std::cout << "min_element() lhs > rhs\n";
			return (lhs > rhs);
		}
		template<typename T>
		auto grt_compare_impl(const T& lhs, const T& rhs, grt_smaller_E)
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
		auto grt_compare_impl(const T& lhs, const T& rhs, grt_smaller_NE)
			-> decltype(lhs < rhs && lhs != rhs)
		{
			//std::cout << "min_element() lhs < rhs && lhs != rhs\n";
			if (lhs != rhs)
			{
				return !(lhs < rhs);
			}
			return false;
		}
		template<typename T>
		auto grt_compare_impl(const T& lhs, const T& rhs, grt_greater_or_equal_E)
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
		auto grt_compare_impl(const T& lhs, const T& rhs, grt_greater_or_equal_NE)
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
		auto grt_compare_impl(const T& lhs, const T& rhs, grt_smaller_or_equal_E)
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
		auto grt_compare_impl(const T& lhs, const T& rhs, grt_smaller_or_equal_NE)
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
		auto grt_compare_impl(const T& lhs, const T& rhs, grt_smaller)
			-> decltype(lhs < rhs)
		{
			//std::cout << "min_element() lhs < rhs\n";
			return !(lhs < rhs);
		}
		template<typename T>
		auto grt_compare_impl(const T& lhs, const T& rhs, grt_greater_or_equal)
			-> decltype(lhs >= rhs)
		{
			//std::cout << "min_element() lhs >= rhs\n";
			return lhs >= rhs;
		}
		template<typename T>
		auto grt_compare_impl(const T& lhs, const T& rhs, grt_smaller_or_equal)
			-> decltype(lhs <= rhs)
		{
			//std::cout << "min_element() lhs <= rhs\n";
			return !(lhs <= rhs);
		}
		template<typename T>
		auto grt_compare_impl(const T& lhs, const T& rhs, grt_no_operator)
			-> bool = delete;

		//Tag dispatch for less_equal_compare_impl functions returning lhs <= rhs using best available operators
		struct less_equal_no_operator {};
		struct less_equal_greater_NE : less_equal_no_operator {};
		struct less_equal_greater_E : less_equal_greater_NE {};
		struct less_equal_less_NE : less_equal_greater_E {};
		struct less_equal_less_E : less_equal_less_NE {};
		struct less_equal_greater_or_equal : less_equal_less_E {};
		struct less_equal_less_or_equal : less_equal_greater_or_equal {};
		struct less_equal_operator_tag : less_equal_less_or_equal {};

		template<typename T>
		auto less_equal_compare_impl(const T& lhs, const T& rhs, less_equal_less_or_equal)
			-> decltype(lhs <= rhs)
		{
			return lhs <= rhs;
		}

		template<typename T>
		auto less_equal_compare_impl(const T& lhs, const T& rhs, less_equal_greater_or_equal)
			-> decltype(lhs >= rhs)
		{
			return !(lhs >= rhs);
		}

		template<typename T>
		auto less_equal_compare_impl(const T& lhs, const T& rhs, less_equal_less_E)
			-> decltype(lhs < rhs && lhs == rhs)
		{
			if (lhs == rhs)
			{
				return true;
			}
			return lhs < rhs;
		}

		template<typename T>
		auto less_equal_compare_impl(const T& lhs, const T& rhs, less_equal_less_NE)
			-> decltype(lhs < rhs && lhs != rhs)
		{
			if (lhs != rhs)
			{
				return  lhs < rhs;
			}
			return true;
		}

		template<typename T>
		auto less_equal_compare_impl(const T& lhs, const T& rhs, less_equal_greater_E)
			-> decltype(lhs > rhs && lhs == rhs)
		{
			if (lhs == rhs)
			{
				return true;
			}
			return !(lhs > rhs);
		}

		template<typename T>
		auto less_equal_compare_impl(const T& lhs, const T& rhs, less_equal_greater_NE)
			-> decltype(lhs > rhs && lhs != rhs)
		{
			if (lhs != rhs)
			{
				return !(lhs > rhs);
			}
			return true;
		}

		template<typename T>
		auto less_equal_compare_impl(const T& lhs, const T& rhs, less_equal_no_operator)
			-> bool = delete;

		//Tag dispatch for less_equal_compare_impl functions returning lhs >= rhs using best available operators
		struct greater_equal_no_operator {};
		struct greater_equal_less_NE : greater_equal_no_operator {};
		struct greater_equal_less_E : greater_equal_less_NE {};
		struct greater_equal_greater_NE : greater_equal_less_E {};
		struct greater_equal_greater_E : greater_equal_greater_NE {};
		struct greater_equal_less_or_equal : greater_equal_greater_E {};
		struct greater_equal_greater_or_equal : greater_equal_less_or_equal {};
		struct greater_equal_operator_tag : greater_equal_greater_or_equal {};

		template<typename T>
		auto greater_equal_compare_impl(const T& lhs, const T& rhs, greater_equal_greater_or_equal)
			-> decltype(lhs >= rhs)
		{
			return lhs >= rhs;
		}

		template<typename T>
		auto greater_equal_compare_impl(const T& lhs, const T& rhs, greater_equal_less_or_equal)
			-> decltype(lhs <= rhs)
		{
			return !(lhs <= rhs);
		}

		template<typename T>
		auto greater_equal_compare_impl(const T& lhs, const T& rhs, greater_equal_greater_E)
			-> decltype (lhs > rhs && lhs == rhs)
		{
			if (lhs == rhs)
			{
				return true;
			}
			return lhs > rhs;
		}

		template<typename T>
		auto greater_equal_compare_impl(const T& lhs, const T& rhs, greater_equal_greater_NE)
			-> decltype (lhs > rhs && lhs != rhs)
		{
			if (lhs != rhs)
			{
				return lhs > rhs;
			}
			return true;
		}

		template<typename T>
		auto greater_equal_compare_impl(const T& lhs, const T& rhs, greater_equal_less_E)
			-> decltype (lhs < rhs && lhs == rhs)
		{
			if (lhs == rhs)
			{
				return true;
			}
			return !(lhs < rhs);
		}

		template<typename T>
		auto greater_equal_compare_impl(const T& lhs, const T& rhs, greater_equal_less_NE)
			-> decltype (lhs < rhs && lhs != rhs)
		{
			if (lhs != rhs)
			{
				return !(lhs < rhs);
			}
			return true;
		}

		template<typename T>
		auto greater_equal_compare_impl(const T& lhs, const T& rhs, greater_equal_no_operator)
			-> bool = delete;

	} // namespace details

	template<typename T>
	struct equal_to
	{
		bool operator()(const T& lhs, const T& rhs) const
		{
			return details::equal_compare_impl(lhs, rhs, details::eql_operator_tag{});
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

	template<typename T>
	struct less_equal
	{
		bool operator()(const T& lhs, const T& rhs) const
		{
			return details::less_equal_compare_impl(lhs, rhs, details::less_equal_operator_tag);
		}
	};

	template<typename T>
	struct greater_equal
	{
		bool operator()(const T& lhs, const T& rhs) const
		{
			return details::greater_equal_compare_impl(lhs, rhs, details::greater_equal_operator_tag);
		}
	};

}

#endif