#ifndef _WARP_SPARK_GROUP_TRAITS_HPP_
#define _WARP_SPARK_GROUP_TRAITS_HPP_

#include "regular_grammar_type_system_enumerations.hpp"

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
    };
}

#endif // _WARP_SPARK_GROUP_TRAITS_HPP_
