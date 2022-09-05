/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_rb_tree.cpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jodufour <jodufour@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/02 12:13:04 by jodufour          #+#    #+#             */
/*   Updated: 2022/09/05 19:00:47 by jodufour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cstdlib>
#include <iostream>
#include "arrays.hpp"
#include "rb_tree.tpp"
#include "tester.hpp"
#include "t_int.hpp"

inline static int	__test_constructor(void)
{
	title(__func__);
	try
	{
		// Default constructor with no argument
		{
			ft::rb_tree<int>	tree;
		}
		// Default constructor with one argument
		{
			ft::rb_node<int> *const	node0 = new ft::rb_node<int>(g_int[0]);
			ft::rb_node<int> *const	node1 = new ft::rb_node<int>(g_int[1]);
			ft::rb_node<int> *const	node2 = new ft::rb_node<int>(g_int[2]);

			node0->child[ft::LEFT] = node1;
			node1->parent = node0;
			node0->child[ft::RIGHT] = node2;
			node2->parent = node0;

			ft::rb_tree<int>	tree(node0);
		}
		// Copy constructor
		{
			ft::rb_node<int> *const	node0 = new ft::rb_node<int>(g_int[0]);
			ft::rb_node<int> *const	node1 = new ft::rb_node<int>(g_int[1]);
			ft::rb_node<int> *const	node2 = new ft::rb_node<int>(g_int[2]);
			ft::rb_node<int> *const	node3 = new ft::rb_node<int>(g_int[3]);
			ft::rb_node<int> *const	node4 = new ft::rb_node<int>(g_int[4]);

			node0->child[ft::RIGHT] = node1;
			node1->parent = node0;
			node0->child[ft::LEFT] = node2;
			node2->parent = node0;

			node1->child[ft::RIGHT] = node3;
			node3->parent = node1;

			node2->child[ft::LEFT] = node4;
			node4->parent = node2;

			ft::rb_tree<int>	tree0(node0);
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

inline static int	__test_function_size(void)
{
	title(__func__);
	try
	{
		// Empty tree
		{
			ft::rb_tree<std::string>	tree;

			if (tree.size() != 0LU)
				return EXIT_FAILURE;
		}
		// Non-empty tree
		{
			ft::rb_node<std::string> *const	node0 = new ft::rb_node<std::string>(g_string[0]);
			ft::rb_node<std::string> *const	node1 = new ft::rb_node<std::string>(g_string[1]);
			ft::rb_node<std::string> *const	node2 = new ft::rb_node<std::string>(g_string[2]);
			ft::rb_node<std::string> *const	node3 = new ft::rb_node<std::string>(g_string[3]);
			ft::rb_node<std::string> *const	node4 = new ft::rb_node<std::string>(g_string[4]);
			ft::rb_node<std::string> *const	node5 = new ft::rb_node<std::string>(g_string[5]);
			ft::rb_node<std::string> *const	node6 = new ft::rb_node<std::string>(g_string[6]);

			node0->child[ft::RIGHT] = node1;
			node1->parent = node0;
			node0->child[ft::LEFT] = node2;
			node2->parent = node0;

			node1->child[ft::RIGHT] = node3;
			node3->parent = node1;
			node1->child[ft::LEFT] = node4;
			node4->parent = node1;

			node2->child[ft::RIGHT] = node5;
			node5->parent = node2;
			node2->child[ft::LEFT] = node6;
			node6->parent = node2;

			ft::rb_tree<std::string>	tree(node0);

			if (tree.size() != 7LU)
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

inline static int	__test_function_begin(void)
{
	title(__func__);
	try
	{
		// Mutable access
		{
			// Empty tree
			{
				ft::rb_tree<void *>				tree;
				ft::rb_tree<void *>::iterator	it;

				it = tree.begin();

				if (it.base())
					return EXIT_FAILURE;
			}
			// One node tree
			{
				ft::rb_node<t_hint> *const		node0 = new ft::rb_node<t_hint>(g_hint[0]);
				ft::rb_tree<t_hint>				tree(node0);
				ft::rb_tree<t_hint>::iterator	it;

				it = tree.begin();

				if (it.base() != node0)
					return EXIT_FAILURE;
			}
			// Two nodes tree
			{
				ft::rb_node<t_luint> *const	node0 = new ft::rb_node<t_luint>(g_luint[0]);
				ft::rb_node<t_luint> *const	node1 = new ft::rb_node<t_luint>(g_luint[1]);

				node0->child[ft::RIGHT] = node1;
				node1->parent = node0;

				ft::rb_tree<t_luint>			tree(node0);
				ft::rb_tree<t_luint>::iterator	it;

				it = tree.begin();

				if (it.base() != node0)
					return EXIT_FAILURE;
			}
			// Many nodes tree
			{
				ft::rb_node<float> *const	node0 = new ft::rb_node<float>(g_float[0]);
				ft::rb_node<float> *const	node1 = new ft::rb_node<float>(g_float[1]);
				ft::rb_node<float> *const	node2 = new ft::rb_node<float>(g_float[2]);
				ft::rb_node<float> *const	node3 = new ft::rb_node<float>(g_float[3]);
				ft::rb_node<float> *const	node4 = new ft::rb_node<float>(g_float[4]);
				ft::rb_node<float> *const	node5 = new ft::rb_node<float>(g_float[5]);
				ft::rb_node<float> *const	node6 = new ft::rb_node<float>(g_float[6]);

				node0->child[ft::RIGHT] = node1;
				node1->parent = node0;
				node0->child[ft::LEFT] = node2;
				node2->parent = node0;

				node1->child[ft::RIGHT] = node3;
				node3->parent = node1;
				node1->child[ft::LEFT] = node4;
				node4->parent = node1;

				node2->child[ft::RIGHT] = node5;
				node5->parent = node2;
				node2->child[ft::LEFT] = node6;
				node6->parent = node2;

				ft::rb_tree<float>				tree(node0);
				ft::rb_tree<float>::iterator	it;

				it = tree.begin();

				if (it.base() != node6)
					return EXIT_FAILURE;
			}
			// Chaotic tree
			{
				ft::rb_node<char> *const	node0 = new ft::rb_node<char>(g_char[0]);
				ft::rb_node<char> *const	node1 = new ft::rb_node<char>(g_char[1]);
				ft::rb_node<char> *const	node2 = new ft::rb_node<char>(g_char[2]);
				ft::rb_node<char> *const	node3 = new ft::rb_node<char>(g_char[3]);
				ft::rb_node<char> *const	node4 = new ft::rb_node<char>(g_char[4]);
				ft::rb_node<char> *const	node5 = new ft::rb_node<char>(g_char[5]);
				ft::rb_node<char> *const	node6 = new ft::rb_node<char>(g_char[6]);
				ft::rb_node<char> *const	node7 = new ft::rb_node<char>(g_char[7]);
				ft::rb_node<char> *const	node8 = new ft::rb_node<char>(g_char[8]);
				ft::rb_node<char> *const	node9 = new ft::rb_node<char>(g_char[9]);

				node0->child[ft::RIGHT] = node6;
				node6->parent = node0;
				node0->child[ft::LEFT] = node1;
				node1->parent = node0;

				node1->child[ft::RIGHT] = node2;
				node2->parent = node1;

				node2->child[ft::RIGHT] = node3;
				node3->parent = node2;
				node2->child[ft::LEFT] = node5;
				node5->parent = node2;

				node3->child[ft::LEFT] = node4;
				node4->parent = node3;

				node5->child[ft::LEFT] = node7;
				node7->parent = node5;

				node7->child[ft::RIGHT] = node9;
				node9->parent = node7;
				node7->child[ft::LEFT] = node8;
				node8->parent = node7;

				ft::rb_tree<char>			tree(node0);
				ft::rb_tree<char>::iterator	it;

				it = tree.begin();

				if (it.base() != node1)
					return EXIT_FAILURE;
			}
		}
		// Constant access
		{
			// Empty tree
			{
				ft::rb_tree<void *> const			tree;
				ft::rb_tree<void *>::const_iterator	cit;

				cit = tree.begin();

				if (cit.base())
					return EXIT_FAILURE;
			}
			// One node tree
			{
				ft::rb_node<t_hint> *const			node0 = new ft::rb_node<t_hint>(g_hint[0]);
				ft::rb_tree<t_hint>					tree(node0);
				ft::rb_tree<t_hint>::const_iterator	cit;

				cit = tree.begin();

				if (cit.base() != node0)
					return EXIT_FAILURE;
			}
			// Two nodes tree
			{
				ft::rb_node<t_luint> *const	node0 = new ft::rb_node<t_luint>(g_luint[0]);
				ft::rb_node<t_luint> *const	node1 = new ft::rb_node<t_luint>(g_luint[1]);

				node0->child[ft::RIGHT] = node1;
				node1->parent = node0;

				ft::rb_tree<t_luint>					tree(node0);
				ft::rb_tree<t_luint>::const_iterator	cit;

				cit = tree.begin();

				if (cit.base() != node0)
					return EXIT_FAILURE;
			}
			// Many nodes tree
			{
				ft::rb_node<float> *const	node0 = new ft::rb_node<float>(g_float[0]);
				ft::rb_node<float> *const	node1 = new ft::rb_node<float>(g_float[1]);
				ft::rb_node<float> *const	node2 = new ft::rb_node<float>(g_float[2]);
				ft::rb_node<float> *const	node3 = new ft::rb_node<float>(g_float[3]);
				ft::rb_node<float> *const	node4 = new ft::rb_node<float>(g_float[4]);
				ft::rb_node<float> *const	node5 = new ft::rb_node<float>(g_float[5]);
				ft::rb_node<float> *const	node6 = new ft::rb_node<float>(g_float[6]);

				node0->child[ft::RIGHT] = node1;
				node1->parent = node0;
				node0->child[ft::LEFT] = node2;
				node2->parent = node0;

				node1->child[ft::RIGHT] = node3;
				node3->parent = node1;
				node1->child[ft::LEFT] = node4;
				node4->parent = node1;

				node2->child[ft::RIGHT] = node5;
				node5->parent = node2;
				node2->child[ft::LEFT] = node6;
				node6->parent = node2;

				ft::rb_tree<float>					tree(node0);
				ft::rb_tree<float>::const_iterator	cit;

				cit = tree.begin();

				if (cit.base() != node6)
					return EXIT_FAILURE;
			}
			// Chaotic tree
			{
				ft::rb_node<char> *const	node0 = new ft::rb_node<char>(g_char[0]);
				ft::rb_node<char> *const	node1 = new ft::rb_node<char>(g_char[1]);
				ft::rb_node<char> *const	node2 = new ft::rb_node<char>(g_char[2]);
				ft::rb_node<char> *const	node3 = new ft::rb_node<char>(g_char[3]);
				ft::rb_node<char> *const	node4 = new ft::rb_node<char>(g_char[4]);
				ft::rb_node<char> *const	node5 = new ft::rb_node<char>(g_char[5]);
				ft::rb_node<char> *const	node6 = new ft::rb_node<char>(g_char[6]);
				ft::rb_node<char> *const	node7 = new ft::rb_node<char>(g_char[7]);
				ft::rb_node<char> *const	node8 = new ft::rb_node<char>(g_char[8]);
				ft::rb_node<char> *const	node9 = new ft::rb_node<char>(g_char[9]);

				node0->child[ft::RIGHT] = node6;
				node6->parent = node0;
				node0->child[ft::LEFT] = node1;
				node1->parent = node0;

				node1->child[ft::RIGHT] = node2;
				node2->parent = node1;

				node2->child[ft::RIGHT] = node3;
				node3->parent = node2;
				node2->child[ft::LEFT] = node5;
				node5->parent = node2;

				node3->child[ft::LEFT] = node4;
				node4->parent = node3;

				node5->child[ft::LEFT] = node7;
				node7->parent = node5;

				node7->child[ft::RIGHT] = node9;
				node9->parent = node7;
				node7->child[ft::LEFT] = node8;
				node8->parent = node7;

				ft::rb_tree<char>					tree(node0);
				ft::rb_tree<char>::const_iterator	cit;

				cit = tree.begin();

				if (cit.base() != node1)
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
	title(__func__);
	try
	{
		// Mutable access
		{
			// Empty tree
			{
				ft::rb_tree<void *>				tree;
				ft::rb_tree<void *>::iterator	it;

				it = tree.end();

				if (it.base())
					return EXIT_FAILURE;
			}
			// One node tree
			{
				ft::rb_node<t_hint> *const		node0 = new ft::rb_node<t_hint>(g_hint[0]);
				ft::rb_tree<t_hint>				tree(node0);
				ft::rb_tree<t_hint>::iterator	it;

				it = tree.end();

				if ((--it).base() != node0)
					return EXIT_FAILURE;
			}
			// Two nodes tree
			{
				ft::rb_node<t_luint> *const	node0 = new ft::rb_node<t_luint>(g_luint[0]);
				ft::rb_node<t_luint> *const	node1 = new ft::rb_node<t_luint>(g_luint[1]);

				node0->child[ft::LEFT] = node1;
				node1->parent = node0;

				ft::rb_tree<t_luint>			tree(node0);
				ft::rb_tree<t_luint>::iterator	it;

				it = tree.end();

				if ((--it).base() != node0)
					return EXIT_FAILURE;
			}
			// Many nodes tree
			{
				ft::rb_node<float> *const	node0 = new ft::rb_node<float>(g_float[0]);
				ft::rb_node<float> *const	node1 = new ft::rb_node<float>(g_float[1]);
				ft::rb_node<float> *const	node2 = new ft::rb_node<float>(g_float[2]);
				ft::rb_node<float> *const	node3 = new ft::rb_node<float>(g_float[3]);
				ft::rb_node<float> *const	node4 = new ft::rb_node<float>(g_float[4]);
				ft::rb_node<float> *const	node5 = new ft::rb_node<float>(g_float[5]);
				ft::rb_node<float> *const	node6 = new ft::rb_node<float>(g_float[6]);

				node0->child[ft::RIGHT] = node1;
				node1->parent = node0;
				node0->child[ft::LEFT] = node2;
				node2->parent = node0;

				node1->child[ft::RIGHT] = node3;
				node3->parent = node1;
				node1->child[ft::LEFT] = node4;
				node4->parent = node1;

				node2->child[ft::RIGHT] = node5;
				node5->parent = node2;
				node2->child[ft::LEFT] = node6;
				node6->parent = node2;

				ft::rb_tree<float>				tree(node0);
				ft::rb_tree<float>::iterator	it;

				it = tree.end();

				if ((--it).base() != node3)
					return EXIT_FAILURE;
			}
			// Chaotic tree
			{
				ft::rb_node<char> *const	node0 = new ft::rb_node<char>(g_char[0]);
				ft::rb_node<char> *const	node1 = new ft::rb_node<char>(g_char[1]);
				ft::rb_node<char> *const	node2 = new ft::rb_node<char>(g_char[2]);
				ft::rb_node<char> *const	node3 = new ft::rb_node<char>(g_char[3]);
				ft::rb_node<char> *const	node4 = new ft::rb_node<char>(g_char[4]);
				ft::rb_node<char> *const	node5 = new ft::rb_node<char>(g_char[5]);
				ft::rb_node<char> *const	node6 = new ft::rb_node<char>(g_char[6]);
				ft::rb_node<char> *const	node7 = new ft::rb_node<char>(g_char[7]);
				ft::rb_node<char> *const	node8 = new ft::rb_node<char>(g_char[8]);
				ft::rb_node<char> *const	node9 = new ft::rb_node<char>(g_char[9]);

				node0->child[ft::RIGHT] = node1;
				node1->parent = node0;

				node1->child[ft::RIGHT] = node3;
				node3->parent = node1;
				node1->child[ft::LEFT] = node2;
				node2->parent = node1;

				node2->child[ft::RIGHT] = node4;
				node4->parent = node2;

				node4->child[ft::RIGHT] = node5;
				node5->parent = node4;

				node5->child[ft::RIGHT] = node6;
				node6->parent = node5;
				node5->child[ft::LEFT] = node7;
				node7->parent = node5;

				node7->child[ft::RIGHT] = node8;
				node8->parent = node7;

				node8->child[ft::RIGHT] = node9;
				node9->parent = node8;

				ft::rb_tree<char>			tree(node0);
				ft::rb_tree<char>::iterator	it;

				it = tree.end();

				if ((--it).base() != node3)
					return EXIT_FAILURE;
			}
		}
		// Constant access
		{
			// Empty tree
			{
				ft::rb_tree<void *> const			tree;
				ft::rb_tree<void *>::const_iterator	cit;

				cit = tree.end();

				if (cit.base())
					return EXIT_FAILURE;
			}
			// One node tree
			{
				ft::rb_node<t_hint> *const			node0 = new ft::rb_node<t_hint>(g_hint[0]);
				ft::rb_tree<t_hint> const			tree(node0);
				ft::rb_tree<t_hint>::const_iterator	cit;

				cit = tree.end();

				if ((--cit).base() != node0)
					return EXIT_FAILURE;
			}
			// Two nodes tree
			{
				ft::rb_node<t_luint> *const	node0 = new ft::rb_node<t_luint>(g_luint[0]);
				ft::rb_node<t_luint> *const	node1 = new ft::rb_node<t_luint>(g_luint[1]);

				node0->child[ft::LEFT] = node1;
				node1->parent = node0;

				ft::rb_tree<t_luint> const				tree(node0);
				ft::rb_tree<t_luint>::const_iterator	cit;

				cit = tree.end();

				if ((--cit).base() != node0)
					return EXIT_FAILURE;
			}
			// Many nodes tree
			{
				ft::rb_node<float> *const	node0 = new ft::rb_node<float>(g_float[0]);
				ft::rb_node<float> *const	node1 = new ft::rb_node<float>(g_float[1]);
				ft::rb_node<float> *const	node2 = new ft::rb_node<float>(g_float[2]);
				ft::rb_node<float> *const	node3 = new ft::rb_node<float>(g_float[3]);
				ft::rb_node<float> *const	node4 = new ft::rb_node<float>(g_float[4]);
				ft::rb_node<float> *const	node5 = new ft::rb_node<float>(g_float[5]);
				ft::rb_node<float> *const	node6 = new ft::rb_node<float>(g_float[6]);

				node0->child[ft::RIGHT] = node1;
				node1->parent = node0;
				node0->child[ft::LEFT] = node2;
				node2->parent = node0;

				node1->child[ft::RIGHT] = node3;
				node3->parent = node1;
				node1->child[ft::LEFT] = node4;
				node4->parent = node1;

				node2->child[ft::RIGHT] = node5;
				node5->parent = node2;
				node2->child[ft::LEFT] = node6;
				node6->parent = node2;

				ft::rb_tree<float> const			tree(node0);
				ft::rb_tree<float>::const_iterator	cit;

				cit = tree.end();

				if ((--cit).base() != node3)
					return EXIT_FAILURE;
			}
			// Chaotic tree
			{
				ft::rb_node<char> *const	node0 = new ft::rb_node<char>(g_char[0]);
				ft::rb_node<char> *const	node1 = new ft::rb_node<char>(g_char[1]);
				ft::rb_node<char> *const	node2 = new ft::rb_node<char>(g_char[2]);
				ft::rb_node<char> *const	node3 = new ft::rb_node<char>(g_char[3]);
				ft::rb_node<char> *const	node4 = new ft::rb_node<char>(g_char[4]);
				ft::rb_node<char> *const	node5 = new ft::rb_node<char>(g_char[5]);
				ft::rb_node<char> *const	node6 = new ft::rb_node<char>(g_char[6]);
				ft::rb_node<char> *const	node7 = new ft::rb_node<char>(g_char[7]);
				ft::rb_node<char> *const	node8 = new ft::rb_node<char>(g_char[8]);
				ft::rb_node<char> *const	node9 = new ft::rb_node<char>(g_char[9]);

				node0->child[ft::RIGHT] = node1;
				node1->parent = node0;

				node1->child[ft::RIGHT] = node3;
				node3->parent = node1;
				node1->child[ft::LEFT] = node2;
				node2->parent = node1;

				node2->child[ft::RIGHT] = node4;
				node4->parent = node2;

				node4->child[ft::RIGHT] = node5;
				node5->parent = node4;

				node5->child[ft::RIGHT] = node6;
				node6->parent = node5;
				node5->child[ft::LEFT] = node7;
				node7->parent = node5;

				node7->child[ft::RIGHT] = node8;
				node8->parent = node7;

				node8->child[ft::RIGHT] = node9;
				node9->parent = node8;

				ft::rb_tree<char> const				tree(node0);
				ft::rb_tree<char>::const_iterator	cit;

				cit = tree.end();

				if ((--cit).base() != node3)
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
	title(__func__);
	try
	{
		// Mutable access
		{
			// Empty tree
			{
				ft::rb_tree<void *>						tree;
				ft::rb_tree<void *>::reverse_iterator	rit;

				rit = tree.rbegin();

				if (rit.base().base())
					return EXIT_FAILURE;
			}
			// One node tree
			{
				ft::rb_node<t_hint> *const				node0 = new ft::rb_node<t_hint>(g_hint[0]);
				ft::rb_tree<t_hint>						tree(node0);
				ft::rb_tree<t_hint>::reverse_iterator	rit;

				rit = tree.rbegin();

				if (rit.base() != tree.end())
					return EXIT_FAILURE;
			}
			// Two nodes tree
			{
				ft::rb_node<t_luint> *const	node0 = new ft::rb_node<t_luint>(g_luint[0]);
				ft::rb_node<t_luint> *const	node1 = new ft::rb_node<t_luint>(g_luint[1]);

				node0->child[ft::LEFT] = node1;
				node1->parent = node0;

				ft::rb_tree<t_luint>					tree(node0);
				ft::rb_tree<t_luint>::reverse_iterator	rit;

				rit = tree.rbegin();

				if (rit.base() != tree.end())
					return EXIT_FAILURE;
			}
			// Many nodes tree
			{
				ft::rb_node<float> *const	node0 = new ft::rb_node<float>(g_float[0]);
				ft::rb_node<float> *const	node1 = new ft::rb_node<float>(g_float[1]);
				ft::rb_node<float> *const	node2 = new ft::rb_node<float>(g_float[2]);
				ft::rb_node<float> *const	node3 = new ft::rb_node<float>(g_float[3]);
				ft::rb_node<float> *const	node4 = new ft::rb_node<float>(g_float[4]);
				ft::rb_node<float> *const	node5 = new ft::rb_node<float>(g_float[5]);
				ft::rb_node<float> *const	node6 = new ft::rb_node<float>(g_float[6]);

				node0->child[ft::RIGHT] = node1;
				node1->parent = node0;
				node0->child[ft::LEFT] = node2;
				node2->parent = node0;

				node1->child[ft::RIGHT] = node3;
				node3->parent = node1;
				node1->child[ft::LEFT] = node4;
				node4->parent = node1;

				node2->child[ft::RIGHT] = node5;
				node5->parent = node2;
				node2->child[ft::LEFT] = node6;
				node6->parent = node2;

				ft::rb_tree<float>						tree(node0);
				ft::rb_tree<float>::reverse_iterator	rit;

				rit = tree.rbegin();

				if (rit.base() != tree.end())
					return EXIT_FAILURE;
			}
			// Chaotic tree
			{
				ft::rb_node<char> *const	node0 = new ft::rb_node<char>(g_char[0]);
				ft::rb_node<char> *const	node1 = new ft::rb_node<char>(g_char[1]);
				ft::rb_node<char> *const	node2 = new ft::rb_node<char>(g_char[2]);
				ft::rb_node<char> *const	node3 = new ft::rb_node<char>(g_char[3]);
				ft::rb_node<char> *const	node4 = new ft::rb_node<char>(g_char[4]);
				ft::rb_node<char> *const	node5 = new ft::rb_node<char>(g_char[5]);
				ft::rb_node<char> *const	node6 = new ft::rb_node<char>(g_char[6]);
				ft::rb_node<char> *const	node7 = new ft::rb_node<char>(g_char[7]);
				ft::rb_node<char> *const	node8 = new ft::rb_node<char>(g_char[8]);
				ft::rb_node<char> *const	node9 = new ft::rb_node<char>(g_char[9]);

				node0->child[ft::RIGHT] = node1;
				node1->parent = node0;

				node1->child[ft::RIGHT] = node3;
				node3->parent = node1;
				node1->child[ft::LEFT] = node2;
				node2->parent = node1;

				node2->child[ft::RIGHT] = node4;
				node4->parent = node2;

				node4->child[ft::RIGHT] = node5;
				node5->parent = node4;

				node5->child[ft::RIGHT] = node6;
				node6->parent = node5;
				node5->child[ft::LEFT] = node7;
				node7->parent = node5;

				node7->child[ft::RIGHT] = node8;
				node8->parent = node7;

				node8->child[ft::RIGHT] = node9;
				node9->parent = node8;

				ft::rb_tree<char>					tree(node0);
				ft::rb_tree<char>::reverse_iterator	rit;

				rit = tree.rbegin();

				if (rit.base() != tree.end())
					return EXIT_FAILURE;
			}
		}
		// Constant access
		{
			// Empty tree
			{
				ft::rb_tree<void *> const					tree;
				ft::rb_tree<void *>::const_reverse_iterator	crit;

				crit = tree.rbegin();

				if (crit.base().base())
					return EXIT_FAILURE;
			}
			// One node tree
			{
				ft::rb_node<t_hint> *const					node0 = new ft::rb_node<t_hint>(g_hint[0]);
				ft::rb_tree<t_hint> const					tree(node0);
				ft::rb_tree<t_hint>::const_reverse_iterator	crit;

				crit = tree.rbegin();

				if (crit.base() != tree.end())
					return EXIT_FAILURE;
			}
			// Two nodes tree
			{
				ft::rb_node<t_luint> *const	node0 = new ft::rb_node<t_luint>(g_luint[0]);
				ft::rb_node<t_luint> *const	node1 = new ft::rb_node<t_luint>(g_luint[1]);

				node0->child[ft::LEFT] = node1;
				node1->parent = node0;

				ft::rb_tree<t_luint> const						tree(node0);
				ft::rb_tree<t_luint>::const_reverse_iterator	crit;

				crit = tree.rbegin();

				if (crit.base() != tree.end())
					return EXIT_FAILURE;
			}
			// Many nodes tree
			{
				ft::rb_node<float> *const	node0 = new ft::rb_node<float>(g_float[0]);
				ft::rb_node<float> *const	node1 = new ft::rb_node<float>(g_float[1]);
				ft::rb_node<float> *const	node2 = new ft::rb_node<float>(g_float[2]);
				ft::rb_node<float> *const	node3 = new ft::rb_node<float>(g_float[3]);
				ft::rb_node<float> *const	node4 = new ft::rb_node<float>(g_float[4]);
				ft::rb_node<float> *const	node5 = new ft::rb_node<float>(g_float[5]);
				ft::rb_node<float> *const	node6 = new ft::rb_node<float>(g_float[6]);

				node0->child[ft::RIGHT] = node1;
				node1->parent = node0;
				node0->child[ft::LEFT] = node2;
				node2->parent = node0;

				node1->child[ft::RIGHT] = node3;
				node3->parent = node1;
				node1->child[ft::LEFT] = node4;
				node4->parent = node1;

				node2->child[ft::RIGHT] = node5;
				node5->parent = node2;
				node2->child[ft::LEFT] = node6;
				node6->parent = node2;

				ft::rb_tree<float> const					tree(node0);
				ft::rb_tree<float>::const_reverse_iterator	crit;

				crit = tree.rbegin();

				if (crit.base() != tree.end())
					return EXIT_FAILURE;
			}
			// Chaotic tree
			{
				ft::rb_node<char> *const	node0 = new ft::rb_node<char>(g_char[0]);
				ft::rb_node<char> *const	node1 = new ft::rb_node<char>(g_char[1]);
				ft::rb_node<char> *const	node2 = new ft::rb_node<char>(g_char[2]);
				ft::rb_node<char> *const	node3 = new ft::rb_node<char>(g_char[3]);
				ft::rb_node<char> *const	node4 = new ft::rb_node<char>(g_char[4]);
				ft::rb_node<char> *const	node5 = new ft::rb_node<char>(g_char[5]);
				ft::rb_node<char> *const	node6 = new ft::rb_node<char>(g_char[6]);
				ft::rb_node<char> *const	node7 = new ft::rb_node<char>(g_char[7]);
				ft::rb_node<char> *const	node8 = new ft::rb_node<char>(g_char[8]);
				ft::rb_node<char> *const	node9 = new ft::rb_node<char>(g_char[9]);

				node0->child[ft::RIGHT] = node1;
				node1->parent = node0;

				node1->child[ft::RIGHT] = node3;
				node3->parent = node1;
				node1->child[ft::LEFT] = node2;
				node2->parent = node1;

				node2->child[ft::RIGHT] = node4;
				node4->parent = node2;

				node4->child[ft::RIGHT] = node5;
				node5->parent = node4;

				node5->child[ft::RIGHT] = node6;
				node6->parent = node5;
				node5->child[ft::LEFT] = node7;
				node7->parent = node5;

				node7->child[ft::RIGHT] = node8;
				node8->parent = node7;

				node8->child[ft::RIGHT] = node9;
				node9->parent = node8;

				ft::rb_tree<char> const				tree(node0);
				ft::rb_tree<char>::const_reverse_iterator	crit;

				crit = tree.rbegin();

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
	title(__func__);
	try
	{
		// Mutable access
		{
			// Empty tree
			{
				ft::rb_tree<void *>						tree;
				ft::rb_tree<void *>::reverse_iterator	rit;

				rit = tree.rend();

				if (rit.base().base())
					return EXIT_FAILURE;
			}
			// One node tree
			{
				ft::rb_node<t_hint> *const				node0 = new ft::rb_node<t_hint>(g_hint[0]);
				ft::rb_tree<t_hint>						tree(node0);
				ft::rb_tree<t_hint>::reverse_iterator	rit;

				rit = tree.rend();

				if (rit.base() != tree.begin())
					return EXIT_FAILURE;
			}
			// Two nodes tree
			{
				ft::rb_node<t_luint> *const	node0 = new ft::rb_node<t_luint>(g_luint[0]);
				ft::rb_node<t_luint> *const	node1 = new ft::rb_node<t_luint>(g_luint[1]);

				node0->child[ft::RIGHT] = node1;
				node1->parent = node0;

				ft::rb_tree<t_luint>					tree(node0);
				ft::rb_tree<t_luint>::reverse_iterator	rit;

				rit = tree.rend();

				if (rit.base() != tree.begin())
					return EXIT_FAILURE;
			}
			// Many nodes tree
			{
				ft::rb_node<float> *const	node0 = new ft::rb_node<float>(g_float[0]);
				ft::rb_node<float> *const	node1 = new ft::rb_node<float>(g_float[1]);
				ft::rb_node<float> *const	node2 = new ft::rb_node<float>(g_float[2]);
				ft::rb_node<float> *const	node3 = new ft::rb_node<float>(g_float[3]);
				ft::rb_node<float> *const	node4 = new ft::rb_node<float>(g_float[4]);
				ft::rb_node<float> *const	node5 = new ft::rb_node<float>(g_float[5]);
				ft::rb_node<float> *const	node6 = new ft::rb_node<float>(g_float[6]);

				node0->child[ft::RIGHT] = node1;
				node1->parent = node0;
				node0->child[ft::LEFT] = node2;
				node2->parent = node0;

				node1->child[ft::RIGHT] = node3;
				node3->parent = node1;
				node1->child[ft::LEFT] = node4;
				node4->parent = node1;

				node2->child[ft::RIGHT] = node5;
				node5->parent = node2;
				node2->child[ft::LEFT] = node6;
				node6->parent = node2;

				ft::rb_tree<float>						tree(node0);
				ft::rb_tree<float>::reverse_iterator	rit;

				rit = tree.rend();

				if (rit.base() != tree.begin())
					return EXIT_FAILURE;
			}
			// Chaotic tree
			{
				ft::rb_node<char> *const	node0 = new ft::rb_node<char>(g_char[0]);
				ft::rb_node<char> *const	node1 = new ft::rb_node<char>(g_char[1]);
				ft::rb_node<char> *const	node2 = new ft::rb_node<char>(g_char[2]);
				ft::rb_node<char> *const	node3 = new ft::rb_node<char>(g_char[3]);
				ft::rb_node<char> *const	node4 = new ft::rb_node<char>(g_char[4]);
				ft::rb_node<char> *const	node5 = new ft::rb_node<char>(g_char[5]);
				ft::rb_node<char> *const	node6 = new ft::rb_node<char>(g_char[6]);
				ft::rb_node<char> *const	node7 = new ft::rb_node<char>(g_char[7]);
				ft::rb_node<char> *const	node8 = new ft::rb_node<char>(g_char[8]);
				ft::rb_node<char> *const	node9 = new ft::rb_node<char>(g_char[9]);

				node0->child[ft::RIGHT] = node6;
				node6->parent = node0;
				node0->child[ft::LEFT] = node1;
				node1->parent = node0;

				node1->child[ft::RIGHT] = node2;
				node2->parent = node1;

				node2->child[ft::RIGHT] = node3;
				node3->parent = node2;
				node2->child[ft::LEFT] = node5;
				node5->parent = node2;

				node3->child[ft::LEFT] = node4;
				node4->parent = node3;

				node5->child[ft::LEFT] = node7;
				node7->parent = node5;

				node7->child[ft::RIGHT] = node9;
				node9->parent = node7;
				node7->child[ft::LEFT] = node8;
				node8->parent = node7;

				ft::rb_tree<char>					tree(node0);
				ft::rb_tree<char>::reverse_iterator	rit;

				rit = tree.rend();

				if (rit.base() != tree.begin())
					return EXIT_FAILURE;
			}
		}
		// Constant access
		{
			// Empty tree
			{
				ft::rb_tree<void *> const					tree;
				ft::rb_tree<void *>::const_reverse_iterator	crit;

				crit = tree.rend();

				if (crit.base().base())
					return EXIT_FAILURE;
			}
			// One node tree
			{
				ft::rb_node<t_hint> *const					node0 = new ft::rb_node<t_hint>(g_hint[0]);
				ft::rb_tree<t_hint> const					tree(node0);
				ft::rb_tree<t_hint>::const_reverse_iterator	crit;

				crit = tree.rend();

				if (crit.base() != tree.begin())
					return EXIT_FAILURE;
			}
			// Two nodes tree
			{
				ft::rb_node<t_luint> *const	node0 = new ft::rb_node<t_luint>(g_luint[0]);
				ft::rb_node<t_luint> *const	node1 = new ft::rb_node<t_luint>(g_luint[1]);

				node0->child[ft::RIGHT] = node1;
				node1->parent = node0;

				ft::rb_tree<t_luint> const						tree(node0);
				ft::rb_tree<t_luint>::const_reverse_iterator	crit;

				crit = tree.rend();

				if (crit.base() != tree.begin())
					return EXIT_FAILURE;
			}
			// Many nodes tree
			{
				ft::rb_node<float> *const	node0 = new ft::rb_node<float>(g_float[0]);
				ft::rb_node<float> *const	node1 = new ft::rb_node<float>(g_float[1]);
				ft::rb_node<float> *const	node2 = new ft::rb_node<float>(g_float[2]);
				ft::rb_node<float> *const	node3 = new ft::rb_node<float>(g_float[3]);
				ft::rb_node<float> *const	node4 = new ft::rb_node<float>(g_float[4]);
				ft::rb_node<float> *const	node5 = new ft::rb_node<float>(g_float[5]);
				ft::rb_node<float> *const	node6 = new ft::rb_node<float>(g_float[6]);

				node0->child[ft::RIGHT] = node1;
				node1->parent = node0;
				node0->child[ft::LEFT] = node2;
				node2->parent = node0;

				node1->child[ft::RIGHT] = node3;
				node3->parent = node1;
				node1->child[ft::LEFT] = node4;
				node4->parent = node1;

				node2->child[ft::RIGHT] = node5;
				node5->parent = node2;
				node2->child[ft::LEFT] = node6;
				node6->parent = node2;

				ft::rb_tree<float> const					tree(node0);
				ft::rb_tree<float>::const_reverse_iterator	crit;

				crit = tree.rend();

				if (crit.base() != tree.begin())
					return EXIT_FAILURE;
			}
			// Chaotic tree
			{
				ft::rb_node<char> *const	node0 = new ft::rb_node<char>(g_char[0]);
				ft::rb_node<char> *const	node1 = new ft::rb_node<char>(g_char[1]);
				ft::rb_node<char> *const	node2 = new ft::rb_node<char>(g_char[2]);
				ft::rb_node<char> *const	node3 = new ft::rb_node<char>(g_char[3]);
				ft::rb_node<char> *const	node4 = new ft::rb_node<char>(g_char[4]);
				ft::rb_node<char> *const	node5 = new ft::rb_node<char>(g_char[5]);
				ft::rb_node<char> *const	node6 = new ft::rb_node<char>(g_char[6]);
				ft::rb_node<char> *const	node7 = new ft::rb_node<char>(g_char[7]);
				ft::rb_node<char> *const	node8 = new ft::rb_node<char>(g_char[8]);
				ft::rb_node<char> *const	node9 = new ft::rb_node<char>(g_char[9]);

				node0->child[ft::RIGHT] = node6;
				node6->parent = node0;
				node0->child[ft::LEFT] = node1;
				node1->parent = node0;

				node1->child[ft::RIGHT] = node2;
				node2->parent = node1;

				node2->child[ft::RIGHT] = node3;
				node3->parent = node2;
				node2->child[ft::LEFT] = node5;
				node5->parent = node2;

				node3->child[ft::LEFT] = node4;
				node4->parent = node3;

				node5->child[ft::LEFT] = node7;
				node7->parent = node5;

				node7->child[ft::RIGHT] = node9;
				node9->parent = node7;
				node7->child[ft::LEFT] = node8;
				node8->parent = node7;

				ft::rb_tree<char>							tree(node0);
				ft::rb_tree<char>::const_reverse_iterator	crit;

				crit = tree.rend();

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
	try
	{
		// TODO: Implement those tests
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
	try
	{
		// TODO: Implement those tests
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
	try
	{
		
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
	try
	{
		
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
		__test_function_size,
		__test_function_begin,
		__test_function_end,
		__test_function_rbegin,
		__test_function_rend,
		__test_type_iterator,
		__test_type_const_iterator,
		__test_type_reverse_iterator,
		__test_type_const_reverse_iterator,
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
	{
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
	}
	std::cout << '\n';
	return koCount;
}
