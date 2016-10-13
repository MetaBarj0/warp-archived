#ifndef _WARP_CORE_TYPE_TRAITS_HPP_
#define _WARP_CORE_TYPE_TRAITS_HPP_

#include "types.hpp"

#include <type_traits>

namespace warp
{
  /**
   * \brief A specific trait to determine if the specified type could be
   * considered empty. The emptiness concept is only related to data member of a
   * class. Thus, a class having several using/typedef, intern types, static or
   * member functions and static fields may be considered empty as long as it
   * inherit directly or indirectly of warp::empty_type
   *
   * \tparam T the type to test the emptiness
   */
  template< class T >
    struct is_empty
    {
      /**
       * \brief The value exposed, indicating the emptiness of the specified
       * type
       */
      static constexpr bool value =
        // compare raw sizes to check if states are contained in T
        sizeof( T ) <= sizeof( empty_type ) &&
          (
            // test for empty_type or a derived of empty_type
            std::is_same< T, empty_type >::value ||
              std::is_base_of< empty_type, T >::value
          );
    };
}

#endif // _WARP_CORE_TYPE_TRAITS_HPP_

// doxygen
/**
 * \file
 * \brief header containing some traits relative to basic types of warp
 */
