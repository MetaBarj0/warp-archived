#ifndef _WARP_SPARK_GROUP_TRAITS_HPP_
#define _WARP_SPARK_GROUP_TRAITS_HPP_

#include "regular_grammar_type_system_enumerations.hpp"
#include "../core/types.hpp"

#include <type_traits>

namespace warp::spark
{
  /**
   * \brief General form of a group traits class, this unspecialized version
   * deals with all type but a valid group type
   *
   * \tparam T any type but a group
   */
  template< class T >
    struct group_traits
    {
      /**
       * \brief This is not a group
       */
      static constexpr bool is_group = false;

      /**
       * \brief name of an invalid group
       */
      using group_name = undefined_type;

      /**
       * \brief It's not a group, so there is not any closure type
       */
      using closure_type = undefined_type;

      /**
       * \brief It's not a group, so there is not any closure
       */
      static constexpr auto closure = -1;

      /**
       * \brief No operand to act on, not a group
       */
      using first_operand = undefined_type;

      /**
       * \brief No operand to act on, not a group
       */
      using second_operand = undefined_type;
    };

  /**
   * \brief Specialization dealing with a valid group type, regarding the
   * template signature. It triggers when the specified group is applying an
   * unary closure on its operand.
   *
   * \tparam GROUP a valid (based on template signature) group template
   * \tparam ID_TYPE integral type of the identifier of the specified group
   * \tparam ID integral identifier of the specified group
   * \tparam CLOSURE the unary closure used in the specified group
   * \tparam FIRST_OPERAND the first (and unique) operand of the specified group
   */
  template
    <
      template
        <
          class,
          class C, C,
          class FO, class... OSO
        > class GROUP,
      class NAME,
      group_unary_closures CLOSURE,
      class FIRST_OPERAND
    >
    struct group_traits
    <
      GROUP
        <
          NAME,
          group_unary_closures, CLOSURE,
          FIRST_OPERAND
        >
    >
    {
      /**
       * \brief This is a group, having only one operand, applying an unary
       * closure
       */
      static constexpr bool is_group = true;

      /**
       * \brief name of the specified group
       */
      using group_name = NAME;

      /**
       * \brief It's a group having one operand, unary closure type, for sure
       */
      using closure_type = group_unary_closures;

      /**
       * \brief value of the unary closure
       */
      static constexpr auto closure = CLOSURE;

      /**
       * \brief The unique operand of this group
       */
      using first_operand = FIRST_OPERAND;

      /**
       * \brief No operand to act on
       */
      using second_operand = undefined_type;
    };

  /**
   * \brief Specialization dealing with a valid group type, regarding the
   * template signature. It triggers when the specified group is applying an
   * binary closure on its operands.
   *
   * \tparam GROUP a valid (based on template signature) group template
   * \tparam ID_TYPE integral type of the identifier of the specified group
   * \tparam ID integral identifier of the specified group
   * \tparam CLOSURE the binary closure used in the specified group
   * \tparam FIRST_OPERAND the first operand of the specified group
   * \tparam SECOND_OPERAND the first operand of the specified group
   */
  template
    <
      template
        <
          class,
          class C, C,
          class FO, class... OSO
        > class GROUP,
      class NAME,
      group_binary_closures CLOSURE,
      class FIRST_OPERAND,
      class SECOND_OPERAND
    >
    struct group_traits
    <
      GROUP
        <
          NAME,
          group_binary_closures, CLOSURE,
          FIRST_OPERAND, SECOND_OPERAND
        >
    >
    {
      /**
       * \brief This is a group, having only one operand, applying an unary
       * closure
       */
      static constexpr bool is_group = true;

      /**
       * \brief name of the specified group
       */
      using group_name = NAME;

      /**
       * \brief It's a group having one operand, unary closure type, for sure
       */
      using closure_type = group_binary_closures;

      /**
       * \brief value of the unary closure
       */
      static constexpr auto closure = CLOSURE;

      /**
       * \brief The unique operand of this group
       */
      using first_operand = FIRST_OPERAND;

      /**
       * \brief No operand to act on
       */
      using second_operand = SECOND_OPERAND;
    };
}

#endif // _WARP_SPARK_GROUP_TRAITS_HPP_
