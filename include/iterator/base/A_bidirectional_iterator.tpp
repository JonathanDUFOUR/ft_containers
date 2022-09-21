/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   A_bidirectional_iterator.tpp                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jodufour <jodufour@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/23 21:18:24 by jodufour          #+#    #+#             */
/*   Updated: 2022/09/19 21:34:23 by jodufour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef A_BIDIRECTIONAL_ITERATOR_TPP
# define A_BIDIRECTIONAL_ITERATOR_TPP

# include "A_forward_iterator.tpp"

namespace ft
{
/**
 * @brief	Abstract class designed to be a base class for any Bidirectional Iterator.
 * 
 * @par		According to the C++98 standard, a Bidirectional Iterator must conform to the following requirements:
 * 			- conform to the Forward Iterator requirements
 * 			- prefix decrementable (--it)
 * 			- postfix decrementable (it--)
 * 
 * @tparam	Derived The type of the derived iterator.
 * @tparam	T The type of the value pointed by the iterator.
 * @tparam	Category One of the standard iterator tag to specify the iterator category.
 * @tparam	Diff The type of the difference between two iterators.
 * @tparam	Ptr The type of the pointer to the value pointed by the iterator.
 * @tparam	Ref The type of the reference to the value pointed by the iterator.
 */
template <
	typename Derived,
	typename T,
	typename Category = std::bidirectional_iterator_tag,
	typename Diff = std::ptrdiff_t,
	typename Ptr = T *,
	typename Ref = T &>
class A_bidirectional_iterator : public A_forward_iterator<Derived, T, Category, Diff, Ptr, Ref>
{
private:
	// Member types
	typedef A_forward_iterator<Derived, T, Category, Diff, Ptr, Ref>		_base_type;
	typedef A_bidirectional_iterator<Derived, T, Category, Diff, Ptr, Ref>	_self_type;

protected:
	// Member types
	using typename _base_type::												_derived_type;

public:
	// Member types
	using typename _base_type::												value_type;
	using typename _base_type::												iterator_category;
	using typename _base_type::												difference_type;
	using typename _base_type::												pointer;
	using typename _base_type::												reference;

// ****************************************************************************************************************** //
//                                                    Constructors                                                    //
// ****************************************************************************************************************** //

	/**
	 * @brief	Construct a new A_bidirectional_iterator object. (default constructor)
	 * 
	 * @param	ptr The pointer to wrap.
	 */
	A_bidirectional_iterator(pointer const ptr = NULL) :
		_base_type(ptr) {}

	/**
	 * @brief	Construct a new A_bidirectional_iterator object.
	 * 			Allow mutable to constant A_bidirectional_iterator conversion. (copy constructor)
	 * 
	 * @tparam	U The type of the A_bidirectional_iterator to copy.
	 * 
	 * @param	src The A_bidirectional_iterator to copy.
	 */
	template <typename _Derived, typename _T>
	A_bidirectional_iterator(A_bidirectional_iterator<_Derived, _T> const &src) :
		_base_type(src) {}

// ***************************************************************************************************************** //
//                                                    Destructors                                                    //
// ***************************************************************************************************************** //

	/**
	 * @brief	Destroy the A_bidirectional_iterator object.
	 */
	virtual ~A_bidirectional_iterator(void) {}

// ***************************************************************************************************************** //
//                                                     Operators                                                     //
// ***************************************************************************************************************** //

	inline virtual _derived_type	&operator--(void) = 0;
	inline virtual _derived_type	operator--(int) = 0;
};
}

#endif
