#ifndef SET_HPP
#define SET_HPP

#include "functional.hpp" // ft::less
#include "memory.hpp" // ft::allocator
#include "red_black_tree.hpp" // ft::red_black_tree
#include "type/fundamentals.hpp" // ft::t_bool
#include "type_traits.hpp" // ft::{enable_if,is_same}
#include "utility.hpp" // ft::pair
#include <cstring>

namespace ft {

template <typename Key, typename Compare = less<Key>, typename Allocator = allocator<Key> >
class set
{
#define SELF set
private: /* types */
    typedef SELF const                                     t_self;
    typedef SELF                                           t_self_mut;
    typedef red_black_tree<false, Key, Compare, Allocator> t_tree;
    typedef typename t_tree::t_node_iterator               t_node_iterator;

public: /* types */
    // ┏━━━━━━━━━━━━━━━━━━━━━━━━┓
    // ┃ Container requirements ┃
    // ┗━━━━━━━━━━━━━━━━━━━━━━━━┛
    typedef Key                                  value_type;
    typedef typename Allocator::reference        reference;
    typedef typename Allocator::const_reference  const_reference;
    typedef typename t_tree::t_node_mut_iterator iterator;
    typedef typename t_tree::t_node_iterator     const_iterator;
    typedef typename enable_if<
        (is_same<typename iterator::difference_type, typename const_iterator::difference_type>()),
        typename iterator::difference_type
    >::type                                               difference_type;
    typedef typename make_unsigned<difference_type>::type size_type;

    // ┏━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┓
    // ┃ Reversible container requirements ┃
    // ┗━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┛
    typedef typename t_tree::t_node_mut_reverse_iterator reverse_iterator;
    typedef typename t_tree::t_node_reverse_iterator     const_reverse_iterator;

    // ┏━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┓
    // ┃ Associative container requirements ┃
    // ┗━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┛
    typedef Key     key_type;
    typedef Compare key_compare;
    typedef Compare value_compare;

    // ┏━━━━━━━━━━━━━━━━━━━━━━━━━━━┓
    // ┃ Set specific requirements ┃
    // ┗━━━━━━━━━━━━━━━━━━━━━━━━━━━┛
    typedef typename Allocator::pointer       pointer;
    typedef typename Allocator::const_pointer const_pointer;
    typedef Allocator                         allocator_type;

private: /* fields */
    t_tree m_tree;

public: /* constructors */
    // ┏━━━━━━━━━━━━━━━━━━━━━━━━┓
    // ┃ Container requirements ┃
    // ┗━━━━━━━━━━━━━━━━━━━━━━━━┛

    //! \complexity O(SetSize+log(SetSize)).
    //!
    SELF(
        t_self &other
    )
    : m_tree(other.m_tree)
    {}

    // ┏━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┓
    // ┃ Associative container requirements ┃
    // ┗━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┛

    //! \complexity O(1).
    //!
    SELF(
        key_compare const &cmp = Compare()
    )
    : m_tree(cmp)
    {}

    //! \complexity O(RangeSize×log(RangeSize)) amortized O(RangeSize) when the range is sorted.
    //!
    //! \warning `ptend` being unreachable by `first` is undefined behavior.
    //!
    template <typename InputIterator>
    SELF(
        InputIterator first, InputIterator const ptend, key_compare const &cmp = Compare()
    )
    : m_tree(first, ptend, cmp)
    {}

    // ┏━━━━━━━━━━━━━━━━━━━━━━━━━━━┓
    // ┃ Set specific requirements ┃
    // ┗━━━━━━━━━━━━━━━━━━━━━━━━━━━┛

    //! \complexity O(1).
    //
    explicit SELF(
        Compare const &cmp, Allocator const &
    )
    : m_tree(cmp)
    {}

    //! \complexity O(RangeSize×log(RangeSize)) amortized O(RangeSize) when the range is sorted.
    //!
    //! \warning `ptend` being unreachable by `first` is undefined behavior.
    //!
    template <typename InputIterator>
    SELF(
        InputIterator first, InputIterator const ptend, Compare const &cmp, Allocator const &
    )
    : m_tree(first, ptend, cmp)
    {}

public: /* destructor */
    // ┏━━━━━━━━━━━━━━━━━━━━━━━━┓
    // ┃ Container requirements ┃
    // ┗━━━━━━━━━━━━━━━━━━━━━━━━┛

    //! \complexity O(SetSize).
    //!
    ~SELF() {};

public: /* methods */
    // ┏━━━━━━━━━━━━━━━━━━━━━━━━┓
    // ┃ Container requirements ┃
    // ┗━━━━━━━━━━━━━━━━━━━━━━━━┛

