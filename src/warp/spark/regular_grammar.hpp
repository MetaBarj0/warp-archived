#ifndef _WARP_REGULAR_GRAMMAR_HPP_
#define _WARP_REGULAR_GRAMMAR_HPP_

#include "../core/types.hpp"
#include "regular_grammar_detail/regular_grammar_string_traits.hpp"
#include "../sequences/sequences.hpp"

#include <type_traits>

/**
 * \brief Holds some hidden stuff related to regular_grammar type implementation
 */
namespace
{
  /**
   * \brief Empty type used to display an understandable error message at
   * compile time when user try to use a regular_grammar type with an invalid
   * regular grammar string type
   */
  struct invalid_regular_grammar_string_type_specified :
    warp::empty_type {};

  /**
   * \brief Validator for any regular grammar string type.
   *
   * \tparam RGS any type needed to be checked to ensure it is a valid regular
   * grammar string definition usable by the regular_grammar class template
   */
  template< class RGS >
    struct test_grammar_string :
    std::enable_if_t
    <
      warp::spark::detail::regular_grammar_string_traits< RGS >::is_valid,
      invalid_regular_grammar_string_type_specified
    > {};
}

namespace warp
{
namespace spark
{
  /**
   * \brief Represents a regular grammar built at compile time. Provides all
   * features needed to recognize a regular language.
   *
   * \tparam REGULAR_GRAMMAR_STRING a warp value-type containing exposing a
   * static constexpr method named value, returning the regular grammar
   * definition string
   */
  template< class REGULAR_GRAMMAR_STRING >
    class regular_grammar final :
    // ensure REGULAR_GRAMMAR_STRING type is valid
    test_grammar_string< REGULAR_GRAMMAR_STRING >
    {
    public :
    private :
      /**
       * \brief Gets the char type used for the regular grammar string
       * definition
       */
      using char_type =
        std::remove_pointer_t
        < std::remove_const_t< decltype( REGULAR_GRAMMAR_STRING::value() ) > >;

      /**
       * \brief Transform the grammar string into an integral sequence.
       *
       * \note Currently broken on all major compiler if the string is too long
       * :'(
       */
      using regular_grammar_string_sequence =
        warp::append_char_buffer_in_t
        < warp::integral_sequence< char_type >, REGULAR_GRAMMAR_STRING >;
    };

} // namespace spark
} // namespace warp

#endif // _WARP_REGULAR_GRAMMAR_HPP_
