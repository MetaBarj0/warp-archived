#ifndef _WARP_SPARK_DETAIL_AUTOMATON_T_FUNCTION_TRAITS_HPP_
#define _WARP_SPARK_DETAIL_AUTOMATON_T_FUNCTION_TRAITS_HPP_

#include "../../sequences/sequence_traits.hpp"
#include "../symbol_traits.hpp"
#include "../../core/types.hpp"
#include "automaton_t_function_args.hpp"
#include "../../sequences/algorithm.hpp"

#include <type_traits>

namespace warp::spark::detail
{
  /**
   * \brief Internal traits class indicating a type is a valid integral sequence
   * for an automaton state. Unspecialized version, the boolean template
   * parameter equaling false indicating provided type is not even an integral
   * sequence
   */
  template< class, bool >
    struct automaton_state_id_traits
    {
      /**
       * \brief Not a valid automaton state identifier
       */
      static constexpr bool is_automaton_state_id = false;
    };

  /**
   * \brief Specialization dealing with a valid integral sequence. However, to
   * be fully valid, this sequence must not be empty
   *
   * \tparam ID automaton state identifier, integral sequence
   */
  template< class ID >
    struct automaton_state_id_traits< ID, true >
    {
      /**
       * \brief Valid if not empty
       */
      static constexpr bool is_automaton_state_id =
        ! warp::is_empty_sequence< ID >::value;
    };

  /**
   * \brief Exposes traits for automaton_t_function type. This unspecialized
   * version is used when specified type is not an automaton_t_function.
   */
  template< class >
    struct automaton_t_function_traits
    {
      /**
       * \brief Not an transition function
       */
      static constexpr bool is_automaton_t_function = false;

      /**
       * \brief Not an transition function
       */
      using source_state_id = undefined_type;

      /**
       * \brief Not an transition function
       */
      using function_argument = undefined_type;

      /**
       * \brief Not an transition function
       */
      using target_state_id = undefined_type;

      /**
       * \brief Not an transition function
       */
      static constexpr bool is_epsilon_transition = false;
    };

  /**
   * \brief This specialization is used when the specified type has a template
   * signature similar to a transition function. Further checks are made to
   * expose traits. This specialization is used when the transition function is
   * parametered with an epsilon transition
   *
   * \tparam F template whose the signature looks good
   * \tparam SOURCE_ID identifier of a source automaton state
   * \tparam TARGET_ID identifier of a target automaton state
   */
  template
    <
      template< class, class, class > class F,
      class SOURCE_ID, class TARGET_ID
    >
    struct automaton_t_function_traits
    < F< SOURCE_ID, epsilon_transition, TARGET_ID > >
    {
      /**
       * \brief Validity is ensure using internal traits designed to work on an
       * integral sequence (the automaton state id)
       */
      static constexpr auto is_automaton_t_function =
        automaton_state_id_traits
        <
          SOURCE_ID, // assumed integral sequence
          meta_sequence_traits< SOURCE_ID >::is_integral_sequence
        >::is_automaton_state_id &&
        automaton_state_id_traits
        <
          TARGET_ID, // assumed integral sequence
          meta_sequence_traits< SOURCE_ID >::is_integral_sequence
        >::is_automaton_state_id;

      /**
       * \brief the source state identifier
       */
      using source_state_id =
        std::conditional_t
        < is_automaton_t_function, SOURCE_ID, undefined_type >;

      /**
       * \brief The argument of the function
       */
      using function_argument =
        std::conditional_t
        < is_automaton_t_function, epsilon_transition, undefined_type >;

      /**
       * \brief The target state identifier
       */
      using target_state_id =
        std::conditional_t
        < is_automaton_t_function, TARGET_ID, undefined_type >;

      /**
       * \brief For this specialization, may be an epsilon transition, depends
       * on the validity of the function
       */
      static constexpr bool is_epsilon_transition = is_automaton_t_function;
    };

  /**
   * \brief Specialization gicing traits of an assumed transition function
   * parametered with an assumed symbol
   *
   * \tparam F template whose the signature looks good
   * \tparam FN_ARG the parameter of the function, assumed to be a symbol
   * \tparam SOURCE_ID identifier of a source automaton state
   * \tparam TARGET_ID identifier of a target automaton state
   */
  template
    <
      template< class, class, class > class F,
      class SOURCE_ID, class FN_ARG, class TARGET_ID
    >
    struct automaton_t_function_traits
    < F< SOURCE_ID, FN_ARG, TARGET_ID > >
    {
      /**
       * \brief Validity is ensure using internal traits designed to work on an
       * integral sequence (the automaton state id) and if the argument of the
       * function is a symbol
       */
      static constexpr auto is_automaton_t_function =
        automaton_state_id_traits
        <
          SOURCE_ID, // assumed integral sequence
          meta_sequence_traits< SOURCE_ID >::is_integral_sequence
        >::is_automaton_state_id &&
        automaton_state_id_traits
        <
          TARGET_ID, // assumed integral sequence
          meta_sequence_traits< SOURCE_ID >::is_integral_sequence
        >::is_automaton_state_id &&
        symbol_traits< FN_ARG >::is_symbol; // a symbol is required

      /**
       * \brief The source state identifier
       */
      using source_state_id =
        std::conditional_t
        < is_automaton_t_function, SOURCE_ID, undefined_type >;

      /**
       * \brief The argument of the function
       */
      using function_argument =
        std::conditional_t
        < is_automaton_t_function, FN_ARG, undefined_type >;

      /**
       * \brief The target state identifier
       */
      using target_state_id =
        std::conditional_t
        < is_automaton_t_function, TARGET_ID, undefined_type >;

      /**
       * \brief For this specialization, the argument is not an epsilon
       * transition
       */
      static constexpr bool is_epsilon_transition = false;
    };
}

#endif // _WARP_SPARK_DETAIL_AUTOMATON_T_FUNCTION_TRAITS_HPP_

// doxygen
/**
 * \file
 *
 * \brief Contains traits types related to the transition function type of the
 * automaton
 */
