#ifndef _WARP_REGULAR_GRAMMAR_HPP_
#define _WARP_REGULAR_GRAMMAR_HPP_

#include "../core/types.hpp"
#include "regular_grammar_traits.hpp"

#include <type_traits>

/**
 * \brief Somme hidden stuff here
 */
namespace
{
struct invalid_regular_grammar_definition :
  warp::empty_type {};

template< class T >
  struct test_regular_grammar_definition :
  std::enable_if_t
  <
    warp::spark::regular_grammar_definition_traits< T >::is_valid,
    invalid_regular_grammar_definition
  >
  {};

template< class T >
  class regular_grammar_impl :
  test_regular_grammar_definition< T >
  {
    using regular_grammar_definition =
      typename warp::spark::regular_grammar_definition_traits< T >::
      sequence_type;
  };
}

namespace warp::spark
{
template< class T >
  class regular_grammar :
  regular_grammar_impl< T >
  {
  };
} // namespace warp::spark

#endif // _WARP_REGULAR_GRAMMAR_HPP_
