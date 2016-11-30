#ifndef _WARP_SPARK_REGULAR_GRAMMAR_HPP_
#define _WARP_SPARK_REGULAR_GRAMMAR_HPP_

#include "../core/types.hpp"
#include "regular_grammar_type_system.hpp"

#include <type_traits>

namespace warp::spark
{
  /**
   * \brief Represents one regular grammar.
   * Regular (or rational) languages form a simple but important family of
   * formal languages. They can be specified in several equivalent ways : using
   * deterministic or non-deterministic finite automata, left (or right) linear
   * grammars, or regular expressions. We start with deterministic finite
   * automata as underlying structure to represent such grammars. Other
   * representations will be discussed for other grammar types.
   *
   * \tparam T A value type or array type or an integral sequence. Such type can
   * be simple class or struct containing either :
   * - an integral sequence containing each character of the regular grammar
   *   definition string
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
    };
} // namespace warp::spark

#endif // _WARP_SPARK_REGULAR_GRAMMAR_HPP_

// doxygen
/**
 * \file
 * \brief This file contains the definition of the regular_grammar template
 * type.
 */
