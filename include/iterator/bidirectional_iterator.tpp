/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bidirectional_iterator.tpp                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jodufour <jodufour@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/23 21:18:24 by jodufour          #+#    #+#             */
/*   Updated: 2022/05/25 10:01:46 by jodufour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BIDIRECTIONAL_ITERATOR_TPP
# define BIDIRECTIONAL_ITERATOR_TPP

# include "forward_iterator.tpp"

namespace ft
{
template <
	typename T,
	typename Category = std::bidirectional_iterator_tag,
	typename Diff = std::ptrdiff_t,
	typename Ptr = T *,
	typename Ref = T &>
class bidirectional_iterator : public ft::forward_iterator<T, Category, Diff, Ptr, Ref>
{
public:
	// Member types
	using typename forward_iterator<T, Category, Diff, Ptr, Ref>::iterator_category;
	using typename forward_iterator<T, Category, Diff, Ptr, Ref>::value_type;
	using typename forward_iterator<T, Category, Diff, Ptr, Ref>::pointer;
	using typename forward_iterator<T, Category, Diff, Ptr, Ref>::reference;
	using typename forward_iterator<T, Category, Diff, Ptr, Ref>::difference_type;

private:
protected:
public:
	// Constructors
	bidirectional_iterator(pointer const ptr = NULL) :
		forward_iterator<T, Category, Diff, Ptr, Ref>(ptr) {}

	// Operators
	inline /* virtual */ bidirectional_iterator &operator--(void) // --it
	{
		--this->_ptr;
		return *this;
	}

	inline /* virtual */ bidirectional_iterator operator--(int) // it--
	{
		bidirectional_iterator	original(*this);

		--this->_ptr;
		return original;
	}
};
}

#endif
