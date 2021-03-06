/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Vector.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbachele <vbachele@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/26 15:25:56 by vbachele          #+#    #+#             */
/*   Updated: 2022/06/26 14:48:03 by vbachele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef vector_HPP
#define vector_HPP
#include "iostream"
#include "limits"
#include "Iterators.hpp"
#include <memory>
#include "Utils.hpp"
#pragma once


/*
**==========================
**    CLASS DECLARATION
**==========================
*/
// std::allocator<T> Alloc is used to define the storage allocation model
namespace ft
{
	template < class T, class Alloc = std::allocator<T> >
	class vector
	{
	public:
	/***************** TYPEDEF **************/
		typedef T										value_type;
		typedef	Alloc									allocator_type;
		typedef size_t									size_type;
		typedef value_type*								pointer;
		//typename is mandatory for the compiler allocator::reference because reference is in the scop of allocator
		//Allocator::reference is reference to an element
		typedef value_type&								reference;
		typedef const value_type&						const_reference;
		typedef vector_iterator<value_type>				iterator;
		typedef vector_iterator<value_type const>		const_iterator;
		typedef ft::reverse_iterator<iterator>				reverse_iterator;
		typedef ft::reverse_iterator<const_iterator>		const_reverse_iterator;

	/***************** CANONICAL FORM **************/
		/*** Default empty constructor ***/
		explicit vector (const allocator_type& alloc = allocator_type());
		/*** fill constructor - with n elements for the array. Each element is a copy of val. ***/
		explicit vector (size_type n, const value_type& val = value_type(),
								const allocator_type& alloc = allocator_type());

		/*** range constructor ***/
		vector (iterator first, iterator last, const allocator_type& alloc = allocator_type());
		/*** copy constructor ***/
		vector (const vector& x);
		vector& operator= (const vector& x);
		~vector();

	/***************** MEMBER FUNCTIONS **************/
		size_type 			size() const;
		void 				set_size(size_type size);
		size_type 			capacity() const;
		size_type			max_size() const;
		bool				empty() const;
		void 				resize(size_type n, value_type val = value_type());
		void 				set_array(pointer array); //Give you a new array
		void 				reserve(size_type n); // request the vector capacity at least n elements
		void				display_array(void) const;

	/***************** ITERATORS FUNCTIONS **************/
		reverse_iterator 		rbegin();
		const_reverse_iterator 	rbegin() const;
		reverse_iterator 		rend();
		const_reverse_iterator 	rend() const;
		iterator 				begin();
		const_iterator 			begin() const;
		iterator				end();
		const_iterator			end() const;

	/***************** MODIFIERS FUNCTIONS **************/
		void				push_back(const value_type& val);
		void				pop_back();
		void				swap (vector& x);
		void 				clear();
		iterator 			insert (iterator position, const value_type& val);
		void 				insert (iterator position, size_type n, const value_type& val);
		void 				insert (iterator position, iterator first, iterator last);
		void 				assign (iterator first, iterator last);
		void 				assign (size_type n, const value_type& val);
		iterator 			erase (iterator position);
		iterator 			erase (iterator first, iterator last);

	/***************** ELEMENT ACCESS FUNCTIONS **************/

		reference operator[] (size_type n) {return *(this->_array + n);}
		const_reference operator[] (size_type n) const 	{return *(this->_array + n);}
		/*** return a reference at the n position ***/
		reference at (size_type n)
		{
			if (this->size() <= n)
				throw std::out_of_range("out of range");
			return *(this->_array + n);
		}
		const_reference at (size_type n) const
		{
			if (this->size() <= n)
				throw std::out_of_range("out of range");
			return *(this->_array + n);
		}
		reference back() {return (this->_array[this->size() - 1]);}
		const_reference back() const {return (this->_array[this->size() - 1]);}
		reference front() {return (this->_array[0]);}
		const_reference front() const{ return (this->_array[0]);}

	private:
		pointer				_array; // Adress of the array - We are using a pointer to allow a dynamic allocation of the memory during runtime of the program
		size_type 			_size; // size of the array
		size_type 			_capacity; //size for the memory
		allocator_type		_alloc;
	};

