/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rb_tree.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: foctavia <foctavia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/07 10:58:01 by foctavia          #+#    #+#             */
/*   Updated: 2023/02/08 11:24:30 by foctavia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RB_TREE_HPP
# define RB_TREE_HPP

namespace ft
{
	enum rb_tree_color { red = false, black = true };

	template< typename Key, typename Value >
	class rb_tree_node
	{
		public:

			typedef Key							key_type;
			typedef Value						value_type;
			typedef rb_tree_node< Key, Value >	node_value;
			typedef rb_tree_node< Key, Value >	*node_pointer;

			key_type							key;
			value_type							value;
			node_pointer						parent;
			node_pointer						left;
			node_pointer						right;
			rb_tree_color						color;
			bool								is_left;

	// CONSTRUCTOR

			rb_tree_node( void ) 
				: key( 0 ), value( 0 ), parent( NULL ), left( NULL ), right( NULL ), color( red ), is_left( false ) { }
			
			rb_tree_node( const key_type &k, const value_type &v ) 
				: key( k ), value( v ), parent( NULL ), left( NULL ), right( NULL ), color( red ), is_left( false ) { }
			
			rb_tree_node( const rb_tree_node &src)
				: key( 0 ), value( 0 ), parent( NULL ), left( NULL ), right( NULL ), color( red ), is_left( false )
			{
				*this = src;
			}

	// DESTRUCTOR
			
			~rb_tree_node( void ) { }

	// ASSIGNMENT OPERATOR

			rb_tree_node	&operator=( const rb_tree_node &rhs )
			{
				key = rhs.key;
				value = rhs.value;
				parent = rhs.parent;
				left = rhs.left;
				right = rhs.right;
				color = rhs.color;
				is_left = rhs.is_left;

				return *this;
			}
	};

	template< typename Key, typename Value, typename Compare = std::less< Key >, 
				typename Allocator = std::allocator< rb_tree_node< T > > >
	class rb_tree
	{
		public:

			typedef Key									key_type;
			typedef Value								value_type;
			typedef Compare								key_compare;
			typedef Allocator							allocator_type;
			
			typedef typename Allocator::size_type		size_type;
			typedef typename Allocator::difference_type	difference_type;
			
			typedef typename Allocator::reference		reference;
			typedef typename Allocator::const_reference	const_reference;
			typedef typename Allocator::pointer			pointer;
			typedef typename Allocator::const_pointer	const_pointer;
			
			typedef rb_tree_node< Key, Value >			node_value;
			typedef rb_tree_node< Key, Value >			*node_pointer;

			node_pointer								root;
			size_type									size;

	// CONSTRUCTOR

			rb_tree( void ) { }
			
			rb_tree( const Compare &comp, const allocator_type &alloc = allocator_type() );

			rb_tree( const rb_tree &src );

	// DESTRUCTOR

			~rb_tree( void );

	// ASSIGNMENT OPERATOR

			rb_tree		&operator=( const rb_tree &rhs );

	// MEMBER FUNCTION

			void		add( const key_type &k, const value_type &v )
			{
				node_pointer	node = new rb_tree_node(k, v);
				if (!root)
				{
					root = node;
					root->color = black;
					size++;
				}
				else
				{
					_add(root, node);
					size++;
				}
			}

			void		_add()
	};
	
}

#endif
