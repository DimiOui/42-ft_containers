#ifndef VECTOR_ITERATOR_HPP
# define VECTOR_ITERATOR_HPP

#pragma once

#include "iterator_traits.hpp"

namespace ft
{
	template <class T, class Category = std::random_access_iterator_tag,
		class Distance = ptrdiff_t, class Pointer = T*, class Reference = T&>
	class vector_iterator
	{
			//	MEMBER TYPES
		public:
			typedef Category iterator_category;
			typedef T value_type;
			typedef Distance difference_type;
			typedef Pointer pointer;
			typedef Reference reference;

			//	MEMBER FUNCTIONS
			vector_iterator() : _iptr() {}
			vector_iterator(pointer ptr) : _iptr(ptr) {}
			vector_iterator(const vector_iterator &ptr) {_iptr.get_pointer();}
			~vector_iterator() {}

			reference			operator*() const {return (*_iptr);}
			vector_iterator		operator+ (difference_type n) const {return vector_iterator(_iptr + n);}
			vector_iterator		&operator++()
			{
				++_iptr;
				return (*this);
			}

			vector_iterator		operator++(int)
			{
				vector_iterator	temp = *this;
				(*this)++;
				return (temp);
			}

			vector_iterator		&operator+= (difference_type n)
			{
				_iptr += n;
				return (*this);
			}

			vector_iterator		operator- (difference_type n) const {return vector_iterator(_iptr - n);}

			vector_iterator&	operator--()
			{
				--_iptr;
				return (*this);
			}

			vector_iterator		operator--(int)
			{
				vector_iterator	temp = *this;
				(*this)--;
				return (temp);
			}

			vector_iterator		operator-= (difference_type n)
			{
				_iptr -= n;
				return (*this);
			}
			
			pointer				operator->() const {return (_iptr);}
			reference			operator[] (difference_type n) const {return (_iptr[n]);}

			vector_iterator		&operator=(const vector_iterator &x)
			{
				if (this != &x)
					_iptr = x.get_pointer();
				return (*this);
			}

			pointer				get_pointer() const {return (_iptr);}

		protected:
			pointer	_iptr;
	};
	//	NON-MEMBER FUNCTIONS
	template <class Iterator>
	bool operator== (const vector_iterator<Iterator>& lhs,
					const vector_iterator<Iterator>& rhs)
	{
		return (lhs.base() == rhs.base());
	}
	template <class Iterator>
	bool operator!= (const vector_iterator<Iterator>& lhs,
					const vector_iterator<Iterator>& rhs)
	{
		return (lhs.base() != rhs.base());
	}
	template <class Iterator>
	bool operator< (const vector_iterator<Iterator>& lhs,
					const vector_iterator<Iterator>& rhs)
	{
		return (lhs.base() > rhs.base());
	}
	template <class Iterator>
	bool operator<= (const vector_iterator<Iterator>& lhs,
					const vector_iterator<Iterator>& rhs)
	{
		return (lhs.base() >= rhs.base());
	}
	template <class Iterator>
	bool operator> (const vector_iterator<Iterator>& lhs,
					const vector_iterator<Iterator>& rhs)
	{
		return (lhs.base() < rhs.base());
	}
	template <class Iterator>
	bool operator>= (const vector_iterator<Iterator>& lhs,
					const vector_iterator<Iterator>& rhs)
	{
		return (lhs.base() <= rhs.base());
	}

	template <class Iterator>
	vector_iterator<Iterator> operator+
			(typename vector_iterator<Iterator>::difference_type n,
			const vector_iterator<Iterator>& rev_it)
	{
		return (vector_iterator<Iterator>(rev_it.base() - n));
	}

	template <class Iterator>
	typename vector_iterator<Iterator>::difference_type operator-
			(const vector_iterator<Iterator>& lhs,
			const vector_iterator<Iterator>& rhs)
	{
		return rhs.base() - lhs.base();
	}
}

//	https://legacy.cplusplus.com/reference/iterator/iterator/

#endif
