/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   forward_iterator.tpp                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jodufour <jodufour@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/23 20:53:25 by jodufour          #+#    #+#             */
/*   Updated: 2022/05/25 10:01:07 by jodufour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FORWARD_ITERATOR_TPP
# define FORWARD_ITERATOR_TPP

# include "input_iterator.tpp"

namespace ft
{
template <
	typename T,
	typename Category = std::forward_iterator_tag,
	typename Diff = std::ptrdiff_t,
	typename Ptr = T *,
	typename Ref = T &>
class forward_iterator : public input_iterator<T, Category, Diff, Ptr, Ref>
{
public:
	// Member types
	using typename input_iterator<T, Category, Diff, Ptr, Ref>::iterator_category;
	using typename input_iterator<T, Category, Diff, Ptr, Ref>::value_type;
	using typename input_iterator<T, Category, Diff, Ptr, Ref>::pointer;
	using typename input_iterator<T, Category, Diff, Ptr, Ref>::reference;
	using typename input_iterator<T, Category, Diff, Ptr, Ref>::difference_type;

private:
protected:
public:
	// Constructors
	forward_iterator(pointer const ptr = NULL) :
		input_iterator<T, Category, Diff, Ptr, Ref>(ptr) {}

	forward_iterator(forward_iterator const &src) :
		input_iterator<T, Category, Diff, Ptr, Ref>(src) {}
};
}

#endif
