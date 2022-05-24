/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   forward_iterator.hpp                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jodufour <jodufour@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/23 20:53:25 by jodufour          #+#    #+#             */
/*   Updated: 2022/05/23 23:38:47 by jodufour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FORWARD_ITERATOR_HPP
# define FORWARD_ITERATOR_HPP

# include "input_iterator.hpp"

namespace ft
{
template <typename T, typename Category = std::forward_iterator_tag>
class forward_iterator : public input_iterator<T, Category>
{
private:
protected:
public:
};
}

#endif
