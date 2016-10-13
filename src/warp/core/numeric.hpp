#ifndef _WARP_CORE_NUMERIC_HPP_
#define _WARP_CORE_NUMERIC_HPP_

#include <type_traits>
#include <limits>

// isolated stuff
namespace
{
  /**
    \brief This function indicates if a compile time constant value can be
    contained in a specified signed integral type.

    \tparam INTEGRAL_TYPE The specified integral type that may contain the
    specified compile time constant, or not.

    \param value The specified compile time value

    \return true if the specified parameter is contained in the specified
    integral type, false otherwise
  **/
  template< class INTEGRAL_TYPE >
    constexpr bool signed_integral_value_contained_in
    ( long long signed int value )
    {
      // uses std::numeric_limits constexpr functions
      return
        ( value >= std::numeric_limits< INTEGRAL_TYPE >::min() ) &&
        ( value <= std::numeric_limits< INTEGRAL_TYPE >::max() );
    }

  /**
    \brief This function indicates if a compile time constant value can be
    contained in a specified unsigned integral type.

    \tparam INTEGRAL_TYPE The specified integral type that may contain the
    specified compile time constant, or not.

    \param value The specified compile time value

    \return true if the specified parameter is contained in the specified
    integral type, false otherwise
  **/
  template< class INTEGRAL_TYPE >
    constexpr bool unsigned_integral_value_contained_in
    ( long long unsigned int value )
    {
      // uses std::numeric_limits constexpr functions
      return
        ( value >= std::numeric_limits< INTEGRAL_TYPE >::min() ) &&
        ( value <= std::numeric_limits< INTEGRAL_TYPE >::max() );
    }
}

namespace warp
{
  /**
    \brief Utility type aiming to provide the most restrictive signed integral
    type that can contain the provided value in the template parameter list

    \tparam CONSTANT The value to be contained in the provided signed integral
    type
  **/
  template< long long signed int CONSTANT >
    struct signed_auto_constant
    {
      // exposed types
      /**
        \brief Determines the most adapted signed integral type that can contain
        the CONSTANT value. The exposed type will always be the smallest
        possible
      **/
      using type =
        std::conditional_t
        <
          signed_integral_value_contained_in< signed char >
            ( CONSTANT ),
          // rank 1 integral type
          signed char,
          std::conditional_t
            <
              signed_integral_value_contained_in< signed short >
                ( CONSTANT ),
              // rank 2 integral type
              signed short,
              std::conditional_t
                <
                  signed_integral_value_contained_in
                    < signed int >( CONSTANT ),
                  // rank 3 integral type
                  signed int,
                  std::conditional_t
                    <
                      signed_integral_value_contained_in
                        < long signed int >( CONSTANT ),
                      // rank 4 integral type
                      long signed int,
                      long long signed int
                    >
                >
            >
        >;
    };

  /**
    \brief Utility type aiming to provide the most restrictive unsigned integral
    type that can contain the provided value in the template parameter list

    \tparam CONSTANT The value to be contained in the provided unsigned integral
    type
  **/
  template< long long unsigned int CONSTANT >
    struct unsigned_auto_constant
    {
      // exposed types
      /**
        \brief Determines the most adapted unsigned integral type that can
        contain the CONSTANT value. The exposed type will always be the smallest
        possible
      **/
      using type =
        std::conditional_t
        <
          unsigned_integral_value_contained_in< unsigned char >
            ( CONSTANT ),
          // rank 1 integral type
          unsigned char,
          std::conditional_t
            <
              unsigned_integral_value_contained_in
                < unsigned short >( CONSTANT ),
              // rank 2 integral type
              unsigned short,
              std::conditional_t
                <
                  unsigned_integral_value_contained_in
                    < unsigned int >( CONSTANT ),
                  // rank 3 integral type
                  unsigned int,
                  std::conditional_t
                    <
                      unsigned_integral_value_contained_in
                        < long unsigned int >( CONSTANT ),
                      // rank 4 integral type
                      long unsigned int,
                      long long unsigned int
                    >
                >
            >
        >;
    };

    /**
      \brief Alias template on signed_auto_constant

      \tparam CONSTANT The value to be contained in the provided unsigned
      integral type
    **/
    template< long long signed int CONSTANT >
      using signed_auto_constant_t =
      typename signed_auto_constant< CONSTANT >::type;

    /**
      \brief Alias template on unsigned_auto_constant

      \tparam CONSTANT The value to be contained in the provided unsigned
      integral type
    **/
    template< long long unsigned int CONSTANT >
      using unsigned_auto_constant_t =
      typename unsigned_auto_constant< CONSTANT >::type;
}

#endif // _WARP_CORE_NUMERIC_HPP_

// doxygen
/**
  \file

  \brief Header containing feature relative to numeric types. It's a core
  feature of warp
 **/

