/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jodufour <jodufour@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/27 10:42:42 by jodufour          #+#    #+#             */
/*   Updated: 2022/09/27 15:56:52 by jodufour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VECTOR_HPP
# define VECTOR_HPP

# include <cstring>
# include <memory>
# include "algorithm.hpp"
# include "iterator/spec/reverse_iterator.tpp"
# include "iterator/spec/vector_iterator.tpp"
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

	typedef typename allocator_type::const_pointer				const_pointer;
	typedef typename allocator_type::pointer					pointer;

	typedef typename allocator_type::const_reference			const_reference;
	typedef typename allocator_type::reference					reference;

	typedef vector_iterator<const_pointer>						const_iterator;
	typedef vector_iterator<pointer>							iterator;

	typedef reverse_iterator<const_iterator>					const_reverse_iterator;
	typedef reverse_iterator<iterator>							reverse_iterator;

	typedef typename iterator_traits<iterator>::difference_type	difference_type;
	typedef size_t												size_type;

private:
	// Attributes
	pointer	_head;
	pointer	_tail;
	pointer	_end_of_storage;

// ****************************************************************************************************************** //
//                                              Private Member Functions                                              //
// ****************************************************************************************************************** //

	/**
	 * @brief	Determine that the called insert() is a fill insertion, thanks to the fourth paramter type.
	 * 
	 * @tparam	U Any integral type.
	 * 
	 * @param	pos The position to insert the elements.
	 * @param	param1 The number of elements to insert.
	 * @param	param2 The element value to fill the vector with.
	 */
	template<typename U>
	inline void	_insertDispatch(iterator const pos, U const param1, U const param2, true_type const)
	{
		this->_insertFill(pos, param1, param2);
	}

	/**
	 * @brief	Determine that the called insert() is a range insertion, thanks to the fourth paramter type.
	 * 
	 * @tparam	U Any non-integral type.
	 * 
	 * @param	pos The position to insert the elements.
	 * @param	param1 The first element of the range to insert.
	 * @param	param2 The last element of the range to insert.
	 */
	template<typename U>
	inline void	_insertDispatch(iterator const pos, U const param1, U const param2, false_type const)
	{
		this->_insertRange(pos, param1, param2);
	}

	/**
	 * @brief	Insert elements at a specific position.
	 * 
	 * @param	pos The position to insert the elements.
	 * @param	n The number of elements to insert.
	 * @param	val The element value to fill the vector with.
	 */
	inline void	_insertFill(iterator const pos, size_type const n, value_type const &val)
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
			this->_rangeMove(this->_head + offset + n, this->_head + offset, this->_tail);
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
				this->_rangeMove(newHead, this->_head, pos.base());
				this->_rangeMove(newHead + offset + n, pos.base(), this->_tail);
				alloc.deallocate(this->_head, this->capacity());
			}
			this->_head = newHead;
			this->_tail = newTail;
			this->_end_of_storage = this->_head + newCapacity;
		}
		for (newHead = this->_head + offset, newTail = newHead + n ; newHead != newTail ; ++newHead)
			alloc.construct(newHead, val);
	}

	/**
	 * @brief	Insert elements at a specific position using a range of iterators,
	 * 			from `first` included to `last` excluded.
	 * 
	 * @tparam	InputIterator The type of the iterators to use.
	 * 			(it must conform to the standard input iterator requirements)
	 * 
	 * @param	pos The position to insert the elements.
	 * @param	first The first element of the range.
	 * @param	last The last element of the range.
	 */
	template <typename InputIterator>
	void	_insertRange(iterator const &pos, InputIterator first, InputIterator const last)
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
				this->_rangeMove(this->_tail - offset + 1, this->_tail - offset, this->_tail);
			else
			{

				if (newCapacity < this->size() + 1)
					newCapacity = this->size() + 1;
				newHead = alloc.allocate(newCapacity, this->_head);
				newTail = newHead + this->size();
				if (this->_head)
				{
					this->_rangeMove(newHead, this->_head, this->_tail - offset);
					this->_rangeMove(newTail - offset + 1, this->_tail - offset, this->_tail);
					alloc.deallocate(this->_head, this->capacity());
				}
				this->_head = newHead;
				this->_tail = newTail;
				this->_end_of_storage = this->_head + newCapacity;
				++newCapacity;
			}
			alloc.construct(this->_tail - offset, *first);
			++this->_tail;
		}
	}

	/**
	 * @brief	Copy elements from a location to another, using a range of pointers,
	 * 			from `first` included to `last` excluded,
	 * 			using either trivial copy if possible, or non-trivial copy if not.
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
			for (dst += (last - first - 1), --first, --last ; first != last ; --last, --dst)
			{
				alloc.construct(dst, *last);
				alloc.destroy(last);
			}
	}

public:
// ****************************************************************************************************************** //
//                                                    Constructors                                                    //
// ****************************************************************************************************************** //

	/**
	 * @brief	Construct a new empty vector object. (default constructor)
	 */
	explicit vector(allocator_type const & = allocator_type()) :
		_head(NULL),
		_tail(NULL),
		_end_of_storage(NULL) {}

	/**
	 * @brief	Construct a new vector object with specific size and content. (fill constructor)
	 * 
	 * @param	n The number of elements to fill the vector with.
	 * @param	val The element value to fill the vector with.
	 */
	explicit vector(size_type const n, value_type const &val = value_type(), allocator_type const & = allocator_type()) :
		_head(NULL),
		_tail(NULL),
		_end_of_storage(NULL)
	{
		this->_insertFill(iterator(), n, val);
	}

	/**
	 * @brief	Construct a new vector object using a range of iterators.
	 * 			The resulting vector will contain the elements from `first` included to `last` excluded.
	 * 			(range constructor)
	 * 
	 * @tparam	InputIterator The type of the iterators to use.
	 * 			(it must conform to the standard input iterator requirements)
	 * 
	 * @param	first The first element of the range.
	 * @param	last The last element of the range.
	 */
	template <typename InputIterator>
	vector(InputIterator first, InputIterator last, allocator_type const & = allocator_type()) :
		_head(NULL),
		_tail(NULL),
		_end_of_storage(NULL)
	{
		this->_insertDispatch(iterator(), first, last, is_integral<InputIterator>());
	}

	/**
	 * @brief	Construct a new vector object as a copy of another one. (copy constructor)
	 * 
	 * @param	src The vector to copy.
	 */
	vector(vector const &src) :
		_head(NULL),
		_tail(NULL),
		_end_of_storage(NULL)
	{
		this->_insertRange(iterator(), src.begin(), src.end());
	}

