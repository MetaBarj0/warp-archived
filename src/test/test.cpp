#include "test.hpp"

#include <iostream>
#include <type_traits>
#include <iterator>

// auto_constant_tester
void test::auto_constant_tester::auto_type_signed_constant()
{
  std::cout << "  +----------------------------------+" << std::endl
            << "  | void auto_type_signed_constant() |" << std::endl
            << "  +----------------------------------+" << std::endl
            << "  This test will test the type inference feature" << std::endl
            << "  for integral signed values"
            << std::endl;

  using infered_signed_type_1 = warp::signed_auto_constant_t< -42 >;
  using infered_signed_type_2 = warp::signed_auto_constant_t< -999 >;
  using infered_signed_type_3 = warp::signed_auto_constant_t< -300 * 300 >;
  using infered_signed_type_4 = warp::signed_auto_constant_t< -5000000000 >;

  std::cout << std::boolalpha
            << "    -42 is signed char type? "
            << std::is_same< signed char, infered_signed_type_1 >::value
            << std::endl
            << "    -999 is signed short type? "
            << std::is_same< signed short, infered_signed_type_2 >::value
            << std::endl
            << "    -300 * 300 is signed int type? "
            << std::is_same< signed int, infered_signed_type_3 >::value
            << std::endl
            << "    -5000000000 is signed long type? "
            << std::is_same< signed long, infered_signed_type_4 >::value
            << std::endl
            << "    -5000000000 is signed long long type? "
            << std::is_same< signed long long, infered_signed_type_4 >::value
            << std::endl;
}

void test::auto_constant_tester::auto_type_unsigned_constant()
{
  std::cout << "  +------------------------------------+" << std::endl
            << "  | void auto_type_unsigned_constant() |" << std::endl
            << "  +------------------------------------+" << std::endl
            << "  This test will test the type inference feature" << std::endl
            << "  for integral unsigned values"
            << std::endl;

  using infered_signed_type_1 = warp::unsigned_auto_constant_t< 242 >;
  using infered_signed_type_2 = warp::unsigned_auto_constant_t< 999 >;
  using infered_signed_type_3 = warp::unsigned_auto_constant_t< 300 * 300 >;
  using infered_signed_type_4 = warp::unsigned_auto_constant_t< 5000000000 >;

  std::cout << std::boolalpha
            << "    242 is signed char type? "
            << std::is_same< unsigned char, infered_signed_type_1 >::value
            << std::endl
            << "    999 is signed short type? "
            << std::is_same< unsigned short, infered_signed_type_2 >::value
            << std::endl
            << "    300 * 300 is signed int type? "
            << std::is_same< unsigned int, infered_signed_type_3 >::value
            << std::endl
            << "    5000000000 is signed long type? "
            << std::is_same< unsigned long, infered_signed_type_4 >::value
            << std::endl
            << "    5000000000 is signed long long type? "
            << std::is_same< unsigned long long, infered_signed_type_4 >::value
            << std::endl;
}

// sequence_algorithms_test
void test::sequence_algorithms_tester::test_algorithms()
{
  std::cout << "  +------------------------+" << std::endl
            << "  | void test_algorithms() |" << std::endl
            << "  +------------------------+" << std::endl
            << "  testing meta sequences algorithms." << std::endl
            << std::endl;

  test_push_back();
  test_push_front();

  test_pop_front();
  test_pop_back();

  test_reverse();

  test_empty();

  test_predicate_aware_algorithms();

  test_unique();
  test_generate();

  test_append_char_buffer();

  test_for_each();

  test_runtime_access_for();

  test_merge();

  std::cout << "  +------------------------+" << std::endl
            << "  | void test_algorithms() |" << std::endl
            << "  +------------------------+" << std::endl
            << "  Sequences algorithms tested." << std::endl
            << std::endl;
}

