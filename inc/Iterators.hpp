/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Iterators.hpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbachele <vbachele@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/03 14:43:42 by vbachele          #+#    #+#             */
/*   Updated: 2022/06/26 17:58:42 by vbachele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RAMDOMIT_HPP
# define RAMDOMIT_HPP
#include "cstdlib"
#include "../inc/Vector.hpp"
#include "iostream"
#include "iterator"
#include "../inc/Utils.hpp"
#pragma once

namespace ft
{
	template <typename T>
	class	vector_iterator
	{
	public:
		typedef std::random_access_iterator_tag iterator_category;
		typedef T								value_type; //here it is the pointer
		typedef	value_type*						pointer; //here is the reference, it is the same as &reference
		typedef value_type&						reference;
		typedef std::ptrdiff_t 					difference_type; //std::ptrdiff_t is used to do the difference between iterators of the same array and ptrdiff canbe negative
	public:
		vector_iterator()
		{
			this->_ptr = NULL;
		} // iterator sans rien
		vector_iterator(value_type *ptr) : _ptr(ptr) {} // iterator with a pointer
		vector_iterator(vector_iterator const &other) : _ptr(other._ptr) {} // iterator avec un autre iterator
		virtual ~vector_iterator() {}

		value_type *_ptr;
	/***************** MEMBER FUNCTIONS **************/
		value_type	*get_ptr() const
		{
			return (this->_ptr);
		}

	/***************** OPERATOR FUNCTIONS **************/

		vector_iterator	&operator=(const vector_iterator &rhs)
		{
			if (this != &rhs)
				this->_ptr = rhs._ptr;
			return (*this);
		}

		vector_iterator &operator++() // prefix incrementation operator
		{
			this->_ptr++;
			return (*this);
		}

		vector_iterator operator++(int) // postfix incrementation operator
		{
			vector_iterator temp = *this;
			++this->_ptr;
			return (temp);
		}

		vector_iterator &operator--() // prefix incrementation operator
		{
			this->_ptr--;
			return (*this);
		}

		vector_iterator operator--(int) // postfix incrementation operator
		{
			vector_iterator temp = *this;
			--this->_ptr;
			return (temp);
		}

		// Return a reference to the element at position n in the vector
		value_type &operator[] (int n)
		{
			return *(this->_ptr + n);
		}

		vector_iterator &operator-=(value_type n)
		{
			this->_ptr -= n;
			return *this;
		}

		vector_iterator &operator+=(value_type n)
		{
			this->_ptr += n;
			return *this;
		}

		// difference _type is the value of the pointer
		vector_iterator operator+(difference_type n) const
		{
			vector_iterator res = this->_ptr + n;
			return (res);
		}

		vector_iterator operator-(difference_type n) const
		{
			vector_iterator res = this->_ptr - n;
			return (res);
		}

		difference_type operator-(const vector_iterator &rhs) const // take 2 operators and do the difference between iterators
		{
			difference_type res = this->_ptr - rhs._ptr;
			return(res);
		}

		difference_type operator+(const vector_iterator &rhs) const // take 2 operators and do the addition between the 2iterators
		{
			difference_type res = this->_ptr + rhs._ptr;
			return(res);
		}

		//renvoie la valeur point?? par l'iterator
		pointer operator->()
		{
			return(this->_ptr);
		}

		//renvoie l'addresse du pointer de l'iterator
		reference operator*()
		{
			return(*this->_ptr);
		}
		bool operator!=(const vector_iterator &other) const
		{
			bool b = this->_ptr != other._ptr; // If diff b = 1
			return (b);
		}

		bool operator<(const vector_iterator &other) const
		{
			bool b = this->_ptr < other._ptr;
			return (b);
		}

		bool operator>(const vector_iterator &other) const
		{
			bool b = this->_ptr > other._ptr;
			return (b);
		}

		bool operator>=(const vector_iterator &other) const
		{
			bool b = this->_ptr >= other._ptr;
			return (b);
		}

		bool operator<=(const vector_iterator &other) const
		{
			bool b = this->_ptr <= other._ptr;
			return (b);
		}

		bool operator==(const vector_iterator &other) const
		{
			return (this->_ptr == other.get_ptr());
		}

	};

	template <typename Iterator>
    vector_iterator<Iterator> operator+(typename vector_iterator<Iterator>::difference_type n, const vector_iterator<Iterator> &it)
    {
        return (vector_iterator<Iterator>(it.base() + n));
    }

    template <typename Iterator>
    vector_iterator<Iterator> operator-(typename vector_iterator<Iterator>::difference_type n, const vector_iterator<Iterator> &it)
    {
        return (vector_iterator<Iterator>(it.base() - n));
    }

    template <typename it1, typename it2>
    bool operator==(const vector_iterator<it1> &a, const vector_iterator<it2> &b)
    {
        bool res = a.get_ptr() == b.get_ptr();
        return (res);
    }

    template <typename it1, typename it2>
    bool operator!=(const vector_iterator<it1> &a, const vector_iterator<it2> &b)
    {
        bool res = a.get_ptr() != b.get_ptr();
        return (res);
    }

    template <typename it1, typename it2>
    bool operator<(const vector_iterator<it1> &a, const vector_iterator<it2> &b)
    {
        bool res = a.get_ptr() < b.get_ptr();
        return (res);
    }

    template <typename it1, typename it2>
    bool operator<=(const vector_iterator<it1> &a, const vector_iterator<it2> &b)
    {
        bool res = a.get_ptr() <= b.get_ptr();
        return (res);
    }

    template <typename it1, typename it2>
    bool operator>(const vector_iterator<it1> &a, const vector_iterator<it2> &b)
    {
        bool res = a.get_ptr() > b.get_ptr();
        return (res);
    }

    template <typename it1, typename it2>
    bool operator>=(const vector_iterator<it1> &a, const vector_iterator<it2> &b)
    {
        bool res = a.get_ptr() >= b.get_ptr();
        return (res);
    }

	template <typename Iterator>
	std::ostream &operator<<(std::ostream &o, vector_iterator<Iterator> &rhs)
	{
		o << *rhs.get_ptr();
   	 return o;
	}
}
namespace ft
{
	template <typename Iterator>
	class	reverse_iterator
	{
	public:
		/*** We define here the member types of our iterator traits ***/
		typedef Iterator												 		iterator_type; //here it is the pointer
		typedef typename ft::iterator_traits<iterator_type>::value_type 		value_type;
		typedef	typename ft::iterator_traits<iterator_type>::pointer 		 	pointer_type; //here is the reference, it is the same as &reference
		typedef typename ft::iterator_traits<iterator_type>::reference 			reference_type;
		typedef typename ft::iterator_traits<iterator_type>::difference_type 	difference_type; //std::ptrdiff_t is used to do the difference between iterators of the same array and ptrdiff canbe negative
		typedef typename ft::iterator_traits<iterator_type>::iterator_category 	iter_category;

