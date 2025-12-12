#ifndef RED_BLACK_TREE_HPP
#define RED_BLACK_TREE_HPP

#include "algorithm.hpp"
#include "functional.hpp"
#include "iterator.hpp"
#include "memory.hpp"
#include "type/fundamentals.hpp"
#include "utility.hpp"

namespace ft {

enum e_rbt_color { RED, BLACK };

typedef e_rbt_color const t_rbt_color;

enum e_rbt_direction {
    LE, // Left
    RI, // Right

    DIRECTION_COUNT,
};

typedef e_rbt_direction const t_rbt_direction;
typedef e_rbt_direction       t_rbt_direction_mut;

template <typename T>
class rbt_node
{
#define SELF rbt_node

private: /* types */
    typedef SELF const    t_self;
    typedef t_self *const t_self_ptr;
    typedef T const       t_value;

    // TODO: remove unused typedefs when all tests pass

private: /* fields */
    // Allows access to the same memory area via:
    // - `node.m_lchild`       ; `node.m_rchild`
    // - `node.m_children[LE]` ; `node.m_children[RI]`
    union
    {
        struct {
            t_self_ptr m_lchild;
            t_self_ptr m_rchild;
        };

        t_self_ptr m_children[DIRECTION_COUNT];
    };

    t_self_ptr      m_parent;
    t_rbt_color     m_color;
    t_rbt_direction m_direction;
    t_value         m_value;

public: /* constructors */
    //! \complexity O(1).
    //!
    SELF(
        t_self_ptr      lchild,
        t_self_ptr      rchild,
        t_self_ptr      parent,
        t_rbt_color     color,
        t_rbt_direction direction,
        t_value        &value
    )
    : m_lchild(lchild)
    , m_rchild(rchild)
    , m_parent(parent)
    , m_color(color)
    , m_direction(direction)
    , m_value(value)
    {}

public: /* methods */
    //! \return The `direction`most child-node from the caller.
    //!
    //! \complexity O(NodesBeforeLmost).
    //!
    //! \warning `direction` being neither `LE` nor `RI` is undefined behavior.
    //!
    t_self_ptr extreme(
        t_rbt_direction direction
    )
    {
        t_self_ptr node = this;

        while (node->m_children[direction]) {
            node = node->m_children[direction];
        }
        return node;
    }

#undef SELF
};

template <typename Node>
class rbt_iterator
{
#define SELF rbt_iterator

private: /* types */
    typedef SELF const        t_self;
    typedef Node const        t_node;
    typedef t_node *const     t_node_ptr;
    typedef t_node_ptr *const t_node_ptr_ptr;

public: /* types */
    typedef bidirectional_iterator_tag    iterator_category;
    typedef t_isize                       difference_type;
    typedef typename Node::t_value        value_type;
    typedef typename Node::t_value       &reference;
    typedef typename Node::t_value *const pointer;

private: /* fields */
    t_node_ptr     m_ptr;
    t_node_ptr_ptr m_max;

public: /* constructors */
    //! \complexity O(1).
    //!
    SELF(
        t_self &other
    )
    : m_ptr(other.m_ptr), m_max(other.m_max)
    {}

    //! \complexity O(1).
    //!
    SELF() : m_ptr(), m_max() {}

    //! \param ptr The node to point to, or `NULL` for the past-the-end element.
    //!
    //! \param max The node holding the maximum value of the tree.
    //!
    //! \complexity O(1).
    //!
    SELF(
        t_node_ptr ptr, t_node_ptr &max
    )
    : m_ptr(ptr), m_max(&max)
    {}

private: /* methods */
    t_self &move(
        t_rbt_direction direction
    )
    {
        t_rbt_direction opposite = direction == LE ? RI : LE;

        if (m_ptr->m_children[direction]) {
            m_ptr = m_ptr->m_children[direction]->extreme(opposite);
            return *this;
        }
        while (m_ptr->direction == direction) {
            m_ptr = m_ptr->m_parent;
        }
        m_ptr = m_ptr->m_parent;
        return *this;
    }

public: /* operators */
    //! \complexity O(1).
    //!
    t_bool operator==(
        t_self &rhs
    ) const
    {
        return m_ptr == rhs.m_ptr;
    }

