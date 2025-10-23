#ifndef ITERATOR_HPP
#define ITERATOR_HPP

#include "type/fundamentals.hpp" // t_isize
#include <iterator> // std::{{in,out}put,foward,bidirectional,random_access}_iterator_tag

namespace ft {

// ┌──────────────────────────────────────────────────────────┐
// │                       requirements                       │
// ├──────────────────────┬───────────────────────────────────┼──────────┬───────────┬─────┬─────┐
// │        *iter = value │ dereferenceable as an lvalue      │          │           │     │     │
// ├──────────────────────┼───────────────────────────────────┼╌╌╌╌╌╌╌╌╌╌┼─────┐     │     │     │
// │     iter(other_iter) │ copy constructible                │          │     │     │     │     │
// ├──────────────────────┼───────────────────────────────────┤  output  │     │     │     │     │
// │    iter = other_iter │ copy assignable                   │          │     │     │     │     │
// ├──────────────────────┼───────────────────────────────────┤ iterator │     │     │     │     │
// │               ++iter │                                   │          │     │     │     │     │
// ├──────────────────────┤ incrementable                     │          │     │     │     │     │
// │               iter++ │                                   │          │     │     │     │     │
// ├──────────────────────┼───────────────────────────────────┼──────────┘     │     │     │     │
// │        value = *iter │ dereferenceable as an rvalue      │ input iterator │     │     │     │
// ├──────────────────────┼───────────────────────────────────┤                │     │     │     │
// │ value = iter->member │ only if `(*iter).member` is valid │                │     │     │     │
// ├──────────────────────┼───────────────────────────────────┤                │     │     │     │
// │   iter == other_iter │ comparable for equivalence        │                │     │     │     │
// ├──────────────────────┼───────────────────────────────────┤                │     │     │     │
// │   iter != other_iter │ comparable for difference         │                │     │     │     │
// ├──────────────────────┼───────────────────────────────────┼────────────────┘     │     │     │
// │        Iterator iter │                                   │   forward iterator   │     │     │
// ├──────────────────────┤ default constructible             │                      │     │     │
// │               iter() │                                   │                      │     │     │
// ├──────────────────────┼───────────────────────────────────┼──────────────────────┘     │     │
// │               --iter │                                   │   bidirectional iterator   │     │
// ├──────────────────────┤ decrementable                     │                            │     │
// │               iter-- │                                   │                            │     │
// ├──────────────────────┼───────────────────────────────────┼────────────────────────────┘     │
// │        offset + iter │                                   │      random access iterator      │
// ├──────────────────────┤                                   │                                  │
// │        iter + offset │ offset constructible              │                                  │
// ├──────────────────────┤                                   │                                  │
// │        iter - offset │                                   │                                  │
// ├──────────────────────┼───────────────────────────────────┤                                  │
// │       iter += offset │                                   │                                  │
// ├──────────────────────┤ offset movable                    │                                  │
// │       iter -= offset │                                   │                                  │
// ├──────────────────────┼───────────────────────────────────┤                                  │
// │         iter[offset] │ offset dereferenceable            │                                  │
// ├──────────────────────┼───────────────────────────────────┤                                  │
// │    iter - other_iter │ distance calculable               │                                  │
// ├──────────────────────┼───────────────────────────────────┤                                  │
// │    iter < other_iter │                                   │                                  │
// ├──────────────────────┤                                   │                                  │
// │    iter > other_iter │                                   │                                  │
// ├──────────────────────┤ comparable for ordering           │                                  │
// │   iter <= other_iter │                                   │                                  │
// ├──────────────────────┤                                   │                                  │
// │   iter >= other_iter │                                   │                                  │
// └──────────────────────┴───────────────────────────────────┴──────────────────────────────────┘

// clang-format off

typedef std::        input_iterator_tag         input_iterator_tag;
typedef std::       output_iterator_tag        output_iterator_tag;
typedef std::      forward_iterator_tag       forward_iterator_tag;
typedef std::bidirectional_iterator_tag bidirectional_iterator_tag;
typedef std::random_access_iterator_tag random_access_iterator_tag;

// clang-format on

template <typename Iterator>
struct iterator_traits {
    typedef typename Iterator::iterator_category iterator_category;
    typedef typename Iterator::difference_type   difference_type;
    typedef typename Iterator::value_type        value_type;
    typedef typename Iterator::reference         reference;
    typedef typename Iterator::pointer           pointer;
};

template <typename T>
struct iterator_traits<T *> {
    typedef random_access_iterator_tag iterator_category;
    typedef t_isize_mut                difference_type;
    typedef T                          value_type;
    typedef T                         &reference;
    typedef T                         *pointer;
};

template <typename T>
struct iterator_traits<T const *> {
    typedef random_access_iterator_tag iterator_category;
    typedef t_isize_mut                difference_type;
    typedef T                          value_type;
    typedef T const                   &reference;
    typedef T const                   *pointer;
};

/// \par Reverse iterators iterate backwards:
///      increasing them moves them towards the beginning of the range.
///      They are implemented as a wrapper around a bidirectional iterator.
///
template <typename BidirectionalIterator>
class reverse_iterator
{
#define SELF reverse_iterator

private:
    typedef BidirectionalIterator const              t_iterator;
    typedef BidirectionalIterator                    t_iterator_mut;
    typedef SELF const                               t_self;
    typedef SELF                                     t_self_mut;
    typedef iterator_traits<t_iterator> const        t_traits;
    typedef typename t_traits::difference_type const t_difference;

protected:
    t_iterator_mut current;

public:
    typedef t_iterator_mut iterator_type;

