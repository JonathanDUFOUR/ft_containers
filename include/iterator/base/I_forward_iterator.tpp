/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   I_forward_iterator.tpp                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jodufour <jodufour@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/23 20:53:25 by jodufour          #+#    #+#             */
/*   Updated: 2022/10/04 12:41:00 by jodufour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef I_FORWARD_ITERATOR_TPP
# define I_FORWARD_ITERATOR_TPP

# include "I_input_iterator.tpp"

namespace ft
{
/**
 * @brief	Interface designed to be a base class for any Forward Iterator.
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
class I_forward_iterator : public I_input_iterator<Derived, T, Category, Diff, Ptr, Ref>
{
private:
	// Member types
	typedef I_input_iterator<Derived, T, Category, Diff, Ptr, Ref>		_base_type;
	typedef I_forward_iterator<Derived, T, Category, Diff, Ptr, Ref>	_self_type;

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
	 * @brief	Construct a new I_forward_iterator object. (default constructor)
	 * 
	 * @param	ptr The pointer to wrap.
	 */
	I_forward_iterator(void) :
		_base_type() {}

	/**
	 * @brief	Construct a new forward iterator object from another one.
	 * 			Allow mutable to constant I_forward_iterator conversion. (copy constructor)
	 * 
	 * @tparam	_Derived The type of the concrete derived class of the I_forward_iterator to copy.
	 * @tparam	_T The type of the value pointed by the I_forward_iterator to copy.
	 * 
	 * @param	src The I_forward_iterator to copy.
	 */
	template <typename _Derived, typename _T>
	I_forward_iterator(I_forward_iterator<_Derived, _T> const &src) :
		_base_type(src) {}

// ***************************************************************************************************************** //
//                                                    Destructors                                                    //
// ***************************************************************************************************************** //

	/**
	 * @brief	Destroy the I_forward_iterator object.
	 */
	virtual ~I_forward_iterator(void) {}
};
}

#endif