    //! \complexity O(1).
    //!
    t_bool operator!=(
        t_self &rhs
    ) const
    {
        return m_ptr != rhs.m_ptr;
    }

    //! \complexity O(1).
    //!
    reference operator*() const { return m_ptr->m_value; }

    //! \complexity O(1).
    //!
    pointer operator->() const { return &m_ptr->m_value; }

    //! \complexity O(1).
    //!
    t_self &operator=(
        t_self &rhs
    )
    {
        m_ptr = rhs.m_ptr;
        m_max = rhs.m_max;
        return *this;
    }

    //! \complexity O(log(TreeSize)) amortized O(1).
    //!
    //! \warning Caller being past-the-end is undefined behavior.
    //!
    t_self &operator++() { return move(RI); }

    //! \complexity O(log(TreeSize)) amortized O(1).
    //!
    //! \warning Caller being past-the-end is undefined behavior.
    //!
    t_self operator++(
        int
    )
    {
        t_self before_inc(*this);

        ++*this;
        return before_inc;
    }

    //! \complexity O(log(TreeSize)) amortized O(1).
    //!
    //! \warning Caller pointing to the first element or an empty tree is undefined behavior.
    //!
    t_self &operator--()
    {
        if (m_ptr) {
            return move(LE);
        }
        m_ptr = *m_max;
        return *this;
    }

    //! \complexity O(log(TreeSize)) amortized O(1).
    //!
    //! \warning Caller pointing to the first element or an empty tree is undefined behavior.
    //!
    t_self operator--(
        int
    )
    {
        t_self before_dec(*this);

        --*this;
        return before_dec;
    }

#undef SELF
};

//! A Red Black Tree is a self-balancing Binary Search Tree (BST)
//! which is ruled by the following properties:
//!  1. Every node is either red or black
//!  2. All `NULL` nodes are considered black
//!  3. A red node does not have a red child
//!  4. Every path from a node to any of its descendant NULL nodes
//!     goes through the same number of black nodes
//!
//! In this implementation:
//!  - a violation of the 3rd property is called a "red violation"
//!  - a violation of the 4th property is called a "black violation"
template <
    t_bool AllowsDuplicates,
    typename T,
    typename Compare   = less<T>,
    typename Allocator = allocator<rbt_node<T> >
>
class red_black_tree
{
#define SELF red_black_tree

private: /* types */
    typedef SELF const                                   t_self;
    typedef SELF                                         t_self_mut;
    typedef T const                                      t_value;
    typedef T                                            t_value_mut;
    typedef Compare const                                t_compare;
    typedef Allocator const                              t_allocator;
    typedef typename Allocator::value_type const         t_node;
    typedef typename Allocator::value_type               t_node_mut;
    typedef typename Allocator::const_pointer const      t_node_ptr;
    typedef rbt_iterator<t_node> const                   t_node_iterator;
    typedef rbt_iterator<t_node_mut> const               t_node_mut_iterator;
    typedef reverse_iterator<t_node_iterator> const      t_node_reverse_iterator;
    typedef reverse_iterator<t_node_mut_iterator> const  t_node_mut_reverse_iterator;
    typedef pair<t_node_iterator, t_node_iterator> const t_node_iterator_pair;

private: /* fields */
    t_compare   m_cmp;
    t_allocator m_alloc;
    t_node_ptr  m_root;

    // Allows both (`tree->m_min`|`tree->m_max`) and
    // (`tree->m_bounds[LE]`|`tree->m_bounds[RI]`)
    union
    {
        struct {
            t_node_ptr m_min;
            t_node_ptr m_max;
        };

        t_node_ptr m_bounds[DIRECTION_COUNT];
    };

    t_usize_mut m_size;

public: /* constructors */
    //! \param cmp The function to compare two elements.
    //!
    //! \complexity O(1).
    //!
    SELF(
        t_compare &cmp = t_compare()
    )
    : m_cmp(cmp), m_alloc(), m_root(), m_min(), m_max(), m_size()
    {}

    //! \complexity O(TreeSize+log(TreeSize)).
    //!
    SELF(
        t_self &other
    )
    : m_cmp(other.m_cmp)
    , m_alloc(other.m_alloc)
    , m_root(recursive_clone(other.m_root))
    , m_min(m_root->lmost())
    , m_max(m_root->rmost())
    , m_size(other.m_size)
    {}

