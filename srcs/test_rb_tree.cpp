/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_rb_tree.cpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jodufour <jodufour@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/02 12:13:04 by jodufour          #+#    #+#             */
/*   Updated: 2022/09/08 00:37:31 by jodufour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <algorithm>
#include <cstdlib>
#include <iostream>
#include <list>
#include <set>
#include "arrays.hpp"
#include "iteratorCheck.tpp"
#include "iterator/base/random_access_iterator.tpp"
#include "rb_tree.tpp"
#include "tester.hpp"
#include "t_int.hpp"
#include "utility.hpp"

template <typename T>
inline static void	__blackSteps(ft::rb_node<T> const *const node, std::list<t_uint> &lst, t_uint const steps)
{
	if (!node)
		return lst.push_back(steps);
	__blackSteps(node->child[ft::LEFT], lst, steps + (node->color == ft::BLACK));
	__blackSteps(node->child[ft::RIGHT], lst, steps + (node->color == ft::BLACK));
}

template <typename T, typename Compare>
inline static int	__propertiesCheck(ft::rb_node<T> const *const node, Compare const cmp)
{
	std::list<t_uint>					lst;
	std::list<t_uint>::const_iterator	it;

	if (!node)
		return EXIT_SUCCESS;
	// Color check
	{
		if (node->color != ft::RED && node->color != ft::BLACK)
			return EXIT_FAILURE;
	}
	// Order check
	{
		if ((node->child[ft::LEFT] && !cmp(node->child[ft::LEFT]->data, node->data)) ||
			(node->child[ft::RIGHT] && !cmp(node->data, node->child[ft::RIGHT]->data)))
			return EXIT_FAILURE;
	}
	// Red violation check
	{
		if (node->color == ft::RED &&
			((node->child[ft::LEFT] && node->child[ft::LEFT]->color == ft::RED) ||
			(node->child[ft::RIGHT] && node->child[ft::RIGHT]->color == ft::RED)))
			return EXIT_FAILURE;
	}
	// Black violation check
	{
		__blackSteps(node, lst, 0U);
		for (it = lst.begin() ; it != lst.end() ; ++it)
			if (*it != *lst.begin())
				return EXIT_FAILURE;
	}
	return __propertiesCheck(node->child[ft::LEFT], cmp) || __propertiesCheck(node->child[ft::RIGHT], cmp);
}

template <typename T>
inline static bool	__cmp(ft::rb_node<T> const &lhs, T const &rhs)
{
	return lhs.data == rhs;
}

inline static int	__test_constructor(void)
{
	title(__func__);
	try
	{
		// Default constructor
		{
			ft::rb_tree<int>	tree;
		}
		// Range constructor
		{
			// Range of input_iterator
			{
				ft::input_iterator<t_huint const> const	it0(&g_huint[0]);
				ft::input_iterator<t_huint const> const	it1(&g_huint[0]);
				ft::rb_tree<t_huint> const				tree(it0, it1);
			}
			// Range of forward_iterator
			{
				ft::forward_iterator<void *> const	it0;
				ft::forward_iterator<void *> const	it1;
				ft::rb_tree<void *> const			tree(it0, it1);
			}
			// Range of random_access_iterator
			{
				ft::random_access_iterator<t_huint const> const	it0(&g_huint[0]);
				ft::random_access_iterator<t_huint const> const	it1(&g_huint[g_huint_size]);
				ft::rb_tree<t_huint> const						tree(it0, it1);
			}
			// Range of char const *
			{
				ft::rb_tree<char> const	ft_vec(&g_char[0], &g_char[g_char_size]);
			}
		}
		// Copy constructor
		{
			ft::rb_tree<int>	tree0(&g_int[0], &g_int[g_int_size]);
			ft::rb_tree<int>	tree1(tree0);
		}
	}
	catch (std::exception const &e)
	{
		std::cerr << "Exception: " << e.what() << '\n';
		return EXIT_FAILURE;
	}
	return EXIT_SUCCESS;
}

inline static int	__test_accessor_getMax(void)
{
	t_uint	idx;

	title(__func__);
	try
	{
		// Empty tree
		{
			ft::rb_tree<long double>	tree;

			if (tree.getMax())
				return EXIT_FAILURE;
		}
		// Non-empty tree
		{
			for (idx = 1U ; idx <= g_long_double_size ; ++idx)
			{
				ft::rb_tree<long double>	tree(&g_long_double[0], &g_long_double[idx]);

				if (!tree.getMax() || tree.getMax()->data != *std::max_element(&g_long_double[0], &g_long_double[idx]))
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

inline static int	__test_accessor_getMin(void)
{
	t_uint	idx;

	title(__func__);
	try
	{
		// Empty tree
		{
			ft::rb_tree<t_uint>	tree;

			if (tree.getMin())
				return EXIT_FAILURE;
		}
		// Non-empty tree
		{
			for (idx = 1U ; idx <= g_uint_size ; ++idx)
			{
				ft::rb_tree<t_uint>	tree(&g_uint[0], &g_uint[idx]);

				if (!tree.getMin() || tree.getMin()->data != *std::min_element(&g_uint[0], &g_uint[idx]))
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

inline static int	__test_accessor_getRoot(void)
{
	t_uint	idx;

	title(__func__);
	try
	{
		// Empty tree
		{
			ft::rb_tree<int>	tree;

			if (tree.getRoot())
				return EXIT_FAILURE;
		}
		// Non-empty tree
		{
			for (idx = 1U ; idx <= g_int_size ; ++idx)
			{
				ft::rb_tree<int>	tree(&g_int[0], &g_int[idx]);

				if (!tree.getRoot() || std::find(&g_int[0], &g_int[idx], tree.getRoot()->data) == &g_int[idx])
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

inline static int	__test_accessor_getSize(void)
{
	t_uint	idx;

	title(__func__);
	try
	{
		// Empty tree
		{
			ft::rb_tree<std::string>	tree;

			if (tree.getSize())
				return EXIT_FAILURE;
		}
		// Non-empty tree
		{
			for (idx = 1U ; idx <= g_string_size ; ++idx)
			{
				ft::rb_tree<std::string>	tree(&g_string[0], &g_string[idx]);

				if (tree.getSize() != idx)
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

inline static int	__test_function_begin(void)
{
	t_uint	idx;

	title(__func__);
	try
	{
		// Mutable access
		{
			for (idx = 0U ; idx <= g_luint_size ; ++idx)
			{
				ft::rb_tree<t_luint>					tree(&g_luint[0], &g_luint[idx]);
				ft::rb_tree<t_luint>::iterator const	it(tree.begin());

				if (it.base() != tree.getMin())
					return EXIT_FAILURE;
			}
		}
		// Constant access
		{
			for (idx = 0U ; idx <= g_luint_size ; ++idx)
			{
				ft::rb_tree<t_luint> const					tree(&g_luint[0], &g_luint[idx]);
				ft::rb_tree<t_luint>::const_iterator const	cit(tree.begin());

				if (cit.base() != tree.getMin())
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

inline static int	__test_function_end(void)
{
	t_uint	idx;

	title(__func__);
	try
	{
		// Mutable access
		{
			for (idx = 0U ; idx <= g_luint_size ; ++idx)
			{
				ft::rb_tree<t_luint>					tree(&g_luint[0], &g_luint[idx]);
				ft::rb_tree<t_luint>::iterator const	it(--tree.end());

				if (it.base() != tree.getMax())
					return EXIT_FAILURE;
			}
		}
		// Constant access
		{
			for (idx = 0U ; idx <= g_luint_size ; ++idx)
			{
				ft::rb_tree<t_luint> const					tree(&g_luint[0], &g_luint[idx]);
				ft::rb_tree<t_luint>::const_iterator const	cit(--tree.end());

				if (cit.base() != tree.getMax())
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

inline static int	__test_function_rbegin(void)
{
	t_uint	idx;

	title(__func__);
	try
	{
		// Mutable access
		{
			for (idx = 0U ; idx <= g_luint_size ; ++idx)
			{
				ft::rb_tree<t_luint>							tree(&g_luint[0], &g_luint[idx]);
				ft::rb_tree<t_luint>::reverse_iterator const	rit(tree.rbegin());

				if (rit.base() != tree.end())
					return EXIT_FAILURE;
			}
		}
		// Constant access
		{
			for (idx = 0U ; idx <= g_luint_size ; ++idx)
			{
				ft::rb_tree<t_luint>								tree(&g_luint[0], &g_luint[idx]);
				ft::rb_tree<t_luint>::const_reverse_iterator const	crit(tree.rbegin());

				if (crit.base() != tree.end())
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

inline static int	__test_function_rend(void)
{
	t_uint	idx;

	title(__func__);
	try
	{
		// Mutable access
		{
			for (idx = 0U ; idx <= g_luint_size ; ++idx)
			{
				ft::rb_tree<t_luint>							tree(&g_luint[0], &g_luint[idx]);
				ft::rb_tree<t_luint>::reverse_iterator const	rit(tree.rend());

				if (rit.base() != tree.begin())
					return EXIT_FAILURE;
			}
		}
		// Constant access
		{
			for (idx = 0U ; idx <= g_luint_size ; ++idx)
			{
				ft::rb_tree<t_luint>								tree(&g_luint[0], &g_luint[idx]);
				ft::rb_tree<t_luint>::const_reverse_iterator const	crit(tree.rend());

				if (crit.base() != tree.begin())
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

inline static int	__test_type_iterator(void)
{
	title(__func__);
	try
	{
		ft::rb_tree<float>				tree(&g_float[0], &g_float[g_float_size]);
		ft::rb_tree<float>::iterator	it;

		it = tree.begin();
		BidirectionalIteratorCheck<ft::rb_tree<float>::iterator>(it);

		if (it.base() != tree.getMin())
			return EXIT_FAILURE;
	}
	catch (std::exception const &e)
	{
		std::cerr << "Exception: " << e.what() << '\n';
		return EXIT_FAILURE;
	}
	return EXIT_SUCCESS;
}

inline static int	__test_type_const_iterator(void)
{
	title(__func__);
	try
	{
		ft::rb_tree<float> const			tree(&g_float[0], &g_float[g_float_size]);
		ft::rb_tree<float>::const_iterator	cit;

		cit = tree.begin();
		BidirectionalIteratorCheck<ft::rb_tree<float>::const_iterator>(cit);

		if (cit.base() != tree.getMin())
			return EXIT_FAILURE;
	}
	catch (std::exception const &e)
	{
		std::cerr << "Exception: " << e.what() << '\n';
		return EXIT_FAILURE;
	}
	return EXIT_SUCCESS;
}

inline static int	__test_type_reverse_iterator(void)
{
	title(__func__);
	try
	{
		ft::rb_tree<float>						tree(&g_float[0], &g_float[g_float_size]);
		ft::rb_tree<float>::reverse_iterator	rit;

		rit = tree.rbegin();
		BidirectionalIteratorCheck<ft::rb_tree<float>::reverse_iterator>(rit);

		if (rit.base() != tree.end())
			return EXIT_FAILURE;
	}
	catch (std::exception const &e)
	{
		std::cerr << "Exception: " << e.what() << '\n';
		return EXIT_FAILURE;
	}
	return EXIT_SUCCESS;
}

inline static int	__test_type_const_reverse_iterator(void)
{
	title(__func__);
	try
	{
		ft::rb_tree<float> const					tree(&g_float[0], &g_float[g_float_size]);
		ft::rb_tree<float>::const_reverse_iterator	crit;

		crit = tree.rbegin();
		BidirectionalIteratorCheck<ft::rb_tree<float>::const_reverse_iterator>(crit);

		if (crit.base() != tree.end())
			return EXIT_FAILURE;
	}
	catch (std::exception const &e)
	{
		std::cerr << "Exception: " << e.what() << '\n';
		return EXIT_FAILURE;
	}
	return EXIT_SUCCESS;
}

inline static int	__test_function_insert(void)
{
	t_uint	idx;

	title(__func__);
	try
	{
		ft::rb_tree<std::string>							tree;
		std::set<std::string>								ref;
		ft::pair<ft::rb_tree<std::string>::iterator, bool>	ft_bi;
		std::pair<std::set<std::string>::iterator, bool>	std_bi;

		for (idx = 0U ; idx < g_string_size * 2 ; ++idx)
		{
			ft_bi = tree.insert(g_string[idx / 2]);
			std_bi = ref.insert(g_string[idx / 2]);

			if (ft_bi.first->data != *std_bi.first || ft_bi.second != std_bi.second || tree.getSize() != ref.size() ||
				__propertiesCheck(tree.getRoot(), ft::rb_tree<std::string>::compare_function_type()) ||
				!std::equal<
					ft::rb_tree<std::string>::const_iterator,
					std::set<std::string>::const_iterator,
					bool (*)(ft::rb_node<std::string> const &, std::string const &)>
					(tree.begin(), tree.end(), ref.begin(), __cmp))
				return EXIT_FAILURE;
		}
	}
	catch (std::exception const &e)
	{
		std::cerr << "Exception: " << e.what() << '\n';
		return EXIT_FAILURE;
	}
	return EXIT_SUCCESS;
}

inline static int	__test_function_clear(void)
{
	t_uint	idx;

	title(__func__);
	try
	{
		for (idx = 0U ; idx < g_char_size ; ++idx)
		{
			ft::rb_tree<char>	tree(&g_char[0], &g_char[idx]);

			tree.clear();
			if (tree.getMax() || tree.getMin() || tree.getRoot() || tree.getSize())
				return EXIT_FAILURE;
		}
	}
	catch (std::exception const &e)
	{
		std::cerr << "Exception: " << e.what() << '\n';
		return EXIT_FAILURE;
	}
	return EXIT_SUCCESS;
}

int	test_rb_tree(void)
{
	t_test const	tests[] = {
		__test_constructor,
		__test_accessor_getMax,
		__test_accessor_getMin,
		__test_accessor_getRoot,
		__test_accessor_getSize,
		__test_function_begin,
		__test_function_end,
		__test_function_rbegin,
		__test_function_rend,
		__test_type_iterator,
		__test_type_const_iterator,
		__test_type_reverse_iterator,
		__test_type_const_reverse_iterator,
		__test_function_insert,
		__test_function_clear,
		NULL
	};
	t_uint			koCount;
	t_uint			idx;

	std::cerr << "\033[38;2;0;173;255m";
	std::cout << "###################################################" << '\n';
	std::cout << "##                    RB_TREE                    ##" << '\n';
	std::cout << "###################################################" << '\n';
	std::cerr << "\033[0m";

	for (koCount = 0U, idx = 0U ; tests[idx] ; ++idx)
		switch (tests[idx]())
		{
			case EXIT_SUCCESS:
				std::cerr << "\033[38;2;0;255;0m";
				std::cout << "[OK]" << '\n';
				std::cerr << "\033[0m";
				break;

			case EXIT_FAILURE:
				std::cerr << "\033[38;2;255;0;0m";
				std::cout << "[KO]" << '\n';
				std::cerr << "\033[0m";
				++koCount;
				break;
		}
	std::cout << '\n';
	return koCount;
}
