#ifndef ALGORITHM_HPP
#define ALGORITHM_HPP

#include "functional.hpp"
#include "iterator.hpp"
#include <cstring>

namespace ft {

//! \param first0 The first element of the first range.
//!
//! \param ptend0 The past-the-end element of the first range.
//!
//! \param first1 The first element of the second range.
//!
//! \param cmp    The function to test each element pair.
//!
//! \return `true` if both ranges match according to `cmp`, `false` otherwise.
//!
//! \complexity O(RangeSize).
//!
//! \warning `ptend0` being unreachable by `first0` is undefined behavior.
//!
//! \warning The first range being longer than the second one is undefined behavior.
//!
template <typename InputIterator0, typename InputIterator1, typename BinaryPredicate>
inline bool equal(
    InputIterator0        first0,
    InputIterator0 const  ptend0,
    InputIterator1        first1,
    BinaryPredicate const cmp
)
{
    while (first0 != ptend0 && cmp(*first0, *first1)) {
        ++first0;
        ++first1;
    }
    return first0 == ptend0;
}

//! \param first0 The first element of the first range.
//!
//! \param ptend0 The past-the-end element of the first range.
//!
//! \param first1 The first element of the second range.
//!
//! \return `true` if both ranges match, `false` otherwise.
//!
//! \complexity O(RangeSize).
//!
//! \warning `ptend0` being unreachable by `first0` is undefined behavior.
//!
//! \warning The first range being longer than the second one is undefined behavior.
//!
template <typename InputIterator0, typename InputIterator1>
inline bool equal(
    InputIterator0 first0, InputIterator0 const ptend0, InputIterator1 first1
)
{
    return ft::equal(
        first0, ptend0, first1, EQ(typename iterator_traits<InputIterator0>::value_type)
    );
}

//! \param first0 The first element of the first range.
//!
//! \param ptend0 The past-the-end element of the first range.
//!
//! \param first1 The first element of the second range.
//!
//! \param ptend1 The past-the-end element of the second range.
//!
//! \param cmp The function to test each element pair.
//!
//! \return `true` if both ranges are lexicographically ordered according to `cmp`,
//!         `false` otherwise.
//!
//! \complexity O(min(RangeSize0, RangeSize1)).
//!
//! \warning `ptend0` being unreachable by `first0` is undefined behavior.
//!
//! \warning `ptend1` being unreachable by `first1` is undefined behavior.
//!
template <typename InputIterator0, typename InputIterator1, typename BinaryPredicate>
inline bool lexicographical_compare(
    InputIterator0        first0,
    InputIterator0 const  ptend0,
    InputIterator1        first1,
    InputIterator1 const  ptend1,
    BinaryPredicate const cmp
)
{
    while (first0 != ptend0 && first1 != ptend1) {
        if (cmp(*first0, *first1)) {
            return true;
        }
        ++first0;
        ++first1;
    }
    return first1 != ptend1;
}

//! \param first0 The first element of the first range.
//!
//! \param ptend0 The past-the-end element of the first range.
//!
//! \param first1 The first element of the second range.
//!
//! \param ptend1 The past-the-end element of the second range.
//!
//! \return `true` if both ranges are lexicographically ordered, `false` otherwise.
//!
//! \complexity O(min(RangeSize0, RangeSize1)).
//!
//! \warning `ptend0` being unreachable by `first0` is undefined behavior.
//!
//! \warning `ptend1` being unreachable by `first1` is undefined behavior.
//!
template <typename InputIterator0, typename InputIterator1>
inline bool lexicographical_compare(
    InputIterator0       first0,
    InputIterator0 const ptend0,
    InputIterator1       first1,
    InputIterator1 const ptend1
)
{
    return ft::lexicographical_compare(
        first0, ptend0, first1, ptend1, less<typename iterator_traits<InputIterator0>::value_type>()
    );
}

//! \complexity O(sizeof(T)).
//!
template <typename T>
inline void swap(
    T &a, T &b
)
{
    T const c = a;

    a = b;
    b = c;
}

} // namespace ft

#endif
