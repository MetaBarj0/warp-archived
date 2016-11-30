#ifndef _WARP_SPARK_SYMBOL_TRAITS_HPP_
#define _WARP_SPARK_SYMBOL_TRAITS_HPP_

#include "symbol.hpp"

namespace warp::spark
{
  /**
   * \brief A traits class for a symbol type. Non specialized version used when
   * T not a symbol type
   *
   * \tparam T any type but a symbol type
   */
  template< class T >
    struct symbol_traits;

  /**
   * \brief A specialization used with a an inclusive symbol type.
   *
   * \tparam NAME the symbol name
   * \tparam LETTER_SEQUENCE the letter sequence the symbol deals with
   */
  template< class NAME, class LETTER_SEQUENCE >
    struct symbol_traits
    < symbol< NAME, symbol_types::inclusive, LETTER_SEQUENCE > >
    {
      /**
       * \brief This symbol is an inclusive one
       */
      static constexpr auto symbol_type = symbol_types::inclusive;

      /**
       * \brief The name of this symbol, integral sequence
       */
      using symbol_name = NAME;

      /**
       * \brief The letter sequence used in the symbol. As it's an inclusive
       * symbol, the sequence contains only one char
       */
      using symbol_letter_sequence = LETTER_SEQUENCE;
    };

  /**
   * \brief A specialization used with a an exclusive symbol type.
   *
   * \tparam NAME the symbol name
   * \tparam LETTER_SEQUENCE the letter sequence the symbol deals with
   */
  template< class NAME, class LETTER_SEQUENCE >
    struct symbol_traits
    < symbol< NAME, symbol_types::exclusive, LETTER_SEQUENCE > >
    {
      /**
       * \brief This symbol is an exclusive one
       */
      static constexpr auto symbol_type = symbol_types::exclusive;

      /**
       * \brief The name of this symbol, integral sequence
       */
      using symbol_name = NAME;

      /**
       * \brief The letter sequence used in the symbol. As it's an exclusive
       * symbol, the sequence contains one or more char
       */
      using symbol_letter_sequence = LETTER_SEQUENCE;
    };

  /**
   * \brief A specialization used with a an any symbol type.
   *
   * \tparam NAME the symbol name
   */
  template< class NAME >
    struct symbol_traits< symbol< NAME, symbol_types::any > >
    {
      /**
       * \brief This symbol is an any one
       */
      static constexpr auto symbol_type = symbol_types::exclusive;

      /**
       * \brief The name of this symbol, integral sequence
       */
      using symbol_name = NAME;

      /**
       * \brief An any symbol does not have any letter sequence
       */
      using symbol_letter_sequence = undefined_type;
    };
} // namespace warp::spark

#endif // _WARP_SPARK_SYMBOL_TRAITS_HPP_

// doxygen
/**
 * \file
 * \brief Contains traits class for warp::spark symbol
 */
