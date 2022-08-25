/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rb_tree.tpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jodufour <jodufour@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/19 21:43:39 by jodufour          #+#    #+#             */
/*   Updated: 2022/08/25 20:20:22 by jodufour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RB_TREE_TPP
# define RB_TREE_TPP

# include <memory>
# include "iterator/base/reverse_iterator.tpp"
# include "iterator/spec/rb_tree_iterator.tpp"
# include "utility.hpp"

namespace ft
{
enum e_rb_color
{
	RED,
	BLACK
};

enum e_rb_direction
{
	LEFT,
	RIGHT
};

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
		parent(NULL),
		child{NULL, NULL} {}
};

template <typename T, typename Compare, typename Alloc = std::allocator<rb_node<T>>>
class rb_tree
{
public:
	// Member types
	typedef T													value_type;
	typedef Compare												compare_function_type;
	typedef Alloc												allocator_type;

	typedef typename ft::rb_node<value_type>					node_type;

	typedef typename allocator_type::pointer					pointer;
	typedef typename allocator_type::const_pointer				const_pointer;

	typedef typename allocator_type::reference					reference;
	typedef typename allocator_type::const_reference			const_reference;

	typedef typename ft::rb_tree_iterator<pointer>				iterator;
	typedef typename ft::rb_tree_iterator<const_pointer>		const_iterator;

	typedef typename ft::reverse_iterator<iterator>				reverse_iterator;
	typedef typename ft::reverse_iterator<const_iterator>		const_reverse_iterator;

	typedef typename iterator_traits<iterator>::difference_type	difference_type;
	typedef size_t												size_type;

private:
	// Attributes
	pointer	_root;

public:
// ****************************************************************************************************************** //
//                                                    Constructors                                                    //
// ****************************************************************************************************************** //

	/**
	 * @brief	Construct a new rb_tree object. (default constructor)
	 * 
	 * @param	root The root node of the new tree.
	 */
	rb_tree(const_pointer const root = NULL) :
		_root(root) {}

	/**
	 * @brief	Construct a new rb_tree object. (copy constructor)
	 * 
	 * @param	src The rb_tree to copy
	 */
	rb_tree(rb_tree const &src) :
		_root(NULL)
	{
		if (src._root)
			this->_root = rb_tree::dup(src._root);
	}

// ***************************************************************************************************************** //
//                                                    Destructors                                                    //
// ***************************************************************************************************************** //

	/**
	 * @brief	Destroy a rb_tree object, relasing its related allocated memory. (destructor)
	 */
	~rb_tree(void)
	{
		rb_tree::clear(this->_root);
	}

// ***************************************************************************************************************** //
//                                              Public Member Functions                                              //
// ***************************************************************************************************************** //

	/**
	 * @brief	Remove every nodes of the given tree.
	 * 
	 * @param	root The root of the tree to clear.
	 */
	static void	clear(pointer const root)
		__attribute__((nonnull))
	{
		allocator_type	alloc;

		if (root->child[LEFT])
			rb_tree::clear(root->child[LEFT]);
		if (root->child[RIGHT])
			rb_tree::clear(root->child[RIGHT]);
		alloc.destroy(root);
		alloc.deallocate(root, 1);
	}

	/**
	 * @brief	Get the direction of the given node, relative to its parent.
	 * 
	 * @param	node The node we want to check the direction.
	 * 
	 * @return	Either LEFT if the given node is the left child of its parent,
	 * 			or RIGHT if the given node is the right child of its parent.
	 */
	static uint8_t	childDirection(const_pointer const node)
		__attribute__((nonnull))
	{
		if (node->parent->child[LEFT] == node)
			return LEFT;
		return RIGHT;
	}

	/**
	 * @brief	Duplicate every node from a tree to another, using deep copy.
	 * 
	 * @param	src The source root.
	 * 
	 * @return	The root of the new tree.
	 */
	static pointer	dup(const_pointer const src)
		__attribute__((nonnull))
	{
		pointer			dst;
		allocator_type	alloc;

		dst = alloc.allocate(1);
		alloc.construct(dst, *src);
		if (src->child[LEFT])
			dst->child[LEFT] = rb_tree::dup(src->child[LEFT]);
		if (src->child[RIGHT])
			dst->child[RIGHT] = rb_tree::dup(src->child[RIGHT]);
		return dst;
	}

	/**
	 * @brief	Rotate a portion of the tree to the given direction. The colors are not modified.
	 * 
	 * @param	root The root of the subtree to rotate.
	 * @param	dir The direction to rotate the subtree.
	 * 
	 * @return	The new root of the rotated subtree. Upon failure, NULL is returned instead.
	 */
	pointer	rotate(pointer const root, uint8_t const dir)
		__attribute__((nonnull))
	{
		node_type	*parent;
		node_type	*oppositeChild;
		node_type	*grandChild;

		parent = root->parent;
		oppositeChild = root->child[!dir];
		if (!oppositeChild)
			return NULL;
		grandChild = oppositeChild->child[dir];

		root->child[!dir] = grandChild;
		if (grandChild)
			grandChild->parent = root;

		oppositeChild->child[dir] = root;
		root->parent = oppositeChild;

		oppositeChild->parent = parent;
		if (parent)
		{
			if (root == parent->child[LEFT])
				parent->child[LEFT] = oppositeChild;
			else
				parent->child[RIGHT] = oppositeChild;
		}
		else
			this->_root = oppositeChild;

		return oppositeChild;
	}

	/**
	 * @brief	Insert a new node in the tree.
	 * 
	 * @param	data The data to insert in the tree.
	 * 
	 * @return	A pair containing an iterator to the node of the tree as `first` member,
	 * 			and a boolean indicating whether a new node has been inserted as `second` member.
	 */
	pair<iterator, bool> insert(value_type const &data)
	{
		pointer					parent;
		pointer					node;
		pointer					pos;
		compare_function_type	cmp;
		allocator_type			alloc;

		if (!this->_root)
		{
			this->_root = alloc.allocate(1LU);
			alloc.construct(this->_root, node_type(data));
			return pair<iterator, bool>(iterator(this->_root), true);
		}
		pos = this->_root;
		while (pos)
		{
			if (cmp(pos->data, data))
			{
				parent = pos;
				pos = pos->child[RIGHT];
			}
			else if (cmp(data, pos->data))
			{
				parent = pos;
				pos = pos->child[LEFT];
			}
			else
				return pair<iterator, bool>(iterator(pos), false);
		}
		node = alloc.allocate(1LU);
		alloc.construct(node, node_type(data));
		node->parent = parent;
		if (cmp(parent->data, data))
			parent->child[RIGHT] = node;
		else
			parent->child[LEFT] = node;
		// REMIND: continue here
	}
};
}
#endif
