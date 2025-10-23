#ifndef RED_BLACK_TREE_HPP
#define RED_BLACK_TREE_HPP

#include "algorithm.hpp" // ft::{equal,lexicographical_compare,swap}
#include "functional.hpp" // ft::less
#include "iterator.hpp" // ft::{bidirectional_iterator_tag,reverse_iterator}
#include "memory.hpp" // ft::allocator
#include "type/fundamentals.hpp" // ft::t_{i,u}size
#include "utility.hpp" // ft::pair

namespace ft {

enum rbt_color { RED, BLACK };

typedef rbt_color const t_rbt_color;

enum rbt_direction {
    LE, // Left
    RI, // Right
    DIRECTION_COUNT
};

typedef rbt_direction const t_rbt_direction;
typedef rbt_direction       t_rbt_direction_mut;

template <typename Inner>
class rbt_node
{
#define SELF rbt_node

private: // types
    typedef SELF const    t_self;
    typedef t_self *const t_self_ptr;
    typedef Inner const   t_inner;

    // TODO: remove unused typedefs when all tests pass

private: // fields
    // Allows both (`node->m_lson`|`node->m_rson`) and
    // (`node->m_sons[LE]`|`node->m_sons[RI]`)
    union
    {
        struct {
            t_self_ptr m_lson;
            t_self_ptr m_rson;
        };

        t_self_ptr m_sons[DIRECTION_COUNT];
    };

    t_self_ptr  m_father;
    t_rbt_color m_color;
    t_inner     m_inner;

public: // constructors
    //! \complexity O(1).
    //!
    SELF(
        t_self_ptr lson, t_self_ptr rson, t_self_ptr father, t_rbt_color color, t_inner &inner
    )
    : m_lson(lson), m_rson(rson), m_father(father), m_color(color), m_inner(inner)
    {}

public: // methods
    //! \return The leftmost node from the caller.
    //!
    //! \complexity O(NodesBeforeLmost).
    //!
    t_self_ptr lmost() const
    {
        t_self_ptr node = this;

        while (node->m_lson) {
            node = node->m_lson;
        }
        return node;
    }

    //! \return The rightmost node from the caller.
    //!
    //! \complexity O(NodesBeforeRmost).
    //!
    t_self_ptr rmost() const
    {
        t_self_ptr node = this;

        while (node->m_rson) {
            node = node->m_rson;
        }
        return node;
    }

#undef SELF
};

template <typename Node>
class rbt_iterator
{
#define SELF rbt_iterator

private: // types
    typedef SELF const        t_self;
    typedef Node const        t_node;
    typedef t_node *const     t_node_ptr;
    typedef t_node_ptr *const t_node_ptr_ptr;

public: // types
    typedef bidirectional_iterator_tag    iterator_category;
    typedef t_isize                       difference_type;
    typedef typename Node::t_inner        value_type;
    typedef typename Node::t_inner       &reference;
    typedef typename Node::t_inner *const pointer;

private: // fields
    t_node_ptr     m_ptr;
    t_node_ptr_ptr m_max;

public: // constructors
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

public: // operators
    //! \complexity O(1).
    //!
    bool operator==(
        t_self &rhs
    )
    {
        return m_ptr == rhs.m_ptr;
    }

    //! \complexity O(1).
    //!
    bool operator!=(
        t_self &rhs
    )
    {
        return m_ptr != rhs.m_ptr;
    }

    //! \complexity O(1).
    //!
    reference operator*() const { return m_ptr->m_inner; }

    //! \complexity O(1).
    //!
    pointer operator->() const { return &m_ptr->m_inner; }

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
    t_self &operator++()
    {
        if (m_ptr->m_rson) {
            m_ptr = m_ptr->m_rson->lmost();
            return *this;
        }
        t_node_ptr father = m_ptr->m_father;

        while (father && m_ptr == father->m_rson) {
            m_ptr  = father;
            father = m_ptr->m_father;
        }
        m_ptr = father;
        return *this;
    }

    //! \complexity O(log(TreeSize)) amortized O(1).
    //!
    //! \warning Caller being past-the-end is undefined behavior.
    //!
    t_self operator++(
        int
    )
    {
        t_self before_move(*this);

        ++*this;
        return before_move;
    }

