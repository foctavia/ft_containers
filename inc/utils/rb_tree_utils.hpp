/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rb_tree_utils.hpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: foctavia <foctavia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/07 18:19:17 by foctavia          #+#    #+#             */
/*   Updated: 2023/02/10 14:49:48 by foctavia         ###   ########.fr       */
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
			
			rb_tree_node( const value_type &v ) 
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
		public:
			

			typedef T								value_type;
			typedef std::bidirectional_iterator_tag	iterator_category;
			typedef T								&reference;
			typedef const T							&const_reference;
			typedef T								*pointer;
			typedef const T							*const_pointer;

			typedef rb_tree_node< T >				node_type;
			typedef rb_tree_node< const T >			const_node_type;

			typedef rb_tree_node< T >				*node_pointer;
			typedef rb_tree_node< const T >			*const_node_pointer;

			typedef rb_tree_iterator< T >			iterator;
			typedef rb_tree_iterator< const T >		const_iterator;

			node_pointer							node;

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
			
		// Member functions for element access
			
			node_pointer		base() const				{ return this->node; }
		
			reference			operator*( void ) const		{ return this->node->value; }

			pointer				operator->( void ) const	{ return &this->node->value; }

			// operator			const_iterator() const		{ return const_iterator(reinterpret_cast<const_node_pointer>(node)); }
		// Member functions for overload operator

			// rb_tree_iterator	&operator++( void )
			// {
			// 	node = rb_increment(node);
			// 	return *this;
			// }

			// rb_tree_iterator	operator++( int )
			// {
			// 	rb_tree_iterator	tmp = *this;
			// 	node = rb_increment(node);
			// 	return tmp;
			// }

			// rb_tree_iterator	&operator--( void )
			// {
			// 	node = rb_decrement(node);
			// 	return *this;
			// }

			// rb_tree_iterator	operator--( int )
			// {
			// 	rb_tree_iterator	tmp = *this;
			// 	node = rb_decrement(node);
			// 	return tmp;
			// }

			bool				operator==( const rb_tree_iterator &other ) const
			{
				return this->node == other.node;
			}

			bool				operator!=( const rb_tree_iterator &other ) const
			{
				return this->node != other.node;
			}

	};

	// NON-MEMBER FUNCTION

	template< typename T1, typename T2 >
	inline bool	operator==( const rb_tree_iterator< T1 > &lhs, const rb_tree_iterator< T2 > &rhs )
	{ return lhs.base() == rhs.base(); }

	template< typename T1, typename T2 >
	inline bool	operator!=( const rb_tree_iterator< T1 > &lhs, const rb_tree_iterator< T2 > &rhs )
	{ return lhs.base() != rhs.base(); }

	template< typename T >
	inline bool	operator==( const rb_tree_iterator< T > &lhs, const rb_tree_iterator< T > &rhs )
	{ return lhs.base() == rhs.base(); }

	template< typename T >
	inline bool	operator!=( const rb_tree_iterator< T > &lhs, const rb_tree_iterator< T > &rhs )
	{ return lhs.base() != rhs.base(); }

	template< typename T1, typename T2 >
	inline bool	operator<( const rb_tree_iterator< T1 > &lhs, const rb_tree_iterator< T2 > &rhs )
	{ return lhs.base() < rhs.base(); }

	template< typename T >
	inline bool	operator<( const rb_tree_iterator< T > &lhs, const rb_tree_iterator< T > &rhs )
	{ return lhs.base() < rhs.base(); }

	template< typename T1, typename T2 >
	inline bool	operator>( const rb_tree_iterator< T1 > &lhs, const rb_tree_iterator< T2 > &rhs )
	{ return lhs.base() > rhs.base(); }

	template< typename T >
	inline bool	operator>( const rb_tree_iterator< T > &lhs, const rb_tree_iterator< T > &rhs )
	{ return lhs.base() > rhs.base(); }

	template< typename T1, typename T2 >
	inline bool	operator<=( const rb_tree_iterator< T1 > &lhs, const rb_tree_iterator< T2 > &rhs )
	{ return lhs.base() <= rhs.base(); }

	template< typename T >
	inline bool	operator<=( const rb_tree_iterator< T > &lhs, const rb_tree_iterator< T > &rhs)
	{ return lhs.base() <= rhs.base(); }

	template< typename T1, typename T2 >
	inline bool	operator>=( const rb_tree_iterator< T1 > &lhs, const rb_tree_iterator< T2 > &rhs )
	{ return lhs.base() >= rhs.base(); }

	template< typename T >
	inline bool	operator>=( const rb_tree_iterator< T > &lhs, const rb_tree_iterator< T > &rhs )
	{ return lhs.base() >= rhs.base(); }
	
}

#endif