    //! \param first The first element of the range.
    //!
    //! \param ptend The past-the-end element of the range.
    //!
    //! \param cmp   The function to compare two elements.
    //!
    //! \complexity O(RangeSize×log(RangeSize)) amortized O(RangeSize) when the range is sorted.
    //!
    //! \warning `ptend` being unreachable by `first` is undefined behavior.
    //!
    template <typename InputIterator>
    SELF(
        InputIterator first, InputIterator const &ptend, t_compare &cmp = t_compare()
    )
    : m_cmp(cmp), m_alloc(), m_root(), m_min(), m_max(), m_size()
    {
        insert(first, ptend);
    }

public: /* destructor */
    //! \complexity O(TreeSize).
    //!
    ~SELF() { recursive_clear(m_root); }

public: /* accessors */
    //! \complexity O(1).
    //!
    t_compare &cmp() const { return m_cmp; }

    //! \complexity O(1).
    //!
    t_usize size() const { return m_size; }

private: /* methods */
    //! \brief Balances/Recolors the `m_root` tree after the insertion of a red leaf-node
    //!        leading to a red violation.
    //!
    //! \param node           The newly inserted node.
    //!
    //! \param parent         The parent-node of `node`.
    //!
    //! \param node_direction Whether `node` is the right or left child of `parent`.
    //!
    //! \complexity O(log(TreeSize)) amortized O(1).
    //!
    //! \warning `node` not being a red leaf of the `m_root` tree or a child-node of `parent`
    //!          is undefined behavior.
    //!
    //! \warning `parent` not being the parent-node of `node` or being black is undefined behavior.
    //!
    //! \warning `node_direction` not being such as `parent->m_children[node_direction] == node`
    //!          is undefined behavior.
    //!
    void fix_red_violation(
        t_node_ptr          node __attribute__((nonnull)),
        t_node_ptr          parent __attribute__((nonnull)),
        t_rbt_direction_mut node_direction
    )
    {
        do {
            t_node_ptr grandparent = parent->m_parent;

            if (!grandparent) {
                // https://en.wikipedia.org/wiki/Red-black_tree#Insert_case_4
                parent->m_color = BLACK;
                return;
            }
            t_rbt_direction pibling_direction = parent == grandparent->m_lchild ? RI : LE;
            t_node_ptr      pibling           = grandparent->m_children[pibling_direction];

            if (!pibling || pibling->m_color == BLACK) {
                if (node_direction == pibling_direction) {
                    // https://en.wikipedia.org/wiki/Red-black_tree#Insert_case_5
                    node   = parent;
                    parent = rotate(parent, node_direction == LE ? RI : LE);
                }
                // https://en.wikipedia.org/wiki/Red-black_tree#Insert_case_6
                rotate(grandparent, pibling_direction);
                grandparent->m_color = RED;
                parent->m_color      = BLACK;
                return;
            }
            // https://en.wikipedia.org/wiki/Red-black_tree#Insert_case_2
            parent->m_color      = BLACK;
            grandparent->m_color = RED;
            pibling->m_color     = BLACK;
            node                 = grandparent;
            parent               = node->m_parent;
            node_direction       = node == parent->m_lchild ? LE : RI;
        }
        while (parent && parent->m_color == RED);
        // https://en.wikipedia.org/wiki/Red-black_tree#Insert_case_1
        // https://en.wikipedia.org/wiki/Red-black_tree#Insert_case_3
    }

