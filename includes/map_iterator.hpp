/*


#ifndef MAP_ITERATOR_HPP
# define MAP_ITERATOR_HPP

#pragma once

#include "iterator_traits.hpp"
#include "map_bst.hpp"

namespace ft
{
	template <class T, class Category = std::bidirectional_iterator_tag,
		class Distance = ptrdiff_t, class Pointer = T*, class Reference = T&>
	class map_iterator
	{
		public:
			//	MEMBER TYPES
			typedef Category iterator_category;
			typedef T value_type;
			typedef Distance difference_type;
			typedef Pointer pointer;
			typedef Reference reference;

			//	MEMBER FUNCTIONS
			map_iterator() : _current_node() {}
			map_iterator(pointer ptr) : _current_node(ptr) {} //not sure
			map_iterator(const reference ref) {*this = ref;} //not sure
			~map_iterator() {}

			operator map_iterator<const T>(void) const
			{
				return (map_iterator<const T>(*this->_current_node));
			}

			reference operator*() const {return (_current_node->val);}

			map_iterator& operator++()
			{
				_current_node = _current_node->next_node();
				return (*this);
			}

			map_iterator operator++ (int)
			{
				map_iterator	temp(*this);
				_current_node = _current_node->next_node();
				return (temp);
			}

			map_iterator& operator--()
			{
				_current_node = _current_node->prev_node();
				return (*this);
			}

			map_iterator operator-- (int)
			{
				map_iterator	temp(*this);
				_current_node = _current_node->prev_node();
				return (*this);
			}

			pointer operator->() const
			{
				return (&_current_node->val);
			}

			map_iterator &operator= (const map_iterator<const T> &x)
			{
				if (this != &x)
					_current_node = x.get_node();
				return (*this);
			}

			pointer get_node() const {return (_current_node);}

			//	COMPARISON
			bool operator== (const map_iterator<const T> &x) const
			{
				return (_current_node == x.get_node());
			}

			bool operator!= (const map_iterator<const T> &x) const
			{
				return (_current_node != x.get_node());
			}


		protected:
			T* _current_node;
	};
}

//	https://legacy.cplusplus.com/reference/iterator/iterator/

#endif

*/

#ifndef MAP_ITERATOR_HPP
# define MAP_ITERATOR_HPP

# include <iterator>
# include "map_bst.hpp"

namespace ft
{
    template <class T, class U, class Category = std::bidirectional_iterator_tag, class Distance = std::ptrdiff_t,
        class Pointer = U*, class Reference = U&>
	class map_iterator
	{
	public:
    	typedef T         		value_type;
    	typedef Distance  		difference_type;
    	typedef Pointer   		pointer;
    	typedef Reference 		reference;
    	typedef Category  		iterator_category;
	protected:
		T *_ptr;
	public:
		map_iterator(void) : _ptr(NULL)
		{
			/* NOP */
		}

		map_iterator(const map_iterator &other)
		{
			*this = other;
		}

		map_iterator(T *ptr) : _ptr(ptr)
		{
			/* NOP */
		}

		~map_iterator(void)
		{
			/* NOP */
		}

		T *get_node(void) const
		{
			return _ptr;
		}

		map_iterator &operator = (const map_iterator &other)
		{
			if (this != &other)
				_ptr = other._ptr;
			return *this;
		}

		map_iterator &operator ++ (void)
		{
			_ptr = _ptr->next_node();
			return *this;
		}

		map_iterator &operator -- (void)
		{
			_ptr = _ptr->prev_node();
			return *this;
		}

		map_iterator operator ++ (int)
		{
			map_iterator tmp = *this;
			_ptr = _ptr->next();
			return tmp;
		}

		map_iterator operator -- (int)
		{
			map_iterator tmp = *this;
			_ptr = _ptr->prev();
			return tmp;
		}

		bool operator == (const map_iterator &other) const
		{
			return _ptr == other._ptr;
		}

		bool operator != (const map_iterator &other) const
		{
			return _ptr != other._ptr;
		}

		reference operator * (void) const
		{
			return _ptr->val;
		}

		pointer operator -> (void) const
		{
			return &_ptr->val;
		}
	};

	template <class T, class U, class map_iterator, class Category = std::bidirectional_iterator_tag, class Distance = std::ptrdiff_t,
        class Pointer = U*, class Reference = U&>
	class Constmap_iterator
	{
	public:
    	typedef T         		value_type;
    	typedef Distance  		difference_type;
    	typedef Pointer   		pointer;
    	typedef Reference 		reference;
    	typedef Category  		iterator_category;
	protected:
		T *_ptr;
	public:
		Constmap_iterator(void) : _ptr(NULL)
		{
			/* NOP */
		}

		Constmap_iterator(const Constmap_iterator &other)
		{
			*this = other;
		}

		Constmap_iterator(T* ptr) : _ptr(ptr)
		{
			/* NOP */
		}

		Constmap_iterator(const map_iterator &other)
		{
			_ptr = other.get_internal_pointer();
		}

		~Constmap_iterator(void)
		{
			/* NOP */
		}

		T *get_internal_pointer(void) const
		{
			return _ptr;
		}

		Constmap_iterator &operator = (const Constmap_iterator &other)
		{
			if (this != &other)
				_ptr = other._ptr;
			return *this;
		}

		Constmap_iterator &operator ++ (void)
		{
			_ptr = _ptr->next();
			return *this;
		}

		Constmap_iterator &operator -- (void)
		{
			_ptr = _ptr->prev();
			return *this;
		}

		Constmap_iterator operator ++ (int)
		{
			Constmap_iterator tmp = *this;
			_ptr = _ptr->next();
			return tmp;
		}

		Constmap_iterator operator -- (int)
		{
			Constmap_iterator tmp = *this;
			_ptr = _ptr->prev();
			return tmp;
		}

		bool operator == (const Constmap_iterator &other) const
		{
			return _ptr == other._ptr;
		}

		bool operator != (const Constmap_iterator &other) const
		{
			return _ptr != other._ptr;
		}

		const reference operator * (void) const
		{
			return _ptr->val;
		}

		const pointer operator -> (void) const
		{
			return &_ptr->val;
		}
	};
}

#endif
