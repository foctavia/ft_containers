/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: foctavia <foctavia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/24 12:23:57 by foctavia          #+#    #+#             */
/*   Updated: 2023/02/10 15:25:20 by foctavia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAP_HPP
# define MAP_HPP

# include <stdexcept>
# include <iostream>
# include <functional>

# include <rb_tree_utils.hpp>
# include <rb_tree.hpp>
# include <utility.hpp>
# include <type_traits.hpp>
# include <reverse_iterator.hpp>
# include <algorithm.hpp>

namespace ft
{
	/* MAP ******************************************************************************** */

	template< class Key, class T, class Compare = std::less< Key >, 
				class Allocator = std::allocator< ft::pair< const Key, T > > >
	class map
	{
		public:

			class											value_compare;
	
			typedef Key										key_type;
			typedef T										mapped_type;
			typedef ft::pair< const Key, T >				value_type;
			typedef Compare									key_compare;
			typedef Allocator								allocator_type;
			
			typedef typename Allocator::size_type			size_type;
			typedef typename Allocator::difference_type		difference_type;

			typedef typename Allocator::reference			reference;
			typedef typename Allocator::const_reference		const_reference;
			typedef typename Allocator::pointer				pointer;
			typedef typename Allocator::const_pointer		const_pointer;

		private:
		
			typedef ft::rb_tree< key_type, value_type, value_compare, allocator_type >
															tree_type;

		public:
																	
			typedef typename tree_type::iterator			iterator;
			typedef typename tree_type::const_iterator		const_iterator;
			
			typedef ft::reverse_iterator< iterator >		reverse_iterator;
			typedef ft::reverse_iterator< const_iterator >	const_reverse_iterator;

			/* VALUE_COMPARE ************************************************************** */

			class value_compare : public std::binary_function< value_type, value_type, bool >
			{
				private:
				
					friend class map< Key, T, Compare, Allocator >;
				
				protected:
					
					key_compare		comp;

			// CONSTRUCTOR

					value_compare( key_compare c ) : comp( c )	{ }
				
				public:

			// MEMBER FUNCTION

					bool	operator()( const value_type &lhs, const value_type &rhs ) const
					{
						return comp(lhs.first, rhs.first);
					}
			};

	// CONSTRUCTOR

			explicit map( const key_compare &comp = key_compare(), const allocator_type &alloc = allocator_type() )
				: _tree( comp, alloc ), _comp( comp ), _alloc( alloc ) { }

			// template< class InputIt >
			// map( InputIt first, InputIt last, const Compare &comp = Compare(), const Allocator &alloc = Allocator() );
			
			// map( const map &src )
			// 	: _tree( 0 ), _comp( src._comp ), _alloc( src._alloc )
			// {
			// 	*this = src;
			// }

	// DESTRUCTOR

			~map( void )
			{}

	// ASSIGNMENT OPERATOR

			// map						&operator=( const map &rhs )
			// {
			// 	if (this != &rhs)
			// 		this->insert(rhs.begin(), rhs.last());

			// 	return *this;
			// }

	// // MEMBER FUNCTION
	
	// 	// Getter

	// 		allocator_type			get_allocator( void ) const;

	// 	// Member functions for Element access
			
	// 		mapped_type				&at( const key_type &key );
	// 		const mapped_type		&at( const key_type &key ) const;

			// mapped_type				&operator[]( const key_type &key );

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
		
			bool					empty( void ) const			{ return _tree.empty(); }

	// 		size_type				size( void ) const;

	// 		size_type				max_size( void ) const;

	// 	// Member functions for Modifiers
		
	// 		void					clear( void );

			ft::pair<iterator, bool>	
				insert( const value_type &value )									{ return _tree.insert(value); }
			
			// iterator				insert( iterator pos, const value_type &value );
	// 		template< class InputIt >
	// 		void					insert( InputIt first, InputIt last );

	// 		iterator				erase( iterator pos );
	// 		iterator				erase( iterator first, iterator last );
	// 		size_type				erase( const key_type &key );

	// 		void					swap( map &other );

	// 	// Member functions for Lookup

	// 		size_type				count( const key_type &key ) const;

	// 		iterator				find( const key_type &key );
	// 		const_iterator			find( const key_type &key ) const;

	// 		ft::pair< iterator, iterator >	
	// 			equal_range( const key_type &key );
	// 		ft::pair< const_iterator, const_iterator >	
	// 			equal_range( const key_type &key ) const;

	// 		iterator				lower_bound( const key_type &key );
	// 		const_iterator			lower_bound( const key_type &key ) const;

	// 		iterator				upper_bound( const key_type &key );
	// 		const_iterator			upper_bound( const key_type &key ) const;
			
	// 	// Member functions for Observers
			
	// 		key_compare				key_comp( void ) const;
			
	// 		ft::map::value_compare	value_comp( void ) const;

		private:

			tree_type		_tree;
			key_compare		_comp;
			allocator_type	_alloc;
			
	};
	
	// NON-MEMBER FUNCTIONS

	template< class Key, class T, class Compare, class Alloc >
	inline bool		operator==( const ft::map< Key, T, Compare, Alloc > &lhs, const ft::map< Key, T, Compare, Alloc > &rhs )
	{
		return (lhs.size() == rhs.size() && ft::equal(lhs.begin(), lhs.end(), rhs.begin()));
	}
	
	template< class Key, class T, class Compare, class Alloc >
	inline bool		operator!=( const ft::map< Key, T, Compare, Alloc > &lhs, const ft::map< Key, T, Compare, Alloc > &rhs )
	{
		return !(lhs == rhs);
	}

	template< class Key, class T, class Compare, class Alloc >
	inline bool		operator<( const ft::map< Key, T, Compare, Alloc > &lhs, const ft::map< Key, T, Compare, Alloc > &rhs )
	{
		return ft::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end());
	}
	
	template< class Key, class T, class Compare, class Alloc >
	inline bool		operator<=( const ft::map< Key, T, Compare, Alloc > &lhs, const ft::map< Key, T, Compare, Alloc > &rhs )
	{
		return !(rhs < lhs);
	}

	template< class Key, class T, class Compare, class Alloc >
	inline bool		operator>( const ft::map< Key, T, Compare, Alloc > &lhs, const ft::map< Key, T, Compare, Alloc > &rhs )
	{
		return rhs < lhs;
	}

	template< class Key, class T, class Compare, class Alloc >
	inline bool		operator>=( const ft::map< Key, T, Compare, Alloc > &lhs, const ft::map< Key, T, Compare, Alloc > &rhs )
	{
		return !(lhs < rhs);
	}

	template< class Key, class T, class Compare, class Alloc >
	inline void		swap( ft::map< Key, T, Compare, Alloc > &lhs, ft::map< Key, T, Compare, Alloc > &rhs )
	{
		lhs.swap(rhs);
	}
	
}

#endif
