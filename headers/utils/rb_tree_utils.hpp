/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rb_tree_utils.hpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: foctavia <foctavia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/07 18:19:17 by foctavia          #+#    #+#             */
/*   Updated: 2023/02/27 18:39:36 by foctavia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RB_TREE_UTILS_HPP
# define RB_TREE_UTILS_HPP

# include "iterator_traits.hpp"
# include "type_traits.hpp"

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
				: value( src.value ), parent( src.parent ), left( src.left ), right( src.right ), color( src.color ), is_left( src.is_left ) { }

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

	template< typename T, typename node_type >
	class rb_tree_iterator
	{		
		public:
			
			typedef std::bidirectional_iterator_tag	iterator_category;
			
			typedef T								value_type;
			typedef T								&reference;
			typedef T								*pointer;
			typedef const T							&const_reference;
			typedef const T							*const_pointer;

			typedef std::ptrdiff_t 					difference_type;

			typedef node_type						*node_pointer;

			node_pointer							node;

	// CONSTRUCTOR

			rb_tree_iterator( void ) : node( ) { }

			rb_tree_iterator( node_pointer n ) : node( n ) { }

			rb_tree_iterator( const rb_tree_iterator &src ) : node( src.node ) { }
			
	// DESTRUCTOR

			~rb_tree_iterator( void ) { }

	// ASSIGNMENT OPERATOR

			rb_tree_iterator	&operator=(const rb_tree_iterator &rhs)
			{
				this->node = rhs.base();
				
				return *this;
			}

	// MEMBER FUNCTIONS

			operator			rb_tree_iterator< const value_type, node_type >( void ) const
			{
				return rb_tree_iterator< const value_type, node_type >(node);
			}
			
		// Member functions for element access
			
			node_pointer		base( void ) const			{ return this->node; }
		
			reference			operator*( void ) const		{ return this->node->value; }

			pointer				operator->( void ) const	{ return &this->node->value; }

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

			bool				operator==( const rb_tree_iterator< const value_type, node_type > &other ) const
			{
				return this->node == other.node;
			}

			bool				operator!=( const rb_tree_iterator< const value_type, node_type > &other ) const
			{
				return this->node != other.node;
			}

		private:

			node_pointer	_rb_increment( node_pointer current )
			{
				node_pointer	next = NULL;

				if (!current)
					return NULL;

				if (current && current->right)
				{
					next = current->right;
					while (next && next->left)
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
				node_pointer	prev = NULL;

				if (!current)
					return NULL;

				if (current && current->left)
				{
					prev = current->left;
					while (prev && prev->right)
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

}

#endif
