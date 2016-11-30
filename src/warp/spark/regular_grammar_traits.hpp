#ifndef _WARP_SPARK_REGULAR_GRAMMAR_TRAITS_HPP_
#define _WARP_SPARK_REGULAR_GRAMMAR_TRAITS_HPP_

#include "regular_grammar.hpp"
#include "../core/type_traits.hpp"
#include "../sequences/algorithm.hpp"

#include <cstdlib>
#include <type_traits>

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

  template< class, class >
    struct join_array_in_sequence;

  template< class T, class U, std::size_t N >
    struct join_array_in_sequence< T, U[ N ] >
    {
      using char_type = std::remove_pointer_t< U >;

      template< class S, std::size_t I >
        struct push_front_char_buffer_in_sequence
        {
          struct current_buffer
          {
            static constexpr auto value = T::array[ I ];
          };

          using current_sequence =
            warp::append_char_buffer_in_t
            < warp::integral_sequence< char_type >, current_buffer >;

          using type =
            typename push_front_char_buffer_in_sequence
            <
              warp::merge_sequence_t< current_sequence, S >,
              I - 1
            >::type;
        };

      template< class S >
        struct push_front_char_buffer_in_sequence< S, 0 >
        {
          struct current_buffer
          {
            static constexpr auto value = T::array[ 0 ];
          };

          using current_sequence =
            warp::append_char_buffer_in_t
            < warp::integral_sequence< char_type >, current_buffer >;

          using type = warp::merge_sequence_t< current_sequence, S >;
        };

      using type =
        typename push_front_char_buffer_in_sequence
        < warp::integral_sequence< char_type >, N - 1 >::type;
    };

  template< class, bool, class = warp::sfinae_type<>::type >
    struct build_sequence_from
    {
      using type = warp::undefined_type;
    };

  template< class T >
    struct build_sequence_from
    <
      T, true,
      typename warp::sfinae_type
        <
          std::enable_if_t
            < warp::is_char_buffer< decltype( T::value ) >::value >
        >::type
    >
    {
      using char_type = std::remove_pointer_t< decltype( T::value ) >;

      using type =
        warp::append_char_buffer_in_t
        < warp::integral_sequence< char_type >, T >;
    };

  template< class T >
    struct build_sequence_from
    < T, true, typename warp::sfinae_type< decltype( T::value() ) >::type >
    {
      using char_type = std::remove_pointer_t< decltype( T::value() ) >;

      using type =
        warp::append_char_buffer_in_t
        < warp::integral_sequence< char_type >, T >;
    };

  template< class T >
    struct build_sequence_from
    < T, true, typename warp::sfinae_type< decltype( T::array ) >::type >
    {
      using array_type = decltype( T::array );

      using type = typename join_array_in_sequence< T, array_type >::type;
    };
}

namespace warp::spark
{
  /**
   * \brief Traits class dealing with a regular grammar definition type. This
   * unspecialized version deal with regular grammar definition type exposing
   * either a value or a value() or an array member within.
   *
   * \tparam T the regular grammar definition of form value type or array type
   */
  template< class T >
    struct regular_grammar_definition_traits
    {
      /**
       * \brief Ensures that T::value, t::value() or t::array expressions are of
       * valid char buffer type, using dedicated traits classes. Ensures also
       * that T exposes exclusively one of these form, not several.
       */
      static constexpr bool is_valid =
        char_buffer_value_traits< T >::is_valid ^
        char_buffer_array_traits< T >::is_valid;

      /**
       * \brief Once the validity of T is established, uniform the regular
       * grammar definition string into an integral sequence.
       */
      using sequence = typename build_sequence_from< T, is_valid >::type;
    };

  /**
   * \brief This specialization deals with a regular grammar definition already
   * having the form of an integral sequence. Some compile time computations are
   * unnecessary here and this type only ensures that the integral type used in
   * the sequence is a valid char type.
   *
   * \tparam S integral sequence template
   * \tparam C integral type used in the sequence
   * \tparam VS value pack contained in the integral sequence
   */
  template< template< class T, T... > class S, class C, C... VS >
    struct regular_grammar_definition_traits< S< C, VS... > >
    {
      /**
       * \brief Ensures the integral type of the sequence is a valid char type
       */
      static constexpr bool is_valid = is_char< C >::value;

      /**
       * \brief Finally, exposes the sequence as is, no computations needed
       */
      using sequence = S< C, VS... >;
    };

  template< class T >
    struct regular_grammar_traits;

  template< class T >
    struct regular_grammar_traits< regular_grammar< T > >
    {
      using grammar_definition = T;
    };
}

#endif // _WARP_SPARK_REGULAR_GRAMMAR_TRAITS_HPP_

// doxygen
/**
 * \file
 * \brief This file contains types exposing traits relative to regular_grammar
 * type.
 */
