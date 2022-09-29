/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rb_node.tpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jodufour <jodufour@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/02 13:02:40 by jodufour          #+#    #+#             */
/*   Updated: 2022/09/29 19:02:52 by jodufour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RB_NODE_TPP
# define RB_NODE_TPP

# include <stdint.h>
# include "e_rb_color.hpp"
# include "e_rb_direction.hpp"

namespace ft
{
template <typename T>
struct rb_node
{
	// Attributes
	T		val;

	uint8_t	color;

	rb_node	*parent;
	rb_node	*child[2];

// ****************************************************************************************************************** //
//                                                    Constructors                                                    //
// ****************************************************************************************************************** //

	/**
	 * @brief	Construct a new rb_node object. (parameter constructor)
	 * 
	 * @param	val The value to store in the node.
	 * @param	color The color of the node.
	 * @param	parent The parent of the node.
	 * @param	child The two children of the node.
	 */
	rb_node(T const &val, uint8_t const color, rb_node *const parent, rb_node *const left, rb_node *const right) :
		val(val),
		color(color),
		parent(parent)
	{
		child[LEFT] = left;
		child[RIGHT] = right;
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
		child[LEFT] = src.child[LEFT];
		child[RIGHT] = src.child[RIGHT];
	}

// ***************************************************************************************************************** //
//                                              Public Member Functions                                              //
// ***************************************************************************************************************** //

	/**
	 * @brief	Get the node placed the most on the left of another one.
	 * 
	 * @param	node The node to start from.
	 * 
	 * @return	The node placed the most on the left of the given one.
	 */
	static rb_node	*leftMost(rb_node *node)
	{
		if (!node)
			return NULL;
		while (node->child[LEFT])
			node = node->child[LEFT];
		return node;
	}

	/**
	 * @brief	Get the node placed the most on the left of another one.
	 * 
	 * @param	node The node to start from.
	 * 
	 * @return	The node placed the most on the left of the given one.
	 */
	static rb_node const	*leftMost(rb_node const *node)
	{
		if (!node)
			return NULL;
		while (node->child[LEFT])
			node = node->child[LEFT];
		return node;
	}

	/**
	 * @brief	Get the node placed the most on the right of another one.
	 * 
	 * @param	node The node to start from.
	 * 
	 * @return	The node placed the most on the right of the given one.
	 */
	static rb_node	*rightMost(rb_node *node)
	{
		if (!node)
			return NULL;
		while (node->child[RIGHT])
			node = node->child[RIGHT];
		return node;
	}

	/**
	 * @brief	Get the node placed the most on the right of another one.
	 * 
	 * @param	node The node to start from.
	 * 
	 * @return	The node placed the most on the right of the given one.
	 */
	static rb_node const	*rightMost(rb_node const *node)
	{
		if (!node)
			return NULL;
		while (node->child[RIGHT])
			node = node->child[RIGHT];
		return node;
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
