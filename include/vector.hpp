/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jodufour <jodufour@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/27 10:42:42 by jodufour          #+#    #+#             */
/*   Updated: 2022/08/24 18:28:04 by jodufour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VECTOR_HPP
# define VECTOR_HPP

# include <cstring>
# include <memory>
# include "algorithm.hpp"
# include "iterator/spec/vector_iterator.tpp"
# include "iterator/base/reverse_iterator.tpp"
# include "type_traits.hpp"

namespace ft
{
template <typename T, typename Alloc = std::allocator<T> >
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

	typedef typename ft::vector_iterator<pointer>				iterator;
	typedef typename ft::vector_iterator<const_pointer>			const_iterator;

	typedef typename ft::reverse_iterator<iterator>				reverse_iterator;
	typedef typename ft::reverse_iterator<const_iterator>		const_reverse_iterator;

	typedef typename iterator_traits<iterator>::difference_type	difference_type;
	typedef size_t												size_type;

private:
	// Attributes
	pointer	_head;
	pointer	_tail;
	pointer	_endOfStorage;

// ************************************************************************** //
//                          Private Member Functions                          //
// ************************************************************************** //

	/**
	 * @brief	Copy elements from a location to another,
	 * 			using a range of pointers,
	 * 			from `first` included to `last` excluded,
	 * 			using either trivial copy if value_type is an integral type,
	 * 			or non-trivial copy if not.
	 * 
	 * @param	dst The destination location.
	 * @param	first The first element of the range.
	 * @param	last The last element of the range.
	 */
	inline void	_rangeMove(pointer dst, pointer first, pointer last)
		__attribute__((nonnull))
	{
		allocator_type	alloc;

		if (is_trivially_copyable<value_type>::value)
			memmove(dst, first, (last - first) * sizeof(value_type));
		else if (dst < first)
			for ( ; first != last ; ++first, ++dst)
			{
				alloc.construct(dst, *first);
				alloc.destroy(first);
			}
		else if (dst > first)
			for (dst += (last - first - 1), --first, --last ;
				first != last ;
				--last, --dst)
			{
				alloc.construct(dst, *last);
				alloc.destroy(last);
			}
	}

	/**
	 * @brief	Determine that the called insert() is a fill insertion,
	 * 			thanks to the fourth paramter type.
	 * 
	 * @tparam	U Any integral type.
	 * 
	 * @param	pos The position to insert the elements.
	 * @param	param1 The number of elements to insert.
	 * @param	param2 The element value to fill the vector with.
	 */
	template<typename U>
	inline void	_insertDispatch(
		iterator const pos,
		U const param1,
		U const param2,
		true_type const)
	{
		this->_insertFill(pos, param1, param2);
	}

	/**
	 * @brief	Determine that the called insert() is a range insertion,
	 * 			thanks to the fourth paramter type.
	 * 
	 * @tparam	U Any non-integral type.
	 * 
	 * @param	pos The position to insert the elements.
	 * @param	param1 The first element of the range to insert.
	 * @param	param2 The last element of the range to insert.
	 */
	template<typename U>
	inline void	_insertDispatch(
		iterator const pos,
		U const param1,
		U const param2,
		false_type const)
	{
		this->_insertRange(pos, param1, param2);
	}

	/**
	 * @brief	Insert elements at a specific position.
	 * 			(fill insertion)
	 * 
	 * @param	pos The position to insert the elements.
	 * @param	n The number of elements to insert.
	 * @param	val The element value to fill the vector with.
	 */
	inline void	_insertFill(
		iterator const pos,
		size_type const n,
		value_type const &val)
	{
		size_type const	offset = pos - this->begin();
		size_type		newCapacity;
		pointer			newHead;
		pointer			newTail;
		allocator_type	alloc;

		if (!n)
			return ;
		if (this->size() + n <= this->capacity())
		{
			this->_rangeMove(
				this->_head + offset + n,
				this->_head + offset,
				this->_tail);
			this->_tail += n;
		}
		else
		{
			newCapacity = this->size() * 2;
			if (newCapacity < this->size() + n)
				newCapacity = this->size() + n;
			newHead = alloc.allocate(newCapacity, this->_head);
			newTail = newHead + this->size() + n;
			if (this->_head)
			{
				this->_rangeMove(
					newHead,
					this->_head,
					pos.base());
				this->_rangeMove(
					newHead + offset + n,
					pos.base(),
					this->_tail);
				alloc.deallocate(this->_head, this->capacity());
			}
			this->_head = newHead;
			this->_tail = newTail;
			this->_endOfStorage = this->_head + newCapacity;
		}
		for (newHead = this->_head + offset, newTail = newHead + n ;
			newHead != newTail ;
			++newHead)
			alloc.construct(newHead, val);
	}

	/**
	 * @brief	Insert elements at a specific position
	 * 			using a range of iterators,
	 * 			from `first` included to `last` excluded.
	 * 			(range insertion)
	 * 
	 * @par		The call to _insertDispacth() instead of directly
	 * 			put the implementation in this one is for handle ambiguous
	 * 			call of an overload of insert().
	 * 
	 * @tparam	InputIterator The type of the iterators to use.
	 * 			(it must conform to the standard input iterator requirements)
	 * 
	 * @param	pos The position to insert the elements.
	 * @param	first The first element of the range.
	 * @param	last The last element of the range.
	 */
	template <typename InputIterator>
	void	_insertRange(
		iterator const pos,
		InputIterator first,
		InputIterator const last)
	{
		size_type const	offset = this->end() - pos;
		size_type		newCapacity;
		pointer			newHead;
		pointer			newTail;
		allocator_type	alloc;

		newCapacity = this->size() * 2;
		for ( ; first != last ; ++first)
		{
			if (this->size() < this->capacity())
			{
				this->_rangeMove(
					this->_tail - offset + 1,
					this->_tail - offset,
					this->_tail);
			}
			else
			{

				if (newCapacity < this->size() + 1)
					newCapacity = this->size() + 1;
				newHead = alloc.allocate(newCapacity, this->_head);
				newTail = newHead + this->size();
				if (this->_head)
				{
					this->_rangeMove(
						newHead,
						this->_head,
						this->_tail - offset);
					this->_rangeMove(
						newTail - offset + 1,
						this->_tail - offset,
						this->_tail);
					alloc.deallocate(this->_head, this->capacity());
				}
				this->_head = newHead;
				this->_tail = newTail;
				this->_endOfStorage = this->_head + newCapacity;
				++newCapacity;
			}
			alloc.construct(this->_tail - offset, *first);
			++this->_tail;
		}
	}

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
		_endOfStorage(NULL) {}

	/**
	 * @brief	Construct a new vector object with specific size and content.
	 * 			(fill constructor)
	 * 
	 * @param	n The number of elements to fill the vector with.
	 * @param	val The element value to fill the vector with.
	 */
	explicit vector(
		size_type const n,
		value_type const &val = value_type(),
		allocator_type const &alloc __attribute__((unused)) = allocator_type()) :
		_head(NULL),
		_tail(NULL),
		_endOfStorage(NULL)
	{
		this->_insertFill(iterator(), n, val);
	}

	/**
	 * @brief	Construct a new vector object with a range of iterators.
	 * 			The resulting vector will contain the elements
	 * 			from `first` included to `last` excluded.
	 * 			(range constructor)
	 * 
	 * @tparam	InputIterator Any type that fulfills
	 * 			the standard input iterator requirements.
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
		_endOfStorage(NULL)
	{
		this->_insertDispatch(iterator(),
			first,
			last,
			is_integral<InputIterator>());
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
		_endOfStorage(NULL)
	{
		this->insert(iterator(), src.begin(), src.end());
	}

// ************************************************************************* //
//                                Destructors                                //
// ************************************************************************* //

	/**
	 * @brief	Destroy a vector object,
	 * 			releasing its related allocated memory.
	 * 			(destructor)
	 */
	~vector(void)
	{
		this->clear();
		if (this->_head)
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
		this->clear();
		this->_insertFill(this->begin(), n, val);
	}

	/**
	 * @brief	Assign a new size and a new content to the vector
	 * 			using a range of iterators,
	 * 			from `first` included to `last` excluded.
	 * 			(range assignation)
	 * 
	 * @tparam	InputIterator Any type that fulfills
	 * 			the standard input iterator requirements.
	 * 
	 * @param	first The first element of the range.
	 * @param	last The last element of the range.
	 */
	template <typename InputIterator>
	void	assign(InputIterator const first, InputIterator const last)
	{
		this->clear();
		this->_insertDispatch(
			this->begin(),
			first,
			last,
			is_integral<InputIterator>());
	}

	/**
	 * @brief	Destroy every element in the vector without deallocating them.
	 */
	void	clear(void)
	{
		allocator_type	alloc;

		if (this->_head == this->_tail)
			return ;
		for (--this->_tail ; this->_tail != this->_head ; --this->_tail)
			alloc.destroy(this->_tail);
		alloc.destroy(this->_tail);
	}

	/**
	 * @brief	Insert elements at a specific position.
	 * 			(fill insertion)
	 * 
	 * @par		The call to _insertFill() instead of directly
	 * 			put the implementation in this one is for handle ambiguous
	 * 			call of an overload of insert().
	 * 
	 * @param	pos The position to insert the elements.
	 * @param	n The number of elements to insert.
	 * @param	val The element value to fill the vector with.
	 */
	void	insert(iterator const pos, size_type const n, value_type const &val)
	{
		this->_insertFill(pos, n, val);
	}

	/**
	 * @brief	Insert elements at a specific position
	 * 			using a range of iterators,
	 * 			from `first` included to `last` excluded.
	 * 			(range insertion)
	 * 
	 * @par		The call to _insertDispacth() instead of directly
	 * 			put the implementation in this one is for handle ambiguous
	 * 			call of an overload of insert().
	 * 
	 * @tparam	InputIterator The type of the iterators to use.
	 * 			(it must conform to the standard input iterator requirements)
	 * 
	 * @param	pos The position to insert the elements.
	 * @param	first The first element of the range.
	 * @param	last The last element of the range.
	 */
	template <typename InputIterator>
	void	insert(
		iterator const pos,
		InputIterator first,
		InputIterator const last)
	{
		this->_insertDispatch(pos, first, last, is_integral<InputIterator>());
	}

	/**
	 * @brief	Destroy the last element in the vector without deallocating it.
	 */
	void	pop_back(void)
	{
		if (this->_tail)
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
		this->_insertFill(this->end(), 1LU, val);
	}

	/**
	 * @brief	Request for a minimum capacity of the vector.
	 * 			It may result in a reallocation of the content.
	 * 
	 * @param	n The minimum capacity to request.
	 */
	void	reserve(size_type const n)
	{
		pointer			newHead;
		pointer			newTail;
		allocator_type	alloc;

		if (n <= this->capacity())
			return ;
		newHead = alloc.allocate(n, this->_head);
		newTail = newHead + this->size();
		this->_rangeMove(
			newHead,
			this->_head,
			this->_tail);
		alloc.deallocate(this->_head, this->capacity());
		this->_head = newHead;
		this->_tail = newTail;
		this->_endOfStorage = this->_head + n;
	}

	/**
	 * @brief	Request for a new size of the vector.
	 * 			In case of a smaller size, the current content is truncated.
	 * 			In case of a greater size, the extra content is filled with `val`.
	 * 			It may result in a reallocation of the content.
	 * 
	 * @param	n The new size of the vector.
	 * @param	val The value to fill the extra content with.
	 */
	void	resize(size_type const n, value_type const val = value_type())
	{
		if (n < this->size())
			this->erase(this->_head + n, this->end());
		else if (n > this->size())
			this->insert(this->end(), n - this->size(), val);
	}

	/**
	 * @brief	Swap the content of the given vector
	 * 			with the content of the current vector.
	 * 
	 * @param	other The vector to swap with.
	 */
	void	swap(vector &other)
	{
		ft::swap<pointer>(this->_head, other._head);
		ft::swap<pointer>(this->_tail, other._tail);
		ft::swap<pointer>(this->_endOfStorage, other._endOfStorage);
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
	 * @brief	Get an iterator to the post-last element of the vector.
	 * 
	 * @return	An iterator to the post-last element of the vector.
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
		return this->erase(pos, pos + 1);
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
			alloc.destroy(it.base());
		this->_rangeMove(first.base(), last.base(), this->_tail);
		this->_tail -= last - first;
		return first;
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
	iterator	insert(iterator const pos, value_type const &val)
	{
		size_type const	offset = pos - this->begin();

		this->insert(pos, 1LU, val);
		return this->begin() + offset;
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
	const_reverse_iterator	rend(void) const
	{
		return const_reverse_iterator(this->begin());
	}

	/**
	 * @brief	Get the number of allocated memory in the vector.
	 * 
	 * @return	The number of allocated memory in the vector.
	 */
	size_type	capacity(void) const
	{
		return this->_endOfStorage - this->_head;
	}

	/**
	 * @brief	Get the maximum number of elements that can be stored in the vector.
	 * 
	 * @return	The maximum number of elements that can be stored in the vector.
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
		return this->_head[n];
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
	vector			&operator=(vector const &rhs)
	{
		if (this != &rhs)
			this->assign(rhs.begin(), rhs.end());
		return *this;
	}

	/**
	 * @brief	Access to an element of the vector.
	 * 
	 * @param	idx The index of the element to get.
	 * 
	 * @return	The element at the given index.
	 */
	reference		operator[](size_type const idx)
	{
		return this->_head[idx];
	}

	/**
	 * @brief	Access to a constant element of the vector.
	 * 
	 * @param	idx The index of the constant element to get.
	 * 
	 * @return	The constant element at the given index.
	 */
	const_reference	operator[](size_type const idx) const
	{
		return this->_head[idx];
	}
	
};
}

#endif