// ***************************************************************************************************************** //
//                                                    Destructors                                                    //
// ***************************************************************************************************************** //

	/**
	 * @brief	Destroy a vector object, releasing its related allocated memory. (destructor)
	 */
	~vector(void)
	{
		this->clear();
		if (this->_head)
			allocator_type().deallocate(this->_head, this->capacity());
	};

// ***************************************************************************************************************** //
//                                              Public Member Functions                                              //
// ***************************************************************************************************************** //

	/**
	 * @brief		Assign a new size and a new content to the vector. (fill assignation)
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
	 * @brief	Assign a new size and a new content to the vector, using a range of iterators,
	 * 			from `first` included to `last` excluded. (range assignation)
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
		this->clear();
		this->_insertDispatch(this->begin(), first, last, is_integral<InputIterator>());
	}

	/**
	 * @param	n The position of the element to access.
	 * 
	 * @return	The element at the given position.
	 */
	reference	at(size_type const n)
	{
		if (n >= this->size())
			throw std::out_of_range("vector::at");
		return this->_head[n];
	}

	/**
	 * @param	n The position of the constant element to access.
	 * 
	 * @return	The constant element at the given position.
	 */
	const_reference	at(size_type const n) const
	{
		if (n >= this->size())
			throw std::out_of_range("vector::at");
		return this->_head[n];
	}

	/**
	 * @return	The last element of the vector.
	 */
	reference	back(void)
	{
		return *(this->_tail - 1);
	}

	/**
	 * @return	The constant last element of the vector.
	 */
	const_reference	back(void) const
	{
		return *(this->_tail - 1);
	}

	/**
	 * @return	An iterator to the first element of the vector.
	 */
	iterator	begin(void)
	{
		return iterator(this->_head);
	}

	/**
	 * @return	A const_iterator to the first element of the vector.
	 */
	const_iterator	begin(void) const
	{
		return const_iterator(this->_head);
	}

	/**
	 * @return	The number of allocated memory in the vector.
	 */
	size_type	capacity(void) const
	{
		return this->_end_of_storage - this->_head;
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
	 * @return	Either true if the vector is empty, or false if not.
	 */
	bool	empty(void) const
	{
		return this->_head == this->_tail;
	}

	/**
	 * @return	An iterator to the post-last element of the vector.
	 */
	iterator	end(void)
	{
		return iterator(this->_tail);
	}

	/**
	 * @return	A const_iterator to the post-last element of the vector.
	 */
	const_iterator	end(void) const
	{
		return const_iterator(this->_tail);
	}

	/**
	 * @brief	Remove a single element from the vector. (single erase)
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
	 * @brief	Remove elements from the vector using a range of iterators,
	 * 			from `first` included to `last` excluded. (range erase)
	 * 
	 * @param	first The first element of the range.
	 * @param	last The last element of the range.
	 * 
	 * @return	An iterator to the element after the removed ones.
	 */
	iterator	erase(iterator const &first, iterator const &last)
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
	 * @return	The first element of the vector.
	 */
	reference	front(void)
	{
		return *this->_head;
	}

	/**
	 * @return	The constant first element of the vector.
	 */
	const_reference	front(void) const
	{
		return *this->_head;
	}

	/**
	 * @return	An allocator_type default object.
	 */
	allocator_type	get_allocator(void) const
	{
		return allocator_type();
	}

	/**
	 * @brief	Insert elements at a specific position. (fill insertion)
	 * 
	 * @par		The call to _insertFill() instead of directly put the implementation here
	 * 			is for handle ambiguous call of an overload of insert().
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
	 * @brief	Insert elements at a specific position using a range of iterators,
	 * 			from `first` included to `last` excluded. (range insertion)
	 * 
	 * @par		The call to _insertDispacth() instead of directly put the implementation here
	 * 			is for handle ambiguous call of an overload of insert().
	 * 
	 * @tparam	InputIterator The type of the iterators to use.
	 * 			(it must conform to the standard input iterator requirements)
	 * 
	 * @param	pos The position to insert the elements.
	 * @param	first The first element of the range.
	 * @param	last The last element of the range.
	 */
	template <typename InputIterator>
	void	insert(iterator const pos, InputIterator first, InputIterator last)
	{
		this->_insertDispatch(pos, first, last, is_integral<InputIterator>());
	}

	/**
	 * @brief	Insert an element at a specific position. (single insertion)
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
	 * @return	The maximum number of elements that can be stored in the vector.
	 */
	size_type	max_size(void) const
	{
		return allocator_type().max_size();
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
	 * @return	A reverse_iterator to the last element of the vector.
	 */
	reverse_iterator	rbegin(void)
	{
		return reverse_iterator(this->end());
	}

	/**
	 * @return	A const_reverse_iterator to the last element of the vector.
	 */
	const_reverse_iterator	rbegin(void) const
	{
		return const_reverse_iterator(this->end());
	}

	/**
	 * @return	A reverse_iterator to the first element of the vector.
	 */
	reverse_iterator	rend(void)
	{
		return reverse_iterator(this->begin());
	}

	/**
	 * @return	A const_reverse_iterator to the first element of the vector.
	 */
	const_reverse_iterator	rend(void) const
	{
		return const_reverse_iterator(this->begin());
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
		else if (n > alloc.max_size())
			throw std::length_error("vector::reserve");
		newHead = alloc.allocate(n, this->_head);
		newTail = newHead + this->size();
		this->_rangeMove(newHead, this->_head, this->_tail);
		alloc.deallocate(this->_head, this->capacity());
		this->_head = newHead;
		this->_tail = newTail;
		this->_end_of_storage = this->_head + n;
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
			this->_insertFill(this->end(), n - this->size(), val);
	}

	/**
	 * @return	The number of stored elements in the vector.
	 */
	size_type	size(void) const
	{
		return this->_tail - this->_head;
	}

	/**
	 * @brief	Swap the content of the given vector with the content of the current vector.
	 * 
	 * @param	other The vector to swap with.
	 */
	void	swap(vector &other)
	{
		ft::swap<pointer>(this->_head, other._head);
		ft::swap<pointer>(this->_tail, other._tail);
		ft::swap<pointer>(this->_end_of_storage, other._end_of_storage);
	}

// ***************************************************************************************************************** //
//                                                     Operators                                                     //
// ***************************************************************************************************************** //

	/**
	 * @brief	Assign a new content to the vector from another one's. (copy assignation)
	 * 
	 * @param	rhs The right hand side vector to copy the content from.
	 * 
	 * @return	The assigned vector.
	 */
	vector	&operator=(vector const &rhs)
	{
		if (this != &rhs)
			this->assign(rhs.begin(), rhs.end());
		return *this;
	}

	/**
	 * @param	idx The index of the element to get.
	 * 
	 * @return	The element at the given index.
	 */
	reference	operator[](size_type const idx)
	{
		return this->_head[idx];
	}

	/**
	 * @param	idx The index of the constant element to get.
	 * 
	 * @return	The constant element at the given index.
	 */
	const_reference	operator[](size_type const idx) const
	{
		return this->_head[idx];
	}

}; // class vector

/**
 * @brief	Check if two vector are equivalent.
 * 
 * @tparam	T The type of the elements stored in both of the vector.
 * @tparam	Alloc The allocator type used in both of the vector.
 * 
 * @param	lhs The left hand side vector to compare.
 * @param	rhs The right hand side vector to compare.
 * 
 * @return	Either true if the two vector are equivalent, or false if not.
 */
template <typename T, typename Alloc>
bool	operator==(vector<T, Alloc> const &lhs, vector<T, Alloc> const &rhs)
{
	return &lhs == &rhs || (lhs.size() == rhs.size() && ft::equal(lhs.begin(), lhs.end(), rhs.begin()));
}

/**
 * @brief	Check if two vector are different.
 * 
 * @tparam	T The type of the elements stored in both of the vector.
 * @tparam	Alloc The allocator type used in both of the vector.
 * 
 * @param	lhs The left hand side vector to compare.
 * @param	rhs The right hand side vector to compare.
 * 
 * @return	Either true if the two vector are different, or false if not.
 */
template <typename T, typename Alloc>
bool	operator!=(vector<T, Alloc> const &lhs, vector<T, Alloc> const &rhs)
{
	return !(lhs == rhs);
}

/**
 * @brief	Check if two vector are strictly lexiographicaly ordered.
 * 
 * @tparam	T The type of the elements stored in both of the vector.
 * @tparam	Alloc The allocator type used in both of the vector.
 * 
 * @param	lhs The left hand side vector to compare.
 * @param	rhs The right hand side vector to compare.
 * 
 * @return	Either true if the two vector are strictly lexiographicaly ordered, or false if not.
 */
template <typename T, typename Alloc>
bool	operator<(vector<T, Alloc> const &lhs, vector<T, Alloc> const &rhs)
{
	return ft::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end());
}

