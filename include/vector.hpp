#ifndef VECTOR_HPP
#define VECTOR_HPP

#include "algorithm.hpp"
#include "iterator.hpp"
#include "type_traits.hpp"
#include <memory>

namespace ft
{
#pragma region[Vector]

template <typename T, typename Alloc = std::allocator<T> >
class Vector
{
public:
    // Member types
    typedef T     ValueType;
    typedef Alloc Allocator;

    typedef typename Allocator::const_reference ConstReference;
    typedef typename Allocator::const_pointer   ConstPointer;
    typedef typename Allocator::pointer         Pointer;
    typedef typename Allocator::reference       Reference;

    typedef ConstPointer                   ConstIterator;
    typedef Pointer                        Iterator;
    typedef ReverseIterator<ConstIterator> ConstReverseIterator;
    typedef ReverseIterator<Iterator>      ReverseIterator;

    typedef typename IteratorTraits<Iterator>::Difference Difference;
    typedef usize                                         Size;

private:
    // Attributes
    Pointer m_head;
    Pointer m_tail;
    Pointer m_end_of_storage;

    // ┏━━━━━━━━━┓
    // ┃ Methods ┃
    // ┗━━━━━━━━━┛

    /**
     * @brief	Determine that the called insert() is a fill insertion,
     * thanks to the fourth paramter type.
     *
     * @tparam	U Any integral type.
     *
     * @param	pos The position to insert the elements.
     * @param	param1 The number of elements to insert.
     * @param	param2 The element value to fill the vector with.
     */
    template <typename U>
    inline void _insertDispatch(
        Iterator const pos, U const param1, U const param2, true_type const
    )
    {
        _insertFill(pos, param1, param2);
    }

    /**
     * @brief	Determine that the called insert() is a range insertion,
     * thanks to the fourth paramter type.
     *
     * @tparam	U Any non-integral type.
     *
     * @param	pos The position to insert the elements.
     * @param	param1 The first element of the range to insert.
     * @param	param2 The last element of the range to insert.
     */
    template <typename U>
    inline void _insertDispatch(
        Iterator const pos, U const param1, U const param2, false_type const
    )
    {
        _insertRange(pos, param1, param2, typename iterator_traits<U>::iterator_category());
    }

    /**
     * @brief	Insert elements at a specific position.
     *
     * @param	pos The position to insert the elements.
     * @param	n The number of elements to insert.
     * @param	inner The element value to fill the vector with.
     */
    inline void _insertFill(
        Iterator const pos, Size const n, ValueType const &inner
    )
    {
        Size const offset = pos - begin();
        Pointer    ptr0;
        Pointer    ptr1;
        Allocator  alloc;

        _prepareMemoryArea(pos, n);

        for (ptr0 = m_head + offset, ptr1 = ptr0 + n; ptr0 != ptr1; ++ptr0) {
            alloc.construct(ptr0, inner);
        }
    }

    /**
     * @brief	Insert elements at a specific position using a range of
     * iterators, from `first` included to `last` excluded. It is assumed
     * that the given iterators are not random access iterators, thanks to
     * the fourth parameter.
     *
     * @tparam	InputIterator The type of the iterators to use.
     * 			(it must conform to the standard input Iterator
     * requirements)
     *
     * @param	pos The position to insert the elements.
     * @param	first The first element of the range.
     * @param	last The last element of the range.
     */
    template <typename InputIterator>
    void _insertRange(
        Iterator const     &pos,
        InputIterator       first,
        InputIterator const last,
        std::input_iterator_tag const
    )
    {
        Size const offset = end() - pos;
        Size       newCapacity;
        Pointer    newHead;
        Pointer    newTail;
        Allocator  alloc;

        newCapacity = size() * 2;
        for (; first != last; ++first) {
            if (size() < capacity()) {
                _rangeMove(m_tail - offset + 1, m_tail - offset, m_tail);
            }
            else {

                if (newCapacity < size() + 1) {
                    newCapacity = size() + 1;
                }
                newHead = alloc.allocate(newCapacity, m_head);
                newTail = newHead + size();
                if (m_head) {
                    _rangeMove(newHead, m_head, m_tail - offset);
                    _rangeMove(newTail - offset + 1, m_tail - offset, m_tail);
                    alloc.deallocate(m_head, capacity());
                }
                m_head           = newHead;
                m_tail           = newTail;
                m_end_of_storage = m_head + newCapacity;
                ++newCapacity;
            }
            alloc.construct(m_tail - offset, *first);
            ++m_tail;
        }
    }

