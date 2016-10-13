#ifndef _WARP_CORE_TYPES_HPP
#define _WARP_CORE_TYPES_HPP

namespace warp
{
  /**
   * \brief Represents the concept of an undefined type. It only exists and does
   * not have its own definition as it is only declared.
   */
  struct undefined_type;

  /**
   * \brief Represents the concept of a type that is completely empty. This type
   * is both declared and defined but doesn't contain anything of value but its
   * inherent emptyness.
   */
  struct empty_type{};

  /**
   * \brief An empty type used as placeholder, meaning this type could be ignore
   * when used in any context
   */
  struct ignore :
    empty_type {};

  /**
   * \brief represent a type if the template parameter is specified
   */
  template< class... >
    struct type;

  /**
   * \brief This specialization does not have any type
   */
  template<>
    struct type<>
    {
      /**
       * \brief There is not type here
       */
      using value_type = undefined_type;
    };

  /**
   * \brief Specialization holding a type
   *
   * \tparam the type hold
   */
  template< class T >
    struct type< T >
    {
      /**
       * \brief Exposes the type
       */
      using value_type = T;
    };

  /**
   * \brief A template that is designed to be used in SFINAE expression and for
   * which the exposed type is previsible and always the same :
   * warp::undefined_type. The SFINAE expression replaces the template parameter
   * pack (by using one or more decltype expressions)
   */
  template< class... >
    struct sfinae_type
    {
      /**
       * \brief Always the same type is used, ensure previsibility allowinf
       * SFINAE usage in template specializations
       */
      using type = warp::undefined_type;
    };
}

#endif // _WARP_CORE_TYPES_HPP

// doxygen
/**
 * \file
 * \brief Header containing core feature relative to types in their most generic
 * representations
 */
