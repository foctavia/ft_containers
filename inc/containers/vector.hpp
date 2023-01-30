/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: foctavia <foctavia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/24 12:23:40 by foctavia          #+#    #+#             */
/*   Updated: 2023/01/30 17:04:36 by foctavia         ###   ########.fr       */
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
	// vector
	
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

			// vector( void );
		
			explicit vector( const allocator_type &alloc = allocator_type() )
				: _first_elem( 0 ), _size( 0 ), _capacity( 0 ), _alloc( alloc ) { }
			
			explicit vector( size_type count, const value_type &value = value_type(), const allocator_type &alloc = allocator_type() )
				: _first_elem( 0 ), _size( 0 ), _capacity( 0 ), _alloc( alloc ) 
			{
				insert(begin(), count, value);
			}
			
			// // Check whether it's an integral type.  If so, it's not an iterator
			// template< class InputIt >
			// vector( InputIt first, InputIt last, typename ft::enable_if<!ft::is_integral<InputIt>::value, InputIt>::type* = 0, const allocator_type &alloc = allocator_type() )
			// 	: _first_elem( 0 ), _size( 0 ), _capacity( 0 ), _alloc( alloc ) 
			// {
			// 	insert(begin(), first, last);
			// }

			vector( vector const &src )
			{ *this = src; }

	// DESTRUCTOR
			
			~vector( void )
			{
				for (size_type i = 0; i < _size; i++)
					_alloc.destroy(_first_elem + i);
				_alloc.deallocate(_first_elem, _capacity);
			}

	// // ASSIGNMENT OPERATOR

	// 		vector					&operator=( vector const &rhs );

	// // MEMBER FUNCTIONS
	// 	// Member functions for Element access

	// 		reference				at( size_type pos );
	// 		const_reference			at( size_type pos ) const;

	// 		reference				operator[]( size_type pos );
	// 		const_reference			operator[]( size_type pos ) const;

	// 		reference				front( void );
	// 		const_reference			front( void ) const;

	// 		reference				back( void );
	// 		reference				back( void ) const;

	// 		value_type				*data( void );
	// 		const value_type		*data( void ) const;		

		// Member functions for Iterator

			iterator				begin( void ) { return iterator(this->_first_elem); }
			const_iterator			begin( void ) const { return const_iterator(this->_first_elem); }
			iterator				end( void ) { return iterator(this->_first_elem + _size); }
			const_iterator			end( void ) const { return const_iterator(this->_first_elem + _size); }

	// 		reverse_iterator		rbegin( void );
	// 		const_reverse_iterator	rbegin( void ) const;
	// 		reverse_iterator		rend( void );
	// 		const_reverse_iterator	rend( void ) const;

		// Member functions for Capacity

			bool					empty( void ) const { return begin() == end(); }
			
			size_type				size( void ) const { return this->_size; }

			size_type				max_size( void ) const { return this->_alloc.max_size(); }
			
			void					reserve( size_type new_cap )
			{
				if (new_cap > max_size())
					exit(1);
				if (new_cap > _capacity)
				{	
					pointer	copy = _copyVector(begin(), end(), new_cap * 2);
					_clearVector(begin(), end(), _capacity);
					this->_capacity = new_cap * 2;
					this->_first_elem = copy;
				}
			}
			
			size_type				capacity( void ) const { return this->_capacity; }

		// Member functions for Modifiers

	// 		void					clear( void);

	
			iterator				insert( iterator pos, const value_type &value )
			{
				// working implementation for 1 insert
				
				// size_type	distance = std::distance(begin(), pos);
				// if (empty() && !_capacity)
				// 	reserve(1);
				// else if (_size == _capacity)
				// 	reserve(_capacity + 1);

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

				insert(pos, 1, value);
				
				return (pos);
			}
			
			iterator				insert( iterator pos, size_type count, const value_type &value )
			{
				size_type	distance = std::distance(begin(), pos);
				
				if (empty() && !_capacity)
					reserve(count);
				else if (_size + count > _capacity)
					reserve(_capacity + count);
				
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
	
				return (pos);
			}
			
			// template< class InputIt >
			// iterator				insert( iterator pos, InputIt first, InputIt last , typename ft::enable_if<!ft::is_integral<InputIt>::value, InputIt>::type* = 0)
			// {
			// 	size_type	distance = std::distance(first, last);
	
			// 	for (size_type i = 0; i < distance; i++)
			// 	{
					
			// 		insert(pos, 1, *(last - i - 1));

			// 		for(iterator it = begin(); it != end(); ++it)
			// 			std::cout << *it << " ";
		
			// 		std::cout << std::endl;
			// 	}

			// 	return (pos);
			// }
			
	// 		iterator				erase( iterator pos );
	// 		Iterator				erase( iterator first, iterator last );
	// 		void					push_back( const value_type &value );
	// 		void					pop_back( void );
	// 		void					resize( size_type count );
	// 		void					resize( size_type count, value_type value = value_type() );
	// 		void					swap( vector &other );

	// 	// Other member functions

	// 		void					assign( size_type count, const value_type &value );
	// 		template< class InputIt >
	// 		void					assign( InputIt first, InputIt last );

	// 	// Getter

	// 		allocator_type			get_allocator( void ) const;
	
		private:

			value_type		*_first_elem;
			size_type		_size;
			size_type		_capacity;
			allocator_type	_alloc;

	// PRIVATE FUNCTIONS

			pointer	_castIteratorToPointer(iterator it)
			{
				size_t	distance = std::distance(begin(), it);
				pointer	p = _first_elem + distance;
				
				return (p);
			}
			
			pointer	_copyVector(iterator first, iterator last, size_t size)
				{
					pointer copy = _alloc.allocate(size);
					for (; first != last; ++first)
						_alloc.construct(copy, *first);
					
					return (copy);
				}
			
			void	_clearVector(iterator first, iterator last, size_t size)
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
			
	// NON-MEMBER FUNCTIONS
		
		// template< class T, class Allocator >
		// bool					operator==( const ft::vector<T, Allocator> &lhs, const ft::vector<T, Allocator> &rhs );
		// template< class T, class Allocator >
		// bool					operator!=( const ft::vector<T, Allocator> &lhs, const ft::vector<T, Allocator> &rhs );
		// template< class T, class Allocator >
		// bool					operator<( const ft::vector<T, Allocator> &lhs, const ft::vector<T, Allocator> &rhs );
		// template< class T, class Allocator >
		// bool					operator<=( const ft::vector<T, Allocator> &lhs, const ft::vector<T, Allocator> &rhs );
		// template< class T, class Allocator >
		// bool					operator>( const ft::vector<T, Allocator> &lhs, const ft::vector<T, Allocator> &rhs );
		// template< class T, class Allocator >
		// bool					operator>=( const ft::vector<T, Allocator> &lhs, const ft::vector<T, Allocator> &rhs );
			
	};
}

#endif
