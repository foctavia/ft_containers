/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: foctavia <foctavia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/24 12:23:40 by foctavia          #+#    #+#             */
/*   Updated: 2023/02/27 21:02:30 by foctavia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VECTOR_HPP
# define VECTOR_HPP

# include <algorithm>
# include <memory>
# include <stdexcept>
# include <iostream>
# include <new>

# include "type_traits.hpp"
# include "reverse_iterator.hpp"
# include "random_access_iterator.hpp"
# include "algorithm.hpp"

namespace ft
{
	/* VECTOR ***************************************************************************** */
	
	template< class T, class Allocator = std::allocator<T> >
	class vector
	{
		public:
		
			typedef T											value_type;
			typedef Allocator									allocator_type;
			
			typedef typename Allocator::size_type				size_type;
			typedef typename Allocator::difference_type			difference_type;
			
			typedef typename Allocator::reference				reference;
			typedef typename Allocator::const_reference			const_reference;
			typedef typename Allocator::pointer					pointer;
			typedef typename Allocator::const_pointer			const_pointer;
			
			typedef ft::random_access_iterator< pointer >		iterator;
			typedef ft::random_access_iterator< const_pointer >	const_iterator;
			
			typedef ft::reverse_iterator< iterator >			reverse_iterator;
			typedef ft::reverse_iterator< const_iterator >		const_reverse_iterator;
	

	// CONSTRUCTORS
		
			explicit vector( const allocator_type &alloc = allocator_type() )
				: _first_elem( 0 ), _size( 0 ), _capacity( 0 ), _alloc( alloc )
			{ }
			
			explicit vector( size_type count, const value_type &value = value_type(), const allocator_type &alloc = allocator_type() )
				: _first_elem( 0 ), _size( 0 ), _capacity( 0 ), _alloc( alloc ) 
			{
				this->insert(begin(), count, value);
			}
			
			// Check whether it's an integral type.  If so, it's not an iterator
			template< class InputIt >
			vector( InputIt first, InputIt last, typename ft::enable_if<!ft::is_integral<InputIt>::value, InputIt>::type* = 0, const allocator_type &alloc = allocator_type() )
				: _first_elem( 0 ), _size( 0 ), _capacity( 0 ), _alloc( alloc ) 
			{	
				_size = ft::distance(first, last);
				
				if (_size > max_size())
					throw std::length_error("vector");
					
				_first_elem = _alloc.allocate(_size);
				_capacity = _size;
				
				for(size_type i = 0; i < _size; i++)
					_alloc.construct(_first_elem + i, *(first++));
			}

			vector( vector const &src )
				: _first_elem( 0 ), _size( 0 ), _capacity( 0 ), _alloc( src._alloc ) 
			{
				*this = src;
			}

	// DESTRUCTOR
			
			~vector( void )
			{
				this->clear();
				this->_alloc.deallocate(this->_first_elem, this->_capacity);
			}

	// ASSIGNMENT OPERATOR

			vector					&operator=( vector const &rhs )
			{
				if (this != &rhs)
					this->assign(rhs.begin(), rhs.end());

				return *this;
			}
	

	// MEMBER FUNCTIONS

		// Getter

			allocator_type			get_allocator( void ) const			{ return this->_alloc; }

		// Member functions for Element access

			reference				operator[]( size_type pos )			{ return *(this->_first_elem + pos); }
			const_reference			operator[]( size_type pos ) const	{ return *(this->_first_elem + pos); }

			reference				at( size_type pos )
			{
				if (pos >= size())
					throw std::out_of_range("vector::at");
					
				return (*this)[pos];
			}
			
			const_reference			at( size_type pos ) const
			{
				if (pos >= size())
					throw std::out_of_range("vector::at");
					
				return (*this)[pos];
			}

			reference				front( void )				{ return *this->begin(); }
			const_reference			front( void ) const			{ return *this->begin(); }

			reference				back( void )				{ return *(this->_first_elem + this->_size - 1); }
			reference				back( void ) const			{ return *(this->_first_elem  + this->_size - 1); }

			value_type				*data( void )				{ return this->_first_elem; }
			const value_type		*data( void ) const			{ return this->_first_elem; }		

		// Member functions for Iterator

			iterator				begin( void )				{ return iterator(this->_first_elem); }
			const_iterator			begin( void ) const			{ return const_iterator(this->_first_elem); }
			
			iterator				end( void )					{ return iterator(this->_first_elem + this->_size); }
			const_iterator			end( void ) const			{ return const_iterator(this->_first_elem + this->_size); }
			
			reverse_iterator		rbegin( void )				{ return reverse_iterator(iterator(this->_first_elem + this->_size)); }
			const_reverse_iterator	rbegin( void ) const		{ return const_reverse_iterator(const_iterator(this->_first_elem + this->_size)); }

			reverse_iterator		rend( void )				{ return reverse_iterator(iterator(this->_first_elem)); }
			const_reverse_iterator	rend( void ) const			{ return const_reverse_iterator(const_iterator(this->_first_elem)); }

		// Member functions for Capacity

			bool					empty( void ) const			{ return this->_size == 0 && this->begin() == this->end(); }
			
			size_type				size( void ) const			{ return this->_size; }

			size_type				max_size( void ) const		{ return this->_alloc.max_size(); }
			
			size_type				capacity( void ) const		{ return this->_capacity; }
			
			void					reserve( size_type new_cap )
			{
				if (new_cap > max_size())
					throw std::length_error("vector::reserve");
				if (new_cap >= max_size())
					throw std::bad_alloc();
				if (new_cap > _capacity)
				{	
					pointer	copy = _upsizeVector(new_cap);
					_clearVector(begin(), end(), _capacity);
					_capacity = new_cap;
					_first_elem = copy;
				}
			}
			
		// Member functions for Modifiers

			iterator				insert( iterator pos, const value_type &value )
			{	
				return insert(pos, 1, value);
			}
			
			iterator				insert( iterator pos, size_type count, const value_type &value )
			{
				if (!count)
					return pos;
					
				size_type	distance = ft::distance(begin(), pos);

				if (_size + count > _capacity)
					reserve(_getNewCapacity(_size + count));

				if (_size)
				{
					pointer	src_end = _first_elem + _size;
					pointer dest_end = _first_elem + _size + count;
					ft::copy_backward(_first_elem + distance, src_end, dest_end);
				}
				
				pointer 	pos_p = _first_elem + distance;
				for (size_type i = 0; i < count; ++i)
					_alloc.construct(pos_p + i, value);

				_size += count;
	
				return iterator(_first_elem + distance);
			}
			
			template< class InputIt >
			void					insert( iterator pos, InputIt first, InputIt last, typename ft::enable_if<!ft::is_integral<InputIt>::value, InputIt>::type* = 0 )
			{
				typedef typename ft::iterator_traits< InputIt >::iterator_category	category;
				if (typeid(category) != typeid(std::input_iterator_tag))
				{
					size_type	distance = ft::distance(first, last);
					
					if (distance && distance >= max_size())
						return ;
				}

				for(; first != last; ++first)
					pos = insert(pos, 1, *first) + 1;

			}
			
			void					clear( void )
			{
				if (_size > 0)
				{	
					for (size_type i = 0; i < _size; i++)
						_alloc.destroy(_first_elem + i);
					_size = 0;
				}
			}
			
			iterator				erase( iterator pos )
			{
				size_type	distance = ft::distance(begin(), pos);
				
				if (distance >= _size)
					exit(1);

				return erase(pos, pos + 1);
			}
			
			
			iterator				erase( iterator first, iterator last )
			{
				size_type	first_dist = std::distance(begin(), first);
				size_type	last_dist = std::distance(begin(), last);
				size_type	count = std::distance(first, last);

				if (first_dist > _size || last_dist > _size || first_dist > last_dist)
					exit(1);
				if (count)
				{
					pointer 	first_p = _first_elem + first_dist;
					pointer		last_p = _first_elem + last_dist;
					
					for(size_type i = 0; i < count; i++)
						_alloc.destroy(first_p + i);
					for (; last_p != _first_elem + _size; ++first_p)
					{
						_alloc.construct(first_p, *last_p);
						_alloc.destroy(last_p);
						last_p++;
					}
					_size -= count;
				}
				return first;
			}
	
			void					push_back( const value_type &value )
			{
				reserve(_getNewCapacity(_size + 1));
				_alloc.construct(_first_elem + _size, value);
				_size++;
			}
	
			void					pop_back( void )
			{
				erase(end() - 1);
			}
			
			void					resize( size_type new_size, value_type value = value_type() )
			{
				if (new_size > max_size())
					throw std::length_error("vector::resize");
				if (new_size >= max_size())
					throw std::bad_alloc();
				if (new_size > _size)
					insert(end(), new_size - _size, value);
				else if (new_size < _size)
					erase(end() - (_size - new_size), end());
			}
	
			void					swap( vector &other )
			{
				size_type		tmp_size		= _size;
				size_type		tmp_capacity	= _capacity;
				pointer			tmp_first_elem	= _first_elem;
				allocator_type	tmp_alloc		= _alloc;

				this->_size						= other.size();
				this->_capacity					= other.capacity();
				this->_first_elem 				= other.data();
				this->_alloc					= other.get_allocator();

				other._size						= tmp_size;
				other._capacity					= tmp_capacity;
				other._first_elem				= tmp_first_elem;
				other._alloc					= tmp_alloc;
			}

		// Other member functions

			void					assign( size_type count, const value_type &value )
			{
				if (count > _capacity)
				{
					vector	tmp(count, value);
					tmp.swap(*this);
				}
				else
				{
					clear();
					insert(begin(), count, value);
				}
			}
			
			template< class InputIt >
			void					assign( InputIt first, InputIt last, typename ft::enable_if<!ft::is_integral<InputIt>::value, InputIt>::type* = 0 )
			{
				size_type	count = std::distance(first, last);
				
				if (count > _capacity)
				{
					vector	tmp(first, last);
					tmp.swap(*this);
				}
				else
				{
					clear();
					insert(begin(), first, last);
				}
			}
	
		private:

			pointer			_first_elem;
			size_type		_size;
			size_type		_capacity;
			allocator_type	_alloc;

	// PRIVATE FUNCTIONS

			size_type	_getNewCapacity( size_type new_size )
			{
				if (empty())
					return (new_size - _size);
				if (new_size <= _capacity)
					return _capacity;
				if (new_size <= _size * 2)
					return _size * 2;
					
				return new_size;
			}
			
			pointer		_upsizeVector( size_t new_cap )
				{
					pointer copy = _alloc.allocate(new_cap);
					
					for (size_type i = 0; i < _size; i++)
						_alloc.construct(copy + i, _first_elem[i]);
		
					return copy;
				}

			pointer		_castIteratorToPointer( iterator it )
			{
				size_t	distance = std::distance(begin(), it);
				pointer	p = _first_elem + distance;
				
				return p;
			}
			
			void		_clearVector( iterator first, iterator last, size_t size )
			{
				iterator	tmp_it = first;
				pointer		tmp_p = _castIteratorToPointer(first);
				
				for (; tmp_it != last; tmp_it++)
					_alloc.destroy(tmp_p++);
				_alloc.deallocate(_castIteratorToPointer(first), size);
			}
			
	};
	
	// NON-MEMBER FUNCTIONS
		
	template< class T, class Allocator >
	inline bool		operator==( const ft::vector<T, Allocator> &lhs, const ft::vector<T, Allocator> &rhs )
	{
		return (lhs.size() == rhs.size() && ft::equal(lhs.begin(), lhs.end(), rhs.begin()));
	}
	
	template< class T, class Allocator >
	inline bool		operator!=( const ft::vector<T, Allocator> &lhs, const ft::vector<T, Allocator> &rhs )
	{
		return !(lhs == rhs);
	}
	
	template< class T, class Allocator >
	inline bool		operator<( const ft::vector<T, Allocator> &lhs, const ft::vector<T, Allocator> &rhs )
	{
		return ft::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end());
	}
	
	template< class T, class Allocator >
	inline bool		operator<=( const ft::vector<T, Allocator> &lhs, const ft::vector<T, Allocator> &rhs )
	{
		return !(rhs < lhs);
	}
	
	template< class T, class Allocator >
	inline bool		operator>( const ft::vector<T, Allocator> &lhs, const ft::vector<T, Allocator> &rhs )
	{
		return rhs < lhs;
	}
	
	template< class T, class Allocator >
	inline bool		operator>=( const ft::vector<T, Allocator> &lhs, const ft::vector<T, Allocator> &rhs )
	{
		return !(lhs < rhs);
	}

	template< class T, class Allocator >
	inline void		swap( ft::vector< T, Allocator > &lhs, ft::vector< T, Allocator > &rhs )
	{
		lhs.swap(rhs);
	}
	
}

#endif
