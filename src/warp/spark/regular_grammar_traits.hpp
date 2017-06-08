#ifndef _WARP_SPARK_REGULAR_GRAMMAR_TRAITS_HPP_
#define _WARP_SPARK_REGULAR_GRAMMAR_TRAITS_HPP_

#include "../core/type_traits.hpp"
#include "../sequences/algorithm.hpp"
#include "../sequences/sequence_traits.hpp"

#include <cstdlib>
#include <type_traits>

namespace warp::spark
{
  /**
   * \brief internal traits class specifically designed for regular grammar
   * definition type having a sequence form. Unspecialized version dealing with
   * invalid regular grammar definition type
   */
  template< class, class = sfinae_type_t<> >
    struct regular_grammar_definition_sequence_traits
    {
      /**
       * \brief Invalid integral sequence specified
       */
      using regular_grammar_definition_sequence = undefined_type;

      /**
       * \brief Invalid integral sequence specified
       */
      static constexpr auto is_regular_grammar_definition = false;
    };

  /**
   * \brief Specialized version working with valid integral sequences. A check
   * is also required about the content of the integral sequence
   *
   * \tparam T an integral sequence that is valid thanks to sfinae check
   */
  template< class T >
    struct regular_grammar_definition_sequence_traits
    <
      T,
      sfinae_type_t
        <
          std::enable_if_t
            < warp::meta_sequence_traits< T >::is_integral_sequence >
        >
    >
    {
      /**
       * \brief Ensures the sequence is not empty, empty sequence cannot contain
       * any grammar definition.
       */
      static constexpr auto is_regular_grammar_definition =
        ! warp::is_empty_sequence< T >::value;

      /**
       * \brief The sequence depends on the size of the grammar definition size
       */
      using regular_grammar_definition_sequence =
        std::conditional_t< is_regular_grammar_definition, T, undefined_type >;
    };

  /**
   * \brief Internal traits class exposing one trait for valid char buffer
   * types. A valid char buffer type is a type having either :
   * - a static constexpr value member of type pointer on char type
   * - a static constexpr value function returning a pointer on char type
   * Moreover, the type must have exclusively one of these. If it has more, it
   * is invalid.
   *
   * \tparam U a potentiel char buffer type
   */
  template< class U >
    struct char_buffer_value_traits
    {
      /**
       * \brief Valid only if one of traits
       */
      static constexpr bool is_char_buffer_value =
        warp::has_static_char_buffer_value_member< U >::value ^
        warp::has_static_char_buffer_value_method< U >::value;
    };

  /**
   * \brief Internal traits class indicating a type is a valid char buffer
   * array. A char buffer array type is a type exposing a static constexpr array
   * member of type pointer on char type. This unspecialized version deals with
   * all but char buffer array types.
   */
  template< class >
    struct is_char_buffer_array
    {
      /**
       * \brief The provided type is not a char buffer array type
       */
      static constexpr bool value = false;
    };

  /**
   * \brief Specialization dealing with valid array
   *
   * \tparam U intended to be a pointer on char type
   * \tparam N the size of the array, intended to be greater than zero
   */
  template< class U, std::size_t N >
    struct is_char_buffer_array< U[ N ] >
    {
      /**
       * \brief Checking size and type of the array
       */
      static constexpr bool value =
        ( N > 0 ) && ( warp::is_char_buffer< U >::value );
    };

  /**
   * \brief SFINAE-friendly traits class designed for char buffer array types. A
   * char buffer array type is a type exposing a static constexpr array member
   * of pointer on char type. This unspecialized version deals with all types
   * but valid char buffer array types.
   */
  template< class, class = sfinae_type_t<> >
    struct has_static_char_buffer_array_member
    {
      /**
       * \brief Provided type is not a valid char buffer array type.
       */
      static constexpr bool value = false;
    };

  /**
   * \brief Specialization dealing with valid char buffer array types.
   *
   * \tparam U a valid char buffer array type, checked by SFINAE (only on array
   * member presence)
   */
  template< class U >
    struct has_static_char_buffer_array_member
    < U, warp::sfinae_type_t< decltype( U::array ) > >
    {
      /**
       * \brief Ensures the type of the array is pointer on char type
       */
      static constexpr bool value =
        is_char_buffer_array< decltype( U::array ) >::value;
    };

  /**
   * \brief Type delivering a trait about a potential char buffer array type.
   *
   * \tparam T a potential char buffer array type
   */
  template< class U >
    struct char_buffer_array_traits
    {
      /**
       * \brief using internal traits class to determine if the provided type is
       * a char buffer array type
       */
      static constexpr bool is_char_buffer_array =
        has_static_char_buffer_array_member< U >::value;
    };

  /**
   * \brief An internal feature joining char buffer array within a sequence type
   */
  template< class, class >
    struct join_array_in_sequence;

  /**
   * \brief Specialization dealing with a valid array type exposing a char
   * buffer array member
   *
   * \tparam T the array type, exposing the array member
   * \tparam V the type of the array (char buffer)
   * \tparam N the size of the array
   */
  template< class T, class V, std::size_t N >
    struct join_array_in_sequence< T, V[ N ] >
    {
      /**
       * \brief Grab the char type of the array's element
       */
      using char_type = std::remove_pointer_t< V >;

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
       * \brief add this char buffer to the resulting sequence, last element
       * first
       */
      using type =
        typename push_front_char_buffer_in_sequence
        < warp::integral_sequence< char_type >, N - 1 >::type;
    };

