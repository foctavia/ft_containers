/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: foctavia <foctavia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/24 12:23:57 by foctavia          #+#    #+#             */
/*   Updated: 2023/02/20 11:43:31 by foctavia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SET_HPP
# define SET_HPP

# include <stdexcept>
# include <iostream>
# include <functional>

# include "rb_tree_utils.hpp"
# include "rb_tree.hpp"
# include "utility.hpp"
# include "type_traits.hpp"
# include "reverse_iterator.hpp"
# include "algorithm.hpp"

namespace ft
{
	/* SET ******************************************************************************** */

	template< class Key, class Compare = std::less< Key >, class Allocator = std::allocator< Key > >
	class set
	{
		public:

			class											value_compare;
	
			typedef Key										key_type;
			typedef Key										value_type;
			typedef Compare									key_compare;
			typedef Allocator								allocator_type;
			
			typedef typename Allocator::size_type			size_type;
			typedef typename Allocator::difference_type		difference_type;

			typedef typename Allocator::reference			reference;
			typedef typename Allocator::const_reference		const_reference;
			typedef typename Allocator::pointer				pointer;
			typedef typename Allocator::const_pointer		const_pointer;

		private:
															
			typedef ft::rb_tree< key_type, key_compare, allocator_type >
															tree_type;

		public:
																	
			typedef typename tree_type::const_iterator		iterator;
			typedef typename tree_type::const_iterator		const_iterator;
			
			typedef ft::reverse_iterator< iterator >		reverse_iterator;
			typedef ft::reverse_iterator< const_iterator >	const_reverse_iterator;

			/* VALUE_COMPARE ************************************************************** */

			class value_compare : public std::binary_function< value_type, value_type, bool >
			{
				private:
				
					friend class set< Key, Compare, Allocator >;
				
				protected:
					
					key_compare		comp;

			// CONSTRUCTOR

					value_compare( key_compare c ) : comp( c )	{ }
				
				public:

			// MEMBER FUNCTION

					bool	operator()( const value_type &lhs, const value_type &rhs ) const
					{
						return comp(lhs, rhs);
					}
			};

	// CONSTRUCTOR

			explicit set( const key_compare &comp = key_compare(), const allocator_type &alloc = allocator_type() )
				: _tree( comp, alloc ), _comp( comp ), _alloc( alloc ) { }

			template< class InputIt >
			set( InputIt first, InputIt last, typename ft::enable_if<!ft::is_integral<InputIt>::value, InputIt>::type* = 0,
				const Compare &comp = Compare(), const Allocator &alloc = Allocator() )
				: _tree( comp, alloc ), _comp( comp ), _alloc( alloc )
			{
				this->_tree.insert(first, last);
			}
			
			set( const set &src )
				: _tree( src._comp, src._alloc ), _comp( src._comp ), _alloc( src._alloc )
			{
				*this = src;
			}

	// DESTRUCTOR

			~set( void )	{ }

	// ASSIGNMENT OPERATOR

			set						&operator=( const set &rhs )
			{
				if (this != &rhs)
					_tree = rhs._tree;

				return *this;
			}

	// MEMBER FUNCTION
	
		// Getter

			allocator_type			get_allocator( void ) const					{ return this->_alloc; }

		// Member functions for Iterator
		
			iterator				begin( void )								{ return _tree.begin(); }
			const_iterator			begin( void ) const							{ return _tree.begin(); }

			iterator				end( void )									{ return _tree.end(); }
			const_iterator			end( void ) const							{ return _tree.end(); }

			reverse_iterator		rbegin( void )								{ return reverse_iterator(end()); }
			const_reverse_iterator	rbegin( void ) const						{ return const_reverse_iterator(end()); }

			reverse_iterator		rend( void )								{ return reverse_iterator(begin()); }
			const_reverse_iterator	rend( void ) const							{ return const_reverse_iterator(begin()); }

		// Member functions for Capacity
		
			bool					empty( void ) const							{ return _tree.size() == 0; }

			size_type				size( void ) const							{ return _tree.size(); }

			size_type				max_size( void ) const						{ return _tree.max_size(); }

		// Member functions for Modifiers
		
			void					clear( void )								{ return _tree.clear(); }

			ft::pair<iterator, bool>	
				insert( const value_type &value )								{ return _tree.insert(value); }
			
			iterator				insert( iterator pos, const value_type &value )
			{
				(void)pos;

				return insert(value).first;
			}
	
			template< class InputIt >
			void					insert( InputIt first, InputIt last, typename ft::enable_if<!ft::is_integral<InputIt>::value, InputIt>::type* = 0 )
																				{ _tree.insert(first, last); }

			iterator				erase( iterator pos )
			{
				if (pos == end())
					return end();
				_tree.erase(*pos);
				
				return pos;
			};
			
			iterator				erase( iterator first, iterator last )		
			{
				size_type	distance = std::distance(first, last);
				
				if (distance && distance < max_size())
				{
					while (first != last)
					{
						value_type	tmp = (*first++);
						_tree.erase(tmp);
					}
				}
				
				return last;
			}
		
			size_type				erase( const key_type &key )				{ return _tree.erase(key); }

			void					swap( set &other )							{ _tree.swap(other._tree); }

		// Member functions for Lookup

			iterator				lower_bound( const key_type &key )			//{ return iterator(_tree.lower_bound(key)); }
			{
				iterator	it = begin();
				
				while (it != end() && *it < key)
					it++;

				return it;	
			}
			
			const_iterator			lower_bound( const key_type &key ) const	//{ return const_iterator(_tree.lower_bound(key)); }
			{
				const_iterator	it = begin();
				
				while (it != end() && *it < key)
					it++;

				return it;
			}

			iterator				upper_bound( const key_type &key )			//{ return iterator(_tree.upper_bound(key)); }
			{
				iterator	it = begin();
				
				while (it != end() && *it <= key)
					it++;

				return it;
			}
			
			const_iterator			upper_bound( const key_type &key ) const	//{ return const_iterator(_tree.upper_bound(key)); }
			{
				const_iterator	it = begin();
				
				while (it != end() && *it <= key)
					it++;

				return it;
			}

			ft::pair< iterator, iterator >	
				equal_range( const key_type &key )								{ return ft::make_pair(lower_bound(key), upper_bound(key)); }
			ft::pair< const_iterator, const_iterator >	
				equal_range( const key_type &key ) const						{ return ft::make_pair(lower_bound(key), upper_bound(key)); }

			iterator				find( const key_type &key )					{ return iterator(_tree.find(key)); }
			const_iterator			find( const key_type &key ) const			{ return iterator(_tree.find(key)); }

			size_type				count( const key_type &key ) const
			{
				ft::pair<const_iterator, const_iterator>	tmp = equal_range(key);
				size_type									count = std::distance(tmp.first, tmp.second);
				
				return count;
			}

		// Member functions for Observers
			
			key_compare				key_comp( void ) const						{ return key_compare(); }
			
			set::value_compare		value_comp( void ) const					{ return value_compare(key_comp()); }

		private:

			tree_type		_tree;
			key_compare		_comp;
			allocator_type	_alloc;
			
	};
	
	// NON-MEMBER FUNCTIONS

	template< class Key, class Compare, class Alloc >
	inline bool		operator==( const ft::set< Key, Compare, Alloc > &lhs, const ft::set< Key, Compare, Alloc > &rhs )
	{
		return (lhs.size() == rhs.size() && ft::equal(lhs.begin(), lhs.end(), rhs.begin()));
	}
	
	template< class Key, class Compare, class Alloc >
	inline bool		operator!=( const ft::set< Key, Compare, Alloc > &lhs, const ft::set< Key, Compare, Alloc > &rhs )
	{
		return !(lhs == rhs);
	}

	template< class Key, class Compare, class Alloc >
	inline bool		operator<( const ft::set< Key, Compare, Alloc > &lhs, const ft::set< Key, Compare, Alloc > &rhs )
	{
		return ft::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end());
	}
	
	template< class Key, class Compare, class Alloc >
	inline bool		operator<=( const ft::set< Key, Compare, Alloc > &lhs, const ft::set< Key, Compare, Alloc > &rhs )
	{
		return !(rhs < lhs);
	}

	template< class Key, class Compare, class Alloc >
	inline bool		operator>( const ft::set< Key, Compare, Alloc > &lhs, const ft::set< Key, Compare, Alloc > &rhs )
	{
		return rhs < lhs;
	}

	template< class Key, class Compare, class Alloc >
	inline bool		operator>=( const ft::set< Key, Compare, Alloc > &lhs, const ft::set< Key, Compare, Alloc > &rhs )
	{
		return !(lhs < rhs);
	}

	template< class Key, class Compare, class Alloc >
	inline void		swap( ft::set< Key, Compare, Alloc > &lhs, ft::set< Key, Compare, Alloc > &rhs )
	{
		lhs.swap(rhs);
	}
	
}

#endif
