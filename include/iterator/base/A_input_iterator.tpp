/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   A_input_iterator.tpp                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jodufour <jodufour@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/23 20:49:20 by jodufour          #+#    #+#             */
/*   Updated: 2022/09/20 19:18:58 by jodufour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef A_INPUT_ITERATOR_TPP
# define A_INPUT_ITERATOR_TPP

# include <iterator>

namespace ft
{
/**
 * @brief	Abstract class designed to be a base class for any Input Iterator.
 * 
 * @par		According to the C++98 standard, an Input Iterator must conform to the following requirements:
 * 			- copy constructible (it0(it1))
 * 			- copy assignable (it0 = it1)
 * 			- equivalent comparable with another iterator of the same type (it0 == it1)
 * 			- different comparable with another iterator of the same type (it0 != it1)
 * 			- dereferenceable in read mode, and in write mode if the value type is mutable (*it)
 * 			- if `(*it).m` is a valid expression, then so is `it->m` (it->m)
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
	typename Category = std::input_iterator_tag,
	typename Diff = std::ptrdiff_t,
	typename Ptr = T *,
	typename Ref = T &>
class A_input_iterator
{
private:
	// Member types
	typedef A_input_iterator<T, Category, Diff, Ptr, Ref>	_self_type;

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
	// Attributes
	pointer	_ptr;

public:
// ****************************************************************************************************************** //
//                                                    Constructors                                                    //
// ****************************************************************************************************************** //

	/**
	 * @brief	Construct a new A_input_iterator object from a pointer. (wrap constructor)
	 * 
	 * @param	ptr The pointer to wrap.
	 */
	A_input_iterator(pointer const ptr) : _ptr(ptr) {}

	/**
	 * @brief	Construct a new A_input_iterator object from another one.
	 * 			Allow mutable to constant A_input_iterator conversion. (copy constructor)
	 * 
	 * @tparam	U The type of the A_input_iterator to copy.
	 * 
	 * @param	src The A_input_iterator to copy.
	 */
	template <typename _Derived, typename _T>
	A_input_iterator(A_input_iterator<_Derived, _T> const &src) : _ptr(src.base()) {}

// ***************************************************************************************************************** //
//                                                    Destructors                                                    //
// ***************************************************************************************************************** //

	/**
	 * @brief	Destroy the A_input_iterator object.
	 */
	virtual ~A_input_iterator(void) {}

// ***************************************************************************************************************** //
//                                                     Operators                                                     //
// ***************************************************************************************************************** //

	inline virtual bool				operator==(_derived_type const &rhs) const = 0;
	inline virtual bool				operator!=(_derived_type const &rhs) const = 0;

	inline virtual reference		operator*(void) const = 0;

	inline virtual pointer			operator->(void) const = 0;

	inline virtual _derived_type	&operator=(_derived_type const &rhs) = 0;
	inline virtual _derived_type	&operator++(void) = 0;
	inline virtual _derived_type	operator++(int) = 0;
};
}

#endif
