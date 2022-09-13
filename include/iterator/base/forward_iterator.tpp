/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   forward_iterator.tpp                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jodufour <jodufour@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/23 20:53:25 by jodufour          #+#    #+#             */
/*   Updated: 2022/09/12 14:23:39 by jodufour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FORWARD_ITERATOR_TPP
# define FORWARD_ITERATOR_TPP

# include "input_iterator.tpp"

namespace ft
{
/**
 * @par		This class is the implementation of the forward_iterator.
 * 			According to the C++98 standard, a Forward Iterator must conform to the following requirements:
 * 			- conform to the Input Iterator requirements
 * 			- default constructible (it) (it())
 * 
 * @tparam	T The type of the value pointed by the iterator.
 * @tparam	Category One of the standard iterator tag to specify the iterator category.
 * @tparam	Diff The type of the difference between two iterators.
 * @tparam	Ptr The type of the pointer to the value pointed by the iterator.
 * @tparam	Ref The type of the reference to the value pointed by the iterator.
 */
template <
	typename T,
	typename Category = std::forward_iterator_tag,
	typename Diff = std::ptrdiff_t,
	typename Ptr = T *,
	typename Ref = T &>
class forward_iterator : public input_iterator<T, Category, Diff, Ptr, Ref>
{
public:
	// Member types
	using typename input_iterator<T, Category, Diff, Ptr, Ref>::	iterator_category;
	using typename input_iterator<T, Category, Diff, Ptr, Ref>::	value_type;
	using typename input_iterator<T, Category, Diff, Ptr, Ref>::	pointer;
	using typename input_iterator<T, Category, Diff, Ptr, Ref>::	reference;
	using typename input_iterator<T, Category, Diff, Ptr, Ref>::	difference_type;

// ****************************************************************************************************************** //
//                                                    Constructors                                                    //
// ****************************************************************************************************************** //

	/**
	 * @brief	Construct a new forward_iterator object. (default constructor)
	 * 
	 * @param	ptr The pointer to wrap.
	 */
	forward_iterator(pointer const ptr = NULL) :
		input_iterator<value_type, iterator_category, difference_type, pointer, reference>(ptr) {}

	/**
	 * @brief	Construct a new forward iterator object from another one.
	 * 			Allow mutable to constant forward_iterator conversion. (copy constructor)
	 * 
	 * @tparam	U The type of the forward_iterator to copy.
	 * 
	 * @param	src The forward_iterator to copy.
	 */
	template <typename U>
	forward_iterator(forward_iterator<U> const &src) :
		input_iterator<value_type, iterator_category, difference_type, pointer, reference>(src) {}

// ***************************************************************************************************************** //
//                                                     Operators                                                     //
// ***************************************************************************************************************** //

	/**
	 * @brief	Check if two forward_iterator are equivalent.
	 * 			Allow comparison between mutable and constant forward_iterator.
	 * 
	 * @tparam	U The type of the forward_iterator to compare with.
	 * 
	 * @param	rhs The forward_iterator to compare with.
	 * 
	 * @return 	Either true if the two forward_iterator are equivalent, or false if not.
	 */
	template <typename U>
	inline bool	operator==(forward_iterator<U> const &rhs) const
	{
		return this->_ptr == rhs.base();
	}

	/**
	 * @brief	Check if two forward_iterator are different.
	 * 			Allow comparison between mutable and constant forward_iterator.
	 * 
	 * @tparam	U The type of the forward_iterator to compare with.
	 * 
	 * @param	rhs The forward_iterator to compare with.
	 * 
	 * @return	Either true if the two forward_iterator are different, or false if not.
	 */
	template <typename U>
	inline bool	operator!=(forward_iterator<U> const &rhs) const
	{
		return this->_ptr != rhs.base();
	}
};
}

#endif
