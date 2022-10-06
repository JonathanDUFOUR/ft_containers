/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rb_tree.tpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jodufour <jodufour@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/19 21:43:39 by jodufour          #+#    #+#             */
/*   Updated: 2022/10/06 17:45:34 by jodufour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RB_TREE_TPP
# define RB_TREE_TPP

# include <cassert>
# include <cstring>
# include <functional>
# include <memory>
# include "algorithm.hpp"
# include "iterator/spec/rb_tree_iterator.tpp"
# include "iterator/spec/reverse_iterator.tpp"
# include "utility.hpp"
# include "rb_node.tpp"
# include "e_rb_color.hpp"
# include "e_rb_direction.hpp"
# include "e_rb_min_max.hpp"

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
private:
	// Member types
	typedef rb_node<T>												_node_type;

public:
	// Member types
	typedef T														value_type;
	typedef Compare													compare_type;
	typedef Alloc													allocator_type;

	typedef typename allocator_type::pointer						pointer;
	typedef typename allocator_type::const_pointer					const_pointer;

	typedef typename allocator_type::reference						reference;
	typedef typename allocator_type::const_reference				const_reference;

	typedef rb_tree_iterator<value_type const, _node_type const>	const_iterator;
	typedef rb_tree_iterator<value_type, _node_type>				iterator;

	typedef reverse_iterator<const_iterator>						const_reverse_iterator;
	typedef reverse_iterator<iterator>								reverse_iterator;

	typedef typename iterator_traits<iterator>::difference_type		difference_type;
	typedef size_t													size_type;

private:
	// Attributes
	pointer			_nil;
	pointer			_root;

	size_type		_size;

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
		if (sibling->color == RB_RED)
		{
			// At this point, the node has a black-deducted parent, and has a red sibling.
			// (D3)
			this->_rotate(parent, dir);
			parent->color = RB_RED;
			sibling->color = RB_BLACK;
			return this->_balanceErase(node, dir);
		}

		// At this point, the node has a parent, and has a black sibling.
		closeNephew = sibling->child[dir];
		if (closeNephew->color == RB_RED)
		{
			// At this point, the node has a parent, has a black sibling, and has a red close nephew.
			// (D5)
			sibling = this->_rotate(sibling, !dir);
			sibling->color = RB_BLACK;
			sibling->child[!dir]->color = RB_RED;
		}
		distantNephew = sibling->child[!dir];
		if (distantNephew->color == RB_RED)
		{
			// At this point, the node has a parent, has a black sibling, and has a red distant nephew.
			// (D6)
			this->_rotate(parent, dir);
			sibling->color = parent->color;
			parent->color = RB_BLACK;
			distantNephew->color = RB_BLACK;
			return ;
		}

		// At this point, the node has a parent, has a black sibling,
		// has either no close nephew or a black close nephew,
		// and has either no distant nephew or a black distant nephew.
		if (parent->color == RB_RED)
		{
			// At this point, the node has a red parent, has a black sibling,
			// has either no close nephew or a black close nephew,
			// and has either no distant nephew or a black distant nephew.
			// (D4)
			sibling->color = RB_RED;
			parent->color = RB_BLACK;
			return ;
		}

		// At this point, the node has a black parent, has a black sibling,
		// has either no close nephew or a black close nephew,
		// and has either no distant nephew or a black distant nephew.
		// (D1)
		sibling->color = RB_RED;
		if (parent->parent != this->_nil)
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
		if (parent->color == RB_BLACK)
			// At this point, the node has a black parent. (I1 + I3)
			return ;

		// At this point, the node is red, and has red parent. (red violation)
		grandParent = parent->parent;
		if (grandParent == this->_nil)
		{
			// At this point, the node is red, has red parent, and has no grandparent. (red violation) (I4)
			node->parent->color = RB_BLACK;
			return ;
		}

		// At this point, the node is red, has a red parent, and has a black grand-parent. (red violation)
		dir = rb_tree::_childDirection(parent);
		uncle = grandParent->child[!dir];
		if (uncle->color == RB_BLACK)
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
			parent->color = RB_BLACK;
			grandParent->color = RB_RED;
		}
		else
		{
			// At this point, the node is red, has a red parent, has a black grand-parent, and has a red uncle.
			// (red violation) (I2)
			parent->color = RB_BLACK;
			uncle->color = RB_BLACK;
			grandParent->color = RB_RED;
			this->_balanceInsert(grandParent);
		}
	}

	/**
	 * @brief	Get the direction of the given node, relative to its parent.
	 * 
	 * @param	node The node we want to check the direction.
	 * 
	 * @return	Either RB_LEFT if the given node is the left child of its parent,
	 * 			or RB_RIGHT if the given node is the right child of its parent.
	 */
	inline static uint8_t	_childDirection(const_pointer const node)
		__attribute__((nonnull))
	{
		if (node->parent->child[RB_LEFT] == node)
			return RB_LEFT;
		return RB_RIGHT;
	}

	/**
	 * @brief	Remove every nodes of the tree except the nil node.
	 * 
	 * @param	root The root of the tree to clear.
	 */
	void	_clear(pointer const root) const
	{
		allocator_type	alloc;

		if (root == this->_nil)
			return ;
		this->_clear(root->child[RB_LEFT]);
		this->_clear(root->child[RB_RIGHT]);
		alloc.destroy(root);
		alloc.deallocate(root, 1LU);
	}

	/**
	 * @brief	Duplicate every node from a tree, using deep copy.
	 * 
	 * @param	srcRoot The source root node.
	 * @param	srcNil The source nil node.
	 * @param	parent The parent node of the new one to create.
	 * 
	 * @return	The root of the new tree.
	 */
	pointer	_dup(const_pointer const srcRoot, pointer const srcNil, pointer const parent) const
	{
		pointer			dst;
		allocator_type	alloc;

		if (srcRoot == srcNil)
			return this->_nil;
		dst = alloc.allocate(1LU);
		alloc.construct(dst, *srcRoot);
		dst->parent = parent;
		dst->child[RB_LEFT] = this->_dup(srcRoot->child[RB_LEFT], srcNil, dst);
		dst->child[RB_RIGHT] = this->_dup(srcRoot->child[RB_RIGHT], srcNil, dst);
		return dst;
	}

	/**
	 * @brief	Get the node placed the most on the left of another one.
	 * 
	 * @param	node The node to start from.
	 * 
	 * @return	The node placed the most on the left of the given one.
	 */
	pointer	_leftMost(pointer node) const
	{
		while (node->child[RB_LEFT] != this->_nil)
			node = node->child[RB_LEFT];
		return node;
	}

	/**
	 * @brief	Get the node placed the most on the left of another one.
	 * 
	 * @param	node The node to start from.
	 * 
	 * @return	The node placed the most on the left of the given one.
	 */
	const_pointer	_leftMost(const_pointer node) const
	{
		while (node->child[RB_LEFT] != this->_nil)
			node = node->child[RB_LEFT];
		return node;
	}

	/**
	 * @brief	Search recursively for the first element in the tree
	 * 			that should be after or at the position of the one with the given value,
	 * 			assuming the searched elemement is lower or equal to the max one.
	 * 
	 * @param	pos The current position to consider.
	 * @param	val The value of the virtual element preceding the searched one.
	 * @param	cmp The comparison functor to use.
	 * 
	 * @return	A pointer to the found element.
	 */
	pointer	_lower_bound(pointer const pos, value_type const &val, compare_type const &cmp) const
	{
		pointer	deeper;

		if (cmp(pos->val, val))
		{
			if (pos->child[RB_RIGHT] == this->_nil)
				return pos;
			return this->_lower_bound(pos->child[RB_RIGHT], val, cmp);
		}
		else if (cmp(val, pos->val))
		{
			if (pos->child[RB_LEFT] == this->_nil)
				return pos;
			deeper = this->_lower_bound(pos->child[RB_LEFT], val, cmp);
			if (!cmp(val, deeper->val))
			{
				if (!cmp(deeper->val, val))
					return deeper;
				return pos;
			}
			return deeper;
		}
		else
			return pos;
	}

	/**
	 * @brief	Relink the children and the parent of a given node to another one,
	 * 			assuming that the nodes are not father and son.
	 * 
	 * @param	dst The destination node.
	 * @param	src The source node.
	 */
	inline void	_relinkGoingTo(pointer const dst, pointer const src) const
		__attribute__((nonnull))
	{
		if (src->parent != this->_nil)
			src->parent->child[rb_tree::_childDirection(src)] = dst;
		if (src->child[RB_LEFT] != this->_nil)
			src->child[RB_LEFT]->parent = dst;
		if (src->child[RB_RIGHT] != this->_nil)
			src->child[RB_RIGHT]->parent = dst;
	}

	/**
	 * @brief	Get the node placed the most on the right of another one.
	 * 
	 * @param	node The node to start from.
	 * 
	 * @return	The node placed the most on the right of the given one.
	 */
	pointer	_rightMost(pointer node) const
	{
		while (node->child[RB_RIGHT] != this->_nil)
			node = node->child[RB_RIGHT];
		return node;
	}

	/**
	 * @brief	Get the node placed the most on the right of another one.
	 * 
	 * @param	node The node to start from.
	 * 
	 * @return	The node placed the most on the right of the given one.
	 */
	const_pointer	_rightMost(const_pointer node) const
	{
		while (node->child[RB_RIGHT] != this->_nil)
			node = node->child[RB_RIGHT];
		return node;
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
		pointer	parent;
		pointer	oppositeChild;
		pointer	grandChild;

		parent = root->parent;
		oppositeChild = root->child[!dir];
		assert(oppositeChild != this->_nil);
		grandChild = oppositeChild->child[dir];

		root->child[!dir] = grandChild;
		if (grandChild != this->_nil)
			grandChild->parent = root;

		oppositeChild->child[dir] = root;
		root->parent = oppositeChild;

		oppositeChild->parent = parent;
		if (parent != this->_nil)
		{
			if (root == parent->child[RB_LEFT])
				parent->child[RB_LEFT] = oppositeChild;
			else
				parent->child[RB_RIGHT] = oppositeChild;
		}
		else
			this->_root = oppositeChild;

		return oppositeChild;
	}

	/**
	 * @brief	Search recursively for the first element in the tree
	 * 			that should be strictly after the position of the one with the given value,
	 * 			assuming the searched elemement is lower or equal to the max one.
	 * 
	 * @param	pos The current position to consider.
	 * @param	val The value of the virtual element preceding the searched one.
	 * @param	cmp The comparison functor to use.
	 * 
	 * @return	A pointer to the found element.
	 */
	pointer	_upper_bound(pointer const pos, value_type const &val, compare_type const &cmp) const
	{
		pointer	deeper;

		if (cmp(pos->val, val) || !cmp(val, pos->val))
		{
			if (pos->child[RB_RIGHT] == this->_nil)
				return pos;
			return this->_upper_bound(pos->child[RB_RIGHT], val, cmp);
		}
		else
		{
			if (pos->child[RB_LEFT] == this->_nil)
				return pos;
			deeper = this->_upper_bound(pos->child[RB_LEFT], val, cmp);
			if (!cmp(val, deeper->val))
				return pos;
			return deeper;
		}
	}

	/**
	 * @brief	Swap indirectly the values stored in two different nodes, assuming that the nodes aren't father and son,
	 * 			changing the links and the colors of the nodes instead of just swapping the values, because we can not
	 * 			be certain that the assignation operator will be available for the value_type.
	 * 
	 * @param	node0 The first node to be swapped.
	 * @param	node1 The second node to be swapped.
	 */
	inline void	_valueSwapFarNodes(pointer const node0, pointer const node1) const
	{
		// Step 0:
		// Swap pointers going to node0 and node1.
		this->_relinkGoingTo(node1, node0);
		this->_relinkGoingTo(node0, node1);

		// Step 1:
		// Swap pointers leaving from node0 and node1.
		ft::swap<pointer>(node0->parent, node1->parent);
		ft::swap<pointer>(node0->child[RB_LEFT], node1->child[RB_LEFT]);
		ft::swap<pointer>(node0->child[RB_RIGHT], node1->child[RB_RIGHT]);

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
	inline void	_valueSwapFatherSon(pointer const father, pointer const son) const
		__attribute__((nonnull))
	{
		uint8_t const	dir = rb_tree::_childDirection(son);

		// Step 0:
		// Swap pointers going to father and son.
		if (father->parent != this->_nil)
			father->parent->child[rb_tree::_childDirection(father)] = son;
		if (father->child[!dir] != this->_nil)
			father->child[!dir]->parent = son;
		if (son->child[RB_LEFT] != this->_nil)
			son->child[RB_LEFT]->parent = father;
		if (son->child[RB_RIGHT] != this->_nil)
			son->child[RB_RIGHT]->parent = father;

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
	inline void	_valueSwap(pointer const node0, pointer const node1) const
		__attribute__((nonnull))
	{
		if (node0->parent == node1)
			this->_valueSwapFatherSon(node1, node0);
		else if (node1->parent == node0)
			this->_valueSwapFatherSon(node0, node1);
		else
			this->_valueSwapFarNodes(node0, node1);
	}

public:
// ****************************************************************************************************************** //
//                                                    Constructors                                                    //
// ****************************************************************************************************************** //

	/**
	 * @brief	Construct a new empty rb_tree object. (default constructor)
	 */
	rb_tree(void) :
		_nil(allocator_type().allocate(1LU)),
		_root(this->_nil),
		_size(0LU)
	{
		allocator_type().construct(this->_nil, _node_type(value_type(), RB_BLACK, NULL, this->_nil, this->_nil));
	}

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
	rb_tree(InputIterator first, InputIterator const &last) :
		_nil(allocator_type().allocate(1LU)),
		_root(this->_nil),
		_size(0LU)
	{
		allocator_type().construct(this->_nil, _node_type(value_type(), RB_BLACK, NULL, this->_nil, this->_nil));
		for (; first != last ; ++first)
			this->insert(*first);
	}

	/**
	 * @brief	Construct a new rb_tree object as a copy of another one. (copy constructor)
	 * 
	 * @param	src The rb_tree to copy
	 */
	rb_tree(rb_tree const &src) :
		_nil(allocator_type().allocate(1LU)),
		_root(this->_dup(src._root, src._nil, this->_nil)),
		_size(src._size)
	{
		allocator_type	alloc;

		if (this->_size)
			alloc.construct(this->_nil, _node_type(
				value_type(),
				RB_BLACK,
				NULL,
				this->_leftMost(this->_root),
				this->_rightMost(this->_root)));
		else
			alloc.construct(this->_nil, _node_type(value_type(), RB_BLACK, NULL, this->_nil, this->_nil));
	}

// ***************************************************************************************************************** //
//                                                    Destructors                                                    //
// ***************************************************************************************************************** //

	/**
	 * @brief	Destroy a rb_tree object, relasing its related allocated memory. (destructor)
	 */
	~rb_tree(void)
	{
		allocator_type	alloc;

		this->clear();
		alloc.destroy(this->_nil);
		alloc.deallocate(this->_nil, 1LU);
	}

// ***************************************************************************************************************** //
//                                                     Accessors                                                     //
// ***************************************************************************************************************** //

	/**
	 * @return	The nil node of the tree.
	 */
	inline pointer const	&getNil(void) const
	{
		return this->_nil;
	}

	/**
	 * @return	The root node of the tree.
	 */
	inline pointer const	&getRoot(void) const
	{
		return this->_root;
	}

	/**
	 * @return	The size of the tree.
	 */
	inline size_type const	&getSize(void) const
	{
		return this->_size;
	}

// ***************************************************************************************************************** //
//                                              Public Member Functions                                              //
// ***************************************************************************************************************** //

	/**
	 * @return	An iterator to the first element of the tree.
	 */
	inline iterator	begin(void)
	{
		return iterator(this->_nil->child[RB_MIN]);
	}

	/**
	 * @return	A const_iterator to the first element of the tree.
	 */
	inline const_iterator	begin(void) const
	{
		return const_iterator(this->_nil->child[RB_MIN]);
	}

	/**
	 * @brief	Remove every nodes of the tree, and set its size accordingly.
	 */
	void	clear(void)
	{
		this->_clear(this->_root);
		this->_nil->child[RB_MIN] = this->_nil;
		this->_nil->child[RB_MAX] = this->_nil;
		this->_root = this->_nil;
		this->_size = 0LU;
	}

	/**
	 * @return	An iterator to the last element of the tree.
	 */
	inline iterator	end(void)
	{
		return iterator(this->_nil);
	}

	/**
	 * @return	A const_iterator to the last element of the tree.
	 */
	inline const_iterator	end(void) const
	{
		return const_iterator(this->_nil);
	}


	/**
	 * @brief	Search for elements matching a given value in the tree.
	 * 			The resulting match is returned as a range of iterator,
	 * 			from the first element included to the last element excluded.
	 * 
	 * @param	val The value to search for.
	 * 
	 * @return	A pair containing an iterator to the first element of the matching range as `first` member,
	 * 			and an iterator to the last element of the matching range as `second` member.
	 */
	pair<iterator, iterator>	equal_range(value_type const &val)
	{
		return pair<iterator, iterator>(this->lower_bound(val), this->upper_bound(val));
	}

	/**
	 * @brief	Search for constant elements matching a given value in the tree.
	 * 			The resulting match is returned as a range of const_iterator,
	 * 			from the first constant element included to the last constant element excluded.
	 * 
	 * @param	val The value to search for.
	 * 
	 * @return	A pair containing an iterator to the first constant element of the matching range as `first` member,
	 * 			and an iterator to the last constant element of the matching range as `second` member.
	 */
	pair<const_iterator, const_iterator>	equal_range(value_type const &val) const
	{
		return pair<const_iterator, const_iterator>(this->lower_bound(val), this->upper_bound(val));
	}

	/**
	 * @brief	Remove a node from the tree. (value erase)
	 * 
	 * @param	val The value of the node to remove.
	 * 
	 * @return	The number of removed node(s).
	 */
	size_type	erase(value_type const &val)
	{
		pointer const	pos = this->find(val);

		if (pos == this->_nil)
			return 0LU;
		this->erase(pos);
		return 1LU;
	}

	/**
	 * @brief	Remove a node from the tree. (position erase)
	 * 
	 * @param	pos The position of the node to remove.
	 */
	void	erase(pointer const pos)
	{
		pointer			successor;
		uint8_t			dir;
		allocator_type	alloc;

		assert(pos && pos != this->_nil);

		// At this point, the node exists.
		if (this->_size == 1LU)
		{
			// At this point, the node is the only one in the tree.
			this->_nil->child[RB_MIN] = this->_nil;
			this->_nil->child[RB_MAX] = this->_nil;
			this->_root = this->_nil;
			this->_size = 0LU;
			alloc.destroy(pos);
			alloc.deallocate(pos, 1LU);
			return ;
		}

		// At this point, the node is not the only one of the tree.
		if (pos->child[RB_LEFT] != this->_nil && pos->child[RB_RIGHT] != this->_nil)
		{
			// At this point, the node has a left child, and has a right child.
			// So we just swap the node with its successor.
			successor = this->_leftMost(pos->child[RB_RIGHT]);
			this->_valueSwap(pos, successor);
			if (this->_root == pos)
				this->_root = successor;
		}

		// At this point, the node has at most one child.
		if (pos->child[RB_LEFT] != this->_nil)
		{
			// At this point, the node is black-deducted, and has only one red-deducted left child.
			if (pos->parent != this->_nil)
				pos->parent->child[rb_tree::_childDirection(pos)] = pos->child[RB_LEFT];
			pos->child[RB_LEFT]->parent = pos->parent;
			pos->child[RB_LEFT]->color = RB_BLACK;
			if (this->_root == pos)
				this->_root = pos->child[RB_LEFT];
			if (this->_nil->child[RB_MAX] == pos)
				this->_nil->child[RB_MAX] = pos->child[RB_LEFT];
		}
		else if (pos->child[RB_RIGHT] != this->_nil)
		{
			// At this point, the node is black-deducted, and has only one red-deducted right child.
			if (pos->parent != this->_nil)
				pos->parent->child[rb_tree::_childDirection(pos)] = pos->child[RB_RIGHT];
			pos->child[RB_RIGHT]->parent = pos->parent;
			pos->child[RB_RIGHT]->color = RB_BLACK;
			if (this->_root == pos)
				this->_root = pos->child[RB_RIGHT];
			if (this->_nil->child[RB_MIN] == pos)
				this->_nil->child[RB_MIN] = pos->child[RB_RIGHT];
		}
		else if (pos->color == RB_RED)
		{
			// At this point, the node is red, has a parent, and has no any child.
			pos->parent->child[rb_tree::_childDirection(pos)] = this->_nil;
			if (this->_nil->child[RB_MIN] == pos)
				this->_nil->child[RB_MIN] = pos->parent;
			if (this->_nil->child[RB_MAX] == pos)
				this->_nil->child[RB_MAX] = pos->parent;
		}
		else
		{
			// At this point, the node is black, has a parent, and has no any child.
			if (this->_nil->child[RB_MIN] == pos)
				this->_nil->child[RB_MIN] = pos->parent;
			if (this->_nil->child[RB_MAX] == pos)
				this->_nil->child[RB_MAX] = pos->parent;
			dir = rb_tree::_childDirection(pos);
			pos->parent->child[dir] = this->_nil;
			this->_balanceErase(pos, dir);
		}
		alloc.destroy(pos);
		alloc.deallocate(pos, 1LU);
		--this->_size;
	}

	/**
	 * @brief	Search for a node in the tree.
	 * 
	 * @param	val The value of the node to search for.
	 * 
	 * @return	A pointer to the node if found, or nil node if not.
	 */
	pointer	find(value_type const &val) const
	{
		pointer			node;
		compare_type	cmp;

		node = this->_root;
		while (node != this->_nil)
			if (cmp(val, node->val))
				node = node->child[RB_LEFT];
			else if (cmp(node->val, val))
				node = node->child[RB_RIGHT];
			else
				break ;
		return node;
	}

	/**
	 * @brief	Insert a new node in the tree. (single insertion)
	 * 
	 * @param	val The value to insert in the tree.
	 * 
	 * @return	A pair containing an iterator to the node of the tree with the given value as `first` member,
	 * 			and a boolean indicating whether a new node has been inserted as `second` member.
	 */
	pair<iterator, bool> insert(value_type const &val)
	{
		pointer			parent;
		pointer			node;
		pointer			pos;
		compare_type	cmp;
		allocator_type	alloc;

		if (!this->_size)
		{
			// At this point, the tree is empty.
			this->_root = alloc.allocate(1LU);
			this->_nil->child[RB_MIN] = this->_root;
			this->_nil->child[RB_MAX] = this->_root;
			this->_size = 1LU;
			alloc.construct(this->_root, _node_type(val, RB_RED, this->_nil, this->_nil, this->_nil));
			return pair<iterator, bool>(iterator(this->_root), true);
		}

		// At this point, the tree is not empty.
		pos = this->_root;
		while (pos != this->_nil)
			if (cmp(val, pos->val))
			{
				parent = pos;
				pos = pos->child[RB_LEFT];
			}
			else if (cmp(pos->val, val))
			{
				parent = pos;
				pos = pos->child[RB_RIGHT];
			}
			else
				return pair<iterator, bool>(iterator(pos), false);

		// At this point, `parent` is the leaf node where the new node will be inserted.
		node = alloc.allocate(1LU);
		alloc.construct(node, _node_type(val, RB_RED, parent, this->_nil, this->_nil));
		if (cmp(val, parent->val))
		{
			parent->child[RB_LEFT] = node;
			if (this->_nil->child[RB_MIN] == parent)
				this->_nil->child[RB_MIN] = node;
		}
		else
		{
			parent->child[RB_RIGHT] = node;
			if (this->_nil->child[RB_MAX] == parent)
				this->_nil->child[RB_MAX] = node;
		}
		++this->_size;
		this->_balanceInsert(node);
		return pair<iterator, bool>(iterator(node), true);
	}

	/**
	 * @brief	Insert a new node in the tree. (single insertion with hint)
	 * 
	 * @param	pos The hint position of the parent of the node to insert.
	 * 			Invalid position causes undefined behavior.
	 * @param	val The value to insert in the tree.
	 * 
	 * @return	An iterator to the node of the tree with the given value.
	 */
	iterator insert(pointer pos, value_type const &val)
	{
		pointer			parent;
		pointer			node;
		compare_type	cmp;
		allocator_type	alloc;

		if (!this->_size)
		{
			// At this point, the tree is empty.
			this->_root = alloc.allocate(1LU);
			this->_nil->child[RB_MIN] = this->_root;
			this->_nil->child[RB_MAX] = this->_root;
			this->_size = 1LU;
			alloc.construct(this->_root, _node_type(val, RB_RED, this->_nil, this->_nil, this->_nil));
			return iterator(this->_root);
		}

		// At this point, the tree is not empty.
		if (pos == this->_nil)
			pos = this->_nil->child[RB_MAX];
		node = pos;
		parent = node->parent;
		if (cmp(val, pos->val))
		{
			// At this point, the node to insert will be placed on the left of the hint node.

			// Check for highly wrong position.
			while (parent != this->_nil && node == parent->child[RB_LEFT])
			{
				node = parent;
				parent = node->parent;
			}
			if (parent != this->_nil)
			{
				if (cmp(val, parent->val))
					return this->insert(val).first;
				else if (!cmp(parent->val, val))
					return iterator(parent);
			}

			// At this point, the node to insert will be placed on the left of the hint node,
			// and the position is on a correct branch.
			parent = pos;
			if (pos->child[RB_LEFT] != this->_nil)
			{
				// At this point, the node to insert will be placed on the left of the hint node,
				// the position is on a correct branch, and is a non-leaf.
				pos = pos->child[RB_LEFT];
				while (pos != this->_nil)
					if (cmp(val, pos->val))
					{
						parent = pos;
						pos = pos->child[RB_LEFT];
					}
					else if (cmp(pos->val, val))
					{
						parent = pos;
						pos = pos->child[RB_RIGHT];
					}
					else
						return iterator(pos);
			}
		}
		else if (cmp(pos->val, val))
		{
			// At this point, the node to insert will be placed on the right of the hint node.

			// Check for highly wrong position.
			while (parent != this->_nil && node == parent->child[RB_RIGHT])
			{
				node = parent;
				parent = node->parent;
			}
			if (parent != this->_nil)
			{
				if (cmp(parent->val, val))
					return this->insert(val).first;
				else if (!cmp(val, parent->val))
					return iterator(parent);
			}

			// At this point, the node to insert will be placed on the right of the hint node,
			// and the position is on a correct branch.
			parent = pos;
			if (pos->child[RB_RIGHT] != this->_nil)
			{
				// At this point, the node to insert will be placed on the right of the hint node,
				// and the position is on a correct branch, and is a non-leaf.
				pos = pos->child[RB_RIGHT];
				while (pos != this->_nil)
					if (cmp(val, pos->val))
					{
						parent = pos;
						pos = pos->child[RB_LEFT];
					}
					else if (cmp(pos->val, val))
					{
						parent = pos;
						pos = pos->child[RB_RIGHT];
					}
					else
						return iterator(pos);
			}
		}
		else
			return iterator(pos);

		// At this point, `parent` is the leaf node where the new node will be inserted.
		node = alloc.allocate(1LU);
		alloc.construct(node, _node_type(val, RB_RED, parent, this->_nil, this->_nil));
		if (cmp(val, parent->val))
		{
			parent->child[RB_LEFT] = node;
			if (this->_nil->child[RB_MIN] == parent)
				this->_nil->child[RB_MIN] = node;
		}
		else
		{
			parent->child[RB_RIGHT] = node;
			if (this->_nil->child[RB_MAX] == parent)
				this->_nil->child[RB_MAX] = node;
		}
		++this->_size;
		this->_balanceInsert(node);
		return iterator(node);
	}

	/**
	 * @brief	Search for the first element in the tree
	 * 			that should be after or at the position of the one with the given value.
	 * 
	 * @param	val The value of the virtual element preceding the searched one.
	 * 
	 * @return	An iterator to the element if found, or end() if not.
	 */
	iterator	lower_bound(value_type const &val)
	{
		compare_type const	cmp;

		if (!this->_size || cmp(this->_nil->child[RB_MAX]->val, val))
			return this->end();
		return iterator(this->_lower_bound(this->_root, val, cmp));
	}

	/**
	 * @brief	Search for the first constant element in the tree
	 * 			that should be after or at the position of the one with the given value.
	 * 
	 * @param	val The value of the virtual element preceding the searched one.
	 * 
	 * @return	An const_iterator to the element if found, or end() if not.
	 */
	const_iterator	lower_bound(value_type const &val) const
	{
		compare_type const	cmp;

		if (!this->_size || cmp(this->_nil->child[RB_MAX]->val, val))
			return this->end();
		return const_iterator(this->_lower_bound(this->_root, val, cmp));
	}

	/**
	 * @return	The node corresponding to the maximum value in the rb_tree.
	 */
	inline pointer	max(void) const
	{
		return this->_nil->child[RB_MAX];
	}

	inline size_type	max_size(void) const
	{
		return allocator_type().max_size();
	}

	/**
	 * @return	The node corresponding to the minimum value in the rb_tree.
	 */
	inline pointer	min(void) const
	{
		return this->_nil->child[RB_MIN];
	}

	/**
	 * @return	A reverse_iterator to the last element of the tree.
	 */
	reverse_iterator	rbegin(void)
	{
		return reverse_iterator(this->end());
	}

	/**
	 * @return	A const_reverse_iterator to the last element of the tree.
	 */
	const_reverse_iterator	rbegin(void) const
	{
		return const_reverse_iterator(this->end());
	}

	/**
	 * @return	A reverse_iterator to the pre-first element of the tree.
	 */
	reverse_iterator	rend(void)
	{
		return reverse_iterator(this->begin());
	}

	/**
	 * @return	A const_reverse_iterator to the pre-first element of the tree.
	 */
	const_reverse_iterator	rend(void) const
	{
		return const_reverse_iterator(this->begin());
	}

	/**
	 * @brief	Swap the content of the given tree with the content of the current tree.
	 * 
	 * @param	other The tree to swap with.
	 */
	void	swap(rb_tree &other)
	{
		ft::swap<pointer>(this->_nil, other._nil);
		ft::swap<pointer>(this->_root, other._root);
		ft::swap<size_type>(this->_size, other._size);
	}

	/**
	 * @brief	Search for the first element in the tree
	 * 			that should be strictly after the position of the one with the given value.
	 * 
	 * @param	val The value of the virtual element preceding the searched one.
	 * 
	 * @return	An const_iterator to the element if found, or end() if not.
	 */
	iterator	upper_bound(value_type const &val)
	{
		compare_type const	cmp;

		if (!this->_size || !cmp(val, this->_nil->child[RB_MAX]->val))
			return this->end();
		return iterator(this->_upper_bound(this->_root, val, cmp));
	}

	/**
	 * @brief	Search for the first constant element in the tree
	 * 			that should be after strictly after the position of the one with the given value.
	 * 
	 * @param	val The value of the virtual element preceding the searched one.
	 * 
	 * @return	An const_iterator to the element if found, or end() if not.
	 */
	const_iterator	upper_bound(value_type const &val) const
	{
		compare_type	cmp;

		if (!this->_size || !cmp(val, this->_nil->child[RB_MAX]->val))
			return this->end();
		return const_iterator(this->_upper_bound(this->_root, val, cmp));
	}

// ***************************************************************************************************************** //
//                                                     Operators                                                     //
// ***************************************************************************************************************** //

	/**
	 * @brief	Assign a new content to the rb_tree from another one's. (copy assignation)
	 * 
	 * @param	rhs The right hand side rb_tree to copy the content from.
	 * 
	 * @return	The assigned rb_tree.
	 */
	rb_tree	&operator=(rb_tree const &rhs)
	{
		if (this != &rhs)
		{
			this->_clear(this->_root);
			this->_root = this->_dup(rhs._root, rhs._nil, this->_nil);
			if (this->_root != this->_nil)
			{
				this->_nil->child[RB_MIN] = this->_leftMost(this->_root);
				this->_nil->child[RB_MAX] = this->_rightMost(this->_root);
			}
			else
			{
				this->_nil->child[RB_MIN] = this->_nil;
				this->_nil->child[RB_MAX] = this->_nil;
			}
			this->_size = rhs._size;
		}
		return *this;
	}

}; // class rb_tree

} // namespace ft

#endif
