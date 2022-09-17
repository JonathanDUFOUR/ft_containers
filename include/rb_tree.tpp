/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rb_tree.tpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jodufour <jodufour@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/19 21:43:39 by jodufour          #+#    #+#             */
/*   Updated: 2022/09/17 05:41:01 by jodufour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RB_TREE_TPP
# define RB_TREE_TPP

# include <cstring>
# include <functional>
# include <memory>
# include "algorithm.hpp"
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
 * 				- a violation of the 4th property is called a "black violation"
 * 				- the "I1", "I2", ... and "D1", "D2", ... notations refer to the different situations
 * 				that can be encountered during an insertion or a deletion
 * 				as described on the Red Black Tree Wikipedia page.
 * 				(https://en.wikipedia.org/wiki/Red%E2%80%93black_tree)
 */

template <typename T>
struct rb_node;

template <typename T, typename Compare = std::less<T>, typename Alloc = std::allocator<rb_node<T> > >
class rb_tree
{
public:
	// Member types
	typedef T													value_type;
	typedef Compare												compare_type;
	typedef Alloc												allocator_type;

	typedef rb_node<value_type>									node_type;

	typedef typename allocator_type::pointer					pointer;
	typedef typename allocator_type::const_pointer				const_pointer;

	typedef typename allocator_type::reference					reference;
	typedef typename allocator_type::const_reference			const_reference;

	typedef rb_tree_iterator<const_pointer>						const_iterator;
	typedef rb_tree_iterator<pointer>							iterator;

	typedef reverse_iterator<const_iterator>					const_reverse_iterator;
	typedef reverse_iterator<iterator>							reverse_iterator;

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
	 * @brief	Balance the tree before an erase of a non-root black leaf node.
	 * 
	 * @param	node	The current node to consider for the balancing.
	 * @param	dir		The direction of the node from its parent.
	 */
	void	_balanceErase(pointer const node, uint8_t const dir)
		__attribute__((nonnull))
	{
		pointer const	parent = node->parent;
		pointer			sibling;
		pointer			closeNephew;
		pointer			distantNephew;

		// At this point, the node has a parent, and has a sibling.
		sibling = parent->child[!dir];
		if (sibling->color == RED)
		{
			// At this point, the node has a black-deducted parent, and has a red sibling.
			// (D3)
			this->_rotate(parent, dir);
			parent->color = RED;
			sibling->color = BLACK;
			return this->_balanceErase(node, dir);
		}

		// At this point, the node has a parent, and has a black sibling.
		closeNephew = sibling->child[dir];
		if (closeNephew && closeNephew->color == RED)
		{
			// At this point, the node has a parent, has a black sibling, and has a red close nephew.
			// (D5)
			sibling = this->_rotate(sibling, !dir);
			sibling->color = BLACK;
			sibling->child[!dir]->color = RED;
		}
		distantNephew = sibling->child[!dir];
		if (distantNephew && distantNephew->color == RED)
		{
			// At this point, the node has a parent, has a black sibling, and has a red distant nephew.
			// (D6)
			this->_rotate(parent, dir);
			sibling->color = parent->color;
			parent->color = BLACK;
			distantNephew->color = BLACK;
			return ;
		}

		// At this point, the node has a parent, has a black sibling,
		// has either no close nephew or a black close nephew,
		// and has either no distant nephew or a black distant nephew.
		if (parent->color == RED)
		{
			// At this point, the node has a red parent, has a black sibling,
			// has either no close nephew or a black close nephew,
			// and has either no distant nephew or a black distant nephew.
			// (D4)
			sibling->color = RED;
			parent->color = BLACK;
			return ;
		}

		// At this point, the node has a black parent, has a black sibling,
		// has either no close nephew or a black close nephew,
		// and has either no distant nephew or a black distant nephew.
		// (D1)
		sibling->color = RED;
		if (parent->parent)
			return this->_balanceErase(parent, rb_tree::_childDirection(parent));

		// At this point, the node has a black parent, has a black sibling,
		// has either no close nephew or a black close nephew,
		// and has either no distant nephew or a black distant nephew,
		// and is the child of the root of tree.
		// (D2)
	}