    /**
     * @brief	Insert elements at a specific position using a range of
     * iterators, from `first` included to `last` excluded. It is assumed
     * that the given iterators are random access iterators, thanks to the
     * fourth parameter.
     *
     * @tparam	RandomAccessIterator The type of the iterators to use.
     * 			(it must conform to the standard random access
     * Iterator requirements)
     *
     * @param	pos The position to insert the elements.
     * @param	first The first element of the range.
     * @param	last The last element of the range.
     */
    template <typename RandomAccessIterator>
    void _insertRange(
        Iterator const            &pos,
        RandomAccessIterator       first,
        RandomAccessIterator const last,
        std::random_access_iterator_tag const
    )
    {
        Size const offset = pos - begin();
        Pointer    ptr;
        Allocator  alloc;

        _prepareMemoryArea(pos, last - first);

        for (ptr = m_head + offset; first != last; ++ptr, ++first) {
            alloc.construct(ptr, *first);
        }
    }

    /**
     * @brief	Reorginize the vector content to make a n-sized hole at
     * a specific position. It may result in a reallocation of the vector.
     *
     * @param	pos The position of the hole to make.
     * @param	n The size of the hole to make.
     */
    void _prepareMemoryArea(
        Iterator const &pos, Size const n
    )
    {
        Size const offset = pos - begin();
        Size       newCapacity;
        Pointer    newHead;
        Pointer    newTail;
        Allocator  alloc;

        if (!n) {
            return;
        }
        if (size() + n <= capacity()) {
            _rangeMove(m_head + offset + n, m_head + offset, m_tail);
            m_tail += n;
        }
        else {
            newCapacity = size() * 2;
            if (newCapacity < size() + n) {
                newCapacity = size() + n;
            }
            newHead = alloc.allocate(newCapacity, m_head);
            newTail = newHead + size() + n;
            if (m_head) {
                _rangeMove(newHead, m_head, pos.base());
                _rangeMove(newHead + offset + n, pos.base(), m_tail);
                alloc.deallocate(m_head, capacity());
            }
            m_head           = newHead;
            m_tail           = newTail;
            m_end_of_storage = m_head + newCapacity;
        }
    }

    /**
     * @brief	Copy elements from a location to another, using a range
     * of pointers, from `first` included to `last` excluded, using either
     * trivial copy if possible, or non-trivial copy if not.
     *
     * @param	dst The destination location.
     * @param	first The first element of the range.
     * @param	last The last element of the range.
     */
    inline void _rangeMove(
        Pointer dst, Pointer first, Pointer last
    ) __attribute__((nonnull))
    {
        Allocator alloc;

        if (is_trivially_copyable<ValueType>::value) {
            memmove(dst, first, (last - first) * sizeof(ValueType));
        }
        else if (dst < first) {
            for (; first != last; ++first, ++dst) {
                alloc.construct(dst, *first);
                alloc.destroy(first);
            }
        }
        else if (dst > first) {
            for (dst += (last - first - 1), --first, --last; first != last; --last, --dst) {
                alloc.construct(dst, *last);
                alloc.destroy(last);
            }
        }
    }

public:
    // ┏━━━━━━━━━━━━━━┓
    // ┃ Constructors ┃
    // ┗━━━━━━━━━━━━━━┛

    /**
     * @brief	Construct a new empty vector object. (default
     * constructor)
     */
    explicit Vector(
        Allocator const & = Allocator()
    )
    : m_head(NULL), m_tail(NULL), m_end_of_storage(NULL)
    {}

