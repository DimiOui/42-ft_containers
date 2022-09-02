#ifndef PAIR_HPP
# define PAIR_HPP

#pragma once

namespace ft
{
	template <class T1, class T2>
	struct pair
	{
		typedef T1	first_type;
		typedef T2	second_type;

	//	MEMBER FUNCTIONS
		pair() {}
		template<class U, class V>
		pair(const pair<U,V>& pr) {}
		pair(const first_type& a, const second_type& b) {}

		pair& operator=(const pair& pr) {}
	};
	//	MAKE PAIR
	template <class T1, class T2>
	pair<T1,T2> make_pair (T1 x, T2 y) {}

	//	NON-MEMBER OVERLOADS
	template <class T1, class T2>
	bool operator== (const pair<T1,T2>& lhs, const pair<T1,T2>& rhs) {}
	template <class T1, class T2>
	bool operator!= (const pair<T1,T2>& lhs, const pair<T1,T2>& rhs) {}
	template <class T1, class T2>
	bool operator< (const pair<T1,T2>& lhs, const pair<T1,T2>& rhs) {}
	template <class T1, class T2>
	bool operator<= (const pair<T1,T2>& lhs, const pair<T1,T2>& rhs) {}
	template <class T1, class T2>
	bool operator> (const pair<T1,T2>& lhs, const pair<T1,T2>& rhs) {}
	template <class T1, class T2>
	bool operator>= (const pair<T1,T2>& lhs, const pair<T1,T2>& rhs) {}
}

//	https://legacy.cplusplus.com/reference/utility/pair/
//	https://legacy.cplusplus.com/reference/utility/make_pair/

#endif
