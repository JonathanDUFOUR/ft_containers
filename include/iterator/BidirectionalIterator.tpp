/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BidirectionalIterator.tpp                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jodufour <jodufour@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/23 21:18:24 by jodufour          #+#    #+#             */
/*   Updated: 2022/05/24 12:03:40 by jodufour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BIDIRECTIONALITERATOR_TPP
# define BIDIRECTIONALITERATOR_TPP

# include "ForwardIterator.tpp"

namespace ft
{
template <
	typename T,
	typename Category = std::bidirectional_iterator_tag,
	typename Diff = std::ptrdiff_t,
	typename Ptr = T *,
	typename Ref = T &>
class BidirectionalIterator : public ft::ForwardIterator<T, Category, Diff, Ptr, Ref>
{
public:
	// Member types
	using typename ForwardIterator<T, Category, Diff, Ptr, Ref>::iterator_category;
	using typename ForwardIterator<T, Category, Diff, Ptr, Ref>::value_type;
	using typename ForwardIterator<T, Category, Diff, Ptr, Ref>::pointer;
	using typename ForwardIterator<T, Category, Diff, Ptr, Ref>::reference;
	using typename ForwardIterator<T, Category, Diff, Ptr, Ref>::difference_type;

private:
protected:
public:
	// Constructors
	BidirectionalIterator(pointer const ptr) :
		ForwardIterator<T, Category, Diff, Ptr, Ref>(ptr) {}

	// Operators
	inline /* virtual */ BidirectionalIterator &operator--(void) // --it
	{
		--this->_ptr;
		return *this;
	}

	inline /* virtual */ BidirectionalIterator operator--(int) // it--
	{
		BidirectionalIterator	original(*this);

		--this->_ptr;
		return original;
	}
};
}

#endif