void test::sequence_algorithms_tester::test_push_back()
{
  // works perfectly
  using sequence_0_t = warp::integral_sequence< signed char, 0 >;
  using sequence_1_t =
    warp::push_back_on_t< sequence_0_t, long long int, 42 >;

  ( void )sequence_1_t{};
 
  // works pretty well, but alert on overflow because of unsigned char sequence
  // in which we try to put a value too big
  // using sequence_2_t =
  //   warp::push_back_on_t< sequence_0_t, int, 422 >;

  // does not work on a non meta sequence type and give message only meta
  // sequence allowed
  // warp::push_back_on_t< int, int, 42 >{};
}

void test::sequence_algorithms_tester::test_push_front()
{
  // testing with integral sequence
  using sequence_0_t = warp::integral_sequence< signed char >;

  using sequence_1_t =
    warp::push_front_on_t< sequence_0_t, char, 42 >;
  ( void )sequence_1_t{};

  using sequence_2_t =
    warp::push_front_on_t< sequence_1_t, char, 41 >;
  ( void )sequence_2_t{};

  // testing with type sequence
  using sequence_3_t = warp::type_sequence<>;

  // works well
  using sequence_4_t = warp::push_front_on_t< sequence_3_t, char >;
  using sequence_5_t = warp::push_back_on_t< sequence_4_t, short >;
  using sequence_6_t = warp::push_front_on_t< sequence_5_t, void >;
  using sequence_7_t = warp::push_back_on_t< sequence_6_t, int >;

  ( void )sequence_7_t{};
}

void test::sequence_algorithms_tester::test_pop_front()
{
  using int_seq_0 = warp::integral_sequence< int, 41 >;
  using typ_seq_0 = warp::type_sequence< void >;

  // works fine, sequences are filled
  using int_seq_1 = warp::push_back_on_t< int_seq_0, int, 42 >;
  using typ_seq_1 = warp::push_back_on_t< typ_seq_0, char >;

  static_assert
    (
      ( 
        ( warp::pop_front_on< int_seq_1 >::value == 41 ) &&
          std::is_same
            <
              warp::integral_sequence< int, 42 >,
              warp::pop_front_on_s< int_seq_1 >
            >::value
      ),
      "Extremely weird..."
    );

  static_assert
    (
      (
        std::is_same
          <
            warp::type_sequence< char >,
            warp::pop_front_on_s< typ_seq_1 >
          >::value &&
          std::is_same
            <
              void,
              warp::pop_front_on_t< typ_seq_1 >
            >::value
      ),
      "Extremely weird..."
    );
}

void test::sequence_algorithms_tester::test_pop_back()
{
  using int_seq_0 = warp::integral_sequence< int, 41 >;
  using typ_seq_0 = warp::type_sequence< void >;

  // works fine, sequences are filled
  using int_seq_1 = warp::push_back_on_t< int_seq_0, int, 42 >;
  using typ_seq_1 = warp::push_back_on_t< typ_seq_0, char >;

  static_assert
    (
      ( 
        ( warp::pop_back_on< int_seq_1 >::value == 42 ) &&
          std::is_same
            <
              warp::integral_sequence< int, 41 >,
              warp::pop_back_on_s< int_seq_1 >
            >::value
      ),
      "Extremely weird..."
    );

  static_assert
    (
      (
        std::is_same
          <
            warp::type_sequence< void >,
            warp::pop_back_on_s< typ_seq_1 >
          >::value &&
          std::is_same
            <
              char,
              warp::pop_back_on_t< typ_seq_1 >
            >::value
      ),
      "Extremely weird..."
    );
}

void test::sequence_algorithms_tester::test_reverse()
{
  using empty_typ_seq = warp::type_sequence<>;
  using empty_int_seq = warp::integral_sequence< int >;

  using int_seq_0 = warp::integral_sequence< int, 1, 2, 3, 4 >;
  using typ_seq_0 = warp::type_sequence< void, char, short, int >;

  static_assert
    (
      std::is_same
        <
          empty_typ_seq,
          warp::reverse_on_t< empty_typ_seq >
        >::value,
      "Extremely weird..."
    );

  static_assert
    (
      std::is_same
        <
          empty_int_seq,
          warp::reverse_on_t< empty_int_seq >
        >::value,
      "Extremely weird..."
    );

  static_assert
    (
      std::is_same
        <
          warp::type_sequence< int, short, char, void >,
          warp::reverse_on_t< typ_seq_0 >
        >::value,
      "Extremely weird..."
    );

  static_assert
    (
      std::is_same
        <
          warp::integral_sequence< int, 4, 3, 2, 1 >,
          warp::reverse_on_t< int_seq_0 >
        >::value,
      "Extremely weird..."
    );
}

