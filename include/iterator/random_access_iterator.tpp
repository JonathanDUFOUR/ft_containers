/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   random_access_iterator.tpp                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jodufour <jodufour@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/23 21:22:55 by jodufour          #+#    #+#             */
/*   Updated: 2022/05/30 12:31:58 by jodufour         ###   ########.fr       */
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
class random_access_iterator : public ft::bidirectional_iterator<T, Category, Diff, Ptr, Ref>
{
public:
	// Member types
	using typename bidirectional_iterator<T, Category, Diff, Ptr, Ref>::iterator_category;
	using typename bidirectional_iterator<T, Category, Diff, Ptr, Ref>::value_type;
	using typename bidirectional_iterator<T, Category, Diff, Ptr, Ref>::pointer;
	using typename bidirectional_iterator<T, Category, Diff, Ptr, Ref>::reference;
	using typename bidirectional_iterator<T, Category, Diff, Ptr, Ref>::difference_type;

	// Constructors
	random_access_iterator(pointer const ptr = NULL) :
		bidirectional_iterator<
			value_type,
			iterator_category,
			difference_type,
			pointer,
			reference>(ptr) {}

	// Destructors
	~random_access_iterator(void) {}

	// Operators
	inline random_access_iterator	&operator+=(difference_type const rhs) // it += n
	{
		this->_ptr += rhs;
		return *this;
	}

	inline random_access_iterator	&operator-=(difference_type const rhs) // it -= n
	{
		this->_ptr -= rhs;
		return *this;
	}

	inline random_access_iterator	operator+(difference_type const rhs) const // it + n
	{
		random_access_iterator<value_type, iterator_category, difference_type, pointer, reference> it(*this);

		it += rhs;
		return it;
	}

	inline random_access_iterator	operator-(difference_type const rhs) const // it - n
	{
		random_access_iterator<value_type, iterator_category, difference_type, pointer, reference> it(*this);

		it -= rhs;
		return it;
	}

	inline difference_type operator-(random_access_iterator const &rhs) const // it0 - it1
	{
		return this->_ptr - rhs._ptr;
	}

	inline reference	operator[](difference_type const idx) const // it[idx]
	{
		return *(this->_ptr + idx);
	}

	inline bool	operator<(random_access_iterator const &rhs) const // it0 < it1
	{
		return this->_ptr < rhs._ptr;
	}

	inline bool	operator>(random_access_iterator const &rhs) const // it0 > it1
	{
		return this->_ptr > rhs._ptr;
	}

	inline bool	operator<=(random_access_iterator const &rhs) const // it0 <= it1
	{
		return this->_ptr <= rhs._ptr;
	}

	inline bool	operator>=(random_access_iterator const &rhs) const // it0 >= it1
	{
		return this->_ptr >= rhs._ptr;
	}
};
}

#endif