    /**
     * @brief	Construct a new vector object with specific size and
     * content. (fill constructor)
     *
     * @param	n The number of elements to fill the vector with.
     * @param	inner The element value to fill the vector with.
     */
    explicit Vector(
        Size const n, ValueType const &inner = ValueType(), Allocator const & = Allocator()
    )
    : m_head(NULL), m_tail(NULL), m_end_of_storage(NULL)
    {
        _insertFill(Iterator(), n, inner);
    }

    /**
     * @brief	Construct a new vector object using a range of
     * iterators. The resulting vector will contain the elements from
     * `first` included to `last` excluded. (range constructor)
     *
     * @tparam	InputIterator The type of the iterators to use.
     * 			(it must conform to the standard input Iterator
     * requirements)
     *
     * @param	first The first element of the range.
     * @param	last The last element of the range.
     */
    template <typename InputIterator>
    Vector(
        InputIterator first, InputIterator last, Allocator const & = Allocator()
    )
    : m_head(NULL), m_tail(NULL), m_end_of_storage(NULL)
    {
        _insertDispatch(Iterator(), first, last, is_integral<InputIterator>());
    }

    /**
     * @brief	Construct a new vector object as a copy of another one.
     * (copy constructor)
     *
     * @param	src The vector to copy.
     */
    Vector(
        Vector const &src
    )
    : m_head(NULL), m_tail(NULL), m_end_of_storage(NULL)
    {
        _insertRange(
            Iterator(),
            src.begin(),
            src.end(),
            typename iterator_traits<Iterator>::iterator_category()
        );
    }

    // ┏━━━━━━━━━━━━┓
    // ┃ Destructor ┃
    // ┗━━━━━━━━━━━━┛

    /**
     * @brief	Destroy a vector object, releasing its related allocated
     * memory. (destructor)
     */
    ~Vector(
        void
    )
    {
        clear();
        if (m_head) {
            Allocator().deallocate(m_head, capacity());
        }
    };

    // ┏━━━━━━━━━┓
    // ┃ Methods ┃
    // ┗━━━━━━━━━┛

    /**
     * @brief		Assign a new size and a new content to the
     * vector. (fill assignation)
     *
     * @param n		The new size of the vector.
     * @param inner	The new value to fill the vector with.
     */
    void assign(
        Size const n, ValueType const &inner
    )
    {
        clear();
        _insertFill(begin(), n, inner);
    }

    /**
     * @brief	Assign a new size and a new content to the vector, using
     * a range of iterators, from `first` included to `last` excluded.
     * (range assignation)
     *
     * @tparam	InputIterator The type of the iterators to use.
     * 			(it must conform to the standard input Iterator
     * requirements)
     *
     * @param	first The first element of the range.
     * @param	last The last element of the range.
     */
    template <typename InputIterator>
    void assign(
        InputIterator first, InputIterator last
    )
    {
        clear();
        _insertDispatch(begin(), first, last, is_integral<InputIterator>());
    }

    /**
     * @param	n The position of the element to access.
     *
     * @return	The element at the given position.
     */
    Reference at(
        Size const n
    )
    {
        if (n >= size()) {
            throw std::out_of_range("vector::at");
        }
        return m_head[n];
    }

    /**
     * @param	n The position of the constant element to access.
     *
     * @return	The constant element at the given position.
     */
    ConstReference at(
        Size const n
    ) const
    {
        if (n >= size()) {
            throw std::out_of_range("vector::at");
        }
        return m_head[n];
    }

    /**
     * @return	The last element of the vector.
     */
    Reference back(
        void
    )
    {
        return *(m_tail - 1);
    }

    /**
     * @return	The constant last element of the vector.
     */
    ConstReference back(
        void
    ) const
    {
        return *(m_tail - 1);
    }

    /**
     * @return	An Iterator to the first element of the vector.
     */
    Iterator begin(
        void
    )
    {
        return Iterator(m_head);
    }

    /**
     * @return	A ConstIterator to the first element of the vector.
     */
    ConstIterator begin(
        void
    ) const
    {
        return ConstIterator(m_head);
    }

    /**
     * @return	The number of allocated memory in the vector.
     */
    Size capacity(
        void
    ) const
    {
        return m_end_of_storage - m_head;
    }