    //! \complexity O(log(TreeSize)) amortized O(1).
    //!
    //! \warning Caller pointing to the first element or an empty tree is undefined behavior.
    //!
    t_self &operator--()
    {
        if (!m_ptr) {
            m_ptr = *m_max;
            return *this;
        }
        if (m_ptr->m_lson) {
            m_ptr = m_ptr->m_lson->rmost();
            return *this;
        }
        t_node_ptr father = m_ptr->m_father;

        while (father && m_ptr == father->m_lson) {
            m_ptr  = father;
            father = m_ptr->m_father;
        }
        m_ptr = father;
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
        t_self before_move(*this);

        --*this;
        return before_move;
    }

#undef SELF
};

//! A Red Black Tree is a self-balancing Binary Search Tree (BST)
//! which is ruled by the following properties:
//!  1. Every node is either red or black
//!  2. All NULL nodes are considered black
//!  3. A red node does not have a red child
//!  4. Every path from a node to any of its descendant NULL nodes
//!     goes through the same number of black nodes
//!
//! In this implementation:
//!  - a violation of the 3rd property is called a "red violation"
//!  - a violation of the 4th property is called a "black violation"
template <
    t_bool AllowsDuplicates,
    typename Inner,
    typename Compare   = less<Inner>,
    typename Allocator = allocator<rbt_node<Inner> >
>
class red_black_tree
{
#define SELF red_black_tree

private: /* types */
    typedef SELF const                                   t_self;
    typedef SELF                                         t_self_mut;
    typedef Inner const                                  t_inner;
    typedef Inner                                        t_inner_mut;
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
    //! \param father         The parent-node of `node`.
    //!
    //! \param node_direction Whether `node` is the right or left son of `father`.
    //!
    //! \complexity O(log(TreeSize)) amortized O(1).
    //!
    //! \warning `node` not being a red leaf of the `m_root` tree or a `father`'s son
    //!          is undefined behavior.
    //!
    //! \warning `father` not being the `node`'s father or being black is undefined behavior.
    //!
    //! \warning `node_direction` not being such as `father->sons[node_direction] == node`
    //!          is undefined behavior.
    //!
    void fix_red_violation(
        t_node_ptr node, t_node_ptr father, t_rbt_direction_mut node_direction
    ) __attribute__((nonnull))
    {
        do {
            t_node_ptr grandfather = father->m_father;

            if (!grandfather) {
                // https://en.wikipedia.org/wiki/Red-black_tree#Insert_case_4
                father->m_color = BLACK;
                return;
            }
            t_rbt_direction uncle_direction = father == grandfather->m_lson ? RI : LE;
            t_node_ptr      uncle           = grandfather->m_sons[uncle_direction];

            if (!uncle || uncle->m_color == BLACK) {
                if (node_direction == uncle_direction) {
                    // https://en.wikipedia.org/wiki/Red-black_tree#Insert_case_5
                    node_direction = node_direction == LE ? RI : LE;
                    father         = rotate(father, node_direction);
                    node           = father->sons[node_direction];
                }
                // https://en.wikipedia.org/wiki/Red-black_tree#Insert_case_6
                rotate(grandfather, uncle_direction)->m_color;
                father->m_color      = BLACK;
                grandfather->m_color = RED;
                return;
            }
            // https://en.wikipedia.org/wiki/Red-black_tree#Insert_case_2
            father->m_color      = BLACK;
            grandfather->m_color = RED;
            uncle->m_color       = BLACK;
            node                 = grandfather;
            father               = node->father;
            node_direction       = node == father->m_lson ? LE : RI;
        }
        while (father && father->m_color == RED);
        // https://en.wikipedia.org/wiki/Red-black_tree#Insert_case_1
        // https://en.wikipedia.org/wiki/Red-black_tree#Insert_case_3
    }

