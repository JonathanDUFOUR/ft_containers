/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   benchmark.hpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jodufour <jodufour@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/06 17:15:35 by jodufour          #+#    #+#             */
/*   Updated: 2022/10/06 19:20:14 by jodufour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BENCHMARK_HPP
# define BENCHMARK_HPP

# include <ctime>
# include <set>

extern clock_t				g_ft_start;
extern clock_t				g_std_start;
extern time_t				g_ft_duration;
extern time_t				g_std_duration;
extern std::set<float>		g_ratio;

void	benchmark_best_case(void);
void	benchmark_worst_case(void);
void	benchmark_average_case(void);

#endif
