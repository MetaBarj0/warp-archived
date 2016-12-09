#ifndef   _WARP_SPARK_REGULAR_GRAMMAR_TYPE_SYSTEM_ENUMERATIONS_HPP_
#define   _WARP_SPARK_REGULAR_GRAMMAR_TYPE_SYSTEM_ENUMERATIONS_HPP_

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
}

#endif // _WARP_SPARK_REGULAR_GRAMMAR_TYPE_SYSTEM_ENUMERATIONS_HPP_
