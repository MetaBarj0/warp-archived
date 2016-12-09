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
   * \tparam ID_TYPE integral type of the symbol's id
   * \tparam ID numerical identifier of this symbol
   * \tparam SYMBOL_TYPE member of the scoped enum symbol_types giving the type
   * of the symbol on wich this type is working on.
   * \tparam LETTER_SEQUENCE sequence of characters containing either the letter
   * the symbol is recognizing or the set of letter the symbol can't recognize
   **/
  template
    <
      class ID_TYPE, ID_TYPE ID,
      symbol_types SYMBOL_TYPE, class... LETTER_SEQUENCE
    >
    class symbol;

  /**
   * \brief Specific specialization working with inclusive symbol type.
   * Inclusive symbol recognizes a single letter.
   *
   * \tparam ID_TYPE integral type of the symbol's id
   * \tparam ID numerical identifier of this symbol
   * \tparam LETTER_SEQUENCE sequence of characters containing the letter the
   * symbol is recognizing
   **/
  template< class ID_TYPE, ID_TYPE ID, class LETTER_SEQUENCE >
    class symbol< ID_TYPE, ID, symbol_types::inclusive, LETTER_SEQUENCE >
    {
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
   * \tparam ID_TYPE integral type of the symbol's id
   * \tparam ID numerical identifier of this symbol
   * \tparam LETTER_SEQUENCE sequence of characters containing letters the
   * symbol is recognizing
   **/
  template< class ID_TYPE, ID_TYPE ID, class LETTER_SEQUENCE >
    class symbol< ID_TYPE, ID, symbol_types::exclusive, LETTER_SEQUENCE >
    {
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
   * \tparam ID_TYPE integral type of the symbol's id
   * \tparam ID numerical identifier of this symbol
   **/
  template< class ID_TYPE, ID_TYPE ID >
    class symbol< ID_TYPE, ID, symbol_types::any >
    {
    };
} // namespace warp::spark

#endif // _WARP_SPARK_SYMBOL_HPP_
