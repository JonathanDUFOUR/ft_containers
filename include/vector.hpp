/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jodufour <jodufour@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/27 10:42:42 by jodufour          #+#    #+#             */
/*   Updated: 2022/05/22 16:50:25 by jodufour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VECTOR_HPP
# define VECTOR_HPP

# include <memory>
# include "iterator_traits.hpp"

namespace ft
{
template < typename Vector >
class VectorIterator
{
public:
	// Member types
	typedef std::random_access_iterator_tag	iterator_category;
	typedef typename Vector::value_type		value_type;
	typedef typename Vector::pointer		pointer;
	typedef typename Vector::reference		reference;
	typedef std::ptrdiff_t					difference_type;

private:
protected:
public:
};

template < typename Vector >
class VectorConstIterator
{
public:
private:
protected:
public:
};

template < typename Vector >
class VectorReverseIterator
{
public:
private:
protected:
public:
};

template < typename Vector >
class VectorConstReverseIterator
{
public:
private:
protected:
public:
};

template < typename T, typename Alloc = std::allocator<T> >
class vector
{
public:
	// Member types
	typedef T																			value_type;
	typedef Alloc																		allocator_type;

	typedef typename allocator_type::pointer											pointer;
	typedef typename allocator_type::const_pointer										const_pointer;

	typedef typename allocator_type::reference											reference;
	typedef typename allocator_type::const_reference									const_reference;

	typedef class VectorIterator< vector< value_type, allocator_type > >				iterator;
	typedef class VectorConstIterator< vector< value_type, allocator_type > >			const_iterator;

	typedef class VectorReverseIterator< vector < value_type, allocator_type > >		reverse_iterator;
	typedef class VectorConstReverseIterator< vector < value_type, allocator_type > >	const_reverse_iterator;

	typedef typename iterator_traits<iterator>::difference_type							difference_type;
	typedef std::size_t																	size_type;

private:
	// Attributes
	allocator_type	_alloc;
	pointer			_content;
	size_type		_capacity;
	size_type		_size;

protected:
public:
	// Constructors
	explicit vector(allocator_type const &alloc = allocator_type());
	explicit vector(
		size_type n,
		value_type const &val = value_type(),
		allocator_type const &alloc = allocator_type());
	template < typename InputIterator >
	vector(
		InputIterator first,
		InputIterator last,
		allocator_type const &alloc = allocator_type());
	vector(vector const &src);

	// Destructors
	~vector(void);

	// Member functions
	template < typename InputIterator >
	void	assign(InputIterator first, InputIterator last);
	void	assign(size_type n, value_type const &val);
	void	clear(void);
	template < typename InputIterator >
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
