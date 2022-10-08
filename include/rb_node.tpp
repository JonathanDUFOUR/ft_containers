/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rb_node.tpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jodufour <jodufour@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/02 13:02:40 by jodufour          #+#    #+#             */
/*   Updated: 2022/10/08 18:49:41 by jodufour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RB_NODE_TPP
# define RB_NODE_TPP

# include "e_rb_color.hpp"
# include "e_rb_direction.hpp"
# include <stdint.h>

namespace ft
{
template <typename T>
struct rb_node
{
	// Member types
	typedef T	value_type;

	// Attributes
	value_type	val;

	uint8_t		color;

	rb_node		*parent;
	rb_node		*child[2];

// ****************************************************************************************************************** //
//                                                    Constructors                                                    //
// ****************************************************************************************************************** //

	/**
	 * @brief	Construct a new rb_node object. (mutable parameter constructor)
	 * 
	 * @param	val The value to store in the node.
	 * @param	color The color of the node.
	 * @param	parent The parent of the node.
	 * @param	left The left child of the node.
	 * @param	right The right child of the node.
	 */
	rb_node(
		value_type const &val,
		uint8_t const color,
		rb_node *const parent,
		rb_node *const left,
		rb_node *const right) :
		val(val),
		color(color),
		parent(parent)
	{
		child[RB_LEFT] = left;
		child[RB_RIGHT] = right;
	}

	/**
	 * @brief	Construct a new rb_node object. (copy constructor)
	 * 
	 * @param	src The rb_node to copy.
	 */
	rb_node(rb_node const &src) :
		val(src.val),
		color(src.color),
		parent(src.parent)
	{
		child[RB_LEFT] = src.child[RB_LEFT];
		child[RB_RIGHT] = src.child[RB_RIGHT];
	}
}; // struct rb_node

/**
 * @brief	Check if two rb_node are equivalent.
 * 			Allow comparison between mutable and constant rb_node.
 * 
 * @tparam	T0 The type of the value stored in the left hand side rb_node.
 * @tparam	T1 The type of the value stored in the right hand side rb_node.
 * 
 * @param	lhs The left hand side rb_node to compare.
 * @param	rhs The right hand side rb_node to compare.
 * 
 * @return	Either true if the two rb_node are equivalent, or false if not.
 */
template <typename T0, typename T1>
bool	operator==(rb_node<T0> const &lhs, rb_node<T1> const &rhs)
{
	return lhs.val == rhs.val;
}

/**
 * @brief	Check if two rb_node are different.
 * 			Allow comparison between mutable and constant rb_node.
 * 
 * @tparam	T0 The type of the value stored in the left hand side rb_node.
 * @tparam	T1 The type of the value stored in the right hand side rb_node.
 * 
 * @param	lhs The left hand side rb_node to compare.
 * @param	rhs The right hand side rb_node to compare.
 * 
 * @return	Either true if the two rb_node are different, or false if not.
 */
template <typename T0, typename T1>
bool	operator!=(rb_node<T0> const &lhs, rb_node<T1> const &rhs)
{
	return lhs.val != rhs.val;
}

} // namespace ft

#endif
