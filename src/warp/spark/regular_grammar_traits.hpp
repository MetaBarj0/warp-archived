#ifndef _WARP_REGULAR_GRAMMAR_TRAITS_HPP_
#define _WARP_REGULAR_GRAMMAR_TRAITS_HPP_

#include "../core/type_traits.hpp"

#include <cstdlib>

namespace
{
  template< class T >
    struct char_buffer_value_traits
    {
      static constexpr bool is_valid =
        warp::has_static_char_buffer_value_member< T >::value ^
        warp::has_static_char_buffer_value_method< T >::value;
    };

  template< class >
    struct is_char_buffer_array
    {
      static constexpr bool value = false;
    };

  template< class T, std::size_t N >
    struct is_char_buffer_array< T[ N ] >
    {
      static constexpr bool value =
        ( N > 0 ) &&
        ( warp::is_char_buffer< T >::value );
    };

  template< class, class = typename warp::sfinae_type<>::type >
    struct has_static_char_buffer_array_member
    {
      static constexpr bool value = false;
    };

  template< class T >
    struct has_static_char_buffer_array_member
    < T, typename warp::sfinae_type< decltype( T::array ) >::type >
    {
      static constexpr bool value =
        is_char_buffer_array< decltype( T::array ) >::value;
    };

  template< class T >
    struct char_buffer_array_traits
    {
      static constexpr bool is_valid =
        has_static_char_buffer_array_member< T >::value;
    };
}

namespace warp::spark
{
template< class T >
  struct regular_grammar_definition_traits
  {
    static constexpr bool is_valid =
      char_buffer_value_traits< T >::is_valid ^
      char_buffer_array_traits< T >::is_valid;

    using sequence_type = warp::undefined_type;
  };

template< template< class T, T... > class S, class C, C... VS >
  struct regular_grammar_definition_traits< S< C, VS... > >
  {
    static constexpr bool is_valid = is_char< C >::value;

    using sequence_type = S< C, VS... >;
  };
}

#endif // _WARP_REGULAR_GRAMMAR_TRAITS_HPP_
