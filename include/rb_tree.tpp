/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rb_tree.tpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jodufour <jodufour@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/19 21:43:39 by jodufour          #+#    #+#             */
/*   Updated: 2022/08/22 23:02:04 by jodufour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RB_TREE_TPP
# define RB_TREE_TPP

# include <memory>

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
	T			data;

	uint8_t		color;

	rb_node	*parent;
	rb_node	*child[2];
};

template <typename T, typename Compare, typename Alloc = std::allocator<rb_node<T>>>
class rb_tree
{
private:
	// Attributes
	rb_node	*_root;

public:
// ************************************************************************** //
//                                Constructors                                //
// ************************************************************************** //

	/**
	 * @brief	Construct a new rb_tree object.
	 * 			(default constructor)
	 * 
	 * @param	root The root node of the new tree.
	 */
	rb_tree(rb_node const *const root = NULL) :
		_root(root) {}

	/**
	 * @brief	Construct a new rb_tree object.
	 * 			(copy constructor)
	 * 
	 * @param	src The rb_tree to copy
	 */
	rb_tree(rb_tree const &src) :
		_root(NULL)
	{
		if (src._root)
			this->_root = rb_tree::dup(src._root);
	}

// ************************************************************************* //
//                                Destructors                                //
// ************************************************************************* //

	/**
	 * @brief	Destroy a rb_tree object,
	 * 			relasing its related allocated memory.
	 * 			(destructor)
	 */
	~rb_tree(void)
	{
		rb_tree::clear(this->_root);
	}

// ************************************************************************* //
//                          Public Member Functions                          //
// ************************************************************************* //

	/**
	 * @brief	Remove every nodes of the given tree.
	 * 
	 * @param	root The root of the tree to clear.
	 */
	static void	clear(rb_node *const root)
		__attribute__((nonnull))
	{
		Alloc	alloc;

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
	static uint8_t	childDirection(rb_node const *const node)
		__attribute__((nonnull))
	{
		if (node->parent->child[LEFT] == node)
			return LEFT;
		return RIGHT;
	}

	/**
	 * @brief	Duplicate every node from a tree to another,
	 * 			using deep copy.
	 * 
	 * @param	src The source root.
	 * 
	 * @return	The root of the new tree.
	 */
	static rb_node<T>	*dup(rb_node<T> const *const src)
		__attribute__((nonnull))
	{
		rb_node<T>	*dst;
		Alloc		alloc;

		dst = alloc.allocate(1);
		alloc.construct(dst, *src);
		if (src->child[LEFT])
			dst->child[LEFT] = rb_tree::dup(src->child[LEFT]);
		if (src->child[RIGHT])
			dst->child[RIGHT] = rb_tree::dup(src->child[RIGHT]);
		return dst;
	}

	/**
	 * @brief	Rotate a portion of the tree to the given direction.
	 * 			The colors are not modified.
	 * 
	 * @param	root The root of the subtree to rotate.
	 * @param	dir The direction to rotate the subtree.
	 * 
	 * @return	The new root of the rotated subtree.
	 * 			Upon failure, NULL is returned instead.
	 */
	rb_node<T>	*rotate(rb_node<T> *const root, uint8_t const dir)
		__attribute__((nonnull))
	{
		rb_node<T>	*parent;
		rb_node<T>	*oppositeChild;
		rb_node<T>	*grandChild;

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
	 * @return	A pair containing an iterator to the node of the tree.
	 */
	pair<> insert(T const &data)
	{
		rb_node<T>	*node;

		
	}
};
}
#endif
