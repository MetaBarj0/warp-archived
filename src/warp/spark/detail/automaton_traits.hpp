#ifndef _WARP_SPARK_DETAIL_AUTOMATON_TRAITS_HPP_
#define _WARP_SPARK_DETAIL_AUTOMATON_TRAITS_HPP_

namespace warp::spark::detail
{
  template< class, class >
    struct automaton_traits
    {
      static constexpr bool is_automaton = false;
    };

  template
    <
      template< class... > class STATE_SEQUENCE,
      class STATE_1, class STATE_2, class... STATES,
      template< class... > class T_FUNCTION_SEQUENCE,
      class T_FUNCTION_1, class... T_FUNCTIONS
    >
    struct automaton_traits
    <
      STATE_SEQUENCE< STATE_1, STATE_2, STATES... >,
      T_FUNCTION_SEQUENCE< T_FUNCTION_1,  T_FUNCTIONS... >
    >
    {
    };
}

#endif // _WARP_SPARK_DETAIL_AUTOMATON_TRAITS_HPP_

// doxygen
/**
 * \file
 *
 * \brief This file contains the definition of traits for an automaton type
 */