    /**
     * @brief	Destroy every element in the vector without deallocating
     * them.
     */
    void clear(
        void
    )
    {
        Allocator alloc;

        if (m_head == m_tail) {
            return;
        }
        for (--m_tail; m_tail != m_head; --m_tail) {
            alloc.destroy(m_tail);
        }
        alloc.destroy(m_tail);
    }

    /**
     * @return	Either true if the vector is empty, or false if not.
     */
    bool empty(
        void
    ) const
    {
        return m_head == m_tail;
    }

    /**
     * @return	An Iterator to the post-last element of the vector.
     */
    Iterator end(
        void
    )
    {
        return Iterator(m_tail);
    }

    /**
     * @return	A ConstIterator to the post-last element of the vector.
     */
    ConstIterator end(
        void
    ) const
    {
        return ConstIterator(m_tail);
    }

    /**
     * @brief	Remove a single element from the vector. (single erase)
     *
     * @param	pos The position of the element to remove.
     *
     * @return	An Iterator to the element after the removed one.
     */
    Iterator erase(
        Iterator const pos
    )
    {
        return erase(pos, pos + 1);
    }

    /**
     * @brief	Remove elements from the vector using a range of
     * iterators, from `first` included to `last` excluded. (range erase)
     *
     * @param	first The first element of the range.
     * @param	last The last element of the range.
     *
     * @return	An Iterator to the element after the removed ones.
     */
    Iterator erase(
        Iterator const &first, Iterator const &last
    )
    {
        Allocator alloc;
        Iterator  it;

        for (it = first; it != last; ++it) {
            alloc.destroy(it.base());
        }
        _rangeMove(first.base(), last.base(), m_tail);
        m_tail -= last - first;
        return first;
    }

    /**
     * @return	The first element of the vector.
     */
    Reference front(
        void
    )
    {
        return *m_head;
    }

    /**
     * @return	The constant first element of the vector.
     */
    ConstReference front(
        void
    ) const
    {
        return *m_head;
    }

    /**
     * @return	An Allocator default object.
     */
    Allocator get_allocator(
        void
    ) const
    {
        return Allocator();
    }

    /**
     * @brief	Insert elements at a specific position. (fill insertion)
     *
     * @par		The call to _insertFill() instead of directly put the
     * implementation here is for handle ambiguous call of an overload of
     * insert().
     *
     * @param	pos The position to insert the elements.
     * @param	n The number of elements to insert.
     * @param	inner The element value to fill the vector with.
     */
    void insert(
        Iterator const pos, Size const n, ValueType const &inner
    )
    {
        _insertFill(pos, n, inner);
    }

    /**
     * @brief	Insert elements at a specific position using a range of
     * iterators, from `first` included to `last` excluded. (range
     * insertion)
     *
     * @par		The call to _insertDispacth() instead of directly put
     * the implementation here is for handle ambiguous call of an overload
     * of insert().
     *
     * @tparam	InputIterator The type of the iterators to use.
     * 			(it must conform to the standard input Iterator
     * requirements)
     *
     * @param	pos The position to insert the elements.
     * @param	first The first element of the range.
     * @param	last The last element of the range.
     */
    template <typename InputIterator>
    void insert(
        Iterator const pos, InputIterator first, InputIterator last
    )
    {
        _insertDispatch(pos, first, last, is_integral<InputIterator>());
    }

    /**
     * @brief	Insert an element at a specific position. (single
     * insertion)
     *
     * @param	pos The position to insert the element.
     * @param	inner The element to insert.
     *
     * @return	An Iterator to the inserted element.
     */
    Iterator insert(
        Iterator const pos, ValueType const &inner
    )
    {
        Size const offset = pos - begin();

        insert(pos, 1LU, inner);
        return begin() + offset;
    }

    /**
     * @return	The maximum number of elements that can be stored in the
     * vector.
     */
    Size max_size(
        void
    ) const
    {
        return Allocator().max_size();
    }

    /**
     * @brief	Destroy the last element in the vector without
     * deallocating it.
     */
    void pop_back(
        void
    )
    {
        if (m_tail) {
            --m_tail;
        }
        Allocator().destroy(m_tail);
    }

