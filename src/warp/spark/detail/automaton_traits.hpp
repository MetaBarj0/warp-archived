#ifndef _WARP_SPARK_DETAIL_AUTOMATON_TRAITS_HPP_
#define _WARP_SPARK_DETAIL_AUTOMATON_TRAITS_HPP_

#include "../../core/types.hpp"
#include "../../sequences/sequence_traits.hpp"
#include "../../sequences/algorithm.hpp"
#include "automaton_state_traits.hpp"
#include "automaton_t_function_traits.hpp"

#include <type_traits>

namespace warp::spark::detail
{
  /**
   * \brief Meta functor designed to work on a type sequence containing
   * automaton states. For each state explored, two internal counter may be
   * updated. This functor exposes a counter for initial and final states.
   * Unspecialized version used as declaration.
   */
  template< class, class... >
    struct count_required_states;

  /**
   * \brief Specialization working for the first element explored in the
   * sequence, initializes counters to zero.
   *
   * \tparam STATE the currently explored type of the sequence, assumed to be an
   * automaton state
   */
  template< class STATE >
    struct count_required_states< STATE >
    {
      /**
       * \brief Counter for initial state. A valid automaton has only one
       * initial state
       */
      static constexpr size_t initial_state_count = 0;

      /**
       * \brief Counter for final states. A valid automaton has at least one
       * final state.
       */
      static constexpr size_t final_state_count = 0;

      /**
       * \brief Type exposed for the next computation occurring on the next
       * element of the sequence. A check is made to ensure STATE is a valid
       * state. If not, a specific specialization of this functor is used to
       * break the recursion, and discard the sequence
       */
      using next =
        std::conditional_t
        <
          automaton_state_traits< STATE >::is_automaton_state,
          // valid automaton state, continue recursion
          count_required_states
            <
              ignore,
              std::integral_constant< size_t, initial_state_count >,
              std::integral_constant< size_t, final_state_count >
            >,
          // not an automaton state, break by invoking specific specialization
          count_required_states
            <
              ignore,
              std::integral_constant< size_t, 2 >,
              std::integral_constant< size_t, 0 >
            >
        >;
    };

  /**
   * \brief Specialization used for all elements in a state sequence but the
   * first. All element in the sequence explored so far are valid automaton
   * states.
   *
   * \tparam STATE the currently explored type in the type sequence
   * \tparam INITIAL value of the initial state counter
   * \tparam FINAL value of the final state counter
   */
  template< class STATE, std::size_t INITIAL, std::size_t FINAL >
    struct count_required_states
    <
      STATE,
      std::integral_constant< std::size_t, INITIAL >,
      std::integral_constant< std::size_t, FINAL >
    >
    {
      /**
       * \brief initializes the initial counter regarding template parameters
       */
      static constexpr auto initial_state_count = INITIAL;

      /**
       * \brief initializes the final counter regarding template parameters
       */
      static constexpr auto final_state_count = FINAL;

      /**
       * \brief So far, the exploration shown the sequence contain only valid
       * automaton states.
       */
      using next =
        std::conditional_t
        <
          automaton_state_traits< STATE >::is_automaton_state,
          // automaton state explored, going ahead, incrementing counters if
          // necessary
          count_required_states
            <
              ignore,
              std::integral_constant
                <
                  std::size_t,
                  INITIAL +
                    automaton_state_traits< STATE >::is_initial ? 1 : 0
                >,
              std::integral_constant
                <
                  std::size_t,
                  FINAL +
                    automaton_state_traits< STATE >::is_final ? 1 : 0
                >
            >,
          // type explored is not an automaton state, using the specific
          // specialization breaking the recursion
          count_required_states
            <
              ignore,
              std::integral_constant< size_t, 2 >,
              std::integral_constant< size_t, 0 >
            >
        >;
    };

  /**
   * \brief Specific specialization breaking the exploration. Indeed, as soon as
   * two initial states have been discovered, the automaton state sequence is
   * invalid and it is not necessary to explore anymore
   *
   * \tparam STATE warp::ignore
   * \tparam FINAL current value of the final state counter. Doesn't matter
   * here, the sequence will be discarded
   */
  template< class STATE, std::size_t FINAL >
    struct count_required_states
    <
      STATE,
      std::integral_constant< std::size_t, 2 >,
      std::integral_constant< std::size_t, FINAL >
    >
    {
      /**
       * \brief Two initial state give an invalid automaton
       */
      static constexpr auto initial_state_count = 2;

      /**
       * \brief If an automaton does not have at least one final state, it's
       * invalid
       */
      static constexpr auto final_state_count = 0;

      /**
       * \brief The stop type, exposing the result of an invalid automaton state
       * sequence iteration
       */
      using stop =
        count_required_states
        <
          ignore,
          // two initial states
          std::integral_constant< std::size_t, 2 >,
          // zero final state
          std::integral_constant< std::size_t, 0 >
        >;
    };

  /**
   * \brief Meta predicate designed to be used on a type sequence, looking for a
   * non automaton transition function type.
   *
   * \tparam T A type inside a type sequence
   */
  template< class T >
    struct not_an_automaton_t_function
    {
      /**
       * \brief Using the currently explored type in a automaton transition
       * function traits class
       */
      static constexpr auto value =
        ! automaton_t_function_traits< T >::is_automaton_t_function;
    };

