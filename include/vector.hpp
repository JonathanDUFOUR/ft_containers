/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jodufour <jodufour@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/27 10:42:42 by jodufour          #+#    #+#             */
/*   Updated: 2022/05/24 11:42:31 by jodufour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VECTOR_HPP
# define VECTOR_HPP

# include <memory>
# include "iterator/iterator_traits.hpp"
# include "iterator/RandomAccessIterator.tpp"
# include "iterator/ReverseIterator.tpp"

namespace ft
{
template <typename T, typename Alloc = typename std::allocator<T> >
class vector
{
public:
	// Member types
	typedef T													value_type;
	typedef Alloc												allocator_type;

	typedef typename allocator_type::pointer					pointer;
	typedef typename allocator_type::const_pointer				const_pointer;

	typedef typename allocator_type::reference					reference;
	typedef typename allocator_type::const_reference			const_reference;

	typedef class RandomAccessIterator<value_type>				iterator;
	typedef class RandomAccessIterator<value_type const>		const_iterator;

	typedef class ReverseIterator<iterator>						reverse_iterator;
	typedef class ReverseIterator<const_iterator>				const_reverse_iterator;

	typedef typename iterator_traits<iterator>::difference_type	difference_type;
	typedef std::size_t											size_type;

private:
	// Attributes
	allocator_type	_alloc;
	iterator		_head;
	iterator		_tail;
	size_type		_capacity;
	size_type		_size;

protected:
public:
	// Constructors
	explicit vector(allocator_type const &alloc = allocator_type()) :
		_alloc(alloc),
		_head(),
		_tail(),
		_capacity(0),
		_size(0) {}

	explicit vector(
		size_type n,
		value_type const &val = value_type(),
		allocator_type const &alloc = allocator_type()) :
		_alloc(alloc),
		_head(),
		_tail(),
		_capacity(0),
		_size(0)
	{
		this->assign(n, val);
	}

	template < typename InputIterator >
	vector(
		InputIterator first,
		InputIterator last,
		allocator_type const &alloc = allocator_type()) :
		_alloc(alloc),
		_head(),
		_tail(),
		_capacity(0),
		_size(0)
	{
		this->assign(first, last);
	}

	vector(vector const &src) :
		_alloc(src._alloc),
		_head(),
		_tail(),
		_capacity(0),
		_size(0)
	{
		this->assign(src.begin(), src.end());
	}

	// Destructors
	~vector(void)
	{
		this->clear();
	};

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
	void	swap(vector &other);

	bool	empty(void) const;

	iterator	begin(void);
	iterator	end(void);
	iterator	erase(iterator pos);
	iterator	erase(iterator first, iterator last);
	iterator	insert(iterator pos, value_type const &val);

	const_iterator	begin(void) const;
	const_iterator	end(void) const;

	reverse_iterator	rbegin(void);
	reverse_iterator	rend(void);

	const_reverse_iterator	rbegin(void) const;
	const_reverse_iterator	rend(void) const;

	size_type	capacity(void) const;
	size_type	max_size(void) const;
	size_type	size(void) const;

	reference	at(size_type n);
	reference	back(void);
	reference	front(void);
	
	const_reference	at(size_type n) const;
	const_reference	back(void) const;
	const_reference	front(void) const;

	allocator_type	get_allocator(void) const;

	// Operators
	vector			&operator=(vector const &rhs);
	
	reference		operator[](size_type n);
	
	const_reference	operator[](size_type n) const;
};
}

#endif