	protected:
		iterator_type	_ptr;
	public:
		reverse_iterator() : _ptr(NULL) {}
		reverse_iterator(iterator_type ptr) : _ptr(ptr) {} // iterator with a pointer
		template <typename iter>
		reverse_iterator(reverse_iterator const &other) : _ptr(other._ptr) {} // iterator avec un autre iterator
		~reverse_iterator() {}
	/***************** MEMBER FUNCTIONS **************/
		/*** return the iterator ***/
		iterator_type base() const
		{
			return (this->_ptr);
		}
	/***************** OPERATOR FUNCTIONS **************/

		reverse_iterator &operator=(const reverse_iterator &rhs)
		{
			if (this != &rhs)
				this->_ptr = rhs._ptr;
			return (*this);
		}

		reverse_iterator &operator++() // prefix incrementation operator
		{
			this->_ptr--;
			return (*this);
		}

		reverse_iterator operator++(int) // postfix incrementation operator
		{
			reverse_iterator temp = *this;
			--this->_ptr;
			return (temp);
		}

		reverse_iterator &operator--() // prefix incrementation operator
		{
			this->_ptr++;
			return (*this);
		}

		reverse_iterator operator--(int) // postfix incrementation operator
		{
			reverse_iterator temp = *this;
			++this->_ptr;
			return (temp);
		}

