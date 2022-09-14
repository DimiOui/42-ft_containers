#ifndef REVERSE_ITERATOR_HPP
# define REVERSE_ITERATOR_HPP

#pragma once

#include "iterator_traits.hpp"
#include "map_iterator.hpp"

namespace ft
{
	template <class Iterator>
	class reverse_iterator
	{
		public:
			typedef Iterator	iterator_type;
			typedef typename iterator_traits<Iterator>::iterator_category	iterator_category;
			typedef typename iterator_traits<Iterator>::value_type			value_type;
			typedef typename iterator_traits<Iterator>::difference_type		difference_type;
			typedef typename iterator_traits<Iterator>::pointer				pointer;
			typedef typename iterator_traits<Iterator>::reference			reference;

	// MEMBER FUNCTIONS
			reverse_iterator() : _base_it() {}
			explicit reverse_iterator(iterator_type it) : _base_it(it) {}
			template <class Iter>
			reverse_iterator(const reverse_iterator<Iter>& rev_it) : _base_it(rev_it.base()) {}

			iterator_type base() const { return (this->_base_it); }

			reference 			operator*() const
			{
				iterator_type	temp = _base_it;
				return *(--temp);
			}

			reverse_iterator	operator+ (difference_type n) const
			{
				return (reverse_iterator<Iterator>(_base_it - n));
			}

			reverse_iterator&	operator++()
			{
				_base_it--;
				return (*this);
			}

			reverse_iterator	operator++(int)
			{
				reverse_iterator	temp = *this;
				++(*this);
				return (temp);
			}

			reverse_iterator&	operator+= (difference_type n)
			{
				_base_it -= n;
				return (*this);
			}

			reverse_iterator	operator- (difference_type n) const
			{
				return (reverse_iterator<Iterator>(_base_it + n));
			}

			reverse_iterator&	operator--()
			{
				_base_it++;
				return (*this);
			}

			reverse_iterator	operator--(int)
			{
				reverse_iterator	temp = *this;
				--(*this);
				return (temp);
			}

			reverse_iterator&	operator-= (difference_type n)
			{
				_base_it += n;
				return (*this);
			}

			pointer				operator->() const
			{
				return &(operator*());
			}

			reference			operator[] (difference_type n) const
			{
				return (_base_it[-n - 1]);
			}

		protected:
			iterator_type		_base_it;

	};
	// NON-MEMBER FUNCTIONS
	template <class Iterator>
	bool operator== (const reverse_iterator<Iterator>& lhs,
					const reverse_iterator<Iterator>& rhs)
	{
		return (lhs.base() == rhs.base());
	}
	template <class Iterator>
	bool operator!= (const reverse_iterator<Iterator>& lhs,
					const reverse_iterator<Iterator>& rhs)
	{
		return (lhs.base() != rhs.base());
	}
	template <class Iterator>
	bool operator< (const reverse_iterator<Iterator>& lhs,
					const reverse_iterator<Iterator>& rhs)
	{
		return (lhs.base() > rhs.base());
	}
	template <class Iterator>
	bool operator<= (const reverse_iterator<Iterator>& lhs,
					const reverse_iterator<Iterator>& rhs)
	{
		return (lhs.base() >= rhs.base());
	}
	template <class Iterator>
	bool operator> (const reverse_iterator<Iterator>& lhs,
					const reverse_iterator<Iterator>& rhs)
	{
		return (lhs.base() < rhs.base());
	}
	template <class Iterator>
	bool operator>= (const reverse_iterator<Iterator>& lhs,
					const reverse_iterator<Iterator>& rhs)
	{
		return (lhs.base() <= rhs.base());
	}

	template <class Iterator>
	reverse_iterator<Iterator> operator+
			(typename reverse_iterator<Iterator>::difference_type n,
			const reverse_iterator<Iterator>& rev_it)
	{
		return (reverse_iterator<Iterator>(rev_it.base() - n));
	}

	template <class Iterator>
	typename reverse_iterator<Iterator>::difference_type operator-
			(const reverse_iterator<Iterator>& lhs,
			const reverse_iterator<Iterator>& rhs)
	{
		return rhs.base() - lhs.base();
	}
}

// https://legacy.cplusplus.com/reference/iterator/reverse_iterator/?kw=reverse_iterator

#endif
