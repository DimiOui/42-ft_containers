#ifndef REVERSE_ITERATOR_HPP
#define REVERSE_ITERATOR_HPP

#pragma once

#include "iterator_traits.hpp"

namespace ft
{
	template <class Iterator>
	class reverse_iterator
	{
	public:
		typedef Iterator iterator_type;
		typedef typename iterator_traits<Iterator>::iterator_category iterator_category;
		typedef typename iterator_traits<Iterator>::value_type value_type;
		typedef typename iterator_traits<Iterator>::difference_type difference_type;
		typedef typename iterator_traits<Iterator>::pointer pointer;
		typedef typename iterator_traits<Iterator>::reference reference;

		// MEMBER FUNCTIONS
		reverse_iterator() : _base_it() {}
		explicit reverse_iterator(iterator_type x) : _base_it(x) {}
		template <class Iter>
		reverse_iterator(const reverse_iterator<Iter> &x) : _base_it(x.base()) {}

		iterator_type base() const { return (iterator_type(_base_it)); }

		reverse_iterator<Iterator> &operator=(const reverse_iterator<Iterator> &x)
		{
			if (this != &x)
				_base_it = x.base();
			return (*this);
		}

		reference operator*() const
		{
			iterator_type temp = _base_it;
			return *(--temp);
		}

		reverse_iterator operator+(difference_type n) const
		{
			return (reverse_iterator<Iterator>(_base_it - n));
		}

		reverse_iterator &operator++()
		{
			_base_it--;
			return (*this);
		}

		reverse_iterator operator++(int)
		{
			reverse_iterator temp = *this;
			++(*this);
			return (temp);
		}

		reverse_iterator &operator+=(difference_type n)
		{
			_base_it -= n;
			return (*this);
		}

		reverse_iterator operator-(difference_type n) const
		{
			return (reverse_iterator<Iterator>(_base_it + n));
		}

		reverse_iterator &operator--()
		{
			_base_it++;
			return (*this);
		}

		reverse_iterator operator--(int)
		{
			reverse_iterator temp = *this;
			--(*this);
			return (temp);
		}

		reverse_iterator &operator-=(difference_type n)
		{
			_base_it += n;
			return (*this);
		}

		pointer operator->() const
		{
			return &(operator*());
		}

		reference operator[](difference_type n) const
		{
			return (_base_it[-n - 1]);
		}

	protected:
		iterator_type _base_it;
	};

	//NON-MEMBER OPERATOR OVERLOADS
	template <class Iterator>
	reverse_iterator<Iterator> operator+(
		typename reverse_iterator<Iterator>::difference_type n,
		 		const reverse_iterator<Iterator> &x)
	{
		return (reverse_iterator<Iterator>(x.base() - n));
	}

	template <class Iterator>
	typename reverse_iterator<Iterator>::difference_type operator-(
			const reverse_iterator<Iterator> &x,
			const reverse_iterator<Iterator> &y)
	{
		return (y.base() - x.base());
	}

	template <class IteratorR, class IteratorL>
	typename reverse_iterator<IteratorL>::difference_type operator-(
			const reverse_iterator<IteratorL> &x,
			const reverse_iterator<IteratorR> &y)
	{
		return (y.base() - x.base());
	}

	template <class Iterator>
	bool operator == (const reverse_iterator<Iterator> &x,
			const reverse_iterator<Iterator> &y)
	{
		return x.base() == y.base();
	}

	template <class IteratorL, class IteratorR>
	bool operator == (const reverse_iterator<IteratorL> &x,
			const reverse_iterator<IteratorR> &y)
	{
		return x.base() == y.base();
	}

	template <class Iterator>
	bool operator != (const reverse_iterator<Iterator> &x,
			const reverse_iterator<Iterator> &y)
	{
		return x.base() != y.base();
	}

	template <class IteratorL, class IteratorR>
	bool operator != (const reverse_iterator<IteratorL> &x,
			const reverse_iterator<IteratorR> &y)
	{
		return x.base() != y.base();
	}

	template <class Iterator>
	bool operator < (const reverse_iterator<Iterator> &x,
			const reverse_iterator<Iterator> &y)
	{
		return x.base() > y.base();
	}

	template <class IteratorL, class IteratorR>
	bool operator < (const reverse_iterator<IteratorL> &x,
			const reverse_iterator<IteratorR> &y)
	{
		return x.base() > y.base();
	}

	template <class Iterator>
	bool operator <= (const reverse_iterator<Iterator> &x,
			const reverse_iterator<Iterator> &y)
	{
		return x.base() >= y.base();
	}

	template <class IteratorL, class IteratorR>
	bool operator <= (const reverse_iterator<IteratorL> &x,
			const reverse_iterator<IteratorR> &y)
	{
		return x.base() >= y.base();
	}

	template <class Iterator>
	bool operator > (const reverse_iterator<Iterator> &x,
			const reverse_iterator<Iterator> &y)
	{
		return x.base() < y.base();
	}

	template <class IteratorL, class IteratorR>
	bool operator > (const reverse_iterator<IteratorL> &x,
			const reverse_iterator<IteratorR> &y)
	{
		return x.base() < y.base();
	}

	template <class Iterator>
	bool operator >= (const reverse_iterator<Iterator> &x,
			const reverse_iterator<Iterator> &y)
	{
		return x.base() <= y.base();
	}

	template <class IteratorL, class IteratorR>
	bool operator >= (const reverse_iterator<IteratorL> &x,
			const reverse_iterator<IteratorR> &y)
	{
		return x.base() <= y.base();
	}
}

// https://legacy.cplusplus.com/reference/iterator/reverse_iterator/?kw=reverse_iterator

#endif
