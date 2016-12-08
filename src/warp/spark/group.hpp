#ifndef _WARP_SPARK_GROUP_HPP_
#define _WARP_SPARK_GROUP_HPP_

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

  template
    <
      class CLOSURE_TYPE, CLOSURE_TYPE CLOSURE,
      class FIRST_GROUP_OR_SYMBOL, class... LAST_GROUP
    >
    class group;
}

#endif // _WARP_SPARK_GROUP_HPP_
