/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rb_tree.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: foctavia <foctavia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/07 10:58:01 by foctavia          #+#    #+#             */
/*   Updated: 2023/02/14 14:15:01 by foctavia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RB_TREE_HPP
# define RB_TREE_HPP

# include <functional>

# include <rb_tree_utils.hpp>
# include <utility.hpp>
# include <reverse_iterator.hpp>

namespace ft
{
	/* RB_TREE **************************************************************************** */

	template< typename Value, typename Compare, 
				typename Allocator = std::allocator< Value > >
	class rb_tree
	{
		public:

			typedef Value									value_type;
			typedef Compare									value_compare;
			typedef std::allocator<Value>					value_allocator;	
			typedef Allocator								allocator_type;
			
			typedef typename Allocator::size_type			size_type;
			typedef typename Allocator::difference_type		difference_type;
			
			typedef typename Allocator::reference			reference;
			typedef typename Allocator::const_reference		const_reference;
			typedef typename Allocator::pointer				pointer;
			typedef typename Allocator::const_pointer		const_pointer;
			
			typedef ft::rb_tree_node< value_type >			node_type;
			typedef ft::rb_tree_node< value_type >			*node_pointer;

			typedef ft::rb_tree_iterator< Value >			iterator;
			typedef ft::rb_tree_iterator< const Value >		const_iterator;

			typedef ft::reverse_iterator< iterator >		reverse_iterator;
			typedef ft::reverse_iterator< const_iterator >	const_reverse_iterator;

			typedef typename Allocator::template rebind< node_type >::other
															node_allocator;

	// CONSTRUCTOR
			
			explicit rb_tree( const value_compare &comp = value_compare(), const allocator_type &alloc = node_allocator() )
				: _root( NULL ), _size( 0 ), _comp( comp ), _node_alloc( alloc )
			{
				this->_root = _createNIL();
			}

			rb_tree( const rb_tree &src )
				: _nil( NULL ), _root( NULL ), _size( 0 ), _comp( src._comp ), _node_alloc( src._node_alloc )
			{
				*this = src;
			}

	// DESTRUCTOR

			~rb_tree( void )
			{
				this->clear();
			}

	// ASSIGNMENT OPERATOR

			rb_tree						&operator=( const rb_tree &rhs )
			{
				// if (this != &rhs)
				// {
					this->clear();
					this->_comp = rhs._comp;
					this->_node_alloc = rhs._node_alloc;
					this->_root = _createNIL();
					if (rhs._root)
					{
						this->insert(rhs.begin(), rhs.end());
					}
				// }

				return *this;
			}

	// MEMBER FUNCTION
	
		// Getter

			allocator_type				get_allocator( void ) const	{ return allocator_type(_node_alloc); }

	// 	// Member functions for Iterator
		
			iterator					begin( void )				{ return iterator(_getMin()); }
			const_iterator				begin( void ) const			{ return const_iterator(_getMin()); }

			iterator					end( void )					{ return iterator(_nil); }
			const_iterator				end( void ) const			{ return const_iterator(_nil); }


	// 	// Member functions for Capacity

			size_type					size( void ) const			{ return this->_size; }

			size_type					max_size( void ) const		{ return this->_node_alloc.max_size(); }

	// 	// Member functions for Modifiers
		
			void						clear( void )
			{
				_clear(_root);
				// if (_nil)
				// 	_clear(_nil);
				_size = 0;
			}

			ft::pair< iterator, bool >	insert( const value_type &val )
			{
				node_pointer	tmp = find(val);
				
				if (tmp != _nil)
					return ft::make_pair(iterator(tmp), false);
				
				node_pointer	node = _createNode(val);
				
				if (_root == _nil)
				{
					_root = node;
					_root->color = black;
					_attachNIL();
					_size++;
				}
				else
				{
					_detachNIL();
					_insert(_root, node);
					_attachNIL();
					_size++;
				}
				
				return ft::make_pair(iterator(node), true);
			}
	
			template< class InputIt >
			void						insert( InputIt first, InputIt last, typename ft::enable_if<!ft::is_integral<InputIt>::value, InputIt>::type* = 0 )
			{
				size_type	distance = std::distance(first, last);
				
				if (distance && distance < max_size())
				{
					for(; first != last; ++first)
						insert(*first);
				}
			}

	//		iterator					erase( iterator pos );
			
	// 		iterator					erase( iterator first, iterator last );

	//		size_type					erase( const value_type &val );

			void						swap( rb_tree &other )
			{
				node_pointer	tmp_nil			= _nil;
				node_pointer	tmp_root		= _root;
				size_type		tmp_size		= _size;
				value_compare	tmp_comp		= _comp;
				node_allocator	tmp_node_alloc	= _node_alloc;

				this->_nil						= other._nil;
				this->_root						= other._root;
				this->_size						= other._size;
				this->_comp						= other._comp;
				this->_node_alloc				= other._node_alloc;
				
				other._nil						= tmp_nil;
				other._root						= tmp_root;
				other._size						= tmp_size;
				other._comp						= tmp_comp;
				other._node_alloc				= tmp_node_alloc;
			}
	
		// Member functions for Lookup

			// node_pointer				get_node(node_pointer node, const value_type &val)
			// {
			// 	if (node == _nil)
			// 		return node;
			// 	if (_comp(val, node->value) && !_comp(node->value, val))
			// 		return (get_node(node->left, val));
			// 	if (!_comp(val, node->value) && _comp(node->value, val))
			// 		return (get_node(node->right, val));
					
			// 	return node;
			// }

			node_pointer				get_node(const value_type &val )
			{
				node_pointer	tmp = _root;

				while (tmp != _nil)
				{
					if (_comp(val, tmp->value))
						tmp = tmp->left;
					else if (_comp(tmp->value, val))
						tmp = tmp->right;
					else
						break ;
				}

				return tmp;
			}

			node_pointer			find( const value_type &val )
			{
				node_pointer	tmp = lower_bound(val);

				if (tmp == _nil || _comp(val, tmp->value))
					return _nil;

				return tmp;
			}

			node_pointer			lower_bound(const value_type &val )
			{
				node_pointer	tmp = _root;
				node_pointer	lower = _nil;
				
				while (tmp && tmp != _nil)
				{	
					if (!_comp(tmp->value, val))
					{
						lower = tmp;
						tmp = tmp->left;
					}
					else
						tmp = tmp->right;
				}

				return lower;
			}

			node_pointer			upper_bound( const value_type &val )
			{
				node_pointer	tmp = _root;
				node_pointer	upper = _nil;

				while (tmp != _nil)
				{
					if (_comp(val, tmp->value))
					{
						upper = tmp;
						tmp = tmp->left;
					}
					else
						tmp = tmp->right;
				}

				return upper;
			}

		private:

			node_pointer	_nil;
			node_pointer	_root;
			size_type		_size;
			value_compare	_comp;
			node_allocator	_node_alloc;

	// PRIVATE MEMBER FUNCTION

			node_pointer	_createNode( const value_type &val )
			{
				node_pointer	newNode = _node_alloc.allocate(1);
				
				_node_alloc.construct(newNode, val);
				// get_allocator().construct(&(newNode->value), val);

				return newNode;
			}

			node_pointer	_createNIL( void )
			{
				_nil = _createNode(value_type());
				_nil->parent = _root;
				_nil->right = _nil->left = NULL;
				_nil->is_left = false;
				_nil->color = black;

				return _nil;
			}

			node_pointer	_getMin( void )
			{
				node_pointer	tmp = _root;
				
				while (tmp && tmp->left)
					tmp = tmp->left;
					
				return tmp;
			}

			node_pointer	_getMax( void )
			{
				node_pointer	tmp = _root;
				
				while (tmp && tmp->right && tmp->right != _nil)
					tmp = tmp->right;
					
				return tmp;
			}
			
			void			_detachNIL( void )
			{
				node_pointer	tmp = _getMax();

				if (tmp && tmp != _nil)
				{
					tmp->right = NULL;
					_nil->parent = NULL;
				}
			}

			void			_attachNIL( void )
			{
				node_pointer	tmp = _getMax();

				if (tmp && tmp != _nil)
				{
					tmp->right = _nil;
					_nil->parent = tmp;
				}
			}

			void					_clear( node_pointer current )
			{
				if (!current)
					return ;
				if (current->left)
					_clear(current->left);
				if (current->right)
					_clear(current->right);
				// get_allocator().destroy(&(current->value));
				_node_alloc.destroy(current);
				_node_alloc.deallocate(current, 1);
				current = NULL;
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

			size_type	_getHeight( void )
			{
				if (!_root)
					return 0;
				return height(_root) - 1;
			}

			size_type	_height( node_pointer node )
			{
				if (!node)
					return 0;
					
				size_type	leftheight = height(node->left) + 1;
				size_type	rightheight = height(node->right) + 1;
				
				if (leftheight > rightheight)
					return leftheight;
					
				return rightheight;
			}

			void			_rotateLeftRight(node_pointer grandparent)
			{
				_rotateLeft(grandparent->left);
				_rotateRight(grandparent);
			}

			void			_rotateRightLeft(node_pointer grandparent)
			{
				_rotateRight(grandparent->right);
				_rotateLeft(grandparent);
			}

			void			_rotateRight(node_pointer grandparent)
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
						tmp->parent->left = tmp;
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

			void			_rotateLeft(node_pointer grandparent)
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
						tmp->parent->left = tmp;
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

			void			_rotate(node_pointer node)
			{
				if (node->is_left && node->parent->is_left) // node is left child and parent is left child
				{
					_rotateRight(node->parent->parent);
					node->color = red;
					node->parent->color = black;
					if (node->parent->right)
						node->parent->right->color = red;
				}
				else if (node->is_left && !node->parent->is_left) // node is left child and parent is right child
				{
					_rotateRightLeft(node->parent->parent);
					node->color = black;
					node->right->color = red;
					node->left->color = red;
				}
				else if (!node->is_left && !node->parent->is_left) // node is right child and parent is right child
				{
					_rotateLeft(node->parent->parent);
					node->color = red;
					node->parent->color = black;
					if (node->parent->left)
						node->parent->left->color = red;
				}
				else // node is right child and parent is left child
				{
					_rotateLeftRight(node->parent->parent);
					node->color = black;
					node->right->color = red;
					node->left->color = red;
				}
			}

			node_pointer	_getAunt(node_pointer node)
			{
				if (!node->parent)
					return NULL;
				if (node->parent->is_left) // if parent is left child then aunt is right child of grandparent
					return node->parent->parent->right;
				
				return node->parent->parent->left;	// if parent is right child then aunt is left child of grandparent
			}

			void			_colorFlip(node_pointer node)
			{
				node_pointer	aunt = _getAunt(node);
				
				if (aunt)
					aunt->color = black;		
				node->parent->parent->color = red;
				node->parent->color = black;
			}

			void			_correctTree(node_pointer node)
			{
				node_pointer	aunt = _getAunt(node);

				if (aunt == NULL || aunt->color == black)
					return _rotate(node);
				_colorFlip(node);
			}

			void			_checkColor(node_pointer node)
			{
				if (node == _root)
				{
					node->color = black;
					return ;
				}
				if (node && node->color == red && node->parent->color == red)
					_correctTree(node);
				if (node && node->parent)
					_checkColor(node->parent);
			}

			void			_insert( node_pointer parent, node_pointer newNode )
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
