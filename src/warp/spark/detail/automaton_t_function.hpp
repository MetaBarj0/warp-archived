#ifndef _WARP_SPARK_DETAIL_AUTOMATON_T_FUNCTION_HPP_
#define _WARP_SPARK_DETAIL_AUTOMATON_T_FUNCTION_HPP_

namespace warp::spark::detail
{
  /**
   * \brief This is an automaton's transition function. A transition function is
   * an entity allowing to change the current state of an automaton from a
   * source to a target if a predicate is verified. The predicate is a test
   * against a symbol or an epsilon transition
   *
   * \tparam ID identifier of this transition function
   * \tparam SOURCE_ID identifier of the source automaton state
   * \tparam FN_ARG argument of this transition function, either a symbol or an
   * epsilon transition.
   * \tparam TARGET_ID identifier of the target automaton state
   */
  template
    < class ID, class SOURCE_STATE_ID, class FN_ARG, class TARGET_STATE_ID >
    struct automaton_t_function {};
}

#endif // _WARP_SPARK_DETAIL_AUTOMATON_T_FUNCTION_HPP_

// doxygen
/**
 * \file
 *
 * \brief Contains the transition function type definition and implementation
 */
