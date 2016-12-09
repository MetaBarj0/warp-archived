#ifndef _WARP_SPARK_GROUP_HPP_
#define _WARP_SPARK_GROUP_HPP_

#include "symbol_traits.hpp"

namespace warp::spark
{
  /**
   * \brief Representing all binary closure types a group can have in its type
   * definition. Binary closures act on two groups
   **/
  enum class group_binary_closures
  {
    /**
     * \brief Concatenation closure
     **/
    concatenation,

    /**
     * \brief Alternation (or union) closure
     **/
    alternation
  };

  /**
   * \brief Representing all unary closure types a group can have in its type
   * definition. Unary closures are quantifiers such as the kleen's star
   **/
  enum class group_unary_closures
  {
    /**
     * \brief Representing the '?' quantifier closure in a regular expression
     **/
    zero_one,

    /**
     * \brief Representing the no quantifier closure in a regular expression
     **/
    one_one,

    /**
     * \brief Representing the quantifier '*' closure in a regular expression.
     * Also know as the Kleen's star closure.
     **/
    zero_many,

    /**
     * \brief Representing the quantifier '+' closure in a regular expression.
     **/
    one_many
  };

  /**
   * \brief General form of a group type. A group has an id, and all is about
   * applying a closure on either a symbol, or a group, or two groups.
   *
   * \tparam ID_TYPE integral type of the group's identifier
   * \tparam ID numerical identifier of the group
   * \tparam CLOSURE_TYPE the type of closure to apply, either unary or binary
   * \tparam CLOSURE the actual closure to apply
   * \tparam SFINAE_OPERANDS SFINAE checks made on operand the closure will
   * apply on.
   * \tparam FIRST_GROUP_OR_SYMBOL the first operand on which the closure apply,
   * may be a symbol or a group, defaulted to allow use of sfinae checks
   * \tparam LAST_GROUP_AND_SFINAE_GROUP the optional last operand the closure
   * applies on, only a group is valid here. it is ensured by the use of some
   * sfinae magic
   */
  template
    <
      class ID_TYPE, ID_TYPE ID,
      class CLOSURE_TYPE, CLOSURE_TYPE CLOSURE,
      class SFINAE_OPERANDS = typename sfinae_type<>::type,
      class FIRST_GROUP_OR_SYMBOL = undefined_type,
      class... LAST_GROUP_AND_SFINAE_GROUP
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
}

#endif // _WARP_SPARK_GROUP_HPP_
