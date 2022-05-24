/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bidirectional_iterator.hpp                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jodufour <jodufour@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/23 21:18:24 by jodufour          #+#    #+#             */
/*   Updated: 2022/05/24 05:52:48 by jodufour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BIDIRECTIONAL_ITERATOR_HPP
# define BIDIRECTIONAL_ITERATOR_HPP

# include "forward_iterator.hpp"

namespace ft
{
template <
	typename T,
	typename Category = std::forward_iterator_tag,
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
	// Operators
	inline bidirectional_iterator &operator--(void) // --it
	{
		--this->_ptr;
		return *this;
	}

	inline bidirectional_iterator operator--(int) // it--
	{
		bidirectional_iterator original(*this);

		--this->_ptr;
		return original;
	}
};
}

#endif
