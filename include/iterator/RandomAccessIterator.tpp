/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RandomAccessIterator.tpp                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jodufour <jodufour@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/23 21:22:55 by jodufour          #+#    #+#             */
/*   Updated: 2022/05/24 10:35:48 by jodufour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RANDOMACCESSITERATOR_TPP
# define RANDOMACCESSITERATOR_TPP

# include "BidirectionalIterator.tpp"

namespace ft
{
template <
	typename T,
	typename Category = std::random_access_iterator_tag,
	typename Diff = std::ptrdiff_t,
	typename Ptr = T *,
	typename Ref = T &>
class RandomAccessIterator : public ft::BidirectionalIterator<T, Category, Diff, Ptr, Ref>
{
public:
	// Member types
	using typename BidirectionalIterator<T, Category, Diff, Ptr, Ref>::iterator_category;
	using typename BidirectionalIterator<T, Category, Diff, Ptr, Ref>::value_type;
	using typename BidirectionalIterator<T, Category, Diff, Ptr, Ref>::pointer;
	using typename BidirectionalIterator<T, Category, Diff, Ptr, Ref>::reference;
	using typename BidirectionalIterator<T, Category, Diff, Ptr, Ref>::difference_type;

private:
protected:
public:
	// Operators
	inline RandomAccessIterator &operator+=(difference_type const rhs) // it += n
	{
		this->_ptr += rhs;
		return *this;
	}

	inline RandomAccessIterator &operator-=(difference_type const rhs) // it -= n
	{
		this->_ptr -= rhs;
		return *this;
	}

	inline RandomAccessIterator	operator+(difference_type const rhs) const // it + n
	{
		RandomAccessIterator<value_type, iterator_category, difference_type, pointer, reference> it(*this);

		it += rhs;
		return it;
	}

	inline RandomAccessIterator	operator-(difference_type const rhs) const // it - n
	{
		RandomAccessIterator<value_type, iterator_category, difference_type, pointer, reference> it(*this);

		it -= rhs;
		return it;
	}

	inline difference_type operator-(RandomAccessIterator const &rhs) const // it0 - it1
	{
		return this->_ptr - rhs._ptr;
	}

	inline reference	operator[](difference_type const idx) const // it[idx]
	{
		return *(this->_ptr + idx);
	}

	inline bool	operator<(RandomAccessIterator const &rhs) const // it0 < it1
	{
		return this->_ptr < rhs._ptr;
	}

	inline bool	operator>(RandomAccessIterator const &rhs) const // it0 > it1
	{
		return this->_ptr > rhs._ptr;
	}

	inline bool	operator<=(RandomAccessIterator const &rhs) const // it0 <= it1
	{
		return this->_ptr <= rhs._ptr;
	}

	inline bool	operator>=(RandomAccessIterator const &rhs) const // it0 >= it1
	{
		return this->_ptr >= rhs._ptr;
	}
};
}

#endif
