/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_algorithm.cpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jodufour <jodufour@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/27 15:09:45 by jodufour          #+#    #+#             */
/*   Updated: 2022/10/08 16:04:43 by jodufour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "algorithm.hpp"
#include "benchmark.hpp"
#include "colors.hpp"
#include "iterator/restrictor/input_iterator_restrictor.tpp"
#include "tester.hpp"
#include "t_int.hpp"
#include <algorithm>
#include <cstdlib>
#include <functional>
#include <iostream>
#include <vector>

static int const			g_int0[] = {
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

static int const			g_int1[] = {
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

static t_huint const		g_huint0[] = {
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

static t_huint const		g_huint1[] = {
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

static std::string const	g_string0[] = {
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

static std::string const	g_string1[] = {
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

static size_t const			g_int0_size = sizeof(g_int0) / sizeof(*g_int0);
static size_t const			g_int1_size = sizeof(g_int1) / sizeof(*g_int1);
static size_t const			g_huint0_size = sizeof(g_huint0) / sizeof(*g_huint0);
static size_t const			g_huint1_size = sizeof(g_huint1) / sizeof(*g_huint1);
static size_t const			g_string0_size = sizeof(g_string0) / sizeof(*g_string0);
static size_t const			g_string1_size = sizeof(g_string1) / sizeof(*g_string1);

inline static int	__test_equal(void)
{
	title(__func__);
	try
	{
		// Array of int
		{
			// Default comparison
			{
				ft::input_iterator_restrictor<int const *> const	first0(&g_int0[0]);
				ft::input_iterator_restrictor<int const *> const	last0(&g_int0[g_int0_size]);
				ft::input_iterator_restrictor<int const *> const	first1(&g_int1[0]);
				bool												ft_ret;
				bool												std_ret;

				g_start = clock();
				ft_ret = ft::equal(first0, last0, first0);
				g_ft_duration = clock() - g_start;

				g_start = clock();
				std_ret = std::equal(first0, last0, first0);
				g_std_duration = clock() - g_start;

				g_ratio.insert(static_cast<float>(g_ft_duration) / static_cast<float>(g_std_duration));

				if (ft_ret != std_ret)
					return EXIT_FAILURE;

				g_start = clock();
				ft_ret = ft::equal(first0, last0, first1);
				g_ft_duration = clock() - g_start;

				g_start = clock();
				std_ret = std::equal(first0, last0, first1);
				g_std_duration = clock() - g_start;

				g_ratio.insert(static_cast<float>(g_ft_duration) / static_cast<float>(g_std_duration));

				if (ft_ret != std_ret)
					return EXIT_FAILURE;
			}
			// Custom comparison
			{
				ft::input_iterator_restrictor<int const *> const	first0(&g_int0[0]);
				ft::input_iterator_restrictor<int const *> const	last0(&g_int0[g_int0_size]);
				ft::input_iterator_restrictor<int const *> const	first1(&g_int1[0]);
				std::less_equal<int const> const					cmp;
				bool												ft_ret;
				bool												std_ret;

				g_start = clock();
				ft_ret = ft::equal(first0, last0, first0, cmp);
				g_ft_duration = clock() - g_start;

				g_start = clock();
				std_ret = std::equal(first0, last0, first0, cmp);
				g_std_duration = clock() - g_start;

				g_ratio.insert(static_cast<float>(g_ft_duration) / static_cast<float>(g_std_duration));

				if (ft_ret != std_ret)
					return EXIT_FAILURE;

				g_start = clock();
				ft_ret = ft::equal(first0, last0, first1, cmp);
				g_ft_duration = clock() - g_start;

				g_start = clock();
				std_ret = std::equal(first0, last0, first1, cmp);
				g_std_duration = clock() - g_start;

				g_ratio.insert(static_cast<float>(g_ft_duration) / static_cast<float>(g_std_duration));

				if (ft_ret != std_ret)
					return EXIT_FAILURE;
			}
		}
		// Array of unsigned short
		{
			// Default comparison
			{
				ft::input_iterator_restrictor<t_huint const *> const	first0(&g_huint0[0]);
				ft::input_iterator_restrictor<t_huint const *> const	last0(&g_huint0[g_huint0_size]);
				ft::input_iterator_restrictor<t_huint const *> const	first1(&g_huint1[0]);
				bool													ft_ret;
				bool													std_ret;

				g_start = clock();
				ft_ret = ft::equal(first0, last0, first0);
				g_ft_duration = clock() - g_start;

				g_start = clock();
				std_ret = std::equal(first0, last0, first0);
				g_std_duration = clock() - g_start;

				g_ratio.insert(static_cast<float>(g_ft_duration) / static_cast<float>(g_std_duration));

				if (ft_ret != std_ret)
					return EXIT_FAILURE;

				g_start = clock();
				ft_ret = ft::equal(first0, last0, first1);
				g_ft_duration = clock() - g_start;

				g_start = clock();
				std_ret = std::equal(first0, last0, first1);
				g_std_duration = clock() - g_start;

				g_ratio.insert(static_cast<float>(g_ft_duration) / static_cast<float>(g_std_duration));

				if (ft_ret != std_ret)
					return EXIT_FAILURE;
			}
			// Custom comparison
			{
				ft::input_iterator_restrictor<t_huint const *> const	first0(&g_huint0[0]);
				ft::input_iterator_restrictor<t_huint const *> const	last0(&g_huint0[g_huint0_size]);
				ft::input_iterator_restrictor<t_huint const *> const	first1(&g_huint1[0]);
				std::less_equal<t_huint const> const					cmp;
				bool													ft_ret;
				bool													std_ret;

				g_start = clock();
				ft_ret = ft::equal(first0, last0, first0, cmp);
				g_ft_duration = clock() - g_start;

				g_start = clock();
				std_ret = std::equal(first0, last0, first0, cmp);
				g_std_duration = clock() - g_start;

				g_ratio.insert(static_cast<float>(g_ft_duration) / static_cast<float>(g_std_duration));

				if (ft_ret != std_ret)
					return EXIT_FAILURE;

				g_start = clock();
				ft_ret = ft::equal(first0, last0, first1, cmp);
				g_ft_duration = clock() - g_start;

				g_start = clock();
				std_ret = std::equal(first0, last0, first1, cmp);
				g_std_duration = clock() - g_start;

				g_ratio.insert(static_cast<float>(g_ft_duration) / static_cast<float>(g_std_duration));

				if (ft_ret != std_ret)
					return EXIT_FAILURE;
			}
		}
		// Array of string
		{
			// Default comparison
			{
				ft::input_iterator_restrictor<std::string const *> const	first0(&g_string0[0]);
				ft::input_iterator_restrictor<std::string const *> const	last0(&g_string0[g_string0_size]);
				ft::input_iterator_restrictor<std::string const *> const	first1(&g_string1[0]);
				bool														ft_ret;
				bool														std_ret;

				g_start = clock();
				ft_ret = ft::equal(first0, last0, first0);
				g_ft_duration = clock() - g_start;

				g_start = clock();
				std_ret = std::equal(first0, last0, first0);
				g_std_duration = clock() - g_start;

				g_ratio.insert(static_cast<float>(g_ft_duration) / static_cast<float>(g_std_duration));

				if (ft_ret != std_ret)
					return EXIT_FAILURE;

				g_start = clock();
				ft_ret = ft::equal(first0, last0, first1);
				g_ft_duration = clock() - g_start;

				g_start = clock();
				std_ret = std::equal(first0, last0, first1);
				g_std_duration = clock() - g_start;

				g_ratio.insert(static_cast<float>(g_ft_duration) / static_cast<float>(g_std_duration));

				if (ft_ret != std_ret)
					return EXIT_FAILURE;
			}
			// Custom comparison
			{
				ft::input_iterator_restrictor<std::string const *> const	first0(&g_string0[0]);
				ft::input_iterator_restrictor<std::string const *> const	last0(&g_string0[g_string0_size]);
				ft::input_iterator_restrictor<std::string const *> const	first1(&g_string1[0]);
				std::less_equal<std::string const> const					cmp;
				bool														ft_ret;
				bool														std_ret;

				g_start = clock();
				ft_ret = ft::equal(first0, last0, first0, cmp);
				g_ft_duration = clock() - g_start;

				g_start = clock();
				std_ret = std::equal(first0, last0, first0, cmp);
				g_std_duration = clock() - g_start;

				g_ratio.insert(static_cast<float>(g_ft_duration) / static_cast<float>(g_std_duration));

				if (ft_ret != std_ret)
					return EXIT_FAILURE;

				g_start = clock();
				ft_ret = ft::equal(first0, last0, first1, cmp);
				g_ft_duration = clock() - g_start;

				g_start = clock();
				std_ret = std::equal(first0, last0, first1, cmp);
				g_std_duration = clock() - g_start;

				g_ratio.insert(static_cast<float>(g_ft_duration) / static_cast<float>(g_std_duration));

				if (ft_ret != std_ret)
					return EXIT_FAILURE;
			}
		}
		// Vector of int
		{
			std::vector<int> const	vec0(&g_int0[0], &g_int0[g_int0_size]);
			std::vector<int> const	vec1(&g_int1[0], &g_int1[g_int1_size]);

			// Default comparison
			{
				std::vector<int>::const_iterator const	first0(vec0.begin());
				std::vector<int>::const_iterator const	last0(vec0.end());
				std::vector<int>::const_iterator const	first1(vec1.begin());
				bool									ft_ret;
				bool									std_ret;

				g_start = clock();
				ft_ret = ft::equal(first0, last0, first0);
				g_ft_duration = clock() - g_start;

				g_start = clock();
				std_ret = std::equal(first0, last0, first0);
				g_std_duration = clock() - g_start;

				g_ratio.insert(static_cast<float>(g_ft_duration) / static_cast<float>(g_std_duration));

				if (ft_ret != std_ret)
					return EXIT_FAILURE;

				g_start = clock();
				ft_ret = ft::equal(first0, last0, first1);
				g_ft_duration = clock() - g_start;

				g_start = clock();
				std_ret = std::equal(first0, last0, first1);
				g_std_duration = clock() - g_start;

				g_ratio.insert(static_cast<float>(g_ft_duration) / static_cast<float>(g_std_duration));

				if (ft_ret != std_ret)
					return EXIT_FAILURE;
			}
			// Custom comparison
			{
				std::vector<int>::const_iterator const	first0(vec0.begin());
				std::vector<int>::const_iterator const	last0(vec0.end());
				std::vector<int>::const_iterator const	first1(vec1.begin());
				std::less_equal<int const> const		cmp;
				bool									ft_ret;
				bool									std_ret;

				g_start = clock();
				ft_ret = ft::equal(first0, last0, first0, cmp);
				g_ft_duration = clock() - g_start;

				g_start = clock();
				std_ret = std::equal(first0, last0, first0, cmp);
				g_std_duration = clock() - g_start;

				g_ratio.insert(static_cast<float>(g_ft_duration) / static_cast<float>(g_std_duration));

				if (ft_ret != std_ret)
					return EXIT_FAILURE;

				g_start = clock();
				ft_ret = ft::equal(first0, last0, first1, cmp);
				g_ft_duration = clock() - g_start;

				g_start = clock();
				std_ret = std::equal(first0, last0, first1, cmp);
				g_std_duration = clock() - g_start;

				g_ratio.insert(static_cast<float>(g_ft_duration) / static_cast<float>(g_std_duration));

				if (ft_ret != std_ret)
					return EXIT_FAILURE;
			}
		}
		// Vector of unsigned short
		{
			std::vector<t_huint> const	vec0(&g_huint0[0], &g_huint0[g_huint0_size]);
			std::vector<t_huint> const	vec1(&g_huint1[0], &g_huint1[g_huint1_size]);

			// Default comparison
			{
				std::vector<t_huint>::const_iterator const	first0(vec0.begin());
				std::vector<t_huint>::const_iterator const	last0(vec0.end());
				std::vector<t_huint>::const_iterator const	first1(vec1.begin());
				bool										ft_ret;
				bool										std_ret;

				g_start = clock();
				ft_ret = ft::equal(first0, last0, first0);
				g_ft_duration = clock() - g_start;

				g_start = clock();
				std_ret = std::equal(first0, last0, first0);
				g_std_duration = clock() - g_start;

				g_ratio.insert(static_cast<float>(g_ft_duration) / static_cast<float>(g_std_duration));

				if (ft_ret != std_ret)
					return EXIT_FAILURE;

				g_start = clock();
				ft_ret = ft::equal(first0, last0, first1);
				g_ft_duration = clock() - g_start;

				g_start = clock();
				std_ret = std::equal(first0, last0, first1);
				g_std_duration = clock() - g_start;

				g_ratio.insert(static_cast<float>(g_ft_duration) / static_cast<float>(g_std_duration));

				if (ft_ret != std_ret)
					return EXIT_FAILURE;
			}
			// Custom comparison
			{
				std::vector<t_huint>::const_iterator const	first0(vec0.begin());
				std::vector<t_huint>::const_iterator const	last0(vec0.end());
				std::vector<t_huint>::const_iterator const	first1(vec1.begin());
				std::less_equal<t_huint const> const		cmp;
				bool										ft_ret;
				bool										std_ret;

				g_start = clock();
				ft_ret = ft::equal(first0, last0, first0, cmp);
				g_ft_duration = clock() - g_start;

				g_start = clock();
				std_ret = std::equal(first0, last0, first0, cmp);
				g_std_duration = clock() - g_start;

				g_ratio.insert(static_cast<float>(g_ft_duration) / static_cast<float>(g_std_duration));

				if (ft_ret != std_ret)
					return EXIT_FAILURE;

				g_start = clock();
				ft_ret = ft::equal(first0, last0, first1, cmp);
				g_ft_duration = clock() - g_start;

				g_start = clock();
				std_ret = std::equal(first0, last0, first1, cmp);
				g_std_duration = clock() - g_start;

				g_ratio.insert(static_cast<float>(g_ft_duration) / static_cast<float>(g_std_duration));

				if (ft_ret != std_ret)
					return EXIT_FAILURE;
			}
		}
		// Vector of string
		{
			std::vector<std::string> const	vec0(&g_string0[0], &g_string0[g_string0_size]);
			std::vector<std::string> const	vec1(&g_string1[0], &g_string1[g_string1_size]);

			// Default comparison
			{
				std::vector<std::string>::const_iterator const	first0(vec0.begin());
				std::vector<std::string>::const_iterator const	last0(vec0.end());
				std::vector<std::string>::const_iterator const	first1(vec1.begin());
				bool											ft_ret;
				bool											std_ret;

				g_start = clock();
				ft_ret = ft::equal(first0, last0, first0);
				g_ft_duration = clock() - g_start;

				g_start = clock();
				std_ret = std::equal(first0, last0, first0);
				g_std_duration = clock() - g_start;

				g_ratio.insert(static_cast<float>(g_ft_duration) / static_cast<float>(g_std_duration));

				if (ft_ret != std_ret)
					return EXIT_FAILURE;

				g_start = clock();
				ft_ret = ft::equal(first0, last0, first1);
				g_ft_duration = clock() - g_start;

				g_start = clock();
				std_ret = std::equal(first0, last0, first1);
				g_std_duration = clock() - g_start;

				g_ratio.insert(static_cast<float>(g_ft_duration) / static_cast<float>(g_std_duration));

				if (ft_ret != std_ret)
					return EXIT_FAILURE;
			}
			// Custom comparison
			{
				std::vector<std::string>::const_iterator const	first0(vec0.begin());
				std::vector<std::string>::const_iterator const	last0(vec0.end());
				std::vector<std::string>::const_iterator const	first1(vec1.begin());
				std::less_equal<std::string const> const		cmp;
				bool											ft_ret;
				bool											std_ret;

				g_start = clock();
				ft_ret = ft::equal(first0, last0, first0, cmp);
				g_ft_duration = clock() - g_start;

				g_start = clock();
				std_ret = std::equal(first0, last0, first0, cmp);
				g_std_duration = clock() - g_start;

				g_ratio.insert(static_cast<float>(g_ft_duration) / static_cast<float>(g_std_duration));

				if (ft_ret != std_ret)
					return EXIT_FAILURE;

				g_start = clock();
				ft_ret = ft::equal(first0, last0, first1, cmp);
				g_ft_duration = clock() - g_start;

				g_start = clock();
				std_ret = std::equal(first0, last0, first1, cmp);
				g_std_duration = clock() - g_start;

				g_ratio.insert(static_cast<float>(g_ft_duration) / static_cast<float>(g_std_duration));

				if (ft_ret != std_ret)
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
			// Default comparison
			{
				ft::input_iterator_restrictor<int const *> const	first0(&g_int0[0]);
				ft::input_iterator_restrictor<int const *> const	last0(&g_int0[g_int0_size]);
				ft::input_iterator_restrictor<int const *> const	first1(&g_int1[0]);
				ft::input_iterator_restrictor<int const *> const	last1(&g_int1[g_int1_size]);
				bool												ft_ret;
				bool												std_ret;

				g_start = clock();
				ft_ret = ft::lexicographical_compare(first0, last0, first0, last0);
				g_ft_duration = clock() - g_start;

				g_start = clock();
				std_ret = std::lexicographical_compare(first0, last0, first0, last0);
				g_std_duration = clock() - g_start;

				g_ratio.insert(static_cast<float>(g_ft_duration) / static_cast<float>(g_std_duration));

				if (ft_ret != std_ret)
					return EXIT_FAILURE;

				g_start = clock();
				ft_ret = ft::lexicographical_compare(first0, last0, first1, last1);
				g_ft_duration = clock() - g_start;

				g_start = clock();
				std_ret = std::lexicographical_compare(first0, last0, first1, last1);
				g_std_duration = clock() - g_start;

				g_ratio.insert(static_cast<float>(g_ft_duration) / static_cast<float>(g_std_duration));

				if (ft_ret != std_ret)
					return EXIT_FAILURE;
			}
			// Custom comparison
			{
				ft::input_iterator_restrictor<int const *> const	first0(&g_int0[0]);
				ft::input_iterator_restrictor<int const *> const	last0(&g_int0[g_int0_size]);
				ft::input_iterator_restrictor<int const *> const	first1(&g_int1[0]);
				ft::input_iterator_restrictor<int const *> const	last1(&g_int1[g_int1_size]);
				std::greater<int const> const						cmp;
				bool												ft_ret;
				bool												std_ret;

				g_start = clock();
				ft_ret = ft::lexicographical_compare(first0, last0, first0, last0, cmp);
				g_ft_duration = clock() - g_start;

				g_start = clock();
				std_ret = std::lexicographical_compare(first0, last0, first0, last0, cmp);
				g_std_duration = clock() - g_start;

				g_ratio.insert(static_cast<float>(g_ft_duration) / static_cast<float>(g_std_duration));

				if (ft_ret != std_ret)
					return EXIT_FAILURE;

				g_start = clock();
				ft_ret = ft::lexicographical_compare(first0, last0, first1, last1, cmp);
				g_ft_duration = clock() - g_start;

				g_start = clock();
				std_ret = std::lexicographical_compare(first0, last0, first1, last1, cmp);
				g_std_duration = clock() - g_start;

				g_ratio.insert(static_cast<float>(g_ft_duration) / static_cast<float>(g_std_duration));

				if (ft_ret != std_ret)
					return EXIT_FAILURE;
			}
		}
		// Array of unsigned short
		{
			// Default comparison
			{
				ft::input_iterator_restrictor<t_huint const *> const	first0(&g_huint0[0]);
				ft::input_iterator_restrictor<t_huint const *> const	last0(&g_huint0[g_huint0_size]);
				ft::input_iterator_restrictor<t_huint const *> const	first1(&g_huint1[0]);
				ft::input_iterator_restrictor<t_huint const *> const	last1(&g_huint1[g_huint1_size]);
				bool													ft_ret;
				bool													std_ret;

				g_start = clock();
				ft_ret = ft::lexicographical_compare(first0, last0, first0, last0);
				g_ft_duration = clock() - g_start;

				g_start = clock();
				std_ret = std::lexicographical_compare(first0, last0, first0, last0);
				g_std_duration = clock() - g_start;

				g_ratio.insert(static_cast<float>(g_ft_duration) / static_cast<float>(g_std_duration));

				if (ft_ret != std_ret)
					return EXIT_FAILURE;

				g_start = clock();
				ft_ret = ft::lexicographical_compare(first0, last0, first1, last1);
				g_ft_duration = clock() - g_start;

				g_start = clock();
				std_ret = std::lexicographical_compare(first0, last0, first1, last1);
				g_std_duration = clock() - g_start;

				g_ratio.insert(static_cast<float>(g_ft_duration) / static_cast<float>(g_std_duration));

				if (ft_ret != std_ret)
					return EXIT_FAILURE;
			}
			// Custom comparison
			{
				ft::input_iterator_restrictor<t_huint const *> const	first0(&g_huint0[0]);
				ft::input_iterator_restrictor<t_huint const *> const	last0(&g_huint0[g_huint0_size]);
				ft::input_iterator_restrictor<t_huint const *> const	first1(&g_huint1[0]);
				ft::input_iterator_restrictor<t_huint const *> const	last1(&g_huint1[g_huint1_size]);
				std::greater<t_huint const> const						cmp;
				bool													ft_ret;
				bool													std_ret;

				g_start = clock();
				ft_ret = ft::lexicographical_compare(first0, last0, first0, last0, cmp);
				g_ft_duration = clock() - g_start;

				g_start = clock();
				std_ret = std::lexicographical_compare(first0, last0, first0, last0, cmp);
				g_std_duration = clock() - g_start;

				g_ratio.insert(static_cast<float>(g_ft_duration) / static_cast<float>(g_std_duration));

				if (ft_ret != std_ret)
					return EXIT_FAILURE;

				g_start = clock();
				ft_ret = ft::lexicographical_compare(first0, last0, first1, last1, cmp);
				g_ft_duration = clock() - g_start;

				g_start = clock();
				std_ret = std::lexicographical_compare(first0, last0, first1, last1, cmp);
				g_std_duration = clock() - g_start;

				g_ratio.insert(static_cast<float>(g_ft_duration) / static_cast<float>(g_std_duration));

				if (ft_ret != std_ret)
					return EXIT_FAILURE;
			}
		}
		// Array of string
		{
			// Default comparison
			{
				ft::input_iterator_restrictor<std::string const *> const	first0(&g_string0[0]);
				ft::input_iterator_restrictor<std::string const *> const	last0(&g_string0[g_string0_size]);
				ft::input_iterator_restrictor<std::string const *> const	first1(&g_string1[0]);
				ft::input_iterator_restrictor<std::string const *> const	last1(&g_string1[g_string1_size]);
				bool														ft_ret;
				bool														std_ret;

				g_start = clock();
				ft_ret = ft::lexicographical_compare(first0, last0, first0, last0);
				g_ft_duration = clock() - g_start;

				g_start = clock();
				std_ret = std::lexicographical_compare(first0, last0, first0, last0);
				g_std_duration = clock() - g_start;

				g_ratio.insert(static_cast<float>(g_ft_duration) / static_cast<float>(g_std_duration));

				if (ft_ret != std_ret)
					return EXIT_FAILURE;

				g_start = clock();
				ft_ret = ft::lexicographical_compare(first0, last0, first1, last1);
				g_ft_duration = clock() - g_start;

				g_start = clock();
				std_ret = std::lexicographical_compare(first0, last0, first1, last1);
				g_std_duration = clock() - g_start;

				g_ratio.insert(static_cast<float>(g_ft_duration) / static_cast<float>(g_std_duration));

				if (ft_ret != std_ret)
					return EXIT_FAILURE;
			}
			// Custom comparison
			{
				ft::input_iterator_restrictor<std::string const *> const	first0(&g_string0[0]);
				ft::input_iterator_restrictor<std::string const *> const	last0(&g_string0[g_string0_size]);
				ft::input_iterator_restrictor<std::string const *> const	first1(&g_string1[0]);
				ft::input_iterator_restrictor<std::string const *> const	last1(&g_string1[g_string1_size]);
				std::greater<std::string const> const						cmp;
				bool														ft_ret;
				bool														std_ret;

				g_start = clock();
				ft_ret = ft::lexicographical_compare(first0, last0, first0, last0, cmp);
				g_ft_duration = clock() - g_start;

				g_start = clock();
				std_ret = std::lexicographical_compare(first0, last0, first0, last0, cmp);
				g_std_duration = clock() - g_start;

				g_ratio.insert(static_cast<float>(g_ft_duration) / static_cast<float>(g_std_duration));

				if (ft_ret != std_ret)
					return EXIT_FAILURE;
				
				g_start = clock();
				ft_ret = ft::lexicographical_compare(first0, last0, first1, last1, cmp);
				g_ft_duration = clock() - g_start;

				g_start = clock();
				std_ret = std::lexicographical_compare(first0, last0, first1, last1, cmp);
				g_std_duration = clock() - g_start;

				g_ratio.insert(static_cast<float>(g_ft_duration) / static_cast<float>(g_std_duration));

				if (ft_ret != std_ret)
					return EXIT_FAILURE;
			}
			
		}
		// Vector of int
		{
			std::vector<int> const	vec0(&g_int0[0], &g_int0[g_int0_size]);
			std::vector<int> const	vec1(&g_int1[0], &g_int1[g_int1_size]);

			// Default comparison
			{
				std::vector<int>::const_iterator const	first0(vec0.begin());
				std::vector<int>::const_iterator const	last0(vec0.end());
				std::vector<int>::const_iterator const	first1(vec1.begin());
				std::vector<int>::const_iterator const	last1(vec1.end());
				bool									ft_ret;
				bool									std_ret;

				g_start = clock();
				ft_ret = ft::lexicographical_compare(first0, last0, first0, last0);
				g_ft_duration = clock() - g_start;

				g_start = clock();
				std_ret = std::lexicographical_compare(first0, last0, first0, last0);
				g_std_duration = clock() - g_start;

				g_ratio.insert(static_cast<float>(g_ft_duration) / static_cast<float>(g_std_duration));

				if (ft_ret != std_ret)
					return EXIT_FAILURE;

				g_start = clock();
				ft_ret = ft::lexicographical_compare(first0, last0, first1, last1);
				g_ft_duration = clock() - g_start;

				g_start = clock();
				std_ret = std::lexicographical_compare(first0, last0, first1, last1);
				g_std_duration = clock() - g_start;

				g_ratio.insert(static_cast<float>(g_ft_duration) / static_cast<float>(g_std_duration));

				if (ft_ret != std_ret)
					return EXIT_FAILURE;
			}
			// Custom comparison
			{
				std::vector<int>::const_iterator const	first0(vec0.begin());
				std::vector<int>::const_iterator const	last0(vec0.end());
				std::vector<int>::const_iterator const	first1(vec1.begin());
				std::vector<int>::const_iterator const	last1(vec1.end());
				std::greater<int const> const			cmp;
				bool									ft_ret;
				bool									std_ret;

				g_start = clock();
				ft_ret = ft::lexicographical_compare(first0, last0, first0, last0, cmp);
				g_ft_duration = clock() - g_start;

				g_start = clock();
				std_ret = std::lexicographical_compare(first0, last0, first0, last0, cmp);
				g_std_duration = clock() - g_start;

				g_ratio.insert(static_cast<float>(g_ft_duration) / static_cast<float>(g_std_duration));

				if (ft_ret != std_ret)
					return EXIT_FAILURE;

				g_start = clock();
				ft_ret = ft::lexicographical_compare(first0, last0, first1, last1, cmp);
				g_ft_duration = clock() - g_start;

				g_start = clock();
				std_ret = std::lexicographical_compare(first0, last0, first1, last1, cmp);
				g_std_duration = clock() - g_start;

				g_ratio.insert(static_cast<float>(g_ft_duration) / static_cast<float>(g_std_duration));

				if (ft_ret != std_ret)
					return EXIT_FAILURE;
			}
		}
		// Vector of unsigned short
		{
			std::vector<t_huint> const	vec0(&g_huint0[0], &g_huint0[g_int0_size]);
			std::vector<t_huint> const	vec1(&g_huint1[0], &g_huint1[g_int1_size]);

			// Default comparison
			{
				std::vector<t_huint>::const_iterator const	first0(vec0.begin());
				std::vector<t_huint>::const_iterator const	last0(vec0.end());
				std::vector<t_huint>::const_iterator const	first1(vec1.begin());
				std::vector<t_huint>::const_iterator const	last1(vec1.end());
				bool										ft_ret;
				bool										std_ret;

				g_start = clock();
				ft_ret = ft::lexicographical_compare(first0, last0, first0, last0);
				g_ft_duration = clock() - g_start;

				g_start = clock();
				std_ret = std::lexicographical_compare(first0, last0, first0, last0);
				g_std_duration = clock() - g_start;

				g_ratio.insert(static_cast<float>(g_ft_duration) / static_cast<float>(g_std_duration));

				if (ft_ret != std_ret)
					return EXIT_FAILURE;

				g_start = clock();
				ft_ret = ft::lexicographical_compare(first0, last0, first1, last1);
				g_ft_duration = clock() - g_start;

				g_start = clock();
				std_ret = std::lexicographical_compare(first0, last0, first1, last1);
				g_std_duration = clock() - g_start;

				g_ratio.insert(static_cast<float>(g_ft_duration) / static_cast<float>(g_std_duration));

				if (ft_ret != std_ret)
					return EXIT_FAILURE;
			}
			// Custom comparison
			{
				std::vector<t_huint>::const_iterator const	first0(vec0.begin());
				std::vector<t_huint>::const_iterator const	last0(vec0.end());
				std::vector<t_huint>::const_iterator const	first1(vec1.begin());
				std::vector<t_huint>::const_iterator const	last1(vec1.end());
				std::greater<t_huint const> const			cmp;
				bool										ft_ret;
				bool										std_ret;

				g_start = clock();
				ft_ret = ft::lexicographical_compare(first0, last0, first0, last0, cmp);
				g_ft_duration = clock() - g_start;

				g_start = clock();
				std_ret = std::lexicographical_compare(first0, last0, first0, last0, cmp);
				g_std_duration = clock() - g_start;

				g_ratio.insert(static_cast<float>(g_ft_duration) / static_cast<float>(g_std_duration));

				if (ft_ret != std_ret)
					return EXIT_FAILURE;

				g_start = clock();
				ft_ret = ft::lexicographical_compare(first0, last0, first1, last1, cmp);
				g_ft_duration = clock() - g_start;

				g_start = clock();
				std_ret = std::lexicographical_compare(first0, last0, first1, last1, cmp);
				g_std_duration = clock() - g_start;

				g_ratio.insert(static_cast<float>(g_ft_duration) / static_cast<float>(g_std_duration));

				if (ft_ret != std_ret)
					return EXIT_FAILURE;
			}
		}
		// Vector of string
		{
			std::vector<std::string> const	vec0(&g_string0[0], &g_string0[g_string0_size]);
			std::vector<std::string> const	vec1(&g_string1[0], &g_string1[g_string1_size]);

			// Default comparison
			{
				std::vector<std::string>::const_iterator const	first0(vec0.begin());
				std::vector<std::string>::const_iterator const	last0(vec0.end());
				std::vector<std::string>::const_iterator const	first1(vec1.begin());
				std::vector<std::string>::const_iterator const	last1(vec1.end());
				bool											ft_ret;
				bool											std_ret;

				g_start = clock();
				ft_ret = ft::lexicographical_compare(first0, last0, first0, last0);
				g_ft_duration = clock() - g_start;

				g_start = clock();
				std_ret = std::lexicographical_compare(first0, last0, first0, last0);
				g_std_duration = clock() - g_start;

				g_ratio.insert(static_cast<float>(g_ft_duration) / static_cast<float>(g_std_duration));

				if (ft_ret != std_ret)
					return EXIT_FAILURE;

				g_start = clock();
				ft_ret = ft::lexicographical_compare(first0, last0, first1, last1);
				g_ft_duration = clock() - g_start;

				g_start = clock();
				std_ret = std::lexicographical_compare(first0, last0, first1, last1);
				g_std_duration = clock() - g_start;

				g_ratio.insert(static_cast<float>(g_ft_duration) / static_cast<float>(g_std_duration));

				if (ft_ret != std_ret)
					return EXIT_FAILURE;
			}
			// Custom comparison
			{
				std::vector<std::string>::const_iterator const	first0(vec0.begin());
				std::vector<std::string>::const_iterator const	last0(vec0.end());
				std::vector<std::string>::const_iterator const	first1(vec1.begin());
				std::vector<std::string>::const_iterator const	last1(vec1.end());
				std::greater<std::string const>					cmp;
				bool											ft_ret;
				bool											std_ret;

				g_start = clock();
				ft_ret = ft::lexicographical_compare(first0, last0, first0, last0, cmp);
				g_ft_duration = clock() - g_start;

				g_start = clock();
				std_ret = std::lexicographical_compare(first0, last0, first0, last0, cmp);
				g_std_duration = clock() - g_start;

				g_ratio.insert(static_cast<float>(g_ft_duration) / static_cast<float>(g_std_duration));

				if (ft_ret != std_ret)
					return EXIT_FAILURE;

				g_start = clock();
				ft_ret = ft::lexicographical_compare(first0, last0, first1, last1, cmp);
				g_ft_duration = clock() - g_start;

				g_start = clock();
				std_ret = std::lexicographical_compare(first0, last0, first1, last1, cmp);
				g_std_duration = clock() - g_start;

				g_ratio.insert(static_cast<float>(g_ft_duration) / static_cast<float>(g_std_duration));

				if (ft_ret != std_ret)
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
/* 
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

		g_start = clock();
		ft::swap(ft_a, ft_b);
		g_ft_duration = clock() - g_start;

		g_start = clock();
		std::swap(std_a, std_b);
		g_std_duration = clock() - g_start;

		g_ratio.insert(static_cast<float>(g_ft_duration) / static_cast<float>(g_std_duration));

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

		g_start = clock();
		ft::swap(ft_a, ft_b);
		g_ft_duration = clock() - g_start;

		g_start = clock();
		std::swap(std_a, std_b);
		g_std_duration = clock() - g_start;

		g_ratio.insert(static_cast<float>(g_ft_duration) / static_cast<float>(g_std_duration));

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

		g_start = clock();
		ft::swap(ft_a, ft_b);
		g_ft_duration = clock() - g_start;

		g_start = clock();
		std::swap(std_a, std_b);
		g_std_duration = clock() - g_start;

		g_ratio.insert(static_cast<float>(g_ft_duration) / static_cast<float>(g_std_duration));

		if (ft_a != std_a || ft_b != std_b)
			return EXIT_FAILURE;
	}
	return EXIT_SUCCESS;
}
 */
int	test_algorithm(void)
{
	t_test const	tests[] = {
		__test_equal,
		__test_lexicographical_compare,
		// __test_swap,
		NULL
	};
	t_uint			koCount;
	t_uint			idx;

	std::cerr << LIGHT_BLUE_FG;
	std::cout << "###################################################" << '\n';
	std::cout << "##                   ALGORITHM                   ##" << '\n';
	std::cout << "###################################################" << '\n';
	std::cerr << RESET;

	for (koCount = 0U, idx = 0U ; tests[idx] ; ++idx)
	{
		switch (tests[idx]())
		{
			case EXIT_SUCCESS:
				std::cerr << GREEN_FG;
				std::cout << "[OK]";
				std::cerr << RESET;
				break;

			case EXIT_FAILURE:
				std::cerr << RED_FG;
				std::cout << "[KO]";
				std::cerr << RESET;
				++koCount;
				break;
		}
		if (!g_ratio.empty())
		{
			std::cout << ' ';
			benchmark_best_case();
			std::cout << ' ';
			benchmark_worst_case();
			std::cout << ' ';
			benchmark_average_case();
			g_ratio.clear();
		}
		std::cout << '\n';
	}
	std::cout << '\n';
	return koCount;
}
