/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: foctavia <foctavia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/24 12:23:40 by foctavia          #+#    #+#             */
/*   Updated: 2023/01/27 18:38:53 by foctavia         ###   ########.fr       */
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
				: _first_elem( 0 ), _last_elem( 0 ), _end_of_strorage( 0 ), _size( 0 ), _capacity( 0 ), _alloc( alloc ) { }
			
			// explicit vector( size_type count, const value_type &value = value_type(), const allocator_type &alloc = allocator_type() )
			// 	: _size( count ), _capacity( count ), _alloc( alloc ) 
			// {
				
			// }
			
			// // Check whether it's an integral type.  If so, it's not an iterator
			// template< class InputIt >
			// vector( InputIt first, InputIt last, typename ft::enable_if<!ft::is_integral<InputIt>::value, InputIt>::type* = 0, const allocator_type &alloc = allocator_type() )
			// 	: _alloc( alloc )
			// {
			// 	this->_size = std::distance(first, last);
			// 	this->_capacity = this->_size;
			// 	this->_first_elem = this->_alloc.allocate(this->_capacity);
			// 	this->_last_elem = _first_elem + _size;
			// 	this->_end_of_strorage = _first_elem + _capacity;
			// 	// for(pointer tmp = _first_elem; tmp != _last_elem; tmp++)
			// 	// 	this->_alloc.construct(_first_elem, value);
			// }

			vector( vector const &src )
			{ *this = src; }

	// DESTRUCTOR
			
			~vector( void )
			{
				if (this->_first_elem)
					this->_alloc.deallocate(this->_first_elem, this->_capacity);
				this->_alloc.destroy(this->_first_elem);
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

			bool					empty( void ) const { return _size == 0; }
			
			size_type				size( void ) const { return this->_size; }

			size_type				max_size( void ) const { return this->_alloc.max_size(); }
			
			void					reserve( size_type new_cap )
			{
				if (new_cap > this->max_size())
					exit(1);
				if (this->capacity < new_cap)
				{	
					this->_alloc.deallocate(this->_first_elem, this->_capacity);
					this->_alloc.destroy(this->_first_elem);
					
					pointer			tmp = this->_alloc.allocate(new_cap * 2);
					
					this->_capacity = new_cap * 2;
					this->_first_elem = tmp;
					this->_last_elem = tmp + _size;
					this->_end_of_strorage = _first_elem + _capacity;
				}
			}
			
			size_type				capacity( void ) const { return this->_capacity; }

		// Member functions for Modifiers

	// 		void					clear( void);
	
			// iterator				insert( const_iterator pos, const value_type &value )

			size_type				countSize( iterator pos )
			{
				size_type	i = 0;
				
				for(iterator first = begin(); first != pos; ++first)
					i++;
				return i;
			}
			
			iterator				insert( iterator pos, size_type count, const value_type &value )
			{
				size_type	i = countSize(pos);
				if (this->empty())
				{
					this->_first_elem = _alloc.allocate(count);

				}
				else
				{
					this->_last_elem = _first_elem + _size - 1;
					for (pointer new_tab_end = _last_elem + count; new_tab_end != _first_elem + i + count - 1; --new_tab_end)
					{
						_alloc.construct(new_tab_end, *_last_elem);
						_alloc.destroy(_last_elem);
						_last_elem--;
					}
				}
				pointer tmp = _first_elem + i;
				while (count--)
				{
					_alloc.construct(tmp, value);
					tmp++;
					_size++;
				}
				return (iterator(this->_first_elem));
			}
			
	// 		template< class InputIt >
	// 		iterator				insert( const_iterator pos, InputIt first, InputIt last );
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
	
	// // NON-MEMBER FUNCTIONS
		
	// 		template< class T, class Allocator >
	// 		bool					operator==( const ft::vector<T, Allocator> &lhs, const ft::vector<T, Allocator> &rhs );
	// 		template< class T, class Allocator >
	// 		bool					operator!=( const ft::vector<T, Allocator> &lhs, const ft::vector<T, Allocator> &rhs );
	// 		template< class T, class Allocator >
	// 		bool					operator<( const ft::vector<T, Allocator> &lhs, const ft::vector<T, Allocator> &rhs );
	// 		template< class T, class Allocator >
	// 		bool					operator<=( const ft::vector<T, Allocator> &lhs, const ft::vector<T, Allocator> &rhs );
	// 		template< class T, class Allocator >
	// 		bool					operator>( const ft::vector<T, Allocator> &lhs, const ft::vector<T, Allocator> &rhs );
	// 		template< class T, class Allocator >
	// 		bool					operator>=( const ft::vector<T, Allocator> &lhs, const ft::vector<T, Allocator> &rhs );
			
		private:

			value_type		*_first_elem;
			value_type		*_last_elem;
			value_type		*_end_of_strorage;
			size_type		_size;
			size_type		_capacity;
			allocator_type	_alloc;
			
	};
}

#endif