    /**
     * @brief	Append a new element at the end of the vector.
     *
     * @param	inner The element value to append.
     */
    void push_back(
        ValueType const &inner
    )
    {
        _insertFill(end(), 1LU, inner);
    }

    /**
     * @return	A ReverseIterator to the last element of the vector.
     */
    ReverseIterator rbegin(
        void
    )
    {
        return ReverseIterator(end());
    }

    /**
     * @return	A ConstReverseIterator to the last element of the
     * vector.
     */
    ConstReverseIterator rbegin(
        void
    ) const
    {
        return ConstReverseIterator(end());
    }

    /**
     * @return	A ReverseIterator to the first element of the vector.
     */
    ReverseIterator rend(
        void
    )
    {
        return ReverseIterator(begin());
    }

    /**
     * @return	A ConstReverseIterator to the first element of the
     * vector.
     */
    ConstReverseIterator rend(
        void
    ) const
    {
        return ConstReverseIterator(begin());
    }

    /**
     * @brief	Request for a minimum capacity of the vector.
     * 			It may result in a reallocation of the content.
     *
     * @param	n The minimum capacity to request.
     */
    void reserve(
        Size const n
    )
    {
        Pointer   newHead;
        Pointer   newTail;
        Allocator alloc;

        if (n <= capacity()) {
            return;
        }
        else if (n > alloc.max_size()) {
            throw std::length_error("vector::reserve");
        }
        newHead = alloc.allocate(n, m_head);
        newTail = newHead + size();
        _rangeMove(newHead, m_head, m_tail);
        alloc.deallocate(m_head, capacity());
        m_head           = newHead;
        m_tail           = newTail;
        m_end_of_storage = m_head + n;
    }

    /**
     * @brief	Request for a new size of the vector.
     * 			In case of a smaller size, the current content
     * is truncated. In case of a greater size, the extra content is filled
     * with `inner`. It may result in a reallocation of the content.
     *
     * @param	n The new size of the vector.
     * @param	inner The value to fill the extra content with.
     */
    void resize(
        Size const n, ValueType const inner = ValueType()
    )
    {
        if (n < size()) {
            erase(m_head + n, end());
        }
        else if (n > size()) {
            _insertFill(end(), n - size(), inner);
        }
    }

    /**
     * @return	The number of stored elements in the vector.
     */
    Size size(
        void
    ) const
    {
        return m_tail - m_head;
    }

    /**
     * @brief	Swap the content of the given vector with the content of
     * the current vector.
     *
     * @param	other The vector to swap with.
     */
    void swap(
        Vector &other
    )
    {
        swap<Pointer>(m_head, other.m_head);
        swap<Pointer>(m_tail, other.m_tail);
        swap<Pointer>(m_end_of_storage, other.m_end_of_storage);
    }

    // ┏━━━━━━━━━━━┓
    // ┃ Operators ┃
    // ┗━━━━━━━━━━━┛

    /**
     * @brief	Assign a new content to the vector from another one's.
     * (copy assignation)
     *
     * @param	rhs The right hand side vector to copy the content from.
     *
     * @return	The assigned vector.
     */
    Vector &operator=(
        Vector const &rhs
    )
    {
        if (this != &rhs) {
            assign(rhs.begin(), rhs.end());
        }
        return *this;
    }

    /**
     * @param	idx The index of the element to get.
     *
     * @return	The element at the given index.
     */
    Reference operator[](
        Size const idx
    )
    {
        return m_head[idx];
    }

