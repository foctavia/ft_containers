/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   type_traits.hpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: foctavia <foctavia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/25 11:03:08 by foctavia          #+#    #+#             */
/*   Updated: 2023/01/25 15:07:58 by foctavia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TYPE_TRAITS_HPP
# define TYPE_TRAITS_HPP

namespace ft
{
	// enable_if 
	
	template< bool, typename T = void >
	struct enable_if { };

	template< typename T >
	struct enable_if< true, T > 
	{
		typedef T	type;
	};
	
	// is_integral

		// integral_constant
		
	template< typename T, T v >
	struct integral_constant
	{
		static const T						value = v;
		typedef T							value_type;
		typedef integral_constant< T, v >	type;
	};

	typedef integral_constant< bool, true >		true_type;
	typedef integral_constant< bool, false >	false_type;
	
		// _is_integral_helper

	template< typename >
	struct _is_integral_helper : public false_type { };
	
	template<>
	struct _is_integral_helper< bool > : public true_type { };

	template<>
	struct _is_integral_helper< char > : public true_type { };

	template<>
	struct _is_integral_helper< signed char > : public true_type { };

	template<>
	struct _is_integral_helper< unsigned char > : public true_type { };

	template<>
	struct _is_integral_helper< wchar_t > : public true_type { };

	template<>
	struct _is_integral_helper< short > : public true_type { };

	template<>
	struct _is_integral_helper< unsigned short > : public true_type { };

	template<>
	struct _is_integral_helper< int > : public true_type { };
	
	template<>
	struct _is_integral_helper< unsigned int > : public true_type { };

	template<>
	struct _is_integral_helper< long > : public true_type { };
		
	template<>
	struct _is_integral_helper< unsigned long > : public true_type { };

	template<>
	struct _is_integral_helper< long long > : public true_type { };

	template<>
	struct _is_integral_helper< unsigned long long > : public true_type { };

		// remove_const

	template< typename T >
	struct remove_const { typedef T	type; };

	template< typename T >
	struct remove_const< T const > { typedef T	type; };

		// remove_volatile

	template< typename T >
	struct remove_volatile { typedef T	type; };

	template< typename T >
	struct remove_volatile<T volatile> { typedef T	type; };

		// remove_cv

	template< typename T >
	struct remove_cv
	{
		typedef typename remove_const< typename remove_volatile< T >::type >::type	type;
	};

		// is_integral

	template< typename T >
	struct is_integral
		: public integral_constant< bool, ( _is_integral_helper< typename remove_cv< T >:: type >::value ) >
	{ };
}

#endif