	/*
	**==========================
	**     CANONICAL FORM
	**==========================
	*/

	template <typename T, typename Alloc>
	vector<T, Alloc>::vector(const allocator_type& alloc)
	{
		this->_size = 0;
		this->_capacity = 0;
		this->_alloc = alloc;
		this->_array = NULL;
	}

	template <typename T, typename Alloc>
	vector<T, Alloc>::vector(size_type n, const value_type& val,
					const allocator_type& alloc)
	{
		this->_size = n;
		this->_capacity = n;
		this->_alloc = alloc;
		this->_array = _alloc.allocate(this->_capacity);
		for (size_type i = 0; i < n; i++)
			this->_array[i] = val;
	}

	template <typename T, typename Alloc>
	vector <T, Alloc>::vector(const vector &x)
	{
		this->_size = x._size;
		this->_capacity = x._capacity;
		this->_alloc = x._alloc;
		this->_array = NULL;
		this->_array = _alloc.allocate(this->_capacity); // here I allocate in the memory the capacity
		for (size_type i = 0; i < this->_size; i++)
			_alloc.construct(&_array[i], x._array[i]);
		return ;
	}

	template <typename T, typename Alloc>
	vector<T, Alloc>::vector(iterator first, iterator last, const allocator_type& alloc)
	{
		this->_size = last - first;
		this->_capacity = last - first;
		this->_alloc = alloc;
		this->_array = _alloc.allocate(this->_capacity);
		this->assign(first, last); // we use assign here to assign the value
	}

	template <typename T, typename Alloc>
	vector<T, Alloc>::~vector()
	{
		size_type i = 0;
		while (i < this->_size)
		{
			this->_alloc.destroy(&this->_array[i]);
			i++;
		}
		this->_alloc.deallocate(this->_array, this->_capacity);
	}

	template <typename T, typename Alloc>
	vector<T, Alloc> &vector<T, Alloc>::operator= (const vector<T, Alloc> & x)
	{
		for (size_type i = 0; i < _size; i++)
			_alloc.destroy(&_array[i]);
		this->_size = x._size;
		this->_capacity = x._capacity;
		this->_alloc = x._alloc;
		this->_array = _alloc.allocate(this->_capacity);
		for (size_type i = 0; i < this->_size; i++)
		{
			_alloc.construct(&_array[i], x._array[i]);
		}
		return (*(this));
	}


	/*
	**==========================
	**    MEMBER FUNCTIONS
	**==========================
	*/

	template <typename T, typename Alloc>
	size_t	vector<T, Alloc>::size(void) const
	{
		return(this->_size);
	}

	template <typename T, typename Alloc>
	void vector<T,Alloc>::set_size(size_type size)
	{
		this->_size = size;
	}

	template <typename T, typename Alloc>
	size_t vector<T, Alloc>::capacity(void) const
	{
		return(this->_capacity);
	}

	/*** Return the maximum finite value representable by the numeric type T ***/
	template <typename T, typename Alloc>
	size_t	vector<T, Alloc>::max_size() const
	{
		return (std::numeric_limits<size_type>::max());
	}

	template <typename T, typename Alloc>
	bool vector<T,Alloc>::empty() const
	{
		if (this->size() == 0)
			return (true);
		return (false);
	}

	template <typename T, typename Alloc>
	void 		vector<T, Alloc>::resize(size_type n, value_type val)
	{
		(void) val;
		if (n > capacity())
			reserve(n);
		if (n > size())
		{
			for (size_type i = size(); i <= n; i++)
			{
				_alloc.construct(&this->_array[i], val);
			}
			set_size(n);
		}
		if (n < size())
		{
			for (size_type i = n; i > size(); i--)
			{
				this->_alloc.destroy(&_array[i]);
			}
			set_size(n);
		}
	}

	template <typename T, typename Alloc>
	void		vector<T, Alloc>::display_array(void) const
	{
		for (size_type i = 0; i < size(); i++)
		{
			std::cout << "value of the array : " << _array[i] << std::endl;
		}
	}

