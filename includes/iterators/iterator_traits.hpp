#ifndef ITERATOR_TRAITS_HPP
#define ITERATOR_TRAITS_HPP

//	Iterator_traits defines the properties of iterators, any custom class with
//	"ft::iterator" will inherits from iterator_traits

#pragma once

#include <cstddef>
#include <iterator>

namespace ft
{
	template <class Iterator>
	class iterator_traits
	{
	public:
		typedef typename Iterator::difference_type difference_type;
		typedef typename Iterator::value_type value_type;
		typedef typename Iterator::pointer pointer;
		typedef typename Iterator::reference reference;
		typedef typename Iterator::iterator_category iterator_category;
	};

	template <class T>
	class iterator_traits<T *>
	{
	public:
		typedef ptrdiff_t difference_type;
		typedef T value_type;
		typedef T *pointer;
		typedef T &reference;
		typedef std::random_access_iterator_tag iterator_category;
	};
	template <class T>
	class iterator_traits<const T *>
	{
	public:
		typedef ptrdiff_t difference_type;
		typedef T value_type;
		typedef const T *pointer;
		typedef const T &reference;
		typedef std::random_access_iterator_tag iterator_category;
	};
}

//	typedef typename lets the compiler know that "***_type" is a type and not a static member
//	of Iterator.

#endif
