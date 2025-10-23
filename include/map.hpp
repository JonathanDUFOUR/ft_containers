#ifndef MAP_HPP
#define MAP_HPP

#include "functional.hpp" // ft::{binary_function,less}
#include "red_black_tree.hpp" // ft::red_black_tree
#include "utility.hpp" // ft::pair

namespace ft {

template <
    typename Key,
    typename T,
    typename Compare   = less<Key>,
    typename Allocator = std::allocator<pair<Key const, T> >
>
class map
{
public: // types
        // value_type      : T
        // reference       : lvalue of T
        // const_reference : const lvalue of T
        // iterator        : iterator type pointing to T
        // const_iterator  : iterator type pointing to const T
        // difference_type : {,const_}iterator::difference_type
        // size_type       : make_unsigned<difference_type>::type
        //
        // reverse_iterator       : reverse_iterator<iterator>
        // const_reverse_iterator : reverse_iterator<const_iterator>
        //
        // key_type      : Key
        // key_compare   : Compare
        // value_compare : container dependent
private:
    typedef red_black_tree<
        pair<Key const, T>,
        Compare,
        typename Allocator::template rebind<rbt_node<pair<Key const, T> > >::other
    >
        tree_type;

public:
    typedef Key                                                 key_type;
    typedef T                                                   mapped_type;
    typedef pair<Key const, T>                                  value_type;
    typedef Compare                                             key_compare;
    typedef Allocator                                           allocator_type;
    typedef typename Allocator::const_reference                 const_reference;
    typedef typename Allocator::reference                       reference;
    typedef typename Allocator::const_pointer                   const_pointer;
    typedef typename Allocator::pointer                         pointer;
    typedef typename tree_type::t_node_iterator_mut             const_iterator;
    typedef typename tree_type::t_node_mut_iterator_mut         iterator;
    typedef typename tree_type::t_node_reverse_iterator_mut     const_reverse_iterator;
    typedef typename tree_type::t_node_mut_reverse_iterator_mut reverse_iterator;
    typedef typename tree_type::t_difference_mut                difference_type;
    typedef typename tree_type::t_size_mut                      size_type;

    class value_compare : public binary_function<value_type, value_type, bool>
    {
        friend class map;

    protected:
        key_compare m_predicate;

        // ┏━━━━━━━━━━━━━━┓
        // ┃ Constructors ┃
        // ┗━━━━━━━━━━━━━━┛

        // ┏━━━━━━━━━━━┓
        // ┃ Operators ┃
        // ┗━━━━━━━━━━━┛
    };

public:
    // ┏━━━━━━━━━━━━━━┓
    // ┃ Constructors ┃
    // ┗━━━━━━━━━━━━━━┛

    /**
     * @brief Default constructor.
     */
    PairComparator(
        KeyComparator const &cmp = KeyComparator()
    )
    : m_cmp(cmp)

    {}

    // ┏━━━━━━━━━━━┓
    // ┃ Operators ┃
    // ┗━━━━━━━━━━━┛

