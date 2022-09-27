#ifndef VECTOR_ITERATOR_HPP
#define VECTOR_ITERATOR_HPP

#pragma once

#include "iterator_traits.hpp"
#include "reverse_iterator.hpp"

namespace ft
{
	template <class T, class Category = std::random_access_iterator_tag,
			  class Distance = ptrdiff_t, class Pointer = T *, class Reference = T &>
	class vector_iterator
	{
	public:
		//	MEMBER TYPES
		typedef Category iterator_category;
		typedef T value_type;
		typedef Distance difference_type;
		typedef Pointer pointer;
		typedef Reference reference;

		//	MEMBER FUNCTIONS
		vector_iterator() : _base_it() {}
		vector_iterator(pointer ptr) : _base_it(ptr) {}
		vector_iterator(const reference ref) { _base_it = ref.get_pointer(); }
		~vector_iterator() {}

		operator vector_iterator<const T>() const
		{
			return (vector_iterator<const T>(this->_base_it));
		}

		vector_iterator &operator=(const vector_iterator<const T> &x)
		{
			if (this != &x)
				_base_it = x.get_pointer();
			return (*this);
		}

		reference operator*() { return (*_base_it); }

		vector_iterator operator+(difference_type n) const
		{
			return vector_iterator(_base_it + n);
		}

		friend difference_type operator+(vector_iterator x, vector_iterator y)
		{
			return (x._base_it + y._base_it);
		}

		friend vector_iterator	operator+(std::ptrdiff_t n, vector_iterator x)
		{
			vector_iterator temp(x.get_pointer());
			temp += n;
			return (temp);
		 }

		vector_iterator &operator++()
		{
			_base_it++;
			return (*this);
		}

		vector_iterator operator++(int)
		{
			vector_iterator temp(*this);
			operator++();
			return (temp);
		}

		vector_iterator &operator+=(difference_type n)
		{
			_base_it += n;
			return (*this);
		}

		vector_iterator operator-(difference_type n) const
		{
			return vector_iterator(_base_it - n);
		}

		friend difference_type operator-(vector_iterator x, vector_iterator y)
		{
			return (x._base_it - y._base_it);
		}

		friend vector_iterator	operator-(std::ptrdiff_t n, vector_iterator x)
		{
			vector_iterator temp(x.get_pointer());
			temp -= n;
			return (temp);
		}

		vector_iterator &operator--()
		{
			_base_it--;
			return (*this);
		}

		vector_iterator operator--(int)
		{
			vector_iterator temp(*this);
			operator--();
			return (temp);
		}

		vector_iterator operator-=(difference_type n)
		{
			_base_it -= n;
			return (*this);
		}

		pointer operator->() { return (_base_it); }

		reference operator[](difference_type n) const { return (_base_it[n]); }

		pointer get_pointer() const { return (_base_it); }

		//	COMPARISON
		bool operator==(const vector_iterator<const T> &x) const
		{
			return (_base_it == x.get_pointer());
		}

		bool operator!=(const vector_iterator<const T> &x) const
		{
			return (_base_it != x.get_pointer());
		}

		bool operator>(const vector_iterator<const T> &x) const
		{
			return (_base_it > x.get_pointer());
		}

		bool operator>=(const vector_iterator<const T> &x) const
		{
			return (_base_it >= x.get_pointer());
		}

		bool operator<(const vector_iterator<const T> &x) const
		{
			return (_base_it < x.get_pointer());
		}

		bool operator<=(const vector_iterator<const T> &x) const
		{
			return (_base_it <= x.get_pointer());
		}

	protected:
		pointer _base_it;
	};
}

//	https://legacy.cplusplus.com/reference/iterator/iterator/

#endif
