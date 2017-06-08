#ifndef _WARP_SPARK_GROUP_HPP_
#define _WARP_SPARK_GROUP_HPP_

#include "regular_grammar_type_system_enumerations.hpp"

namespace warp::spark
{
  /**
   * \brief General form of a group type. A group has an id, and all is about
   * applying a closure on either a symbol, or a group, or two groups.
   *
   * \tparam NAME the name of the group, integral sequence
   * \tparam CLOSURE_TYPE the type of closure to apply, either unary or binary
   * \tparam CLOSURE the actual closure to apply
   * \tparam FIRST_GROUP_OR_SYMBOL the first operand on which the closure apply,
   * may be a symbol or a group, defaulted to allow use of sfinae checks
   * \tparam LAST_GROUP the optional last operand the closure
   * applies on, only a group is valid here.
   */
  template
    <
      class NAME,
      class CLOSURE_TYPE, CLOSURE_TYPE CLOSURE,
      class FIRST_GROUP_OR_SYMBOL,
      class... LAST_GROUP
    >
    class group;

  /**
   * \brief Specialization applying the one to one unary closure on a symbol
   * type.
   *
   * \tparam NAME the name of the group, integral sequence
   * \tparam SYMBOL a correct symbol template (signature). Using this pattern
   * remove all coupling between the group type and the symbol type. The
   * end-user could provide its own symbol template implementation here as soon
   * as he respects its template signature.
   * \tparam SYMBOL_NAME the name of the specified symbol operand
   * \tparam SYMBOL_TYPE type of the provided symbol
   * \tparam SYMBOL_LETTER_SEQUENCE letter sequence used in the provided symbol
   */
  template
    <
      class NAME,
      template< class, symbol_types, class... > class SYMBOL,
      class SYMBOL_NAME,
      symbol_types SYMBOL_TYPE, class SYMBOL_LETTER_SEQUENCE
    >
    class group
    <
      NAME,
      group_unary_closures, group_unary_closures::one_one,
      SYMBOL
        <
          SYMBOL_NAME,
          SYMBOL_TYPE, SYMBOL_LETTER_SEQUENCE
        >
    > {};

  /**
   * \brief Specialization applying the zero to one unary closure on a symbol
   * type.
   *
   * \tparam NAME the name of the group, integral sequence
   * \tparam SYMBOL a correct symbol template (signature). Using this pattern
   * remove all coupling between the group type and the symbol type. The
   * end-user could provide its own symbol template implementation here.
   * \tparam SYMBOL_NAME the name of the specified symbol operand
   * \tparam SYMBOL_TYPE type of the provided symbol
   * \tparam SYMBOL_LETTER_SEQUENCE letter sequence used in the provided symbol
   */
  template
    <
      class NAME,
      template< class, symbol_types, class... > class SYMBOL,
      class SYMBOL_NAME,
      symbol_types SYMBOL_TYPE, class SYMBOL_LETTER_SEQUENCE
    >
    class group
    <
      NAME,
      group_unary_closures, group_unary_closures::zero_one,
      SYMBOL
        <
          SYMBOL_NAME,
          SYMBOL_TYPE, SYMBOL_LETTER_SEQUENCE
        >
    > {};

  /**
   * \brief Specialization applying the one to many unary closure on a symbol
   * type.
   *
   * \tparam NAME the name of the group, integral sequence
   * \tparam SYMBOL a correct symbol template (signature). Using this pattern
   * remove all coupling between the group type and the symbol type. The
   * end-user could provide its own symbol template implementation here.
   * \tparam SYMBOL_NAME the name of the specified symbol operand
   * \tparam SYMBOL_TYPE type of the provided symbol
   * \tparam SYMBOL_LETTER_SEQUENCE letter sequence used in the provided symbol
   */
  template
    <
      class NAME,
      template< class, symbol_types, class... > class SYMBOL,
      class SYMBOL_NAME,
      symbol_types SYMBOL_TYPE, class SYMBOL_LETTER_SEQUENCE
    >
    class group
    <
      NAME,
      group_unary_closures, group_unary_closures::one_many,
      SYMBOL
        <
          SYMBOL_NAME,
          SYMBOL_TYPE, SYMBOL_LETTER_SEQUENCE
        >
    > {};

  /**
   * \brief Specialization applying the zero to many unary closure on a symbol
   * type.
   *
   * \tparam NAME the name of the group, integral sequence
   * \tparam SYMBOL a correct symbol template (signature). Using this pattern
   * remove all coupling between the group type and the symbol type. The
   * end-user could provide its own symbol template implementation here.
   * \tparam SYMBOL_NAME the name of the specified symbol operand
   * \tparam SYMBOL_TYPE type of the provided symbol
   * \tparam SYMBOL_LETTER_SEQUENCE letter sequence used in the provided symbol
   */
  template
    <
      class NAME,
      template< class, symbol_types, class... > class SYMBOL,
      class SYMBOL_NAME,
      symbol_types SYMBOL_TYPE, class SYMBOL_LETTER_SEQUENCE
    >
    class group
    <
      NAME,
      group_unary_closures, group_unary_closures::zero_many,
      SYMBOL
        <
          SYMBOL_NAME,
          SYMBOL_TYPE, SYMBOL_LETTER_SEQUENCE
        >
    > {};