		// Return a reference to the element at position n in the vector
		difference_type &operator[] (difference_type n)
		{
			return *(this->base()[-n-1]);
		}

		reverse_iterator &operator-=(difference_type n)
		{
			this->_ptr += n;
			return *this;
		}

		reverse_iterator &operator+=(difference_type n)
		{
			this->_ptr -= n;
			return *this;
		}

		// difference _type is the value of the pointer
		reverse_iterator operator+(difference_type n) const
		{
			reverse_iterator res = this->_ptr - n;
			return (res);
		}

		reverse_iterator operator-(difference_type n) const
		{
			reverse_iterator res = this->_ptr + n;
			return (res);
		}

		//renvoie l'adresse pointe par l'iterator
		pointer_type operator->() const
		{
			return(&(operator*()));
		}

		//renvoie la valeur de l'iterator
		reference_type operator*() const
		{
			iterator_type it = this->_ptr;
      	  	it--;
			return(*it);
		}

	bool operator!=(const reverse_iterator &other) const
	{
		bool b = this->_ptr != other._ptr; // If diff b = 1
		return (b);
	}

	bool operator<(const reverse_iterator &other) const
	{
		bool b = this->_ptr < other._ptr;
		return (b);
	}

	bool operator>(const reverse_iterator &other) const
	{
		bool b = this->_ptr > other._ptr;
		return (b);
	}

	bool operator>=(const reverse_iterator &other) const
	{
		bool b = this->_ptr >= other._ptr;
		return (b);
	}

	bool operator<=(const reverse_iterator &other) const
	{
		bool b = this->_ptr <= other._ptr;
		return (b);
	}

	bool operator==(const reverse_iterator &other) const
	{
		return (this->_ptr == other.get_ptr());
	}
	};

	template <typename Iterator>
	reverse_iterator<Iterator> operator+(typename reverse_iterator<Iterator>::difference_type n, const reverse_iterator<Iterator> &it)
	{
		return (reverse_iterator<Iterator>(it.base() - n));
	}

	template <typename Iterator>
	reverse_iterator<Iterator> operator-(typename reverse_iterator<Iterator>::difference_type n, const reverse_iterator<Iterator> &it)
	{
		return (reverse_iterator<Iterator>(it.base() + n));
	}
	template< class Iterator1, class Iterator2 >
	bool operator==( const reverse_iterator<Iterator1>& lhs,
                const reverse_iterator<Iterator2>& rhs )
	{
		return (lhs.base() = rhs.base());
	}

	template< class Iterator1, class Iterator2 >
	bool operator!=( const reverse_iterator<Iterator1>& lhs,
                const reverse_iterator<Iterator2>& rhs )
	{
		return (lhs.base() != rhs.base());
	}

	template< class Iterator1, class Iterator2 >
	bool operator<( const std::reverse_iterator<Iterator1>& lhs,
                const std::reverse_iterator<Iterator2>& rhs )
	{
		return (lhs.base() < rhs.base());
	}

	template< class Iterator1, class Iterator2 >
	bool operator<=( const std::reverse_iterator<Iterator1>& lhs,
                const std::reverse_iterator<Iterator2>& rhs )
	{
		return (lhs.base() <= rhs.base());
	}

	template< class Iterator1, class Iterator2 >
	bool operator>( const std::reverse_iterator<Iterator1>& lhs,
                const std::reverse_iterator<Iterator2>& rhs)
	{
		return (lhs.base() > rhs.base());
	}