void test::sequence_algorithms_tester::test_predicate_aware_algorithms()
{
  test_find_first();
  test_find_all();

  test_remove_first();
  test_remove_all();

  test_sort();

  test_partition();
}

void test::sequence_algorithms_tester::test_find_first()
{
  // create a basic type sequence to find stuff into
  using typ_seq_0 =
    warp::type_sequence< short, int, long, long long, char, char, double >;

  // integral sequence created for the same purpose
  using int_seq_0 = warp::integral_sequence< int, 0, 1, 42, 2, 42, 3, 42 >;

  // search the first char type in the type sequence, giving another type
  // sequence beginning with the found type
  using typ_seq_1 =
    warp::find_first_in_type_sequence_t< typ_seq_0, the_type, char >;

  // look into the integral sequence for the first odd number, giving a new
  // integral sequence beginning with this number
  using int_seq_1 =
    warp::find_first_in_integral_sequence_t< int_seq_0, odd_number >;

  ( void )std::enable_if_t< true, typ_seq_1 >{};
  ( void )std::enable_if_t< true, int_seq_1 >{};
}

void test::sequence_algorithms_tester::test_find_all()
{
  // create a basic type sequence to find stuff into
  using typ_seq_0 =
    warp::type_sequence< short, int, long, long long, char, char, double >;

  // integral sequence created for the same purpose
  using int_seq_0 = warp::integral_sequence< int, 0, 1, 42, 2, 42, 3, 42 >;

  // search for all types bigger than a short
  using typ_seq_1 =
    warp::find_all_in_type_sequence_t< typ_seq_0, type_bigger_than, int >;

  // look into the integral sequence for all 42 numbers
  using int_seq_1 =
    warp::find_all_in_integral_sequence_t
    < int_seq_0, the_number, std::integral_constant< int, 42 > >;

  ( void )std::enable_if_t< true, int_seq_1 >{};
  ( void )std::enable_if_t< true, typ_seq_1 >{};
}

void test::sequence_algorithms_tester::test_empty()
{
  // declare both empty and non empty valid sequences
  using typ_seq_0 = warp::type_sequence<>;
  using typ_seq_1 = warp::type_sequence< void, char >;

  using int_seq_0 = warp::integral_sequence< int >;
  using int_seq_1 = warp::integral_sequence< int, 42 >;

  // test emptiness in all sequences
  ( void )std::enable_if_t
    < warp::is_empty_sequence< typ_seq_0 >::value, typ_seq_0 >{};
  ( void )std::enable_if_t
    < ! warp::is_empty_sequence< typ_seq_1 >::value, typ_seq_1 >{};

  ( void )std::enable_if_t
    < warp::is_empty_sequence< int_seq_0 >::value, int_seq_0 >{};
  ( void )std::enable_if_t
    < ! warp::is_empty_sequence< int_seq_1 >::value, int_seq_1 >{};
}

void test::sequence_algorithms_tester::test_remove_first()
{
  // create a basic type sequence to remove stuff into
  using typ_seq_0 =
    warp::type_sequence< short, int, long, long long, char, char, double >;

  // integral sequence created for the same purpose
  using int_seq_0 = warp::integral_sequence< int, 0, 1, 42, 2, 42, 3, 42 >;

  // remove the first char type in the type sequence, giving another type
  // sequence without the found type
  using typ_seq_1 =
    warp::remove_first_in_type_sequence_t< typ_seq_0, the_type, char >;

  // look into the integral sequence for the first odd number, giving a new
  // integral sequence without this number
  using int_seq_1 =
    warp::remove_first_in_integral_sequence_t< int_seq_0, odd_number >;

  ( void )std::enable_if_t< true, typ_seq_1 >{};
  ( void )std::enable_if_t< true, int_seq_1 >{};
}

