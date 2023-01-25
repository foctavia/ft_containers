/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: foctavia <foctavia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/24 12:23:40 by foctavia          #+#    #+#             */
/*   Updated: 2023/01/25 17:27:12 by foctavia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VECTOR_HPP
# define VECTOR_HPP

# include <algorithm>
# include <memory>
# include <type_traits.hpp>
# include <iterators.hpp>

namespace ft
{
	template< class T, class Allocator = std::allocator<T> >
	class vector
	{
	// 	public:
		
	// 		typedef T											value_type;
	// 		typedef Allocator									allocator_type;
			
	// 		typedef std::size_t									size_type;
	// 		typedef std::ptrdiff_t								difference_type;
			
	// 		typedef typename allocator_type::reference			reference;
	// 		typedef typename allocator_type::const_reference	const_reference;
	// 		typedef typename allocator_type::pointer			pointer;
	// 		typedef typename allocator_type::const_pointer		const_pointer;
			
	// 		typedef T											*iterator;
	// 		typedef const T										*const_iterator;
			
	// 		typedef ft::reverse_iterator< iterator >			reverse_iterator;
	// 		typedef ft::reverse_iterator< const_iterator >		const_reverse_iterator;
	

	// // CONSTRUCTORS
		
	// 		explicit vector( const allocator_type &alloc = allocator_type() );
			
	// 		explicit vector( size_type count, const value_type &value = value_type(), const allocator_type &alloc = allocator_type() );
			
	// 		template< class InputIt >
	// 		vector( InputIt first, InputIt last, const allocator_type &alloc = allocator_type() );

	// 		vector( vector const &src );

	// // DESTRUCTOR
			
	// 		~vector( void );

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

	// 	// Member functions for Iterator

	// 		iterator				begin( void );
	// 		const_iterator			begin( void ) const;
	// 		iterator				end( void );
	// 		const_iterator			end( void ) const;

	// 		reverse_iterator		rbegin( void );
	// 		const_reverse_iterator	rbegin( void ) const;
	// 		reverse_iterator		rend( void );
	// 		const_reverse_iterator	rend( void ) const;

	// 	// Member functions for Capacity

	// 		bool					empty( void ) const;
	// 		size_type				size( void ) const;
	// 		size_type				max_size( void ) const;
	// 		void					reserve( size_type new_cap );
	// 		size_type				capacity( void ) const;

	// 	// Member functions for Modifiers

	// 		void					clear( void);
	// 		iterator				insert( const_iterator pos, const value_type &value );
	// 		iterator				insert( const_iterator pos, size_type count, const value_type &value );
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
			
	// 	private:

	// 		value_type		*_elem;
	// 		size_type		_size;
	// 		size_type		_capacity;
	// 		allocator_type	_alloc;
			
	};
}

#endif
