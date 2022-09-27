#ifndef MAP_ITERATOR_HPP
#define MAP_ITERATOR_HPP

#include "iterator_traits.hpp"
#include "reverse_iterator.hpp"
#include "../utils/map_binary_tree.hpp"

namespace ft
{
	template <class T, class U, class Category = std::bidirectional_iterator_tag,
			  class Distance = std::ptrdiff_t, class Pointer = U *, class Reference = U &>
	class map_iterator
	{
	public:
		//	MEMBER TYPES
		typedef Category iterator_category;
		typedef T value_type;
		typedef Distance difference_type;
		typedef Pointer pointer;
		typedef Reference reference;

		// MEMBER FUNCTIONS
		map_iterator() : _current_node() {}
		map_iterator(T *ptr) : _current_node(ptr) {}
		map_iterator(const map_iterator &x) { *this = x; }
		~map_iterator() {}

		reference operator*() const { return _current_node->val; }

		map_iterator &operator++()
		{
			_current_node = _current_node->next_node();
			return (*this);
		}

		map_iterator operator++(int)
		{
			map_iterator temp = *this;
			_current_node = _current_node->next_node();
			return (temp);
		}

		map_iterator &operator--()
		{
			_current_node = _current_node->prev_node();
			return (*this);
		}

		map_iterator operator--(int)
		{
			map_iterator temp = *this;
			_current_node = _current_node->prev_node();
			return (temp);
		}

		pointer operator->() const
		{
			return (&_current_node->val);
		}

		map_iterator &operator=(const map_iterator &x)
		{
			if (this != &x)
				_current_node = x.get_node();
			return (*this);
		}

		T *get_node() const { return (_current_node); }

		// COMPARISON
		bool operator==(const map_iterator &x) const
		{
			return (_current_node == x.get_node());
		}

		bool operator!=(const map_iterator &x) const
		{
			return (_current_node != x.get_node());
		}

	protected:
		T *_current_node;
	};

	template <class T, class U, class map_iterator, class Category = std::bidirectional_iterator_tag,
			  class Distance = std::ptrdiff_t, class Pointer = U *, class Reference = U &>
	class const_map_iterator
	{
	public:
		// MEMBER TYPES
		typedef Category iterator_category;
		typedef T value_type;
		typedef Distance difference_type;
		typedef Pointer pointer;
		typedef Reference reference;

	public:
		//	MEMBER FUNCTIONS
		const_map_iterator() : _current_node() {}
		const_map_iterator(T *ptr) : _current_node(ptr) {}
		const_map_iterator(const const_map_iterator &x) { *this = x; }
		const_map_iterator(const map_iterator &x) { _current_node = x.get_node(); }
		~const_map_iterator() {}

		const reference operator*() const { return (_current_node->val); }

		const_map_iterator &operator++()
		{
			_current_node = _current_node->next_node();
			return (*this);
		}

		const_map_iterator operator++(int)
		{
			const_map_iterator temp = *this;
			_current_node = _current_node->next_node();
			return (temp);
		}

		const_map_iterator &operator--()
		{
			_current_node = _current_node->prev_node();
			return (*this);
		}

		const_map_iterator operator--(int)
		{
			const_map_iterator temp = *this;
			_current_node = _current_node->prev_node();
			return (temp);
		}

		const pointer operator->() const
		{
			return (&_current_node->val);
		}

		const_map_iterator &operator=(const const_map_iterator &x)
		{
			if (this != &x)
				_current_node = x._current_node;
			return (*this);
		}

		T *get_node() const { return (_current_node); }

		//	COMPARISON
		bool operator==(const const_map_iterator &x) const
		{
			return _current_node == x._current_node;
		}

		bool operator!=(const const_map_iterator &x) const
		{
			return _current_node != x._current_node;
		}

	protected:
		T *_current_node;
	};
}

//	https://legacy.cplusplus.com/reference/iterator/iterator/

#endif
