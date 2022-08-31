/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_algorithm.cpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jodufour <jodufour@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/27 15:09:45 by jodufour          #+#    #+#             */
/*   Updated: 2022/08/30 22:51:05 by jodufour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <algorithm>
#include <cstdlib>
#include <functional>
#include <iostream>
#include <vector>
#include "algorithm.hpp"
#include "iterator/base/input_iterator.tpp"
#include "tester.hpp"

inline static int	__test_equal(void)
{
	title(__func__);
	try
	{
		// Array of int
		{
			int const	arr0[] = {
				-54321,
				-4321,
				-321,
				-21,
				-1,
				0,
				1,
				21,
				321,
				4321,
			};
			int const	arr1[] = {
				-54321,
				-4321,
				-321,
				-21,
				-1,
				0,
				1,
				21,
				321,
				43210,
			};

			// Default comparison
			{
				ft::input_iterator<int const>	first0(arr0);
				ft::input_iterator<int const>	last0(arr0 + sizeof(arr0) / sizeof(*arr0));
				ft::input_iterator<int const>	first1(arr1);

				if (ft::equal(first0, last0, first0) != std::equal(first0, last0, first0) ||
					ft::equal(first0, last0, first1) != std::equal(first0, last0, first1))
					return EXIT_FAILURE;
			}
			// Custom comparison
			{
				ft::input_iterator<int const>	first0(arr0);
				ft::input_iterator<int const>	last0(arr0 + sizeof(arr0) / sizeof(*arr0));
				ft::input_iterator<int const>	first1(arr1);
				std::less_equal<int const>		cmp;

				if (ft::equal(first0, last0, first0, cmp) != std::equal(first0, last0, first0, cmp) ||
					ft::equal(first0, last0, first1, cmp) != std::equal(first0, last0, first1, cmp))
					return EXIT_FAILURE;
			}
		}
		// Array of unsigned short
		{
			t_huint const	arr0[] = {
				2U,
				3U,
				5U,
				7U,
				11U,
				13U,
				17U,
				19U,
				23U,
				29U,
			};
			t_huint const	arr1[] = {
				2U,
				3U,
				5U,
				7U,
				11U,
				13U,
				17U,
				19U,
				23U,
				31U,
			};

			// Default comparison
			{
				ft::input_iterator<t_huint const>	first0(arr0);
				ft::input_iterator<t_huint const>	last0(arr0 + sizeof(arr0) / sizeof(*arr0));
				ft::input_iterator<t_huint const>	first1(arr1);

				if (ft::equal(first0, last0, first0) != std::equal(first0, last0, first0) ||
					ft::equal(first0, last0, first1) != std::equal(first0, last0, first1))
					return EXIT_FAILURE;
			}
			// Custom comparison
			{
				ft::input_iterator<t_huint const>	first0(arr0);
				ft::input_iterator<t_huint const>	last0(arr0 + sizeof(arr0) / sizeof(*arr0));
				ft::input_iterator<t_huint const>	first1(arr1);
				std::less_equal<t_huint const>		cmp;

				if (ft::equal(first0, last0, first0, cmp) != std::equal(first0, last0, first0, cmp) ||
					ft::equal(first0, last0, first1, cmp) != std::equal(first0, last0, first1, cmp))
					return EXIT_FAILURE;
			}
		}
		// Array of string
		{
			std::string const	arr0[] = {
				std::string("Half-past twelve"),
				std::string("And I'm watching the late show in my flat all alone"),
				std::string("How I hate to spend the evening on my own"),
				std::string("Autumn winds"),
				std::string("Blowing outside the window as I look around the room"),
				std::string("And it makes me so depressed to see the gloom"),
				std::string("There's not a soul out there"),
				std::string("No one to hear my prayer"),
				std::string("Gimme, gimme, gimme a man after midnight"),
				std::string("Won't somebody help me chase the shadows away ?"),
			};
			std::string const	arr1[] = {
				std::string("Half-past twelve"),
				std::string("And I'm watching the late show in my flat all alone"),
				std::string("How I hate to spend the evening on my own"),
				std::string("Autumn winds"),
				std::string("Blowing outside the window as I look around the room"),
				std::string("And it makes me so depressed to see the gloom"),
				std::string("There's not a soul out there"),
				std::string("No one to hear my prayer"),
				std::string("Gimme, gimme, gimme a man after midnight"),
				std::string("Won't somebody help me chase the shadows away?"),
			};

			// Default comparison
			{
				ft::input_iterator<std::string const>	first0(arr0);
				ft::input_iterator<std::string const>	last0(arr0 + sizeof(arr0) / sizeof(*arr0));
				ft::input_iterator<std::string const>	first1(arr1);

				if (ft::equal(first0, last0, first0) != std::equal(first0, last0, first0) ||
					ft::equal(first0, last0, first1) != std::equal(first0, last0, first1))
					return EXIT_FAILURE;
			}
			// Custom comparison
			{
				ft::input_iterator<std::string const>	first0(arr0);
				ft::input_iterator<std::string const>	last0(arr0 + sizeof(arr0) / sizeof(*arr0));
				ft::input_iterator<std::string const>	first1(arr1);
				std::less_equal<std::string const>		cmp;

				if (ft::equal(first0, last0, first0, cmp) != std::equal(first0, last0, first0, cmp) ||
					ft::equal(first0, last0, first1, cmp) != std::equal(first0, last0, first1, cmp))
					return EXIT_FAILURE;
			}
			
		}
		// Vector of int
		{
			int const				arr0[] = {
				-54321,
				-4321,
				-321,
				-21,
				-1,
				0,
				1,
				21,
				321,
				4321
			};
			int const				arr1[] = {
				-54321,
				-4321,
				-321,
				-21,
				-1,
				0,
				1,
				21,
				321,
				43210
			};
			std::vector<int> const	vec0(arr0, arr0 + sizeof(arr0) / sizeof(*arr0));
			std::vector<int> const	vec1(arr1, arr1 + sizeof(arr1) / sizeof(*arr1));

			// Default comparison
			{
				std::vector<int>::const_iterator	first0(vec0.begin());
				std::vector<int>::const_iterator	last0(vec0.end());
				std::vector<int>::const_iterator	first1(vec1.begin());

				if (ft::equal(first0, last0, first0) != std::equal(first0, last0, first0) ||
					ft::equal(first0, last0, first1) != std::equal(first0, last0, first1))
					return EXIT_FAILURE;
			}
			// Custom comparison
			{
				std::vector<int>::const_iterator	first0(vec0.begin());
				std::vector<int>::const_iterator	last0(vec0.end());
				std::vector<int>::const_iterator	first1(vec1.begin());
				std::less_equal<int const>			cmp;

				if (ft::equal(first0, last0, first0, cmp) != std::equal(first0, last0, first0, cmp) ||
					ft::equal(first0, last0, first1, cmp) != std::equal(first0, last0, first1, cmp))
					return EXIT_FAILURE;
			}
		}
		// Vector of unsigned short
		{
			t_huint const				arr0[] = {
				2U,
				3U,
				5U,
				7U,
				11U,
				13U,
				17U,
				19U,
				23U,
				29U
			};
			t_huint const				arr1[] = {
				2U,
				3U,
				5U,
				7U,
				11U,
				13U,
				17U,
				19U,
				23U,
				31U
			};
			std::vector<t_huint> const	vec0(arr0, arr0 + sizeof(arr0) / sizeof(*arr0));
			std::vector<t_huint> const	vec1(arr1, arr1 + sizeof(arr1) / sizeof(*arr1));

			// Default comparison
			{
				std::vector<t_huint>::const_iterator	first0(vec0.begin());
				std::vector<t_huint>::const_iterator	last0(vec0.end());
				std::vector<t_huint>::const_iterator	first1(vec1.begin());

				if (ft::equal(first0, last0, first0) != std::equal(first0, last0, first0) ||
					ft::equal(first0, last0, first1) != std::equal(first0, last0, first1))
					return EXIT_FAILURE;
			}
			// Custom comparison
			{
				std::vector<t_huint>::const_iterator	first0(vec0.begin());
				std::vector<t_huint>::const_iterator	last0(vec0.end());
				std::vector<t_huint>::const_iterator	first1(vec1.begin());
				std::less_equal<t_huint const>			cmp;

				if (ft::equal(first0, last0, first0, cmp) != std::equal(first0, last0, first0, cmp) ||
					ft::equal(first0, last0, first1, cmp) != std::equal(first0, last0, first1, cmp))
					return EXIT_FAILURE;
			}
		}
		// Vector of string
		{
			std::string const				arr0[] = {
				std::string("Half-past twelve"),
				std::string("And I'm watching the late show in my flat all alone"),
				std::string("How I hate to spend the evening on my own"),
				std::string("Autumn winds"),
				std::string("Blowing outside the window as I look around the room"),
				std::string("And it makes me so depressed to see the gloom"),
				std::string("There's not a soul out there"),
				std::string("No one to hear my prayer"),
				std::string("Gimme, gimme, gimme a man after midnight"),
				std::string("Won't somebody help me chase the shadows away ?"),
			};
			std::string const				arr1[] = {
				std::string("Half-past twelve"),
				std::string("And I'm watching the late show in my flat all alone"),
				std::string("How I hate to spend the evening on my own"),
				std::string("Autumn winds"),
				std::string("Blowing outside the window as I look around the room"),
				std::string("And it makes me so depressed to see the gloom"),
				std::string("There's not a soul out there"),
				std::string("No one to hear my prayer"),
				std::string("Gimme, gimme, gimme a man after midnight"),
				std::string("Won't somebody help me chase the shadows away?"),
			};
			std::vector<std::string> const	vec0(arr0, arr0 + sizeof(arr0) / sizeof(*arr0));
			std::vector<std::string> const	vec1(arr1, arr1 + sizeof(arr1) / sizeof(*arr1));

			// Default comparison
			{
				std::vector<std::string>::const_iterator	first0(vec0.begin());
				std::vector<std::string>::const_iterator	last0(vec0.end());
				std::vector<std::string>::const_iterator	first1(vec1.begin());

				if (ft::equal(first0, last0, first0) != std::equal(first0, last0, first0) ||
					ft::equal(first0, last0, first1) != std::equal(first0, last0, first1))
					return EXIT_FAILURE;
			}
			// Custom comparison
			{
				std::vector<std::string>::const_iterator	first0(vec0.begin());
				std::vector<std::string>::const_iterator	last0(vec0.end());
				std::vector<std::string>::const_iterator	first1(vec1.begin());
				std::less_equal<std::string const>			cmp;

				if (ft::equal(first0, last0, first0, cmp) != std::equal(first0, last0, first0, cmp) ||
					ft::equal(first0, last0, first1, cmp) != std::equal(first0, last0, first1, cmp))
					return EXIT_FAILURE;
			}
		}
	}
	catch (std::exception const &e)
	{
		std::cerr << "Exception: " << e.what() << '\n';
		return EXIT_FAILURE;
	}
	return EXIT_SUCCESS;
}

inline static int	__test_lexicographical_compare(void)
{
	title(__func__);
	try
	{
		// Array of int
		{
			int const	arr0[] = {
				-54321,
				-4321,
				-321,
				-21,
				-1,
				0,
				1,
				21,
				321,
				4321,
			};
			int const	arr1[] = {
				-54321,
				-4321,
				-321,
				-21,
				-1,
				0,
				1,
				21,
				321,
				43210,
			};

			// Default comparison
			{
				ft::input_iterator<int const>	first0(arr0);
				ft::input_iterator<int const>	last0(arr0 + sizeof(arr0) / sizeof(*arr0));
				ft::input_iterator<int const>	first1(arr1);
				ft::input_iterator<int const>	last1(arr1 + sizeof(arr1) / sizeof(*arr1));

				if (ft::lexicographical_compare(first0, last0, first0, last0) !=
					std::lexicographical_compare(first0, last0, first0, last0) ||
					ft::lexicographical_compare(first0, last0, first1, last1) !=
					std::lexicographical_compare(first0, last0, first1, last1))
					return EXIT_FAILURE;
			}
			// Custom comparison
			{
				ft::input_iterator<int const>	first0(arr0);
				ft::input_iterator<int const>	last0(arr0 + sizeof(arr0) / sizeof(*arr0));
				ft::input_iterator<int const>	first1(arr1);
				ft::input_iterator<int const>	last1(arr1 + sizeof(arr1) / sizeof(*arr1));
				std::greater<int const>			cmp;

				if (ft::lexicographical_compare(first0, last0, first0, last0, cmp) !=
					std::lexicographical_compare(first0, last0, first0, last0, cmp) ||
					ft::lexicographical_compare(first0, last0, first1, last1, cmp) !=
					std::lexicographical_compare(first0, last0, first1, last1, cmp))
					return EXIT_FAILURE;
			}
		}
		// Array of unsigned short
		{
			t_huint const	arr0[] = {
				2U,
				3U,
				5U,
				7U,
				11U,
				13U,
				17U,
				19U,
				23U,
				29U,
			};
			t_huint const	arr1[] = {
				2U,
				3U,
				5U,
				7U,
				11U,
				13U,
				17U,
				19U,
				23U,
				31U,
			};

			// Default comparison
			{
				ft::input_iterator<t_huint const>	first0(arr0);
				ft::input_iterator<t_huint const>	last0(arr0 + sizeof(arr0) / sizeof(*arr0));
				ft::input_iterator<t_huint const>	first1(arr1);
				ft::input_iterator<t_huint const>	last1(arr1 + sizeof(arr1) / sizeof(*arr1));

				if (ft::lexicographical_compare(first0, last0, first0, last0) !=
					std::lexicographical_compare(first0, last0, first0, last0) ||
					ft::lexicographical_compare(first0, last0, first1, last1) !=
					std::lexicographical_compare(first0, last0, first1, last1))
					return EXIT_FAILURE;
			}
			// Custom comparison
			{
				ft::input_iterator<t_huint const>	first0(arr0);
				ft::input_iterator<t_huint const>	last0(arr0 + sizeof(arr0) / sizeof(*arr0));
				ft::input_iterator<t_huint const>	first1(arr1);
				ft::input_iterator<t_huint const>	last1(arr1 + sizeof(arr1) / sizeof(*arr1));
				std::greater<t_huint const>			cmp;

				if (ft::lexicographical_compare(first0, last0, first0, last0, cmp) !=
					std::lexicographical_compare(first0, last0, first0, last0, cmp) ||
					ft::lexicographical_compare(first0, last0, first1, last1, cmp) !=
					std::lexicographical_compare(first0, last0, first1, last1, cmp))
					return EXIT_FAILURE;
			}
		}
		// Array of string
		{
			std::string const	arr0[] = {
				std::string("Half-past twelve"),
				std::string("And I'm watching the late show in my flat all alone"),
				std::string("How I hate to spend the evening on my own"),
				std::string("Autumn winds"),
				std::string("Blowing outside the window as I look around the room"),
				std::string("And it makes me so depressed to see the gloom"),
				std::string("There's not a soul out there"),
				std::string("No one to hear my prayer"),
				std::string("Gimme, gimme, gimme a man after midnight"),
				std::string("Won't somebody help me chase the shadows away ?"),
			};
			std::string const	arr1[] = {
				std::string("Half-past twelve"),
				std::string("And I'm watching the late show in my flat all alone"),
				std::string("How I hate to spend the evening on my own"),
				std::string("Autumn winds"),
				std::string("Blowing outside the window as I look around the room"),
				std::string("And it makes me so depressed to see the gloom"),
				std::string("There's not a soul out there"),
				std::string("No one to hear my prayer"),
				std::string("Gimme, gimme, gimme a man after midnight"),
				std::string("Won't somebody help me chase the shadows away?"),
			};

			// Default comparison
			{
				ft::input_iterator<std::string const>	first0(arr0);
				ft::input_iterator<std::string const>	last0(arr0 + sizeof(arr0) / sizeof(*arr0));
				ft::input_iterator<std::string const>	first1(arr1);
				ft::input_iterator<std::string const>	last1(arr1 + sizeof(arr1) / sizeof(*arr1));

				if (ft::lexicographical_compare(first0, last0, first0, last0) !=
					std::lexicographical_compare(first0, last0, first0, last0) ||
					ft::lexicographical_compare(first0, last0, first1, last1) !=
					std::lexicographical_compare(first0, last0, first1, last1))
					return EXIT_FAILURE;
			}
			// Custom comparison
			{
				ft::input_iterator<std::string const>	first0(arr0);
				ft::input_iterator<std::string const>	last0(arr0 + sizeof(arr0) / sizeof(*arr0));
				ft::input_iterator<std::string const>	first1(arr1);
				ft::input_iterator<std::string const>	last1(arr1 + sizeof(arr1) / sizeof(*arr1));
				std::greater<std::string const>			cmp;

				if (ft::lexicographical_compare(first0, last0, first0, last0, cmp) !=
					std::lexicographical_compare(first0, last0, first0, last0, cmp) ||
					ft::lexicographical_compare(first0, last0, first1, last1, cmp) !=
					std::lexicographical_compare(first0, last0, first1, last1, cmp))
					return EXIT_FAILURE;
			}
			
		}
		// Vector of int
		{
			int const				arr0[] = {
				-54321,
				-4321,
				-321,
				-21,
				-1,
				0,
				1,
				21,
				321,
				4321
			};
			int const				arr1[] = {
				-54321,
				-4321,
				-321,
				-21,
				-1,
				0,
				1,
				21,
				321,
				43210
			};
			std::vector<int> const	vec0(arr0, arr0 + sizeof(arr0) / sizeof(*arr0));
			std::vector<int> const	vec1(arr1, arr1 + sizeof(arr1) / sizeof(*arr1));

			// Default comparison
			{
				std::vector<int>::const_iterator	first0(vec0.begin());
				std::vector<int>::const_iterator	last0(vec0.end());
				std::vector<int>::const_iterator	first1(vec1.begin());
				std::vector<int>::const_iterator	last1(vec1.end());

				if (ft::lexicographical_compare(first0, last0, first0, last0) !=
					std::lexicographical_compare(first0, last0, first0, last0) ||
					ft::lexicographical_compare(first0, last0, first1, last1) !=
					std::lexicographical_compare(first0, last0, first1, last1))
					return EXIT_FAILURE;
			}
			// Custom comparison
			{
				std::vector<int>::const_iterator	first0(vec0.begin());
				std::vector<int>::const_iterator	last0(vec0.end());
				std::vector<int>::const_iterator	first1(vec1.begin());
				std::vector<int>::const_iterator	last1(vec1.end());
				std::greater<int const>				cmp;

				if (ft::lexicographical_compare(first0, last0, first0, last0, cmp) !=
					std::lexicographical_compare(first0, last0, first0, last0, cmp) ||
					ft::lexicographical_compare(first0, last0, first1, last1, cmp) !=
					std::lexicographical_compare(first0, last0, first1, last1, cmp))
					return EXIT_FAILURE;
			}
		}
		// Vector of unsigned short
		{
			t_huint const				arr0[] = {
				2U,
				3U,
				5U,
				7U,
				11U,
				13U,
				17U,
				19U,
				23U,
				29U
			};
			t_huint const				arr1[] = {
				2U,
				3U,
				5U,
				7U,
				11U,
				13U,
				17U,
				19U,
				23U,
				31U
			};
			std::vector<t_huint> const	vec0(arr0, arr0 + sizeof(arr0) / sizeof(*arr0));
			std::vector<t_huint> const	vec1(arr1, arr1 + sizeof(arr1) / sizeof(*arr1));

			// Default comparison
			{
				std::vector<t_huint>::const_iterator	first0(vec0.begin());
				std::vector<t_huint>::const_iterator	last0(vec0.end());
				std::vector<t_huint>::const_iterator	first1(vec1.begin());
				std::vector<t_huint>::const_iterator	last1(vec1.end());

				if (ft::lexicographical_compare(first0, last0, first0, last0) !=
					std::lexicographical_compare(first0, last0, first0, last0) ||
					ft::lexicographical_compare(first0, last0, first1, last1) !=
					std::lexicographical_compare(first0, last0, first1, last1))
					return EXIT_FAILURE;
			}
			// Custom comparison
			{
				std::vector<t_huint>::const_iterator	first0(vec0.begin());
				std::vector<t_huint>::const_iterator	last0(vec0.end());
				std::vector<t_huint>::const_iterator	first1(vec1.begin());
				std::vector<t_huint>::const_iterator	last1(vec1.end());
				std::greater<t_huint const>				cmp;

				if (ft::lexicographical_compare(first0, last0, first0, last0, cmp) !=
					std::lexicographical_compare(first0, last0, first0, last0, cmp) ||
					ft::lexicographical_compare(first0, last0, first1, last1, cmp) !=
					std::lexicographical_compare(first0, last0, first1, last1, cmp))
					return EXIT_FAILURE;
			}
		}
		// Vector of string
		{
			std::string const				arr0[] = {
				std::string("Half-past twelve"),
				std::string("And I'm watching the late show in my flat all alone"),
				std::string("How I hate to spend the evening on my own"),
				std::string("Autumn winds"),
				std::string("Blowing outside the window as I look around the room"),
				std::string("And it makes me so depressed to see the gloom"),
				std::string("There's not a soul out there"),
				std::string("No one to hear my prayer"),
				std::string("Gimme, gimme, gimme a man after midnight"),
				std::string("Won't somebody help me chase the shadows away ?"),
			};
			std::string const				arr1[] = {
				std::string("Half-past twelve"),
				std::string("And I'm watching the late show in my flat all alone"),
				std::string("How I hate to spend the evening on my own"),
				std::string("Autumn winds"),
				std::string("Blowing outside the window as I look around the room"),
				std::string("And it makes me so depressed to see the gloom"),
				std::string("There's not a soul out there"),
				std::string("No one to hear my prayer"),
				std::string("Gimme, gimme, gimme a man after midnight"),
				std::string("Won't somebody help me chase the shadows away?"),
			};
			std::vector<std::string> const	vec0(arr0, arr0 + sizeof(arr0) / sizeof(*arr0));
			std::vector<std::string> const	vec1(arr1, arr1 + sizeof(arr1) / sizeof(*arr1));

			// Default comparison
			{
				std::vector<std::string>::const_iterator	first0(vec0.begin());
				std::vector<std::string>::const_iterator	last0(vec0.end());
				std::vector<std::string>::const_iterator	first1(vec1.begin());
				std::vector<std::string>::const_iterator	last1(vec1.end());

				if (ft::lexicographical_compare(first0, last0, first0, last0) !=
					std::lexicographical_compare(first0, last0, first0, last0) ||
					ft::lexicographical_compare(first0, last0, first1, last1) !=
					std::lexicographical_compare(first0, last0, first1, last1))
					return EXIT_FAILURE;
			}
			// Custom comparison
			{
				std::vector<std::string>::const_iterator	first0(vec0.begin());
				std::vector<std::string>::const_iterator	last0(vec0.end());
				std::vector<std::string>::const_iterator	first1(vec1.begin());
				std::vector<std::string>::const_iterator	last1(vec1.end());
				std::greater<std::string const>				cmp;

				if (ft::lexicographical_compare(first0, last0, first0, last0, cmp) !=
					std::lexicographical_compare(first0, last0, first0, last0, cmp) ||
					ft::lexicographical_compare(first0, last0, first1, last1, cmp) !=
					std::lexicographical_compare(first0, last0, first1, last1, cmp))
					return EXIT_FAILURE;
			}
		}
	}
	catch (std::exception const &e)
	{
		std::cerr << "Exception: " << e.what() << '\n';
		return EXIT_FAILURE;
	}
	return EXIT_SUCCESS;
}

inline static int	__test_swap(void)
{
	title(__func__);
	// Swap int
	{
		int	ft_a;
		int	ft_b;
		int	std_a;
		int	std_b;

		ft_a = 42;
		ft_b = -21;
		std_a = ft_a;
		std_b = ft_b;

		ft::swap(ft_a, ft_b);
		std::swap(std_a, std_b);

		if (ft_a != std_a || ft_b != std_b)
			return EXIT_FAILURE;
	}
	// Swap string
	{
		std::string	ft_a;
		std::string	ft_b;
		std::string	std_a;
		std::string	std_b;

		ft_a = std::string("Hello");
		ft_b = std::string("World");
		std_a = ft_a;
		std_b = ft_b;

		ft::swap(ft_a, ft_b);
		std::swap(std_a, std_b);

		if (ft_a != std_a || ft_b != std_b)
			return EXIT_FAILURE;
	}
	// Swap vector of unsigned char
	{
		std::vector<t_hhuint>	ft_a;
		std::vector<t_hhuint>	ft_b;
		std::vector<t_hhuint>	std_a;
		std::vector<t_hhuint>	std_b;
		t_uint					idx;

		for (idx = 0U ; idx < 21U ; ++idx)
			ft_a.push_back(static_cast<t_hhuint>((idx * 7 - 5) / 3));
		for (idx = 0U ; idx < 42U ; ++idx)
			ft_b.push_back(static_cast<t_hhuint>((idx * 5 - 7) / 3));
		std_a = ft_a;
		std_b = ft_b;

		ft::swap(ft_a, ft_b);
		std::swap(std_a, std_b);

		if (ft_a != std_a || ft_b != std_b)
			return EXIT_FAILURE;
	}
	return EXIT_SUCCESS;
}

int	test_algorithm(void)
{
	t_test const	tests[] = {
		__test_equal,
		__test_lexicographical_compare,
		__test_swap,
		NULL
	};
	t_uint			koCount;
	t_uint			idx;

	std::cerr << "\033[38;2;0;173;255m";
	std::cout << "###################################################" << '\n';
	std::cout << "##                   ALGORITHM                   ##" << '\n';
	std::cout << "###################################################" << '\n';
	std::cerr << "\033[0m";

	for (koCount = 0U, idx = 0U ; tests[idx] ; ++idx)
	{
		if (tests[idx]())
		{
			std::cerr << "\033[38;2;255;0;0m";
			std::cout << "[KO]" << '\n';
			std::cerr << "\033[0m";
			++koCount;
		}
		else
		{
			std::cerr << "\033[38;2;0;255;0m";
			std::cout << "[OK]" << '\n';
			std::cerr << "\033[0m";
		}
	}
	std::cout << '\n';
	return koCount;
}
