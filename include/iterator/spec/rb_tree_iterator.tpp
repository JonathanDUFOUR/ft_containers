/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rb_tree_iterator.tpp                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jodufour <jodufour@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/22 22:37:54 by jodufour          #+#    #+#             */
/*   Updated: 2022/09/02 10:05:14 by jodufour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RB_TREE_ITERATOR_TPP
# define RB_TREE_ITERATOR_TPP

# include "iterator/base/bidirectional_iterator.tpp"
# include "iterator.hpp"

namespace ft
{
template <typename Iterator>
class rb_tree_iterator : public bidirectional_iterator<
	typename iterator_traits<Iterator>::value_type,
	typename iterator_traits<Iterator>::iterator_category,
	typename iterator_traits<Iterator>::difference_type,
	typename iterator_traits<Iterator>::pointer,
	typename iterator_traits<Iterator>::reference>
{
public:
	// Member types
	typedef typename iterator_traits<Iterator>::iterator_category	iterator_category;
	typedef typename iterator_traits<Iterator>::value_type			value_type;
	typedef typename iterator_traits<Iterator>::pointer				pointer;
	typedef typename iterator_traits<Iterator>::reference			reference;
	typedef typename iterator_traits<Iterator>::difference_type		difference_type;

// ****************************************************************************************************************** //
//                                                    Constructors                                                    //
// ****************************************************************************************************************** //

	/**
	 * @brief	Construct a new rb_tree_iterator object. (default constructor)
	 * 
	 * @param	ptr	The pointer to wrap.
	 */
	rb_tree_iterator(pointer const ptr = NULL) :
		bidirectional_iterator<value_type, iterator_category, difference_type, pointer, reference>(ptr) {}

	/**
	 * @brief	Construct a new rb_tree_iterator object from another one.
	 * 			Allow mutable to constant rb_tree_iterator conversion. (copy constructor)
	 * 
	 * @tparam	_Iterator The type of the rb_tree_iterator to copy.
	 * 
	 * @param	src The rb_tree_iterator to copy.
	 */
	template <typename _Iterator>
	rb_tree_iterator(rb_tree_iterator<_Iterator> const &src) :
		bidirectional_iterator<value_type, iterator_category, difference_type, pointer, reference>(src.base()) {}

// ***************************************************************************************************************** //
//                                                     Operators                                                     //
// ***************************************************************************************************************** //

	/**
	 * @brief	Update the wrapped pointer to pointe to the next element. (prefix incrementation)
	 * 
	 * @return	A reference to the incremented rb_tree_iterator.
	 */
	inline rb_tree_iterator &operator++(void)
	{
		if (this->child[RIGHT])
		{
			this->_pointer = this->child[RIGHT];
			while (this->child[LEFT])
				this->_pointer = this->child[LEFT];
		}
		else
		{
			while (this->parent && this->_pointer == this->parent->child[RIGHT])
				this->_pointer = this->parent;
			this->_pointer = this->parent;
		}
		return *this;
	}

	/**
	 * @brief	Update the wrapped pointer to pointe to the next element. (postfix incrementation)
	 * 
	 * @return	A copy of the rb_tree_iterator before the incrementation.
	 */
	inline rb_tree_iterator operator++(int)
	{
		rb_tree_iterator	original(*this);

		++*this;
		return original;
	}

	/**
	 * @brief	Update the wrapped pointer to pointe to the previous element. (prefix decrementation)
	 * 
	 * @return	A reference to the decremented rb_tree_iterator.
	 */
	inline rb_tree_iterator &operator--(void)
	{
		if (this->child[LEFT])
		{
			this->_pointer = this->child[LEFT];
			while (this->child[RIGHT])
				this->_pointer = this->child[RIGHT];
		}
		else
		{
			while (this->parent && this->_pointer == this->parent->child[LEFT])
				this->_pointer = this->parent;
			this->_pointer = this->parent;
		}
	}

	/**
	 * @brief	Update the wrapped pointer to pointe to the previous element. (postfix decrementation)
	 * 
	 * @return	A copy of the rb_tree_iterator before the decrementation.
	 */
	inline rb_tree_iterator operator--(int)
	{
		rb_tree_iterator	original(*this);

		--*this;
		return original;
	}
};
}

#endif