	template <typename T, typename Alloc>
	void vector<T,Alloc>::set_array(pointer array)
	{
		this->_array = array;
	}


	template <typename T, typename Alloc>
	void		vector<T, Alloc>::reserve(size_type size) // allocation of a nez capacity
	{
		if (size > capacity())
		{
			pointer n = _alloc.allocate(size);
			int i = 0;
			int max = this->size();
			while (i < max)
			{
				this->_alloc.construct(&n[i], this->_array[i]);
				this->_alloc.destroy(&_array[i]);
				i++;
			}
			this->_alloc.deallocate(this->_array, this->_capacity);
			set_array(n);
			this->_capacity = size;
		}
	}

	/*
	**==========================
	**   MODIFIERS FUNCTIONS
	**==========================
	*/

	template <typename T, typename Alloc>
	void		vector<T, Alloc>::push_back(const value_type& val)
	{
		if (capacity() == size())
		{
			if (size() == 0)
				this->reserve(2); // I attribute the memory of 2 for the program
			else
			{
				this->reserve(capacity() + 1);
			}
		}
		_array[_size] = val;
		this->_size++;
	}

	template <typename T, typename Alloc>
	void		vector<T, Alloc>::pop_back()
	{
		if (size() > 0)
			this->_size -= 1;
	}

	template <typename T, typename Alloc>
	void 		vector<T, Alloc>::swap(vector& x)
	{
		pointer 		start = x._array;
		size_type 		start_size = x._size;
		size_type 		start_capacity = x._capacity;
		allocator_type 	start_allocator = x._alloc;

		x._array = this->_array;
		x._size = this->_size;
		x._capacity = this->_capacity;
		x._alloc = this->_alloc;

		this->_array = start;
		this->_size = start_size;
		this->_capacity = start_capacity;
		this->_alloc = start_allocator;
	}

	template <typename T, typename Alloc>
	void 		vector<T, Alloc>::clear()
	{
		this->_size = 0;
	}

	template <typename T, typename Alloc>
	typename  vector<T, Alloc>::iterator vector<T,Alloc>::insert(iterator position, const value_type& val)
	{
		size_type n = (position - this->begin());
		this->insert(position, 1, val);
		return (iterator(&this->_array[n])); // point to the first element newly inserted
	}

	template <typename T, typename Alloc>
	void 				vector<T, Alloc>::insert(iterator position, size_type n, const value_type& val)
	{
		// temp to assign the store the value
		vector<T, Alloc> temp(position, this->end());
		this->_size -= (this->end() - position); // just keeping the good size
		for (size_type i = 0; i < n ; i++)
			this->push_back(val); // inserting the value on front
		iterator it_begin = temp.begin();
		iterator it_end = temp.end();
		while (it_begin != it_end)
		{
			this->push_back(*it_begin);
			++it_begin;
		}
	}

	template <typename T, typename Alloc>
	void 				vector<T, Alloc>::insert(iterator position, iterator first, iterator last)
	{
		vector<T, Alloc> temp(position, this->end());
		this->_size -= (this->end() - position);
		while (first != last)
		{
			this->push_back(*first);
			first++;
		} // inserting the value on front
		iterator it_begin = temp.begin();
		iterator it_end = temp.end();
		while (it_begin != it_end)
		{
			this->push_back(*it_begin);
			++it_begin;
		}
	}

	template <typename T, typename Alloc >
	void 	vector<T, Alloc>::assign(iterator first, iterator last)
	{
		this->clear();
		while (first != last)
		{
			this->push_back(*first);
			++first;
		}
	}

	template <typename T, typename Alloc >
	void 	vector<T, Alloc>::assign(size_type n, const value_type& val)
	{
		this->clear();
		for (size_type i = 0; i < n; i++)
			this->push_back(val);
	}

	/*** Remove from the vector the element at "position", that means we have to reallocate the size ***/
	template <typename T, typename Alloc >
	typename 	vector<T, Alloc>::iterator vector<T, Alloc>::erase(iterator position)
	{
		iterator temp(position);
		iterator it_end = this->end() - 1;
		while (position < it_end)
		{
			*position = *(position + 1);
			position++;
		}
		this->_size--;
		return (temp);
	}

