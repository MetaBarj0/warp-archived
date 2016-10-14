#include "test.hpp"

/**
 * \brief The test program entry point
 */
int main( int, char *[] )
{
  // (un)signed_auto_constant tests
  test::auto_constant_tester::auto_type_signed_constant();
  test::auto_constant_tester::auto_type_unsigned_constant();

  // meta sequences tests
  test::sequence_algorithms_tester::test_algorithms();

  // spark testing
  test::spark_tester::test_all();
}

// doxygen
/**
 * \file
 * \brief Main program. Used to test warp capabilities.  Mainly rely on exposed
 * tests.
 */
