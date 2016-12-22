#ifndef _WARP_SPARK_DETAIL_AUTOMATON_STATE_TRAITS_HPP_
#define _WARP_SPARK_DETAIL_AUTOMATON_STATE_TRAITS_HPP_

#include "automaton_state_enumeration.hpp"
#include "../../core/types.hpp"
#include "../../sequences/sequence_traits.hpp"

#include <type_traits>

namespace warp::spark::detail
{
  /**
   * \brief Provides various traits for automaton_state type. This unspecialized
   * version is used when specified type is not a valid automaton_state.
   */
  template< class, state_types >
    struct automaton_state_traits
    {
      /**
       * \brief This is not an automaton state
       */
      static constexpr bool is_automaton_state = false;

      /**
       * \brief This is not an automaton state
       */
      using identifier = undefined_type;

      /**
       * \brief This is not an automaton state
       */
      static constexpr auto type = static_cast< state_types >( -1 );

      /**
       * \brief Not a valid state
       */
      static constexpr bool is_initial = false;

      /**
       * \brief Not a valid state
       */
      static constexpr bool is_intermediate = false;

      /**
       * \brief Not a valid state
       */
      static constexpr bool is_final = false;
    };

  /**
   * \brief Specialized version providing traits for a supposed valid
   * automaton_state type. The validity is supposed thanks to the correct
   * signature of an integral sequence for the identifier
   *
   * \tparam S a template signature matching a valid integral sequence
   * \tparam T integral type used in the provided integral sequence
   * \tparam I first element of the integral sequence
   * \tparam IS remaining values of the provided integral sequence
   */
  template
    < template< class T, T... > class S, class U, U I, U... IS, state_types ST >
    struct automaton_state_traits< S< U, I, IS... >, ST >
    {
      /**
       * \brief Validity ensured if provided identifier is a valid integral
       * sequence
       */
      static constexpr auto is_automaton_state =
        warp::meta_sequence_traits< S< U, I, IS... > >::is_integral_sequence;

      /**
       * \brief Validity ensures the identifier exposition
       */
      using identifier =
        std::conditional_t
        < is_automaton_state, S< U, I, IS... >, undefined_type >;

      /**
       * \brief Exposition ensured by the state validity
       */
      static constexpr auto type =
        is_automaton_state ? ST : static_cast< state_types >( -1 );

      /**
       * \brief useful for some algorithms
       */
      static constexpr bool is_initial =
        is_automaton_state ?
        ( ( ST == state_types::initial ) ||
          ( ST == state_types::initial_and_final ) ) :
        false;

      /**
       * \brief useful for some algorithms
       */
      static constexpr bool is_intermediate =
        is_automaton_state ?
        ( ST == state_types::intermediate ) :
        false;

      /**
       * \brief useful for some algorithms
       */
      static constexpr bool is_final =
        is_automaton_state ?
        ( ( ST == state_types::final ) ||
          ( ST == state_types::initial_and_final ) ) :
        false;
    };
}

#endif // _WARP_SPARK_DETAIL_AUTOMATON_STATE_TRAITS_HPP_

// doxygen
/**
 * \file
 *
 * \brief A file implementing the automaton state traits type. Traits gives the
 * ability to ensure the observed type is valid under defined rules and give
 * valuable information on the observed types as well.
 */