  /**
   * \brief Specialization applying the one to one unary closure on a group
   * type.
   *
   * \tparam NAME the name of the group, integral sequence
   * \tparam OPERAND_NAME the name of the group operand
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
      class NAME,
      class OPERAND_NAME,
      class OPERAND_CLOSURE_TYPE, OPERAND_CLOSURE_TYPE OPERAND_CLOSURE,
      class OPERAND_FIRST_GROUP_OR_SYMBOL,
      class... OPERAND_LAST_GROUP
    >
    class group
    <
      NAME,
      group_unary_closures, group_unary_closures::one_one,
      group
        <
          OPERAND_NAME,
          OPERAND_CLOSURE_TYPE, OPERAND_CLOSURE,
          OPERAND_FIRST_GROUP_OR_SYMBOL,
          OPERAND_LAST_GROUP...
        >
    > {};

  /**
   * \brief Specialization applying the zero to one unary closure on a group
   * type.
   *
   * \tparam NAME the name of the group, integral sequence
   * \tparam OPERAND_NAME the name of the group operand
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
      class NAME,
      class OPERAND_NAME,
      class OPERAND_CLOSURE_TYPE, OPERAND_CLOSURE_TYPE OPERAND_CLOSURE,
      class OPERAND_FIRST_GROUP_OR_SYMBOL,
      class... OPERAND_LAST_GROUP
    >
    class group
    <
      NAME,
      group_unary_closures, group_unary_closures::zero_one,
      group
        <
          OPERAND_NAME,
          OPERAND_CLOSURE_TYPE, OPERAND_CLOSURE,
          OPERAND_FIRST_GROUP_OR_SYMBOL,
          OPERAND_LAST_GROUP...
        >
    > {};

  /**
   * \brief Specialization applying the one to many unary closure on a group
   * type.
   *
   * \tparam NAME the name of the group, integral sequence
   * \tparam OPERAND_NAME the name of the group operand
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
      class NAME,
      class OPERAND_NAME,
      class OPERAND_CLOSURE_TYPE, OPERAND_CLOSURE_TYPE OPERAND_CLOSURE,
      class OPERAND_FIRST_GROUP_OR_SYMBOL,
      class... OPERAND_LAST_GROUP
    >
    class group
    <
      NAME,
      group_unary_closures, group_unary_closures::one_many,
      group
        <
          OPERAND_NAME,
          OPERAND_CLOSURE_TYPE, OPERAND_CLOSURE,
          OPERAND_FIRST_GROUP_OR_SYMBOL,
          OPERAND_LAST_GROUP...
        >
    > {};

  /**
   * \brief Specialization applying the zero to many unary closure on a group
   * type.
   *
   * \tparam NAME the name of the group, integral sequence
   * \tparam OPERAND_NAME the name of the group operand
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
      class NAME,
      class OPERAND_NAME,
      class OPERAND_CLOSURE_TYPE, OPERAND_CLOSURE_TYPE OPERAND_CLOSURE,
      class OPERAND_FIRST_GROUP_OR_SYMBOL,
      class... OPERAND_LAST_GROUP
    >
    class group
    <
      NAME,
      group_unary_closures, group_unary_closures::zero_many,
      group
        <
          OPERAND_NAME,
          OPERAND_CLOSURE_TYPE, OPERAND_CLOSURE,
          OPERAND_FIRST_GROUP_OR_SYMBOL,
          OPERAND_LAST_GROUP...
        >
    > {};

  /**
   * \brief Specialization applying the concatenation closure on two group
   * operand types.
   *
   * \tparam NAME the name of the group, integral sequence
   * \tparam FIRST_OPERAND_NAME the name of the first group operand
   * \tparam FIRST_OPERAND_CLOSURE_TYPE the type of closure to apply, either
   * unary or binary. part of the first operand.
   * \tparam FIRST_OPERAND_CLOSURE the actual closure to apply. Part of the
   * first operand
   * \tparam FIRST_OPERAND_FIRST_GROUP_OR_SYMBOL the first operand on which the
   * closure apply, may be a symbol or a group.
   * \tparam FIRST_OPERAND_LAST_GROUP the optional last operand the closure
   * applies on, only a group is valid here.
   * \tparam LAST_OPERAND_NAME the name of the last group operand
   * \tparam LAST_OPERAND_CLOSURE_TYPE the type of closure to apply, either
   * unary or binary. part of the last operand.
   * \tparam LAST_OPERAND_CLOSURE the actual closure to apply. Part of the
   * last operand
   * \tparam LAST_OPERAND_LAST_GROUP_OR_SYMBOL the last operand on which the
   * closure apply, may be a symbol or a group.
   * \tparam LAST_OPERAND_LAST_GROUP the optional last operand the closure
   * applies on, only a group is valid here.
   */
  template
    <
      class NAME,
      class FIRST_OPERAND_NAME,
      class FIRST_OPERAND_CLOSURE_TYPE,
      FIRST_OPERAND_CLOSURE_TYPE FIRST_OPERAND_CLOSURE,
      class FIRST_OPERAND_FIRST_GROUP_OR_SYMBOL,
      class... FIRST_OPERAND_LAST_GROUP,
      class LAST_OPERAND_NAME,
      class LAST_OPERAND_CLOSURE_TYPE,
      LAST_OPERAND_CLOSURE_TYPE LAST_OPERAND_CLOSURE,
      class LAST_OPERAND_LAST_GROUP_OR_SYMBOL,
      class... LAST_OPERAND_LAST_GROUP
    >
    class group
    <
      NAME,
      group_binary_closures, group_binary_closures::concatenation,
      group
        <
          FIRST_OPERAND_NAME,
          FIRST_OPERAND_CLOSURE_TYPE, FIRST_OPERAND_CLOSURE,
          FIRST_OPERAND_FIRST_GROUP_OR_SYMBOL,
          FIRST_OPERAND_LAST_GROUP...
        >,
      group
        <
          LAST_OPERAND_NAME,
          LAST_OPERAND_CLOSURE_TYPE, LAST_OPERAND_CLOSURE,
          LAST_OPERAND_LAST_GROUP_OR_SYMBOL,
          LAST_OPERAND_LAST_GROUP...
        >
    > {};