    bool operator()(
        Pair const &lhs, Pair const &rhs
    ) const
    {
        return m_cmp(lhs.first, rhs.first);
    }

}; // class PairComparator

private:
RedBlackTree<Pair, PairComparator, NodeAllocator> m_inner;

public:
// ┏━━━━━━━━━━━━━━┓
// ┃ Constructors ┃
// ┗━━━━━━━━━━━━━━┛

/**
 * @brief Default constructor.
 */
explicit Map(
    KeyComparator const &cmp = KeyComparator(), Allocator const &alloc = Allocator()
)
: m_inner(PairComparator(cmp), alloc)
{}

/**
 * @brief Range constructor.
 *
 * @tparam InputIterator The iterator type of the range.
 *                       (must conform to the input iterator requirements)
 *
 * @param begin The first element of the range.
 * @param end The post-last element of the range.
 */
template <typename InputIterator>
Map(
    InputIterator const &begin,
    InputIterator const &end,
    KeyComparator const &cmp   = KeyComparator(),
    Allocator const     &alloc = Allocator()
)
: m_inner(begin, end, PairComparator(cmp), alloc)
{}

/**
 * @brief Copy constructor.
 *
 * @param other The map to copy.
 */
Map(
    Map const &other
)
: m_inner(other.m_inner)
{}

// ┏━━━━━━━━━━━━┓
// ┃ Destructor ┃
// ┗━━━━━━━━━━━━┛

~Map() { m_inner.clear(); }

// ┏━━━━━━━━━┓
// ┃ Methods ┃
// ┗━━━━━━━━━┛

/**
 * @return An iterator to the first element of the map.
 */
Iterator begin() { return m_inner.begin(); }

/**
 * @return An iterator to the first element of the map.
 */
ConstIterator begin() const { return m_inner.begin(); }

/**
 * @brief Removes every element from the Map.
 */
void clear() { m_inner.clear(); }

/**
 * @return The number of elements matching the `key`.
 */
Size count(
    Key const &key
) const
{
    if (m_inner.find(Pair(key, MappedElement())) != m_inner.nil()) {
        return 1;
    }
    return 0;
}

/**
 * @return `true` if the map is empty, `false` otherwise.
 */
bool empty() const { return m_inner.size() == 0; }

/**
 * @return An iterator to the post-last element of the map.
 */
Iterator end() { return m_inner.end(); }

/**
 * @return An iterator to the post-last element of the map.
 */
ConstIterator end() const { return m_inner.end(); }

/**
 * @return An iterator range with every element matching the `key`.
 */
Pair<Iterator, Iterator> equal_range(
    Key const &key
)
{
    return m_inner.equal_range(Pair(key, MappedElement()));
}

/**
 * @return An iterator range with every element matching the `key`.
 */
Pair<ConstIterator, ConstIterator> equal_range(
    Key const &key
) const
{
    return m_inner.equal_range(Pair(key, MappedElement()));
}

/**
 * @brief Removes the single `target` element.
 */
void erase(
    Iterator const &target
)
{
    m_inner.erase(target);
}

/**
 * @brief Removes the single element matching the `needle` key if it exists.
 *
 * @return 1 if the element with the `needle` key
 *         has been found and removed, 0 otherwise.
 */
Size erase(
    Key const &needle
)
{
    return m_inner.erase(Pair(needle, MappedElement()));
}

/**
 * @brief Removes all elements in the range [`begin`, `end`).
 */
void erase(
    Iterator const &begin, Iterator const &end
)
{
    m_inner.erase(begin, end);
}

/**
 * @return The single element matching the `key` if it exists,
 *         `end()` otherwise.
 */
Iterator find(
    Key const &key
)
{
    return m_inner.find(Pair(key, MappedElement()));
}

/**
 * @brief	Search for a constant element in the Map.
 *
 * @param	key The key of the constant element to search.
 *
 * @return	A ConstIterator to the constant element if found, or end() if
 * not.
 */
ConstIterator find(
    Key const &key
) const
{
    return ConstIterator(m_inner.find(Pair(key, MappedElement())));
}

/**
 * @brief	Insert elements in the Map using a range of iterators,
 * 			from `first` included to `last` excluded. (range
 * insertion)
 *
 * @tparam	InputIterator The type of the iterators to use.
 * 			(it must conform to the standard input Iterator
 * requirements)
 *
 * @param	first The first element of the range.
 * @param	last The last element of the range.
 */
template <typename InputIterator>
void insert(
    InputIterator first, InputIterator const last
)
{
    for (; first != last; ++first) {
        insert(*first);
    }
}

/**
 * @brief	Insert an element in the Map. (single insertion)
 *
 * @param	inner The value of the element to insert in the Map.
 *
 * @return	A Pair containing an Iterator to the element of the Map with the
 * given value as `first` member, and a boolean indicating whether a new
 * element has been inserted as `second` member.
 */
Pair<Iterator, bool> insert(
    Pair const &inner
)
{
    return m_inner.insert(inner);
}

/**
 * @brief	Insert an element in the Map. (single insertion with hint)
 *
 * @param	pos The position where to insert the element.
 * @param	inner The value of the element to insert in the Map.
 *
 * @return	An Iterator to the element of the Map with the given value.
 */
Iterator insert(
    Iterator const pos, Pair const &inner
)
{
    return m_inner.insert(pos.base(), inner);
}

/**
 * @return	A KeyComparator default object.
 */
KeyComparator key_comp(
    void
) const
{
    return KeyComparator();
}

/**
 * @brief	Search for the first element in the Map that should be after or
 * at the given key.
 *
 * @param	key The key of the virtual element preceding the searched one.
 *
 * @return	An Iterator to the element if found, or end() if not.
 */
Iterator lower_bound(
    Key const &key
)
{
    return m_inner.lower_bound(Pair(key, MappedElement()));
}

/**
 * @brief	Search for the first constant element in the Map that should be
 * after or at the given key.
 *
 * @param	key The key of the virtual element preceding the searched one.
 *
 * @return	An Iterator to the constant element if found, or end() if not.
 */
ConstIterator lower_bound(
    Key const &key
) const
{
    return m_inner.lower_bound(Pair(key, MappedElement()));
}

/**
 * @return	The maximum number of elements that can be stored in the Map.
 */
Size max_size(
    void
) const
{
    return m_inner.max_size();
}

/**
 * @return	A ReverseIterator to the last element of the Map.
 */
ReverseIterator rbegin(
    void
)
{
    return m_inner.rbegin();
}

/**
 * @return	A ConstReverseIterator to the last element of the Map.
 */
ConstReverseIterator rbegin(
    void
) const
{
    return m_inner.rbegin();
}

/**
 * @return	A ReverseIterator to the pre-first element of the Map.
 */
ReverseIterator rend(
    void
)
{
    return m_inner.rend();
}

/**
 * @return	A ConstReverseIterator to the pre-first element of the Map.
 */
ConstReverseIterator rend(
    void
) const
{
    return m_inner.rend();
}

/**
 * @return	The number of stored elements in the Map.
 */
Size size(
    void
) const
{
    return m_inner.getSize();
}

/**
 * @brief	Swap the content of the given Map with the content of the
 * current Map.
 *
 * @param	other The Map to swap with.
 */
void swap(
    Map &other
)
{
    m_inner.swap(other.m_inner);
}

/**
 * @brief	Search for the first element in the Map that should be strictly
 * after the given key.
 *
 * @param	key The key of the virtual element preceding the searched one.
 *
 * @return	An Iterator to the element if found, or end() if not.
 */
Iterator upper_bound(
    Key const &key
)
{
    return m_inner.upper_bound(Pair(key, MappedElement()));
}

/**
 * @brief	Search for the first constant element in the Map that should be
 * strictly after the given key.
 *
 * @param	key The key of the virtual element preceding the searched one.
 *
 * @return	A ConstIterator to the element if found, or end() if not.
 */
ConstIterator upper_bound(
    Key const &key
) const
{
    return m_inner.upper_bound(Pair(key, MappedElement()));
}

/**
 * @return	A PairComparator default object.
 */
PairComparator value_comp(
    void
) const
{
    return PairComparator();
}

// *****************************************************************************************************************
// //
//                                                     Operators //
// *****************************************************************************************************************
// //

/**
 * @brief	Assign a new content to the Map from another one's. (copy
 * assignation)
 *
 * @param	rhs The right hand side Map to copy the content from.
 *
 * @return	The assigned Map.
 */
Map &operator=(
    Map const &rhs
)
{
    if (this != &rhs) {
        m_inner = rhs.m_inner;
    }
    return *this;
}

/**
 * @brief	Look for an element in the Map, inserting it if not found.
 *
 * @param	key The key of the element to get.
 *
 * @return	The element matching the given key.
 */
MappedElement &operator[](
    Key const &key
)
{
    Iterator      it;
    KeyComparator cmp;

    if (!m_inner.getSize()) {
        return m_inner.insert(Pair(key, MappedElement())).first->second;
    }

    it = lower_bound(key);
    if (it == end()) {
        return m_inner.insert(m_inner.getNil()->childs[RCHILD], Pair(key, MappedElement()))->second;
    }

    if (cmp(it->first, key) || cmp(key, it->first)) {
        return m_inner.insert(it.base(), Pair(key, MappedElement()))->second;
    }

    return it->second;
}

}; // class Map

