/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   A_random_access_iterator.tpp                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jodufour <jodufour@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/23 21:22:55 by jodufour          #+#    #+#             */
/*   Updated: 2022/09/20 18:55:11 by jodufour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ARANDOM_ACCESS_ITERATOR_TPP
# define ARANDOM_ACCESS_ITERATOR_TPP

# include "A_bidirectional_iterator.tpp"

namespace ft
{
/**
 * @brief	Abstract class designed to be a base class for any Random Access Iterator.
 * 
 * @par		According to the C++98 standard, a Random Access Iterator must conform to the following requirements:
 * 			- conform to the Bidirectional Iterator requirements
 * 			- distance incrementable (it += n)
 * 			- distance decrementable (it -= n)
 * 			- distance addable (it + n || n + it)
 * 			- distance subtractable (it - n)
 * 			- distance calculable (it0 - it1)
 * 			- subscriptable (it[n])
 * 			- lower comparable (it0 < it1)
 * 			- greater comparable (it0 > it1)
 * 			- lower or equal comparable (it0 <= it1)
 * 			- greater or equal comparable (it0 >= it1)
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
	typename Category = std::random_access_iterator_tag,
	typename Diff = std::ptrdiff_t,
	typename Ptr = T *,
	typename Ref = T &>
class A_random_access_iterator : public A_bidirectional_iterator<Derived, T, Category, Diff, Ptr, Ref>
{
private:
	// Member types
	typedef A_bidirectional_iterator<Derived, T, Category, Diff, Ptr, Ref>	_base_type;
	typedef A_random_access_iterator<Derived, T, Category, Diff, Ptr, Ref>	_self_type;

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
	 * @brief	Construct a new A_random_access_iterator object. (default constructor)
	 * 
	 * @param	ptr	The pointer to wrap.
	 */
	A_random_access_iterator(pointer const ptr = NULL) :
		_base_type(ptr) {}

	/**
	 * @brief	Construct a new A_random_access_iterator object.
	 * 			Allow mutable to constant A_random_access_iterator conversion. (copy constructor)
	 * 
	 * @tparam	U The type of the A_random_access_iterator to copy.
	 * 
	 * @param	src The A_random_access_iterator to copy.
	 */
	template <typename _Derived, typename _T>
	A_random_access_iterator(A_random_access_iterator<_Derived, _T> const &src) :
		_base_type(src) {}

// ***************************************************************************************************************** //
//                                                    Destructors                                                    //
// ***************************************************************************************************************** //

	/**
	 * @brief	Destroy the A_random_access_iterator object.
	 */
	virtual ~A_random_access_iterator(void) {}

// ***************************************************************************************************************** //
//                                                     Operators                                                     //
// ***************************************************************************************************************** //

	inline virtual bool				operator<(_derived_type const &rhs) const = 0;
	inline virtual bool				operator>(_derived_type const &rhs) const = 0;
	inline virtual bool				operator<=(_derived_type const &rhs) const = 0;
	inline virtual bool				operator>=(_derived_type const &rhs) const = 0;

	inline virtual _derived_type	&operator+=(difference_type const rhs) = 0;
	inline virtual _derived_type	&operator-=(difference_type const rhs) = 0;
	inline virtual _derived_type	operator+(difference_type const rhs) const = 0;
	inline virtual _derived_type	operator-(difference_type const rhs) const = 0;

	inline virtual difference_type	operator-(_derived_type const &rhs) const = 0;

	inline virtual reference		operator[](difference_type const idx) const = 0;
};
}

#endif
