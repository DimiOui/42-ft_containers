#ifndef REVERSE_ITERATOR_HPP
# define REVERSE_ITERATOR_HPP

#pragma once

#include "iterator_traits.hpp"

namespace ft
{
	template <class Iterator>
	class reverse_iterator
	{
		public:
			typedef Iterator	iterator_type; //not sure
			typedef typename iterator_traits<Iterator>::iterator_category	iterator_category;
			typedef typename iterator_traits<Iterator>::value_type			value_type;
			typedef typename iterator_traits<Iterator>::difference_type		difference_type;
			typedef typename iterator_traits<Iterator>::pointer				pointer;
			typedef typename iterator_traits<Iterator>::reference			reference;

	// MEMBER FUNCTIONS
			//	constructors
			reverse_iterator() {}
			explicit reverse_iterator(iterator_type it) {}
			template <class Iter>
			reverse_iterator(const reverse_iterator<Iter>& rev_it) {}

			//	base
			iterator_type base() const {}

			//	operators
			reference 			operator*() const {}
			reverse_iterator	operator+ (difference_type n) const {}
			reverse_iterator&	operator++() {}
			reverse_iterator	operator++(int) {}
			reverse_iterator&	operator+= (difference_type n) {}
			reverse_iterator	operator- (difference_type n) const {}
			reverse_iterator&	operator--() {}
			reverse_iterator	operator--(int) {}
			reverse_iterator&	operator-= (difference_type n) {}
			pointer				operator->() const {}
			reference			operator[] (difference_type n) const {}

	};
	// NON-MEMBER FUNCTIONS
	//relational operators
	template <class Iterator>
	bool operator== (const reverse_iterator<Iterator>& lhs, const reverse_iterator<Iterator>& rhs);
	template <class Iterator>
	bool operator!= (const reverse_iterator<Iterator>& lhs, const reverse_iterator<Iterator>& rhs);
	template <class Iterator>
	bool operator< (const reverse_iterator<Iterator>& lhs, const reverse_iterator<Iterator>& rhs);
	template <class Iterator>
	bool operator<= (const reverse_iterator<Iterator>& lhs, const reverse_iterator<Iterator>& rhs);
	template <class Iterator>
	bool operator> (const reverse_iterator<Iterator>& lhs, const reverse_iterator<Iterator>& rhs);
	template <class Iterator>
	bool operator>= (const reverse_iterator<Iterator>& lhs, const reverse_iterator<Iterator>& rhs);
	//operator +
	template <class Iterator>
	reverse_iterator<Iterator> operator+ (typename reverse_iterator<Iterator>::difference_type n,
														const reverse_iterator<Iterator>& rev_it);
	//operator -
	template <class Iterator>
	typename reverse_iterator<Iterator>::difference_type operator- (const reverse_iterator<Iterator>& lhs,
																const reverse_iterator<Iterator>& rhs);
}

// https://legacy.cplusplus.com/reference/iterator/reverse_iterator/?kw=reverse_iterator

#endif
