#ifndef VECTOR_HPP
# define VECTOR_HPP

#pragma once

#include "reverse_iterator.hpp"
#include "enable_if.hpp"
#include "reverse_iterator.hpp"
#include "equal.hpp"
#include "is_integral.hpp"
#include "lexicographical_compare.hpp"

namespace ft
{
	template <class Type, class Allocator = std::allocator<Type>>
	class vector
	{
		//	MEMBER TYPES
	public:
		typedef Type value_type;
		typedef Allocator allocator_type;
		typedef std::size_t size_type;
		typedef std::ptrdiff_t difference_type;
		typedef value_type &reference;
		typedef const value_type &const_reference;
		typedef value_type *pointer;
		typedef const value_type *const_pointer;
		// need to include the iterators that i need to do
		typedef iterator;
		typedef const_iterator;
		typedef reverse_iterator;
		typedef const_reverse_iterator;

		//	MEMBER FUNCTIONS
		explicit vector(const allocator_type &alloc = allocator_type()) :
						_data(NULL), _capacity(0), _size(0), _alloc(alloc)
		{
			//	Constructs an empty container, with no elements.
		}

		explicit vector(size_type n, const_reference val = value_type(),
						const allocator_type &alloc = allocator_type()) :
						_data(NULL), _capacity(n), _size(n), _alloc(alloc)
		{
			//	Constructs a container with n elements. Each element is a copy of val.
			_data = _data.allocate(n);
			for (size_type i = 0; i<n; i++)
				_alloc.construct(&_data[i], val);
		}

		template <class InputIterator>
		vector(InputIterator first, InputIterator last,
				const allocator_type &alloc = allocator_type()) :
				_data(NULL), _capacity(0), _size(0), _alloc(alloc)
		{
			//	Constructs a container with as many elements as the range (first,last)
			this->assign(first, last);
		}

		vector(const vector &x) :
				_data(NULL), _capacity(x._size), _size(x._size), _alloc(x.alloc)
		{
			//	Constructs a container with a copy of each of the elements in x, in the same order.
			_data = _alloc.allocate(x._size);
			for (size_t i = 0; i<_size; i++)
				_alloc.construct(&_data[i], x._data[i]);
		}

		~vector()
		{
			if (_capacity)
			{
				this->clear();
				_alloc.deallocate(_data, _capacity);
			}
		}

		vector &operator=(const vector &x)
		{
			// NOT SURE ABOUT THIS ONE
			if (*this != &x)
			{
				this->clear();
				this->reserve(x._size);
				for (size_t i = 0; i<_size; i++)
					_alloc.construct(&_data[i], x._data[i]);
			}
			return (*this);
		}

		//	ITERATORS
		iterator begin() {return (iterator(_data));}
		const_iterator begin() const {return (const_iterator(_data));}
		iterator end() {return (iterator(_data + _size));}
		const_iterator end() const {return (const_iterator(_data + _size));}
		reverse_iterator rbegin() {return (reverse_iterator(this->end()));}
		const_reverse_iterator rbegin() const {return (const_reverse_iterator(this->end()));}
		reverse_iterator rend() {return (reverse_iterator(this->begin()));}
		const_reverse_iterator rend() const {retunr (const_reverse_iterator(this->begin()));}

		//	CAPACITY
		size_type size() const {return (_size);}
		size_type max_size() const {return (_alloc.max_size());}
		size_type capacity() const {return (_capacity);}
		bool empty() const { if (_size == 0) return true; else return false;}

		void resize(size_type n, value_type val = value_type())
		{
			while (_size < n)
				this->pop_back();
			if (n <= _size * 2 && n > _capacity)
				_capacity.reserve(size * 2);
			else if (n > _capacity)
				_capacity.reserve(n);
			while (n != _size)
				push_back(val);
		}

		void reserve(size_type n)
		{
			if (n > this->max_size())
				throw std::length_error("vector::reserve");
			if (_capacity < n && n != 0)
			{
				pointer tmp = _alloc.allocate(n);
				for (size_type i = 0; i < _size; i++)
				{
					_alloc.construct(&tmp[i], _data[i]);
					_alloc.destroy(&_data[i]);
				}
				_alloc.deallocate(_data, _capacity);
				_capacity = n;
				_data = tmp;
			}
		}

		//	ELEMENT ACCESS
		reference operator[](size_type n) {return (_data[n]);}
		const_reference operator[](size_type n) const {return (data[n]);}
		reference front() {return (_data);}
		const_reference front() const {return (_data);}
		reference back() {return (_data[_size - 1]);}
		const_reference back() const {return (data[_size - 1]);}

		reference at(size_type n)
		{
			if (n > _size)
				throw std::out_of_range("'at' vector out of range.");
			return (_data[n]);
		}

		const_reference at(size_type n) const
		{
			if (n > _size)
				throw std::out_of_range("'at' vector out of range.");
			return (_data[n]);
		}

		//	MODIFIERS
		template <class InputIterator>
		void assign(InputIterator first, InputIterator last) {}
		void assign(size_type n, const_reference val) {}

		void push_back(const_reference val) {}
		void pop_back() {}

		iterator insert(iterator position, const_reference val) {}
		void insert(iterator position, size_type n, const_reference val) {}
		template <class InputIterator>
		void insert(iterator position, InputIterator first, InputIterator last) {}

		iterator erase(iterator position) {}
		iterator erase(iterator first, iterator last) {}
		void swap(vector &x) {}
		void clear() {}

		//	ALLOCATOR
		allocator_type get_allocator() const {}

	private:
		pointer _data;
		allocator_type _alloc;
		size_type _capacity;
		size_type _size;
	};

	//	NON-MEMBER FUNCTIONS
	template <class T, class Alloc>
	bool operator==(const vector<T, Alloc> &lhs, const vector<T, Alloc> &rhs)
	{
		if (lhs.size() != rhs.size())
			return (false);
		return (equal(lhs.begin(), lhs.end(), rhs.begin()));
	}

	template <class T, class Alloc>
	bool operator!=(const vector<T, Alloc> &lhs, const vector<T, Alloc> &rhs)
	{
		return !(lhs == rhs);
	}

	template <class T, class Alloc>
	bool operator<(const vector<T, Alloc> &lhs, const vector<T, Alloc> &rhs)
	{
		return (lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end() && lhs != rhs));
	}

	template <class T, class Alloc>
	bool operator<=(const vector<T, Alloc> &lhs, const vector<T, Alloc> &rhs)
	{
		return !(rhs < lhs);
	}

	template <class T, class Alloc>
	bool operator>(const vector<T, Alloc> &lhs, const vector<T, Alloc> &rhs)
	{
		return (rhs < lhsl);
	}

	template <class T, class Alloc>
	bool operator>=(const vector<T, Alloc> &lhs, const vector<T, Alloc> &rhs)
	{
		return !(lhs < rhs);
	}

	template <class T, class Alloc>
	void swap(vector<T, Alloc> &lhs, vector<T, Alloc> &rhs)
	{
		x.swap(y);
	}
}
//	https://legacy.cplusplus.com/reference/vector/vector/

#endif
