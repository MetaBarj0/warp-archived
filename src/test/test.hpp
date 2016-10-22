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
# This is a documentation line. Each documentation line must be enclosed by a  #
# pair of ## characters. Documentation lines can be mixed together just like   #
# this : ##another infos# #last infos. These documentation lines are just for  #
# the user of the grammar and are not useful to create the parser. Moreover,   #
# documentation lines can be inserted everywhere in the grammar definition but #
# cannot be interlaced with other grammar entities like groups or symbols.     #
      )grammar",
      R"grammar(
# You can put any end line you want and where you want as well as white spaces #
# unless it breaks the syntax of the grammar definition                        #

# MANDATORY section of a regular grammar definition. This section will contain #
# all symbols that can be used in a group definition. Even the simplest        #
# grammar must define at least one symbol. Although it is not an optimal way   #
# to proceed, all symbols that are defined below are not mandatory used in     #
      )grammar",
      R"grammar(
# further groups. This section ends with a semicolon. The BEGIN_SYMBOLS        #
# section must be the first one defined entity container in the grammar        #
# definition.                                                                  #

BEGIN_SYMBOLS; # Note the semicolon at the end of the block name               #

# This is a really simple symbol representing the 'a' letter. Note the         #
# semicolon at the end of the definition. The semicolon is mandatory.          #
      )grammar",
      R"grammar(
  a = a;
# ^   ^                                                                        #
# |   |                                                                        #
# |   +- symbol value                                                          #
# +- symbol name, used in group definitions                                    #
      )grammar",
      R"grammar(
# Another way to define obvious symbols consists to use predefined macros :    #
  BASIC_SYMBOLS helowrd!; # ending by a semicolon too.                         #
# +------------ -------+                                                       #
# |                    |                                                       #
# +-> macro name       +-> symbols declared                                    #
# This statement as the same effect as :                                       #
      )grammar",
      R"grammar(
h=h; e=e; l=l; o=o; w=w; r=r; d=d; !=!;
# But is really much more handful                                              #
  BASIC_SYMBOLS [I'mafoseicln:;]; # semicolon ending the symbol declaration    #
# This symbol declaration use the BASIC_SYMBOLS macro and the square brace to  #
# allow the user to use meta character as raw character (see below). The only  #
# exception is the user cannot use the white space characters nor an '=' in a  #
      )grammar",
      R"grammar(
# BASIC_SYMBOLS macro.                                                         #
# To sumarize :                                                                #
# - BASIC_SYMBOLS defines symbols whose names are identical to their values.   #
# - symbols defined are only inclusive.                                        #
# - All meta character used are automatically escaped except but the ';' and   #
#   '[' if specified at first position                                         #
      )grammar",
      R"grammar(
# - characters used in a BASIC_SYMBOLS must follow this pattern :              #
#   [^= \n\r\t\v]+ that is the same rule for unique symbol definition.         #
# This is a really simple symbol representing the 'b' letter.                  #
  b = b;

# A single letter can also be defined inside a pair of braces. A pair of brace #
# nullifies all special meaning of meta character. Meta-characters for symbols #
# are :                                                                        #
      )grammar",
      R"grammar(
# white spaces : are completely ignored                                        #
# '.' for the any-character concept                                            #
# '-' for the exclusive symbol definition (all but that is written after       #
#     the minus sign)                                                          #
# braces : a full pair of braces can be used to nullify any meta               #
#          characters, semicolon included                                      #
      )grammar",
      R"grammar(
# ';' for the end of statement meaning.                                        #
c = [c]; # this is the same as c = c;                                          #

# If you want to recognize a white space define its representation inside a    #
# brace pair                                                                   #
  white_space = [ ];
  horizontal_tab = [	];
      )grammar",
      R"grammar(
# White spaces can only be defined using a single letter symbol.               #
# Recognize the semicolon character                                            #
  semicolon = [;];

# The same as above but for the d letter                                       #
d = [d]; # same as  d = d;                                                     #
      )grammar",
      R"grammar(
