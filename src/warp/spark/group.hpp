#ifndef _WARP_SPARK_GROUP_HPP_
#define _WARP_SPARK_GROUP_HPP_

#include "regular_grammar_type_system_enumerations.hpp"

namespace warp::spark
{
  /**
   * \brief General form of a group type. A group has an id, and all is about
   * applying a closure on either a symbol, or a group, or two groups.
   *
   * \tparam ID_TYPE integral type of the group's identifier
   * \tparam ID numerical identifier of the group
   * \tparam CLOSURE_TYPE the type of closure to apply, either unary or binary
   * \tparam CLOSURE the actual closure to apply
   * \tparam FIRST_GROUP_OR_SYMBOL the first operand on which the closure apply,
   * may be a symbol or a group, defaulted to allow use of sfinae checks
   * \tparam LAST_GROUP the optional last operand the closure
   * applies on, only a group is valid here.
   */
  template
    <
      class ID_TYPE, ID_TYPE ID,
      class CLOSURE_TYPE, CLOSURE_TYPE CLOSURE,
      class FIRST_GROUP_OR_SYMBOL,
      class... LAST_GROUP
    >
    class group;

  /**
   * \brief Specialization applying the one to one unary closure on a symbol
   * type.
   *
   * \tparam ID_TYPE the integral type of the group identifier
   * \tparam ID the numerical identifier of the group
   * \tparam SYMBOL a correct symbol template (signature). Using this pattern
   * remove all coupling between the group type and the symbol type. The
   * end-user could provide its own symbol template implementation here.
   * \tparam SYMBOL_ID_TYPE integral type used by the identifier of the provided
   * symbol
   * \tparam ID identifier of the provided symbol
   * \tparam SYMBOL_TYPE type of the provided symbol
   * \tparam SYMBOL_LETTER_SEQUENCE letter sequence used in the provided symbol
   */
  template
    <
      class ID_TYPE, ID_TYPE ID,
      template< class I, I, symbol_types, class... > class SYMBOL,
      class SYMBOL_ID_TYPE, SYMBOL_ID_TYPE SYMBOL_ID,
      symbol_types SYMBOL_TYPE, class SYMBOL_LETTER_SEQUENCE
    >
    class group
    <
      ID_TYPE, ID,
      group_unary_closures, group_unary_closures::one_one,
      SYMBOL
        <
          SYMBOL_ID_TYPE, SYMBOL_ID,
          SYMBOL_TYPE, SYMBOL_LETTER_SEQUENCE
        >
    > {};

  /**
   * \brief Specialization applying the zero to one unary closure on a symbol
   * type.
   *
   * \tparam ID_TYPE the integral type of the group identifier
   * \tparam ID the numerical identifier of the group
   * \tparam SYMBOL a correct symbol template (signature). Using this pattern
   * remove all coupling between the group type and the symbol type. The
   * end-user could provide its own symbol template implementation here.
   * \tparam SYMBOL_ID_TYPE integral type used by the identifier of the provided
   * symbol
   * \tparam ID identifier of the provided symbol
   * \tparam SYMBOL_TYPE type of the provided symbol
   * \tparam SYMBOL_LETTER_SEQUENCE letter sequence used in the provided symbol
   */
  template
    <
      class ID_TYPE, ID_TYPE ID,
      template< class I, I, symbol_types, class... > class SYMBOL,
      class SYMBOL_ID_TYPE, SYMBOL_ID_TYPE SYMBOL_ID,
      symbol_types SYMBOL_TYPE, class SYMBOL_LETTER_SEQUENCE
    >
    class group
    <
      ID_TYPE, ID,
      group_unary_closures, group_unary_closures::zero_one,
      SYMBOL
        <
          SYMBOL_ID_TYPE, SYMBOL_ID,
          SYMBOL_TYPE, SYMBOL_LETTER_SEQUENCE
        >
    > {};

