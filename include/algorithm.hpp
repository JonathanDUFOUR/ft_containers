/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   algorithm.hpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jodufour <jodufour@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/27 13:09:13 by jodufour          #+#    #+#             */
/*   Updated: 2022/08/25 20:14:55 by jodufour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ALGORITHM_HPP
# define ALGORITHM_HPP

# include <cstddef>
# include <cstdlib>
# include "type_traits.hpp"

namespace ft
{

/**
 * @brief	Swap two elements of any type.
 * 
 * @tparam	T The type of the elements to swap.
 */
template <typename T>
void	swap(T &a, T &b)
{
	T const	tmp = a;

	a = b;
	b = tmp;
}

/**
 * @brief	Compare elements with some others, using ranges of iterators, from `first0` included to `last0` excluded.
 * 
 * @tparam	InputIterator0 The type of the iterators to use as first and second paramters.
 * 			(it must conform to the standard input iterator requirements)
 * @tparam	InputIterator1 The type of the iterator to use as third paramter.
 * 			(it must conform to the standard input iterator requirements)
 * 
 * @param	first0 The first element of the first range.
 * @param	last0 The last element of the first range.
 * @param	first1 The first element of the second range, to compare with.
 * 
 * @return	Either true if both ranges are equal, or false if not.
 */
template <typename InputIterator0, typename InputIterator1>
bool	equal(InputIterator0 first0, InputIterator0 last0, InputIterator1 first1)
{
	while (first0 != last0 && *first0 == *first1)
	{
		++first0;
		++first1;
	}
	return first0 == last0;
}

/**
 * @brief	Compare elements with some others, using ranges of iterators, from `first0` included to `last0` excluded.
 * 
 * @tparam	InputIterator0 The type of the iterators to use as first and second paramters.
 * 			(it must conform to the standard input iterator requirements)
 * @tparam	InputIterator1 The type of the iterator to use as third paramter.
 * 			(it must conform to the standard input iterator requirements)
 * @tparam	BinaryPredicate A function pointer type that returns an integral type.
 * 
 * @param	first0 The first element of the first range.
 * @param	last0 The last element of the first range.
 * @param	first1 The first element of the second range, to compare with.
 * @param	pred The function to use to compare elements.
 * 
 * @return	Either true if both ranges are equal according to `pred`, or false if not.
 */
template <typename InputIterator0, typename InputIterator1, typename BinaryPredicate>
bool	equal(InputIterator0 first0, InputIterator0 last0, InputIterator1 first1, BinaryPredicate pred)
{
	while (first0 != last0 && pred(*first0, *first1))
	{
		++first0;
		++first1;
	}
	return first0 == last0;
}

/**
 * @brief	Compare lexicographically elements with some others, using ranges of iterators,
 * 			from `first0` included to `last0` excluded, and from `first1` included to `last1` excluded.
 * 
 * @tparam	InputIterator0 The type of the iterators to use as first and second paramters.
 * 			(it must conform to the standard input iterator requirements)
 * @tparam	InputIterator1 The type of the iterators to use as third and fourth paramters.
 * 			(it must conform to the standard input iterator requirements)
 * 
 * @param	first0 The first element of the first range.
 * @param	last0 The last element of the first range.
 * @param	first1 The first element of the second range, to compare with.
 * @param	last1 The last element of the second range, to compare with.
 * 
 * @return	Either true if both ranges are lexicographically ordered, or false if not.
 */
template <typename InputIterator0, typename InputIterator1>
bool	lexicographical_compare(
	InputIterator0 first0,
	InputIterator0 last0,
	InputIterator1 first1,
	InputIterator1 last1)
{
	while (first0 != last0 && first1 != last1 && *first0 == *first1)
	{
		++first0;
		++first1;
	}
	return (first0 == last0) || (first1 != last1 && *first0 < *first1);
}

/**
 * @brief	Compare lexicographically elements with some others, using ranges of iterators,
 * 			from `first0` included to `last0` excluded, and from `first1` included to `last1` excluded.
 * 
 * @tparam	InputIterator0 The type of the iterators to use as first and second paramters.
 * 			(it must conform to the standard input iterator requirements)
 * @tparam	InputIterator1 The type of the iterators to use as third and fourth paramters.
 * 			(it must conform to the standard input iterator requirements)
 * @tparam	Compare A function pointer type that returns an integral type.
 * 
 * @param	first0 The first element of the first range.
 * @param	last0 The last element of the first range.
 * @param	first1 The first element of the second range, to compare with.
 * @param	last1 The last element of the second range, to compare with.
 * @param	comp The function to use to compare elements.
 * 
 * @return	Either true if both ranges are lexicographically ordered according to `comp`, or false if not.
 */
template <typename InputIterator0, typename InputIterator1, typename Compare>
bool	lexicographical_compare(
	InputIterator0 first0,
	InputIterator0 last0,
	InputIterator1 first1,
	InputIterator1 last1,
	Compare comp)
{
	while (first0 != last0 && first1 != last1 && !comp(*first0, *first1) && !comp(*first1, *first0))
	{
		++first0;
		++first1;
	}
	return (first0 == last0) || (first1 != last1 && comp(*first0, *first1));
}
}
#endif
