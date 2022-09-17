/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   output_iterator_restrictor.tpp                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jodufour <jodufour@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/17 06:26:53 by jodufour          #+#    #+#             */
/*   Updated: 2022/09/17 06:35:06 by jodufour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef OUTPUT_ITERATOR_RESTRICTOR_TPP
# define OUTPUT_ITERATOR_RESTRICTOR_TPP

# include "iterator.hpp"

namespace ft
{
/**
 * @par		This class is the implementation of the output_iterator_restrictor.
 * 			It is designed to restrict any type of iterator to the Output Iterator requirements only.
 * 			According to the C++98 standard, an Output Iterator must conform to the following requirements:
 * 			- copy constructible (it0(it1))
 * 			- copy assignable (it0 = it1)
 * 			- dereferenceable in write mode (*it = value)
 * 			- prefix incrementable (++it)
 * 			- postfix incrementable (it++)
 * 
 * @tparam	T The type of the value pointed by the iterator.
 * @tparam	Category One of the standard iterator tag to specify the iterator category.
 * @tparam	Diff The type of the difference between two iterators.
 * @tparam	Ptr The type of the pointer to the value pointed by the iterator.
 * @tparam	Ref The type of the reference to the value pointed by the iterator.
 */
template <typename Iterator>
class output_iterator_restrictor
{
public:
	// Member types
	typedef typename Iterator											iterator_type;

	typedef typename iterator_traits<iterator_type>::iterator_category	iterator_category;
	typedef typename iterator_traits<iterator_type>::value_type			value_type;
	typedef typename iterator_traits<iterator_type>::pointer			pointer;
	typedef typename iterator_traits<iterator_type>::reference			reference;
	typedef typename iterator_traits<iterator_type>::					difference_type;

protected:
	// Attributes
	iterator_type	_it;

public:
// ****************************************************************************************************************** //
//                                                    Constructors                                                    //
// ****************************************************************************************************************** //

	/**
	 * @brief	Construct a new output_iterator_restrictor object from an iterator. (wrap constructor)
	 * 
	 * @param	it The iterator to wrap.
	 */
	output_iterator_restrictor(iterator_type const &it) : _it(it) {}

	/**
	 * @brief	Construct a new output_iterator_restrictor object.
	 * 			Allow mutable to constant output_iterator_restrictor conversion. (copy constructor)
	 * 
	 * @tparam	U The type of the output_iterator_restrictor to copy.
	 * 
	 * @param	src The output_iterator_restrictor to copy.
	 */
	template <typename U>
	output_iterator_restrictor(output_iterator_restrictor<U> const &src) : _it(src.base()) {}

// ***************************************************************************************************************** //
//                                                     Accessors                                                     //
// ***************************************************************************************************************** //

	/**
	 * @brief	Get a copy of the wrapped iterator in the output_iterator_restrictor.
	 * 
	 * @return	A copy of the wrapped iterator in the output_iterator_restrictor.
	 */
	inline iterator base(void) const
	{
		return this->_it;
	}

// ***************************************************************************************************************** //
//                                                     Operators                                                     //
// ***************************************************************************************************************** //

	/**
	 * @brief	Assign a new iterator to the output_iterator_restrictor.
	 * 			Allow mutable to constant output_iterator_restrictor conversion. (copy assignment)
	 * 
	 * @tparam	U The type of the output_iterator_restrictor to copy.
	 * 
	 * @param	rhs The output_iterator_restrictor to copy the iterator from.
	 * 
	 * @return	A reference to the assigned output_iterator_restrictor.
	 */
	template <typename U>
	inline output_iterator_restrictor	&operator=(output_iterator_restrictor<U> const &rhs)
	{
		if (this != &rhs)
			this->_it = rhs.base();
		return *this;
	}

	/**
	 * @brief	Dereference the wrapped iterator.
	 * 
	 * @return 	The element pointed by the wrapped iterator.
	 */
	inline reference	operator*(void)
	{
		return *this->_it;
	}

	/**
	 * @brief	Increase the wrapped iterator value by 1. (prefix incrementation)
	 * 
	 * @return	A reference to the incremented output_iterator_restrictor.
	 */
	inline output_iterator_restrictor	&operator++(void)
	{
		++this->_it;
		return *this;
	}

	/**
	 * @brief	Increase the wrapped iterator value by 1. (postfix incrementation)
	 * 
	 * @return	A copy of the output_iterator_restrictor before the incrementation.
	 */
	inline output_iterator_restrictor	operator++(int)
	{
		return output_iterator_restrictor(this->_it++);
	}
};
}

#endif
