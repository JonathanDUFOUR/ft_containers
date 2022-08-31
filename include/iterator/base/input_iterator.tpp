/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_iterator.tpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jodufour <jodufour@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/23 20:49:20 by jodufour          #+#    #+#             */
/*   Updated: 2022/08/31 08:35:30 by jodufour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef INPUT_ITERATOR_TPP
# define INPUT_ITERATOR_TPP

# include <iterator>

namespace ft
{
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

// ****************************************************************************************************************** //
//                                                    Constructors                                                    //
// ****************************************************************************************************************** //

	/**
	 * @brief	Construct a new input_iterator object. (default constructor)
	 */
	input_iterator(void) : _ptr(NULL) {}

public:

	/**
	 * @brief	Construct a new input_iterator object from a pointer. (wrap constructor)
	 * 
	 * @param	ptr The pointer to wrap.
	 */
	input_iterator(pointer const ptr) : _ptr(ptr) {}

	/**
	 * @brief	Construct a new input_iterator object from another one. (copy constructor)
	 * 
	 * @param	src The iterator to copy.
	 */
	input_iterator(input_iterator const &src) : _ptr(src._ptr) {}

// ***************************************************************************************************************** //
//                                                     Accessors                                                     //
// ***************************************************************************************************************** //

	/**
	 * @brief	Get the pointer wrapped by the iterator.
	 * 
	 * @return	The pointer wrapped by the iterator.
	 */
	pointer	base(void) const
	{
		return _ptr;
	}

// ***************************************************************************************************************** //
//                                                     Operators                                                     //
// ***************************************************************************************************************** //

	/**
	 * @brief	Assign a new pointer to the iterator.
	 * 
	 * @param	rhs The input_iterator to copy the pointer from.
	 * 
	 * @return 	A reference to the assigned input_iterator.
	 */
	inline input_iterator	&operator=(input_iterator const &rhs)
	{
		this->_ptr = rhs._ptr;
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
		return this->base() == rhs.base();
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
		return this->base() != rhs.base();
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
	 * @brief	Increase the wrapped pointer value by 1. (prefix incrementation)
	 * 
	 * @return 	A reference to the incremented input_iterator.
	 */
	inline input_iterator	&operator++(void)
	{
		++this->_ptr;
		return *this;
	}

	/**
	 * @brief	Increase the wrapped pointer value by 1. (postfix incrementation)
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
