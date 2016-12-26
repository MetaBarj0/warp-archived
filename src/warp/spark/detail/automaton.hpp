#ifndef _WARP_SPARK_DETAIL_AUTOMATON_HPP_
#define _WARP_SPARK_DETAIL_AUTOMATON_HPP_

#include "automaton_state_traits.hpp"
#include "automaton_t_function_traits.hpp"

/**
 * \brief A namespace containing implementation details. Elements inside this
 * namespace are not intended to be directly used in the client side
 */
namespace warp::spark::detail
{
  /**
   * \brief Represents a regular grammar automaton.
   *
   * \tparam STATES sequence of states, intended to be a valid type sequence
   * containing at least 2 states, an initial and a final one.
   * \tparam T_FUNCTIONS transition functions of the automaton. At least one is
   * necessary to ensure the consistency of the automaton
   */
  template< class STATES, class T_FUNCTIONS >
    class automaton {};
}

#endif // _WARP_SPARK_DETAIL_AUTOMATON_HPP_

// doxygen
/**
 * \file
 *
 * \brief This file contains the definition of a deterministic finite automaton,
 * graph representation of a spark regular grammar
 */