  /**
   * \brief Specialization applying the one to many unary closure on a symbol
   * type.
   *
   * \tparam ID_TYPE the integral type of the group identifier
   * \tparam ID the numerical identifier of the group
   * \tparam SYMBOL a correct symbol template (signature). Using this pattern
   * remove all coupling between the group type and the symbol type. The
   * end-user could provide its own symbol template implementation here.
   * \tparam SYMBOL_ID_TYPE integral type used by the identifier of the provided
   * symbol
   * \tparam ID identifier of the provided symbol
   * \tparam SYMBOL_TYPE type of the provided symbol
   * \tparam SYMBOL_LETTER_SEQUENCE letter sequence used in the provided symbol
   */
  template
    <
      class ID_TYPE, ID_TYPE ID,
      template< class I, I, symbol_types, class... > class SYMBOL,
      class SYMBOL_ID_TYPE, SYMBOL_ID_TYPE SYMBOL_ID,
      symbol_types SYMBOL_TYPE, class SYMBOL_LETTER_SEQUENCE
    >
    class group
    <
      ID_TYPE, ID,
      group_unary_closures, group_unary_closures::one_many,
      SYMBOL
        <
          SYMBOL_ID_TYPE, SYMBOL_ID,
          SYMBOL_TYPE, SYMBOL_LETTER_SEQUENCE
        >
    > {};

  /**
   * \brief Specialization applying the zero to many unary closure on a symbol
   * type.
   *
   * \tparam ID_TYPE the integral type of the group identifier
   * \tparam ID the numerical identifier of the group
   * \tparam SYMBOL a correct symbol template (signature). Using this pattern
   * remove all coupling between the group type and the symbol type. The
   * end-user could provide its own symbol template implementation here.
   * \tparam SYMBOL_ID_TYPE integral type used by the identifier of the provided
   * symbol
   * \tparam ID identifier of the provided symbol
   * \tparam SYMBOL_TYPE type of the provided symbol
   * \tparam SYMBOL_LETTER_SEQUENCE letter sequence used in the provided symbol
   */
  template
    <
      class ID_TYPE, ID_TYPE ID,
      template< class I, I, symbol_types, class... > class SYMBOL,
      class SYMBOL_ID_TYPE, SYMBOL_ID_TYPE SYMBOL_ID,
      symbol_types SYMBOL_TYPE, class SYMBOL_LETTER_SEQUENCE
    >
    class group
    <
      ID_TYPE, ID,
      group_unary_closures, group_unary_closures::zero_many,
      SYMBOL
        <
          SYMBOL_ID_TYPE, SYMBOL_ID,
          SYMBOL_TYPE, SYMBOL_LETTER_SEQUENCE
        >
    > {};

  /**
   * \brief Specialization applying the one to one unary closure on a group
   * type.
   *
   * \tparam ID_TYPE the integral type of the group identifier
   * \tparam ID the numerical identifier of the group
   * \tparam OPERAND_ID_TYPE the integral type of the group operand
   * \tparam OPERAND_ID the numerical identifier of the group operand
   * \tparam OPERAND_CLOSURE_TYPE the type of closure to apply, either unary or
   * binary
   * \tparam OPERAND_CLOSURE the actual closure to apply
   * \tparam OPERAND_FIRST_GROUP_OR_SYMBOL the first operand on which the
   * closure apply, may be a symbol or a group, defaulted to allow use of sfinae
   * checks
   * \tparam OPERAND_LAST_GROUP the optional last operand the closure applies
   * on, only a group is valid here.
   */
  template
    <
      class ID_TYPE, ID_TYPE ID,
      class OPERAND_ID_TYPE, OPERAND_ID_TYPE OPERAND_ID,
      class OPERAND_CLOSURE_TYPE, OPERAND_CLOSURE_TYPE OPERAND_CLOSURE,
      class OPERAND_FIRST_GROUP_OR_SYMBOL,
      class... OPERAND_LAST_GROUP
    >
    class group
    <
      ID_TYPE, ID,
      group_unary_closures, group_unary_closures::one_one,
      group
        <
          OPERAND_ID_TYPE, OPERAND_ID,
          OPERAND_CLOSURE_TYPE, OPERAND_CLOSURE,
          OPERAND_FIRST_GROUP_OR_SYMBOL,
          OPERAND_LAST_GROUP...
        >
    > {};

