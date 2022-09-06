/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rb_node.tpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jodufour <jodufour@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/02 13:02:40 by jodufour          #+#    #+#             */
/*   Updated: 2022/09/06 14:27:42 by jodufour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RB_NODE_TPP
# define RB_NODE_TPP

# include <stdint.h>
# include "e_rb_color.hpp"

namespace ft
{
template <typename T>
struct rb_node
{
	// Attributes
	T		data;

	uint8_t	color;

	rb_node	*parent;
	rb_node	*child[2];

// ****************************************************************************************************************** //
//                                                    Constructors                                                    //
// ****************************************************************************************************************** //

	/**
	 * @brief	Construct a new rb_node object. (default constructor)
	 * 
	 * @param	data The data to store in the node.
	 */
	rb_node(T const &data = T()) :
		data(data),
		color(RED),
		parent(NULL)
	{
		child[LEFT] = NULL;
		child[RIGHT] = NULL;
	}

// ***************************************************************************************************************** //
//                                              Public Member Functions                                              //
// ***************************************************************************************************************** //

	/**
	 * @brief	Calculate the number of descendant nodes of another one.
	 * 
	 * @param	node The node to count the descendant nodes of.
	 * 
	 * @return	The number of descendant nodes of the given one.
	 */
	static size_t	descendantCount(rb_node const *const node)
	{
		if (!node)
			return 0LU;
		return rb_node::descendantCount(node->child[LEFT]) + rb_node::descendantCount(node->child[RIGHT]) + 1LU;
	}

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
			return (NULL);
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
			return (NULL);
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
			return (NULL);
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
			return (NULL);
		while (node->child[RIGHT])
			node = node->child[RIGHT];
		return node;
	}

// ***************************************************************************************************************** //
//                                                     Operators                                                     //
// ***************************************************************************************************************** //

	/**
	 * friend keyword is here to call the non-member operators,
	 * instead of redefining them.
	 */

	template <typename _T>
	friend bool	operator==(rb_node<_T> const &lhs, rb_node<_T> const &rhs);
	template <typename _T>
	friend bool	operator!=(rb_node<_T> const &lhs, rb_node<_T> const &rhs);
};

/**
 * @brief	Check if two rb_node are equivalent.
 * 
 * @tparam	T The type of the data stored in both rb_node. 
 * 
 * @param	lhs The left hand side rb_node to compare.
 * @param	rhs The right hand side rb_node to compare.
 * 
 * @return	Either true if the two rb_node are equivalent, or false if not.
 */
template <typename T>
bool	operator==(rb_node<T> const &lhs, rb_node<T> const &rhs)
{
	return lhs.data == rhs.data;
}

/**
 * @brief	Check if two rb_node are different.
 * 
 * @tparam	T The type of the data stored in both rb_node. 
 * 
 * @param	lhs The left hand side rb_node to compare.
 * @param	rhs The right hand side rb_node to compare.
 * 
 * @return	Either true if the two rb_node are different, or false if not.
 */
template <typename T>
bool	operator!=(rb_node<T> const &lhs, rb_node<T> const &rhs)
{
	return lhs.data != rhs.data;
}
}

#endif
