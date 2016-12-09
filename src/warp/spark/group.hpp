#ifndef _WARP_SPARK_GROUP_HPP_
#define _WARP_SPARK_GROUP_HPP_

#include "../core/types.hpp"
#include "symbol_traits.hpp"

#include <type_traits>

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
   * \tparam SFINAE_SLOT SFINAE checks made on operand the closure will apply
   * on.
   * \tparam FIRST_GROUP_OR_SYMBOL the first operand on which the closure apply,
   * may be a symbol or a group, defaulted to allow use of sfinae checks
   * \tparam LAST_GROUP the optional last operand the closure
   * applies on, only a group is valid here.
   */
  template
    <
      class ID_TYPE, ID_TYPE ID,
      class CLOSURE_TYPE, CLOSURE_TYPE CLOSURE,
      class SFINAE_SLOT = typename sfinae_type<>::type,
      class FIRST_GROUP_OR_SYMBOL = undefined_type,
      class... LAST_GROUP
    >
    class group;

  /**
   * \brief Specialization applying the one to one unary closure on a symbol
   * type.
   *
   * \tparam ID_TYPE the integral type of the group identifier
   * \tparam ID the numerical identifier of the group
   * \tparam SYMBOL the symbol operand to apply the one to one closure on
   */
  template< class ID_TYPE, ID_TYPE ID, class SYMBOL >
    class group
    <
      ID_TYPE, ID,
      group_unary_closures, group_unary_closures::one_one,
      typename sfinae_type
        < std::enable_if_t< symbol_traits< SYMBOL >::is_symbol > >::type,
      SYMBOL
    > {};

  /**
   * \brief Specialization applying the zero to one unary closure on a symbol
   * type.
   *
   * \tparam ID_TYPE the integral type of the group identifier
   * \tparam ID the numerical identifier of the group
   * \tparam SYMBOL the symbol operand to apply the zero to one closure on
   */
  template< class ID_TYPE, ID_TYPE ID, class SYMBOL >
    class group
    <
      ID_TYPE, ID,
      group_unary_closures, group_unary_closures::zero_one,
      typename sfinae_type
        < std::enable_if_t< symbol_traits< SYMBOL >::is_symbol > >::type,
      SYMBOL
    > {};

  /**
   * \brief Specialization applying the one to many unary closure on a symbol
   * type.
   *
   * \tparam ID_TYPE the integral type of the group identifier
   * \tparam ID the numerical identifier of the group
   * \tparam SYMBOL the symbol operand to apply the one to one closure on
   */
  template< class ID_TYPE, ID_TYPE ID, class SYMBOL >
    class group
    <
      ID_TYPE, ID,
      group_unary_closures, group_unary_closures::one_many,
      typename sfinae_type
        < std::enable_if_t< symbol_traits< SYMBOL >::is_symbol > >::type,
      SYMBOL
    > {};

  /**
   * \brief Specialization applying the zero to many unary closure on a symbol
   * type.
   *
   * \tparam ID_TYPE the integral type of the group identifier
   * \tparam ID the numerical identifier of the group
   * \tparam SYMBOL the symbol operand to apply the zero to many closure on
   */
  template< class ID_TYPE, ID_TYPE ID, class SYMBOL >
    class group
    <
      ID_TYPE, ID,
      group_unary_closures, group_unary_closures::zero_many,
      typename sfinae_type
        < std::enable_if_t< symbol_traits< SYMBOL >::is_symbol > >::type,
      SYMBOL
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
   * \tparam OPERAND_SFINAE_SLOT SFINAE checks made on operand the closure will
   * apply on.
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
      class OPERAND_SFINAE_SLOT,
      class OPERAND_FIRST_GROUP_OR_SYMBOL,
      class... OPERAND_LAST_GROUP
    >
    class group
    <
      ID_TYPE, ID,
      group_unary_closures, group_unary_closures::one_one,
      sfinae_placeholder, // no sfinae check here, operand is a group
      group
        <
          OPERAND_ID_TYPE, OPERAND_ID,
          OPERAND_CLOSURE_TYPE, OPERAND_CLOSURE,
          OPERAND_SFINAE_SLOT,
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
   * \tparam OPERAND_SFINAE_SLOT SFINAE checks made on operand the closure will
   * apply on.
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
      class OPERAND_SFINAE_SLOT,
      class OPERAND_FIRST_GROUP_OR_SYMBOL,
      class... OPERAND_LAST_GROUP
    >
    class group
    <
      ID_TYPE, ID,
      group_unary_closures, group_unary_closures::zero_one,
      sfinae_placeholder, // no sfinae check here, operand is a group
      group
        <
          OPERAND_ID_TYPE, OPERAND_ID,
          OPERAND_CLOSURE_TYPE, OPERAND_CLOSURE,
          OPERAND_SFINAE_SLOT,
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
   * \tparam OPERAND_SFINAE_SLOT SFINAE checks made on operand the closure will
   * apply on.
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
      class OPERAND_SFINAE_SLOT,
      class OPERAND_FIRST_GROUP_OR_SYMBOL,
      class... OPERAND_LAST_GROUP
    >
    class group
    <
      ID_TYPE, ID,
      group_unary_closures, group_unary_closures::one_many,
      sfinae_placeholder, // no sfinae check here, operand is a group
      group
        <
          OPERAND_ID_TYPE, OPERAND_ID,
          OPERAND_CLOSURE_TYPE, OPERAND_CLOSURE,
          OPERAND_SFINAE_SLOT,
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
   * \tparam OPERAND_SFINAE_SLOT SFINAE checks made on operand the closure will
   * apply on.
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
      class OPERAND_SFINAE_SLOT,
      class OPERAND_FIRST_GROUP_OR_SYMBOL,
      class... OPERAND_LAST_GROUP
    >
    class group
    <
      ID_TYPE, ID,
      group_unary_closures, group_unary_closures::zero_many,
      sfinae_placeholder, // no sfinae check here, operand is a group
      group
        <
          OPERAND_ID_TYPE, OPERAND_ID,
          OPERAND_CLOSURE_TYPE, OPERAND_CLOSURE,
          OPERAND_SFINAE_SLOT,
          OPERAND_FIRST_GROUP_OR_SYMBOL,
          OPERAND_LAST_GROUP...
        >
    > {};
}

#endif // _WARP_SPARK_GROUP_HPP_
