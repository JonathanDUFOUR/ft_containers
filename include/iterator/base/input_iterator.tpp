/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_iterator.tpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jodufour <jodufour@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/23 20:49:20 by jodufour          #+#    #+#             */
/*   Updated: 2022/09/05 16:57:37 by jodufour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef INPUT_ITERATOR_TPP
# define INPUT_ITERATOR_TPP

# include <iterator>

namespace ft
{
/**
 * @par		This class is the implementation of the input_iterator.
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
 * @tparam	T The type of the value pointed by the iterator.
 * @tparam	Category One of the standard iterator tag to specify the iterator category.
 * @tparam	Diff The type of the difference between two iterators.
 * @tparam	Ptr The type of the pointer to the value pointed by the iterator.
 * @tparam	Ref The type of the reference to the value pointed by the iterator.
 */
template <
	typename T,
	typename Category = std::input_iterator_tag,
	typename Diff = std::ptrdiff_t,
	typename Ptr = T *,
	typename Ref = T &>
class input_iterator
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
	 * @brief	Construct a new input_iterator object from a pointer. (wrap constructor)
	 * 
	 * @param	ptr The pointer to wrap.
	 */
	input_iterator(pointer const ptr) : _ptr(ptr) {}

	/**
	 * @brief	Construct a new input_iterator object from another one.
	 * 			Allow mutable to constant input_iterator conversion. (copy constructor)
	 * 
	 * @tparam	U The type of the input_iterator to copy.
	 * 
	 * @param	src The input_iterator to copy.
	 */
	template <typename U>
	input_iterator(input_iterator<U> const &src) : _ptr(src.base()) {}

// ***************************************************************************************************************** //
//                                                     Accessors                                                     //
// ***************************************************************************************************************** //

	/**
	 * @brief	Get the wrapped pointer wrapped in the input_iterator.
	 * 
	 * @return	The wrapped pointer in the input_iterator.
	 */
	inline pointer	base(void) const
	{
		return this->_ptr;
	}

// ***************************************************************************************************************** //
//                                                     Operators                                                     //
// ***************************************************************************************************************** //

	/**
	 * @brief	Assign a new pointer to the input_iterator.
	 * 
	 * @param	rhs The input_iterator to copy the pointer from.
	 * 
	 * @return 	A reference to the assigned input_iterator.
	 */
	inline input_iterator	&operator=(input_iterator const &rhs)
	{
		if (this != &rhs)
			this->_ptr = rhs.base();
		return *this;
	}

	/**
	 * @brief	Check if two input_iterator are equivalent.
	 * 			Allow comparison between mutable and constant input_iterator.
	 * 
	 * @tparam	U The type of the input_iterator to compare with.
	 * 
	 * @param	rhs The input_iterator to compare with.
	 * 
	 * @return 	Either true if the two input_iterator are equivalent, or false if not.
	 */
	template <typename U>
	inline bool	operator==(input_iterator<U> const &rhs) const
	{
		return this->_ptr == rhs.base();
	}

	/**
	 * @brief	Check if two input_iterator are different.
	 * 			Allow comparison between mutable and constant input_iterator.
	 * 
	 * @tparam	U The type of the input_iterator to compare with.
	 * 
	 * @param	rhs The input_iterator to compare with.
	 * 
	 * @return	Either true if the two input_iterator are different, or false if not.
	 */
	template <typename U>
	inline bool	operator!=(input_iterator<U> const &rhs) const
	{
		return this->_ptr != rhs.base();
	}

	/**
	 * @brief	Dereference the wrapped pointer.
	 * 
	 * @return 	The element pointed by the wrapped pointer.
	 */
	inline reference	operator*(void) const
	{
		return *this->_ptr;
	}

	/**
	 * @brief	Get the wrapped pointer value.
	 * 
	 * @return 	The wrapped pointer value.
	 */
	inline pointer	operator->(void) const
	{
		return this->_ptr;
	}

	/**
	 * @brief	Increment the wrapped pointer value by 1. (prefix incrementation)
	 * 
	 * @return 	A reference to the incremented input_iterator.
	 */
	inline input_iterator	&operator++(void)
	{
		++this->_ptr;
		return *this;
	}

	/**
	 * @brief	Increment the wrapped pointer value by 1. (postfix incrementation)
	 * 
	 * @return 	A copy of the input_iterator before the incrementation.
	 */
	inline input_iterator	operator++(int)
	{
		input_iterator	original(*this);

		++this->_ptr;
		return original;
	}
};
}

#endif
