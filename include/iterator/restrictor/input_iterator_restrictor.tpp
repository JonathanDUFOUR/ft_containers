/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_iterator_restrictor.tpp                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jodufour <jodufour@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/17 06:06:43 by jodufour          #+#    #+#             */
/*   Updated: 2022/09/18 07:08:42 by jodufour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef INPUT_ITERATOR_RESTRICTOR_TPP
# define INPUT_ITERATOR_RESTRICTOR_TPP

# include "iterator.hpp"

namespace ft
{
/**
 * @par		This class is the implementation of the input_iterator_restrictor.
 * 			It is designed to restrict any type of iterator to the Input Iterator requirements only.
 * 			According to the C++98 standard, an Input Iterator must conform to the following requirements:
 * 			- copy constructible (it0(it1))
 * 			- copy assignable (it0 = it1)
 * 			- equivalent comparable with another iterator of the same type (it0 == it1)
 * 			- different comparable with another iterator of the same type (it0 != it1)
 * 			- dereferenceable in read mode, and in write mode if the value type is mutable (*it)
 * 			- if `(*it).m` is a valid expression, then so is `it->m` (it->m)
 * 			- prefix incrementable (++it)
 * 			- postfix incrementable (it++)
 * 
 * @tparam	Iterator The type of the iterator to restrict.
 */
template <typename Iterator>
class input_iterator_restrictor
{
public:
	// Member types
	typedef Iterator													iterator_type;

	typedef typename iterator_traits<iterator_type>::iterator_category	iterator_category;
	typedef typename iterator_traits<iterator_type>::value_type			value_type;
	typedef typename iterator_traits<iterator_type>::pointer			pointer;
	typedef typename iterator_traits<iterator_type>::reference			reference;
	typedef typename iterator_traits<iterator_type>::difference_type	difference_type;

protected:
	// Attributes
	iterator_type	_it;

public:
// ****************************************************************************************************************** //
//                                                    Constructors                                                    //
// ****************************************************************************************************************** //

	/**
	 * @brief	Construct a new input_iterator_restrictor object from an iterator. (wrap constructor)
	 * 
	 * @param	it The iterator to wrap.
	 */
	input_iterator_restrictor(iterator_type const &it) : _it(it) {}

	/**
	 * @brief	Construct a new input_iterator_restrictor object from another one.
	 * 			Allow mutable to constant input_iterator_restrictor conversion. (copy constructor)
	 * 
	 * @tparam	U The type of the input_iterator_restrictor to copy.
	 * 
	 * @param	src The input_iterator_restrictor to copy.
	 */
	template <typename U>
	input_iterator_restrictor(input_iterator_restrictor<U> const &src) : _it(src.base()) {}

// ***************************************************************************************************************** //
//                                                     Accessors                                                     //
// ***************************************************************************************************************** //

	/**
	 * @brief	Get a copy of the wrapped iterator in the input_iterator_restrictor.
	 * 
	 * @return	A copy of the wrapped iterator in the input_iterator_restrictor.
	 */
	inline iterator_type	base(void) const
	{
		return this->_it;
	}

// ***************************************************************************************************************** //
//                                                     Operators                                                     //
// ***************************************************************************************************************** //

	/**
	 * @brief	Assign a new iterator to the input_iterator_restrictor.
	 * 			Allow mutable to constant input_iterator_restrictor conversion.
	 * 
	 * @tparam	U The type of the input_iterator_restrictor to copy.
	 * 
	 * @param	rhs The input_iterator_restrictor to copy the iterator from.
	 * 
	 * @return 	A reference to the assigned input_iterator_restrictor.
	 */
	template <typename U>
	inline input_iterator_restrictor	&operator=(input_iterator_restrictor<U> const &rhs)
	{
		if (this != &rhs)
			this->_it = rhs.base();
		return *this;
	}

	/**
	 * @brief	Check if two input_iterator_restrictor are equivalent.
	 * 			Allow comparison between mutable and constant input_iterator_restrictor.
	 * 
	 * @tparam	U The type of the input_iterator_restrictor to compare with.
	 * 
	 * @param	rhs The input_iterator_restrictor to compare with.
	 * 
	 * @return 	Either true if the two input_iterator_restrictor are equivalent, or false if not.
	 */
	template <typename U>
	inline bool	operator==(input_iterator_restrictor<U> const &rhs) const
	{
		return this->_it == rhs.base();
	}

	/**
	 * @brief	Check if two input_iterator_restrictor are different.
	 * 			Allow comparison between mutable and constant input_iterator_restrictor.
	 * 
	 * @tparam	U The type of the input_iterator_restrictor to compare with.
	 * 
	 * @param	rhs The input_iterator_restrictor to compare with.
	 * 
	 * @return	Either true if the two input_iterator_restrictor are different, or false if not.
	 */
	template <typename U>
	inline bool	operator!=(input_iterator_restrictor<U> const &rhs) const
	{
		return this->_it != rhs.base();
	}

	/**
	 * @brief	Dereference the wrapped iterator.
	 * 
	 * @return 	The element pointed by the wrapped iterator.
	 */
	inline reference	operator*(void) const
	{
		return *this->_it;
	}

	/**
	 * @brief	Get the wrapped pointer value.
	 * 
	 * @return 	The wrapped pointer value.
	 */
	inline pointer	operator->(void) const
	{
		return this->_it.operator->();
	}

	/**
	 * @brief	Increment the wrapped iterator value by 1. (prefix incrementation)
	 * 
	 * @return 	A reference to the incremented input_iterator_restrictor.
	 */
	inline input_iterator_restrictor	&operator++(void)
	{
		++this->_it;
		return *this;
	}

	/**
	 * @brief	Increment the wrapped iterator value by 1. (postfix incrementation)
	 * 
	 * @return 	A copy of the input_iterator_restrictor before the incrementation.
	 */
	inline input_iterator_restrictor	operator++(int)
	{
		return input_iterator_restrictor(this->_it++);
	}
};
}

#endif