# The any letter concept. Must be specified nude, aka not within a brace pair. #
# Indeed, a brace pair nullify the any meaning of '.'                          #
  any = .;

# The '.' character, losing it special meaning inside a brace pair.            #
  dot = [.];
      )grammar",
      R"grammar(
# The '-' character, losing it special meaning inside a brace pair.            #
  minus = [-];

# The '-' character, specified alone, doesn't have its special meaning         #
  minus = -;
      )grammar",
      R"grammar(
# This symbol is an exclusive symbol. It means that the letter sequence        #
# defined after the affectation sign represent all the letter we don't want to #
# be recognized by the symbol. An exclusive symbol is prefixed by the '-' meta #
# character. The '-' must be specified at the first position of the right      #
# operand of the symbol and out of a brace pair otherwise, it loses it special #
# meanings and is considered as a raw '-' character like any others.           #
      )grammar",
      R"grammar(
# IMPORTANT NOTE : only exclusive symbol can define sequence of letter.        #
# Inclusive symbol (not prefixed by '-' can have only one letter or 'any'      #
# assignation. Consider to use BASIC_SYMBOLS macro to define several inclusive #
# symbols at once. By the way, it is impossible to use the special meaning of  #
# '.' in an exclusive symbol definition.                                       #
  all_but_dot = -.;
      )grammar",
      R"grammar(
# all but digit characters. note the '-' at the start of the letter sequence   #
# meaning we consider all characters are valid but digits.                     #
  all_but_digit = -0123456789;
      )grammar",
      R"grammar(
# The same rule as above, just applied to lowercase letters. Note that the     #
# sequence can also be defined inside a brace pair though it is absolutely not #
# necessary because all character  in the brace pair don't have any special    #
# meaning                                                                      #
  all_but_lowercase_letters = -[abcdefghijklmnopqrstuvwxyz];
      )grammar",
      R"grammar(
# If a brace character is specified alone, it loses its special meaning        #
  left_brace = [;
  right_brace = ];
# This behavior is similar to the '-' character. Same behavior when braces are #
# specified in reverse order within a BASIC_SYMBOLS macros :                   #
BASIC_SYMBOLS ][;
      )grammar",
      R"grammar(
# These symbol definitions are identical and consist to recognize any input    #
# that does not match with any symbol meta-characters. The first 2 don't       #
# exclude the semicolon meta-character                                         #

# Note how braces are written here                                             #
  all_but_meta_1 = -][.-;
      )grammar",
      R"grammar(
# all_but_meta_1 = -[].-;  is an error as brace content is not considered      #
# valid (not finished)                                                         #

# OK, all lose their special meaning                                           #
  all_but_meta_2 = --[.];
# Braces are not meta here because not just right after the '-'                #
      )grammar",
      R"grammar(
# OK as the right brace is right after the opening one that is meta. The       #
# semicolon is handled here and the first left brace is finished before ';'    #
  all_but_meta_3 = -[]-.;[];
      )grammar",
      R"grammar(
# To summarize the symbol section definition :                                 #
# - The couple 'BEGIN_SYMBOLS;/END_SYMBOLS;' is mandatory in the grammar       #
#   definition string and must be the first container defined in the grammar.  #
      )grammar",
      R"grammar(
# - multiple inclusive symbols can be defined using the BASIC_SYMBOLS macro    #
#   - each symbol defined with this macro has its name identical to its value  #
#   - valid symbols that can be used follow the same constraint as the symbol  #
#     name rule : single word [^= \n\r\t\v]+                                   #
      )grammar",
      R"grammar(
# - Each unique symbol definition is built with 3 parts :                      #
#   - A name declaration (single word, [^= \n\r\t\v]+)                         #
#   - An affectation sign '=' prefixed and/or postfixed by an arbitrary        #
#     number of whitespace characters                                          #
#   - The definition (see examples above)                                      #
# - Each symbol definition must be terminated by a semicolon character.        #
      )grammar",
      R"grammar(
