/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rb_tree_utils.hpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: foctavia <foctavia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/07 18:19:17 by foctavia          #+#    #+#             */
/*   Updated: 2023/02/09 12:01:04 by foctavia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RB_TREE_UTILS_HPP
# define RB_TREE_UTILS_HPP

# include <iterator_traits.hpp>
# include <type_traits.hpp>

namespace ft
{
	/* RB_TREE_COLOR ********************************************************************** */

	enum rb_tree_color { red = false, black = true };

	/* RB_TREE_NODE *********************************************************************** */

	template< typename Value >
	class rb_tree_node
	{
		public:

			typedef Value					value_type;
			typedef rb_tree_node< Value >	node_type;
			typedef rb_tree_node< Value >	*node_pointer;

			value_type						value;
			node_pointer					parent;
			node_pointer					left;
			node_pointer					right;
			rb_tree_color					color;
			bool							is_left;

	// CONSTRUCTOR

			rb_tree_node( void ) 
				: value( 0 ), parent( NULL ), left( NULL ), right( NULL ), color( red ), is_left( false ) { }
			
			rb_tree_node( const key_type &k, const value_type &v ) 
				: value( v ), parent( NULL ), left( NULL ), right( NULL ), color( red ), is_left( false ) { }
			
			rb_tree_node( const rb_tree_node &src)
				: value( 0 ), parent( NULL ), left( NULL ), right( NULL ), color( red ), is_left( false )
			{
				*this = src;
			}

	// DESTRUCTOR
			
			~rb_tree_node( void ) { }

	// ASSIGNMENT OPERATOR

			rb_tree_node	&operator=( const rb_tree_node &rhs )
			{
				value = rhs.value;
				parent = rhs.parent;
				left = rhs.left;
				right = rhs.right;
				color = rhs.color;
				is_left = rhs.is_left;

				return *this;
			}
	};
	
	/* RB_TREE_ITERATOR ******************************************************************* */

	template< typename T >
	class rb_tree_iterator : public std::iterator< std::bidirectional_iterator_tag, T, std::ptrdiff_t, T *, T & >
	{		
		protected:

			typedef ft::iterator_traits< T >				traits_type;

		public:
			
			typedef T										*iterator_type;
			typedef std::bidirectional_iterator_tag			iterator_category;
			typedef typename traits_type::value_type		value_type;
			typedef typename traits_type::difference_type	difference_type;
			typedef typename traits_type::reference			reference;
			typedef typename traits_type::pointer			pointer;

			typedef rb_tree_node< T >						node_type;
			typedef rb_tree_node< T >						*node_pointer;

			typedef rb_tree_iterator< T >					iterator;
			typedef rb_tree_iterator< const T >				const_iterator;

			node_pointer									node;

	// CONSTRUCTOR

			rb_tree_iterator( void ) : node() { }

			explicit rb_tree_iterator( const node_pointer n ) : node( n ) { }

			template< typename _T >
			rb_tree_iterator(const rb_tree_iterator< _T > &src) : node(NULL)
			{
				*this = src;
			}
			
	// DESTRUCTOR

			~rb_tree_iterator( void ) { }

	// ASSIGNMENT OPERATOR

			template< typename _T >
			rb_tree_iterator	&operator=(const rb_tree_iterator< _T > &rhs)
			{
				this->node = rhs.node;
				
				return *this;
			}

	// MEMBER FUNCTIONS
			
// 		// Member functions for element access
			
// 		Iter const	&base() const									{ return current; }
		
		reference	operator*( void ) const							{ return this->node->value; }

// 		pointer		operator->( void ) const 						{ return current; }

// 		reference	operator[]( const difference_type &n ) const	{ return *(current + n); }

// 		// Member functions for overload operator

// 		random_access_iterator	operator++( int )					{ return random_access_iterator(current++); }

// 		random_access_iterator	operator--( int )					{ return random_access_iterator(current--); }

// 		random_access_iterator	&operator++( void )
// 		{
// 			++current;
// 			return *this;
// 		}

// 		random_access_iterator	&operator--( void )
// 		{
// 			--current;
// 			return *this;
// 		}

// 		random_access_iterator	&operator+=( const difference_type &n )
// 		{
// 			current += n;
// 			return *this;
// 		}

// 		random_access_iterator	&operator-=( const difference_type &n )
// 		{
// 			current -= n;
// 			return *this;
// 		}

// 		random_access_iterator	operator+( const difference_type &n ) const
// 		{
// 			return random_access_iterator( current + n );
// 		}
		
// 		random_access_iterator	operator-( const difference_type &n ) const
// 		{
// 			return random_access_iterator( current - n );
// 		}

// 		difference_type			operator+( const random_access_iterator &it ) const
// 		{
// 			return current + it.current;
// 		}

// 		difference_type			operator-( const random_access_iterator &it ) const
// 		{
// 			return current - it.current;
// 		}

	};