	template< class Iterator1, class Iterator2 >
	bool operator>=( const std::reverse_iterator<Iterator1>& lhs,
                const std::reverse_iterator<Iterator2>& rhs)
	{
		return (lhs.base() >= rhs.base());
	}
	template <typename Iterator>
	std::ostream &operator<<(std::ostream &o, reverse_iterator<Iterator> &rhs)
	{
		o << *rhs.base();
   	 	return o;
	}
}

namespace ft
{
template <typename T, typename node_pointer>
class	map_iterator
{
public:
	typedef	T								value_type;
	typedef value_type*						pointer;
	typedef value_type&						reference;
	typedef std::ptrdiff_t 					difference_type;
    typedef std::bidirectional_iterator_tag iterator_category; // Kind of iterator category for map


protected:
    node_pointer _ptr;

public:
/*
**==========================
**     CANONICAL FUNCTIONS
**==========================
*/
	map_iterator() : _ptr(NULL) {}
	map_iterator (node_pointer ptr) : _ptr(ptr) {}
	map_iterator(map_iterator const &obj) : _ptr(obj._ptr) {}
	map_iterator &operator=(map_iterator const &rhs)
	{
		if (this != &rhs)
			this->_ptr = rhs._ptr;
		return (*(this));
	}

	virtual ~map_iterator() {}
/*
**==========================
**     OPERATORS FUNCTION
**==========================
*/
	map_iterator &operator++(void)
	{
		increase();
		return(*this);
	}

	map_iterator operator++(int)
	{
		map_iterator it = *this;
		++(*this);
		return(it);
	}

	map_iterator &operator--(void)
	{
		decrease();
		return(*this);
	}

	map_iterator operator--(int)
	{
		map_iterator it = *this;
		--(*this);
		return(*this);
	}

	reference operator*() const
	{
		return (this->_ptr->value_type);
	}

	pointer operator->() const
	{
		return &(operator*());
	}

	node_pointer get_node()
	{
		return (this->_ptr);
	}

	node_pointer get_node() const
	{
		return (this->_ptr);
	}

	operator map_iterator<const T, node_pointer>() const
	{
		return map_iterator<const T, node_pointer>(this->_ptr);
	}

	template <typename it2>
	bool operator==(const map_iterator<it2, node_pointer> &b) const
	{
		return (this->_ptr == b.get_node());
	}

	template <typename it2>
	bool operator!=(const map_iterator<it2, node_pointer> &b) const
	{
		return (this->_ptr != b.get_node());
	}
	private :

	void	increase()
	{
		// if I have a node in the right
		if (this->_ptr->right)
		{
			// I keep the right node
			this->_ptr = this->_ptr->right;
			//I'm going to the subtree
			while(this->_ptr->left)
				this->_ptr = this->_ptr->left;
		}
		else
		{
			 //sinon, je remonte dans les parents pour retrouver le plus grand directement suivant
			node_pointer temp = this->_ptr;
			this->_ptr = this->_ptr->parent;
			while (this->_ptr->left != temp)
			{
				temp = this->_ptr;
				this->_ptr = this->_ptr->parent;
			}
		}
	}

	void	decrease()
	{
		if (this->_ptr->left)
		{
			this->ptr = this->ptr->left;
			while(this->_ptr->right)
				this->_ptr = this->_ptr->right;
		}
		else
		{
			node_pointer temp = this->_ptr;
			this->_ptr = this->_ptr->parent;
			while (this->_ptr->right != temp)
			{
				temp = this->_ptr;
				this->_ptr = this->_ptr->parent;
			}
		}
	}
};

template <typename One, typename Two>
std::ostream &operator<<(std::ostream &o, map_iterator<One, Two> const &rhs)
{
    o << *rhs.get_node();
	return o;
}
}
#endif