	/**
	 * @par		Balance the tree after an insertion.
	 * 
	 * @param	node The newly inserted node.
	 */
	void	_balanceInsert(pointer node)
		__attribute__((nonnull))
	{
		pointer	parent;
		pointer	grandParent;
		pointer	uncle;
		uint8_t	dir;

		// At this point, the node is red.
		parent = node->parent;
		if (!parent || parent->color == BLACK)
			// At this point, the node has a black parent. (I1 + I3)
			return ;

		// At this point, the node is red, and has red parent. (red violation)
		grandParent = parent->parent;
		if (!grandParent)
		{
			// At this point, the node is red, has red parent, and has no grandparent. (red violation) (I4)
			node->parent->color = BLACK;
			return ;
		}

		// At this point, the node is red, has a red parent, and has a black grand-parent. (red violation)
		dir = rb_tree::_childDirection(parent);
		uncle = grandParent->child[!dir];
		if (!uncle || uncle->color == BLACK)
		{
			// At this point, the node is red, has a red parent, has a black grand-parent, and has a black uncle.
			// (red violation)
			if (node == parent->child[!dir])
			{
				// At this point, the node is red, has a red parent, has a black grand-parent, has a black uncle,
				// and is the inner grand-child of its grand-parent. (red violation) (I5)
				parent = this->_rotate(parent, dir);
				node = parent->child[dir];
			}

			// At this point, the node is red, has a red parent, has a black grand-parent, has a black uncle,
			// and is the outer grand-child of its grand-parent. (red violation) (I6)
			this->_rotate(grandParent, !dir);
			parent->color = BLACK;
			grandParent->color = RED;
		}
		else
		{
			// At this point, the node is red, has a red parent, has a black grand-parent, and has a red uncle.
			// (red violation) (I2)
			parent->color = BLACK;
			uncle->color = BLACK;
			grandParent->color = RED;
			this->_balanceInsert(grandParent);
		}
	}

	/**
	 * @brief	Get the direction of the given node, relative to its parent.
	 * 
	 * @param	node The node we want to check the direction.
	 * 
	 * @return	Either LEFT if the given node is the left child of its parent,
	 * 			or RIGHT if the given node is the right child of its parent.
	 */
	inline static uint8_t	_childDirection(const_pointer const node)
		__attribute__((nonnull))
	{
		if (node->parent->child[LEFT] == node)
			return LEFT;
		return RIGHT;
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
		alloc.deallocate(root, 1LU);
	}

	/**
	 * @brief	Duplicate every node from a tree to another, using deep copy.
	 * 
	 * @param	src The source root.
	 * 
	 * @return	The root of the new tree.
	 */
	static pointer	_dup(const_pointer const src)
	{
		pointer			dst;
		allocator_type	alloc;

		if (!src)
			return NULL;
		dst = alloc.allocate(1);
		alloc.construct(dst, *src);
		dst->child[LEFT] = rb_tree::_dup(src->child[LEFT]);
		dst->child[RIGHT] = rb_tree::_dup(src->child[RIGHT]);
		return dst;
	}

