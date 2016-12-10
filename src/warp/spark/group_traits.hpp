#ifndef _WARP_SPARK_GROUP_TRAITS_HPP_
#define _WARP_SPARK_GROUP_TRAITS_HPP_

#include "regular_grammar_type_system_enumerations.hpp"
#include "../core/types.hpp"

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
       * \brief Identifier of an invalid group
       */
      static constexpr auto group_id = -1;

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
}

#endif // _WARP_SPARK_GROUP_TRAITS_HPP_