/**
 * @brief	Check if two Map are equivalent.
 *
 * @tparam	Key The key type of both of the Map.
 * @tparam	MappedElement The mapped type of both of the Map.
 * @tparam	KeyComparator The functor to use to compare the keys.
 * @tparam	Allocator The allocator type used in both of the Map.
 *
 * @param	lhs The left hand side Map to compare.
 * @param	rhs The right hand side Map to compare.
 *
 * @return	Either true if the two Map are equivalent, or false if not.
 */
template <typename Key, typename MappedElement, typename KeyComparator, typename Allocator>
bool operator==(
    Map<Key, MappedElement, KeyComparator, Allocator> const &lhs,
    Map<Key, MappedElement, KeyComparator, Allocator> const &rhs
)
{
    return &lhs == &rhs
        || (lhs.size() == rhs.size() && ft::equal(lhs.begin(), lhs.end(), rhs.begin()));
}

/**
 * @brief	Check if two Map are different.
 *
 * @tparam	Key The key type of both of the Map.
 * @tparam	MappedElement The mapped type of both of the Map.
 * @tparam	KeyComparator The functor to use to compare the keys.
 * @tparam	Allocator The allocator type used in both of the Map.
 *
 * @param	lhs The left hand side Map to compare.
 * @param	rhs The right hand side Map to compare.
 *
 * @return	Either true if the two Map are different, or false if not.
 */
