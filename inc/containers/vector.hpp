/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: foctavia <foctavia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/24 12:23:40 by foctavia          #+#    #+#             */
/*   Updated: 2023/01/31 23:29:02 by foctavia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VECTOR_HPP
# define VECTOR_HPP

# include <algorithm>
# include <memory>
# include <stdexcept>
# include <type_traits.hpp>
# include <iterator_traits.hpp>
# include <reverse_iterator.hpp>
# include <random_access_iterator.hpp>
# include <iterator>
# include <iostream>

namespace ft
{
	/* VECTOR ***************************************************************************** */
	
	template< class T, class Allocator = std::allocator<T> >
	class vector
	{
		public:
		
			typedef T											value_type;
			typedef Allocator									allocator_type;
			
			typedef std::size_t									size_type;
			typedef std::ptrdiff_t								difference_type;
			
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
				this->insert(begin(), first, last);
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
				this->_alloc.deallocate(_first_elem, _capacity);
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

			allocator_type			get_allocator( void ) const	{ return this->_alloc; }

		// Member functions for Element access

			reference				operator[]( size_type pos )
			{
				if (pos >= size())
					exit(1); // to change with exception out_of_range;
				return *(_first_elem + pos);
			}
			
			const_reference			operator[]( size_type pos ) const
			{
				if (pos >= size())
					exit(1); // to change with exception out_of_range;
				return *(_first_elem + pos);
			}

			reference				at( size_type pos )			{ return (*this)[pos]; }
			const_reference			at( size_type pos ) const	{ return (*this)[pos]; }

			reference				front( void )				{ return *this->begin(); }
			const_reference			front( void ) const			{ return *this->begin(); }

			reference				back( void )				{ return *(this->end() - 1); }
			reference				back( void ) const			{ return *(this->end() - 1); }

			value_type				*data( void )				{ return _first_elem; }
			const value_type		*data( void ) const			{ return _first_elem; }		

		// Member functions for Iterator

			iterator				begin( void )				{ return iterator(_first_elem); }
			const_iterator			begin( void ) const			{ return const_iterator(_first_elem); }
			
			iterator				end( void )					{ return iterator(_first_elem + _size); }
			const_iterator			end( void ) const			{ return const_iterator(_first_elem + _size); }

			reverse_iterator		rbegin( void )				{ return reverse_iterator(_first_elem); }
			const_reverse_iterator	rbegin( void ) const		{ return const_reverse_iterator(_first_elem); }
			
			reverse_iterator		rend( void )				{ return reverse_iterator(_first_elem + _size); }
			const_reverse_iterator	rend( void ) const			{ return const_reverse_iterator(_first_elem + _size); }

		// Member functions for Capacity

			bool					empty( void ) const			{ return this->begin() == this->end(); }
			
			size_type				size( void ) const			{ return this->_size; }

			size_type				max_size( void ) const		{ return this->_alloc.max_size(); }
			
			size_type				capacity( void ) const		{ return this->_capacity; }
			
			void					reserve( size_type new_cap )
			{
				if (new_cap > max_size())
					exit(1); // to change with exception length_error
				if (new_cap > _capacity)
				{	
					pointer	copy = _upsizeVector(new_cap * 2);
					_clearVector(begin(), end(), _capacity);
					this->_capacity = new_cap * 2;
					this->_first_elem = copy;
				}
			}
			
		// Member functions for Modifiers

			iterator				insert( iterator pos, const value_type &value )
			{
				// size_type	distance = std::distance(begin(), pos);
				
				// reserve(_getNewCapacity(1));

				// pointer		end = _first_elem + _size;
				// pointer		last = end - 1;
				
				// for (; end != _first_elem + distance; --end)
				// {
				// 	_alloc.construct(end, *last );
				// 	_alloc.destroy(last);
				// 	last--;
				// }
				// _alloc.construct(_first_elem + distance, value);
				// _size++;
				
				return insert(pos, 1, value);
			}
			
			iterator				insert( iterator pos, size_type count, const value_type &value )
			{
				size_type	distance = std::distance(begin(), pos);
				
				reserve(_getNewCapacity(count));

				pointer		last = _first_elem + _size - 1;
				pointer 	pos_p = _first_elem + distance;

				if (_size)
				{
					for (pointer new_last = last + count; new_last != pos_p + count - 1; --new_last)
					{
						_alloc.construct(new_last, *last);
						_alloc.destroy(last);
						last--;
					}
				}
				for (size_type i = 0; i < count; i++)
				{
					_alloc.construct(pos_p + i, value);
					_size++;
				}
	
				return iterator(_first_elem + distance);
			}
			
			template< class InputIt >
			iterator				insert( iterator pos, InputIt first, InputIt last, typename ft::enable_if<!ft::is_integral<InputIt>::value, InputIt>::type* = 0)
			{
				size_type	distance = std::distance(begin(), pos);
				size_type	count = std::distance(first, last);

				reserve(_getNewCapacity(count));

				for(; first != last; last--)
					insert(iterator(_first_elem + distance), 1, *(last - 1));

				return iterator(_first_elem + distance);
			}
			
			void					clear( void)
			{
				if (_first_elem != NULL)
				{
					pointer	tmp = _first_elem;
					
					while (--_size)
						_alloc.destroy(tmp++);
				}
			}
			
			iterator				erase( iterator pos )
			{
				size_type	distance = std::distance(begin(), pos);
				
				if (distance >= _size)
					exit(1);
					
				// pointer 	pos_p = _first_elem + distance;
				// _alloc.destroy(pos_p);
				// _size--;
				
				// for (; pos_p != _first_elem + _size; ++pos_p)
				// {
				// 	_alloc.construct(pos_p, *(pos_p + 1));
				// 	_alloc.destroy(pos_p + 1);
				// }

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
					this->_size -= count;
				}
				return first;
			}
	
			void					push_back( const value_type &value )
			{
				reserve(_getNewCapacity(1));
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
					exit(1); // to be changed with length error exception
				if (new_size > _size)
					insert(end(), new_size - _size, value);
				else if (new_size < _size)
					erase(end() - (_size - new_size), end());
			}
	
			void					swap( vector &other )
			{
				pointer			tmp_first_elem	= _first_elem;
				size_type		tmp_size		= _size;
				size_type		tmp_capacity	= _capacity;
				allocator_type	tmp_alloc		= _alloc;

				this->_first_elem 				= other._first_elem;
				this->_size						= other._size;
				this->_capacity					= other._capacity;
				this->_alloc					= other._alloc;

				other._first_elem				= tmp_first_elem;
				other._size						= tmp_size;
				other._capacity					= tmp_capacity;
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

			size_type	_getNewCapacity(size_type count)
			{
				if ((empty() && !_capacity) || _size + count > _capacity)
					return (_capacity + count);
					
				return (_capacity);
			}
			
			pointer		_upsizeVector(size_t new_cap)
				{
					pointer copy = _alloc.allocate(new_cap);
					for (size_type i = 0; i < _size; i++)
						_alloc.construct(copy + i, _first_elem[i]);			
					return (copy);
				}

			pointer		_castIteratorToPointer(iterator it)
			{
				size_t	distance = std::distance(begin(), it);
				pointer	p = _first_elem + distance;
				
				return (p);
			}
			
			void		_clearVector(iterator first, iterator last, size_t size)
			{
				iterator	tmp_it = first;
				pointer		tmp_p = _castIteratorToPointer(first);
				
				for (; tmp_it != last; ++tmp_it)
					_alloc.destroy(++tmp_p);
				_alloc.deallocate(_castIteratorToPointer(first), size);
			}
			
			size_t	_getDistance(iterator first, iterator last)
			{
				size_t	i = 0;

				while (++first != last)
					i++;

				return i;
			}
			
	};
	
	// NON-MEMBER FUNCTIONS
		
		template< class T, class Allocator >
		inline bool		operator==( const ft::vector<T, Allocator> &lhs, const ft::vector<T, Allocator> &rhs )
		{
			return (lhs.size() == rhs.size() && std::equal(lhs.begin(), lhs.end(), rhs.begin())); // to be changed with ft::equal
		}
		
		template< class T, class Allocator >
		inline bool		operator!=( const ft::vector<T, Allocator> &lhs, const ft::vector<T, Allocator> &rhs )
		{
			return !(lhs == rhs);
		}
		
		template< class T, class Allocator >
		inline bool		operator<( const ft::vector<T, Allocator> &lhs, const ft::vector<T, Allocator> &rhs )
		{
			return std::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end()); // to be changed with ft::lexicographical
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
		
}

#endif
