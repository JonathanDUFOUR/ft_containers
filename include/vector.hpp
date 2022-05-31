/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jodufour <jodufour@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/27 10:42:42 by jodufour          #+#    #+#             */
/*   Updated: 2022/05/31 17:49:40 by jodufour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VECTOR_HPP
# define VECTOR_HPP

# include <cstring>
# include <memory>
# include "iterator/spec/vector_iterator.tpp"
# include "iterator/base/reverse_iterator.tpp"

namespace ft
{
template <typename T, typename Alloc = typename std::allocator<T> >
class vector
{
public:
	// Member types
	typedef T														value_type;
	typedef Alloc													allocator_type;

	typedef typename allocator_type::pointer						pointer;
	typedef typename allocator_type::const_pointer					const_pointer;

	typedef typename allocator_type::reference						reference;
	typedef typename allocator_type::const_reference				const_reference;

	typedef class ft::vector_iterator<pointer>						iterator;
	typedef class ft::vector_iterator<const_pointer>				const_iterator;

	typedef class ft::reverse_iterator<iterator>					reverse_iterator;
	typedef class ft::reverse_iterator<const_iterator>				const_reverse_iterator;

	typedef typename ft::iterator_traits<iterator>::difference_type	difference_type;
	typedef std::size_t												size_type;

private:
	// Attributes
	pointer	_head;
	pointer	_tail;
	pointer	_eos;

public:
// ************************************************************************** //
//                                Constructors                                //
// ************************************************************************** //

	/**
	 * @brief	Construct a new empty vector object.
	 * 			(default constructor)
	 * 
	 * @param	alloc An optional allocator to use for instanciation.
	 */
	explicit vector(
		allocator_type const &alloc __attribute__((unused)) = allocator_type()) :
		_head(NULL),
		_tail(NULL),
		_eos(NULL) {}

	/**
	 * @brief	Construct a new vector object with specific size and content.
	 * 			(fill constructor)
	 * 
	 * @param	n The number of elements to fill the vector with.
	 * @param	val The element value to fill the vector with.
	 */
	explicit vector(
		size_type n,
		value_type const &val = value_type(),
		allocator_type const &alloc __attribute__((unused)) = allocator_type()) :
		_head(NULL),
		_tail(NULL),
		_eos(NULL)
	{
		this->insert(iterator(), n, val);
	}

	/**
	 * @brief	Construct a new vector object with a range of iterators.
	 * 			The resulting vector will contain the elements
	 * 			from `first` included to `last` excluded.
	 * 			(range constructor)
	 * 
	 * @tparam	InputIterator The type of the iterators to use.
	 * 			(it must conform to the standard input iterator requirements)
	 * 
	 * @param	first The first element of the range.
	 * @param	last The last element of the range.
	 */
	template <typename InputIterator>
	vector(
		InputIterator const &first,
		InputIterator const &last,
		allocator_type const &alloc __attribute__((unused)) = allocator_type()) :
		_head(NULL),
		_tail(NULL),
		_eos(NULL)
	{
		this->insert(iterator(), first, last);
	}

	/**
	 * @brief	Construct a new vector object as a copy of another one.
	 * 			(copy constructor)
	 * 
	 * @param	src The vector to copy.
	 */
	vector(vector const &src) :
		_head(NULL),
		_tail(NULL),
		_eos(NULL)
	{
		this->insert(iterator(), src._head, src._tail);
	}

// ************************************************************************* //
//                                Destructors                                //
// ************************************************************************* //

	/**
	 * @brief	Destruct a vector object, releasing its related allocated memory.
	 * 			(destructor)
	 */
	~vector(void)
	{
		allocator_type().deallocate(this->_head, this->capacity());
	};