    //! \brief Balances/Recolors the `m_root` tree before the removal of a black leaf-node.
    //!
    //! \param node   The node to remove.
    //!
    //! \param parent The parent-node of `node`.
    //!
    //! \param inner  Whether `node` is the right or left child-node of `parent`.
    //!
    //! \complexity O(log(TreeSize)) amortized O(1).
    //!
    //! \warning `node` not being part of the `m_root` tree or a child-node of `parent`
    //!          is undefined behavior.
    //!
    //! \warning `parent` not being part of the `m_root` tree or the parent-node of `node`
    //!          is undefined behavior.
    //!
    //! \warning `inner` not being such as `parent->m_children[inner] == node`
    //!          is undefined behavior.
    //!
    void prevent_black_violation(
        t_node_ptr      node __attribute__((nonnull)),
        t_node_ptr      parent __attribute__((nonnull)),
        t_rbt_direction inner
    )
    {
        t_rbt_direction_mut outer;
        t_node_ptr          sibling;
        t_node_ptr          inner_nibling;
        t_node_ptr          outer_nibling;

        do {
            outer   = inner == LE ? RI : LE;
            sibling = parent->m_children[outer];

            if (sibling->m_color == RED) {
                // https://en.wikipedia.org/wiki/Red-black_tree#Delete_case_3
                rotate(parent, inner);
                parent->m_color  = RED;
                sibling->m_color = BLACK;
                sibling          = parent->m_children[outer];

                outer_nibling = sibling->m_children[outer];
                if (outer_nibling && outer_nibling->m_color == RED) {
                    goto D6;
                }
                inner_nibling = sibling->m_children[inner];
                if (inner_nibling && inner_nibling->m_color == RED) {
                    goto D5;
                }
                // https://en.wikipedia.org/wiki/Red-black_tree#Delete_case_4
                parent->m_color  = BLACK;
                sibling->m_color = RED;
                return;
            }
            outer_nibling = sibling->m_children[outer];
            if (outer_nibling && outer_nibling->m_color == RED) {
                goto D6;
            }
            inner_nibling = sibling->m_children[inner];
            if (inner_nibling && inner_nibling->m_color == RED) {
                goto D5;
            }
            if (!parent) {
                // https://en.wikipedia.org/wiki/Red-black_tree#Delete_case_1
                return;
            }
            if (parent->m_color == RED) {
                // https://en.wikipedia.org/wiki/Red-black_tree#Delete_case_4
                parent->m_color  = BLACK;
                sibling->m_color = RED;
                return;
            }
            // https://en.wikipedia.org/wiki/Red-black_tree#Delete_case_2
            sibling->m_color = RED;
            node             = parent;
            parent           = node->m_parent;
            inner            = node == parent->m_lchild ? LE : RI;
        }
        while (parent);
    D5: // https://en.wikipedia.org/wiki/Red-black_tree#Delete_case_5
        outer_nibling          = sibling;
        sibling                = rotate(sibling, outer);
        outer_nibling->m_color = RED;
        sibling->m_color       = BLACK;
    D6: // https://en.wikipedia.org/wiki/Red-black_tree#Delete_case_6
        rotate(parent, inner);
        sibling->m_color       = parent->m_color;
        parent->m_color        = BLACK;
        outer_nibling->m_color = BLACK;
    }

    //! \param node The root-node of the tree to clear.
    //!
    //! \complexity O(TreeSize).
    //!
    //! \warning `node` not being part of the `m_root` tree is undefined behavior.
    //!
    void recursive_clear(
        t_node_ptr node
    ) const
    {
        if (!node) {
            return;
        }
        recursive_clear(node->m_lchild);
        recursive_clear(node->m_rchild);
        m_alloc.destroy(node);
        m_alloc.deallocate(node, 1);
    }

    //! \param node   The root-node of the tree to clone.
    //!
    //! \param parent The parent-node of the new node.
    //!
    //! \complexity O(TreeSize).
    //!
    //! \return The root-node of the new tree.
    //!
    t_node_ptr recursive_clone(
        t_node_ptr node, t_node_ptr parent = NULL
    ) const
    {
        if (!node) {
            return NULL;
        }
        t_node_ptr new_node = m_alloc.allocate(1);

        m_alloc.construct(
            new_node,
            node(
                recursive_clone(node->m_lchild, new_node),
                recursive_clone(node->m_rchild, new_node),
                parent,
                node->m_color,
                node->m_value
            )
        );
        return new_node;
    }

    //! \brief Updates every child-node of `node` to point back to `node` as parent-node.
    //!
    //! \complexity O(1).
    //!
    void relink_children(
        t_node &node
    )
    {
        if (node.lchild) {
            node.lchild->parent = node;
        }
        if (node.rchild) {
            node.rchild->parent = node;
        }
    }

