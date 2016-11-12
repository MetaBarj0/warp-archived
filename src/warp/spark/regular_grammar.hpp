#ifndef _WARP_REGULAR_GRAMMAR_HPP_
#define _WARP_REGULAR_GRAMMAR_HPP_

#include "../core/types.hpp"
#include "regular_grammar_traits.hpp"

#include <type_traits>

namespace
{
/**
 * \brief Hidden implementation of the regular_grammar template. This type is
 * not accessible outside of its compilation unit and contains all that is
 * necessary to implement the regular_grammar concept. This type will performs
 * all compile time checks to ensure the regular grammar definition validity
 * and, if appropriate, provide and understandable error message at compile
 * time.
 *
 * \tparam T the regular grammar definition
 */
template< class T >
  class regular_grammar_impl
  {
    static_assert( warp::spark::regular_grammar_definition_traits< T >::
                     is_valid,
                   "Specified template parameter type is not a valid "
                   "regular grammar definition. Please, refer to the "
                   "documentation to know how to define valid regular "
                   "grammars usable by spark.");

    /**
     * \brief Define an uniformed form of regular grammar definition. At this
     * point, regular grammar definition is considered valid and is transformed
     * into an integral sequence containing each characters of the regular
     * grammar definition using a dedicated traits class.
     */
    using regular_grammar_definition_sequence =
      typename warp::spark::regular_grammar_definition_traits< T >::
      sequence_type;
  };
}

namespace warp::spark
{
/**
 * \brief Represents one regular grammar.
 * Regular (or rational) languages form a simple but important family of formal
 * languages. They can be specified in several equivalent ways : using
 * deterministic or non-deterministic finite automata, left (or right) linear
 * grammars, or regular expressions. We start with deterministic finite
 * automata as underlying structure to represent such grammars. Other
 * representations will be discussed for other grammar types.
 *
 * \tparam T A value type or array type. Such type can be simple class or struct
 * containing either :
 * - a static value member of constexpr constant char buffer type
 * \code
 * struct grammar_string { static constexpr auto value = "..."; };
 * \endcode
 * - or a static value function of constexpr constant char buffer type
 * \code
 * struct grammar_string { static constexpr auto value() { return "..."; } };
 * \endcode
 * - or a static array member storing constexpr char buffers
 * \code
 * struct grammar_strings
 * { static constexpr const char *array[] = { "...", "..." }; };
 * \endcode
 * The last form (array) is a workaround allowing the user to deal with large
 * constexpr char buffer longer than 512 characters long.
 */
template< class T >
  class regular_grammar
  {
    using impl = regular_grammar_impl< T >;
  };
} // namespace warp::spark

#endif // _WARP_REGULAR_GRAMMAR_HPP_
