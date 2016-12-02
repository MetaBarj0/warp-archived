#ifndef _WARP_SPARK_REGULAR_GRAMMAR_HPP_
#define _WARP_SPARK_REGULAR_GRAMMAR_HPP_

#include "../core/types.hpp"
#include "regular_grammar_type_system.hpp"

namespace warp::spark
{
  /**
   * \brief A forward declaration
   */
  template< class >
    class regular_grammar;

  /**
   * \brief Represents one regular grammar.
   * Regular (or rational) languages form a simple but important family of
   * formal languages. They can be specified in several equivalent ways : using
   * deterministic or non-deterministic finite automata, left (or right) linear
   * grammars, or regular expressions. We start with deterministic finite
   * automata as underlying structure to represent such grammars. Other
   * representations will be discussed for other grammar types.
   * This specialization accept a regular grammar definition having a form of an
   * integral sequence containing each character of a regular grammar.
   *
   * \tparam S an integral sequence template
   * \tparam T an integral type used in an integral sequence
   * \tparam VS value pack contained in the integral sequence
   *
   * \note to see how to define regular grammar, take a look at the
   * documentation on the regular_grammar template specialization dealing with a
   * value or an array type
   */
  template< template< class C, C... > class S, class T, T... VS >
    class regular_grammar< S< T, VS... > >
    {
      /**
       * \todo ensure correctness of the integral sequence type
       */

      /**
       * \todo transform this grammar into a group expression template here
       */
      using group_type = undefined_type;
    };

  /**
   * \brief Represents one regular grammar.
   * Regular (or rational) languages form a simple but important family of
   * formal languages. They can be specified in several equivalent ways : using
   * deterministic or non-deterministic finite automata, left (or right) linear
   * grammars, or regular expressions. We start with deterministic finite
   * automata as underlying structure to represent such grammars. Other
   * representations will be discussed for other grammar types.
   * This specialization works with a value or an array type containing a
   * regular grammar definition having a form of a string. It is more friendly
   * for the end-user to declare regular grammar as string rather than using a
   * rough integral sequence.
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
      /**
       * \todo ensure correctness of the value or array type
       */

      /**
       * \todo Use the type provided by the specialization using an integral
       * sequence
       */
      using group_type = undefined_type;
    };

} // namespace warp::spark

#endif // _WARP_SPARK_REGULAR_GRAMMAR_HPP_

// doxygen
/**
 * \file
 * \brief This file contains the definition of the regular_grammar template
 * type.
 */
