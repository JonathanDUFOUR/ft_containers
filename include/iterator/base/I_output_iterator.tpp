/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   I_output_iterator.tpp                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jodufour <jodufour@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/23 20:50:41 by jodufour          #+#    #+#             */
/*   Updated: 2022/10/04 12:40:52 by jodufour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef I_OUTPUT_ITERATOR_TPP
# define I_OUTPUT_ITERATOR_TPP

# include <iterator>

namespace ft
{
/**
 * @brief	Interface designed to be a base class for any Output Iterator.
 * 
 * @par		According to the C++98 standard, an Output Iterator must conform to the following requirements:
 * 			- copy constructible (it0(it1))
 * 			- copy assignable (it0 = it1)
 * 			- dereferenceable in write mode (*it = value)
 * 			- prefix incrementable (++it)
 * 			- postfix incrementable (it++)
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
	typename Category = std::output_iterator_tag,
	typename Diff = std::ptrdiff_t,
	typename Ptr = T *,
	typename Ref = T &>
class I_output_iterator
{
private:
	// Member types
	typedef I_output_iterator<T, Category, Diff, Ptr, Ref>	_self_type;

protected:
	// Member types
	typedef Derived											_derived_type;

public:
	// Member types
	typedef T												value_type;
	typedef Category										iterator_category;
	typedef Diff											difference_type;
	typedef Ptr												pointer;
	typedef Ref												reference;

protected:
// ****************************************************************************************************************** //
//                                                    Constructors                                                    //
// ****************************************************************************************************************** //

	/**
	 * @brief	Construct a new I_output_iterator object. (default constructor)
	 */
	I_output_iterator(void) {}

public:

	/**
	 * @brief	Construct a new I_output_iterator object.
	 * 			Allow mutable to constant I_output_iterator conversion. (copy constructor)
	 * 
	 * @tparam	_Derived The type of the concrete derived class of the I_output_iterator to copy.
	 * @tparam	_T The type of the value pointed by the I_output_iterator to copy.
	 * 
	 * @param	src The I_output_iterator to copy.
	 */
	template <typename _Derived, typename _T>
	I_output_iterator(I_output_iterator<_Derived, _T> const &src) {}

// ***************************************************************************************************************** //
//                                                    Destructors                                                    //
// ***************************************************************************************************************** //

	/**
	 * @brief	Destroy the I_output_iterator object.
	 */
	virtual ~I_output_iterator(void) {}

// ***************************************************************************************************************** //
//                                                     Operators                                                     //
// ***************************************************************************************************************** //

	inline virtual reference		operator*(void) = 0;

	inline virtual _derived_type	&operator=(_derived_type const &rhs) = 0;
	inline virtual _derived_type	&operator++(void) = 0;
	inline virtual _derived_type	&operator++(int) = 0;
};
}

#endif
