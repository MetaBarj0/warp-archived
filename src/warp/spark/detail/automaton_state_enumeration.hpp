#ifndef _WARP_SPARK_DETAIL_AUTOMATON_STATE_ENUMERATION_HPP_
#define _WARP_SPARK_DETAIL_AUTOMATON_STATE_ENUMERATION_HPP_

namespace warp::spark::detail
{
  /**
   * \brief Gather all automaton state types. Each state can have one of these
   */
  enum class state_types
  {
    /**
     * \brief The initial state. Each automaton has one and only one initial
     * state
     */
    initial,

    /**
     * \brief The final state. An automaton has at least one terminal state
     */
    final,

    /**
     * \brief An intermediate state. An automaton that is big enough may have
     * one or more intermediate states.
     */
    intermediate,

    /**
     * \brief Both initial and final state. A state of this type behaves like an
     * initial and a final state. An automaton might have one and unique initial
     * and final state.
     */
    initial_and_final
  };
}

#endif // _WARP_SPARK_DETAIL_AUTOMATON_STATE_ENUMERATION_HPP_
