#ifndef kqpair_
#define kqpair_

#include "other.h"

namespace kq 
{
		
		template<typename fT, typename sT>
		struct pair
		{
		public:

			using first_type = fT;
			using second_type = sT;

			pair() : first(), second() {}
			pair(const pair& other) : first(other.first), second(other.second) {}
			pair(pair&& other) noexcept : first(std::move(other.first)), second(std::move(other.second))  {}
			pair(const first_type& f, const second_type& s) : first(f), second(s) {}
			pair(const first_type& f, second_type&& s) : first(f), second(std::move(s)) {}
			pair(first_type&& f, const second_type& s) : first(std::move(f)), second(s) {}
			pair(first_type&& f, second_type&& s) : first(std::move(f)), second(std::move(s)) {}

			pair& operator=(const pair& other) { first = other.first; second = other.second; }
			pair& operator=(pair&& other) noexcept { first = std::move(other.first); second = std::move(other.second); }

			bool operator==(const pair& other) const;
			bool operator!=(const pair& other) const;

			first_type first;
			second_type second;
		};

		template<typename first_type, typename second_type>
		pair<first_type, second_type> make_pair(const first_type& f,const second_type& s)
		{
			return pair<first_type, second_type>(f, s);
		}

		template<typename fT, typename sT>
		bool pair<fT, sT>::operator==(const pair<fT, sT>& other) const
		{
			return (equal_compare_impl(first, other.first) && equal_compare_impl(second, other.second));
		}

		template<typename fT, typename sT>
		bool pair<fT, sT>::operator!=(const pair<fT, sT>& other) const
		{
			return !(equal_compare_impl(first, other.first) && equal_compare_impl(second, other.second));
		}

}



#endif