    //! \brief Rotates the `node` tree to the given `direction` + updates `m_root` if needed.
    //!        The colors are not modified.
    //!
    //! \return The new root-node of the rotated tree.
    //!
    //! \complexity O(1).
    //!
    //! \warning `node` not being part of the `m_root` tree
    //!          or having no child in the opposite `direction` is undefined behavior.
    //!
    //! \warning `direction` being neither `LE` nor `RI` is undefined behavior.
    //!
    t_node_ptr rotate(
        t_node_ptr node __attribute__((nonnull)), t_rbt_direction direction
    )
    {
        t_rbt_direction opposite   = direction == LE ? RI : LE;
        t_node_ptr      child      = node->m_children[opposite];
        t_node_ptr      grandchild = child->m_children[direction];
        t_node_ptr      parent     = node->m_parent;

        node->m_children[opposite]   = grandchild;
        node->m_parent               = child;
        child->m_parent              = parent;
        child->m_children[direction] = node;
        if (grandchild) {
            grandchild->m_parent = node;
        }
        if (parent) {
            parent->m_children[node == parent->m_lchild ? LE : RI] = child;
        }
        else {
            m_root = child;
        }
        return child;
    }

    //! \brief Swaps two adjacent nodes `parent` and `child` by adjusting their neighbor-nodes,
    //!        instead of naively swapping their inner values.
    //!        This allows to keep iterators/pointers/references valid
    //!        and to make swapping time constant regardless of the `Inner` type.
    //!
    //! \complexity O(1).
    //!
    //! \warning `parent` not being the parent-node of `child` or part of the `m_root` tree
    //!          is undefined behavior.
    //!
    //! \warning `child` not being a child-node of `parent` or part of the `m_root` tree
    //!          is undefined behavior.
    //!
    void swap_adjacent_nodes(
        t_node &parent, t_node &child
    )
    {
        t_rbt_direction direction = child == parent.m_lchild ? LE : RI;
        t_rbt_direction opposite  = direction == LE ? RI : LE;

        parent.m_parent = &child;
        // TODO
    }

    //! \brief Swaps `a` and `b` by adjusting their neighbor-nodes
    //!        instead of naively swapping their inner values.
    //!        This allows to keep iterators/pointers/references valid
    //!        and to make swapping time constant regardless of the `Inner` type.
    //!
    //! \complexity O(1).
    //!
    //! \warning `a` being `b` or not being part of the `m_root` tree is undefined behavior.
    //!
    //! \warning `b` not being part of the `m_root` tree is undefined behavior.
    //!
    void swap_nodes(
        t_node &a, t_node &b
    )
    {
        _Bool const a_is_parent_of_b = !!(b.m_parent - &a);
        _Bool const b_is_parent_of_a = !!(a.m_parent - &b);

        switch (!!(a.m_parent - &b) << 1 | !!(b.m_parent - &a)) {
        case 0 : return swap_non_adjacent_nodes(a, b);
        case 1 : return swap_adjacent_nodes(a, b);
        case 2 : return swap_adjacent_nodes(b, a);
        default: __builtin_unreachable();
        }
    }

    //! \brief Swaps two non-adjacent nodes `a` and `b` by adjusting their neighbor-nodes,
    //!        instead of naively swapping their inner values.
    //!        This allows to keep iterators/pointers/references valid
    //!        and to make swapping time constant regardless of the `Inner` type.
    //!
    //! \complexity O(1).
    //!
    //! \warning `a` being adjacent to `b` or not being part of the `m_root` tree
    //!          is undefined behavior.
    //!
    //! \warning `b` being adjacent to `a` or not being part of the `m_root` tree
    //!          is undefined behavior.
    //!
    void swap_non_adjacent_nodes(
        t_node &a, t_node &b
    )
    {
        // TODO
    }

public: /* methods */
    // ┏━━━━━━━━━━━┓
    // ┃ Iterators ┃
    // ┗━━━━━━━━━━━┛

    //! \complexity O(1).
    //!
    t_node_iterator begin() const { return t_node_iterator(m_min, m_max); }

    //! \complexity O(1).
    //!
    t_node_iterator end() const { return t_node_iterator(NULL, m_max); }

