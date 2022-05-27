/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   algorithm.hpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jodufour <jodufour@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/27 13:09:13 by jodufour          #+#    #+#             */
/*   Updated: 2022/05/27 14:22:29 by jodufour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ALGORITHM_HPP
# define ALGORITHM_HPP

template <typename InputIterator0, typename InputIterator1>
bool	equal(
	InputIterator0 first0,
	InputIterator0 last0,
	InputIterator1 first1)
{
	while (first0 != last0 && *first0 == *first1)
	{
		++first0;
		++first1;
	}
	return first0 == last0;
}

template <typename InputIterator0, typename InputIterator1, typename BinaryPredicate>
bool	equal(
	InputIterator0 first0,
	InputIterator0 last0,
	InputIterator1 first1,
	BinaryPredicate pred)
{
	while (first0 != last0 && pred(*first0, *first1))
	{
		++first0;
		++first1;
	}
	return first0 == last0;
}

template <typename InputIterator0, typename InputIterator1>
bool	lexicographical_compare(
			InputIterator0 first0,
			InputIterator0 last0,
			InputIterator1 first1,
			InputIterator1 last1)
{
	while (first0 != last0
		&& first1 != last1
		&& *first0 == *first1)
	{
		++first0;
		++first1;
	}
	return (first0 == last0) || (first1 != last1 && *first0 < *first1);
}

template <typename InputIterator0, typename InputIterator1, typename Compare>
bool	lexicographical_compare(
			InputIterator0 first0,
			InputIterator0 last0,
			InputIterator1 first1,
			InputIterator1 last1,
			Compare comp)
{
	while (first0 != last0
		&& first1 != last1
		&& !comp(*first0, *first1)
		&& !comp(*first1, *first0))
	{
		++first0;
		++first1;
	}
	return (first0 == last0) || (first1 != last1 && comp(*first0, *first1));
}

#endif