# - A symbol definition can be :                                               #
#   - Inclusive (uses only one letter that may be inside a brace pair to       #
#     nullify some meta meaning)                                               #
#   - Exclusive (uses a sequence of one or more letter prefixed by '-'         #
#     character. The sequence letter may be contained inside a brace pair      #
# - A brace pair usage nullifies all meaning of meta character placed inside   #
      )grammar",
      R"grammar(
#   it both for inclusive and exclusive symbol.                                #
# - Meta characters are applicable in the right hand side of the symbol        #
#   definition and are from the following list :                               #
#    - ';' end a symbol definition                                             #
#    - '.' means 'any character'                                               #
#    - '-' specified at the begining of a letter sequence, means that          #
      )grammar",
      R"grammar(
#      the symbol recognize all letter but those specified.                    #
#    - '[]' The brace pair is not a single meta character but have its         #
#      own meaning, nullifying any special meaning of meta character, allowing #
#      them to be recognized as standard characters by the symbol. See above   #
#      for examples.                                                           #
# - Though it is not optimal, it is possible to define symbols that are never  #
      )grammar",
      R"grammar(
#   used further in any group.                                                 #
END_SYMBOLS; # Terminates the symbol definitions                               #
      )grammar",
      R"grammar(
# MANDATORY section of a regular grammar definition. Contains at least one     #
# group that describe the grammar able to recognize a regular language. A      #
# group works ONLY with defined symbols in 'BEGIN_SYMBOLS;/END_SYMBOLS;'       #
# section and groups that are PREVIOUSLY defined.                              #
#                             ----------                                       #
# The name resolution to know if an entity is a symbol or a group takes        #
      )grammar",
      R"grammar(
# place in this order :                                                        #
# - First, look inside previsouly defined group. If one is found, use it.      #
# - Last, if not any group is found, take a look in symbols.                   #
# If more than one group names are resolved (several groups have the same      #
# name) an error will occur. There is some sort of ODR in the grammar          #
# definition. Same rule for symbols resolved.                                  #
      )grammar",
      R"grammar(
# The grammar recognize any language that is parsed by the LAST group defined  #
#                                                          ----                #
# in this section. This section must contain at least one group definition     #
      )grammar",
      R"grammar(
  BEGIN_GROUPS;
# A simple group definition, using a previously defined symbol and applying an #
# unary closure (Kleen's star) on it The '*' closure is available for both     #
# symbol and group values                                                      #
  a* = a*;
# First a group name is created, then, a symbol is resolved, finally a closure #
      )grammar",
      R"grammar(
# is applied on the symbol.                                                    #
# This group is even simpler than the previously defined one. It uses the b    #
# symbol defined above as is :                                                 #
  b = b;
      )grammar",
      R"grammar(
# You can enclose the symbol name in a brace pair. It is usefull if the the    #
# symbol name contains some meta character relative to right hand side group   #
# definition (closure characters and semicolon) though not absolutely          #
# necessary in this case (see above).                                          #
  c = [c];
      )grammar",
      R"grammar(
# This group uses the 'd' symbol and applies on it the '?' closure that means  #
# 'recognize zero or one occurence of the symbol' NOTE that you can put any    #
# number of white space characters between the symbol and the closure          #
# meta-character.  The '?' closure is available for both symbol and group      #
# values                                                                       #
  d? = d ?;
      )grammar",
      R"grammar(
# This group uses previously defined group that used symbols and unary         #
# closures (quantifiers). The closure used here is the concatenation and the   #
# only valid operands are previously defined group.  Consequently, the order   #
# of group definition matters. The '.' closure is only valid for use with      #
# group values, not symbol, thus, if the 'c' group weren't defined, this       #
# definition would be invalid.                                                 #
      )grammar",
      R"grammar(
  cd? = c . d?;
# Uses the alternation closure with previsouly defined groups The '|' closure  #
# is only valid for use with group values, not symbol Group value is read from #
# left to right, no brace pair needed on cd?                                   #
  b|cd? = b | cd?;
      )grammar",
      R"grammar(