    //! \brief Balances/Recolors the `m_root` tree before the removal of a black leaf-node.
    //!
    //! \param node   The node to remove.
    //!
    //! \param father The `node`'s father.
    //!
    //! \param inner  Whether `node` is the right or left son of `father`.
    //!
    //! \complexity O(log(TreeSize)) amortized O(1).
    //!
    //! \warning `node` being `NULL` or not being a `father`'s son is undefined behavior.
    //!
    //! \warning `father` not being the `node`'s father is undefined behavior.
    //!
    //! \warning `inner` not being such as `father->sons[inner] == node` is undefined behavior.
    //!
    void prevent_black_violation(
        t_node_ptr node, t_node_ptr father, t_rbt_direction inner
    )
    {
        t_rbt_direction_mut outer;
        t_node_ptr          brother;
        t_node_ptr          inner_nephew;
        t_node_ptr          outer_nephew;

        do {
            outer        = inner == LE ? RI : LE;
            brother      = father->m_sons[outer];
            inner_nephew = brother->m_sons[inner];
            outer_nephew = brother->m_sons[outer];

            if (brother->m_color == RED) {
                // https://en.wikipedia.org/wiki/Red-black_tree#Delete_case_3
                rotate(father, inner);
                father->m_color  = RED;
                brother->m_color = BLACK;
                brother          = inner_nephew;
                outer_nephew     = brother->m_sons[outer];
                if (outer_nephew->m_color == RED) {
                    goto D6;
                }
                inner_nephew = brother->m_sons[inner];
                if (inner_nephew->m_color == RED) {
                    goto D5;
                }
                // https://en.wikipedia.org/wiki/Red-black_tree#Delete_case_4
                father->m_color  = BLACK;
                brother->m_color = RED;
                return;
            }
            if (outer_nephew->m_color == RED) {
                goto D6;
            }
            if (inner_nephew->m_color == RED) {
                goto D5;
            }
            if (father->m_color == RED) {
                // https://en.wikipedia.org/wiki/Red-black_tree#Delete_case_4
                father->m_color  = BLACK;
                brother->m_color = RED;
                return;
            }
            if (!father) {
                // https://en.wikipedia.org/wiki/Red-black_tree#Delete_case_1
                return;
            }
            // https://en.wikipedia.org/wiki/Red-black_tree#Delete_case_2
            brother->m_color = RED;
            node             = father;
            father           = node->m_father;
            inner            = node == father->m_lson ? LE : RI;
        }
        while (father);
    D5: // https://en.wikipedia.org/wiki/Red-black_tree#Delete_case_5
        rotate(brother, outer);
        brother->m_color      = RED;
        inner_nephew->m_color = BLACK;
        outer_nephew          = brother;
        brother               = inner_nephew;
    D6: // https://en.wikipedia.org/wiki/Red-black_tree#Delete_case_6
        rotate(father, inner);
        brother->m_color      = father->m_color;
        father->m_color       = BLACK;
        outer_nephew->m_color = BLACK;
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
        recursive_clear(node->m_lson);
        recursive_clear(node->m_rson);
        m_alloc.destroy(node);
        m_alloc.deallocate(node, 1);
    }

    //! \param node   The root-node of the tree to clone.
    //!
    //! \param father The parent-node of the new node.
    //!
    //! \complexity O(TreeSize).
    //!
    //! \return The root-node of the new tree.
    //!
    t_node_ptr recursive_clone(
        t_node_ptr node, t_node_ptr father = NULL
    ) const
    {
        if (!node) {
            return NULL;
        }
        t_node_ptr new_node = m_alloc.allocate(1);

        m_alloc.construct(
            new_node,
            node(
                recursive_clone(node->m_lson, new_node),
                recursive_clone(node->m_rson, new_node),
                father,
                node->m_color,
                node->m_inner
            )
        );
        return new_node;
    }

