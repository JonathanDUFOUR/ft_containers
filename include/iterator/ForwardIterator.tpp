/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ForwardIterator.tpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jodufour <jodufour@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/23 20:53:25 by jodufour          #+#    #+#             */
/*   Updated: 2022/05/24 12:03:52 by jodufour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FORWARDITERATOR_TPP
# define FORWARDITERATOR_TPP

# include "InputIterator.tpp"

namespace ft
{
template <
	typename T,
	typename Category = std::forward_iterator_tag,
	typename Diff = std::ptrdiff_t,
	typename Ptr = T *,
	typename Ref = T &>
class ForwardIterator : public InputIterator<T, Category, Diff, Ptr, Ref>
{
public:
	// Member types
	using typename InputIterator<T, Category, Diff, Ptr, Ref>::iterator_category;
	using typename InputIterator<T, Category, Diff, Ptr, Ref>::value_type;
	using typename InputIterator<T, Category, Diff, Ptr, Ref>::pointer;
	using typename InputIterator<T, Category, Diff, Ptr, Ref>::reference;
	using typename InputIterator<T, Category, Diff, Ptr, Ref>::difference_type;

private:
protected:
public:
	// Constructors
	ForwardIterator(void) :
		InputIterator<T, Category, Diff, Ptr, Ref>() {}

	ForwardIterator(pointer const ptr) :
		InputIterator<T, Category, Diff, Ptr, Ref>(ptr) {}

	ForwardIterator(ForwardIterator const &src) :
		InputIterator<T, Category, Diff, Ptr, Ref>(src) {}
};
}

#endif
