#ifndef   _WARP_SPARK_DETAIL_AUTOMATON_T_FUNCTION_ARGS_HPP_
#define   _WARP_SPARK_DETAIL_AUTOMATON_T_FUNCTION_ARGS_HPP_

namespace warp::spark::detail
{
  /**
   * \brief This is an epsilon transition argument that can be used in the
   * definition of an automaton's transition function. An epsilon transition is
   * somewhat a null predicate allowing to pass from one automaton state to
   * another when used in a transition function.
   */
  struct epsilon_transition {};
}

#endif // _WARP_SPARK_DETAIL_AUTOMATON_T_FUNCTION_ARGS_HPP_
