/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bidirectional_iterator.hpp                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: foctavia <foctavia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/07 18:19:17 by foctavia          #+#    #+#             */
/*   Updated: 2023/02/07 20:52:42 by foctavia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BIDIRECTIONAL_ITERATOR_HPP
# define BIDIRECTIONAL_ITERATOR_HPP

# include <iterator_traits.hpp>
# include <type_traits.hpp>

namespace ft
{
	/* BIDIRECTIONAL_ITERATOR ************************************************************* */

	template< typename T >
	class bidirectional_iterator : public std::iterator< std::bidirectional_iterator_tag, T, std::ptrdiff_t, T *, T & >
	{		
		protected:

			typedef ft::iterator_traits< T >				traits_type;

		public:
			
			typedef T										*iterator_type;
			typedef std::bidirectional_iterator_tag			iterator_category;
			typedef typename traits_type::value_type		value_type;
			typedef typename traits_type::difference_type	difference_type;
			typedef typename traits_type::reference			reference;
			typedef typename traits_type::pointer			pointer;

	};
	
}

#endif
