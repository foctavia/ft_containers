/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rb_tree.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: foctavia <foctavia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/07 10:58:01 by foctavia          #+#    #+#             */
/*   Updated: 2023/02/07 20:49:34 by foctavia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RB_TREE_HPP
# define RB_TREE_HPP

namespace ft
{
	enum rb_tree_color { black = false, red = true };

	template< typename T >
	class rb_tree_node
	{
		public:

			typedef T				value_type;
			typedef rb_tree_node	*node_pointer;

			value_type				value;
			node_pointer			parent;
			node_pointer			left;
			node_pointer			right;
			rb_tree_color			color;

	// CONSTRUCTOR

			rb_tree_node( void ) : value( 0 ), parent( NULL ), left( NULL ), right( NULL ), color( black ) { }
			
			rb_tree_node( const value_type &val ) : value( val ), parent( NULL ), left( NULL ), right( NULL ), color( red ) { }
			
			rb_tree_node( const rb_tree_node &src) : value( 0 ), parent( NULL ), left( NULL ), right( NULL ), color( black )
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

				return *this;
			}
	};

	template< typename Key, typename T, typename Compare = std::less< Key >, 
				typename Allocator = std::allocator< rb_tree_node< T > > >
	class rb_tree
	{
		public:

			typedef Key									key_type;
			typedef Val									value_type;
			typedef Compare								key_compare;
			typedef Allocator							allocator_type;
			
			typedef typename Allocator::size_type		size_type;
			typedef typename Allocator::difference_type	difference_type;
			
			typedef typename Allocator::reference		reference;
			typedef typename Allocator::const_reference	const_reference;
			typedef typename Allocator::pointer			pointer;
			typedef typename Allocator::const_pointer	const_pointer;
			
			typedef rb_tree_node<Val>					node;
			typedef rb_tree_node						*node_ptr;
			typedef const rb_tree_node					*const_node_ptr;

	// CONSTRUCTOR

			rb_tree( void ) { }
			
			rb_tree( const Compare &comp, const allocator_type &alloc = allocator_type() );

			rb_tree( const rb_tree &src );

	// DESTRUCTOR

			~rb_tree( void );

	// ASSIGNMENT OPERATOR

			rb_tree		&operator=( const rb_tree &rhs );
	};
	
}

#endif
