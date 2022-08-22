/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   output_iterator.tpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jodufour <jodufour@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/23 20:50:41 by jodufour          #+#    #+#             */
/*   Updated: 2022/08/22 23:15:29 by jodufour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef OUTPUT_ITERATOR_TPP
# define OUTPUT_ITERATOR_TPP

# include <iterator>

namespace ft
{
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

private:
	// Attributes
	pointer	_ptr;

public:
// ************************************************************************** //
//                                Constructors                                //
// ************************************************************************** //

	/**
	 * @brief	Construct a new output_iterator object from a pointer.
	 * 			(wrap constructor)
	 * 
	 * @param	ptr The pointer to wrap.
	 */
	output_iterator(pointer const ptr) : _ptr(ptr) {}

	/**
	 * @brief	Construct a new output_iterator object.
	 * 			(copy constructor)
	 */
	output_iterator(output_iterator const &src) : _ptr(src._ptr) {}

// ************************************************************************* //
//                                 Operators                                 //
// ************************************************************************* //

	/**
	 * @brief	Assign a new pointer to the iterator.
	 * 
	 * @param	rhs The output_iterator to copy the pointer from.
	 * 
	 * @return	A reference to the assigned output_iterator.
	 */
	inline output_iterator	&operator=(output_iterator const &rhs)
	{
		this->_ptr = rhs._ptr;
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
	 * @brief	Increase the wrapped pointer value by 1.
	 * 			(prefix incrementation)
	 * 
	 * @return	A reference to the incremented output_iterator.
	 */
	inline output_iterator	&operator++(void)
	{
		++this->_ptr;
		return *this;
	}

	/**
	 * @brief	Increase the wrapped pointer value by 1.
	 * 			(postfix incrementation)
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