# This group use an unary closure on another group. The usage of the brace     #
# pair is absolutely mandatory because b is a previsouly defined group as well #
# as b|cd?.  If 'b' is resolved, '|' will be considered as the binary closure  #
# instead as a part of a group name, leading 'cd?+' to be seen as a group name #
# that doesn't exist.                                                          #
  (b|cd?)+ = [b|cd?]+;
      )grammar",
      R"grammar(
# This is the last group defined, so the final regular grammar definition.     #
# Group value is read from left to right, brace pair necessary around a* to    #
# prevent error due to remaining characters after unary closure definition.    #
  a*(b|cd?)+ = [a*] . (b|cd?)+;
      )grammar",
      R"grammar(
# Summary of group definition and composition :                                #
# - The couple 'BEGIN_GROUPS;/END_GROUPS;' is mandatory in the grammar         #
#   definition string and must be define AFTER symbol definitions              #
# - Each group definition is built with 3 parts :                              #
#   - A name declaration (single word, [^= \n\r\t\v]+)                         #
      )grammar",
      R"grammar(
#   - An affectation sign '='                                                  #
#   - The definition (see examples above)                                      #
# - Each group definition must be terminated by a semicolon character.         #
# - At least one group must exist inside the section                           #
# - The last group defined decides of the languages recognized by the grammar. #
# - Contrary on symbols definitions, group definitions rely on                 #
      )grammar",
      R"grammar(
#   previously defined entities (either symbol or groups). Trying to refer to  #
#   an unexisting symbol or group within a group definition is an error.       #
# - The brace pair is also available in group definition. It may be useful     #
#   to express clearly the right hand side part of a group definition; it is   #
#   mandatory when the right hand side part of the group definition contains   #
#   group's names made with meta-characters.                                   #
      )grammar",
      R"grammar(
# - Meta characters for groups  are :                                          #
#   - ';' : this one has the same meaning for groups and symbols. It           #
#           terminates the group definition.                                   #
#   - '[]' : the brace pair have the same purpose for symbols and groups       #
#            definitions. It could be used for the sake of clarity or to       #
#            disambiguate group's names containing some meta characters.       #
      )grammar",
      R"grammar(
#   - '?' : means 0 to 1 quantifier. It is an unary closure that can be used   #
#           either on a previously defined symbol OR on a previously defined   #
#           group.                                                             #
#   - '*' : means 0 to n quantifier. It is an unary closure that can be used   #
#           either on a previously defined symbol OR on a previously defined   #
#           group.                                                             #
      )grammar",
      R"grammar(
#   - '+' : means 0 to n quantifier. It is an unary closure that can be used   #
#           either on a previously defined symbol OR on a previously defined   #
#           group.                                                             #
#   - '.' : this is the concatenation binary closure. Contrary on unary        #
#           closures, binary closures can only be used on 2 group operands.    #
#   - '|' : this is the alternation binary closure. Contrary on unary          #
      )grammar",
      R"grammar(
#           closures, binary closures can only be used on 2 group operands.    #
# - The last group that is defined rules the entire grammar and defines which  #
#   languages are recognized by this one.                                      #
  END_GROUPS;
      )grammar",
      R"grammar(
# That's it for the grammar definition string. Here, you can see that some     #
# symbols are unused. It is not an error, and they can be safely deleted.      #
# They won't be included in the compiled grammar, just ignored.                #

# Below is an example one of the simplest regular grammar definition you can   #
# do :                                                                         #
      )grammar",
      R"grammar(
# BEGIN_SYMBOLS;                                                               #
#   a = a;                                                                     #
# END_SYMBOLS;                                                                 #

# BEGIN_GROUPS;                                                                #
#   a = a;                                                                     #
# END_GROUPS;                                                                  #
      )grammar",
      R"grammar(
# That's it! This regular grammar only recognize the 'a' letter.               #
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
   * \brief Test all features of spark
   */
  static void test_all();

  /**
   * \brief Test all feature related to regular grammar facilities
   */
  static void test_regular_grammar();

  /**
   * \brief Test the regular_grammar type instantiation
   */
  static void test_regular_grammar_instantiation();
};
}

#endif

// doxygen
/**
 * \file
 * \brief Header of a basic testing facility.
 */
