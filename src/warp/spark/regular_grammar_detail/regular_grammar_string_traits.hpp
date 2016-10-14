#ifndef _WARP_SPARK_REGULAR_GRAMMAR_DETAIL_RGS_TRAITS_HPP_
#define _WARP_SPARK_REGULAR_GRAMMAR_DETAIL_RGS_TRAITS_HPP_

#include "core/types.hpp"
#include "core/type_traits.hpp"

#include <type_traits>

namespace warp
{
namespace spark
{
/**
 * \brief This namespace contains some implementation details that are not
 * intended to be directly used by the client code
 */
namespace detail
{
  /**
   * \brief Gives some traits relative to regular grammar string types.
   *
   * \tparam T any type but a valid regular grammar definition string
   */
  template< class T, class = typename sfinae_type<>::type >
    struct regular_grammar_string_traits
    {
      /**
       * \brief For this (non) specialization, RGS is not considered valid
       */
      static constexpr bool is_valid = false;
    };

  /**
   * \brief Specialization used by a sfinae resolution when T exposes a
   * constexpr method named value
   *
   * \tparam T a warp value type, exposing a static constexpr method named value
   */
  template< class T >
    struct regular_grammar_string_traits
    < T, typename warp::sfinae_type< decltype( T::value() ) >::type >
    {
      /**
       * \brief A last check to make sure of the return type of the method
       */
      static constexpr bool is_valid =
        warp::is_char_buffer< decltype( T::value() ) >::value;
    };
}
}
}

#endif // _WARP_SPARK_REGULAR_GRAMMAR_DETAIL_RGS_TRAITS_HPP_
