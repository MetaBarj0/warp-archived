#ifndef _WARP_SPARK_DETAIL_AUTOMATON_G_COMMAND_TRAITS_HPP_
#define _WARP_SPARK_DETAIL_AUTOMATON_G_COMMAND_TRAITS_HPP_

#include "automaton_g_command_types.hpp"
#include "../../sequences/sequence_traits.hpp"

namespace warp::spark::detail
{
  /**
   * \brief The traits class designed to recognize a valid automaton group
   * command. This unspecialized version is used if the provided type does not
   * match the group command template signature
   */
  template< class >
    struct automaton_g_command_traits
    {
      /**
       * \brief Not a group command type
       */
      static constexpr bool is_automaton_g_command = false;
    };

  /**
   * \brief Specialization used when the template signature of the provided type
   * match with the automaton_g_command template.
   *
   * \tparam G_COMMAND template matching with the automaton_g_command template
   * \tparam TYPE the type of the provided group command type
   * \tparam GROUP_NAME_SEQUENCE the integral sequence template for the group
   * name operand
   * \tparam GNS_T the integral type used in the group name integral sequence
   * \tparam GN1 first character of the group name operand. Actually a group
   * name cannot be empty
   * \tparam GNN remaining optionnal letters of a group name
   * \tparam T_FUNCTION_ID_SEQUENCE the integral sequence template for the
   * transition function identifier operand
   * \tparam TFIS_T the integral type used in the integral sequence for the
   * transition function template
   * \tparam TFI1 the first letter of the integral sequence for the transition
   * function identifier operand. Indeed, a valid transition function identifier
   * must not be empty.
   * \tparam TFIN the optional remaining letter of the transition function
   * identifier integral sequence
   */
  template
    <
      template< group_command_types, class, class > class G_COMMAND,
      group_command_types TYPE,
      template< class T, T... > class GROUP_NAME_SEQUENCE,
      class GNS_T, GNS_T GN1, GNS_T... GNN,
      template< class T, T... > class T_FUNCTION_ID_SEQUENCE,
      class TFIS_T, TFIS_T TFI1, TFIS_T... TFIN
    >
    struct automaton_g_command_traits
    <
      G_COMMAND
        <
          TYPE,
          GROUP_NAME_SEQUENCE< GNS_T, GN1, GNN... >,
          T_FUNCTION_ID_SEQUENCE< TFIS_T, TFI1, TFIN... >
        >
    >
    {
      /**
       * \brief This is a group command only if group name and transition
       * function identifier are valid integral sequences
       */
      static constexpr auto is_automaton_g_command =
        meta_sequence_traits
          < GROUP_NAME_SEQUENCE< GNS_T, GN1, GNN... > >::is_integral_sequence &&
        meta_sequence_traits
          < T_FUNCTION_ID_SEQUENCE< TFIS_T, TFI1, TFIN... > >::
          is_integral_sequence;
    };
}

#endif // _WARP_SPARK_DETAIL_AUTOMATON_G_COMMAND_TRAITS_HPP_

//doxygen
/**
 * \file
 *
 * This file contain the traits class for the automaton group command concept,
 * giving a way to the user to ensure a given type is or is not a valid group
 * command type
 */
