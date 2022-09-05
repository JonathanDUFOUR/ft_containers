/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rb_tree.tpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jodufour <jodufour@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/19 21:43:39 by jodufour          #+#    #+#             */
/*   Updated: 2022/09/05 18:48:02 by jodufour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RB_TREE_TPP
# define RB_TREE_TPP

# include <functional>
# include <memory>
# include "iterator/base/reverse_iterator.tpp"
# include "iterator/spec/rb_tree_iterator.tpp"
# include "utility.hpp"
# include "rb_node.tpp"
# include "e_rb_color.hpp"
# include "e_rb_direction.hpp"

namespace ft
{
/**
 * @file	This file contains the implementation of the rb_tree class. (Red Black Tree)
 * 			A Red Black Tree is a self-balancing Binary Search Tree (BST) which is ruled by the following properties:
 * 				1. Every node has a color either red or black.
 * 				2. All NULL nodes are considered black.
 * 				3. A red node cannot have a red child.
 * 				4. Every path from a node to its descendant NULL nodes goes through the same number of black nodes.
 * 
 * 			In this implementation:
 * 				- a violation of the 3rd property is called a "red violation"
 * 				- a violation of the 4th property is called a "black violation".
 */

template <typename T>
struct rb_node;

template <typename T, typename Compare = std::less<T>, typename Alloc = std::allocator<rb_node<T> > >
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
	pointer		_root;
	pointer		_min;
	pointer		_max;

	size_type	_size;

// ****************************************************************************************************************** //
//                                              Private Member Functions                                              //
// ****************************************************************************************************************** //

	/**
	 * @par		Balance a tree after an insertion.
	 * 
	 * @param	node The newly inserted node.
	 */
	void	_balanceInsert(pointer const node)
		__attribute__((nonnull))
	{
		pointer		parent;
		pointer		grandParent;
		pointer		uncle;
		uint8_t		dir;

		// At this point, the node is red.
		parent = node->parent;
		if (!parent || parent->color == BLACK)
			return ;

		// At this point, the node is red, and has red parent. (red violation)
		grandParent = parent->parent;
		if (!grandParent)
		{
			// At this point, the node is red, has red parent, and has no grandparent. (red violation)
			node->parent->color = BLACK;
			return ;
		}

		// At this point, the node is red, has a red parent, and has a black grand-parent. (red violation)
		dir = rb_tree::childDirection(parent);
		uncle = grandParent->child[!dir];
		if (!uncle || uncle->color == BLACK)
		{
			// At this point, the node is red, has a red parent, has a black grand-parent, and has a black uncle.
			// (red violation)
			if (node == parent->child[!dir])
			{
				// At this point, the node is red, has a red parent, has a black grand-parent, has a black uncle,
				// and is the inner grand-child of its grand-parent. (red violation)
				parent = this->_rotate(parent, dir);
				node = parent->child[dir];
			}

			// At this point, the node is red, has a red parent, has a black grand-parent, has a black uncle,
			// and is the outer grand-child of its grand-parent. (red violation)
			this->_rotate(grandParent, !dir);
			parent->color = BLACK;
			grandParent->color = RED;
		}
		else
		{
			// At this point, the node is red, has a red parent, has a black grand-parent, and has a red uncle.
			// (red violation)
			parent->color = BLACK;
			uncle->color = BLACK;
			grandParent->color = RED;
			this->_balanceInsert(grandParent);
		}
	}

	/**
	 * @brief	Remove every nodes of a tree.
	 * 
	 * @param	root The root of the tree to clear.
	 */
	static void	_clear(pointer const root)
	{
		allocator_type	alloc;

		if (!root)
			return ;
		rb_tree::_clear(root->child[LEFT]);
		rb_tree::_clear(root->child[RIGHT]);
		alloc.destroy(root);
		alloc.deallocate(root, 1);
	}

	/**
	 * @brief	Rotate a tree to the given direction. The colors are not modified. The rotating tree may be a subtree.
	 * 
	 * @param	root The root of the tree to rotate.
	 * @param	dir The direction to rotate the subtree.
	 * 
	 * @return	The new root of the rotated tree. Upon failure, NULL is returned instead.
	 */
	pointer	_rotate(pointer const root, uint8_t const dir)
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

