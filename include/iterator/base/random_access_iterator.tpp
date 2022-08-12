/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   random_access_iterator.tpp                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jodufour <jodufour@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/23 21:22:55 by jodufour          #+#    #+#             */
/*   Updated: 2022/08/12 01:40:37 by jodufour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RANDOM_ACCESS_ITERATOR_TPP
# define RANDOM_ACCESS_ITERATOR_TPP

# include "bidirectional_iterator.tpp"

namespace ft
{
template <
	typename T,
	typename Category = std::random_access_iterator_tag,
	typename Diff = std::ptrdiff_t,
	typename Ptr = T *,
	typename Ref = T &>
class random_access_iterator : public bidirectional_iterator<T, Category, Diff, Ptr, Ref>
{
public:
	// Member types
	using typename bidirectional_iterator<T, Category, Diff, Ptr, Ref>::iterator_category;
	using typename bidirectional_iterator<T, Category, Diff, Ptr, Ref>::value_type;
	using typename bidirectional_iterator<T, Category, Diff, Ptr, Ref>::pointer;
	using typename bidirectional_iterator<T, Category, Diff, Ptr, Ref>::reference;
	using typename bidirectional_iterator<T, Category, Diff, Ptr, Ref>::difference_type;

// ************************************************************************** //
//                                Constructors                                //
// ************************************************************************** //

	/**
	 * @brief	Construct a new random_access_iterator object.
	 * 			(default constructor)
	 * 
	 * @param	ptr	The pointer to wrap.
	 */
	random_access_iterator(pointer const ptr = NULL) :
		bidirectional_iterator<
			value_type,
			iterator_category,
			difference_type,
			pointer,
			reference>(ptr) {}

// ************************************************************************* //
//                                Destructors                                //
// ************************************************************************* //

	/**
	 * @brief	Destroy the random_access iterator object.
	 */
	~random_access_iterator(void) {}

// ************************************************************************* //
//                                 Operators                                 //
// ************************************************************************* //

	/**
	 * @brief	Increase the wrapped pointer value by N.
	 * 
	 * @param	rhs The number to increase the pointer by.
	 * 
	 * @return	A reference to the increased random_access_iterator.
	 */
	inline random_access_iterator	&operator+=(difference_type const rhs)
	{
		this->_ptr += rhs;
		return *this;
	}

	/**
	 * @brief	Decrease the wrapped pointer value by N.
	 * 
	 * @param	rhs The number to decrease the pointer by.
	 * 
	 * @return	A reference to the decreased random_access_iterator.
	 */
	inline random_access_iterator	&operator-=(difference_type const rhs)
	{
		this->_ptr -= rhs;
		return *this;
	}

	/**
	 * @brief	Add N to the wrapped pointer value.
	 * 
	 * @param	rhs The number to add to the pointer.
	 * 
	 * @return	A random_access_iterator pointing to the new position.
	 */
	inline random_access_iterator	operator+(difference_type const rhs) const
	{
		random_access_iterator<
			value_type,
			iterator_category,
			difference_type,
			pointer,
			reference> it(*this);

		it += rhs;
		return it;
	}

	/**
	 * @brief	Subtract N from the wrapped pointer value.
	 * 
	 * @param	rhs The number to subtract from the pointer.
	 * 
	 * @return   A random_access_iterator pointing to the new position.
	 */
	inline random_access_iterator	operator-(difference_type const rhs) const
	{
		random_access_iterator<
			value_type,
			iterator_category,
			difference_type,
			pointer,
			reference> it(*this);

		it -= rhs;
		return it;
	}

	/**
	 * @brief	Calculate the distance between two random_access_iterator.
	 * 
	 * @param	rhs The random_access_iterator to calculate the distance to.
	 * 
	 * @return	The distance between the two random_access_iterator.
	 */
	inline difference_type operator-(random_access_iterator const &rhs) const
	{
		return this->_ptr - rhs._ptr;
	}

	/**
	 * @brief	Access to a distant element from the pointed one.
	 * 
	 * @param	idx The index of the element to access.
	 * 
	 * @return	A reference to the distant element.
	 */
	inline reference	operator[](difference_type const idx) const
	{
		return *(this->_ptr + idx);
	}

	/**
	 * @brief	Check if two random_access_iterator are strictly ordered.
	 * 
	 * @param	rhs The random_access_iterator to compare with.
	 * 
	 * @return	Either true if the two random_access_iterator are strictly ordered,
	 * 			or false if not.
	 */
	inline bool	operator<(random_access_iterator const &rhs) const
	{
		return this->_ptr < rhs._ptr;
	}

	/**
	 * @brief	Check if two random_access_iterator are strictly reverse ordered.
	 * 
	 * @param	rhs The random_access_iterator to compare with.
	 * 
	 * @return	Either true if the two random_access_iterator are strictly reverse ordered,
	 * 			or false if not.
	 */
	inline bool	operator>(random_access_iterator const &rhs) const
	{
		return this->_ptr > rhs._ptr;
	}

	/**
	 * @brief	Check if two random_access_iterator are ordered or equivalent.
	 * 
	 * @param	rhs The random_access_iterator to compare with.
	 * 
	 * @return	Either true if the two random_access_iterator are ordered or equivalent,
	 * 			or false if not.
	 */
	inline bool	operator<=(random_access_iterator const &rhs) const
	{
		return this->_ptr <= rhs._ptr;
	}

	/**
	 * @brief	Check if two random_access_iterator are reverse ordered or equivalent.
	 * 
	 * @param	rhs The random_access_iterator to compare with.
	 * 
	 * @return	Either true if the two random_access_iterator are reverse ordered or equivalent,
	 * 			or false if not.
	 */
	inline bool	operator>=(random_access_iterator const &rhs) const
	{
		return this->_ptr >= rhs._ptr;
	}
};
}

#endif
