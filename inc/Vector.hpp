/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Vector.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbachele <vbachele@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/26 15:25:56 by vbachele          #+#    #+#             */
/*   Updated: 2022/06/01 16:00:17 by vbachele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VECTOR_HPP
#define VECTOR_HPP
#include "iostream"
#include "limits"
#pragma once

/*
**==========================
**    CLASS DECLARATION
**==========================
*/
// std::allocator<T> Alloc is used to define the storage allocation model
template < class T, class Alloc = std::allocator<T> >
class Vector
{
public:
/***************** TYPEDEF **************/
	typedef T							value_type;
	typedef	Alloc						allocator_type;
	typedef size_t						size_type;
	typedef value_type*					pointer;

/***************** CANONICAL FORM **************/
	/*** Default empty constructor ***/
	explicit Vector (const allocator_type& alloc = allocator_type());
	/*** fill constructor - with n elements for the array. Each element is a copy of val. ***/
	explicit Vector (size_type n, const value_type& val = value_type(),
							const allocator_type& alloc = allocator_type());

	/*** range constructor ***/
	// template <class InputIterator>
    //      Vector (InputIterator first, InputIterator last,
    //              const allocator_type& alloc = allocator_type());

	/*** copy constructor ***/
	Vector (const Vector& x);
	Vector& operator= (const Vector& x);
	~Vector();

/***************** MEMBER FUNCTIONS **************/
	size_type 	size() const;
	void 		set_size(size_type size);
	size_type 	capacity() const;
	size_type	max_size() const;
	bool		empty() const;
	void 		resize(size_type n, value_type val = value_type());
	void 		set_array(pointer array); //Give you a new array
	void 		reserve(size_type n); // request the vector capacity at least n elements

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
Vector<T, Alloc>::Vector(const allocator_type& alloc)
{
	this->_size = 0;
	this->_capacity = 0;
	this->_alloc = alloc;
	this->_array = NULL;
	std::cout << "-------------- DEFAULT CONSTRUCTOR ---------------" << std::endl << std::endl;
	std::cout << "Constructor is called" << std::endl;
	std::cout << "Initial Capacity is: " << _capacity << std::endl;
	std::cout << "size is: " << _size << std::endl << std::endl;
}

template <typename T, typename Alloc>
Vector<T, Alloc>::Vector(size_type n, const value_type& val,
                 const allocator_type& alloc)
{
	this->_size = n;
	this->_capacity = n;
	this->_alloc = alloc;
	this->_array = _alloc.allocate(this->_capacity);;
	std::cout << "-------------- FILL CONSTRUCTOR ---------------" << std::endl << std::endl;
	std::cout << "Initial Capacity is: " << _capacity << std::endl;
	std::cout << "size is: " << _size << std::endl;
	for (size_type i = 0; i < n; i++)
	{
		this->_array[i] = val;
		std::cout << "Value of the Array: " << this->_array[i] << std::endl;
	}
	std::cout << std::endl;
}

template <typename T, typename Alloc>
Vector <T, Alloc>::Vector(const Vector &x)
{
	std::cout << "-------------- COPY CONSTRUCTOR ---------------" << std::endl << std::endl;
	std::cout << "Copy Constructor is called" << std::endl;
	this->_size = x._size;
	this->_capacity = x._capacity;
	this->_alloc = x._alloc;
	this->_array = NULL;
	this->_array = _alloc.allocate(this->_capacity); // here I allocate in the memory the capacity
	for (size_type i = 0; i < this->_size; i++)
	{
		_alloc.construct(&_array[i], x._array[i]);
		std::cout << "Value of the Array: " << _array[i] << std::endl;
	}
	std::cout << "Initial Capacity is: " << _capacity << std::endl;
	std::cout << "size is: " << _size << std::endl << std::endl;
	return ;
}

template <typename T, typename Alloc>
Vector<T, Alloc>::~Vector()
{
	std::cout << "-------------- DESTRUCTOR ---------------" << std::endl << std::endl;
	size_type i = 0;
	while (i < this->_size)
	{
		std::cout << "I delete an member of my array" << std::endl;
		this->_alloc.destroy(&this->_array[i]);
		i++;
	}
	this->_alloc.deallocate(this->_array, this->_capacity);
	std::cout << "Destructor is called" << std::endl;
}

template <typename T, typename Alloc>
Vector<T, Alloc> &Vector<T, Alloc>::operator= (const Vector<T, Alloc> & x)
{
	std::cout << "-------------- OPERATOR == ---------------" << std::endl << std::endl;
	for (size_type i = 0; i < _size; i++)
		_alloc.destroy(&_array[i]);
	this->_size = x._size;
	this->_capacity = x._capacity;
	this->_alloc = x._alloc;
	this->_array = _alloc.allocate(this->_capacity);
	for (size_type i = 0; i < this->_size; i++)
	{
		_alloc.construct(&_array[i], x._array[i]);
		std::cout << "Value of the Array: " << _array[i] << std::endl;
	}
	std::cout << "Initial Capacity is: " << this->_capacity << std::endl;
	std::cout << "size is: " << this->_size << std::endl;
	return (*(this));
}


/*
**==========================
**    MEMBER FUNCTIONS
**==========================
*/

template <typename T, typename Alloc>
size_t	Vector<T, Alloc>::size(void) const
{
	return(this->_size);
}

template <typename T, typename Alloc>
void Vector<T,Alloc>::set_size(size_type size)
{
	this->_size = size;
}

template <typename T, typename Alloc>
size_t Vector<T, Alloc>::capacity(void) const
{
	return(this->_capacity);
}

// Return the maximum finite value representable by the numeric type T
template <typename T, typename Alloc>
size_t	Vector<T, Alloc>::max_size() const
{
	return (std::numeric_limits<size_type>::max());
}

template <typename T, typename Alloc>
bool Vector<T,Alloc>::empty() const
{
	if (this->size() == 0)
		return (true);
	return (false);
}

template <typename T, typename Alloc>
void 		Vector<T, Alloc>::resize(size_type n, value_type val)
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
	for (size_type i = 0; i < n; i++)
	{
		std::cout << "n = " << n << " i = " << i << std::endl;
		std::cout << "value of the array : " << _array[i] << std::endl;
	}
}

template <typename T, typename Alloc>
void Vector<T,Alloc>::set_array(pointer array)
{
	this->_array = array;
}


template <typename T, typename Alloc>
void		Vector<T, Alloc>::reserve(size_type size) // allocation of a nez capacity
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

#endif