public:
// ****************************************************************************************************************** //
//                                                    Constructors                                                    //
// ****************************************************************************************************************** //

	/**
	 * @brief	Construct a new rb_tree object. (default constructor)
	 * 
	 * @param	root The root node of the new tree.
	 */
	rb_tree(pointer const root = NULL) :
		_root(root),
		_min(rb_node<value_type>::leftMost(root)),
		_max(rb_node<value_type>::rightMost(root)),
		_size(rb_node<value_type>::descendantCount(root)) {}

	/**
	 * @brief	Construct a new rb_tree object. (copy constructor)
	 * 
	 * @param	src The rb_tree to copy
	 */
	rb_tree(rb_tree const &src) :
		_root(rb_tree::dup(src._root)),
		_min(rb_node<value_type>::leftMost(this->_root)),
		_max(rb_node<value_type>::rightMost(this->_root)),
		_size(src._size) {}

// ***************************************************************************************************************** //
//                                                    Destructors                                                    //
// ***************************************************************************************************************** //

	/**
	 * @brief	Destroy a rb_tree object, relasing its related allocated memory. (destructor)
	 */
	~rb_tree(void)
	{
		this->clear();
	}

// ***************************************************************************************************************** //
//                                              Public Member Functions                                              //
// ***************************************************************************************************************** //

	/**
	 * @brief	Get an iterator to the first element of the tree.
	 * 
	 * @return	An iterator to the first element of the tree.
	 */
	iterator	begin(void)
	{
		return iterator(this->_min, &this->_root);
	}

	/**
	 * @brief	Get a const_iterator to the first element of the tree.
	 * 
	 * @return	A const_iterator to the first element of the tree.
	 */
	const_iterator	begin(void) const
	{
		return const_iterator(this->_min, &this->_root);
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
	 * @brief	Remove every nodes of the tree, and set its size accordingly.
	 */
	void	clear(void)
	{
		rb_tree::_clear(this->_root);
		this->_root = NULL;
		this->_size = 0LU;
	}

	/**
	 * @brief	Duplicate every node from a tree to another, using deep copy.
	 * 
	 * @param	src The source root.
	 * 
	 * @return	The root of the new tree.
	 */
	static pointer	dup(const_pointer const src)
	{
		pointer			dst;
		allocator_type	alloc;

		if (!src)
			return NULL;
		dst = alloc.allocate(1);
		alloc.construct(dst, *src);
		dst->child[LEFT] = rb_tree::dup(src->child[LEFT]);
		dst->child[RIGHT] = rb_tree::dup(src->child[RIGHT]);
		return dst;
	}

	/**
	 * @brief	Get an iterator to the post-last element of the tree.
	 * 
	 * @return	An iterator to the last element of the tree.
	 */
	iterator	end(void)
	{
		return iterator(NULL, &this->_root);
	}

	/**
	 * @brief	Get a const_iterator to the post-last element of the tree.
	 * 
	 * @return	A const_iterator to the last element of the tree.
	 */
	const_iterator	end(void) const
	{
		return const_iterator(NULL, &this->_root);
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
		++this->_size;
		this->_balanceInsert();
		return pair<iterator, bool>(iterator(node), true);
	}

	/**
	 * @brief	Get a reverse_iterator to the last element of the tree.
	 * 
	 * @return	A reverse_iterator to the last element of the tree.
	 */
	reverse_iterator	rbegin(void)
	{
		
		return reverse_iterator(this->end());
	}

	/**
	 * @brief	Get a const_reverse_iterator to the last element of the tree.
	 * 
	 * @return	A const_reverse_iterator to the last element of the tree.
	 */
	const_reverse_iterator	rbegin(void) const
	{
		return const_reverse_iterator(this->end());
	}

	/**
	 * @brief	Get a reverse_iterator to the pre-first element of the tree.
	 * 
	 * @return	A reverse_iterator to the pre-first element of the tree.
	 */
	reverse_iterator	rend(void)
	{
		return reverse_iterator(this->begin());
	}

	/**
	 * @brief	Get a const_reverse_iterator to the pre-first element of the tree.
	 * 
	 * @return	A const_reverse_iterator to the pre-first element of the tree.
	 */
	const_reverse_iterator	rend(void) const
	{
		return const_reverse_iterator(this->begin());
	}

	/**
	 * @brief	Get the size of the tree.
	 * 
	 * @return	The size of the tree.
	 */
	size_type	size(void) const
	{
		return this->_size;
	}
};
}
#endif