// 	// NON-MEMBER FUNCTION

// 	template< typename Iter1, typename Iter2 >
// 	inline bool	operator==( const random_access_iterator< Iter1 > &lhs, const random_access_iterator< Iter2 > &rhs )
// 	{ return lhs.base() == rhs.base(); }

// 	template< typename Iter1, typename Iter2 >
// 	inline bool	operator!=( const random_access_iterator< Iter1 > &lhs, const random_access_iterator< Iter2 > &rhs )
// 	{ return lhs.base() != rhs.base(); }

// 	template< typename Iter >
// 	inline bool	operator==( const random_access_iterator< Iter > &lhs, const random_access_iterator< Iter > &rhs )
// 	{ return lhs.base() == rhs.base(); }

// 	template< typename Iter >
// 	inline bool	operator!=( const random_access_iterator< Iter > &lhs, const random_access_iterator< Iter > &rhs )
// 	{ return lhs.base() != rhs.base(); }

// 	template< typename Iter1, typename Iter2 >
// 	inline bool	operator<( const random_access_iterator< Iter1 > &lhs, const random_access_iterator< Iter2 > &rhs )
// 	{ return lhs.base() < rhs.base(); }

// 	template< typename Iter >
// 	inline bool	operator<( const random_access_iterator< Iter > &lhs, const random_access_iterator< Iter > &rhs )
// 	{ return lhs.base() < rhs.base(); }

// 	template< typename Iter1, typename Iter2 >
// 	inline bool	operator>( const random_access_iterator< Iter1 > &lhs, const random_access_iterator< Iter2 > &rhs )
// 	{ return lhs.base() > rhs.base(); }

// 	template< typename Iter >
// 	inline bool	operator>( const random_access_iterator< Iter > &lhs, const random_access_iterator< Iter > &rhs )
// 	{ return lhs.base() > rhs.base(); }

// 	template< typename Iter1, typename Iter2 >
// 	inline bool	operator<=( const random_access_iterator< Iter1 > &lhs, const random_access_iterator< Iter2 > &rhs )
// 	{ return lhs.base() <= rhs.base(); }

// 	template< typename Iter >
// 	inline bool	operator<=( const random_access_iterator< Iter > &lhs, const random_access_iterator< Iter > &rhs )
// 	{ return lhs.base() <= rhs.base(); }

// 	template< typename Iter1, typename Iter2 >
// 	inline bool	operator>=( const random_access_iterator< Iter1 > &lhs, const random_access_iterator< Iter2 > &rhs )
// 	{ return lhs.base() >= rhs.base(); }

// 	template< typename Iter >
// 	inline bool	operator>=( const random_access_iterator< Iter > &lhs, const random_access_iterator< Iter > &rhs )
// 	{ return lhs.base() >= rhs.base(); }

// 	template< typename Iter >
// 	inline typename random_access_iterator< Iter >::difference_type
// 	operator-( const random_access_iterator< Iter > &lhs, const random_access_iterator< Iter > &rhs)
// 	{ return lhs.base() - rhs.base(); }
	
// 	template< typename Iter >
// 	inline random_access_iterator< Iter >
// 	operator+( typename random_access_iterator< Iter >::difference_type n, const random_access_iterator< Iter > &i )
// 	{ return random_access_iterator<Iter>(i.base() + n); }
	
}

#endif