    typedef typename t_traits::iterator_category iterator_category;
    typedef typename t_traits::difference_type   difference_type;
    typedef typename t_traits::value_type        value_type;
    typedef typename t_traits::reference         reference;
    typedef typename t_traits::pointer           pointer;

    // ┏━━━━━━━━━━━━━━┓
    // ┃ Constructors ┃
    // ┗━━━━━━━━━━━━━━┛

    SELF() {}

    explicit SELF(
        t_iterator iter
    )
    : current(iter)
    {}

    template <typename OtherBidirectionalIterator> // allows mut-to-const conversion
    SELF(
        SELF<OtherBidirectionalIterator> const &other
    )
    : current(other.current)
    {}

    // ┏━━━━━━━━━┓
    // ┃ Methods ┃
    // ┗━━━━━━━━━┛

    t_iterator base() const { return current; }

    // ┏━━━━━━━━━━━┓
    // ┃ Operators ┃
    // ┗━━━━━━━━━━━┛

    reference &operator*() const { return *--t_iterator(current); }

    pointer operator->() const { return &**this; }

    reference operator[](
        t_difference ofs
    ) const
    {
        return current[-ofs - 1];
    }

    t_self &operator++()
    {
        --current;
        return *this;
    };

    t_self operator++(
        int
    )
    {
        return t_self(current--);
    }

    t_self &operator--()
    {
        ++current;
        return *this;
    }

    t_self operator--(
        int
    )
    {
        return t_self(current++);
    };

    t_self &operator+=(
        t_difference rhs
    )
    {
        return current -= rhs, *this;
    }

    t_self &operator-=(
        t_difference rhs
    )
    {
        return current += rhs, *this;
    }

    t_self operator+(
        t_difference rhs
    ) const
    {
        return reverse_iterator(current - rhs);
    }

    t_self operator-(
        t_difference rhs
    ) const
    {
        return reverse_iterator(current + rhs);
    }

#undef SELF
};

template <typename BidirectionalIterator>
inline bool operator==(
    reverse_iterator<BidirectionalIterator> const &lhs,
    reverse_iterator<BidirectionalIterator> const &rhs
)
{
    return lhs.current == rhs.current;
}

template <typename BidirectionalIterator>
inline bool operator!=(
    reverse_iterator<BidirectionalIterator> const &lhs,
    reverse_iterator<BidirectionalIterator> const &rhs
)
{
    return lhs.current != rhs.current;
}

template <typename BidirectionalIterator>
inline bool operator<(
    reverse_iterator<BidirectionalIterator> const &lhs,
    reverse_iterator<BidirectionalIterator> const &rhs
)
{
    return lhs.current > rhs.current;
}

template <typename BidirectionalIterator>
inline bool operator>(
    reverse_iterator<BidirectionalIterator> const &lhs,
    reverse_iterator<BidirectionalIterator> const &rhs
)
{
    return lhs.current < rhs.current;
}

template <typename BidirectionalIterator>
inline bool operator<=(
    reverse_iterator<BidirectionalIterator> const &lhs,
    reverse_iterator<BidirectionalIterator> const &rhs
)
{
    return lhs.current >= rhs.current;
}

template <typename BidirectionalIterator>
inline bool operator>=(
    reverse_iterator<BidirectionalIterator> const &lhs,
    reverse_iterator<BidirectionalIterator> const &rhs
)
{
    return lhs.current <= rhs.current;
}

template <typename BidirectionalIterator>
inline reverse_iterator<BidirectionalIterator> operator+(
    typename reverse_iterator<BidirectionalIterator>::t_difference lhs,
    reverse_iterator<BidirectionalIterator> const                 &rhs
)
{
    return rhs + lhs;
}

template <typename BidirectionalIterator>
inline typename reverse_iterator<BidirectionalIterator>::t_difference operator-(
    reverse_iterator<BidirectionalIterator> const &lhs,
    reverse_iterator<BidirectionalIterator> const &rhs
)
{
    return rhs.current - lhs.current;
}
} // namespace ft
#endif