    //! \brief Rotates the `node` tree to the given `direction` + updates `m_root` if needed.
    //!        The colors are not modified.
    //!
    //! \return The new root-node of the rotated tree.
    //!
    //! \complexity O(1).
    //!
    //! \warning `node` being `NULL` or not being part of the `m_root` tree
    //!          or having no son in the opposite `direction` is undefined behavior.
    //!
    //! \warning `direction` being neither `LE` nor `RI` is undefined behavior.
    //!
    t_node_ptr rotate(
        t_node_ptr node, t_rbt_direction direction
    ) __attribute__((nonnull))
    {
        t_rbt_direction opposite = direction == LE ? RI : LE;
        t_node_ptr      son      = node->m_sons[opposite];
        t_node_ptr      grandson = son->m_sons[direction];
        t_node_ptr      father   = node->m_father;

        node->m_sons[opposite] = grandson;
        node->m_father         = son;
        son->m_father          = father;
        son->m_sons[direction] = node;
        if (grandson) {
            grandson->m_father = node;
        }
        if (father) {
            father->m_sons[node == father->m_lson ? LE : RI] = son;
        }
        else {
            m_root = son;
        }
        return son;
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
        t_inner &needle
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
    //!       Remember that the first encountered does not mean the first in order.
    //!
    //! \complexity O(log(TreeSize)).
    //!
    t_node_iterator find(
        t_inner &needle
    ) const
    {
        t_node_ptr node = m_root;

        while (node) {
            if (m_cmp(needle, node->m_inner)) {
                node = node->m_lson;
            }
            else if (m_cmp(node->m_inner, needle)) {
                node = node->m_rson;
            }
            else {
                break;
            }
        }
        return t_node_iterator(node, m_max);
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
        t_node_ptr successor = node->m_rson;

        // `node` has at most 2 child-nodes
        if (successor) {
            successor = successor->lmost();
            swap(node->m_inner, successor->m_inner);
            node = successor;
        }
        // `node` has at most 1 child-node
        successor = node->m_lson | node->m_rson;
        if (successor) {
            swap(node->m_inner, successor->m_inner);
            node = successor;
        }
        // `node` has no child-nodes
        t_node_ptr      father    = node->m_father;
        t_rbt_direction direction = node == father->m_lson ? LE : RI;

        if (node->m_color == BLACK) {
            prevent_black_violation(node, father, direction);
        }
        father->m_sons[direction] = NULL;
        if (m_bounds[direction] == node) {
            m_bounds[direction] = father;
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
        t_inner &needle
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
        t_inner &value
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
        t_node_ptr          father;

        if (AllowsDuplicates) {
            do {
                direction = m_cmp(value, node->m_inner) ? LE : RI;
                father    = node;
                node      = node->m_sons[direction];
            }
            while (node);
        }
        else {
            do {
                switch (!!m_cmp(value, node->m_inner) | !!m_cmp(node->m_inner, value) << 1) {
                case 0 : return make_pair(t_node_iterator(node, m_max), false);
                case 1 : direction = LE; break;
                case 2 : direction = RI; break;
                default: __builtin_unreachable();
                }
                father = node;
                node   = node->m_sons[direction];
            }
            while (node);
        }

        node                      = m_alloc.allocate(1);
        father->m_sons[direction] = node;
        if (m_bounds[direction] == father) {
            m_bounds[direction] = node;
        }
        ++m_size;
        m_alloc.construct(node, node(NULL, NULL, father, RED, value));
        if (father->m_color == RED) {
            fix_red_violation(node, father, direction);
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
        t_node_iterator &hint, t_inner &value
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
        t_node_ptr          node = hint.m_ptr->m_rson;
        t_node_ptr          father;
        t_rbt_direction_mut direction;

        if (node) {
            father    = node->lmost();
            direction = LE;
        }
        else {
            father    = hint.m_ptr;
            direction = RI;
        }
        node                      = m_alloc.allocate(1);
        father->m_sons[direction] = node;
        if (m_bounds[direction] == father) {
            m_bounds[direction] = node;
        }
        ++m_size;
        m_alloc.construct(node, node(NULL, NULL, father, RED, value));
        if (father->m_color == RED) {
            fix_red_violation(node, father, direction);
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
        t_inner &value
    ) const
    {
        t_node_ptr node           = m_root;
        t_node_ptr first_not_less = NULL;

        while (node) {
            if (m_cmp(node->m_inner, value)) {
                node = node->m_rson;
            }
            else {
                first_not_less = node;
                node           = node->m_lson;
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
        t_inner &value
    ) const
    {
        t_node_ptr node          = m_root;
        t_node_ptr first_greater = NULL;

        while (node) {
            if (m_cmp(value, node->m_inner)) {
                first_greater = node;
                node          = node->m_lson;
            }
            else {
                node = node->m_rson;
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
        return lexicographical_compare(begin(), end(), rhs.begin(), rhs.end(), LT(t_inner));
    }

    //! \complexity O(TreeSize+TreeSize×log(TreeSize)) amortized O(TreeSize).
    //!
    t_bool operator>(
        t_self &rhs
    ) const
    {
        // TODO: check if final binary differs between these two implementations
        // return rhs < *this;
        return lexicographical_compare(begin(), end(), rhs.begin(), rhs.end(), GT(t_inner));
    }

    //! \complexity O(TreeSize+TreeSize×log(TreeSize)) amortized O(TreeSize).
    //!
    t_bool operator<=(
        t_self &rhs
    ) const
    {
        // TODO: check if final binary differs between these two implementations
        // return !(*this > rhs);
        return lexicographical_compare(begin(), end(), rhs.begin(), rhs.end(), LE(t_inner));
    }

    //! \complexity O(TreeSize+TreeSize×log(TreeSize)) amortized O(TreeSize).
    //!
    t_bool operator>=(
        t_self &rhs
    ) const
    {
        // TODO: check if final binary differs between these two implementations
        // return !(*this < rhs);
        return lexicographical_compare(begin(), end(), rhs.begin(), rhs.end(), GE(t_inner));
    }

#undef SELF
};

} // namespace ft

#endif
