#ifndef _WARP_SPARK_SYMBOL_HPP_
#define _WARP_SPARK_SYMBOL_HPP_

#include "../sequences/sequence_traits.hpp"
#include "../sequences/algorithm.hpp"

namespace warp::spark
{
  /**
   * \brief Different type of symbol types
   */
  enum class symbol_types
  {
    /**
     * \brief an inclusive symbol recognizes an unique letter
     */
    inclusive,

    /**
     * \brief An exclusive symbol recognizes any but specified letters
     **/
    exclusive,

    /**
     * \brief An any symbol recognizes any letter
     **/
    any
  };

  /**
   * \brief General form of the type representing a regular grammar symbol
   *
   * \tparam NAME the name of this symbol, intended to be an integral sequence
   * \tparam SYMBOL_TYPE member of the scoped enum symbol_types giving the type
   * of the symbol on wich this type is working on.
   * \tparam LETTER_SEQUENCE sequence of characters containing either the letter
   * the symbol is recognizing or the set of letter the symbol can't recognize
   **/
  template< class NAME,  symbol_types SYMBOL_TYPE, class... LETTER_SEQUENCE >
    class symbol;

  /**
   * \brief Specific specialization working with inclusive symbol type.
   * Inclusive symbol recognizes a single letter.
   *
   * \tparam NAME the name of this symbol, intended to be an integral sequence
   * \tparam LETTER_SEQUENCE sequence of characters containing the letter the
   * symbol is recognizing
   **/
  template< class NAME, class LETTER_SEQUENCE >
    class symbol< NAME, symbol_types::inclusive, LETTER_SEQUENCE >
    {
      // check type and content of NAME
      static_assert( meta_sequence_traits< NAME >::integral_sequence,
                     "The symbol's name (NAME template parameter) is intended "
                     "to be an integral sequence." );

      static_assert( ! is_empty_sequence< NAME >::value,
                     "The symbol's name (NAME template parameter) cannot be "
                     "empty." );

      // checking the type of LETTER_SEQUENCE
      static_assert( meta_sequence_traits< LETTER_SEQUENCE >::integral_sequence,
                     "The letter sequence recognized by the symbol "
                     "(LETTER_SEQUENCE template parameter) is intended to be "
                     "an integral sequence." );

      /**
       * \brief Alias on the letter sequence after removed all duplicated values
       */
      using letter_sequence_unique = unique_on_t< LETTER_SEQUENCE >;

      // checking the size of LETTER_SEQUENCE
      static_assert( for_each_value_in_t
                       < letter_sequence_unique, count_integral >::value == 1,
                     "The letter sequence recognized by the symbol "
                     "(LETTER_SEQUENCE template parameter) must contain only "
                     " one element. Inclusive symbols can recognize only one "
                     "letter." );
    };

  /**
   * \brief Specific specialization working with exclusive symbol type.
   * Exclusive symbol represents any letters but those that are specified
   *
   * \tparam NAME the name of this symbol, intended to be an integral sequence
   * \tparam LETTER_SEQUENCE sequence of characters containing letters the
   * symbol is recognizing
   **/
  template< class NAME, class LETTER_SEQUENCE >
    class symbol< NAME, symbol_types::exclusive, LETTER_SEQUENCE >
    {
      // check type and content of NAME
      static_assert( meta_sequence_traits< NAME >::integral_sequence,
                     "The symbol's name (NAME template parameter) is intended "
                     "to be an integral sequence." );

      static_assert( ! is_empty_sequence< NAME >::value,
                     "The symbol's name (NAME template parameter) cannot be "
                     "empty." );

      // checking the type and content of LETTER_SEQUENCE
      static_assert( meta_sequence_traits< LETTER_SEQUENCE >::integral_sequence,
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
   * \tparam NAME the name of this symbol, intended to be an integral sequence
   **/
  template< class NAME >
    class symbol< NAME, symbol_types::any >
    {
      // check type and content of NAME
      static_assert( meta_sequence_traits< NAME >::integral_sequence,
                     "The symbol's name (NAME template parameter) is intended "
                     "to be an integral sequence." );

      static_assert( ! is_empty_sequence< NAME >::value,
                     "The symbol's name (NAME template parameter) cannot be "
                     "empty." );
    };
} // namespace warp::spark

#endif // _WARP_SPARK_SYMBOL_HPP_
