#ifndef _WARP_SPARK_SYMBOL_HPP_
#define _WARP_SPARK_SYMBOL_HPP_

#include "regular_grammar_type_system_enumerations.hpp"

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
    class symbol< NAME, symbol_types::inclusive, LETTER_SEQUENCE > {};

  /**
   * \brief Specific specialization working with exclusive symbol type.
   * Exclusive symbol represents any letters but those that are specified
   *
   * \tparam NAME the name of this symbol, encoded in an integral sequence
   * \tparam LETTER_SEQUENCE sequence of characters containing letters the
   * symbol is recognizing
   **/
  template< class NAME, class LETTER_SEQUENCE >
    class symbol< NAME, symbol_types::exclusive, LETTER_SEQUENCE > {};

  /**
   * \brief Specific specialization working with any symbol type.
   * Any symbol type recognizes any letter.
   *
   * \tparam NAME the name of this symbol, encoded in an integral sequence
   **/
  template< class NAME >
    class symbol< NAME, symbol_types::any > {};
} // namespace warp::spark

#endif // _WARP_SPARK_SYMBOL_HPP_
