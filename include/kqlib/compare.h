#ifndef KQCOMPARE_
#define KQCOMPARE_

namespace kq
{

	template<typename T>
	struct equal_to
	{
		bool operator()(const T& lhs, const T& rhs) const
		{
			return lhs == rhs;
		}
	};

	template<typename T>
	struct not_equal_to
	{
		bool operator()(const T& lhs, const T& rhs) const
		{
			return lhs != rhs;
		}
	};

	template<typename T>
	struct less
	{
		bool operator()(const T& lhs, const T& rhs) const
		{
			return lhs < rhs;
		}
	};

	template<typename T>
	struct greater
	{
		bool operator()(const T& lhs, const T& rhs) const
		{
			return lhs > rhs;
		}
	};

	template<typename T>
	struct less_equal
	{
		bool operator()(const T& lhs, const T& rhs) const
		{
			return lhs <= rhs;
		}
	};

	template<typename T>
	struct greater_equal
	{
		bool operator()(const T& lhs, const T& rhs) const
		{
			return lhs >= rhs;
		}
	};

}

#endif