    //! \complexity O(1).
    //!
    iterator begin() { return m_tree.begin(); }

    //! \complexity O(1).
    //!
    const_iterator begin() const { return m_tree.begin(); }

    //! \complexity O(1).
    //!
    iterator end() { return m_tree.end(); }

    //! \complexity O(1).
    //!
    const_iterator end() const { return m_tree.end(); }

    //! \complexity O(1).
    //!
    void swap(
        t_self_mut &other
    )
    {
        swap(*this, other);
    }

    //! \complexity O(1).
    //!
    size_type size() const { return m_tree.size(); }

    //! \complexity O(1).
    //!
    size_type max_size() const { return m_tree.max_size(); }

    //! \complexity O(1).
    //!
    bool empty() const { return !m_tree.size(); }

    // ┏━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┓
    // ┃ Reversible container requirements ┃
    // ┗━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┛

    //! \complexity O(1).
    //!
    reverse_iterator rbegin() { return m_tree.rbegin(); }

    //! \complexity O(1).
    //!
    const_reverse_iterator rbegin() const { return m_tree.rbegin(); }

    //! \complexity O(1).
    //!
    reverse_iterator rend() { return m_tree.rend(); }

    //! \complexity O(1).
    //!
    const_reverse_iterator rend() const { return m_tree.rend(); }

    // ┏━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┓
    // ┃ Associative container requirements ┃
    // ┗━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┛

    //! \return The inner key comparison function object.
    //!
    //! \complexity O(1).
    //!
    key_compare key_comp() const { return m_tree.cmp(); }

    //! \return The inner value comparison function object.
    //!
    //! \complexity O(1).
    //!
    value_compare value_comp() const { return m_tree.cmp(); }

    //! \brief Inserts the `value` element if not already present.
    //!
    //! \return A pair where the `first` field points to the element equivalent to `value`
    //!         and the `second` field indicates whether the insertion took place.
    //!
    //! \complexity O(log(SetSize)).
    //!
    pair<iterator, bool> insert(
        value_type const &value
    )
    {
        return m_tree.insert(value);
    }

    //! \brief Inserts the `value` element if not already present,
    //!        using a `hint` to possibly speed up the insertion.
    //!
    //! \param hint The element right before where `value` shall be inserted. (ignored if wrong)
    //!
    //! \return The element equivalent to `value`.
    //!
    //! \complexity O(log(SetSize)) amortized O(1) when `hint` is correct.
    //!
    //! \warning `hint` not being an iterator over the caller is undefined behavior.
    //!
    iterator insert(
        iterator hint, value_type const &value
    )
    {
        return m_tree.insert(hint, value);
    }

    //! \complexity O(RangeSize×log(SetSize+RangeSize))
    //!             amortized O(RangeSize) when the range is sorted.
    //!
    //! \warning `first` being an iterator over the caller is undefined behavior.
    //!
    //! \warning `ptend` being unreachable by `first` is undefined behavior.
    //!
    template <typename InputIterator>
    void insert(
        InputIterator first, InputIterator const ptend
    )
    {
        m_tree.insert(first, ptend);
    }

    //! \brief Removes the element matching the `needle` if any.
    //!
    //! \note Every pointer/reference/iterator referring to the removed element is invalidated.
    //!
    //! \return 1 if the erasure took place, 0 otherwise.
    //!
    //! \complexity O(log(SetSize)).
    //!
    size_type erase(
        key_type const &needle
    )
    {
        return m_tree.erase(needle);
    }

    //! \brief Removes the `target` element.
    //!
    //! \note Every pointer/reference/iterator referring to the removed element is invalidated.
    //!
    //! \complexity O(log(SetSize)) amortized O(1).
    //!
    //! \warning `target` being past-the-end or not being an iterator over the caller
    //!          is undefined behavior.
    //!
    void erase(
        iterator target
    )
    {
        m_tree.erase(target);
    }

    //! \brief Removes elements in the range [`first`,`ptend`).
    //!
    //! \note Every pointer/reference/iterator referring to the removed element·s is invalidated.
    //!
    //! \complexity O(RangeSize+log(TreeSize)).
    //!
    //! \warning `first` not being an interator over the caller is undefined behavior.
    //!
    //! \warning `ptend` being unreachable by `first` is undefined behavior.
    //!
    void erase(
        iterator first, iterator const ptend
    )
    {
        m_tree.erase(first, ptend);
    }

