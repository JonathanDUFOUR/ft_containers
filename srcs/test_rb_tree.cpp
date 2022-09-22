/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_rb_tree.cpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jodufour <jodufour@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/02 12:13:04 by jodufour          #+#    #+#             */
/*   Updated: 2022/09/22 17:20:50 by jodufour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <algorithm>
#include <cstdlib>
#include <iostream>
#include <list>
#include <set>
#include "arrays.hpp"
#include "iteratorCheck.tpp"
#include "iterator/restrictor/random_access_iterator_restrictor.tpp"
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
		if ((node->child[ft::LEFT] && !cmp(node->child[ft::LEFT]->val, node->val)) ||
			(node->child[ft::RIGHT] && !cmp(node->val, node->child[ft::RIGHT]->val)))
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
inline static int	__integrityCheck(ft::rb_node<T> const *const node)
{
	if (!node)
		return EXIT_SUCCESS;
	if (node->child[ft::LEFT] && node->child[ft::LEFT]->parent != node)
		return EXIT_FAILURE;
	if (node->child[ft::RIGHT] && node->child[ft::RIGHT]->parent != node)
		return EXIT_FAILURE;
	return __integrityCheck(node->child[ft::LEFT]) || __integrityCheck(node->child[ft::RIGHT]);
}

template <typename T>
inline static bool	__cmp(ft::rb_node<T> const &lhs, T const &rhs)
{
	return lhs.val == rhs;
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
			// Range of input_iterator_restrictor
			{
				ft::input_iterator_restrictor<t_huint const *> const	it0(&g_huint[0]);
				ft::input_iterator_restrictor<t_huint const *> const	it1(&g_huint[0]);
				ft::rb_tree<t_huint> const								tree(it0, it1);
			}
			// Range of forward_iterator_restrictor
			{
				ft::forward_iterator_restrictor<void *const *> const	it;
				ft::rb_tree<void *> const								tree(it, it);
			}
			// Range of random_access_iterator
			{
				ft::random_access_iterator_restrictor<t_huint const *> const	it0(&g_huint[0]);
				ft::random_access_iterator_restrictor<t_huint const *> const	it1(&g_huint[g_huint_size]);
				ft::rb_tree<t_huint> const										tree(it0, it1);
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

				if (!tree.getMax() || tree.getMax()->val != *std::max_element(&g_long_double[0], &g_long_double[idx]))
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

				if (!tree.getMin() || tree.getMin()->val != *std::min_element(&g_uint[0], &g_uint[idx]))
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

				if (!tree.getRoot() || tree.getRoot()->parent ||
					std::find(&g_int[0], &g_int[idx], tree.getRoot()->val) == &g_int[idx])
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
			ft::rb_tree<t_luint>::iterator	it;

			for (idx = 0U ; idx <= g_luint_size ; ++idx)
			{
				ft::rb_tree<t_luint>	tree(&g_luint[0], &g_luint[idx]);

				it = tree.begin();
				if (it.getCurr() != tree.getMin())
					return EXIT_FAILURE;
			}
		}
		// Constant access
		{
			ft::rb_tree<t_luint>::const_iterator	cit;

			for (idx = 0U ; idx <= g_luint_size ; ++idx)
			{
				ft::rb_tree<t_luint> const	tree(&g_luint[0], &g_luint[idx]);

				cit = tree.begin();
				if (cit.getCurr() != tree.getMin())
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

				if (it.getCurr() != tree.getMax())
					return EXIT_FAILURE;
			}
		}
		// Constant access
		{
			for (idx = 0U ; idx <= g_luint_size ; ++idx)
			{
				ft::rb_tree<t_luint> const					tree(&g_luint[0], &g_luint[idx]);
				ft::rb_tree<t_luint>::const_iterator const	cit(--tree.end());

				if (cit.getCurr() != tree.getMax())
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

		if (it.getCurr() != tree.getMin())
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

		if (cit.getCurr() != tree.getMin())
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
		ft::pair<ft::rb_tree<std::string>::iterator, bool>	ft_ret;
		std::pair<std::set<std::string>::iterator, bool>	std_ret;

		for (idx = 0U ; idx < g_string_size * 2 ; ++idx)
		{
			ft_ret = tree.insert(g_string[idx / 2]);
			std_ret = ref.insert(g_string[idx / 2]);

			if (tree.getSize() != ref.size() ||
				*ft_ret.first != *std_ret.first || ft_ret.second != std_ret.second ||
				__integrityCheck(tree.getRoot()) ||
				__propertiesCheck(tree.getRoot(), ft::rb_tree<std::string>::compare_type()) ||
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

inline static int	__test_function_erase(void)
{
	t_uint idx;

	title(__func__);
	try
	{
		// Position erase
		{
			ft::rb_tree<long double>	tree(&g_long_double[0], &g_long_double[g_long_double_size]);
			std::set<long double>		ref(&g_long_double[0], &g_long_double[g_long_double_size]);

			for (idx = 0U ; idx < g_long_double_size ; ++idx)
			{
				if (idx % 2)
				{
					tree.erase(tree.begin().getCurr());
					ref.erase(ref.begin());
				}
				else
				{
					tree.erase((--tree.end()).getCurr());
					ref.erase(--ref.end());
				}

				if (tree.getSize() != ref.size() ||
					__integrityCheck(tree.getRoot()) ||
					__propertiesCheck(tree.getRoot(), ft::rb_tree<long double>::compare_type()) ||
					!std::equal<
						ft::rb_tree<long double>::const_iterator,
						std::set<long double>::const_iterator,
						bool (*)(ft::rb_node<long double> const &, long double const &)>
						(tree.begin(), tree.end(), ref.begin(), __cmp))
					return EXIT_FAILURE;
			}
		}
		// Value erase
		{
			ft::rb_tree<char>	tree(&g_char[0], &g_char[g_char_size]);
			std::set<char>		ref(&g_char[0], &g_char[g_char_size]);
			size_t				ft_ret;
			size_t				std_ret;

			for (idx = 0U ; idx < g_char_size * 2 ; ++idx)
			{
				ft_ret = tree.erase(g_char[idx / 2]);
				std_ret = ref.erase(g_char[idx / 2]);

				if (tree.getSize() != ref.size() || ft_ret != std_ret ||
					__integrityCheck(tree.getRoot()) ||
					__propertiesCheck(tree.getRoot(), ft::rb_tree<char>::compare_type()) ||
					!std::equal<
						ft::rb_tree<char>::const_iterator,
						std::set<char>::const_iterator,
						bool (*)(ft::rb_node<char> const &, char const &)>
						(tree.begin(), tree.end(), ref.begin(), __cmp))
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

inline static int	__test_function_find(void)
{
	t_uint	idx;
	t_lint	nb;

	title(__func__);
	try
	{
		ft::rb_tree<t_lint>	tree(&g_lint[0], &g_lint[g_lint_size]);
		std::set<t_lint>	ref(&g_lint[0], &g_lint[g_lint_size]);

		for (idx = 0U ; idx < g_lint_size * 2 ; ++idx)
		{
			if (idx % 2)
			{
				nb = rand();
				while (std::find(&g_lint[0], &g_lint[g_lint_size], nb) != &g_lint[g_lint_size])
					nb = rand();
				if (tree.find(nb))
					return EXIT_FAILURE;
			}
			else if (tree.find(g_lint[idx / 2])->val != *ref.find(g_lint[idx / 2]))
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

inline static int	__test_function_swap(void)
{
	title(__func__);
	try
	{
		// Swapping empty | empty
		{
			ft::rb_tree<float>	tree0;
			ft::rb_tree<float>	tree1;
			std::set<float>		ref0;
			std::set<float>		ref1;

			tree0.swap(tree1);
			ref0.swap(ref1);
			if (tree0.getSize() != ref0.size() || tree1.getSize() != ref1.size() ||
				__integrityCheck(tree0.getRoot()) || __integrityCheck(tree1.getRoot()) ||
				__propertiesCheck(tree0.getRoot(), ft::rb_tree<float>::compare_type()) ||
				__propertiesCheck(tree1.getRoot(), ft::rb_tree<float>::compare_type()) ||
				!std::equal<
					ft::rb_tree<float>::const_iterator,
					std::set<float>::const_iterator,
					bool (*)(ft::rb_node<float> const &, float const &)>
					(tree0.begin(), tree0.end(), ref0.begin(), __cmp) ||
				!std::equal<
					ft::rb_tree<float>::const_iterator,
					std::set<float>::const_iterator,
					bool (*)(ft::rb_node<float> const &, float const &)>
					(tree1.begin(), tree1.end(), ref1.begin(), __cmp))
				return EXIT_FAILURE;
		}
		// Swapping empty | non-empty
		{
			ft::rb_tree<float>	tree0;
			ft::rb_tree<float>	tree1(&g_float[g_float_size / 2], &g_float[g_float_size]);
			std::set<float>		ref0;
			std::set<float>		ref1(&g_float[g_float_size / 2], &g_float[g_float_size]);

			tree0.swap(tree1);
			ref0.swap(ref1);
			if (tree0.getSize() != ref0.size() || tree1.getSize() != ref1.size() ||
				__integrityCheck(tree0.getRoot()) || __integrityCheck(tree1.getRoot()) ||
				__propertiesCheck(tree0.getRoot(), ft::rb_tree<float>::compare_type()) ||
				__propertiesCheck(tree1.getRoot(), ft::rb_tree<float>::compare_type()) ||
				!std::equal<
					ft::rb_tree<float>::const_iterator,
					std::set<float>::const_iterator,
					bool (*)(ft::rb_node<float> const &, float const &)>
					(tree0.begin(), tree0.end(), ref0.begin(), __cmp) ||
				!std::equal<
					ft::rb_tree<float>::const_iterator,
					std::set<float>::const_iterator,
					bool (*)(ft::rb_node<float> const &, float const &)>
					(tree1.begin(), tree1.end(), ref1.begin(), __cmp))
				return EXIT_FAILURE;
		}
		// Swapping non-empty | empty
		{
			ft::rb_tree<float>	tree0(&g_float[0], &g_float[g_float_size / 2]);
			ft::rb_tree<float>	tree1;
			std::set<float>		ref0(&g_float[0], &g_float[g_float_size / 2]);
			std::set<float>		ref1;

			tree0.swap(tree1);
			ref0.swap(ref1);
			if (tree0.getSize() != ref0.size() || tree1.getSize() != ref1.size() ||
				__integrityCheck(tree0.getRoot()) || __integrityCheck(tree1.getRoot()) ||
				__propertiesCheck(tree0.getRoot(), ft::rb_tree<float>::compare_type()) ||
				__propertiesCheck(tree1.getRoot(), ft::rb_tree<float>::compare_type()) ||
				!std::equal<
					ft::rb_tree<float>::const_iterator,
					std::set<float>::const_iterator,
					bool (*)(ft::rb_node<float> const &, float const &)>
					(tree0.begin(), tree0.end(), ref0.begin(), __cmp) ||
				!std::equal<
					ft::rb_tree<float>::const_iterator,
					std::set<float>::const_iterator,
					bool (*)(ft::rb_node<float> const &, float const &)>
					(tree1.begin(), tree1.end(), ref1.begin(), __cmp))
				return EXIT_FAILURE;
		}
		// Swapping non-empty | non-empty
		{
			ft::rb_tree<float>	tree0(&g_float[0], &g_float[g_float_size / 2]);
			ft::rb_tree<float>	tree1(&g_float[g_float_size / 2], &g_float[g_float_size]);
			std::set<float>		ref0(&g_float[0], &g_float[g_float_size / 2]);
			std::set<float>		ref1(&g_float[g_float_size / 2], &g_float[g_float_size]);

			tree0.swap(tree1);
			ref0.swap(ref1);
			if (tree0.getSize() != ref0.size() || tree1.getSize() != ref1.size() ||
				__integrityCheck(tree0.getRoot()) || __integrityCheck(tree1.getRoot()) ||
				__propertiesCheck(tree0.getRoot(), ft::rb_tree<float>::compare_type()) ||
				__propertiesCheck(tree1.getRoot(), ft::rb_tree<float>::compare_type()) ||
				!std::equal<
					ft::rb_tree<float>::const_iterator,
					std::set<float>::const_iterator,
					bool (*)(ft::rb_node<float> const &, float const &)>
					(tree0.begin(), tree0.end(), ref0.begin(), __cmp) ||
				!std::equal<
					ft::rb_tree<float>::const_iterator,
					std::set<float>::const_iterator,
					bool (*)(ft::rb_node<float> const &, float const &)>
					(tree1.begin(), tree1.end(), ref1.begin(), __cmp))
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
		__test_function_erase,
		__test_function_clear,
		__test_function_find,
		__test_function_swap,
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