// ************************************************************************* //
//                          Public Member Functions                          //
// ************************************************************************* //

	/**
	 * @brief		Assign a new size and a new content to the vector.
	 * 				(fill assignation)
	 * 
	 * @param n		The new size of the vector.
	 * @param val	The new value to fill the vector with.
	 */
	void	assign(size_type const n, value_type const &val)
	{
		size_type	idx;

		if (n > this->size())
		{
			for (idx = 0U ; idx < this->size() ; ++idx)
				this->_head[idx] = val;
			this->insert(this->end(), n - this->size(), val);
		}
		else 
		{
			for (idx = 0U ; idx < n ; ++idx)
				this->_head[idx] = val;
			if (n < this->size())
				this->erase(this->begin() + n, this->end());
		}
	}

	/**
	 * @brief	Assign a new size and a new content to the vector
	 * 			using a range of iterators,
	 * 			from `first` included to `last` excluded.
	 * 			(range assignation)
	 * 
	 * @tparam	InputIterator The type of the iterators to use.
	 * 			(it must conform to the standard input iterator requirements)
	 * 
	 * @param	first The first element of the range.
	 * @param	last The last element of the range.
	 */
	template <typename InputIterator>
	void	assign(InputIterator first, InputIterator last)
	{
		
	}

	/**
	 * @brief	Destroy every element in the vector without deallocating them.
	 */
	void	clear(void)
	{
		allocator_type	alloc;

		for (--this->_tail ; this->_tail != this->_head ; --this->_tail)
			alloc.destroy(this->_tail);
		alloc.destroy(this->_tail);
	}

	/**
	 * @brief	Insert elements at a specific position
	 * 			using a range of iterators,
	 * 			from `first` included to `last` excluded.
	 * 			(range insertion)
	 * 
	 * @tparam	InputIterator The type of the iterators to use.
	 * 			(it must conform to the standard input iterator requirements)
	 * 
	 * @param	pos The position to insert the elements.
	 * @param	first The first element of the range.
	 * @param	last The last element of the range.
	 */
	template <typename InputIterator>
	void	insert(iterator pos, InputIterator first, InputIterator last)
	{
		
	}

	/**
	 * @brief	Insert elements at a specific position.
	 * 			(fill insertion)
	 * 
	 * @param	pos The position to insert the elements.
	 * @param	n The number of elements to insert.
	 * @param	val The element value to fill the vector with.
	 */
	void	insert(iterator pos, size_type n, value_type const &val)
	{
		
	}

	/**
	 * @brief	Destroy the last element in the vector without deallocating it.
	 */
	void	pop_back(void)
	{
		--this->_tail;
		allocator_type().destroy(this->_tail);
	}

	/**
	 * @brief	Append a new element at the end of the vector.
	 * 
	 * @param	val The element value to append.
	 */
	void	push_back(value_type const &val)
	{
		this->insert(this->end(), val);
	}

	/**
	 * @brief	Request for a minimum capacity of the vector.
	 * 			It may result in a reallocation of the content.
	 * 
	 * @param	n The minimum capacity to request.
	 */
	void	reserve(size_type n)
	{
		
	}

	/**
	 * @brief	Request for a new size of the vector.
	 * 			In case of a smaller size, the current content is truncated.
	 * 			In case of a greater size, the extra content is filled with `val`.
	 * 
	 * @param	n The new size of the vector.
	 * @param	val The value to fill the extra content with.
	 */
	void	resize(size_type n, value_type val = value_type())
	{
		
	}

	/**
	 * @brief	Swap the content of the given vector
	 * 			with the content of the current vector.
	 * 
	 * @param	other The vector to swap with.
	 */
	void	swap(vector &other)
	{
		
	}

	/**
	 * @brief	Check if the vector is empty.
	 * 
	 * @return	Either true if the vector is empty, or false if not.
	 */
	bool	empty(void) const
	{
		return this->_head == this->_tail;
	}

	/**
	 * @brief	Get an iterator to the first element of the vector.
	 * 
	 * @return	An iterator to the first element of the vector.
	 */
	iterator	begin(void)
	{
		return iterator(this->_head);
	}

	/**
	 * @brief	Get an iterator to the last element of the vector.
	 * 
	 * @return	An iterator to the last element of the vector.
	 */
	iterator	end(void)
	{
		return iterator(this->_tail);
	}

	/**
	 * @brief	Remove a single element from the vector.
	 * 			(single erase)
	 * 
	 * @param	pos The position of the element to remove.
	 * 
	 * @return	An iterator to the element after the removed one.
	 */
	iterator	erase(iterator const pos)
	{
		allocator_type().destroy(pos.operator->());
		memmove(
			pos.operator->(),
			pos.operator->() + 1,
			(this->_tail - pos.operator->() - 1) * sizeof(value_type));
	}

	/**
	 * @brief	Remove elements from the vector
	 * 			using a range of iterators,
	 * 			from `first` included to `last` excluded.
	 * 			(range erase)
	 * 
	 * @param	first The first element of the range.
	 * @param	last The last element of the range.
	 * 
	 * @return	An iterator to the element after the removed ones.
	 */
	iterator	erase(iterator const first, iterator const last)
	{
		allocator_type	alloc;
		iterator		it;

		for (it = first ; it != last ; ++it)
			alloc.destroy(it.operator->());
		memmove(
			first.operator->(),
			last.operator->(),
			(this->_tail - last.operator->()) * sizeof(value_type));
	}

	/**
	 * @brief	Insert an element at a specific position.
	 * 			(single insertion)
	 * 
	 * @param	pos The position to insert the element.
	 * @param	val The element to insert.
	 * 
	 * @return	An iterator to the inserted element.
	 */
	iterator	insert(iterator pos, value_type const &val)
	{
		difference_type const	idx = pos - this->begin();

		return iterator(this->_head + idx);
	}

	/**
	 * @brief	Get a const_iterator to the first element of the vector.
	 * 
	 * @return	A const_iterator to the first element of the vector.
	 */
	const_iterator	begin(void) const
	{
		return const_iterator(this->_head);
	}

	/**
	 * @brief	Get a const_iterator to the last element of the vector.
	 * 
	 * @return	A const_iterator to the last element of the vector.
	 */
	const_iterator	end(void) const
	{
		return const_iterator(this->_tail);
	}

	/**
	 * @brief	Get a reverse_iterator to the last element of the vector.
	 * 
	 * @return	A reverse_iterator to the last element of the vector.
	 */
	reverse_iterator	rbegin(void)
	{
		return reverse_iterator(this->end());
	}

	/**
	 * @brief	Get a reverse_iterator to the first element of the vector.
	 * 
	 * @return	A reverse_iterator to the first element of the vector.
	 */
	reverse_iterator	rend(void)
	{
		return reverse_iterator(this->begin());
	}

	/**
	 * @brief	Get a const_reverse_iterator to the last element of the vector.
	 * 
	 * @return	A const_reverse_iterator to the last element of the vector.
	 */
	const_reverse_iterator	rbegin(void) const
	{
		return const_reverse_iterator(this->end());
	}

	/**
	 * @brief	Get a const_reverse_iterator to the first element of the vector.
	 * 
	 * @return	A const_reverse_iterator to the first element of the vector.
	 */
	const_reverse_iterator	rend(void) const;

	/**
	 * @brief	Get the number of allocated memory in the vector.
	 * 
	 * @return	The number of allocated memory in the vector.
	 */
	size_type	capacity(void) const
	{
		return this->_eos - this->_head;
	}

	/**
	 * @brief	Get the maximum number of elements that can be stored in the vector.
	 * 
	 * @return The maximum number of elements that can be stored in the vector.
	 */
	size_type	max_size(void) const
	{
		return allocator_type().max_size();
	}

	/**
	 * @brief	Get the number of stored elements in the vector.
	 * 
	 * @return	The number of stored elements in the vector.
	 */
	size_type	size(void) const
	{
		return this->_tail - this->_head;
	}

	/**
	 * @brief	Access to an element of the vector.
	 * 
	 * @param	n The position of the element to access.
	 * 
	 * @return	The element at the given position.
	 */
	reference	at(size_type const n)
	{
		return *(this->_head + n);
	}

	/**
	 * @brief	Access to the last element of the vector.
	 * 
	 * @return	The last element of the vector.
	 */
	reference	back(void)
	{
		return *(this->_tail - 1);
	}

	/**
	 * @brief	Access to the first element of the vector.
	 * 
	 * @return	The first element of the vector.
	 */
	reference	front(void)
	{
		return *this->_head;
	}

	/**
	 * @brief	Access to a constant element of the vector.
	 * 
	 * @param	n The position of the element to access.
	 * 
	 * @return	The constant element at the given position.
	 */
	const_reference	at(size_type const n) const
	{
		return *(this->_head + n);
	}

	/**
	 * @brief	Access the constant last element of the vector.
	 * 
	 * @return	The constant last element of the vector.
	 */
	const_reference	back(void) const
	{
		return *(this->_tail - 1);
	}

	/**
	 * @brief	Access the constant first element of the vector.
	 * 
	 * @return	The constant first element of the vector.
	 */
	const_reference	front(void) const
	{
		return *this->_head;
	}

	/**
	 * @brief	Get an allocator_type object,
	 * 			corresponding to the one used in the vector.
	 * 
	 * @return	An allocator object.
	 */
	allocator_type	get_allocator(void) const
	{
		return allocator_type();
	}

// ************************************************************************* //
//                                 Operators                                 //
// ************************************************************************* //

	/**
	 * @brief	Replace the current content of the vector
	 * 			by an other vector one's.
	 * 			(copy assignation)
	 * 
	 * @param	rhs The right hand side vector to copy the content from.
	 * 
	 * @return	The assigned vector.
	 */
	vector			&operator=(vector const &rhs);

	/**
	 * @brief	Access to an element of the vector.
	 * 
	 * @param	idx The index of the element to get.
	 * 
	 * @return	The element at the given index.
	 */
	reference		operator[](size_type const idx);

	/**
	 * @brief	Access to a constant element of the vector.
	 * 
	 * @param	idx The index of the constant element to get.
	 * 
	 * @return	The constant element at the given index.
	 */
	const_reference	operator[](size_type const idx) const;
};
}

#endif
