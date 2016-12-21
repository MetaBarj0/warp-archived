#ifndef _WARP_SPARK_DETAIL_AUTOMATON_STATE_HPP_
#define _WARP_SPARK_DETAIL_AUTOMATON_STATE_HPP_

#include "automaton_state_enumeration.hpp"

namespace warp::spark::detail
{
  /**
   * \brief This is an automaton state.
   *
   * \tparam ID identifier of this state, intended to be an integral sequence
   * \tparam ST state type, see the enumeration for more details
   */
  template< class ID, state_types ST >
    struct automaton_state {};
}

#endif // _WARP_SPARK_DETAIL_AUTOMATON_STATE_HPP_

// doxygen
/**
 * \file
 *
 * \brief A file implementing the automaton state template type. An automaton
 * state is a part of an automaton.
 */
