/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   A_forward_iterator.tpp                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jodufour <jodufour@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/23 20:53:25 by jodufour          #+#    #+#             */
/*   Updated: 2022/09/19 21:32:47 by jodufour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef A_FORWARD_ITERATOR_TPP
# define A_FORWARD_ITERATOR_TPP

# include "A_input_iterator.tpp"

namespace ft
{
/**
 * @brief	Abstract class designed to be a base class for any Forward Iterator.
 * 
 * @par		According to the C++98 standard, a Forward Iterator must conform to the following requirements:
 * 			- conform to the Input Iterator requirements
 * 			- default constructible (it) (it())
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
	typename Category = std::forward_iterator_tag,
	typename Diff = std::ptrdiff_t,
	typename Ptr = T *,
	typename Ref = T &>
class A_forward_iterator : public A_input_iterator<Derived, T, Category, Diff, Ptr, Ref>
{
private:
	// Member types
	typedef A_input_iterator<Derived, T, Category, Diff, Ptr, Ref>		_base_type;
	typedef A_forward_iterator<Derived, T, Category, Diff, Ptr, Ref>	_self_type;

protected:
	// Member types
	using typename _base_type::											_derived_type;

public:
	// Member types
	using typename _base_type::											value_type;
	using typename _base_type::											iterator_category;
	using typename _base_type::											difference_type;
	using typename _base_type::											pointer;
	using typename _base_type::											reference;

// ****************************************************************************************************************** //
//                                                    Constructors                                                    //
// ****************************************************************************************************************** //

	/**
	 * @brief	Construct a new A_forward_iterator object. (default constructor)
	 * 
	 * @param	ptr The pointer to wrap.
	 */
	A_forward_iterator(pointer const ptr = NULL) :
		_base_type(ptr) {}

	/**
	 * @brief	Construct a new forward iterator object from another one.
	 * 			Allow mutable to constant A_forward_iterator conversion. (copy constructor)
	 * 
	 * @tparam	U The type of the A_forward_iterator to copy.
	 * 
	 * @param	src The A_forward_iterator to copy.
	 */
	template <typename _Derived, typename _T>
	A_forward_iterator(A_forward_iterator<_Derived, _T> const &src) :
		_base_type(src) {}

// ***************************************************************************************************************** //
//                                                    Destructors                                                    //
// ***************************************************************************************************************** //

	/**
	 * @brief	Destroy the A_forward_iterator object.
	 */
	virtual ~A_forward_iterator(void) {}
};
}

#endif