  /**
   * \brief Specialization applying the zero to one unary closure on a group
   * type.
   *
   * \tparam ID_TYPE the integral type of the group identifier
   * \tparam ID the numerical identifier of the group
   * \tparam OPERAND_ID_TYPE the integral type of the group operand
   * \tparam OPERAND_ID the numerical identifier of the group operand
   * \tparam OPERAND_CLOSURE_TYPE the type of closure to apply, either unary or
   * binary
   * \tparam OPERAND_CLOSURE the actual closure to apply
   * \tparam OPERAND_FIRST_GROUP_OR_SYMBOL the first operand on which the
   * closure apply, may be a symbol or a group, defaulted to allow use of sfinae
   * checks
   * \tparam OPERAND_LAST_GROUP the optional last operand the closure applies
   * on, only a group is valid here.
   */
  template
    <
      class ID_TYPE, ID_TYPE ID,
      class OPERAND_ID_TYPE, OPERAND_ID_TYPE OPERAND_ID,
      class OPERAND_CLOSURE_TYPE, OPERAND_CLOSURE_TYPE OPERAND_CLOSURE,
      class OPERAND_FIRST_GROUP_OR_SYMBOL,
      class... OPERAND_LAST_GROUP
    >
    class group
    <
      ID_TYPE, ID,
      group_unary_closures, group_unary_closures::zero_one,
      group
        <
          OPERAND_ID_TYPE, OPERAND_ID,
          OPERAND_CLOSURE_TYPE, OPERAND_CLOSURE,
          OPERAND_FIRST_GROUP_OR_SYMBOL,
          OPERAND_LAST_GROUP...
        >
    > {};

  /**
   * \brief Specialization applying the one to many unary closure on a group
   * type.
   *
   * \tparam ID_TYPE the integral type of the group identifier
   * \tparam ID the numerical identifier of the group
   * \tparam OPERAND_ID_TYPE the integral type of the group operand
   * \tparam OPERAND_ID the numerical identifier of the group operand
   * \tparam OPERAND_CLOSURE_TYPE the type of closure to apply, either unary or
   * binary
   * \tparam OPERAND_CLOSURE the actual closure to apply
   * \tparam OPERAND_FIRST_GROUP_OR_SYMBOL the first operand on which the
   * closure apply, may be a symbol or a group, defaulted to allow use of sfinae
   * checks
   * \tparam OPERAND_LAST_GROUP the optional last operand the closure applies
   * on, only a group is valid here.
   */
  template
    <
      class ID_TYPE, ID_TYPE ID,
      class OPERAND_ID_TYPE, OPERAND_ID_TYPE OPERAND_ID,
      class OPERAND_CLOSURE_TYPE, OPERAND_CLOSURE_TYPE OPERAND_CLOSURE,
      class OPERAND_FIRST_GROUP_OR_SYMBOL,
      class... OPERAND_LAST_GROUP
    >
    class group
    <
      ID_TYPE, ID,
      group_unary_closures, group_unary_closures::one_many,
      group
        <
          OPERAND_ID_TYPE, OPERAND_ID,
          OPERAND_CLOSURE_TYPE, OPERAND_CLOSURE,
          OPERAND_FIRST_GROUP_OR_SYMBOL,
          OPERAND_LAST_GROUP...
        >
    > {};

  /**
   * \brief Specialization applying the zero to many unary closure on a group
   * type.
   *
   * \tparam ID_TYPE the integral type of the group identifier
   * \tparam ID the numerical identifier of the group
   * \tparam OPERAND_ID_TYPE the integral type of the group operand
   * \tparam OPERAND_ID the numerical identifier of the group operand
   * \tparam OPERAND_CLOSURE_TYPE the type of closure to apply, either unary or
   * binary
   * \tparam OPERAND_CLOSURE the actual closure to apply
   * \tparam OPERAND_FIRST_GROUP_OR_SYMBOL the first operand on which the
   * closure apply, may be a symbol or a group, defaulted to allow use of sfinae
   * checks
   * \tparam OPERAND_LAST_GROUP the optional last operand the closure applies
   * on, only a group is valid here.
   */
  template
    <
      class ID_TYPE, ID_TYPE ID,
      class OPERAND_ID_TYPE, OPERAND_ID_TYPE OPERAND_ID,
      class OPERAND_CLOSURE_TYPE, OPERAND_CLOSURE_TYPE OPERAND_CLOSURE,
      class OPERAND_FIRST_GROUP_OR_SYMBOL,
      class... OPERAND_LAST_GROUP
    >
    class group
    <
      ID_TYPE, ID,
      group_unary_closures, group_unary_closures::zero_many,
      group
        <
          OPERAND_ID_TYPE, OPERAND_ID,
          OPERAND_CLOSURE_TYPE, OPERAND_CLOSURE,
          OPERAND_FIRST_GROUP_OR_SYMBOL,
          OPERAND_LAST_GROUP...
        >
    > {};
}

#endif // _WARP_SPARK_GROUP_HPP_
