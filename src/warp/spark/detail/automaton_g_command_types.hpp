#ifndef _WARP_SPARK_DETAIL_AUTOMATON_G_COMMAND_TYPES_HPP_
#define _WARP_SPARK_DETAIL_AUTOMATON_G_COMMAND_TYPES_HPP_

namespace warp::spark::detail
{
  /**
   * \brief Enumerates all types for a group command
   */
  enum class group_command_types
  {
    /**
     * \brief Finishing a group
     */
    finishing,

    /**
     * \brief Capturing for a group
     */
    capturing,

    /**
     * \brief Resetting a group
     */
    resetting
  };
}

#endif // _WARP_SPARK_DETAIL_AUTOMATON_G_COMMAND_TYPES_HPP_

//doxygen
/**
 * \file
 *
 * This file contain the definition of constant for all group command types.
 */
