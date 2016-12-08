#ifndef _WARP_SPARK_REGULAR_GRAMMAR_TRAITS_HPP_
#define _WARP_SPARK_REGULAR_GRAMMAR_TRAITS_HPP_

#include "regular_grammar.hpp"
#include "../core/type_traits.hpp"
#include "../sequences/algorithm.hpp"

#include <cstdlib>
#include <type_traits>

namespace
{
  /**
   * \brief An internal feature joining char buffer array within a sequence type
   */
  template< class, class >
    struct join_array_in_sequence;

  /**
   * \brief Specialization dealing with the last element of the array
   *
   * \tparam T the array type, exposing the array member
   * \tparam U the type of the array (char buffer)
   * \tparam N the size of the array
   */
  template< class T, class U, std::size_t N >
    struct join_array_in_sequence< T, U[ N ] >
    {
      /**
       * \brief Grab the char type of the array's element
       */
      using char_type = std::remove_pointer_t< U >;

      /**
       * \brief Push an array element inside the specified sequence
       *
       * \brief S sequence in which push front a buffer
       * \tparam I index where a buffer is located in T::array
       */
      template< class S, std::size_t I >
        struct push_front_char_buffer_in_sequence
        {
          /**
           * \brief Makes a value type with array's element
           */
          struct current_buffer
          {
            /**
             * \brief Mandatory to build a value type
             */
            static constexpr auto value = T::array[ I ];
          };

          /**
           * \brief Build a temporary sequence with found buffer
           */
          using current_sequence =
            warp::append_char_buffer_in_t
            < warp::integral_sequence< char_type >, current_buffer >;

          /**
           * \brief merge the temporary sequence inside the target one, then,
           * recursively call the feature
           */
          using type =
            typename push_front_char_buffer_in_sequence
            <
              warp::merge_sequence_t< current_sequence, S >,
              I - 1
            >::type;
        };

      /**
       * \brief Adds the last array element inside the sequence
       *
       * \tparam S the sequence containing all array buffer but the first
       */
      template< class S >
        struct push_front_char_buffer_in_sequence< S, 0 >
        {
          /**
           * \brief A value type containing the array element
           */
          struct current_buffer
          {
            /**
             * \brief Requirement for a value type
             */
            static constexpr auto value = T::array[ 0 ];
          };

          /**
           * \brief Create a temporary sequence with the current buffer
           */
          using current_sequence =
            warp::append_char_buffer_in_t
            < warp::integral_sequence< char_type >, current_buffer >;

          /**
           * \brief Uses the merge algorithm to obtain the final sequence
           */
          using type = warp::merge_sequence_t< current_sequence, S >;
        };

      /**
       * \brief add this char buffer to the resulting sequence
       */
      using type =
        typename push_front_char_buffer_in_sequence
        < warp::integral_sequence< char_type >, N - 1 >::type;
    };

  /**
   * \brief How to build an integral sequence from a constexpr array or string?
   * Use this type.
   */
  template< class, class = warp::sfinae_type<>::type >
    struct build_sequence_from
    {
      /**
       * \brief SFINAE friendly specialization detecting that the template
       * parameter passed is not an array type nor a value type
       */
      using type = warp::undefined_type;
    };

  /**
   * \brief SFINAE friendly specialization triggered if provided template
   * parameter is a value type of char type
   *
   * \tparam T a value type containing a value member of char type
   */
  template< class T >
    struct build_sequence_from
    <
      T,
      typename warp::sfinae_type
        <
          std::enable_if_t
            < warp::is_char_buffer< decltype( T::value ) >::value >
        >::type
    >
    {
      /**
       * \brief Grab the char type
       */
      using char_type = std::remove_pointer_t< decltype( T::value ) >;

      /**
       * \brief expose the resulting sequence
       */
      using type =
        warp::append_char_buffer_in_t
        < warp::integral_sequence< char_type >, T >;
    };

  /**
   * \brief SFINAE friendly specialization triggered if provided template
   * parameter is a value type of char type
   *
   * \tparam T a value type containing a value function returning a char type
   */
  template< class T >
    struct build_sequence_from
    <
      T,
      typename warp::sfinae_type
        <
          std::enable_if
            < warp::is_char_buffer< decltype( T::value() ) >::value >
        >::type
    >
    {
      /**
       * \brief Grab the char type
       */
      using char_type = std::remove_pointer_t< decltype( T::value() ) >;

      /**
       * \brief Exposes the resulting sequence
       */
      using type =
        warp::append_char_buffer_in_t
        < warp::integral_sequence< char_type >, T >;
    };

  /**
   * \brief SFINAE friendly specialization dealing with array type (type having
   * an array of char buffer member)
   *
   * \tparam T an array of char buffer type
   */
  template< class T >
    struct build_sequence_from
    <
      T,
      typename warp::sfinae_type
        <
          std::enable_if_t
            <
              warp::is_char_buffer
                < std::remove_extent_t< decltype( T::array ) > >::value
            >
        >::type
    >
    {
      /**
       * \brief Grab the array type
       */
      using array_type = decltype( T::array );

      /**
       * \brief Uses an internal feature to unfold the array into a sequence
       */
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
       * \brief Uniforms the regular grammar definition string into an integral
       * sequence.
       */
      using sequence = typename build_sequence_from< T >::type;
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
       * \brief Finally, exposes the sequence as is, no computations needed
       */
      using sequence = S< C, VS... >;
    };

  /**
   * \brief This class exposes some stuff relative to regular grammar types.
   * unspecialized version.
   */
  template< class >
    struct regular_grammar_traits;

  /**
   * \brief Specialized version of traits class working with any type having a
   * template signature of a regular grammar type
   *
   * \tparam G template of a regular grammar
   * \tparam T the regular grammar definition type
   */
  template< template< class > class G, class T >
    struct regular_grammar_traits< G< T > >
    {
      /**
       * \brief Exposing the grammar definition
       */
      using grammar_definition = T;

      /**
       * \brief Exposing the group type. group is part of the regular grammar
       * type system.
       */
      using group_type = typename G< T >::group_type;
    };
}

#endif // _WARP_SPARK_REGULAR_GRAMMAR_TRAITS_HPP_

// doxygen
/**
 * \file
 * \brief This file contains types exposing traits relative to regular_grammar
 * type.
 */
