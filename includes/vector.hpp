#ifndef VECTOR_HPP
# define VECTOR_HPP

#pragma once

#include <algorithm>
#include "vector_iterator.hpp"
#include "reverse_iterator.hpp"
#include "enable_if.hpp"
#include "reverse_iterator.hpp"
#include "equal.hpp"
#include "is_integral.hpp"
#include "lexicographical_compare.hpp"

namespace ft
{
	template <class Type, class Allocator = std::allocator<Type> >
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
		typedef vector_iterator<value_type> iterator;
		typedef vector_iterator<const value_type> const_iterator;
		typedef ft::reverse_iterator<iterator> reverse_iterator;
		typedef ft::reverse_iterator<const_iterator> const_reverse_iterator;

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
			_data = _alloc.allocate(n);
			for (size_type i = 0; i<n; i++)
				_alloc.construct(&_data[i], val);
		}

		template <class InputIterator>
		vector(typename ft::enable_if<!ft::is_integral<InputIterator>::value,
				InputIterator>::type first, InputIterator last,
				const allocator_type &alloc = allocator_type()) :
				_data(NULL), _capacity(0), _size(0), _alloc(alloc)
		{
			//	Constructs a container with as many elements as the range (first,last)
			try
			{
				this->assign(first, last);
			}
			catch(const std::exception& e)
			{
				std::cerr << e.what() << '\n';
			}
		}

		vector(const vector &x) :
				_data(NULL), _capacity(x._size), _size(x._size), _alloc(x._alloc)
		{
			//	Constructs a container with a copy of each of the elements in x, in the same order.
			try
			{
				_data = _alloc.allocate(x._size);
				for (size_t i = 0; i<_size; i++)
					_alloc.construct(&_data[i], x._data[i]);
			}
			catch(const std::exception& e)
			{
				std::cerr << e.what() << '\n';
			}
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
			if (this != &x)
			{
				try
				{
					this->clear();
					_alloc.deallocate(_data, _capacity);
					_capacity = x._capacity;
					_size = x._size;
					_data = _alloc.allocate(_capacity);
					for (size_t i = 0; i<_size; i++)
						_alloc.construct(&_data[i], x._data[i]);
				}
				catch(const std::exception& e)
				{
					std::cerr << e.what() << '\n';
				}
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
			// Not sure about this one either
			while (n < _size)
				this->pop_back();
			if (n > _size)
			{
				if (n > _capacity)
				try
				{this->reserve(n);}
				catch(const std::exception& e)
				{std::cerr << e.what() << '\n';}
				while (n > _size)
					this->push_back(val);
			}
		}

		void reserve(size_type n)
		{
			if (n > this->max_size())
				throw std::length_error("length_error: vector::reserve");
			if (_capacity < n && n != 0)
			{
				pointer tmp = _alloc.allocate(n);
				try
				{
					for (size_type i = 0; i < _size; i++)
					{
						_alloc.construct(&tmp[i], _data[i]);
						_alloc.destroy(&_data[i]);
					}
					_alloc.deallocate(_data, _capacity);
					_capacity = n;
					_data = tmp;
				}
				catch(const std::exception& e)
				{
					throw std::bad_alloc();
				}
			}
		}

		//	ELEMENT ACCESS
		reference operator[](size_type n) {return (_data[n]);}
		const_reference operator[](size_type n) const {return (_data[n]);}
		reference front() {return (_data[0]);}
		const_reference front() const {return (_data);}
		reference back() {return (_data[_size - 1]);}
		const_reference back() const {return (_data[_size - 1]);}

		reference at(size_type n)
		{
			if (n > _size)
				throw std::out_of_range("vector::at");
			return (_data[n]);
		}

		const_reference at(size_type n) const
		{
			if (n > _size)
				throw std::out_of_range("vector::at const");
			return (_data[n]);
		}

		//	MODIFIERS
		template <class InputIterator>
		void assign(typename ft::enable_if<
					!ft::is_integral<InputIterator>::value,
					InputIterator>::type first, InputIterator last)
		{
			//Not sure about this one
			try
			{
				this->clear();
			}
			catch(const std::exception& e)
			{
				std::cerr << e.what() << '\n';
			}
			for (; first != last; ++first)
				this->push_back(*first);
		}

		void assign(size_type n, const_reference val)
		{
			try
			{
				this->clear();
			}
			catch(const std::exception& e)
			{
				std::cerr << e.what() << '\n';
			}
			for (size_type i = 0; i < n; i++)
				push_back(val);
		}

		void push_back(const_reference val)
		{
			if (_capacity < _size + 1)
			{
				if (_size == 0)
					try
					{
						this->reserve(1);
					}
					catch(std::exception& e) {
						std::cerr << e.what() << '\n';
					}
				else
					try
					{
						this->reserve(_size * 2);
					}
					catch(std::exception& e) {
						std::cerr << e.what() << '\n';
					}
			}
			_alloc.construct(&_data[_size], val);
			_size++;
		}

		void pop_back()
		{
			if (!empty())
			{
				try
				{
					_alloc.destroy(&_data[_size - 1]);
					_size--;
				}
				catch(const std::exception& e)
				{
					throw std::bad_alloc();
				}
			}
		}

		iterator insert(iterator position, const_reference val)
		{
			value_type	swap;
			size_type	insert_pos = 0;

			if (position != this->end())
			{
				for (iterator it = this->begin(); it != position; it++)
					insert_pos++;
				try
				{
				this->push_back(val);
				}
				catch(const std::exception& e)
				{
					std::cerr << e.what() << '\n';
				}
				for (size_type i = _size - 1; i > insert_pos; i--)
				{
					swap = _data[i];
					_data[i] = _data[i - 1];
					_data[i - 1] = swap;
				}
				return (iterator(_data + insert_pos));
			}
			try
			{
				this->push_back(val);
			}
			catch(const std::exception& e)
			{
				std::cerr << e.what() << '\n';
			}
			return (end() - 1);
		}

		void insert(iterator position, size_type n, const_reference val)
		{
			while (n--)
				position = insert(position, val);
		}

		template <class InputIterator>
		void insert(iterator position, typename ft::enable_if<
					!ft::is_integral<InputIterator>::value,
					InputIterator>::type first, InputIterator last)
		{
			for (; first != last; ++first)
				position = insert(position, *first) + 1;
		}

		iterator erase(iterator position)
		{
			iterator	temp;
			size_type	i = 0;

			for (iterator it = this->begin(); it < position; it++)
				i++;
			if (i < this->_size)
				temp = position;
			else
				temp = this->end();
			for (iterator it = position + 1; it < this->end(); it++)
			{
				_data[i] = _data[i + 1];
				i++;
			}
			try
			{
				this->pop_back();
			}
			catch(const std::exception& e)
			{
				std::cerr << e.what() << '\n';
			}
			return (temp);
		}

		iterator erase(iterator first, iterator last)
		{
			size_type	i = 0;

			for (iterator it = first; it != last; it++)
				i++;
			while (i)
			{
				erase(first);
				i--;
			}
			return (first);
		}

		void swap(vector &x)
		{
			pointer			tmp_data = this->_data;
			size_type		tmp_size = this->_size;
			size_type		tmp_capacity = this->_capacity;
			allocator_type	tmp_alloc = this->_alloc;

			if (this == &x)
				return;
			this->_data = x._data;
			this->_size = x._size;
			this->_capacity = x._capacity;
			this->_alloc = x._alloc;

			x._data = tmp_data;
			x._size = tmp_size;
			x._capacity = tmp_capacity;
			x._alloc = tmp_alloc;
		}

		void clear()
		{
			for (size_type i = 0; i < _size; i++)
				_alloc.destroy(&_data[i]);
			this->_size = 0;
		}

		//	ALLOCATOR
		allocator_type get_allocator() const {return (_alloc);}

	private:
		pointer _data;
		size_type _capacity;
		size_type _size;
		allocator_type _alloc;
	};

	//	NON-MEMBER FUNCTIONS
	template <class T, class Alloc>
	bool operator==(const vector<T, Alloc> &lhs, const vector<T, Alloc> &rhs)
	{
		if (lhs.size() != rhs.size())
			return (false);
		return (ft::equal(lhs.begin(), lhs.end(), rhs.begin()));
	}

	template <class T, class Alloc>
	bool operator!=(const vector<T, Alloc> &lhs, const vector<T, Alloc> &rhs)
	{
		return !(lhs == rhs);
	}

	template <class T, class Alloc>
	bool operator<(const vector<T, Alloc> &lhs, const vector<T, Alloc> &rhs)
	{
		return (ft::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end()));
	}

	template <class T, class Alloc>
	bool operator<=(const vector<T, Alloc> &lhs, const vector<T, Alloc> &rhs)
	{
		return !(rhs < lhs);
	}

	template <class T, class Alloc>
	bool operator>(const vector<T, Alloc> &lhs, const vector<T, Alloc> &rhs)
	{
		return (rhs < lhs);
	}

	template <class T, class Alloc>
	bool operator>=(const vector<T, Alloc> &lhs, const vector<T, Alloc> &rhs)
	{
		return !(lhs < rhs);
	}

	template <class T, class Alloc>
	void swap(vector<T, Alloc> &lhs, vector<T, Alloc> &rhs)
	{
		lhs.swap(rhs);
	}
}
//	https://legacy.cplusplus.com/reference/vector/vector/

#endif