template <typename Key, typename MappedElement, typename KeyComparator, typename Allocator>
bool operator!=(
    Map<Key, MappedElement, KeyComparator, Allocator> const &lhs,
    Map<Key, MappedElement, KeyComparator, Allocator> const &rhs
)
{
    return !(lhs == rhs);
}

/**
 * @brief	Check if two Map are strictly lexiographicaly ordered.
 *
 * @tparam	Key The key type of both of the Map.
 * @tparam	MappedElement The mapped type of both of the Map.
 * @tparam	KeyComparator The functor to use to compare the keys.
 * @tparam	Allocator The allocator type used in both of the Map.
 *
 * @param	lhs The left hand side Map to compare.
 * @param	rhs The right hand side Map to compare.
 *
 * @return	Either true if the two Map are strictly lexiographicaly ordered,
 * or false if not.
 */
template <typename Key, typename MappedElement, typename KeyComparator, typename Allocator>
bool operator<(
    Map<Key, MappedElement, KeyComparator, Allocator> const &lhs,
    Map<Key, MappedElement, KeyComparator, Allocator> const &rhs
)
{
    return ft::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end());
}

/**
 * @brief	Check if two Map are strictly lexiographicaly reverse-ordered.
 *
 * @tparam	Key The key type of both of the Map.
 * @tparam	MappedElement The mapped type of both of the Map.
 * @tparam	KeyComparator The functor to use to compare the keys.
 * @tparam	Allocator The allocator type used in both of the Map.
 *
 * @param	lhs The left hand side Map to compare.
 * @param	rhs The right hand side Map to compare.
 *
 * @return	Either true if the two Map are strictly lexiographicaly
 * reverse-ordered, or false if not.
 */
template <typename Key, typename MappedElement, typename KeyComparator, typename Allocator>
bool operator>(
    Map<Key, MappedElement, KeyComparator, Allocator> const &lhs,
    Map<Key, MappedElement, KeyComparator, Allocator> const &rhs
)
{
    return rhs < lhs;
}

/**
 * @brief	Check if two Map are lexiographicaly ordered or equivalent.
 *
 * @tparam	Key The key type of both of the Map.
 * @tparam	MappedElement The mapped type of both of the Map.
 * @tparam	KeyComparator The functor to use to compare the keys.
 * @tparam	Allocator The allocator type used in both of the Map.
 *
 * @param	lhs The left hand side Map to compare.
 * @param	rhs The right hand side Map to compare.
 *
 * @return	Either true if the two Map are lexiographicaly ordered or
 * equivalent, or false if not.
 */
template <typename Key, typename MappedElement, typename KeyComparator, typename Allocator>
bool operator<=(
    Map<Key, MappedElement, KeyComparator, Allocator> const &lhs,
    Map<Key, MappedElement, KeyComparator, Allocator> const &rhs
)
{
    return !(rhs < lhs);
}

/**
 * @brief	Check if two Map are lexiographicaly reverse-ordered or
 * equivalent.
 *
 * @tparam	Key The key type of both of the Map.
 * @tparam	MappedElement The mapped type of both of the Map.
 * @tparam	KeyComparator The functor to use to compare the keys.
 * @tparam	Allocator The allocator type used in both of the Map.
 *
 * @param	lhs The left hand side Map to compare.
 * @param	rhs The right hand side Map to compare.
 *
 * @return	Either true if the two Map are lexiographicaly reverse-ordered
 * or equivalent, or false if not.
 */
template <typename Key, typename MappedElement, typename KeyComparator, typename Allocator>
bool operator>=(
    Map<Key, MappedElement, KeyComparator, Allocator> const &lhs,
    Map<Key, MappedElement, KeyComparator, Allocator> const &rhs
)
{
    return !(lhs < rhs);
}

// *****************************************************************************************************************
// //
//                                               Specialized Functions //
// *****************************************************************************************************************
// //

/**
 * @brief	Swap the contents of two given Map.
 *
 * @tparam	Key The key type of both of the Map.
 * @tparam	MappedElement The mapped type of both of the Map.
 * @tparam	KeyComparator The functor to use to compare the keys.
 * @tparam	Allocator The allocator type used in both of the Map.
 *
 * @param	a The first Map to swap.
 * @param	b The second Map to swap.
 */
template <typename Key, typename MappedElement, typename KeyComparator, typename Allocator>
void swap(
    Map<Key, MappedElement, KeyComparator, Allocator> &a,
    Map<Key, MappedElement, KeyComparator, Allocator> &b
)
{
    a.swap(b);
}

} // namespace ft

#endif
