/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   iterator_traits.hpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: foctavia <foctavia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/25 16:26:34 by foctavia          #+#    #+#             */
/*   Updated: 2023/02/01 16:09:05 by foctavia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ITERATOR_TRAITS_HPP
# define ITERATOR_TRAITS_HPP

# include <iterator>

namespace ft
{
	/* ITERATOR *************************************************************************** */

	template< class Category, class T, class Distance = std::ptrdiff_t, class Pointer = T*, class Reference = T& >
	struct iterator
	{
		typedef	Category							iterator_category;
		typedef T									value_type;
		typedef Distance							difference_type;
		typedef Pointer								pointer;
		typedef Reference							reference;
	};

	
	/* ITERATOR_TRAITS ******************************************************************** */
	
	template< typename Iter >
	struct iterator_traits
	{
		typedef typename Iter::iterator_category	iterator_category;
		typedef typename Iter::value_type			value_type;
		typedef typename Iter::difference_type		difference_type;
		typedef typename Iter::pointer				pointer;
		typedef typename Iter::reference			reference;
	};
	
	template< typename T >
	struct iterator_traits< T * >
	{
		typedef std::random_access_iterator_tag		iterator_category;
		typedef T									value_type;
		typedef std::ptrdiff_t						difference_type;
		typedef T									*pointer;
		typedef T									&reference;
	};

	template< typename T >
	struct iterator_traits< const T * >
	{
		typedef std::random_access_iterator_tag		iterator_category;
		typedef T									value_type;
		typedef std::ptrdiff_t						difference_type;
		typedef const T								*pointer;
		typedef const T								&reference;	
	};

}

#endif