    //! \complexity O(1).
    //!
    t_node_reverse_iterator rbegin() const { return t_node_reverse_iterator(end()); }

    //! \complexity O(1).
    //!
    t_node_reverse_iterator rend() const { return t_node_reverse_iterator(begin()); }

    // ┏━━━━━━━━━━━┓
    // ┃ Observers ┃
    // ┗━━━━━━━━━━━┛

    //! \return An iterator range with every element matching the `needle`.
    //!
    //! \complexity O(log(TreeSize)).
    //!
    t_node_iterator_pair equal_range(
        t_value &needle
    ) const
    {
        if (AllowsDuplicates) {
            return make_pair(lower_bound(needle), upper_bound(needle));
        }
        t_node_iterator_pair range;

        range.first = range.second = find(needle);
        if (range.second != end()) {
            ++range.second;
        }
        return range;
    }

    //! \return An element matching the `needle` if any, `end()` otherwise.
    //!
    //! \note If multiple elements match the `needle`, only the first encountered shall be returned.
    //!       It may or may not be the first in order.
    //!
    //! \complexity O(log(TreeSize)).
    //!
    t_node_iterator find(
        t_value &needle
    ) const
    {
        t_node_ptr node = m_root;

        while (node) {
            switch (!!m_cmp(node->m_value, needle) << 1 | !!m_cmp(needle, node->m_value)) {
            case 0 : return t_node_iterator(node, m_max);
            case 1 : node = node->m_lchild; break;
            case 2 : node = node->m_rchild; break;
            default: __builtin_unreachable();
            }
        }
        return end();
    }

    // ┏━━━━━━━━━━━┓
    // ┃ Modifiers ┃
    // ┗━━━━━━━━━━━┛

    //! \brief Removes every element.
    //!
    //! \complexity O(TreeSize).
    //!
    void clear()
    {
        recursive_clear(m_root);
        m_root = NULL;
        m_min  = NULL;
        m_max  = NULL;
        m_size = 0;
    }

    //! \brief Removes the `target` element.
    //!
    //! \note Every pointer/reference/iterator referring to the removed element is invalidated.
    //!
    //! \complexity O(log(TreeSize)) amortized O(1).
    //!
    //! \warning `target` being past-the-end or not being an iterator over the caller
    //!          is undefined behavior.
    //!
    void erase(
        t_node_iterator &target
    )
    {
        if (m_size == 1) {
            m_alloc.destroy(m_root);
            m_alloc.deallocate(m_root, 1);
            m_root = NULL;
            m_min  = NULL;
            m_max  = NULL;
            m_size = 0;
            return;
        }
        t_node_ptr node      = target.m_ptr;
        t_node_ptr successor = node->m_rchild;

        // `node` has at most 2 child-nodes
        if (successor) {
            successor = successor->lmost();
            swap_nodes(node, successor);
            node = successor;
        }
        // `node` has at most 1 child-node
        successor = node->m_lchild | node->m_rchild;
        if (successor) {
            swap_nodes(node, successor);
            node = successor;
        }
        // `node` has no child-nodes
        t_node_ptr      parent    = node->m_parent;
        t_rbt_direction direction = node == parent->m_lchild ? LE : RI;

        if (node->m_color == BLACK) {
            prevent_black_violation(node, parent, direction);
        }
        parent->m_children[direction] = NULL;
        if (m_bounds[direction] == node) {
            m_bounds[direction] = parent;
        }
        m_alloc.destroy(node);
        m_alloc.deallocate(node, 1);
        --m_size;
    }

    //! \brief Removes all elements in the range [`first`,`ptend`).
    //!
    //! \note Every pointer/reference/iterator referring to the removed element·s is invalidated.
    //!
    //! \return The number of removed element·s.
    //!
    //! \complexity O(RangeSize+log(TreeSize)).
    //!
    //! \warning `first` not being an iterator over the caller is undefined behavior.
    //!
    //! \warning `ptend` being unreachable by `first` is undefined behavior.
    //!
    t_usize erase(
        t_node_iterator &first, t_node_iterator &ptend
    )
    {
        t_usize_mut count = 0;

        while (first != ptend) {
            erase(first++);
            ++count;
        }
        return count;
    }