  /**
   * \brief Specialization applying the alternation closure on two group operand
   * types.
   *
   * \tparam NAME the name of the group, integral sequence
   * \tparam FIRST_OPERAND_NAME the name of the first group operand
   * \tparam FIRST_OPERAND_CLOSURE_TYPE the type of closure to apply, either
   * unary or binary. part of the first operand.
   * \tparam FIRST_OPERAND_CLOSURE the actual closure to apply. Part of the
   * first operand
   * \tparam FIRST_OPERAND_FIRST_GROUP_OR_SYMBOL the first operand on which the
   * closure apply, may be a symbol or a group.
   * \tparam FIRST_OPERAND_LAST_GROUP the optional last operand the closure
   * applies on, only a group is valid here.
   * \tparam LAST_OPERAND_NAME the name of the last group operand
   * \tparam LAST_OPERAND_CLOSURE_TYPE the type of closure to apply, either
   * unary or binary. part of the last operand.
   * \tparam LAST_OPERAND_CLOSURE the actual closure to apply. Part of the
   * last operand
   * \tparam LAST_OPERAND_LAST_GROUP_OR_SYMBOL the last operand on which the
   * closure apply, may be a symbol or a group.
   * \tparam LAST_OPERAND_LAST_GROUP the optional last operand the closure
   * applies on, only a group is valid here.
   */
  template
    <
      class NAME,
      class FIRST_OPERAND_NAME,
      class FIRST_OPERAND_CLOSURE_TYPE,
      FIRST_OPERAND_CLOSURE_TYPE FIRST_OPERAND_CLOSURE,
      class FIRST_OPERAND_FIRST_GROUP_OR_SYMBOL,
      class... FIRST_OPERAND_LAST_GROUP,
      class LAST_OPERAND_NAME,
      class LAST_OPERAND_CLOSURE_TYPE,
      LAST_OPERAND_CLOSURE_TYPE LAST_OPERAND_CLOSURE,
      class LAST_OPERAND_LAST_GROUP_OR_SYMBOL,
      class... LAST_OPERAND_LAST_GROUP
    >
    class group
    <
      NAME,
      group_binary_closures, group_binary_closures::alternation,
      group
        <
          FIRST_OPERAND_NAME,
          FIRST_OPERAND_CLOSURE_TYPE, FIRST_OPERAND_CLOSURE,
          FIRST_OPERAND_FIRST_GROUP_OR_SYMBOL,
          FIRST_OPERAND_LAST_GROUP...
        >,
      group
        <
          LAST_OPERAND_NAME,
          LAST_OPERAND_CLOSURE_TYPE, LAST_OPERAND_CLOSURE,
          LAST_OPERAND_LAST_GROUP_OR_SYMBOL,
          LAST_OPERAND_LAST_GROUP...
        >
    > {};
}

#endif // _WARP_SPARK_GROUP_HPP_
