/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rb_tree_iterator.tpp                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jodufour <jodufour@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/22 22:37:54 by jodufour          #+#    #+#             */
/*   Updated: 2022/10/04 12:50:57 by jodufour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RB_TREE_ITERATOR_TPP
# define RB_TREE_ITERATOR_TPP

# include "iterator/base/I_bidirectional_iterator.tpp"
# include "iterator.hpp"
# include "rb_node.tpp"
# include "e_rb_min_max.hpp"

namespace ft
{
template <typename T, typename Node>
class rb_tree_iterator : public I_bidirectional_iterator<rb_tree_iterator<T, Node>, T>
{
private:
	// Member types
	typedef rb_tree_iterator<T, Node>				_self_type;
	typedef I_bidirectional_iterator<_self_type, T>	_base_type;
	typedef Node									_node_type;

public:
	// Member types
	using typename _base_type::						value_type;
	using typename _base_type::						iterator_category;
	using typename _base_type::						difference_type;
	using typename _base_type::						pointer;
	using typename _base_type::						reference;

private:
	// Attributes
	_node_type	*_curr;

public:
// ****************************************************************************************************************** //
//                                                    Constructors                                                    //
// ****************************************************************************************************************** //

	/**
	 * @brief	Construct a new rb_tree_iterator object. (wrap constructor)
	 * 
	 * @param	curr The current rb_node pointer to wrap.
	 */
	rb_tree_iterator(_node_type *const curr = NULL) :
		_base_type(),
		_curr(curr) {}

	/**
	 * @brief	Construct a new rb_tree_iterator object from another one.
	 * 			Allow mutable to constant rb_tree_iterator conversion. (copy constructor)
	 * 
	 * @tparam	_T The type of the pointed value of the rb_tree_iterator to copy.
	 * @tparam	_Node The type of the rb_node of the rb_tree_iterator to copy.
	 * 
	 * @param	src The rb_tree_iterator to copy.
	 */
	template <typename _T, typename _Node>
	rb_tree_iterator(rb_tree_iterator<_T, _Node> const &src) :
		_base_type(),
		_curr(src.base()) {}

// ***************************************************************************************************************** //
//                                              Public Member Functions                                              //
// ***************************************************************************************************************** //

	/**
	 * @return	A copy of the wrapped pointer.
	 */
	inline _node_type	*base(void) const
	{
		return this->_curr;
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
	inline _self_type	&operator=(_self_type const &rhs)
	{
		if (this != &rhs)
			this->_curr = rhs._curr;
		return *this;
	}

	/**
	 * @brief	Check if two rb_tree_iterator are equivalent.
	 * 
	 * @param	rhs The rb_tree_iterator to compare with.
	 * 
	 * @return 	Either true if the two rb_tree_iterator are equivalent, or false if not.
	 */
	inline bool	operator==(_self_type const &rhs) const
	{
		return this->_curr == rhs._curr;
	}

	/**
	 * @brief	Check if two rb_tree_iterator are equivalent.
	 * 			Allow comparison between mutable and constant rb_tree_iterator.
	 * 
	 * @tparam	_T The type of the pointed value of the rb_tree_iterator to copy.
	 * @tparam	_Node The type of the rb_node of the rb_tree_iterator to copy.
	 * 
	 * @param	rhs The rb_tree_iterator to compare with.
	 * 
	 * @return 	Either true if the two rb_tree_iterator are equivalent, or false if not.
	 */
	template <typename _T, typename _Node>
	inline bool	operator==(rb_tree_iterator<_T, _Node> const &rhs) const
	{
		return this->_curr == rhs.base();
	}

	/**
	 * @brief	Check if two rb_tree_iterator are different.
	 * 
	 * @param	rhs The rb_tree_iterator to compare with.
	 * 
	 * @return	Either true if the two rb_tree_iterator are different, or false if not.
	 */
	inline bool	operator!=(_self_type const &rhs) const
	{
		return !(*this == rhs);
	}

	/**
	 * @brief	Check if two rb_tree_iterator are different.
	 * 			Allow comparison between mutable and constant rb_tree_iterator.
	 * 
	 * @tparam	_T The type of the pointed value of the rb_tree_iterator to copy.
	 * @tparam	_Node The type of the rb_node of the rb_tree_iterator to copy.
	 * 
	 * @param	rhs The rb_tree_iterator to compare with.
	 * 
	 * @return	Either true if the two rb_tree_iterator are different, or false if not.
	 */
	template <typename _T, typename _Node>
	inline bool	operator!=(rb_tree_iterator<_T, _Node> const &rhs) const
	{
		return !(*this == rhs);
	}

	/**
	 * @return 	A reference to the inner value of the pointed node.
	 */
	inline reference	operator*(void) const
	{
		return this->_curr->val;
	}

	/**
	 * @return 	The address of the inner value of the pointed node.
	 */
	inline pointer	operator->(void) const
	{
		return &this->_curr->val;
	}

	/**
	 * @brief	Update the wrapped pointer to pointe to the next element. (prefix incrementation)
	 * 
	 * @return	A reference to the incremented rb_tree_iterator.
	 */
	inline _self_type	&operator++(void)
	{
		if (!this->_curr->parent)
			this->_curr = this->_curr->child[MIN];
		else
		{
			if (this->_curr->child[RIGHT]->parent)
			{
				this->_curr = this->_curr->child[RIGHT];
				while (this->_curr->child[LEFT]->parent)
					this->_curr = this->_curr->child[LEFT];
			}
			else
			{
				while (this->_curr->parent->parent && this->_curr == this->_curr->parent->child[RIGHT])
					this->_curr = this->_curr->parent;
				this->_curr = this->_curr->parent;
			}
		}
		return *this;
	}

	/**
	 * @brief	Update the wrapped pointer to pointe to the next element. (postfix incrementation)
	 * 
	 * @return	A copy of the rb_tree_iterator before the incrementation.
	 */
	inline _self_type	operator++(int)
	{
		_self_type	original(*this);

		++*this;
		return original;
	}

	/**
	 * @brief	Update the wrapped pointer to pointe to the previous element. (prefix decrementation)
	 * 
	 * @return	A reference to the decremented rb_tree_iterator.
	 */
	inline _self_type	&operator--(void)
	{
		if (!this->_curr->parent)
			this->_curr = this->_curr->child[MAX];
		else
		{
			if (this->_curr->child[LEFT]->parent)
			{
				this->_curr = this->_curr->child[LEFT];
				while (this->_curr->child[RIGHT]->parent)
					this->_curr = this->_curr->child[RIGHT];
			}
			else
			{
				while (this->_curr->parent->parent && this->_curr == this->_curr->parent->child[LEFT])
					this->_curr = this->_curr->parent;
				this->_curr = this->_curr->parent;
			}
		}
		return *this;
	}

	/**
	 * @brief	Update the wrapped pointer to pointe to the previous element. (postfix decrementation)
	 * 
	 * @return	A copy of the rb_tree_iterator before the decrementation.
	 */
	inline _self_type	operator--(int)
	{
		_self_type	original(*this);

		--*this;
		return original;
	}
};
} // namespace ft
#endif