void test::sequence_algorithms_tester::test_remove_all()
{
  // create a basic type sequence to remove stuff into
  using typ_seq_0 =
    warp::type_sequence< short, int, long, long long, char, char, double >;

  // integral sequence created for the same purpose
  using int_seq_0 = warp::integral_sequence< int, 0, 1, 42, 2, 42, 3, 42 >;

  // remove all types bigger than a int
  using typ_seq_1 =
    warp::remove_all_in_type_sequence_t< typ_seq_0, type_bigger_than, int >;

  // remove all 42 into the integral sequence
  using int_seq_1 =
    warp::remove_all_in_integral_sequence_t
    < int_seq_0, the_number, std::integral_constant< int, 42 > >;

  ( void )std::enable_if_t< true, int_seq_1 >{};
  ( void )std::enable_if_t< true, typ_seq_1 >{};
}

void test::sequence_algorithms_tester::test_sort()
{
  using typ_seq_0 =
    warp::type_sequence
    < short, char, long long, char, long double, double, wchar_t, int >;

  using typ_seq_1 =
    warp::sort_type_sequence_t< typ_seq_0, warp::type_less_size >;

  using int_seq_0 = warp::integral_sequence< int, 2,4,1,6,2,8,0,7,9,3,5 >;

  using int_seq_1 =
    warp::sort_integral_sequence_t< int_seq_0, warp::integral_less >;

  ( void )std::enable_if_t< true, typ_seq_1 >{};
  ( void )std::enable_if_t< true, int_seq_1 >{};
}

void test::sequence_algorithms_tester::test_partition()
{
  using typ_seq_0 = warp::type_sequence< void, char, int, float, double, long >;
  using int_seq_0 = warp::integral_sequence< int, 0,1,2,3,4,5,6,7,8,9 >;

  // standard type traits are usable, cool huh?
  using typ_seq_1 =
    warp::partition_type_sequence_t< typ_seq_0, std::is_integral >;
  using int_seq_1 =
    warp::partition_integral_sequence_t< int_seq_0, odd_number >;

  ( void )std::enable_if_t< true, typ_seq_1 >{};
  ( void )std::enable_if_t< true, int_seq_1 >{};
}

void test::sequence_algorithms_tester::test_unique()
{
  using typ_seq_0 = warp::type_sequence< char, int, int, char, float, char >;
  using int_seq_0 = warp::integral_sequence< int, 1,2,4,4,3,5,4,1,2,4,4,1,2,4 >;

  using typ_seq_1 = warp::unique_on_t< typ_seq_0 >;
  using int_seq_1 = warp::unique_on_t< int_seq_0 >;

  ( void )std::enable_if_t< true, typ_seq_1 >{};
  ( void )std::enable_if_t< true, int_seq_1 >{};
}

void test::sequence_algorithms_tester::test_generate()
{
  // generate the 0..49 sequence
  using int_seq_0 =
    warp::generate_unsigned_integral_sequence_t< 50, warp::indices >;

  // generate the sequence of 50 first triangular numbers. A triangular number
  // is one obtained by this formula : ( n * ( n + 1 ) ) / 2
  using int_seq_1 =
    warp::generate_unsigned_integral_sequence_t< 50, warp::triangular >;

  // generate the 30 first fibonacci's number
  using int_seq_2 =
    warp::generate_unsigned_integral_sequence_t< 30, warp::fibonacci >;

  // generate 30 first prime numbers, beware, this is greedy either in time and
  // in memory
  using int_seq_3 =
    warp::generate_unsigned_integral_sequence_t< 50, warp::prime >;

  ( void )std::enable_if_t< true, int_seq_0 >{};
  ( void )std::enable_if_t< true, int_seq_1 >{};
  ( void )std::enable_if_t< true, int_seq_2 >{};
  ( void )std::enable_if_t< true, int_seq_3 >{};
}

