/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rb_tree.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: foctavia <foctavia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/07 10:58:01 by foctavia          #+#    #+#             */
/*   Updated: 2023/02/19 18:15:11 by foctavia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RB_TREE_HPP
# define RB_TREE_HPP

# define BLACK "\033[1;30m"
# define RED "\033[1;31m"
# define GREEN "\033[1;32m"
# define RESET "\033[m"

# include <functional>

# include "rb_tree_utils.hpp"
# include "utility.hpp"
# include "reverse_iterator.hpp"

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
			typedef ft::rb_tree_const_iterator< Value >		const_iterator;

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
				this->_destroyNode(_nil);
			}

	// ASSIGNMENT OPERATOR

			rb_tree						&operator=( const rb_tree &rhs )
			{
				this->clear();
				
				this->_comp = rhs._comp;
				this->_node_alloc = rhs._node_alloc;
				if (rhs._root)
				{
					this->insert(rhs.begin(), rhs.end());
				}

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
				
				_nil->parent = _root;
				_nil->left = _nil->right = NULL;
				_nil->is_left = false;
				_nil->color = black;
				_root = _nil;
				
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
					_size++;
					_attachNIL();
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
			
			void	_correctTreeErase(node_pointer parent, bool is_left)
			{
				node_pointer	sister = _getSibling(parent, is_left);
				node_pointer	child = _getChild(parent, is_left);

				

				if (parent)
					std::cout << "parent value is " << parent->value.first << " color is " << parent->color << std::endl;
				if (is_left)
					std::cout << "it is left" << std::endl;
				else 
					std::cout << "it is right" << std::endl;

				if (child && child->color == red)
				{
					child->color = black;
					return ;
				}
				
				if (is_left)
				{	
					if (sister && sister->color == red)
					{
						if (sister)
							std::cout << "red sister value is " << sister->value.first << std::endl;
						sister->color = black;
						parent->color = red;
						_rotateLeft(parent);
						_correctTreeErase(parent, is_left);
					}
					if (sister && (!sister->right || (sister->right && sister->right->color == black)) && (!sister->left || (sister->left && sister->left->color == black)))
					{
						if (sister)
							std::cout << "1. black sister value is " << sister->value.first << std::endl;
						sister->color = red;
						if (parent->color == red)
						{
							std::cout << "it stop!" << std::endl;
							parent->color = black;
							return ;
						}
						else if (parent->color == black && parent == _root)
						{
							
							return ;
						}
						else
						{
							
							_correctTreeErase(parent->parent, parent->is_left);
						}
					}
					else
					{
						if (sister && sister->right && sister->right->color == black)
						{
							if (sister->left)
								sister->left->color = black;
							sister->color = red;
							_rotateRight(sister);
							sister = parent->right;
						}							
						sister->color = parent->color;
						parent->color = black;
						if (sister->right)
							sister->right->color = black;
						_rotateLeft(parent);
					}
				}
				else
				{
					if (sister && sister->color == red)
					{
						sister->color = black;
						parent->color = red;
						_rotateRight(parent);
						_correctTreeErase(parent, is_left);
					}
					if (sister && (!sister->left || (sister->left && sister->left->color == black)) && (!sister->right || (sister->right && sister->right->color == black)))
					{
						sister->color = red;
						if (parent->color == red)
						{
							parent->color = black;
							return ;
						}
						else if (parent->color == black && parent == _root)
							return ;
						else
							_correctTreeErase(parent->parent, parent->is_left);
					}
					else
					{
						if (sister && sister->left && sister->left->color == black)
						{
							if (sister->right)
								sister->right->color = black;
							sister->color = red;
							_rotateLeft(sister);
							sister = parent->left;
						}
						sister->color = parent->color;
						parent->color = black;
						if (sister->left)
							sister->left->color = black;
						_rotateRight(parent);
					}
				}
			}

			node_pointer				_getSibling(node_pointer parent, bool is_left)
			{	
				if (is_left)
					return parent->right;
				return parent->left;
			}

			node_pointer				_getChild(node_pointer parent, bool is_left)
			{	
				if (is_left)
					return parent->left;
				return parent->right;
			}

			void	_checkColorErase(node_pointer node, node_pointer replace, node_pointer parent, bool is_left)
			{		
				if (node->color == black && replace && replace->color == red)
					replace->color = black;
				else if (node->color == red && replace && replace->color == black)
				{
					replace->color = red;
					_erase_fix(parent, is_left);
				}
				else if (node->color == black && (!replace || (replace && replace->color == black)) && _getChild(parent, is_left) != _root)
					_erase_fix(parent, is_left);
			}

			void						_replaceNode(node_pointer node, node_pointer replace)
			{
				bool				is_left = node->is_left;
				node_pointer		parent = node->parent;
				node_pointer		left = node->left;
				node_pointer		right = node->right;

				if (node == _root)
				{
					_root = replace;
					_root->parent = NULL;
					_root->color = black;
				}
				else if (!parent)
					_root = replace;	
				else
				{
					if (is_left)
						parent->left = replace;
					else
						parent->right = replace;
				}
				
				if (replace)
				{	
					replace->parent = parent;
					replace->is_left = is_left;
					if (left != replace)
						replace->left = left;
					if (right != replace)
						replace->right = right;
					if (left && left != replace)
						left->parent = replace;
					if (right && right != replace)
						right->parent = replace;
				}	
			}

			void			_erase(node_pointer node)
			{
				node_pointer	replace = NULL;
				node_pointer	parent = NULL;
				bool			is_left;

				if (!node->left && !node->right)
				{
					_replaceNode(node, NULL);
					parent = node->parent;
					is_left = node->is_left;
				}
				else if (!node->left || !node->right)
				{
					if (!node->right)
						replace = node->left;
					else
						replace = node->right;
					is_left = replace->is_left;
					parent = node->parent;
					_replaceNode(node, replace);
				}
				else
				{
					replace = _getSuccessor(node);
					if (replace == node->right)
					{
						is_left = replace->is_left;
						parent = replace;
						_replaceNode(node, replace);
					}
					else
					{
						parent = replace->parent;
						is_left = replace->is_left;
						_replaceNode(replace, replace->right);
						_replaceNode(node, replace);
					}
				}
				
				if (parent)
					_checkColorErase(node, replace, parent, is_left);
				
				_destroyNode(node);
			}

			size_type					erase( const value_type &value )
			{
				node_pointer	tmp = find(value);
				
				if (tmp == _nil)
					return 0;
					
				if (_size == 1)
					clear();
				else
				{	
					_detachNIL();
					_erase(tmp);
					_attachNIL();
					_size--;
				}
				displayTree();

				return 1;
			}

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

			// node_pointer				find( value_type val )
			// {
			// 	node_pointer	tmp = _root;

			// 	while (tmp && tmp != _nil)
			// 	{
			// 		if (_comp(val, tmp->value))
			// 			tmp = tmp->left;
			// 		else if (_comp(tmp->value, val))
			// 			tmp = tmp->right;
			// 		else
			// 			break ;
			// 	}

			// 	return tmp;
			// }

			node_pointer			find( value_type val ) const
			{
				node_pointer	tmp = lower_bound(val);

				if (tmp == _nil || _comp(val, tmp->value))
					return _nil;

				return tmp;
			}

			node_pointer			lower_bound( value_type val ) const
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

			node_pointer			upper_bound( value_type val ) const
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
			
			void	displayTree( void )
			{
				if (_root)
				{
					_treeHelper("", _root, true);
					std::cout << std::endl;
				}
				_check_rules_violation();
			}

		private:

			node_pointer	_nil;
			node_pointer	_root;
			size_type		_size;
			value_compare	_comp;
			node_allocator	_node_alloc;

	// PRIVATE MEMBER FUNCTION

			node_pointer	_createNode( value_type val )
			{
				node_pointer	newNode = _node_alloc.allocate(1);
				
				_node_alloc.construct(newNode, val);

				return newNode;
			}

			void			_destroyNode( node_pointer node )
			{
				_node_alloc.destroy(node);
				_node_alloc.deallocate(node, 1);
				
				node = NULL;
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

			node_pointer	_getSuccessor(node_pointer node)
			{
				node_pointer	successor = node->right;
				
				while (successor && successor->left)
					successor = successor->left;

				return successor;
			}

			node_pointer	_getMin( void ) const
			{
				node_pointer	tmp = _root;
				
				while (tmp && tmp->left)
					tmp = tmp->left;
					
				return tmp;
			}

			node_pointer	_getMax( void ) const
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

			void			_clear( node_pointer current )
			{
				if (current == _nil || !current)
					return ;
				if (current->left)
					_clear(current->left);
				if (current->right)
					_clear(current->right);
					
				_destroyNode(current);
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
				if (node->parent && node->parent->parent && node->parent->parent != _root)	
					node->parent->parent->color = red;
				if (node->parent)
					node->parent->color = black;
			}

			void			_correctTreeInsert(node_pointer node)
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
					_correctTreeInsert(node);
				
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

			bool	_check_black_nodes( node_pointer node, int black_count, int &path_black_count)
			{
				if (!node)
				{
					if (path_black_count == -1)
						path_black_count = black_count;
					else if (path_black_count != black_count)
					{
						std::cout << "There isn't the same amount of black nodes in each path from root to null!" << std::endl;
						return false; 
					}
					return true;
				}
				if (node != _nil && node->color == black)
					black_count++;
				return _check_black_nodes(node->left, black_count, path_black_count) && _check_black_nodes(node->right, black_count, path_black_count);
			}

			bool	_check_consecutive_red( node_pointer node )
			{
				if (!node)
					return true;
				if (node->color == red && node->parent && node->parent->color == red)
				{
					std::cout << "There are two consecutive red nodes in the tree!" << std::endl;
					return false;
				}
				return _check_consecutive_red(node->left) && _check_consecutive_red(node->right);
			}

			void	_check_rules_violation( void)
			{
				bool	violation = false;

				if (_root->color == red)
				{
					violation = true;
					std::cout << "Root is not black as supposed to!" << std::endl;
				}
				int		path_black_count = -1;
				if (!_check_black_nodes(_root, 0, path_black_count))
					violation = true;
				if (!_check_consecutive_red(_root))
					violation = true;
				if (violation)
					std::cout << RED << "One of the red black tree rules has been violated" << RESET << std::endl << std::endl;
				else
					std::cout << GREEN << "Tree is balanced!" << RESET << std::endl << std::endl;
			}

			void	_treeHelper(std::string prefix, node_pointer node, bool is_left)
			{
				if (node)
				{
					_treeHelper(prefix + "	", node->right, false);
					std::cout << prefix;
					std::cout << (is_left ? "└──" : "┌──");
					if (node != _nil)
					{
						if (node->color == red)
							std::cout << RED;
						else
							std::cout << BLACK;
						std::cout << " " << node->value.first << RESET << std::endl;
					}
					else
						std::cout << " #" << std::endl;
					_treeHelper(prefix + (is_left ? "	" : "|	"), node->left, true);
				}
			}

			void	_printTree( node_pointer node )
			{
				if (node && node != _nil)
				{
					std::cout << node->value.first << ". parent is " << node->parent << " left is "  << node->left << " right is " << node->right << std::endl;
				}
			}

			

			void	printTree( void )
			{
				node_pointer	first = _getMin();
				
				while(first != _nil)
				{
					_printTree(first);
					first++;
				}
			}
			
	};
}

#endif
