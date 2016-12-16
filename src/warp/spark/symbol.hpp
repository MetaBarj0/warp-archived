#ifndef _WARP_SPARK_SYMBOL_HPP_
#define _WARP_SPARK_SYMBOL_HPP_

#include "regular_grammar_type_system_enumerations.hpp"
#include "../sequences/sequence_traits.hpp"
#include "../sequences/algorithm.hpp"

namespace warp::spark
{
  /**
   * \brief General form of the type representing a regular grammar symbol
   *
   * \tparam NAME the name of this symbol, encoded in an integral sequence
   * \tparam SYMBOL_TYPE member of the scoped enum symbol_types giving the type
   * of the symbol on wich this type is working on.
   * \tparam LETTER_SEQUENCE sequence of characters containing either the letter
   * the symbol is recognizing or the set of letter the symbol can't recognize
   **/
  template
    <
      class NAME,
      symbol_types SYMBOL_TYPE, class... LETTER_SEQUENCE
    >
    class symbol;

  /**
   * \brief Specific specialization working with inclusive symbol type.
   * Inclusive symbol recognizes a single letter.
   *
   * \tparam NAME the name of this symbol, encoded in an integral sequence
   * \tparam LETTER_SEQUENCE sequence of characters containing the letter the
   * symbol is recognizing
   **/
  template< class NAME, class LETTER_SEQUENCE >
    class symbol< NAME, symbol_types::inclusive, LETTER_SEQUENCE >
    {
      // rough check on name, verifying its nature and content
      static_assert( meta_sequence_traits< NAME >::is_integral_sequence,
                     "The name of the symbol (NAME template parameter) "
                     "is intended to be a valid integral sequence." );

      static_assert( for_each_value_in_t< NAME, count_integral >::value > 0,
                     "The name of the symbol (NAME template parameter) must "
                     "not be empty." );

      // checking the type of LETTER_SEQUENCE
      static_assert( meta_sequence_traits< LETTER_SEQUENCE >::
                       is_integral_sequence,
                     "The letter sequence recognized by the symbol "
                     "(LETTER_SEQUENCE template parameter) is intended to be "
                     "an integral sequence." );

      // checking the size of LETTER_SEQUENCE
      static_assert( for_each_value_in_t
                       < unique_on_t< LETTER_SEQUENCE >, count_integral >::
                       value == 1,
                     "The letter sequence recognized by the symbol "
                     "(LETTER_SEQUENCE template parameter) must contain only "
                     " one element. Inclusive symbols can recognize only one "
                     "letter." );
    };

  /**
   * \brief Specific specialization working with exclusive symbol type.
   * Exclusive symbol represents any letters but those that are specified
   *
   * \tparam NAME the name of this symbol, encoded in an integral sequence
   * \tparam LETTER_SEQUENCE sequence of characters containing letters the
   * symbol is recognizing
   **/
  template< class NAME, class LETTER_SEQUENCE >
    class symbol< NAME, symbol_types::exclusive, LETTER_SEQUENCE >
    {
      // rough check on name, verifying its nature and content
      static_assert( meta_sequence_traits< NAME >::is_integral_sequence,
                     "The name of the symbol (NAME template parameter) "
                     "is intended to be a valid integral sequence." );

      static_assert( for_each_value_in_t< NAME, count_integral >::value > 0,
                     "The name of the symbol (NAME template parameter) must "
                     "not be empty." );

      // checking the type and content of LETTER_SEQUENCE
      static_assert( meta_sequence_traits< LETTER_SEQUENCE >::
                       is_integral_sequence,
                     "The letter sequence recognized by the symbol "
                     "(LETTER_SEQUENCE template parameter) is intended to be "
                     "an integral sequence." );

      static_assert( ! is_empty_sequence< LETTER_SEQUENCE >::value,
                     "The letter sequence recognized by the symbol "
                     "(LETTER_SEQUENCE template parameter) must no be empty." );
    };

  /**
   * \brief Specific specialization working with any symbol type.
   * Any symbol type recognizes any letter.
   *
   * \tparam NAME the name of this symbol, encoded in an integral sequence
   **/
  template< class NAME >
    class symbol< NAME, symbol_types::any >
    {
      // rough check on name, verifying its nature and content
      static_assert( meta_sequence_traits< NAME >::is_integral_sequence,
                     "The name of the symbol (NAME template parameter) "
                     "is intended to be a valid integral sequence." );

      static_assert( for_each_value_in_t< NAME, count_integral >::value > 0,
                     "The name of the symbol (NAME template parameter) must "
                     "not be empty." );
    };
} // namespace warp::spark

#endif // _WARP_SPARK_SYMBOL_HPP_
