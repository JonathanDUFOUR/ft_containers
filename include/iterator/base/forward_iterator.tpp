/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   forward_iterator.tpp                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jodufour <jodufour@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/23 20:53:25 by jodufour          #+#    #+#             */
/*   Updated: 2022/08/31 08:35:11 by jodufour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FORWARD_ITERATOR_TPP
# define FORWARD_ITERATOR_TPP

# include "input_iterator.tpp"

namespace ft
{
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
	using typename input_iterator<T, Category, Diff, Ptr, Ref>::iterator_category;
	using typename input_iterator<T, Category, Diff, Ptr, Ref>::value_type;
	using typename input_iterator<T, Category, Diff, Ptr, Ref>::pointer;
	using typename input_iterator<T, Category, Diff, Ptr, Ref>::reference;
	using typename input_iterator<T, Category, Diff, Ptr, Ref>::difference_type;

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
	 * @brief	Construct a new forward iterator object from another one. (copy constructor)
	 * 
	 * @param	src The iterator to copy.
	 */
	forward_iterator(forward_iterator const &src) :
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
		return this->base() == rhs.base();
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
		return this->base() != rhs.base();
	}
};
}

#endif
