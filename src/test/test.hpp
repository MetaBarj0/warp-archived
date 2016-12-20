#ifndef _TEST_HPP_
#define _TEST_HPP_

// this is the library tested
#include "warp.hpp"

/**
 * \brief The test namespace will contain all that is necessary to test stuff.
 * Will contain types and functions.
 */
namespace test
{
/**
  \brief Types containing all tests for warp::signed_auto_constant and
  warp::unsigned_auto_constant
**/
struct auto_constant_tester
{
  // static methods
  /**
    \brief This method will contain all code necessary to obtain the strictest
    signed integral type that contain a specified value
  **/
  static void auto_type_signed_constant();

  /**
    \brief This method will contain all code necessary to obtain the strictest
    unsigned integral type that contain a specified value
  **/
  static void auto_type_unsigned_constant();
};

/**
 * \brief A tester relative to meta sequences
 */
struct sequence_algorithms_tester
{
  // some intern types
  /**
   * \brief Base class used for type list runtime access
   */
  struct a 
  {
    /**
     * \brief implement the required contract
     *
     * \return a foo string
     */
    virtual const char * foo() const noexcept { return "a - foo"; }
  };

  /**
   * \brief type that is stored inside a type sequence
   */
  struct b : public a
  {
    /**
     * \brief implement the required contract
     *
     * \return a foo string
     */
    const char * foo() const noexcept final { return "b - foo"; }
  };

  /**
   * \brief type that is stored inside a type sequence
   */
  struct c : public a
  {
    /**
     * \brief implement the required contract
     *
     * \return a foo string
     */
    const char * foo() const noexcept final { return "c - foo"; }
  };

  /**
   * \brief type that is stored inside a type sequence
   */
  struct d : public a
  {
    /**
     * \brief implement the required contract
     *
     * \return a foo string
     */
    const char * foo() const noexcept final { return "d - foo"; }
  };

  /**
   * \brief type that is stored inside a type sequence
   */
  struct e : public a
  {
    /**
     * \brief implement the required contract
     *
     * \return a foo string
     */
    const char * foo() const noexcept final { return "e - foo"; }
  };
  
  /**
   * \brief type that is stored inside a type sequence
   */
  struct f : public a
  {
    /**
     * \brief implement the required contract
     *
     * \return a foo string
     */
    const char * foo() const noexcept final { return "f - foo"; }
  };

  // playing with meta-predicates
  /**
   * \brief Predicate ready to be used on a type sequence
   *
   * \tparam T the currently explored type while iterating the type sequence
   * \tparam U parameters the predicate, used as operand to determine the
   * predicate value for the currently explored type of the type sequenec
   */
  template< class T, class U >
    struct the_type
    {
      /**
       * \brief If currently explored type is the same as U, exposes true,
       * otherwise, exposes false
       */
      static constexpr auto value = std::is_same< T, U >::value;
    };

  /**
   * \brief Predicate to be used on type sequence, veryfying if the currently
   * explored type is bigger than the specified one
   *
   * \tparam T the currently explored type in the type sequene
   * \tparam U parameter used in value evaluation
   */
  template< class T, class U >
    struct type_bigger_than
    {
      /**
       * \brief simple size comparison
       */
      static constexpr auto value = sizeof( T ) > sizeof( U );
    };

  /**
   * \brief Predicate to be used on integral sequence, looks for an odd number
   *
   * \tparam T the integral type used in the integral sequence
   * \tparam V the currently explored value while iterating the integral
   * sequence
   */
  template< class T, T V >
    struct odd_number
    {
      /**
       * \brief Odd number searching
       */
      static constexpr auto value = ( ( V % 2 ) != 0 );
    };

  /**
   * \brief Declaration of a predicate used on an integral sequence.
   * Specialized later
   *
   * \tparam T integral type used in the integral sequence
   * \tparam V currently explored value in the integral sequence
   * \tparam U a type that is specialized, used as predicate parameter
   */
  template< class T, T V, class U >
    struct the_number;

  /**
   * \brief Only valid version of the predicate, specialized for its parameter
   *
   * \tparam T integral type used in the integral sequence
   * \tparam V currently explored value in the integral sequence
   * \tparam U integral type used in an integral_constant template
   * \tparam W the value used in the integral_constant
   */
  template< class T, T V, class U, U W >
    struct the_number< T, V, std::integral_constant< U, W > >
    {
      /**
       * \brief Simple comparison
       */
      static constexpr auto value = ( V == W );
    };

  // static methods
  /**
   * \brief Test algorithms implementation using integral sequence provided by
   * warp and custom integral sequence as well
   */
  static void test_algorithms();

  /**
   * \brief Tests push_back on both type and integral sequences
   */
  static void test_push_back();

  /**
   * \brief Testing push_front features
   */
  static void test_push_front();

  /**
   * \brief pop_front testing on both integral and type sequence types
   */
  static void test_pop_front();

  /**
   * \brief pop_back testing on both integral and type sequence types
   */
  static void test_pop_back();

  /**
   * \brief Testing reverse algorithms
   */
  static void test_reverse();

  /**
   * \brief Groups all predicate aware algorithms
   */
  static void test_predicate_aware_algorithms();

  /**
   * \brief Tests the find_first algorithms for both type and integral
   * sequence
   */
  static void test_find_first();

  /**
   * \brief Tests the find_all algorithms for both type and integral
   * sequence
   */
  static void test_find_all();