  /**
   * \brief How to build an integral sequence from a constexpr array or string?
   * Use this type.
   */
  template< class, class = warp::sfinae_type_t<> >
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
      warp::sfinae_type_t
        <
          std::enable_if_t
            < warp::is_char_buffer< decltype( T::value ) >::value >
        >
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
   * \tparam T a value type containing a value function returning a char
   * type
   */
  template< class T >
    struct build_sequence_from
    <
      T,
      warp::sfinae_type_t
        <
          std::enable_if
            < warp::is_char_buffer< decltype( T::value() ) >::value >
        >
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
      warp::sfinae_type_t
        <
          std::enable_if_t
            <
              warp::is_char_buffer
                < std::remove_extent_t< decltype( T::array ) > >::value
            >
        >
    >
    {
      /**
       * \brief Grab the array type
       */
      using array_type = decltype( T::array );

      /**
       * \brief Uses an internal feature to join the array into a sequence
       */
      using type = typename join_array_in_sequence< T, array_type >::type;
    };

  /**
   * \brief Internal traits class designed to be used on a value or array type
   * containing a regular grammar definition. This unspecialized version deals
   * with invalid type specified : neither a value type nor an array type
   * exposing a char buffer.
   */
  template< class, class = sfinae_type_t<> >
    struct regular_grammar_definition_value_or_array_traits
    {
      /**
       * \brief Invalid value or array type specified
       */
      using regular_grammar_definition_sequence = undefined_type;

      /**
       * \brief Invalid value or array type specified
       */
      static constexpr auto is_regular_grammar_definition = false;
    };

  /**
   * \brief This specialization is triggered when the T type is matching the
   * signature of a value type (both member and function) or an array type
   * exposing a value of type buffer on char
   *
   * \tparam T an assumed value or array type
   */
  template< class T >
    struct regular_grammar_definition_value_or_array_traits
    <
      T,
      sfinae_type_t
        <
          std::enable_if_t
            <
              char_buffer_value_traits< T >::is_char_buffer_value ^
                char_buffer_array_traits< T >::is_char_buffer_array
            >
        >
    >
    {
      /**
       * \brief uses an internal feature to transform the provided regular
       * grammar definition into an integral sequence
       */
      using regular_grammar_definition_sequence =
        typename build_sequence_from< T >::type;

      /**
       * \brief Valid only if resulting sequence is not empty
       */
      static constexpr bool is_regular_grammar_definition =
        ! warp::is_empty_sequence< regular_grammar_definition_sequence >::
        value;
    };

  /**
   * \brief Traits class dealing with a regular grammar definition type. This
   * non-specialized version deal with regular grammar definition type exposing
   * either a value or a value() or an array member within.
   *
   * \tparam T the regular grammar definition of form value type or array type
   */
  template< class T >
    struct regular_grammar_definition_traits
    {
      /**
       * \brief sfinae check had ensured the validity of the regular grammar
       * definition and the size of the resulting sequence
       */
      static constexpr bool is_regular_grammar_definition =
        regular_grammar_definition_value_or_array_traits
        < T >::is_regular_grammar_definition;

      /**
       * \brief Uniforms the regular grammar definition string into an integral
       * sequence.
       */
      using regular_grammar_definition_sequence =
        typename regular_grammar_definition_value_or_array_traits
        < T >::regular_grammar_definition_sequence;
    };

  /**
   * \brief This specialization deals with a regular grammar definition already
   * having the form of an integral sequence. Some compile time computations are
   * unnecessary here and this type only ensures that the integral type used in
   * the sequence is valid and is not empty.
   *
   * \tparam S integral sequence template
   * \tparam C integral type used in the sequence
   * \tparam VS value pack contained in the integral sequence
   */
  template< template< class T, T... > class S, class C, C... VS >
    struct regular_grammar_definition_traits< S< C, VS... > >
    {
      /**
       * \brief the integral sequence used for the provided regular grammar
       * definition. Undefined if the provided regular grammar definiton is not
       * considered valid
       */
      using regular_grammar_definition_sequence =
        typename regular_grammar_definition_sequence_traits
        < S< C, VS... > >::regular_grammar_definition_sequence;

      /**
       * \brief Delegating to internal traits class
       */
      static constexpr auto is_regular_grammar_definition =
        regular_grammar_definition_sequence_traits
        < S< C, VS... > >::is_regular_grammar_definition;
    };

  /**
   * \brief This traits class is designed to deal with regular_grammar type.
   * This non specialized version works with all types but a regular grammar.
   */
  template< class >
    struct regular_grammar_traits
    {
      /**
       * \brief Provided type is not a regular grammar
       */
      static constexpr bool is_regular_grammar = false;

      /**
       * \brief No regular grammar, no definition
       */
      using regular_grammar_definition = undefined_type;
    };

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
       * \brief This value depends on the validity of the provided regular
       * grammar definition
       */
      static constexpr auto is_regular_grammar =
        regular_grammar_definition_traits< T >::is_regular_grammar_definition;

      /**
       * \brief The definition of this regular grammar
       */
      using regular_grammar_definition =
        std::conditional_t< is_regular_grammar, T, undefined_type >;
    };
}

#endif // _WARP_SPARK_REGULAR_GRAMMAR_TRAITS_HPP_

// doxygen
/**
 * \file
 * \brief This file contains types exposing traits relative to regular_grammar
 * type.
 */