  /**
   * \brief Internal trait designed to work with automaton state sequence types.
   * This unspecialized version works with a type that is not even a type
   * sequence.
   */
  template< class, class = warp::sfinae_type_t<> >
    struct state_sequence_traits
    {
      /**
       * \brief Not an automaton state type sequence
       */
      static constexpr bool is_state_sequence = false;
    };

  /**
   * \brief Specialization working with a type that is a type sequence. It
   * remains however to check the content of the sequence as a valid automaton
   * state sequence must contains at least two states amongst it must be an
   * initial state and at least one final state.
   */
  template< class T >
    struct state_sequence_traits
    <
      T,
      // ok, type sequence evaluated
      sfinae_type_t
        < std::enable_if_t< meta_sequence_traits< T >::is_type_sequence > >
    >
    {
    private :
      /**
       * \brief Not an exposed trait but, contains information about how many
       * initial and final states there is in the sequence
       */
      using required_state_counter =
        for_each_type_in_t< T, count_required_states >;

    public :
      /**
       * \brief Trait indicating the state sequence is valid regarding the count
       * of initial and final states in the sequence
       */
      static constexpr auto is_state_sequence =
      ( required_state_counter::initial_state_count == 1 ) &&
      ( required_state_counter::final_state_count > 0 );
    };

  /**
   * \brief Internal traits designed to work with transition function sequence
   * type. This unspecialized version is used when the specified type is all but
   * a transition function sequence
   */
  template< class, class = sfinae_type_t<> >
    struct t_function_sequence_traits
    {
      /**
       * \brief Not a transition function sequence
       */
      static constexpr bool is_t_function_sequence = false;
    };

  /**
   * \brief Specialization used when the specified type is a valid type
   * sequence. However, the content of the sequence has to be checked.
   *
   * \tparam T a type sequence supposed to contain transtion function types
   */
  template< class T >
    struct t_function_sequence_traits
    <
      T,
      // ok, type sequence
      sfinae_type_t
        < std::enable_if_t< meta_sequence_traits< T >::is_type_sequence > >
    >
    {
    private :
      /**
       * \brief Not a trait, but looks for a type that isn't a transition
       * function. If the sequence contains one element matching this predicate,
       * the complete sequence is discarded and seen as invalid sequence of
       * transition functions
       */
      using not_a_t_function_type =
        find_first_in_type_sequence_t< T, not_an_automaton_t_function >;

    public :
      /**
       * \brief This trait depends of the type found when looking for a non
       * transition function. If undefined_type, the sequence is considered as
       * valid, otherwise, not.
       */
      static constexpr auto is_t_function_sequence =
        std::is_same< undefined_type, not_a_t_function_type >::value;
    };

  /**
   * \brief Provides traits for an assumed automaton type. This unspecialized
   * version works with types that are not valid automaton types.
   */
  template< class >
    struct automaton_traits
    {
      /**
       * \brief Specified type is not an automaton type
       */
      static constexpr bool is_automaton = false;
    };

  /**
   * \brief Specialization dealing with a type whose template signature is valid
   * regarding the definition of an automaton type
   *
   * \tparam AUTOMATON template signature for an automaton
   * \tparam STATE_SEQUENCE a type sequence representing the states of the
   * specified assumed automaton
   * \tparam STATE_1 the first state of the state sequence
   * \tparam STATE_2 the second state of the state sequence (a valid automaton
   * contains at least 2 states)
   * \tparam STATES type pack representing remaining states of the sequence
   * \tparam T_FUNCTION_SEQUENCE a sequence of transition function associated
   * with the specified assumed automaton type
   * \tparam T_FUNCTION_1 the first transition function of the specified
   * sequence (a valid automaton as at least one transition function)
   * \tparam T_FUNCTIONS reamining transition function in the sequence
   */
  template
    <
      template< class, class > class AUTOMATON,
      template< class... > class STATE_SEQUENCE,
      class STATE_1, class STATE_2, class... STATES,
      template< class... > class T_FUNCTION_SEQUENCE,
      class T_FUNCTION_1, class... T_FUNCTIONS
    >
    struct automaton_traits
    <
      AUTOMATON
        <
          STATE_SEQUENCE< STATE_1, STATE_2, STATES... >,
          T_FUNCTION_SEQUENCE< T_FUNCTION_1,  T_FUNCTIONS... >
        >
    >
    {
      /**
       * \brief Validity of an automaton depends on validity of the state
       * sequence and the transition function sequence
       */
      static constexpr auto is_automaton =
        state_sequence_traits
          < STATE_SEQUENCE< STATE_1, STATE_2, STATES... > >::
          is_state_sequence &&
        t_function_sequence_traits
          < T_FUNCTION_SEQUENCE< T_FUNCTION_1, T_FUNCTIONS... > >::
          is_t_function_sequence;

    };
}

#endif // _WARP_SPARK_DETAIL_AUTOMATON_TRAITS_HPP_

// doxygen
/**
 * \file
 *
 * \brief This file contains the definition of traits for an automaton type
 */
