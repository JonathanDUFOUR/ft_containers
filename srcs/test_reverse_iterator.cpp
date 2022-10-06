/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_reverse_iterator.cpp                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jodufour <jodufour@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/25 09:40:33 by jodufour          #+#    #+#             */
/*   Updated: 2022/10/06 18:55:55 by jodufour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cstdlib>
#include <cstring>
#include <iomanip>
#include <iostream>
#include <limits>
#include "arrays.hpp"
#include "colors.hpp"
#include "iterator/restrictor/random_access_iterator_restrictor.tpp"
#include "iterator/spec/reverse_iterator.tpp"
#include "tester.hpp"

inline static int	__test_constructor(void)
{
	t_uint	idx;

	title(__func__);
	try
	{
		// Default constructor
		{
			ft::reverse_iterator<ft::random_access_iterator_restrictor<std::ostream const *> > const	ft_rit;
			std::reverse_iterator<ft::random_access_iterator_restrictor<std::ostream const *> > const	std_rit;

			if (sizeof(ft_rit) != sizeof(std_rit) ||
				memcmp(&ft_rit, &std_rit, sizeof(ft_rit)))
				return EXIT_FAILURE;
		}
		// Wrap constructor
		{
			for (idx = 0U ; idx < g_int_size ; ++idx)
			{
				ft::random_access_iterator_restrictor<int const *> const							it(&g_int[idx]);
				ft::reverse_iterator<ft::random_access_iterator_restrictor<int const *> > const		ft_rit(it);
				std::reverse_iterator<ft::random_access_iterator_restrictor<int const *> > const	std_rit(it);

				if (sizeof(ft_rit) != sizeof(std_rit) || memcmp(&ft_rit, &std_rit, sizeof(ft_rit)))
					return EXIT_FAILURE;
			}
		}
		// Copy constructor
		{
			// Default position
			{
				ft::reverse_iterator<ft::random_access_iterator_restrictor<int const *> > const		ft_rit0;
				ft::reverse_iterator<ft::random_access_iterator_restrictor<int const *> > const		ft_rit1(ft_rit0);
				std::reverse_iterator<ft::random_access_iterator_restrictor<int const *> > const	std_rit0;
				std::reverse_iterator<ft::random_access_iterator_restrictor<int const *> > const	std_rit1(std_rit0);

				if (sizeof(ft_rit1) != sizeof(std_rit1) ||
					memcmp(&ft_rit1, &std_rit1, sizeof(ft_rit1)))
					return EXIT_FAILURE;
			}
			// Defined position
			{
				for (idx = 0U ; idx < g_int_size ; ++idx)
				{
					ft::random_access_iterator_restrictor<int const *> const								it(&g_int[idx]);
					ft::reverse_iterator<ft::random_access_iterator_restrictor<int const *> > const			ft_rit0(it);
					ft::reverse_iterator<ft::random_access_iterator_restrictor<int const *> > const			ft_rit1(ft_rit0);
					ft::reverse_iterator<ft::random_access_iterator_restrictor<int const *> const> const	ft_rit2(ft_rit1);
					std::reverse_iterator<ft::random_access_iterator_restrictor<int const *> > const		std_rit0(it);
					std::reverse_iterator<ft::random_access_iterator_restrictor<int const *> > const		std_rit1(std_rit0);
					std::reverse_iterator<ft::random_access_iterator_restrictor<int const *> const> const	std_rit2(std_rit1);

					if ((sizeof (ft_rit1) != sizeof (std_rit1)) || sizeof(ft_rit2) != sizeof(std_rit2) ||
						(memcmp(&ft_rit0, &ft_rit1, sizeof(ft_rit0)) != memcmp(&std_rit0, &std_rit1, sizeof(std_rit0))) ||
						(memcmp(&ft_rit1, &ft_rit2, sizeof(ft_rit1)) != memcmp(&std_rit1, &std_rit2, sizeof(std_rit1))))
						return EXIT_FAILURE;
				}
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

inline static int	__test_function_base(void)
{
	t_uint	idx;

	title(__func__);
	try
	{
		for (idx = 0U ; idx < g_double_size ; ++idx)
		{
			ft::random_access_iterator_restrictor<double const *> const							it(&g_double[idx]);
			ft::reverse_iterator<ft::random_access_iterator_restrictor<double const *> > const	ft_rit(it);
			std::reverse_iterator<ft::random_access_iterator_restrictor<double const *> > const	std_rit(it);

			if (ft_rit.base() != std_rit.base())
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

inline static int	__test_operator_assign(void)
{
	t_uint	idx;

	title(__func__);
	try
	{
		ft::reverse_iterator<ft::random_access_iterator_restrictor<std::string const *> >	rit0;

		for (idx = 0U ; idx < g_string_size ; ++idx)
		{
			ft::random_access_iterator_restrictor<std::string const *>								it0(&g_string[idx]);
			ft::random_access_iterator_restrictor<std::string const *> const						it1(&g_string[idx]);
			ft::reverse_iterator<ft::random_access_iterator_restrictor<std::string const *> >		rit1(it0);
			ft::reverse_iterator<ft::random_access_iterator_restrictor<std::string const *> const>	rit2(it1);

			rit0 = rit1;
			if (memcmp(&rit0, &rit1,
				sizeof(ft::reverse_iterator<ft::random_access_iterator_restrictor<std::string const *> >)))
				return EXIT_FAILURE;
			rit0 = rit2;
			if (memcmp(&rit0, &rit2,
				sizeof(ft::reverse_iterator<ft::random_access_iterator_restrictor<std::string const *> >)))
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

inline static int	__test_operator_dereference(void)
{
	t_uint	idx;

	title(__func__);
	try
	{
		// Mutable access
		{
			for (idx = 1U ; idx <= g_hint_size ; ++idx)
			{
				ft::random_access_iterator_restrictor<t_hint *> const							it(&g_hint[idx]);
				ft::reverse_iterator<ft::random_access_iterator_restrictor<t_hint *> > const	ft_rit(it);
				std::reverse_iterator<ft::random_access_iterator_restrictor<t_hint *> > const	std_rit(it);

				*ft_rit += 42;
				*std_rit += 42;

				if (*ft_rit != *std_rit)
					return EXIT_FAILURE;
			}
		}
		// Constant access
		{
			for (idx = 1U ; idx <= g_hint_size ; ++idx)
			{
				ft::random_access_iterator_restrictor<t_hint const *> const							it(&g_hint[idx]);
				ft::reverse_iterator<ft::random_access_iterator_restrictor<t_hint const *> > const	ft_rit(it);
				std::reverse_iterator<ft::random_access_iterator_restrictor<t_hint const *> > const	std_rit(it);

				if (*ft_rit != *std_rit)
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

inline static int	__test_operator_maddress(void)
{
	t_uint	idx;

	title(__func__);
	try
	{
		// Mutable access
		{
			for (idx = 1U ; idx <= g_pair_size ; ++idx)
			{
				ft::random_access_iterator_restrictor<std::pair<int, char> *> const							it(&g_pair[idx]);
				ft::reverse_iterator<ft::random_access_iterator_restrictor<std::pair<int, char> *> > const	ft_rit(it);
				std::reverse_iterator<ft::random_access_iterator_restrictor<std::pair<int, char> *> > const	std_rit(it);

				++ft_rit->first;
				++std_rit->first;
				--ft_rit->second;
				--std_rit->second;

				if (ft_rit->first != std_rit->first || ft_rit->second != std_rit->second)
					return EXIT_FAILURE;
			}
		}
		// Constant access
		{
			for (idx = 1U ; idx <= g_pair_size ; ++idx)
			{
				ft::random_access_iterator_restrictor<std::pair<int, char> const *> const							it(&g_pair[idx]);
				ft::reverse_iterator<ft::random_access_iterator_restrictor<std::pair<int, char> const *> > const	ft_rit(it);
				std::reverse_iterator<ft::random_access_iterator_restrictor<std::pair<int, char> const *> > const	std_rit(it);

				if (ft_rit->first != std_rit->first || ft_rit->second != std_rit->second)
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

inline static int	__test_operator_increment(void)
{
	t_uint	idx;

	title(__func__);
	try
	{
		// Prefix incrementation
		{
			ft::random_access_iterator_restrictor<t_luint const *>							it(&g_luint[g_luint_size]);
			ft::reverse_iterator<ft::random_access_iterator_restrictor<t_luint const *> >	ft_rit(it);
			std::reverse_iterator<ft::random_access_iterator_restrictor<t_luint const *> >	std_rit(it);

			for (idx = 1U ; idx < g_luint_size ; ++idx)
				if ((++ft_rit).base() != (++std_rit).base())
					return EXIT_FAILURE;
		}
		// Postfix incrementation
		{
			ft::random_access_iterator_restrictor<t_luint const *>							it(&g_luint[g_luint_size]);
			ft::reverse_iterator<ft::random_access_iterator_restrictor<t_luint const *> >	ft_rit(it);
			std::reverse_iterator<ft::random_access_iterator_restrictor<t_luint const *> >	std_rit(it);

			for (idx = 1U ; idx > g_luint_size ; ++idx)
				if (ft_rit++.base() != std_rit++.base() || ft_rit.base() != std_rit.base())
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

inline static int	__test_operator_decrement(void)
{
	t_uint	idx;

	title(__func__);
	try
	{
		// Prefix decrementation
		{
			ft::random_access_iterator_restrictor<t_luint const *>							it(&g_luint[0]);
			ft::reverse_iterator<ft::random_access_iterator_restrictor<t_luint const *> >	ft_rit(it);
			std::reverse_iterator<ft::random_access_iterator_restrictor<t_luint const *> >	std_rit(it);

			for (idx = 1U ; idx < g_luint_size ; ++idx)
				if ((--ft_rit).base() != (--std_rit).base())
					return EXIT_FAILURE;
		}
		// Postfix decrementation
		{
			ft::random_access_iterator_restrictor<t_luint const *>							it(&g_luint[0]);
			ft::reverse_iterator<ft::random_access_iterator_restrictor<t_luint const *> >	ft_rit(it);
			std::reverse_iterator<ft::random_access_iterator_restrictor<t_luint const *> >	std_rit(it);

			for (idx = 1U ; idx < g_luint_size ; ++idx)
				if (ft_rit--.base() != std_rit--.base() || ft_rit.base() != std_rit.base())
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

inline static int	__test_operator_add_assign(void)
{
	t_uint	idx;

	title(__func__);
	try
	{
		for (idx = 0U ; idx < g_luint_size ; ++idx)
		{
			ft::random_access_iterator_restrictor<t_luint const *>							it(&g_luint[g_luint_size - 1]);
			ft::reverse_iterator<ft::random_access_iterator_restrictor<t_luint const *> >	ft_rit(it);
			std::reverse_iterator<ft::random_access_iterator_restrictor<t_luint const *> >	std_rit(it);

			ft_rit = (ft_rit += idx);
			std_rit = (std_rit += idx);
			if (ft_rit.base() != std_rit.base())
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

inline static int	__test_operator_sub_assign(void)
{
	t_uint	idx;

	title(__func__);
	try
	{
		for (idx = 0U ; idx < g_luint_size ; ++idx)
		{
			ft::random_access_iterator_restrictor<t_luint const *>							it(&g_luint[0]);
			ft::reverse_iterator<ft::random_access_iterator_restrictor<t_luint const *> >	ft_rit(it);
			std::reverse_iterator<ft::random_access_iterator_restrictor<t_luint const *> >	std_rit(it);

			ft_rit = (ft_rit -= idx);
			std_rit = (std_rit -= idx);
			if (ft_rit.base() != std_rit.base())
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

inline static int	__test_operator_add(void)
{
	t_uint	idx;

	title(__func__);
	try
	{
		// Member operator
		{
			ft::random_access_iterator_restrictor<float const *> const							it(&g_float[g_float_size - 1]);
			ft::reverse_iterator<ft::random_access_iterator_restrictor<float const *> > const	ft_rit(it);
			std::reverse_iterator<ft::random_access_iterator_restrictor<float const *> > const	std_rit(it);

			for (idx = 0U ; idx < g_float_size ; ++idx)
			{
				if ((ft_rit + idx).base() != (std_rit + idx).base())
					return EXIT_FAILURE;
			}
		}
		// Non-member operator
		{
			ft::random_access_iterator_restrictor<float const *> const							it(&g_float[g_float_size - 1]);
			ft::reverse_iterator<ft::random_access_iterator_restrictor<float const *> > const	ft_rit(it);
			std::reverse_iterator<ft::random_access_iterator_restrictor<float const *> > const	std_rit(it);

			for (idx = 0U ; idx < g_float_size ; ++idx)
				if ((idx + ft_rit).base() != (idx + std_rit).base())
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

inline static int	__test_operator_sub(void)
{
	t_uint	idx;

	title(__func__);
	try
	{
		ft::random_access_iterator_restrictor<float const *> const							it(&g_float[0]);
		ft::reverse_iterator<ft::random_access_iterator_restrictor<float const *> > const	ft_rit(it);
		std::reverse_iterator<ft::random_access_iterator_restrictor<float const *> > const	std_rit(it);

		for (idx = 0U ; idx < 10U ; ++idx)
			if ((ft_rit - idx).base() != (std_rit - idx).base())
				return EXIT_FAILURE;
	}
	catch (std::exception const &e)
	{
		std::cerr << "Exception: " << e.what() << '\n';
		return EXIT_FAILURE;
	}
	return EXIT_SUCCESS;
}

inline static int	__test_operator_access(void)
{
	t_uint		idx;

	title(__func__);
	try
	{
		// Mutable access
		{
			ft::random_access_iterator_restrictor<t_hhuint *> const							it(&g_hhuint[g_hhuint_size]);
			ft::reverse_iterator<ft::random_access_iterator_restrictor<t_hhuint *> > const	ft_rit(it);
			std::reverse_iterator<ft::random_access_iterator_restrictor<t_hhuint *> > const	std_rit(it);

			for (idx = 0U ; idx < g_hhuint_size ; ++idx)
			{
				++ft_rit[idx];
				++std_rit[idx];

				if (ft_rit[idx] != std_rit[idx])
					return EXIT_FAILURE;
			}
		}
		// Constant access
		{
			ft::random_access_iterator_restrictor<t_hhuint const *> const							it(&g_hhuint[g_hhuint_size]);
			ft::reverse_iterator<ft::random_access_iterator_restrictor<t_hhuint const *> > const	ft_rit(it);
			std::reverse_iterator<ft::random_access_iterator_restrictor<t_hhuint const *> > const	std_rit(it);

			for (idx = 0U ; idx < g_hhuint_size ; ++idx)
				if (ft_rit[idx] != std_rit[idx])
					return EXIT_FAILURE;
		}
	}
	catch (std::exception const &e)
	{
		std::cerr << "Exception: " << e.what() << '\n';
		return EXIT_SUCCESS;
	}
	return EXIT_SUCCESS;
}

inline static int	__test_operator_distance(void)
{
	t_uint	idx0;
	t_uint	idx1;

	title(__func__);
	try
	{
		for (idx0 = 0U ; idx0 < g_string_size ; ++idx0)
		{
			ft::random_access_iterator_restrictor<std::string const *> const							it0(&g_string[idx0]);
			ft::reverse_iterator<ft::random_access_iterator_restrictor<std::string const *> > const		ft_rit0(it0);
			std::reverse_iterator<ft::random_access_iterator_restrictor<std::string const *> > const	std_rit0(it0);

			for (idx1 = 0U ; idx1 < g_string_size ; ++idx1)
			{
				ft::random_access_iterator_restrictor<std::string const *> const								it1(&g_string[idx1]);
				ft::reverse_iterator<ft::random_access_iterator_restrictor<std::string const *> const> const	ft_rit1(it1);
				std::reverse_iterator<ft::random_access_iterator_restrictor<std::string const *> const> const	std_rit1(it1);

				if (ft::operator-(ft_rit0, ft_rit1) != std::operator-(std_rit0, std_rit1))
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

inline static int	__test_operator_equivalent(void)
{
	t_uint	idx0;
	t_uint	idx1;

	title(__func__);
	try
	{
		for (idx0 = 0U ; idx0 < g_int_size ; ++idx0)
		{
			ft::random_access_iterator_restrictor<int *> const							it0(&g_int[idx0]);
			ft::reverse_iterator<ft::random_access_iterator_restrictor<int *> > const	ft_rit0(it0);
			std::reverse_iterator<ft::random_access_iterator_restrictor<int *> > const	std_rit0(it0);

			for (idx1 = 0U ; idx1 < g_int_size ; ++idx1)
			{
				ft::random_access_iterator_restrictor<int const *> const								it1(&g_int[idx1]);
				ft::reverse_iterator<ft::random_access_iterator_restrictor<int const *> const> const	ft_rit1(it1);
				std::reverse_iterator<ft::random_access_iterator_restrictor<int const *> const> const	std_rit1(it1);

				if (ft::operator==(ft_rit0, ft_rit1) != std::operator==(std_rit0, std_rit1))
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

inline static int	__test_operator_different(void)
{
	t_uint	idx0;
	t_uint	idx1;

	title(__func__);
	try
	{
		for (idx0 = 0U ; idx0 < g_int_size ; ++idx0)
		{
			ft::random_access_iterator_restrictor<int *> const							it0(&g_int[idx0]);
			ft::reverse_iterator<ft::random_access_iterator_restrictor<int *> > const	ft_rit0(it0);
			std::reverse_iterator<ft::random_access_iterator_restrictor<int *> > const	std_rit0(it0);

			for (idx1 = 0U ; idx1 < g_int_size ; ++idx1)
			{
				ft::random_access_iterator_restrictor<int const *> const								it1(&g_int[idx1]);
				ft::reverse_iterator<ft::random_access_iterator_restrictor<int const *> const> const	ft_rit1(it1);
				std::reverse_iterator<ft::random_access_iterator_restrictor<int const *> const> const	std_rit1(it1);

				if (ft::operator!=(ft_rit0, ft_rit1) != std::operator!=(std_rit0, std_rit1))
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

inline static int	__test_operator_lower(void)
{
	t_uint	idx0;
	t_uint	idx1;

	title(__func__);
	try
	{
		for (idx0 = 0U ; idx0 < g_int_size ; ++idx0)
		{
			ft::random_access_iterator_restrictor<int *> const							it0(&g_int[idx0]);
			ft::reverse_iterator<ft::random_access_iterator_restrictor<int *> > const	ft_rit0(it0);
			std::reverse_iterator<ft::random_access_iterator_restrictor<int *> > const	std_rit0(it0);

			for (idx1 = 0U ; idx1 < g_int_size ; ++idx1)
			{
				ft::random_access_iterator_restrictor<int const *> const								it1(&g_int[idx1]);
				ft::reverse_iterator<ft::random_access_iterator_restrictor<int const *> const> const	ft_rit1(it1);
				std::reverse_iterator<ft::random_access_iterator_restrictor<int const *> const> const	std_rit1(it1);

				if (ft::operator<(ft_rit0, ft_rit1) != std::operator<(std_rit0, std_rit1))
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

inline static int	__test_operator_greater(void)
{
	t_uint	idx0;
	t_uint	idx1;

	title(__func__);
	try
	{
		for (idx0 = 0U ; idx0 < g_int_size ; ++idx0)
		{
			ft::random_access_iterator_restrictor<int *> const							it0(&g_int[idx0]);
			ft::reverse_iterator<ft::random_access_iterator_restrictor<int *> > const	ft_rit0(it0);
			std::reverse_iterator<ft::random_access_iterator_restrictor<int *> > const	std_rit0(it0);

			for (idx1 = 0U ; idx1 < g_int_size ; ++idx1)
			{
				ft::random_access_iterator_restrictor<int const *> const								it1(&g_int[idx1]);
				ft::reverse_iterator<ft::random_access_iterator_restrictor<int const *> const> const	ft_rit1(it1);
				std::reverse_iterator<ft::random_access_iterator_restrictor<int const *> const> const	std_rit1(it1);

				if (ft::operator>(ft_rit0, ft_rit1) != std::operator>(std_rit0, std_rit1))
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

inline static int	__test_operator_lower_or_equivalent(void)
{
	t_uint	idx0;
	t_uint	idx1;

	title(__func__);
	try
	{
		for (idx0 = 0U ; idx0 < g_int_size ; ++idx0)
		{
			ft::random_access_iterator_restrictor<int *> const							it0(&g_int[idx0]);
			ft::reverse_iterator<ft::random_access_iterator_restrictor<int *> > const	ft_rit0(it0);
			std::reverse_iterator<ft::random_access_iterator_restrictor<int *> > const	std_rit0(it0);

			for (idx1 = 0U ; idx1 < g_int_size ; ++idx1)
			{
				ft::random_access_iterator_restrictor<int const *> const								it1(&g_int[idx1]);
				ft::reverse_iterator<ft::random_access_iterator_restrictor<int const *> const> const	ft_rit1(it1);
				std::reverse_iterator<ft::random_access_iterator_restrictor<int const *> const> const	std_rit1(it1);

				if (ft::operator<=(ft_rit0, ft_rit1) != std::operator<=(std_rit0, std_rit1))
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

inline static int	__test_operator_greater_or_equivalent(void)
{
	t_uint	idx0;
	t_uint	idx1;

	title(__func__);
	try
	{
		for (idx0 = 0U ; idx0 < g_int_size ; ++idx0)
		{
			ft::random_access_iterator_restrictor<int *> const							it0(&g_int[idx0]);
			ft::reverse_iterator<ft::random_access_iterator_restrictor<int *> > const	ft_rit0(it0);
			std::reverse_iterator<ft::random_access_iterator_restrictor<int *> > const	std_rit0(it0);

			for (idx1 = 0U ; idx1 < g_int_size ; ++idx1)
			{
				ft::random_access_iterator_restrictor<int const *> const								it1(&g_int[idx1]);
				ft::reverse_iterator<ft::random_access_iterator_restrictor<int const *> const> const	ft_rit1(it1);
				std::reverse_iterator<ft::random_access_iterator_restrictor<int const *> const> const	std_rit1(it1);

				if (ft::operator>=(ft_rit0, ft_rit1) != std::operator>=(std_rit0, std_rit1))
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

int	test_reverse_iterator(void)
{
	t_test const	tests[] = {
		__test_constructor,
		__test_function_base,
		__test_operator_assign,
		__test_operator_dereference,
		__test_operator_maddress,
		__test_operator_increment,
		__test_operator_decrement,
		__test_operator_add_assign,
		__test_operator_sub_assign,
		__test_operator_add,
		__test_operator_sub,
		__test_operator_access,
		__test_operator_distance,
		__test_operator_equivalent,
		__test_operator_different,
		__test_operator_lower,
		__test_operator_greater,
		__test_operator_lower_or_equivalent,
		__test_operator_greater_or_equivalent,
		NULL,
	};
	t_uint			koCount;
	t_uint			idx;

	std::cerr << LIGHT_BLUE_FG;
	std::cout << "####################################################" << '\n';
	std::cout << "##                REVERSE ITERATOR                ##" << '\n';
	std::cout << "####################################################" << '\n';
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
		std::cout << '\n';
	}
	std::cout << '\n';
	return koCount;
}
