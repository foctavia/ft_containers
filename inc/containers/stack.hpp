/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stack.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: foctavia <foctavia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/24 12:23:43 by foctavia          #+#    #+#             */
/*   Updated: 2023/01/24 21:18:20 by foctavia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STACK_HPP
# define STACK_HPP

# include <deque>

namespace ft
{
	template< class T, class Container = std::deque<T> >
	class stack
	{
		public:
		
			typedef Container									container_type;
			typedef typename container_type::value_type			value_type;
			typedef typename container_type::size_type			size_type;
			typedef typename container_type::reference			reference;
			typedef typename container_type::const_reference	const_reference;

	// CONSTRUCTOR
			
			explicit stack( const container_type &cont = container_type() ) : _c( cont ) {}
	
	// DESTRUCTOR

			~stack( void ) { this->_c.clear(); }
			
	// ASSIGNMENT OPERATOR

			stack	&operator=( const stack &other )
			{
				if (this != &other)
					this->_c = other._c;
				return *this;
			}

	// MEMBER FUNCTIONS
		// Member functions for Element access

			reference		top( void ) { return this->_c.back(); }
			const_reference	top( void ) { return this->_c.back(); }

		// Member functions for Capacity
		
			bool			empty( void ) const { return this->_c.empty(); }
			size_type		size( void ) const { return this->_c.size(); }

		// Member functions for Modifiers

			void			push( const value_type &value ) { this->_c.push_back(value); }
			void			pop( void ) { this->_c.pop_back(); }

	// NON-MEMBER FUNCTIONS
		
			template< class T, class Container >
			bool	operator==( const ft::vector<T, Allocator> &lhs, const ft::vector<T, Allocator> &rhs )
			{
				return (lhs._c == rhs._c);
			}
			
			template< class T, class Container >
			bool	operator!=( const ft::vector<T, Allocator> &lhs, const ft::vector<T, Allocator> &rhs )
			{
				return (lhs._c != rhs._c);
			}
			
			template< class T, class Container >
			bool	operator<( const ft::vector<T, Allocator> &lhs, const ft::vector<T, Allocator> &rhs )
			{
				return (lhs._c < rhs._c);
			}
			
			template< class T, class Container >
			bool	operator<=( const ft::vector<T, Allocator> &lhs, const ft::vector<T, Allocator> &rhs )
			{
				return (lhs._c <= rhs._c);
			}
			
			template< class T, class Container >
			bool	operator>( const ft::vector<T, Allocator> &lhs, const ft::vector<T, Allocator> &rhs )
			{
				return (lhs._c > rhs._c);
			}
			
			template< class T, class Container >
			bool	operator>=( const ft::vector<T, Allocator> &lhs, const ft::vector<T, Allocator> &rhs )
			{
				return (lhs._c >= rhs._c);
			}
			
		protected:

			container_type	_c;
			
	};
}

#endif