/**
 * @brief	Check if two vector are strictly lexiographicaly reverse-ordered.
 * 
 * @tparam	T The type of the elements stored in both of the vector.
 * @tparam	Alloc The allocator type used in both of the vector.
 * 
 * @param	lhs The left hand side vector to compare.
 * @param	rhs The right hand side vector to compare.
 * 
 * @return	Either true if the two vector are strictly lexiographicaly reverse-ordered, or false if not.
 */
template <typename T, typename Alloc>
bool	operator>(vector<T, Alloc> const &lhs, vector<T, Alloc> const &rhs)
{
	return rhs < lhs;
}

/**
 * @brief	Check if two vector are lexiographicaly ordered or equivalent.
 * 
 * @tparam	T The type of the elements stored in both of the vector.
 * @tparam	Alloc The allocator type used in both of the vector.
 * 
 * @param	lhs The left hand side vector to compare.
 * @param	rhs The right hand side vector to compare.
 * 
 * @return	Either true if the two vector are lexiographicaly ordered or equivalent, or false if not.
 */
template <typename T, typename Alloc>
bool	operator<=(vector<T, Alloc> const &lhs, vector<T, Alloc> const &rhs)
{
	return !(rhs < lhs);
}

/**
 * @brief	Check if two vector are lexiographicaly reverse-ordered or equivalent.
 * 
 * @tparam	T The type of the elements stored in both of the vector.
 * @tparam	Alloc The allocator type used in both of the vector.
 * 
 * @param	lhs The left hand side vector to compare.
 * @param	rhs The right hand side vector to compare.
 * 
 * @return	Either true if the two vector are lexiographicaly reverse-ordered or equivalent, or false if not.
 */
template <typename T, typename Alloc>
bool	operator>=(vector<T, Alloc> const &lhs, vector<T, Alloc> const &rhs)
{
	return !(lhs < rhs);
}

// ***************************************************************************************************************** //
//                                               Specialized Functions                                               //
// ***************************************************************************************************************** //

/**
 * @brief	Swap the contents of two given vector.
 * 
 * @tparam	T The type of the elements stored in both of the vector.
 * @tparam	Alloc The allocator type used in both of the vector.
 * 
 * @param	a The first vector to swap.
 * @param	b The second vector to swap.
 */
template <typename T, typename Alloc>
void	swap(vector<T, Alloc> &a, vector<T, Alloc> &b)
{
	a.swap(b);
}

} // namespace ft

#endif
