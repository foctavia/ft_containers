/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rb_tree.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: foctavia <foctavia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/07 10:58:01 by foctavia          #+#    #+#             */
/*   Updated: 2023/02/08 16:17:53 by foctavia         ###   ########.fr       */
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

			node_value									root;
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

			size_type	blackNodes(node_value node)
			{
				if (!node)
					return 1;
				size_type	rightBlackNode = blackNodes(node.right);
				size_type	leftBlackNode = blackNodes(node.left);
				if (rightBlackNode != leftBlackNode)
				{
					// throw error
					// or fix the tree
				}
				else
				{
					if (node.color == black)
						leftBlackNode++;
					return leftBlackNode;
				}
			}

			size_type	height( void )
			{
				if (!root)
					return 0;
				return height(root) - 1;
			}

			size_type	height(node_value node)
			{
				if (!node)
					return 0;
				size_type	leftheight = height(node.left) + 1;
				size_type	rightheight = height(node.right) + 1;
				if (leftheight > rightheight)
					return leftheight;
				return rightheight;
			}

			void		add( const key_type &k, const value_type &v )
			{
				node_value	node = new rb_tree_node(k, v);
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
				checkColor(node);
			}

			void		rotateLeftRight(node_value grandparent)
			{
				rotateLeft(grandparent.left);
				rotateRight(grandparent);
			}

			void		rotateLeft(node_value grandparent)
			{
				node_value	tmp = grandparent.right;
				grandparent.right = tmp.left;
				if (grandparent.right)
				{
					grandparent.right.parent = grandparent;
					grandparent.right.is_left = false
				}
				if (grandparent.parent == NULL) // grandparent is root
				{
					root = tmp;
					tmp.parent = NULL;
				}
				else
				{
					tmp.parent = grandparent.parent;
					if (grandparent.is_left)
					{
						tmp.is_left = true;
						tmp.parent.left = tmp;
					}
					else
					{
						tmp.is_left = false;
						tmp.parent.right = tmp;
					}
				}
				tmp.left = grandparent;
				grandparent.is_left = true;
				grandparent.parent = tmp;
			}

			void		rotate(node_value node)
			{
				if (node.is_left)
				{
					if (node.parent.is_left)
					{
						rotateRight(node.parent.parent);
						node.color = red;
						node.parent.color = black;
						if (node.parent.right)
							node.parent.right.color = red;
					}
					else
					{
						rotateRightLeft(node.parent.parent);
						node.color = black;
						node.right.color = red;
						node.left.color = red;
					}
				}
				else
				{
					if (node.parent.is_left)
					{
						rotateLeft(node.parent.parent);
						node.color = red;
						node.parent.color = black;
						if (node.parent.right)
							node.parent.right.color = red;
					}
					else
					{
						rotateLeftRight(node.parent.parent);
						node.color = black;
						node.right.color = red;
						node.left.color = red;
					}
				}
			}

			void		correctTree(node_value node)
			{
				if (node.parent.is_left) // aunt is grandparent right child
				{
					if (node.parent.parent.right == NULL || node.parent.parent.right.color == black)
						return rotate(node);
					if (node.parent.parent.right != NULL)
						node.parent.parent.right.color = black;
					node.parent.parent.color = red;
					node.parent.color = black;
					return ;
				}
				else // aunt is grandparent left child
				{
					if (node.parent.parent.left == NULL || node.parent.parent.left.color == black)
						return rotate(node);
					if (node.parent.parent.left != NULL)
						node.parent.parent.left.color = black;
					node.parent.parent.color = red;
					node.parent.color = black;
					return ;
				}
			}

			void		checkColor(node_value node)
			{
				if (node == root)
					return ;
				if (node.color == red && node.parent.color == red)
					correctTree(node);
			}

		private:

	// PRIVATE MEMBER FUNCTION 

			void		_add( node_value parent, node_value newNode )
			{
				
				if(((Comparable<Key>)newNode.key)compareTo(parent.key) > 0)
				{
					if (!parent.right)
					{
						parent.right = newNode;
						newNode.parent = parent;
						newNode.is_left = false;
						return ;
					}
					return _add(parent.right, newNode);
				}
				if (!parent.left)
				{
					parent.left = newNode;
					newNode.parent = parent;
					newNode.is_left = true;
					return ;
				}
				return _add(parent.left, newNode);
			}
	};
	
}

#endif
