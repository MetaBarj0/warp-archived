#ifndef _WARP_SPARK_DETAIL_AUTOMATON_G_COMMAND_HPP_
#define _WARP_SPARK_DETAIL_AUTOMATON_G_COMMAND_HPP_

#include "automaton_g_command_types.hpp"

namespace warp::spark::detail
{
  /**
   * \brief This is the definition of a group command. A group command is
   * attached to a transition function. A transition function may have several
   * group command. Each group command is attached to a single group. It
   * dictates how a group is built when its related transition function is
   * traversed.
   *
   * \tparam TYPE the type of the group command. Defines the operation to apply
   * on a group
   * \tparam GROUP_NAME a group name. Usually a group is defined inside a
   * regular grammar definition or a group template type definition. Intended to
   * be an integral sequence.
   * \tparam T_FUNCTION_ID the identifier of the attached transition function.
   * Intended to be an integral sequence
   */
  template
    <
      group_command_types TYPE,
      class GROUP_NAME,
      class T_FUNCTION_ID
    >
    class automaton_g_command {};
}

#endif // _WARP_SPARK_DETAIL_AUTOMATON_G_COMMAND_HPP_

//doxygen
/**
 * \file
 *
 * This file contain the class for the automaton group command concept.
 */