	/***Remove from the vector the element between last(not included) and first(included), that means we have to reallocate the size
		We allocate the new value after last until the end of the array ***/
	template <typename T, typename Alloc >
	typename 	vector<T, Alloc>::iterator vector<T, Alloc>::erase(iterator first, iterator last)
	{
		iterator temp(last);
		iterator it_end = this->end();
		while (last < it_end)
		{
			*first = *last;
			++first;
			++last++;
		}
		this->_size -= (last - first);
		return (temp);
	}

	/*
	**==========================
	**   ITERATOR FUNCTIONS
	**==========================
	*/

	template <typename T, typename Alloc>
	typename vector<T, Alloc>::iterator	vector<T,Alloc>::begin()
	{
		// I return the pointer pointer at the first element of the array
		return (iterator(this->_array));
	}

	template <typename T, typename Alloc>
	typename vector<T, Alloc>::const_iterator	vector<T,Alloc>::begin() const
	{
		return (const_iterator(this->_array));
	}

	template <typename T, typename Alloc>
	typename vector<T, Alloc>::iterator	vector<T,Alloc>::end()
	{
		// I return the pointer pointer at the first element of the array
		return (iterator(this->_array + this->_size));
	}

	template <typename T, typename Alloc>
	typename vector<T, Alloc>::const_iterator vector<T,Alloc>::end() const
	{
		return (const_iterator(&this->_array[_size]));
	}

		template <typename T, typename Alloc>
	typename vector<T, Alloc>::reverse_iterator vector<T, Alloc>::rend()
	{
		return reverse_iterator(begin());
	}

	template <typename T, typename Alloc>
	typename vector<T, Alloc>::const_reverse_iterator vector<T, Alloc>::rend() const
	{
		return const_reverse_iterator(begin());
	}

	template <typename T, typename Alloc>
	typename vector<T, Alloc>::reverse_iterator vector<T, Alloc>::rbegin()
	{
		return reverse_iterator(end());
	}

	template <typename T, typename Alloc>
	typename vector<T, Alloc>::const_reverse_iterator vector<T, Alloc>::rbegin() const
	{
		return const_reverse_iterator(end());
	}

	/*
	**==========================
	** NON MEMBER FUNCTIONS OVERLOAD
	**==========================
	*/

	template <class T, class Alloc>
	bool operator==(const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs)
	{
		typename vector<T, Alloc>::const_iterator begin_lhs = lhs.begin();
		typename vector<T, Alloc>::const_iterator begin_rhs = rhs.begin();
		typename vector<T, Alloc>::const_iterator end_lhs = lhs.end();
		typename vector<T, Alloc>::const_iterator end_rhs = rhs.end();

		// we compare each value of iterators
		while ((begin_lhs != end_lhs) && (begin_rhs != end_rhs))
		{
			if (*begin_rhs != *begin_lhs)
				return (false);
			++begin_lhs;
			++begin_rhs;
		}
		if ((begin_lhs != end_lhs) && (begin_rhs != end_rhs))
			return (false);
		return true;
	}

	template <class T, class Alloc>
	bool operator!= (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs)
	{
		if (lhs == rhs)
			return (false);
		return (true);
	}

	template<typename T, typename Alloc>
	bool operator<(const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs)
	{
		return(lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end()));
	}

	template <class T, class Alloc>
	bool operator<= (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs)
	{
		return (!(rhs < lhs));
	}

	template <class T, class Alloc>
	bool operator>  (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs)
	{
		return (rhs < lhs); // we just check if rhs < lhs is false
	}

	template <class T, class Alloc>
	bool operator>= (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs)
	{
		return (!(rhs > lhs)); // we just check if rhs < lhs is true
	}

	template <class T, class Alloc>
	void swap (vector<T,Alloc>& x, vector<T,Alloc>& y)
	{
		vector<T,Alloc> temp = x;
		x = y;
		y = x;
	}
}

#endif