    /**
     * @param	idx The index of the constant element to get.
     *
     * @return	The constant element at the given index.
     */
    ConstReference operator[](
        Size const idx
    ) const
    {
        return m_head[idx];
    }

}; // class vector

/**
 * @brief	Check if two vector are equivalent.
 *
 * @tparam	T The type of the elements stored in both of the vector.
 * @tparam	Alloc The allocator type used in both of the vector.
 *
 * @param	lhs The left hand side vector to compare.
 * @param	rhs The right hand side vector to compare.
 *
 * @return	Either true if the two vector are equivalent, or false if not.
 */
template <typename T, typename Alloc>
bool operator==(
    Vector<T, Alloc> const &lhs, Vector<T, Alloc> const &rhs
)
{
    return &lhs == &rhs || (lhs.size() == rhs.size() && equal(lhs.begin(), lhs.end(), rhs.begin()));
}

/**
 * @brief	Check if two vector are different.
 *
 * @tparam	T The type of the elements stored in both of the vector.
 * @tparam	Alloc The allocator type used in both of the vector.
 *
 * @param	lhs The left hand side vector to compare.
 * @param	rhs The right hand side vector to compare.
 *
 * @return	Either true if the two vector are different, or false if not.
 */
template <typename T, typename Alloc>
bool operator!=(
    Vector<T, Alloc> const &lhs, Vector<T, Alloc> const &rhs
)
{
    return !(lhs == rhs);
}

/**
 * @brief	Check if two vector are strictly lexiographicaly ordered.
 *
 * @tparam	T The type of the elements stored in both of the vector.
 * @tparam	Alloc The allocator type used in both of the vector.
 *
 * @param	lhs The left hand side vector to compare.
 * @param	rhs The right hand side vector to compare.
 *
 * @return	Either true if the two vector are strictly lexiographicaly
 * ordered, or false if not.
 */
template <typename T, typename Alloc>
bool operator<(
    Vector<T, Alloc> const &lhs, Vector<T, Alloc> const &rhs
)
{
    return lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end());
}

/**
 * @brief	Check if two vector are strictly lexiographicaly
 * reverse-ordered.
 *
 * @tparam	T The type of the elements stored in both of the vector.
 * @tparam	Alloc The allocator type used in both of the vector.
 *
 * @param	lhs The left hand side vector to compare.
 * @param	rhs The right hand side vector to compare.
 *
 * @return	Either true if the two vector are strictly lexiographicaly
 * reverse-ordered, or false if not.
 */
template <typename T, typename Alloc>
bool operator>(
    Vector<T, Alloc> const &lhs, Vector<T, Alloc> const &rhs
)
{
    return rhs < lhs;
}

/**
 * @brief	Check if two vector are lexiographicaly ordered or equivalent.
 *
 * @tparam	T The type of the elements stored in both of the vector.
 * @tparam	Alloc The allocator type used in both of the vector.
 *
 * @param	lhs The left hand side vector to compare.
 * @param	rhs The right hand side vector to compare.
 *
 * @return	Either true if the two vector are lexiographicaly ordered or
 * equivalent, or false if not.
 */
template <typename T, typename Alloc>
bool operator<=(
    Vector<T, Alloc> const &lhs, Vector<T, Alloc> const &rhs
)
{
    return !(rhs < lhs);
}

/**
 * @brief	Check if two vector are lexiographicaly reverse-ordered or
 * equivalent.
 *
 * @tparam	T The type of the elements stored in both of the vector.
 * @tparam	Alloc The allocator type used in both of the vector.
 *
 * @param	lhs The left hand side vector to compare.
 * @param	rhs The right hand side vector to compare.
 *
 * @return	Either true if the two vector are lexiographicaly
 * reverse-ordered or equivalent, or false if not.
 */
template <typename T, typename Alloc>
bool operator>=(
    Vector<T, Alloc> const &lhs, Vector<T, Alloc> const &rhs
)
{
    return !(lhs < rhs);
}

// ┏━━━━━━━━━━━━━━━━━━━━━━━┓
// ┃ Specialized functions ┃
// ┗━━━━━━━━━━━━━━━━━━━━━━━┛

/**
 * @brief	Swap the contents of two given vector.
 *
 * @tparam	T The type of the elements stored in both of the vector.
 * @tparam	Alloc The allocator type used in both of the vector.
 *
 * @param	a The first vector to swap.
 * @param	b The second vector to swap.
 */
template <typename T, typename Alloc>
void swap(
    Vector<T, Alloc> &a, Vector<T, Alloc> &b
)
{
    a.swap(b);
}

#pragma endregion
} // namespace ft

#endif
