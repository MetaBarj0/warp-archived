#ifndef _WARP_CORE_TYPE_TRAITS_HPP_
#define _WARP_CORE_TYPE_TRAITS_HPP_

#include "core/types.hpp"

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

/**
 * \brief Intern feature checking if a specified type correspond to char
 * buffer type. This unspecialized version is used with any type but a
 * char buffer type.
 */
template< class >
  struct is_char_buffer
  {
    /**
     * \brief The spcified type is not a char buffer
     */
    static constexpr bool value = false;
  };

/**
 * \brief Valid char buffer type specified
 */
template<>
  struct is_char_buffer< const char * >
  {
    /**
     * \brief Valid char buffer type
     */
    static constexpr bool value = true;
  };

/**
 * \brief Valid char buffer type specified
 */
template<>
  struct is_char_buffer< const wchar_t * >
  {
    /**
     * \brief Valid char buffer type
     */
    static constexpr bool value = true;
  };

/**
 * \brief Valid char buffer type specified
 */
template<>
  struct is_char_buffer< const char16_t * >
  {
    /**
     * \brief Valid char buffer type
     */
    static constexpr bool value = true;
  };

/**
 * \brief Valid char buffer type specified
 */
template<>
  struct is_char_buffer< const char32_t * >
  {
    /**
     * \brief Valid char buffer type
     */
    static constexpr bool value = true;
  };

/**
 * \brief Valid char buffer type specified
 */
template<>
  struct is_char_buffer< const char * const >
  {
    /**
     * \brief Valid char buffer type
     */
    static constexpr bool value = true;
  };

/**
 * \brief Valid char buffer type specified
 */
template<>
  struct is_char_buffer< const wchar_t * const >
  {
    /**
     * \brief Valid char buffer type
     */
    static constexpr bool value = true;
  };

/**
 * \brief Valid char buffer type specified
 */
template<>
  struct is_char_buffer< const char16_t * const >
  {
    /**
     * \brief Valid char buffer type
     */
    static constexpr bool value = true;
  };

/**
 * \brief Valid char buffer type specified
 */
template<>
  struct is_char_buffer< const char32_t * const >
  {
    /**
     * \brief Valid char buffer type
     */
    static constexpr bool value = true;
  };

/**
 * \brief Intern feature checking if a specified type correspond to char
 * buffer type. This unspecialized version is used with any type but a
 * char buffer type.
 */
template< class >
  struct is_char
  {
    /**
     * \brief The spcified type is not a char buffer
     */
    static constexpr bool value = false;
  };

/**
 * \brief Valid char type specified
 */
template<>
  struct is_char< char >
  {
    /**
     * \brief Valid char type
     */
    static constexpr bool value = true;
  };

/**
 * \brief Valid char type specified
 */
template<>
  struct is_char< wchar_t >
  {
    /**
     * \brief Valid char type
     */
    static constexpr bool value = true;
  };

/**
 * \brief Valid char type specified
 */
template<>
  struct is_char< char16_t >
  {
    /**
     * \brief Valid char type
     */
    static constexpr bool value = true;
  };

/**
 * \brief Valid char type specified
 */
template<>
  struct is_char< char32_t >
  {
    /**
     * \brief Valid char type
     */
    static constexpr bool value = true;
  };

/**
 * \brief Valid char type specified
 */
template<>
  struct is_char< const char >
  {
    /**
     * \brief Valid char type
     */
    static constexpr bool value = true;
  };

/**
 * \brief Valid char type specified
 */
template<>
  struct is_char< const wchar_t >
  {
    /**
     * \brief Valid char type
     */
    static constexpr bool value = true;
  };

/**
 * \brief Valid char type specified
 */
template<>
  struct is_char< const char16_t >
  {
    /**
     * \brief Valid char type
     */
    static constexpr bool value = true;
  };

/**
 * \brief Valid char type specified
 */
template<>
  struct is_char< const char32_t >
  {
    /**
     * \brief Valid char type
     */
    static constexpr bool value = true;
  };

/**
 * \brief Meta function indicating if a specified type has a specified static
 * member named value that is a buffer of char type. Relies on SFINAE
 * availaibility in the
 * compiler.
 * This non specialized version is used if the specified type doesn't have any
 * static value member found within T
 *
 * \tparam T the type to look for a static member named value within
 */
template< class T, class = sfinae_type_t<> >
  struct has_static_char_buffer_value_member
  {
    /**
     * \brief T::value does not exist
     */
    static constexpr bool value = false;
  };

/**
 * \brief Specialized version in which a static member named value exists in
 * T. Despite its existence, I must ensure this member has the right type.
 *
 * \tparam T the type to look for a static member named value within
 */
template< class T >
  struct has_static_char_buffer_value_member
  < T, sfinae_type_t< decltype( T::value ) > >
  {
    /**
     * \brief Relies on an internal feature to check the type of T::value
     */
    static constexpr bool value =
      warp::is_char_buffer< decltype( T::value ) >::value;
  };

/**
 * \brief Meta function indicating if a specified type has a specified static
 * method named value returning a buffer of char type. Relies on SFINAE
 * availaibility in the compiler.
 * This non specialized version is used if the specified type doesn't have any
 * static value methd found within T
 *
 * \tparam T the type to look for a static method named value within
 */
template< class T, class = sfinae_type_t<> >
  struct has_static_char_buffer_value_method
  {
    /**
     * \brief T::value() does not exist
     */
    static constexpr bool value = false;
  };

/**
 * \brief Specialized version in which a static method named value exists in
 * T. Despite its existence, I must ensure this method returns has the right
 * type.
 *
 * \tparam T the type to look for a static method named value within
 */
template< class T >
  struct has_static_char_buffer_value_method
  < T, sfinae_type_t< decltype( T::value() ) > >
  {
    /**
     * \brief Relies on an internal feature to check the type of T::value
     */
    static constexpr bool value =
      warp::is_char_buffer< decltype( T::value() ) >::value;
  };
}

#endif // _WARP_CORE_TYPE_TRAITS_HPP_

// doxygen
/**
 * \file
 * \brief header containing some traits relative to basic types of warp
 */