    //! \brief Removes every element matching the `needle`.
    //!
    //! \note Every pointer/reference/iterator referring to the removed element·s is invalidated.
    //!
    //! \return The number of removed element·s.
    //!
    //! \complexity O(MatchCount+log(TreeSize)).
    //!
    t_usize erase(
        t_value &needle
    )
    {
        t_node_iterator_pair range = equal_range(needle);

        return erase(range.first, range.second);
    }

    //! \param value The value to insert.
    //!
    //! \return A pair where the `first` field points to an element equivalent to `value`
    //!         and the `second` field indicates whether the insertion took place.
    //!
    //! \complexity O(log(TreeSize)).
    //!
    pair<t_node_iterator, bool> insert(
        t_value &value
    )
    {
        if (!m_size) {
            m_root = m_alloc.allocate(1);
            m_min  = m_root;
            m_max  = m_root;
            m_size = 1;
            m_alloc.construct(m_root, t_node(NULL, NULL, NULL, BLACK, value));
            return make_pair(t_node_iterator(m_root, m_max), true);
        }
        t_rbt_direction_mut direction;
        t_node_ptr          node = m_root;
        t_node_ptr          parent;

        if (AllowsDuplicates) {
            do {
                direction = m_cmp(value, node->m_value) ? LE : RI;
                parent    = node;
                node      = node->m_children[direction];
            }
            while (node);
        }
        else {
            do {
                switch (!!m_cmp(node->m_value, value) << 1 | !!m_cmp(value, node->m_value)) {
                case 0 : return make_pair(t_node_iterator(node, m_max), false);
                case 1 : direction = LE; break;
                case 2 : direction = RI; break;
                default: __builtin_unreachable();
                }
                parent = node;
                node   = node->m_children[direction];
            }
            while (node);
        }

        node                          = m_alloc.allocate(1);
        parent->m_children[direction] = node;
        if (m_bounds[direction] == parent) {
            m_bounds[direction] = node;
        }
        ++m_size;
        m_alloc.construct(node, node(NULL, NULL, parent, RED, value));
        if (parent->m_color == RED) {
            fix_red_violation(node, parent, direction);
        }
        return make_pair(t_node_iterator(node, m_max), true);
    }

    //! \param hint  The element right before where `value` shall be inserted. (ignored if wrong)
    //!
    //! \param value The value to insert.
    //!
    //! \return The/An element equivalent to `value`.
    //!
    //! \complexity O(log(TreeSize)) amortized O(1) when `hint` is correct.
    //!
    //! \warning `hint` not being an iterator over the caller is undefined behavior.
    //!
    t_node_iterator insert(
        t_node_iterator &hint, t_value &value
    )
    {
        if (hint == end() || m_cmp(value, *hint) || (++hint != end() && m_cmp(*hint, value))) {
            return insert(value).first;
        }
        if (!AllowsDuplicates && !m_cmp(value, *hint)) {
            return hint;
        }
        --hint;
        if (!AllowsDuplicates && !m_cmp(*hint, value)) {
            return hint;
        }
        t_node_ptr          node = hint.m_ptr->m_rchild;
        t_node_ptr          parent;
        t_rbt_direction_mut direction;

        if (node) {
            parent    = node->lmost();
            direction = LE;
        }
        else {
            parent    = hint.m_ptr;
            direction = RI;
        }
        node                          = m_alloc.allocate(1);
        parent->m_children[direction] = node;
        if (m_bounds[direction] == parent) {
            m_bounds[direction] = node;
        }
        ++m_size;
        m_alloc.construct(node, node(NULL, NULL, parent, RED, value));
        if (parent->m_color == RED) {
            fix_red_violation(node, parent, direction);
        }
        return t_node_iterator(node, m_max);
    }

    //! \param first The first element of the range.
    //!
    //! \param ptend The past-the-end element of the range.
    //!
    //! \complexity O(RangeSize×log(TreeSize+RangeSize))
    //!             amortized O(RangeSize) when the range is sorted.
    //!
    //! \warning `first` being an iterator over the caller is undefined behavior.
    //!
    //! \warning `ptend` being unreachable by `first` is undefined behavior.
    //!
    template <typename InputIterator>
    void insert(
        InputIterator &first, InputIterator const &ptend
    )
    {
        if (first == ptend) {
            return;
        }
        t_node_iterator previously_inserted = insert(*first);

        while (++first != ptend) {
            previously_inserted = insert(previously_inserted, *first);
        }
    }

