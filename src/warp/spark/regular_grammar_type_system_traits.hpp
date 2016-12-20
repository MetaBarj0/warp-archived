#ifndef _WARP_SPARK_REGULAR_GRAMMAR_TYPE_SYSTEM_TRAITS_HPP_
#define _WARP_SPARK_REGULAR_GRAMMAR_TYPE_SYSTEM_TRAITS_HPP_

#include "../sequences/sequence_traits.hpp"
#include "../sequences/algorithm.hpp"

namespace warp::spark
{
  /**
   * \brief An internal utility traits class used to check if a symbol or a
   * group name is valid.
   *
   * \tparam T The name of a symbol or a group, supposed integral sequence.
   */
  template< class T >
    struct name_traits
    {
      /**
       * \brief Internal traits checking the size of a valid integral sequence.
       * Unspecialized version is used when the specified type is not a valid
       * integral sequence
       */
      template< class, bool >
        struct internal_traits
        {
          /**
           * \brief Type specified is not an integral sequence, the symbol name
           * is not valid
           */
          static constexpr bool is_name = false;
        };

      /**
       * \brief Specialization used when type specified is a valid integral
       * sequence.
       *
       * \tparam U an integral sequence
       */
      template< class U >
        struct internal_traits< U, true >
        {
          /**
           * \brief The validity of the integral sequence depends on its content
           * size
           */
          static constexpr auto is_name =
            ! warp::is_empty_sequence< U >::value;
        };

      /**
       * \brief Validity of the name depends of 2 things : T must be a valid
       * integral sequence type and the integral sequence size if greater than 0
       */
      static constexpr bool is_name =
        internal_traits
        < T, warp::meta_sequence_traits< T >::is_integral_sequence >::is_name;
    };

  /**
   * \brief This trait class is used when a type is specified as letter
   * sequence. To be valid, inclusive and exclusive symbols must have one letter
   * sequence that is an integral sequence. This internal trait class is not
   * used when dealing with any symbol as any symbols don't use letter sequences
   *
   * \tparam T an intended type sequence
   */
  template< class T >
    struct symbol_letter_sequence_traits
    {
      /**
       * \brief Internal traits used to filter integral sequence type. This
       * unspecialized version is used when specified type is not an integral
       * sequence
       */
      template< class, bool >
        struct internal_traits
        {
          /**
           * \brief Specified type is not an integral sequence
           */
          static constexpr bool is_valid_inclusive_letter_sequence = false;

          /**
           * \brief Specified type is not an integral sequence
           */
          static constexpr bool is_valid_exclusive_letter_sequence = false;
        };

      /**
       * \brief This specialization is used when specified type is a valid
       * integral sequence. Validity of letter sequence depends on its size and
       * of the symbol type
       *
       * \tparam U the letter sequence being a valid integral sequence
       */
      template< class U >
        struct internal_traits< U, true >
        {
          /**
           * \brief For an inclusive symbol type, the letter sequence must
           * contain only one element
           */
          static constexpr bool is_valid_inclusive_letter_sequence =
            warp::for_each_value_in_t< U, warp::count_integral >::value == 1;

          /**
           * \brief For an exclusive symbol ,the letter sequence must not be
           * empty
           */
          static constexpr bool is_valid_exclusive_letter_sequence =
            ! warp::is_empty_sequence< U >::value;
        };

      /**
       * \brief Delegates to an internal traits first ensuring T is an integral
       * sequence
       */
      static constexpr auto is_valid_inclusive_letter_sequence =
        internal_traits
        < T, warp::meta_sequence_traits< T >::is_integral_sequence >::
        is_valid_inclusive_letter_sequence;

      /**
       * \brief Delegates to an internal traits first ensuring T is an integral
       * sequence
       */
      static constexpr auto is_valid_exclusive_letter_sequence =
        internal_traits
        < T, warp::meta_sequence_traits< T >::is_integral_sequence >::
        is_valid_exclusive_letter_sequence;
    };
}

#endif // _WARP_SPARK_REGULAR_GRAMMAR_TYPE_SYSTEM_TRAITS_HPP_

// doxygen
/**
 * \file
 *
 * \brief This file groups common traits used both by group and symbol template
 */
