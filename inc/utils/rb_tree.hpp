/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rb_tree.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: foctavia <foctavia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/07 10:58:01 by foctavia          #+#    #+#             */
/*   Updated: 2023/02/09 15:32:05 by foctavia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RB_TREE_HPP
# define RB_TREE_HPP

# include <rb_tree_utils.hpp>
# include <utility.hpp>
# include <reverse_iterator.hpp>

namespace ft
{
	/* RB_TREE **************************************************************************** */

	template< typename Key, typename Value, typename Compare = std::less< Key >, 
				typename Allocator = std::allocator< rb_tree_node< Value > > >
	class rb_tree
	{
		public:

			typedef Key										key_type;
			typedef Value									value_type;
			typedef Compare									key_compare;
			typedef Allocator								allocator_type;
			
			typedef typename Allocator::size_type			size_type;
			typedef typename Allocator::difference_type		difference_type;
			
			typedef typename Allocator::reference			reference;
			typedef typename Allocator::const_reference		const_reference;
			typedef typename Allocator::pointer				pointer;
			typedef typename Allocator::const_pointer		const_pointer;
			
			typedef ft::rb_tree_node< Value >				node_type;
			typedef ft::rb_tree_node< Value >				*node_pointer;

			typedef ft::rb_tree_iterator< Value >			iterator;
			typedef ft::rb_tree_iterator< const Value >		const_iterator;

			typedef ft::reverse_iterator< iterator >		reverse_iterator;
			typedef ft::reverse_iterator< const iterator >	const_reverse_iterator;

			typedef typename Allocator::template rebind< node_type >::other
														node_allocator;

	// CONSTRUCTOR
			
			rb_tree( const Compare &comp, const allocator_type &alloc = allocator_type() )
				: _root( NULL ), _size( 0 ), _comp( comp ), _node_alloc( alloc ) { }

			rb_tree( const rb_tree &src )
				: _root( NULL ), _size( 0 ), _comp( src._comp ), _node_alloc( src._node_alloc )
			{
				*this = src;
			}

	// DESTRUCTOR

			~rb_tree( void )
			{
				this->clear();
			}

	// ASSIGNMENT OPERATOR

			rb_tree		&operator=( const rb_tree &rhs )
			{
				if (this != &rhs)
				{
					this->clear();
					this->_comp = rhs._comp;
					if (rhs._root)
					{
						// copying or insert
					}
				}

				return *this;
			}

	// MEMBER FUNCTION

		// Member functions for Iterator
		
			iterator				begin( void );
			const_iterator			begin( void ) const;

			iterator				end( void );
			const_iterator			end( void ) const;

			reverse_iterator		rbegin( void );
			const_reverse_iterator	rbegin( void ) const;

			reverse_iterator		rend( void );
			const_reverse_iterator	rend( void ) const;

		// Member functions for Observers
			
			key_compare				key_comp( void ) const
			{
				return this->_comp;
			}

// 			size_type	countBlackNodes( node_pointer node )
// 			{
// 				if (!node)
// 					return 1;

// 				size_type	rightBlackNode = countBlackNodes(node->right);
// 				size_type	leftBlackNode = countBlackNodes(node->left);

// 				if (rightBlackNode != leftBlackNode)
// 				{
// 					// throw error
// 					// or fix the tree
// 				}
// 				else
// 				{
// 					if (node->color == black)
// 						leftBlackNode++;
// 					return leftBlackNode;
// 				}
// 			}

			size_type	getHeight( void )
			{
				if (!_root)
					return 0;
				return height(_root) - 1;
			}

			size_type	height( node_pointer node )
			{
				if (!node)
					return 0;
					
				size_type	leftheight = height(node->left) + 1;
				size_type	rightheight = height(node->right) + 1;
				
				if (leftheight > rightheight)
					return leftheight;
					
				return rightheight;
			}

			ft::pair<node_pointer, bool>		insert( const value_type &v )
			{
				node_pointer	node = new node_pointer(v);
				
				if (!_root)
				{
					_root = node;
					_root->color = black;
					_size++;
				}
				else
				{
					_insert(_root, node);
					_size++;
				}
			}

		private:

			node_pointer	_root;
			size_type		_size;
			key_compare		_comp;
			node_allocator	_node_alloc;

	// PRIVATE MEMBER FUNCTION


			void		_rotateLeftRight(node_pointer grandparent)
			{
				_rotateLeft(grandparent->left);
				_rotateRight(grandparent);
			}

			void		_rotateRightLeft(node_pointer grandparent)
			{
				_rotateRight(grandparent->right);
				_rotateLeft(grandparent);
			}

			void		_rotateRight(node_pointer grandparent)
			{
				node_pointer	tmp = grandparent->left;
				grandparent->left = tmp->right;
				if (grandparent->left)
				{
					grandparent->left->parent = grandparent;
					grandparent->left->is_left = true;
				}
				if (grandparent->parent == NULL) // grandparent is root
				{
					_root = tmp;
					tmp->parent = NULL;
				}
				else
				{
					tmp->parent = grandparent->parent;
					if (grandparent->is_left)
					{
						tmp->is_left = true;
						tmp->parent.left = tmp;
					}
					else
					{
						tmp->is_left = false;
						tmp->parent->right = tmp;
					}
				}
				tmp->right = grandparent;
				grandparent->is_left = false;
				grandparent->parent = tmp;
			}

			void		_rotateLeft(node_pointer grandparent)
			{
				node_pointer	tmp = grandparent->right;
				grandparent->right = tmp->left;
				if (grandparent->right)
				{
					grandparent->right->parent = grandparent;
					grandparent->right->is_left = false;
				}
				if (grandparent->parent == NULL) // grandparent is root
				{
					_root = tmp;
					tmp->parent = NULL;
				}
				else
				{
					tmp->parent = grandparent->parent;
					if (grandparent->is_left)
					{
						tmp->is_left = true;
						tmp->parent.left = tmp;
					}
					else
					{
						tmp->is_left = false;
						tmp->parent->right = tmp;
					}
				}
				tmp->left = grandparent;
				grandparent->is_left = true;
				grandparent->parent = tmp;
			}

			void		_rotate(node_pointer node)
			{
				if (node->is_left)
				{
					if (node->parent->is_left)
					{
						_rotateRight(node->parent->parent);
						node->color = red;
						node->parent->color = black;
						if (node->parent->right)
							node->parent->right->color = red;
					}
					else
					{
						_rotateRightLeft(node->parent->parent);
						node->color = black;
						node->right->color = red;
						node->left->color = red;
					}
				}
				else
				{
					if (node->parent->is_left)
					{
						_rotateLeft(node->parent->parent);
						node->color = red;
						node->parent->color = black;
						if (node->parent->right)
							node->parent->right->color = red;
					}
					else
					{
						_rotateLeftRight(node->parent->parent);
						node->color = black;
						node->right->color = red;
						node->left->color = red;
					}
				}
			}

			void		_correctTree(node_pointer node)
			{
				if (node->parent->is_left) // aunt is grandparent right child
				{
					if (node->parent->parent->right == NULL || node->parent->parent->right->color == black)
						return _rotate(node);
					if (node->parent->parent->right != NULL)
						node->parent->parent->right->color = black;
					node->parent->parent->color = red;
					node->parent->color = black;
				}
				else // aunt is grandparent left child
				{
					if (node->parent->parent->left == NULL || node->parent->parent->left->color == black)
						return _rotate(node);
					if (node->parent->parent->left != NULL)
						node->parent->parent->left->color = black;
					node->parent->parent->color = red;
					node->parent->color = black;
				}
			}

			void		_checkColor(node_pointer node)
			{
				if (node == _root)
					return ;
				if (node->color == red && node->parent->color == red)
					_correctTree(node);
			}

			void		_insert( node_pointer parent, node_pointer newNode )
			{
				if(_comp(parent->value, newNode->value))
				{
					if (!parent->right)
					{
						parent->right = newNode;
						newNode->parent = parent;
						newNode->is_left = false;
					}
					else
						_insert(parent->right, newNode);
				}
				else
				{
					if (!parent->left)
					{
						parent->left = newNode;
						newNode->parent = parent;
						newNode->is_left = true;
					}
					else
						_insert(parent->left, newNode);
				}
				
				_checkColor(newNode);
			}
	};
	
}

#endif