    //! \return The first element not less than `value` if any, `end()` otherwise.
    //!
    //! \complexity O(log(TreeSize)).
    //!
    t_node_iterator lower_bound(
        t_value &value
    ) const
    {
        t_node_ptr node           = m_root;
        t_node_ptr first_not_less = NULL;

        while (node) {
            if (m_cmp(node->m_value, value)) {
                node = node->m_rchild;
            }
            else {
                first_not_less = node;
                node           = node->m_lchild;
            }
        }
        return t_node_iterator(first_not_less, m_max);
    }

    //! \return The maximum number of elements the tree can holds at a time.
    //!
    //! \complexity O(1).
    //!
    t_usize max_size() const { return m_alloc.max_size(); }

    //! \return The first element greater than `value` if any, `end()` otherwise.
    //!
    //! \complexity O(log(TreeSize)).
    //!
    t_node_iterator upper_bound(
        t_value &value
    ) const
    {
        t_node_ptr node          = m_root;
        t_node_ptr first_greater = NULL;

        while (node) {
            if (m_cmp(value, node->m_value)) {
                first_greater = node;
                node          = node->m_lchild;
            }
            else {
                node = node->m_rchild;
            }
        }
        return t_node_iterator(first_greater, m_max);
    }

public: /* operators */
    //! \complexity O(TreeSize+log(TreeSize)) amortized O(1) when assigning itself.
    //!
    t_self &operator=(
        t_self &rhs
    )
    {
        if (this == &rhs) {
            return *this;
        }
        recursive_clear(m_root);
        m_cmp   = rhs.m_cmp;
        m_alloc = rhs.m_alloc;
        m_root  = recursive_clone(rhs.m_root);
        m_min   = m_root->lmost();
        m_max   = m_root->rmost();
        m_size  = rhs.m_size;
        return *this;
    }

    //! \complexity O(TreeSize+TreeSize×log(TreeSize)) amortized O(TreeSize).
    //!
    t_bool operator==(
        t_self &rhs
    ) const
    {
        return this == &rhs || (m_size == rhs.m_size && equal(begin(), end(), rhs.begin()));
    }

    //! \complexity O(TreeSize+TreeSize×log(TreeSize)) amortized O(TreeSize).
    //!
    t_bool operator!=(
        t_self &rhs
    ) const
    {
        // TODO: check if final binary differs between these two implementations
        // return !(*this == rhs);
        return this != &rhs && (m_size != rhs.m_size || !equal(begin(), end(), rhs.begin()));
    }

    //! \complexity O(TreeSize+TreeSize×log(TreeSize)) amortized O(TreeSize).
    //!
    t_bool operator<(
        t_self &rhs
    ) const
    {
        return lexicographical_compare(begin(), end(), rhs.begin(), rhs.end(), LT(t_value));
    }

    //! \complexity O(TreeSize+TreeSize×log(TreeSize)) amortized O(TreeSize).
    //!
    t_bool operator>(
        t_self &rhs
    ) const
    {
        // TODO: check if final binary differs between these two implementations
        // return rhs < *this;
        return lexicographical_compare(begin(), end(), rhs.begin(), rhs.end(), GT(t_value));
    }

    //! \complexity O(TreeSize+TreeSize×log(TreeSize)) amortized O(TreeSize).
    //!
    t_bool operator<=(
        t_self &rhs
    ) const
    {
        // TODO: check if final binary differs between these two implementations
        // return !(*this > rhs);
        return lexicographical_compare(begin(), end(), rhs.begin(), rhs.end(), LE(t_value));
    }

    //! \complexity O(TreeSize+TreeSize×log(TreeSize)) amortized O(TreeSize).
    //!
    t_bool operator>=(
        t_self &rhs
    ) const
    {
        // TODO: check if final binary differs between these two implementations
        // return !(*this < rhs);
        return lexicographical_compare(begin(), end(), rhs.begin(), rhs.end(), GE(t_value));
    }

#undef SELF
};

} // namespace ft

#endif
