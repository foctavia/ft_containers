/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rb_tree_utils.hpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: foctavia <foctavia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/07 18:19:17 by foctavia          #+#    #+#             */
/*   Updated: 2023/02/14 13:57:06 by foctavia         ###   ########.fr       */
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
				: parent( 0 ), left( 0 ), right( 0 ), color( red ), is_left( false ) { }
			
			rb_tree_node( const value_type &val ) 
				: value( val ), parent( 0 ), left( 0 ), right( 0 ), color( red ), is_left( false ) { }
			
			rb_tree_node( const rb_tree_node &src)
				: value( src.value ), parent( src.parent ), left( src.left ), right( src.right ), color( src.color ), is_left( src.is_left )
			{
				// *this = src;
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

			rb_tree_iterator( void ) : node( NULL ) { }

			rb_tree_iterator( const node_pointer n ) : node( n ) { }

			template< typename _T >
			rb_tree_iterator(const rb_tree_iterator< _T > &src) : node( NULL )
			{
				*this = src;
			}
			
	// DESTRUCTOR

			~rb_tree_iterator( void ) { }

	// ASSIGNMENT OPERATOR

			template< typename _T >
			rb_tree_iterator	&operator=(const rb_tree_iterator< _T > &rhs)
			{
				this->node = rhs.base();
				
				return *this;
			}

	// MEMBER FUNCTIONS
			
		// Member functions for element access
			
			node_pointer		base() const				{ return this->node; }
		
			reference			operator*( void )			{ return this->node->value; }
			const_reference		operator*( void ) const		{ return this->node->value; }

			pointer				operator->( void )			{ return &this->node->value; }
			const_pointer		operator->( void ) const	{ return &this->node->value; }

		// Member functions for overload operator

			rb_tree_iterator	&operator++( void )
			{
				node = _rb_increment(node);
				
				return *this;
			}

			rb_tree_iterator	operator++( int )
			{
				rb_tree_iterator	tmp = *this;
				
				node = _rb_increment(node);
				
				return tmp;
			}

			rb_tree_iterator	&operator--( void )
			{
				node = _rb_decrement(node);
				
				return *this;
			}

			rb_tree_iterator	operator--( int )
			{
				rb_tree_iterator	tmp = *this;
				
				node = _rb_decrement(node);

				return tmp;
			}

			bool				operator==( const rb_tree_iterator &other ) const
			{
				return this->node == other.node;
			}

			bool				operator!=( const rb_tree_iterator &other ) const
			{
				return this->node != other.node;
			}

		private:

			node_pointer	_rb_increment( node_pointer current )
			{
				node_pointer	next;

				if (!current)
					return NULL;

				if (current->right)
				{
					next = current->right;
					while (next->left)
						next = next->left;
				}
				else
				{
					next = current->parent;
					while (next && !current->is_left)
					{
						current = next;
						next = next->parent;
					}
				}
				
				return next;
			}

			node_pointer	_rb_decrement( node_pointer current )
			{
				node_pointer	prev;

				if (!current)
					return NULL;

				if (current->left)
				{
					prev = current->left;
					while (prev->right)
						prev = prev->right;
				}
				else
				{
					prev = current->parent;
					while (prev && current->is_left)
					{
						current = prev;
						prev = prev->parent;
					}
				}
				
				return prev;
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
