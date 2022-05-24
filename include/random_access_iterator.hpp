/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   random_access_iterator.hpp                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jodufour <jodufour@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/23 21:22:55 by jodufour          #+#    #+#             */
/*   Updated: 2022/05/24 05:55:39 by jodufour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RANDOM_ACCESS_ITERATOR_HPP
# define RANDOM_ACCESS_ITERATOR_HPP

# include "bidirectional_iterator.hpp"

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

private:
protected:
public:
	// Operators
	random_access_iterator &operator+=(Diff const rhs) // it += n
	{
		this->_ptr += rhs;
		return *this;
	}

	random_access_iterator &operator-=(Diff const rhs) // it -= n
	{
		this->_ptr -= rhs;
		return *this;
	}

	random_access_iterator	operator+(Diff const rhs) const // it + n
	{
		random_access_iterator<T, Category, Diff, Ptr, Ref> it(*this);

		it += rhs;
		return it;
	}

	random_access_iterator	operator-(Diff const rhs) const // it - n
	{
		random_access_iterator<T, Category, Diff, Ptr, Ref> it(*this);

		it -= rhs;
		return it;
	}

	difference_type operator-(random_access_iterator const &rhs) const // it0 - it1
	{
		return this->_ptr - rhs._ptr;
	}

	reference	operator[](Diff const idx) const // it[n]
	{
		return *(this->_ptr + idx);
	}

	bool	operator<(random_access_iterator const &rhs) const // it0 < it1
	{
		return this->_ptr < rhs._ptr;
	}

	bool	operator>(random_access_iterator const &rhs) const // it0 > it1
	{
		return this->_ptr > rhs._ptr;
	}

	bool	operator<=(random_access_iterator const &rhs) const // it0 <= it1
	{
		return this->_ptr <= rhs._ptr;
	}

	bool	operator>=(random_access_iterator const &rhs) const // it0 >= it1
	{
		return this->_ptr >= rhs._ptr;
	}
};
}

#endif