	/**
	 * @brief	Relink the children and the parent of a given node to another one,
	 * 			assuming that the nodes are not father and son.
	 * 
	 * @param	dst The destination node.
	 * @param	src The source node.
	 */
	inline static void	_relinkGoingTo(pointer const dst, pointer const src)
		__attribute__((nonnull))
	{
		if (src->parent)
			src->parent->child[rb_tree::_childDirection(src)] = dst;
		if (src->child[LEFT])
			src->child[LEFT]->parent = dst;
		if (src->child[RIGHT])
			src->child[RIGHT]->parent = dst;
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

	/**
	 * @brief	Swap indirectly the values stored in two different nodes, assuming that the nodes aren't father and son,
	 * 			changing the links and the colors of the nodes instead of just swapping the values, because we can not
	 * 			be certain that the assignation operator will be available for the value_type.
	 * 
	 * @param	node0 The first node to be swapped.
	 * @param	node1 The second node to be swapped.
	 */
	inline static void	_valueSwapFarNodes(pointer const node0, pointer const node1)
	{
		// Step 0:
		// Swap pointers going to node0 and node1.
		rb_tree::_relinkGoingTo(node1, node0);
		rb_tree::_relinkGoingTo(node0, node1);

		// Step 1:
		// Swap pointers leaving from node0 and node1.
		ft::swap<pointer>(node0->parent, node1->parent);
		ft::swap<pointer>(node0->child[LEFT], node1->child[LEFT]);
		ft::swap<pointer>(node0->child[RIGHT], node1->child[RIGHT]);

		// Step 2:
		// Swap colors of node0 and node1.
		ft::swap<uint8_t>(node0->color, node1->color);
	}

	/**
	 * @brief	Swap indirectly the values stored in two different nodes, assuming that the nodes are father and son,
	 * 			changing the links and the colors of the nodes instead of just swapping the values, because we can not
	 * 			be certain that the assignation operator will be available for the value_type.
	 * 
	 * @param	father The father node.
	 * @param	son The son node.
	 */
	inline static void	_valueSwapFatherSon(pointer const father, pointer const son)
	{
		uint8_t const	dir = rb_tree::_childDirection(son);

		// Step 0:
		// Swap pointers going to father and son.
		if (father->parent)
			father->parent->child[rb_tree::_childDirection(father)] = son;
		if (father->child[!dir])
			father->child[!dir]->parent = son;
		if (son->child[LEFT])
			son->child[LEFT]->parent = father;
		if (son->child[RIGHT])
			son->child[RIGHT]->parent = father;

		// Step 1:
		// Swap the pointers leaving from father and son.
		son->parent = father->parent;
		father->parent = son;
		father->child[dir] = son->child[dir];
		son->child[dir] = father;
		ft::swap<pointer>(father->child[!dir], son->child[!dir]);

		// Step 2:
		// Swap the colors.
		ft::swap<uint8_t>(father->color, son->color);
	}

	/**
	 * @brief	Swap indirectly the values stored in two different nodes, changing the links and the colors of the nodes
	 * 			instead of just swapping values, because we can not be certain that the assignation operator will be
	 * 			available for the value_type.
	 * 
	 * @param	node0 The first node to be swapped.
	 * @param	node1 The second node to be swapped.
	 */
	inline static void	_valueSwap(pointer const node0, pointer const node1)
		__attribute__((nonnull))
	{
		if (node0->parent == node1)
			rb_tree::_valueSwapFatherSon(node1, node0);
		else if (node1->parent == node0)
			rb_tree::_valueSwapFatherSon(node0, node1);
		else
			rb_tree::_valueSwapFarNodes(node0, node1);
	}

public:
// ****************************************************************************************************************** //
//                                                    Constructors                                                    //
// ****************************************************************************************************************** //

	/**
	 * @brief	Construct a new empty rb_tree object. (default constructor)
	 */
	rb_tree(void) :
		_root(NULL),
		_min(NULL),
		_max(NULL),
		_size(0LU) {}

	/**
	 * @brief	Construct a new rb_tree object using a range of iterators.
	 * 			The resulting rb_tree will contain elements from `first` included to `last` excluded.
	 * 			(range constructor)
	 * 
	 * @tparam	InputIterator The type of the iterators to use.
	 * 			(it must conform to the standard input iterator requirements)
	 * 
	 * @param	first The first element of the range.
	 * @param	last The last element of the range.
	 */
	template <typename InputIterator>
	rb_tree(InputIterator first, InputIterator const last) :
		_root(NULL),
		_min(NULL),
		_max(NULL),
		_size(0LU)
	{
		for (; first != last ; ++first)
		{
			this->insert(*first);
		}
	}

	/**
	 * @brief	Construct a new rb_tree object as a copy of another one. (copy constructor)
	 * 
	 * @param	src The rb_tree to copy
	 */
	rb_tree(rb_tree const &src) :
		_root(rb_tree::_dup(src._root)),
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
//                                                     Accessors                                                     //
// ***************************************************************************************************************** //

	/**
	 * @brief	Get the node with the greatest value of the tree.
	 * 
	 * @return	The node with the greatest value of the tree.
	 */
	pointer const	&getMax(void) const
	{
		return this->_max;
	}

	/**
	 * @brief	Get the node with the lowest value of the tree.
	 * 
	 * @return	The node with the lowest value of the tree.
	 */
	pointer const	&getMin(void) const
	{
		return this->_min;
	}

	/**
	 * @brief	Get the root node of the tree.
	 * 
	 * @return	The root node of the tree.
	 */
	pointer const	&getRoot(void) const
	{
		return this->_root;
	}

	/**
	 * @brief	Get the size of the tree.
	 * 
	 * @return	The size of the tree.
	 */
	size_type const	&getSize(void) const
	{
		return this->_size;
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
	 * @brief	Remove every nodes of the tree, and set its size accordingly.
	 */
	void	clear(void)
	{
		rb_tree::_clear(this->_root);
		bzero(this, sizeof(*this));
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
	 * @brief	Remove a node from the tree.
	 * 
	 * @param	data The data of the node to remove.
	 * 
	 * @return	The number of removed node(s).
	 */
	size_type	erase(value_type const &data)
	{
		pointer const	node = this->find(data);
		pointer			successor;
		uint8_t			dir;
		allocator_type	alloc;

		if (!node)
			return 0LU;

		// At this point, the node exists.
		if (this->_size == 1LU)
		{
			// At this point, the node is the only one in the tree.
			bzero(this, sizeof(*this));
			alloc.destroy(node);
			alloc.deallocate(node, 1LU);
			return 1LU;
		}

		// At this point, the node is not the only one of the tree.
		if (node->child[LEFT] && node->child[RIGHT])
		{
			// At this point, the node has a left child, and has a right child.
			// So we just swap the node with its successor
			successor = rb_node<value_type>::leftMost(node->child[RIGHT]);
			rb_tree::_valueSwap(node, successor);
			if (node == this->_root)
				this->_root = successor;
		}

		// At this point, the node has at most one child.
		if (node->child[LEFT])
		{
			// At this point, the node is black, and has only one red left child.
			if (node->parent)
				node->parent->child[rb_tree::_childDirection(node)] = node->child[LEFT];
			node->child[LEFT]->parent = node->parent;
			node->child[LEFT]->color = BLACK;
			if (node == this->_root)
				this->_root = node->child[LEFT];
			if (node == this->_max)
				this->_max = node->child[LEFT];
		}
		else if (node->child[RIGHT])
		{
			// At this point, the node is black, and has only one red right child.
			if (node->parent)
				node->parent->child[rb_tree::_childDirection(node)] = node->child[RIGHT];
			node->child[RIGHT]->parent = node->parent;
			node->child[RIGHT]->color = BLACK;
			if (node == this->_root)
				this->_root = node->child[RIGHT];
			if (node == this->_min)
				this->_min = node->child[RIGHT];
		}
		else if (node->color == RED)
		{
			// At this point, the node is red, and has no any child.
			if (node->parent)
				node->parent->child[rb_tree::_childDirection(node)] = NULL;
		}
		else
		{
			// At this point, the node is black, has a parent, and has no any child.
			if (node == this->_min)
				this->_min = node->parent;
			if (node == this->_max)
				this->_max = node->parent;
			dir = rb_tree::_childDirection(node);
			node->parent->child[dir] = NULL;
			this->_balanceErase(node, dir);
		}
		alloc.destroy(node);
		alloc.deallocate(node, 1LU);
		--this->_size;
		return 1LU;
	}

	/**
	 * @brief	Search for a node in the tree.
	 * 
	 * @param	data The data of the node to search for.
	 * 
	 * @return	A pointer to the node if found, or NULL if not.
	 */
	pointer	find(value_type const &data) const
	{
		pointer			node;
		compare_type	cmp;

		node = this->_root;
		while (node && node->data != data)
			if (cmp(data, node->data))
				node = node->child[LEFT];
			else
				node = node->child[RIGHT];
		return node;
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
		pointer			parent;
		pointer			node;
		pointer			pos;
		compare_type	cmp;
		allocator_type	alloc;

		if (!this->_root)
		{
			this->_root = alloc.allocate(1LU);
			this->_min = this->_root;
			this->_max = this->_root;
			this->_size = 1LU;
			alloc.construct(this->_root, node_type(data));
			return pair<iterator, bool>(iterator(this->_root), true);
		}

		pos = this->_root;
		while (pos)
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

		node = alloc.allocate(1LU);
		alloc.construct(node, node_type(data));
		node->parent = parent;
		if (cmp(parent->data, data))
		{
			parent->child[RIGHT] = node;
			if (parent == this->_max)
				this->_max = node;
		}
		else
		{
			parent->child[LEFT] = node;
			if (parent == this->_min)
				this->_min = node;
		}
		++this->_size;
		this->_balanceInsert(node);
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
};
}
#endif
