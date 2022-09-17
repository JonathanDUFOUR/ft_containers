/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   output_iterator.tpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jodufour <jodufour@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/23 20:50:41 by jodufour          #+#    #+#             */
/*   Updated: 2022/09/17 06:34:32 by jodufour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef OUTPUT_ITERATOR_TPP
# define OUTPUT_ITERATOR_TPP

# include <iterator>

namespace ft
{
/**
 * @par		This class is the implementation of the output_iterator.
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
template <
	typename T,
	typename Category = std::output_iterator_tag,
	typename Diff = std::ptrdiff_t,
	typename Ptr = T *,
	typename Ref = T &>
class output_iterator
{
public:
	// Member types
	typedef Category	iterator_category;
	typedef T			value_type;
	typedef Ptr			pointer;
	typedef Ref			reference;
	typedef Diff		difference_type;

protected:
	// Attributes
	pointer	_ptr;

public:
// ****************************************************************************************************************** //
//                                                    Constructors                                                    //
// ****************************************************************************************************************** //

	/**
	 * @brief	Construct a new output_iterator object from a pointer. (wrap constructor)
	 * 
	 * @param	ptr The pointer to wrap.
	 */
	output_iterator(pointer const ptr) : _ptr(ptr) {}

	/**
	 * @brief	Construct a new output_iterator object.
	 * 			Allow mutable to constant output_iterator conversion. (copy constructor)
	 * 
	 * @tparam	U The type of the output_iterator to copy.
	 * 
	 * @param	src The output_iterator to copy.
	 */
	template <typename U>
	output_iterator(output_iterator<U> const &src) : _ptr(src.base()) {}

// ***************************************************************************************************************** //
//                                                     Accessors                                                     //
// ***************************************************************************************************************** //

	/**
	 * @brief	Get a copy of the wrapped pointer in the output_iterator.
	 * 
	 * @return	A copy of the wrapped pointer in the output_iterator.
	 */
	inline pointer base(void) const
	{
		return this->_ptr;
	}

// ***************************************************************************************************************** //
//                                                     Operators                                                     //
// ***************************************************************************************************************** //

	/**
	 * @brief	Assign a new pointer to the output_iterator.
	 * 			Allow mutable to constant output_iterator conversion. (copy assignment)
	 * 
	 * @tparam	U The type of the output_iterator to copy.
	 * 
	 * @param	rhs The output_iterator to copy the pointer from.
	 * 
	 * @return	A reference to the assigned output_iterator.
	 */
	template <typename U>
	inline output_iterator	&operator=(output_iterator<U> const &rhs)
	{
		if (this != &rhs)
			this->_ptr = rhs.base();
		return *this;
	}

	/**
	 * @brief	Dereference the wrapped pointer.
	 * 
	 * @return 	The element pointed by the wrapped pointer.
	 */
	inline reference	operator*(void)
	{
		return *this->_ptr;
	}

	/**
	 * @brief	Increase the wrapped pointer value by 1. (prefix incrementation)
	 * 
	 * @return	A reference to the incremented output_iterator.
	 */
	inline output_iterator	&operator++(void)
	{
		++this->_ptr;
		return *this;
	}

	/**
	 * @brief	Increase the wrapped pointer value by 1. (postfix incrementation)
	 * 
	 * @return	A copy of the output_iterator before the incrementation.
	 */
	inline output_iterator	operator++(int)
	{
		output_iterator	original(*this);

		++this->_ptr;
		return original;
	}
};
}

#endif