    //! \complexity O(SetSize).
    //!
    void clear() { m_tree.clear(); }

    //! \return An element matching `needle` if any, `end()` otherwise.
    //!
    //! \complexity O(log(SetSize)).
    //!
    iterator find(
        key_type const &needle
    ) const
    {
        return m_tree.find(needle);
    }

    //! \return 0 if `needle` matches no element, 1 otherwise.
    //!
    //! \complexity O(log(SetSize)).
    //!
    size_type count(
        key_type const &needle
    ) const
    {
        return find(needle) == end() ? 0 : 1;
    }

    //! \return The first element not less than `value` if any, `end()` otherwise.
    //!
    //! \complexity O(log(SetSize)).
    //!
    iterator lower_bound(
        key_type const &value
    ) const
    {
        return m_tree.lower_bound(value);
    }

    //! \return The first element greater than `value` if any, `end()` otherwise.
    //!
    //! \complexity O(log(TreeSize)).
    //!
    iterator upper_bound(
        key_type const &value
    ) const
    {
        return m_tree.upper_bound(value);
    }

    //! \return An iterator range with every element matching `needle`.
    //!
    //! \complexity O(log(TreeSize)).
    //!
    pair<iterator, iterator> equal_range(
        key_type const &needle
    ) const
    {
        return m_tree.equal_range(needle);
    }

public: /* operators */
    // ┏━━━━━━━━━━━━━━━━━━━━━━━━┓
    // ┃ Container requirements ┃
    // ┗━━━━━━━━━━━━━━━━━━━━━━━━┛

    //! \complexity O(SetSize+log(SetSize)) amortized O(1) when assigning itself.
    //!
    t_self_mut &operator=(
        t_self &rhs
    )
    {
        m_tree = rhs.m_tree;
        return *this;
    }

#undef SELF
};

// ┏━━━━━━━━━━━━━━━━━━━━━━━━━━━┓
// ┃ Set specific requirements ┃
// ┗━━━━━━━━━━━━━━━━━━━━━━━━━━━┛

//! \complexity O(SetSize+SetSize×log(SetSize)) amortized O(SetSize).
//!
template <typename Key, typename Compare, typename Allocator>
inline bool operator==(
    set<Key, Compare, Allocator> const &lhs, set<Key, Compare, Allocator> const &rhs
)
{
    return lhs.m_tree == rhs.m_tree;
}

//! \complexity O(SetSize+SetSize×log(SetSize)) amortized O(SetSize).
//!
template <typename Key, typename Compare, typename Allocator>
inline bool operator!=(
    set<Key, Compare, Allocator> const &lhs, set<Key, Compare, Allocator> const &rhs
)
{
    return lhs.m_tree != rhs.m_tree;
}

//! \complexity O(SetSize+SetSize×log(SetSize)) amortized O(SetSize).
//!
template <typename Key, typename Compare, typename Allocator>
inline bool operator<(
    set<Key, Compare, Allocator> const &lhs, set<Key, Compare, Allocator> const &rhs
)
{
    return lhs.m_tree < rhs.m_tree;
}

//! \complexity O(SetSize+SetSize×log(SetSize)) amortized O(SetSize).
//!
template <typename Key, typename Compare, typename Allocator>
inline bool operator>(
    set<Key, Compare, Allocator> const &lhs, set<Key, Compare, Allocator> const &rhs
)
{
    return lhs.m_tree > rhs.m_tree;
}

//! \complexity O(SetSize+SetSize×log(SetSize)) amortized O(SetSize).
//!
template <typename Key, typename Compare, typename Allocator>
inline bool operator<=(
    set<Key, Compare, Allocator> const &lhs, set<Key, Compare, Allocator> const &rhs
)
{
    return lhs.m_tree <= rhs.m_tree;
}

//! \complexity O(SetSize+SetSize×log(SetSize)) amortized O(SetSize).
//!
template <typename Key, typename Compare, typename Allocator>
inline bool operator>=(
    set<Key, Compare, Allocator> const &lhs, set<Key, Compare, Allocator> const &rhs
)
{
    return lhs.m_tree >= rhs.m_tree;
}

#define T set<Key, Compare, Allocator>

template <typename Key, typename Compare, typename Allocator>
inline void swap(
    T &a, T &b
)
{
    t_u8 c[sizeof(T)];

    memcpy(&c, &a, sizeof(T));
    memcpy(&a, &b, sizeof(T));
    memcpy(&b, &c, sizeof(T));
}

#undef T

} // namespace ft

#endif
