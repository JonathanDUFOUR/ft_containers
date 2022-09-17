/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_map.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jodufour <jodufour@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/15 00:13:27 by jodufour          #+#    #+#             */
/*   Updated: 2022/09/17 05:56:22 by jodufour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include <list>
#include <map>
#include "arrays.hpp"
#include "iterator/base/random_access_iterator.tpp"
#include "map.hpp"
#include "tester.hpp"
#include "e_ret.hpp"

inline static int	__test_constructor(void)
{
	t_uint	idx;
	int		ret;

	title(__func__);
	ret = IMP_OK;
	try
	{
		// Default constructor
		{
			ft::map<int, int>	ft_map;
			std::map<int, int>	std_map;

			if (sizeof(ft_map) != sizeof(std_map) || memcmp(&ft_map, &std_map, sizeof(ft_map)))
				ret = ISO_OK;
		}
		// Range constructor
		{
			// Range of input_iterator
			{
				std::list<ft::pair<int, t_hhuint> >		ft_lst;
				std::list<std::pair<int, t_hhuint> >	std_lst;

				for (idx = 0U ; idx < g_int_size && idx < g_hhuint_size ; ++idx)
				{
					ft_lst.push_back(ft::pair<int, t_hhuint>(g_int[idx], g_hhuint[idx]));
					std_lst.push_back(std::pair<int, t_hhuint>(g_int[idx], g_hhuint[idx]));
				}

				ft::input_iterator<ft::pair<int, t_hhuint> >	ft_it0(ft_lst.begin());
				ft::input_iterator<ft::pair<int, t_hhuint> >	ft_it1(ft_lst.end());
				ft::input_iterator<std::pair<int, t_hhuint> >	std_it0(std_lst.begin());
				ft::input_iterator<std::pair<int, t_hhuint> >	std_it1(std_lst.end());
				std::map<int, t_hhuint>							std_map(std_it0, std_it1);
				ft::map<int, t_hhuint>							ft_map(ft_it0, ft_it1);

				if (sizeof(ft_map) != sizeof(std_map))
					ret = ISO_OK;
			}
			// Range of forward_iterator
			{
				ft::forward_iterator<ft::pair<t_uint, void *> >		ft_it;
				ft::forward_iterator<std::pair<t_uint, void *> >	std_it;
				ft::map<int, void *>								ft_map(ft_it, ft_it);
				std::map<int, void *>								std_map(std_it, std_it);

				if (sizeof(ft_map) != sizeof(std_map))
					ret = ISO_OK;
			}
			// Range of random_access_iterator
			{
				std::list<ft::pair<t_uint, t_lint> >	ft_lst;
				std::list<std::pair<t_uint, t_lint> >	std_lst;

				for (idx = 0U ; idx < g_uint_size && idx < g_lint_size ; ++idx)
				{
					ft_lst.push_back(ft::pair<t_uint, t_lint>(g_uint[idx], g_lint[idx]));
					std_lst.push_back(std::pair<t_uint, t_lint>(g_uint[idx], g_lint[idx]));
				}

				ft::random_access_iterator<ft::pair<t_uint, t_lint> >	ft_it0(&*ft_lst.begin());
				ft::random_access_iterator<ft::pair<t_uint, t_lint> >	ft_it1(&*ft_lst.end());
				ft::random_access_iterator<std::pair<t_uint, t_lint> >	std_it0(&*std_lst.begin());
				ft::random_access_iterator<std::pair<t_uint, t_lint> >	std_it1(&*std_lst.end());
				ft::map<t_uint, t_lint>									ft_map(ft_it0, ft_it1);
				std::map<t_uint, t_lint>								std_map(std_it0, std_it1);

				if (sizeof(ft_map) != sizeof(std_map))
					ret = ISO_OK;
			}
			// Range of pair *
			{
				std::list<ft::pair<char, int> >		ft_lst;
				std::list<std::pair<char, int> >	std_lst;

				for (idx = 0U ; idx < g_char_size && idx < g_int_size ; ++idx)
				{
					ft_lst.push_back(ft::pair<char, int>(g_char[idx], g_int[idx]));
					std_lst.push_back(std::pair<char, int>(g_char[idx], g_int[idx]));
				}

				ft::map<int, char>	ft_map(&*ft_lst.begin(), &*ft_lst.end());
				std::map<int, char>	std_map(&*std_lst.begin(), &*std_lst.end());

				if (sizeof(ft_map) != sizeof(std_map))
					ret = ISO_OK;
			}
		}
		// Copy constructor
		{
			
		}
	}
	catch (std::exception const &e)
	{
		std::cerr << "Exception: " << e.what() << '\n';
	}
	return EXIT_SUCCESS;
}

int	test_map(void)
{
	t_test const	tests[] = {
		__test_constructor,
		NULL
	};
	t_uint			koCount;
	t_uint			idx;

	std::cerr << "\033[38;2;0;173;255m";
	std::cout << "###################################################" << '\n';
	std::cout << "##                      MAP                      ##" << '\n';
	std::cout << "###################################################" << '\n';
	std::cerr << "\033[0m";
	for (koCount = 0U, idx = 0U ; tests[idx] ; ++idx)
		switch (tests[idx]())
		{
			case IMP_OK:
				std::cerr << "\033[38;2;0;255;0m";
				std::cout << "[OK]" << '\n';
				std::cerr << "\033[0m";
				break;

			case ISO_OK:
				std::cerr << "\033[38;2;255;255;0m";
				std::cout << "[OK]" << '\n';
				std::cerr << "\033[0m";
				break;

			case KO:
				std::cerr << "\033[38;2;255;0;0m";
				std::cout << "[KO]" << '\n';
				std::cerr << "\033[0m";
				++koCount;
				break;
		}
	std::cout << '\n';
	return koCount;
}
