/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jodufour <jodufour@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/27 10:42:42 by jodufour          #+#    #+#             */
/*   Updated: 2022/05/20 07:23:33 by jodufour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VECTOR_HPP
# define VECTOR_HPP

# include <iterator>
# include <memory>

namespace ft
{
template <typename T, typename Alloc = std::allocator<T>>
class Vector
{
private:
	// Attributes
	value_type *_content;
	size_type _size;
	size_type _capacity;
protected:

public:
	// Member types
	typedef T												value_type;
	typedef Alloc											allocator_type;
	typedef allocator_type::reference						reference;
	typedef allocator_type::const_reference					const_reference;
	typedef allocator_type::pointer							pointer;
	typedef allocator_type::const_pointer					const_pointer;
	typedef class Iterator									iterator;
	typedef class ConstIterator								const_iterator;
	typedef std::reverse_iterator<iterator>					reverse_iterator;
	typedef std::reverse_iterator<const_iterator>			const_reverse_iterator;
	typedef std::iterator_traits<iterator>::difference_type	difference_type;
	typedef std::size_t										size_type;

	// Constructors
	explicit Vector(allocator_type const &alloc = allocator_type());
	explicit Vector(
		size_type n,
		value_type const &val = value_type(),
		allocator_type const &alloc = allocator_type());
	template <typename InputIterator>
	Vector(
		InputIterator first,
		InputIterator last,
		allocator_type const &alloc = allocator_type());
	Vector(Vector const &src);

	// Destructors
	~Vector(void);

	// Member functions
	template <typename InputIterator>
	void	assign(InputIterator first, InputIterator last);
	void	assign(size_type n, value_type const &val);
	void	clear(void);
	template <typename InputIterator>
	void	insert(iterator pos, InputIterator first, InputIterator last);
	void	insert(iterator pos, size_type n, value_type const &val);
	void	pop_back(void);
	void	push_back(value_type const &val);
	void	reserve(size_type n);
	void	resize(size_type n, value_type val = value_type());
	void	swap(Vector &other);

	bool	empty(void) const;

	iterator	begin(void) const;
	iterator	end(void) const;
	iterator	erase(iterator pos);
	iterator	erase(iterator first, iterator last);
	iterator	insert(iterator pos, value_type const &val);

	const_iterator	begin(void) const;
	const_iterator	end(void) const;

	reverse_iterator	rbegin(void) const;
	reverse_iterator	rend(void) const;

	const_reverse_iterator	rbegin(void) const;
	const_reverse_iterator	rend(void) const;

	size_type	capacity(void) const;
	size_type	max_size(void) const;
	size_type	size(void) const;

	reference	at(size_type n) const;
	reference	back(void) const;
	reference	front(void) const;
	
	const_reference	at(size_type n) const;
	const_reference	back(void) const;
	const_reference	front(void) const;

	allocator_type	get_allocator(void) const;

	// Operators
	Vector			&operator=(Vector const &rhs);
	
	reference		operator[](size_type n) const;
	
	const_reference	operator[](size_type n) const;
};
}

#endif