void test::sequence_algorithms_tester::test_append_char_buffer()
{
  using int_seq_0 = warp::integral_sequence< char >;
  struct hello { static constexpr auto value() { return "hello"; } };
  struct world { static constexpr auto value() { return " world!"; } };

  using int_seq_1 = warp::append_char_buffer_in_t< int_seq_0, hello >;
  using int_seq_2 = warp::append_char_buffer_in_t< int_seq_1, world >;

  ( void )std::enable_if_t< true, int_seq_2 >{};
}

void test::sequence_algorithms_tester::test_for_each()
{
  using int_seq_0 = warp::integral_sequence< int, 2, 3, 0, 1 >;
  using typ_seq_0 =
    warp::type_sequence< char, double, long long, char, int, long double >;

  static constexpr auto average =
    warp::for_each_value_in_t< int_seq_0, warp::average >::value();
  std::cout << average << std::endl;

  static constexpr auto sum =
    warp::for_each_value_in_t< int_seq_0, warp::sum >::value;

  static constexpr auto min =
    warp::for_each_value_in_t< int_seq_0, warp::min >::value;

  static constexpr auto max =
    warp::for_each_value_in_t< int_seq_0, warp::max >::value;

  static constexpr auto first_strictest_alignment_value =
    warp::for_each_type_in_t
    < typ_seq_0, warp::first_strictest_alignment >::value;

  using first_strictest_alignment_type =
    typename warp::for_each_type_in_t
    < typ_seq_0, warp::first_strictest_alignment >::type;

  static constexpr auto biggest_type_size =
    warp::for_each_type_in_t
    < typ_seq_0, warp::first_biggest_type >::value;

  using biggest_type =
    typename warp::for_each_type_in_t
    < typ_seq_0, warp::first_biggest_type >::type;

  static constexpr auto count_type =
    warp::for_each_type_in_t
    < typ_seq_0, warp::count_type >::value;

  static constexpr auto count_integral =
    warp::for_each_value_in_t
    < int_seq_0, warp::count_integral >::value;

  ( void )average;
  ( void )sum;
  ( void )min;
  ( void )max;
  ( void )first_strictest_alignment_value;
  ( void )std::enable_if_t< true, first_strictest_alignment_type >{};
  ( void )biggest_type_size;
  ( void )std::enable_if_t< true, biggest_type >{};
  ( void ) count_type;
  ( void ) count_integral;
}

void test::sequence_algorithms_tester::test_runtime_access_for()
{
  std::cout << "  +--------------------------------+" << std::endl
            << "  | void test_runtime_access_for() |" << std::endl
            << "  +--------------------------------+" << std::endl
            << std::endl;

  using int_seq_0 = warp::integral_sequence< int, 1,2,3,4,5 >;
  using arr_0 = warp::runtime_access_for_t< int_seq_0 >;

  for( auto n : arr_0{} )
    std::cout << n << ' ';

  std::cout << std::endl;

  using a = test::sequence_algorithms_tester::a;
  using b = test::sequence_algorithms_tester::b;
  using c = test::sequence_algorithms_tester::c;
  using d = test::sequence_algorithms_tester::d;
  using e = test::sequence_algorithms_tester::e;
  using f = test::sequence_algorithms_tester::f;

  using typ_seq_0 = warp::type_sequence< a, b, c, d, e, f >;
  using typ_seq_1 = warp::type_sequence< a >;
  using typ_seq_2 = warp::type_sequence<>;

  using con_0 = warp::runtime_access_for_t< typ_seq_0, a >;
  con_0 container_0;

  using con_1 = warp::runtime_access_for_t< typ_seq_1, a >;
  con_1 container_1;

  using con_2 = warp::runtime_access_for_t< typ_seq_2, a >;
  con_2 container_2;

  auto it_0 = container_0.begin();
  auto it_0_end = container_0.end();

  auto it_1 = container_1.begin();
  auto it_2 = container_2.begin();
  ( void )it_1; ( void )it_2;

  for( ; it_0 != it_0_end; ++it_0 )
  { std::cout << it_0->foo() << std::endl; }

  // testing brackets...random access
  for( auto i = std::distance( container_0.begin(), it_0 ) - 1; i >= 0; --i )
  { std::cout << container_0.begin()[ i ].foo() << std::endl; }

  // will cause a runtime error (dereferencing invalid iterator)
  // ++it_0;
  // std::cout << it_0->foo() << std::endl;
}

