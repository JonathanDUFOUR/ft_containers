/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rb_tree_iterator.tpp                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jodufour <jodufour@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/22 22:37:54 by jodufour          #+#    #+#             */
/*   Updated: 2022/09/17 06:16:34 by jodufour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RB_TREE_ITERATOR_TPP
# define RB_TREE_ITERATOR_TPP

# include "iterator/base/bidirectional_iterator.tpp"
# include "iterator.hpp"
# include "e_rb_direction.hpp"

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

private:
	// Attributes
	pointer const	*_root;

public:
// ****************************************************************************************************************** //
//                                                    Constructors                                                    //
// ****************************************************************************************************************** //

	/**
	 * @brief	Construct a new rb_tree_iterator object. (default constructor)
	 * 
	 * @param	ptr	The pointer to wrap.
	 */
	rb_tree_iterator(pointer const ptr = NULL, pointer const *const root = NULL) :
		bidirectional_iterator<value_type, iterator_category, difference_type, pointer, reference>(ptr),
		_root(root) {}

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
		bidirectional_iterator<value_type, iterator_category, difference_type, pointer, reference>(src.base()),
		_root(src.getRoot()) {}

// ***************************************************************************************************************** //
//                                                     Accessors                                                     //
// ***************************************************************************************************************** //

	/**
	 * @brief	Get the inner root address in the rb_tree_iterator.
	 * 
	 * @return	The inner root address in the rb_tree_iterator.
	 */
	inline pointer const *const	&getRoot(void) const
	{
		return this->_root;
	}

// ***************************************************************************************************************** //
//                                                     Operators                                                     //
// ***************************************************************************************************************** //

	/**
	 * @brief	Assign a new pointer and a new root to the rb_tree_iterator.
	 * 
	 * @param	rhs The rb_tree_iterator to copy the pointer and the root from.
	 * 
	 * @return	A reference to the assigned rb_tree_iterator.
	 */
	rb_tree_iterator	&operator=(rb_tree_iterator const &rhs)
	{
		if (this != &rhs)
		{
			this->_ptr = rhs.base();
			this->_root = rhs.getRoot();
		}	
		return *this;
	}

	/**
	 * @brief	Check if two rb_tree_iterator are equivalent.
	 * 			Allow comparison between mutable and constant rb_tree_iterator.
	 * 
	 * @tparam	U The type of the rb_tree_iterator to compare with.
	 * 
	 * @param	rhs The rb_tree_iterator to compare with.
	 * 
	 * @return 	Either true if the two rb_tree_iterator are equivalent, or false if not.
	 */
	template <typename U>
	inline bool	operator==(rb_tree_iterator<U> const &rhs) const
	{
		return this->_ptr == rhs.base();
	}

	/**
	 * @brief	Check if two rb_tree_iterator are different.
	 * 			Allow comparison between mutable and constant rb_tree_iterator.
	 * 
	 * @tparam	U The type of the rb_tree_iterator to compare with.
	 * 
	 * @param	rhs The rb_tree_iterator to compare with.
	 * 
	 * @return	Either true if the two rb_tree_iterator are different, or false if not.
	 */
	template <typename U>
	inline bool	operator!=(rb_tree_iterator<U> const &rhs) const
	{
		return this->base() != rhs.base();
	}

	/**
	 * @brief	Update the wrapped pointer to pointe to the next element. (prefix incrementation)
	 * 
	 * @return	A reference to the incremented rb_tree_iterator.
	 */
	inline rb_tree_iterator &operator++(void)
	{
		if (!this->_ptr && this->_root && *this->_root)
			this->_ptr = value_type::leftMost(*this->_root);
		else if (this->_ptr)
		{
			if (this->_ptr->child[RIGHT])
			{
				this->_ptr = this->_ptr->child[RIGHT];
				while (this->_ptr->child[LEFT])
					this->_ptr = this->_ptr->child[LEFT];
			}
			else
			{
				while (this->_ptr->parent && this->_ptr == this->_ptr->parent->child[RIGHT])
					this->_ptr = this->_ptr->parent;
				this->_ptr = this->_ptr->parent;
			}
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
		if (!this->_ptr && this->_root && *this->_root)
			this->_ptr = value_type::rightMost(*this->_root);
		else if (this->_ptr)
		{
			if (this->_ptr->child[LEFT])
			{
				this->_ptr = this->_ptr->child[LEFT];
				while (this->_ptr->child[RIGHT])
					this->_ptr = this->_ptr->child[RIGHT];
			}
			else
			{
				while (this->_ptr->parent && this->_ptr == this->_ptr->parent->child[LEFT])
					this->_ptr = this->_ptr->parent;
				this->_ptr = this->_ptr->parent;
			}
		}
		return *this;
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