  /**
   * \brief Test empty algorithms for both integral and type sequences
   */
  static void test_empty();

  /**
   * \brief Testing remove_first algorithms on both integral and type sequenes
   */
  static void test_remove_first();

  /**
   * \brief Testing remove_all algorithms on both integral and type sequenes
   */
  static void test_remove_all();

  /**
   * \brief Testing sorting feature for both integral and type sequence
   */
  static void test_sort();

  /**
   * \brief Tests partition algorithm for both integral and type sequence
   */
  static void test_partition();

  /**
   * \brief Tests unique algorithm on both type and integral sequences
   */
  static void test_unique();

  /**
   * \brief Testing generate ability
   */
  static void test_generate();

  /**
   * \brief Testind appending a char buffer inside an integral sequence
   */
  static void test_append_char_buffer();

  /**
   * \brief Testing the for_each_(type|value) feature
   */
  static void test_for_each();

  /**
   * \brief Testing runtime access feature for both integral and type
   * sequences. A runtime acces for sequences allow the user to iterate
   * through instances of integers and types inside a sequence that has been
   * constructed in compile time at runtime
   */
  static void test_runtime_access_for();

  /**
   * \brief Testing the merge feature for both integral and type sequence. The
   * merge feature will combine an A sequence with a B sequence giving an AB
   * sequence
   */
  static void test_merge();
};

/**
 * \brief Holds all that is necessary to test the spark module of warp.
 */
struct spark_tester
{
  /**
   * \brief A type exposing a constexpr initialized array of char buffer. This
   * is a workaround to the limit of recursive computation of constexpr provided
   * by major compilers. The user who wants to provide a large grammar
   * definition could use this trick
   */
  struct regular_grammar_strings_array
  {
    /**
     * \brief This array contains a bunch of constexpr strings. Each string is
     * less than 512 character long because of the limited capabilities of
     * constexpr operations on all of major compilers. These strings will be
     * merged together inside an integral sequence seamlessly within the
     * regular_grammar template
     */
    static constexpr const char *array[] =
    {
      R"grammar(
BEGIN_SYMBOLS;
  a=a;
END_SYMBOLS;
      )grammar",
      R"grammar(
BEGIN_GROUPS;
a=a;
END_GROUPS;
      )grammar"
    };
  };

  /**
   * \brief Exposes a regular grammar definition using a raw char buffer
   */
  struct regular_grammar_string
  {
    /**
     * \brief The regular grammar definition
     */
    static constexpr auto value =
      "BEGIN_SYMBOLS;"
      "a=a;"
      "END_SYMBOLS;"
      "BEGIN_GROUPS;"
      "a=a;"
      "END_GROUPS;";
  };

  /**
   * \brief Exposes a regular grammar definition using a raw char buffer
   * returning function
   */
  struct regular_grammar_string_function
  {
    /**
     * \brief Makes use of the regular grammar defined above
     *
     * \return a regular grammar definition
     */
    static constexpr auto value()
    { return regular_grammar_string::value; }
  };

  /**
   * \brief Defines an integral sequence containing a regular grammar definition
   */
  struct regular_grammar_sequence
  {
    /**
     * \brief The definition on its own
     */
    using sequence =
      warp::integral_sequence
      <
        const char,
        'B', 'E', 'G', 'I', 'N', '_', 'S', 'Y', 'M', 'B', 'O', 'L', 'S', ';',
        'b', '=', 'b', ';',
        'E', 'N', 'D', '_', 'S', 'Y', 'M', 'B', 'O', 'L', 'S', ';',
        'B', 'E', 'G', 'I', 'N', '_', 'G', 'R', 'O', 'U', 'P', 'S', ';',
        'b', '=', 'b', ';',
        'E', 'N', 'D', '_', 'G', 'R', 'O', 'U', 'P', 'S', ';'
      >;
  };

  /**
   * \brief This is a minimalistic regular grammar definition
   */
  struct minimal_interesting_regular_grammar
  {
    /**
     * \brief this grammar is similar to the '.*a*(b|cd?)+' regular expression.
     * It is small enough to not need to be split in an array
     */
    static constexpr auto value =
      "BEGIN_SYMBOLS;"
        "BASIC_SYMBOLS 'abcd;"
        "any = .;"
      "END_SYMBOLS;"

      "BEGIN_GROUPS;"
        ".* = any*;"
        "a* = a*;"
        "SYMBOLS_AS_GROUPS b c ';"
        "d? = d?;"
        "cd? = c.d?;"
        "b|cd? = b|cd?;"
        "(b|cd?)+ = `b|cd?`+;"
        "BINARY_CLOSURE_ON . '.*a*(b|cd?)+' ' .* a* (b|cd?)+ ';"
      "END_GROUPS;";
  };

  /**
   * \brief Test all features of spark
   */
  static void test_all();

  /**
   * \brief Test all feature related to regular grammar facilities
   */
  static void test_regular_grammar();

  /**
   * \brief This test the regular grammar type system, aka group and symbol
   * types
   */
  static void test_regular_grammar_type_system();

  /**
   * \brief Test the regular_grammar type instantiation
   */
  static void test_regular_grammar_instantiation();

  /**
   * \brief testing the transcription algorithm to use at compile time
   */
  static void test_compile_time_transcription();

  /**
   * \brief testing the transcription algorithm to use at run time
   */
  static void test_run_time_transcription();
};
}

#endif

// doxygen
/**
 * \file
 * \brief Header of a basic testing facility.
 */