void test::sequence_algorithms_tester::test_merge()
{
  using typ_seq_0 = warp::type_sequence< char, bool >;
  using int_seq_0 = warp::integral_sequence< char, 'a', 'b', 'c' >;
  using typ_seq_1 = warp::type_sequence< short, int >;
  using int_seq_1 = warp::integral_sequence< char, 'd', 'e', 'f' >;

  using int_seq_2 = warp::merge_sequence_t< int_seq_0, int_seq_1 >;
  using typ_seq_2 = warp::merge_sequence_t< typ_seq_0, typ_seq_1 >;

  constexpr bool int_seq_ok =
    std::is_same
    < int_seq_2,
      warp::integral_sequence< char, 'a', 'b', 'c', 'd', 'e', 'f' > >::value;

  constexpr bool typ_seq_ok =
    std::is_same
    < typ_seq_2, warp::type_sequence< char, bool, short, int > >::value;

  ( void )std::enable_if_t< int_seq_ok, int_seq_2 >{};
  ( void )std::enable_if_t< typ_seq_ok, typ_seq_2 >{};
}

// spark tests
void test::spark_tester::test_all()
{
  std::cout << "  +------------------------+" << std::endl
            << "  | spark testing facility |" << std::endl
            << "  +------------------------+" << std::endl
            << std::endl;

  test_regular_grammar();
}

void test::spark_tester::test_regular_grammar()
{
  std::cout << "    +----------------------------------+" << std::endl
            << "    | Regular grammar facility testing |" << std::endl
            << "    +----------------------------------+" << std::endl
            << std::endl;

  test_regular_grammar_instantiation();
  test_regular_grammar_type_system();
  test_compile_time_transcription();
  test_run_time_transcription();
}

void test::spark_tester::test_regular_grammar_instantiation()
{
  std::cout << "      +---------------------------------------+" << std::endl
            << "      | Regular grammar instantiation testing |" << std::endl
            << "      +---------------------------------------+" << std::endl
            << std::endl;

  // testing with a array of little constexpr strings
  warp::spark::regular_grammar< regular_grammar_strings_array > g1;

  // testing with a little enough constexpr string
  warp::spark::regular_grammar< regular_grammar_string > g2;

  // testing with a little enough constexpr string returned by a function
  warp::spark::regular_grammar< regular_grammar_string_function > g3;

  // testing with an integral sequence
  warp::spark::regular_grammar
    < typename regular_grammar_sequence::sequence > g4;

  // testing a realistic minimalistic grammar
  warp::spark::regular_grammar< minimal_interesting_regular_grammar > g5;

  ( void )g1, ( void )g2, ( void )g3, ( void )g4, ( void )g5;

  // testing traits
  using rgt = warp::spark::regular_grammar_traits< decltype( g5 ) >;
  using rgd = typename rgt::regular_grammar_definition;
  using rgdt = typename warp::spark::regular_grammar_definition_traits< rgd >;
  using rgds = typename rgdt::regular_grammar_definition_sequence;

  static_assert( rgt::is_regular_grammar, "Uh oh..." );
  static_assert( rgdt::is_regular_grammar_definition, "Uh oh..." );
  static_assert( warp::meta_sequence_traits< rgds >::is_integral_sequence,
                 "Uh oh..." );
}

void test::spark_tester::test_regular_grammar_type_system()
{
  std::cout << "      +-----------------------------------+" << std::endl
            << "      | spark regular grammar type system |" << std::endl
            << "      | testing                           |" << std::endl
            << "      +-----------------------------------+" << std::endl
            << std::endl;

  // attempting to build a .*a*(b|cd?)+ template expression
  using s_any =
    warp::spark::symbol
    <
      warp::integral_sequence< char, 'a', 'n', 'y' >,
      warp::spark::symbol_types::any
    >;

  using s_a =
    warp::spark::symbol
    <
      warp::integral_sequence< char, 'a' >,
      warp::spark::symbol_types::inclusive,
      warp::integral_sequence< char, 'a' >
    >;

  using s_b =
    warp::spark::symbol
    <
      warp::integral_sequence< char, 'b' >,
      warp::spark::symbol_types::inclusive,
      warp::integral_sequence< char, 'b' >
    >;

  using s_c =
    warp::spark::symbol
    <
      warp::integral_sequence< char, 'c' >,
      warp::spark::symbol_types::inclusive,
      warp::integral_sequence< char, 'c' >
    >;

  using s_d =
    warp::spark::symbol
    <
      warp::integral_sequence< char, 'd' >,
      warp::spark::symbol_types::inclusive,
      warp::integral_sequence< char, 'd' >
    >;

  using g_any_star =
    warp::spark::group
    <
      warp::integral_sequence< char, '.', '*' >,
      warp::spark::group_unary_closures,
      warp::spark::group_unary_closures::zero_many,
      s_any
    >;

  using g_a_star =
    warp::spark::group
    <
      warp::integral_sequence< char, 'a', '*' >,
      warp::spark::group_unary_closures,
      warp::spark::group_unary_closures::zero_many,
      s_a
    >;

  using g_b =
    warp::spark::group
    <
      warp::integral_sequence< char, 'b' >,
      warp::spark::group_unary_closures,
      warp::spark::group_unary_closures::one_one,
      s_b
    >;

  using g_c =
    warp::spark::group
    <
      warp::integral_sequence< char, 'c' >,
      warp::spark::group_unary_closures,
      warp::spark::group_unary_closures::one_one,
      s_c
    >;

  using g_d_maybe =
    warp::spark::group
    <
      warp::integral_sequence< char, 'd', '?' >,
      warp::spark::group_unary_closures,
      warp::spark::group_unary_closures::zero_one,
      s_d
    >;

  using g_cd_maybe =
    warp::spark::group
    <
      warp::integral_sequence< char, 'c', 'd', '?' >,
      warp::spark::group_binary_closures,
      warp::spark::group_binary_closures::concatenation,
      g_c, g_d_maybe
    >;

  using g_b_or_cd_maybe =
    warp::spark::group
    <
      warp::integral_sequence< char, 'b', '|', 'c', 'd', '?' >,
      warp::spark::group_binary_closures,
      warp::spark::group_binary_closures::alternation,
      g_b, g_cd_maybe
    >;

  using g_a_star__b_or_cd_maybe =
    warp::spark::group
    <
      warp::integral_sequence
        < char, 'a', '*', '(', 'b', '|', 'c', 'd', '?', ')' >,
      warp::spark::group_binary_closures,
      warp::spark::group_binary_closures::concatenation,
      g_a_star, g_b_or_cd_maybe
    >;

  using group =
    warp::spark::group
    <
      warp::integral_sequence
        < char, '.', '*', 'a', '*', '(', 'b', '|', 'c', 'd', '?', ')' >,
      warp::spark::group_binary_closures,
      warp::spark::group_binary_closures::concatenation,
      g_any_star, g_a_star__b_or_cd_maybe
    >;

  // getting traits of the final group
  using group_traits = warp::spark::group_traits< group >;

  // using traits...
  static_assert( group_traits::is_group, "Uh oh..." );
}

void test::spark_tester::test_compile_time_transcription()
{
  std::cout << "      +------------------------------------------+" << std::endl
            << "      | spark compile time transcription testing |" << std::endl
            << "      +------------------------------------------+" << std::endl
            << std::endl;
}

void test::spark_tester::test_run_time_transcription()
{
  std::cout << "      +--------------------------------------+" << std::endl
            << "      | spark run time transcription testing |" << std::endl
            << "      +--------------------------------------+" << std::endl
            << std::endl;
}

// doxygen
/**
 * \file
 * \brief Contains the implementation of a very basic testing facility
 */
