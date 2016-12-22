#ifndef _WARP_SEQUENCES_ALGORITHM_HPP_
#define _WARP_SEQUENCES_ALGORITHM_HPP_

#include "sequence_traits.hpp"

#include <utility>
#include <array>
#include <iterator>

// hidden private stuff, contains empty types used in SFINAE
namespace
{
  template< class B, class... TS >
    struct test_base_specified_for :
    warp::empty_type {};

  template< class B, class T, class... TS >
    struct test_base_specified_for< B, T, TS... > :
    test_base_specified_for< B, TS... >
    {
      static_assert
        (
          std::is_base_of< B, T >::value,
          "Invalid type specified as base of type inside the type sequence"
        );
    };

  template< class B, class T >
    struct test_base_specified_for< B, T >
    {
      static_assert
        (
          std::is_base_of< B, T >::value,
          "Invalid type specified as base of type inside the type sequence"
        );
    };

  /**
   * \brief Hidden implementation of the push back feature for both integral
   * and type sequence
   *
   * \tparam T the sequence type
   * \tparam U integral type of pushed value for integral sequence, type to push
   * for the type sequence
   * \tparam V the value to push in case of use with an integral sequence
   */
  template< class T, class U, U... V >
    struct push_back_on_impl
    {
      static_assert( warp::meta_sequence_traits< T >::is_meta_sequence,
                     "Invalid type used. Onlye meta-sequences (type or "
                     "integral sequences) are allowed." );
    };

  /**
   * \brief Specialization working on an integral sequence.
   *
   * \tparam S an integral sequence template that must be validated by
   * test_integral_sequence_traits.
   * \tparam U integral type of the integral sequence
   * \tparam VS value pack contained in the integral sequence
   * \tparam X integral type of the value to push
   * \tparam V the value to push
   */
  template< template< class T, T... > class S, class U, U... VS, class X, X V >
    struct push_back_on_impl< S< U, VS... >, X, V >
    {
      static_assert( warp::meta_sequence_traits< S< U, VS... > >::
                       is_integral_sequence,
                     "Invalid type used. Only integral sequence types are "
                     "allowed." );
        
      /**
       * \brief Exposes a sequence with the value at the end
       */
      using type = S< U, VS..., V >;
    };

  /**
   * \brief Specialization working with a type sequence
   *
   * \tparam S the type sequence validated by test_type_sequence_traits.
   * \tparam TS type pack contained in the type sequence
   * \tparam T the type to push
   */
  template< template< class... > class S, class...TS, class T >
    struct push_back_on_impl< S< TS... >, T >
    {
      static_assert( warp::meta_sequence_traits< S< TS... > >::is_type_sequence,
                     "Invalid type used. Only type sequence types are "
                     "allowed." );
        
      /**
       * \brief Exposes a type sequence with the new type at the end
       */
      using type = S< TS..., T >;
    };

  /**
   * \brief Hidden implementation of the push front feature for both integral
   * and type sequence
   *
   * \tparam T the sequence type
   * \tparam U integral type of pushed value for integral sequence, type to push
   * for the type sequence
   * \tparam V the value to push in case of use with an integral sequence
   */
  template< class T, class U, U... V >
    struct push_front_on_impl
    {
      static_assert( warp::meta_sequence_traits< T >::is_meta_sequence,
                     "Invalid type used. Onlye meta-sequences (type or "
                     "integral sequences) are allowed." );
    };

  /**
   * \brief Specialization working on an integral sequence.
   *
   * \tparam S an integral sequence template that must be validated by
   * test_integral_sequence_traits.
   * \tparam U integral type of the integral sequence
   * \tparam VS value pack contained in the integral sequence
   * \tparam X integral type of the value to push
   * \tparam V the value to push
   */
  template< template< class T, T... > class S, class U, U... VS, class X, X V >
    struct push_front_on_impl< S< U, VS... >, X, V >
    {
      static_assert( warp::meta_sequence_traits< S< U, VS... > >::
                       is_integral_sequence,
                     "Invalid type used. Only integral sequence types are "
                     "allowed." );

      /**
       * \brief Exposes a sequence with the value at the beginning
       */
      using type = S< U, V, VS... >;
    };

  /**
   * \brief Specialization working with a type sequence
   *
   * \tparam S the type sequence validated by test_type_sequence_traits.
   * \tparam TS type pack contained in the type sequence
   * \tparam T the type to push
   */
  template< template< class... > class S, class...TS, class T >
    struct push_front_on_impl< S< TS... >, T >
    {
      static_assert( warp::meta_sequence_traits< S< TS... > >::is_type_sequence,
                     "Invalid type used. Only type sequence types are "
                     "allowed." );

      /**
       * \brief Exposes a type sequence with the new type at the beginning
       */
      using type = S< T, TS... >;
    };

  /**
   * \brief General form of the algorithm. Serves only for further
   * specializations.
   *
   * \tparam T supposed integral or type sequence
   */
  template< class T >
    struct pop_front_on_impl;

  /**
   * \brief Specialization working on type sequences that are empty. Indicates
   * to the user that empty sequences are invalid
   *
   * \tparam S type sequence template
   * \tparam TS type pack used in the type sequence (but here, it's empty)
   */
  template< template< class... > class S, class... TS >
    struct pop_front_on_impl< S< TS... > >
    {
      static_assert( warp::meta_sequence_traits< S< TS... > >::
                       is_type_sequence &&
                       ( sizeof...( TS ) > 0 )
                     ,
                     "Invalid type used. Only non empty type sequence types "
                     "are allowed" );
    };

  /**
   * \brief Specialization used on type sequence containing at least on type.
   *
   * \tparam S type sequence template
   * \tparam T the first type in the type sequence
   * \tparam TS type pack representing the remaining types in the sequence. may
   * be empty.
   */
  template< template< class... > class S, class T, class...TS >
    struct pop_front_on_impl< S< T, TS... > >
    {
      static_assert( warp::meta_sequence_traits< S< T, TS... > >::
                       is_type_sequence,
                     "Invalid type used. Only type sequence types are "
                     "allowed." );

      /**
       * \brief The first type is what you need
       */
      using type = T;

      /**
       * \brief Sequence in which first type is removed
       */
      using sequence = S< TS... >;
    };

  /**
   * \brief Specialization working on an empty integral sequence which is not
   * allowed.
   *
   * \tparam S integral sequence template
   * \tparam U the integral type in the sequence
   * \tparam VS value pack in the integral sequence (here it's empty)
   */
  template< template< class T, T... > class S, class U, U... VS >
    struct pop_front_on_impl< S< U, VS... > >
    {
      static_assert( warp::meta_sequence_traits< S< U, VS... > >::
                       is_integral_sequence &&
                       ( sizeof...( VS ) > 0 ),
                     "Invalid type used. Only non empty integral sequence "
                     "types are allowed" );
    };

  /**
   * \brief Specialization working on a sequence containing at leat one value.
   *
   * \tparam S integral sequence template
   * \tparam U the integral type in the sequence
   * \tparam V the first value of the sequence
   * \tparam VS value pack in the integral sequence (may be empty)
   */
  template< template< class T, T... > class S, class U, U V, U...VS >
    struct pop_front_on_impl< S< U, V, VS... > >
    {
      static_assert( warp::meta_sequence_traits< S< U, V, VS... > >::
                       is_integral_sequence,
                     "Invalid type used. Only integral sequence types are "
                     "allowed." );

      /**
       * \brief The first value is what you want
       */
      static constexpr auto value = V;

      /**
       * \brief Exposes the sequences without its first value
       */
      using sequence = S< U, VS... >;
    };

  /**
   * \brief General form of this algorithm. Not used directly but serves for
   * further specializations.
   *
   * \tparam T A sequence type, either integral or type.
   * \tparam TS context-dependent meaning template argument. When used with
   * integral sequence, it is a integral sequence whereas it is a type pack when
   * used with a type sequence. See below for details.
   */
  template< class T, class...TS >
    struct pop_back_on_impl;

  /**
   * \brief Specialization working on invalid empty type sequence. Notifies the
   * user that empty sequences cannot be used with this algorithm.
   *
   * \tparam S sequence template
   * \tparam TS type pack that is empty
   * \tparam pumped types from the sequence (empty as well)
   */
  template< template< class... > class S, class... TS, class... US >
    struct pop_back_on_impl< S< TS... >, US... >
    {
      static_assert( warp::meta_sequence_traits< S< TS... > >::
                       is_type_sequence &&
                       ( sizeof...( TS ) > 0 ),
                     "Invalid type used. Only non empty type sequence "
                     "types are allowed" );
    };

  /**
   * \brief Specialization working on type sequence containing at least on
   * element.
   *
   * \tparam S sequence template
   * \tparam T first type in the sequecne
   * \tparam TS remaining types in the sequence
   * \tparam US types that has been pumped out from the sequence, will be used
   * to build the popped sequence
   */
  template< template< class... > class S, class T, class... TS, class... US >
    struct pop_back_on_impl< S< T, TS... >, US... >
    {
      static_assert( warp::meta_sequence_traits< S< T, TS... > >::
                       is_type_sequence,
                     "Invalid type used. Only type sequence types are "
                     "allowed." );

      /**
       * \brief Recursively compute the sequence and pump out the first type
       * from the initial sequence to the US type pack. Types are put to build
       * the popped sequence in the right order
       */
      using sequence =
        typename pop_back_on_impl< S< TS... >, US..., T >::sequence;

      /**
       * \brief Recursively obtains the type popped out from the sequence
       */
      using type = typename pop_back_on_impl< S< TS... >, US..., T >::type;
    };

  /**
   * \brief Specialization working with a type sequence containing exactly one
   * type within. Ends the recursion.
   *
   * \tparam S sequence template
   * \tparam T the unique type inside the sequence
   * \tparam US types that have been pumped out from the sequence. Contain all
   * types that were in the initial type sequence but the last one
   */
  template< template< class... > class S, class T, class...US >
    struct pop_back_on_impl< S< T >, US... >
    {
      static_assert( warp::meta_sequence_traits< S< T > >::is_type_sequence,
                     "Invalid type used. Only type sequence types are "
                     "allowed." );

      /**
       * \brief Build the popped type sequence from pumped out types
       */
      using sequence = S< US... >;

      /**
       * \brief The last type of the sequence
       */
      using type = T;
    };

  /**
   * \brief Specialization working with an integral sequence, empty or not.
   * Emptiness is checked through inheritance as usual but instead of doing
   * nothing, sequence and value calculation are delegated to another
   * specialization working with 2 integral sequence, one is the original
   * sequence we want to be popped, the other one is a pump that take value of
   * the first sequence to perform the pop action.
   *
   * \tparam S integral sequence to pop, if empty, trigger a compile time
   * error
   * \tparam U integral type used in the integral sequence
   * \tparam VS value pack used in the sequence
   */
  template< template< class T, T... > class S, class U, U... VS >
    struct pop_back_on_impl< S< U, VS... > >
    {
      static_assert( warp::meta_sequence_traits< S< U, VS... > >::
                       is_integral_sequence &&
                       ( sizeof...( VS ) > 0 ),
                     "Invalid type used. Only non empty integral sequence "
                     "types are allowed" );

      /**
       * \brief Delegating to another specialization, providing an empty
       * integral sequence for the pump
       */
      static constexpr auto value =
        pop_back_on_impl< S< U, VS... >, warp::integral_sequence< U > >::value;

      /**
       * \brief Delegating to another specialization, providing an empty
       * integral sequence for the pump
       */
      using sequence =
        typename pop_back_on_impl
        < S< U, VS... >, warp::integral_sequence< U > >::sequence;
    };

  /**
   * \brief Specialization working with an integral sequence having at least one
   * value within, and a pump for popped values
   *
   * \tparam S sequence template
   * \tparam U integral type used in the sequecne and the pump
   * \tparam V the first value of the sequence
   * \tparam VS remaining values in the sequence
   * \tparam WS values that are stored in the pump integral sequence
   */
  template< template< class T, T... > class S, class U, U V, U...VS, U... WS >
    struct pop_back_on_impl
    < S< U, V, VS... >, warp::integral_sequence< U, WS... > >
    {
      static_assert( warp::meta_sequence_traits< S< U, V, VS... > >::
                       is_integral_sequence,
                     "Invalid type used. Only integral sequence types are "
                     "allowed." );

      /**
       * \brief Recursively pop value inside the pump until it remains only one
       * value in the sequence to be popped
       */
      static constexpr auto value =
        pop_back_on_impl
        < S< U, VS... >, warp::integral_sequence< U, WS..., V > >::value;

      /**
       * \brief Recursively pop value inside the pump until it remains only one
       * value in the sequence to be popped
       */
      using sequence = 
        typename pop_back_on_impl
        < S< U, VS... >, warp::integral_sequence< U, WS..., V > >::sequence;
    };

  /**
   * \brief Specialization working with integral sequence containing only one
   * value. breaks recursion.
   *
   * \tparam S sequence template
   * \tparam U integral type used in the sequence
   * \tparam V the unique value in the sequence
   * \tparam WS value pack in the pump integral sequence
   */
  template< template< class T, T... > class S, class U, U V, U... WS >
    struct pop_back_on_impl< S< U, V >, warp::integral_sequence< U, WS... > >
    {
      static_assert( warp::meta_sequence_traits< S< U, V > >::
                       is_integral_sequence,
                     "Invalid type used. Only integral sequence types are "
                     "allowed." );

      /**
       * \brief This is the last value of the initial integral sequence
       */
      static constexpr auto value = V;

      /**
       * \brief using the pump to build the popped sequence
       */
      using sequence = S< U, WS... >;
    };

  /**
   * \brief General form of the algorithm, used if T is not a valid sequence,
   * triggering an explicit compile time error
   *
   * \tparam T all but a valid sequence type
   * \tparam 2 purpose type pack : when used with a type sequence, reverted
   * types that will be exposed after calculations, if used with integral
   * sequence, integral sequence that will contain reverted value from the
   * initial sequence
   */
  template< class T, class... TS >
    struct reverse_on_impl
    {
      static_assert( warp::meta_sequence_traits< T >::is_meta_sequence,
                     "Invalid type used. Only meta sequence types are "
                     "allowed." );
    };

  /**
   * \brief Specialization working on a type sequence containing at leat one
   * element
   *
   * \tparam S type sequence template
   * \tparam T first type in type sequence
   * \tparam TS remaining types in the sequence
   * \tparam US pumped-out type pack
   */
  template< template< class... > class S, class T, class... TS, class... US >
    struct reverse_on_impl< S< T, TS... >, US... >
    {
      static_assert( warp::meta_sequence_traits< S< T, TS... > >::
                       is_type_sequence,
                     "Invalid type used. Only type sequence types are "
                     "allowed." );

      /**
       * \brief Remove the first type of the sequence and place it at the
       * begining of pumped types pack
       */
      using type = typename reverse_on_impl< S< TS... >, T, US... >::type;
    };

  /**
   * \brief Specialization working for an empty type sequence
   *
   * \tparam S type sequence template
   * \tparam TS empty type pack for the sequence
   * \tparam US pumped-out type pack from the original type sequence
   */
  template< template< class... > class S, class... TS, class... US >
    struct reverse_on_impl< S< TS... >, US... >
    {
      static_assert( warp::meta_sequence_traits< S< TS... > >::is_type_sequence,
                     "Invalid type used. Only type sequence types are "
                     "allowed." );

      /**
       * \brief Use directly pumped out type, in reverse order
       */
      using type = S< US... >;
    };

  /**
   * \brief Specialization working with any valid integral sequence, relying on
   * specific version with an integral sequence as pump
   *
   * \tparam S integral sequence template
   * \tparam U integral type used in the sequence
   * \tparam VS value pack in the integral sequence
   */
  template< template< class T, T... > class S, class U, U...VS >
    struct reverse_on_impl< S< U, VS... > >
    {
      static_assert( warp::meta_sequence_traits< S< U, VS... > >::
                       is_integral_sequence,
                     "Invalid type used. Only integral sequence types are "
                     "allowed." );

      /**
       * \brief Call another implementation with an internal integral sequence
       * as pump
       */
      using type =
        typename reverse_on_impl
        < S< U, VS... >, warp::integral_sequence< U > >::type;
    };

  /**
   * \brief Specialization working with an integral sequence containing at least
   * one element and used with a value pump.
   *
   * \tparam S integral sequence template
   * \tparam U integral type used in the integral sequence
   * \tparam V the first value of the integral sequence
   * \tparam VS value pack, remaining values of the integral sequence
   * \tparam WS value pack in the pump, in reverse order of the original
   * integral sequence
   */
  template< template< class T, T... > class S, class U, U V, U...VS, U... WS >
    struct reverse_on_impl
    < S< U, V, VS... >, warp::integral_sequence<U, WS... > >
    {
      static_assert( warp::meta_sequence_traits< S< U, V, VS... > >::
                       is_integral_sequence,
                     "Invalid type used. Only integral sequence types are "
                     "allowed." );

      /**
       * \brief Pumping-out the first value from the integral sequence to the
       * pump, in reverse order
       */
      using type =
        typename reverse_on_impl
        < S< U, VS... >, warp::integral_sequence< U, V, WS... > >::type;
    };

  /**
   * \brief Specialization working with an empty integral sequence and a value
   * pump (empty or not)
   *
   * \tparam S integral sequence template
   * \tparam U integral type used in the integral sequence
   * \tparam VS value pack, (empty here)
   * \tparam WS value pack in the pump, in reverse order of the original
   * integral sequence
   */
  template< template< class T, T... > class S, class U, U...VS, U... WS >
    struct reverse_on_impl< S< U, VS... >, warp::integral_sequence< U, WS... > >
    {
      static_assert( warp::meta_sequence_traits< S< U, VS... > >::
                       is_integral_sequence,
                     "Invalid type used. Only integral sequence types are "
                     "allowed." );

      /**
       * \brief Exposing a sequence with value picked from the pump
       */
      using type = S< U, WS... >;
    };

  /**
   * \brief Non specialized template for find_first_in_type_sequence_impl. Only
   * used when the provided type sequence (T) does not match to a valid type
   * sequence template signature
   *
   * \tparam T arbitrary type that does not match to a valid type sequence
   * signature
   */
  template< class T, template< class, class... > class, class... >
    struct find_first_in_type_sequence_impl
    {
      static_assert( warp::meta_sequence_traits< T >::is_type_sequence,
                     "Invalid type used. Only type sequence types are "
                     "allowed." );
    };

  /**
   * \brief Specialized version working with empty type sequence specified.
   * A check is made only on the provided type sequence.
   *
   * \tparam S the empty type sequence
   * \tparam TS empty type pack of the sequence
   * \tparam P predicate template
   * \tparam US type pack used as argument of the predicate template
   */
  template
    <
      template< class... > class S, class... TS,
      template< class, class... > class P, class... US
    >
    struct find_first_in_type_sequence_impl< S< TS... >, P, US... >
    {
      static_assert( warp::meta_sequence_traits< S< TS... > >::is_type_sequence,
                     "Invalid type used. Only type sequence types are "
                     "allowed." );

      /**
       * \brief Exposes the sequence as is as it is empty
       */
      using type = S< TS... >;
    };

  /**
   * \brief Specialization working on a type sequence that contains at least one
   * element. Checks are performed on both type sequence and the predicate
   * template instance that will be used to ensure the 2 are valid
   *
   * \tparam S the type sequence template
   * \tparam T the first type inside the type sequence
   * \tparam TS remaining types in the type sequence
   * \tparam P predicate template
   * \tparam US type pack used as parameter for the predicate
   */
  template
    <
      template< class... > class S, class T, class... TS,
      template< class, class... > class P, class... US
    >
    struct find_first_in_type_sequence_impl< S< T, TS... >, P, US... >
    {
      static_assert( warp::meta_sequence_traits< S< T, TS... > >::
                       is_type_sequence,
                     "Invalid type used. Only type sequence types are "
                     "allowed." );
        
      static_assert( warp::meta_predicate_traits< P< T, US... > >::
                       is_type_sequence_predicate,
                     "Invalid type used. Only type sequence predicate types "
                     "are allowed." );

      /**
       * \brief Using a predicate template instance and conditional type
       * deduction. Recursive search if T doesn't match the predicate value
       */
      using type =
        std::conditional_t
          <
            P< T, US... >::value,
            S< T, TS... >,
            typename find_first_in_type_sequence_impl
              < S< TS... >, P, US... >::type
          >;
    };

  /**
   * \brief Non specialized template for find_first_in_integral_sequence_impl.
   * Only used when the provided integral sequence (T) does not match to a valid
   * integral sequence template signature
   *
   * \tparam T arbitrary integral that does not match to a valid integral
   * sequence signature
   */
  template< class T, template< class U, U, class... > class, class... >
    struct find_first_in_integral_sequence_impl
    {
      static_assert( warp::meta_sequence_traits< T >::
                       is_integral_sequence,
                     "Invalid type used. Only integral sequence types are "
                     "allowed." );
    };

  /**
   * \brief Specialized version working with empty integral sequence specified.
   * A check is made only on the provided integral sequence.
   *
   * \tparam S the empty integral sequence
   * \tparam U integral type used in the sequence
   * \tparam VS empty integral pack of the sequence
   * \tparam P predicate template
   * \tparam US integral pack used as argument of the predicate template
   */
  template
    <
      template< class T, T... > class S, class U, U... VS,
      template< class V, V, class... > class P, class... US
    >
    struct find_first_in_integral_sequence_impl< S< U, VS... >, P, US... >
    {
      static_assert( warp::meta_sequence_traits< S< U, VS... > >::
                       is_integral_sequence,
                     "Invalid type used. Only integral sequence types are "
                     "allowed." );

      /**
       * \brief Exposes the sequence as is as it is empty
       */
      using type = S< U, VS... >;
    };

  /**
   * \brief Specialization working on a integral sequence that contains at least
   * one element. Checks are performed on both integral sequence and the
   * predicate template instance that will be used to ensure the 2 are valid
   *
   * \tparam S the integral sequence template
   * \tparam T the first integral inside the integral sequence
   * \tparam TS remaining integrals in the integral sequence
   * \tparam P predicate template
   * \tparam US integral pack used as parameter for the predicate
   */
  template
    <
      template< class T, T... > class S, class U, U V, U... VS,
      template< class W, W, class... > class P, class... US
    >
    struct find_first_in_integral_sequence_impl< S< U, V, VS... >, P, US... >
    {
      static_assert( warp::meta_sequence_traits< S< U, V, VS... > >::
                       is_integral_sequence,
                     "Invalid type used. Only integral sequence types are "
                     "allowed." );

      static_assert( warp::meta_predicate_traits< P< U, V, US... > >::
                       is_integral_sequence_predicate,
                     "Invalid type used. Only integral sequence predicates are "
                     "allowed." );
        
      /**
       * \brief Using a predicate template instance and conditional type
       * deduction. Recursive search if V doesn't match the predicate value
       */
      using type =
        std::conditional_t
          <
            P< U, V, US... >::value,
            S< U, V, VS... >,
            typename find_first_in_integral_sequence_impl
              < S< U, VS... >, P, US... >::type
          >;
    };

  /**
   * \brief Non specialized template for find_all_in_type_sequence_impl. Only
   * used when the provided type sequence (T) does not match to a valid type
   * sequence template signature
   *
   * \tparam T arbitrary type that does not match to a valid type sequence
   * signature
   */
  template< class T, template< class, class... > class, class... >
    struct find_all_in_type_sequence_impl
    {
      static_assert( warp::meta_sequence_traits< T >::is_type_sequence,
                     "Invalid type used. Only type sequence types are "
                     "allowed." );
    };

  /**
   * \brief Specialized version working with empty type sequence specified.
   * A check is made only on the provided type sequence.
   *
   * \tparam S the empty type sequence
   * \tparam TS empty type pack of the sequence
   * \tparam P predicate template
   * \tparam US type pack used as argument of the predicate template
   * \tparam WS type pack corresponding to all type that are matching the
   * predicate before the S< TS... > sequence was empty
   */
  template
    <
      template< class... > class S, class... TS,
      template< class, class... > class P, class... US,
      class... WS
    >
    struct find_all_in_type_sequence_impl
    <
      S< TS... >, P,
      warp::type_sequence< US... >,
      warp::type_sequence< WS... >
    >
    {
      static_assert( warp::meta_sequence_traits< S< TS... > >::is_type_sequence,
                     "Invalid type used. Only type sequence types are "
                     "allowed." );

      /**
       * \brief Exposes the sequence made of type inside the variadic pump as
       * S< TS... > is empty
       */
      using type = S< WS... >;
    };

  /**
   * \brief Specialization working on a type sequence that contains at least one
   * element. Checks are performed on both type sequence and the predicate
   * template instance that will be used to ensure the 2 are valid
   *
   * \tparam S the type sequence template
   * \tparam T the all type inside the type sequence
   * \tparam TS remaining types in the type sequence
   * \tparam P predicate template
   * \tparam US type pack used as parameter for the predicate
   */
  template
    <
      template< class... > class S, class T, class... TS,
      template< class, class... > class P, class... US,
      class... WS
    >
    struct find_all_in_type_sequence_impl
    <
      S< T, TS... >, P,
      warp::type_sequence< US... >,
      warp::type_sequence< WS... >
    >
    {
      static_assert( warp::meta_sequence_traits< S< T, TS... > >::
                       is_type_sequence,
                     "Invalid type used. Only type sequence types are "
                     "allowed." );

      static_assert( warp::meta_predicate_traits< P< T, US... > >::
                       is_type_sequence_predicate,
                     "Invalid type used. Only type sequence types are "
                     "allowed." );

      /**
       * \brief Using a predicate template instance and conditional type
       * deduction. Recursive search until the original sequence observed is
       * empty. If T matches the predicate, add it to the type list pump
       */
      using type =
        std::conditional_t
          <
            // predicate matched
            P< T, US... >::value,
            // recursive search, adding T into the pump
            typename find_all_in_type_sequence_impl
              <
                S< TS... >, P,
                warp::type_sequence< US... >,
                warp::type_sequence< WS..., T >
              >::type,
            // else, recursive search leaving pump untouched
            typename find_all_in_type_sequence_impl
              <
                S< TS... >, P,
                warp::type_sequence< US... >,
                warp::type_sequence< WS... >
              >::type
          >;
    };

  /**
   * \brief Non specialized template for find_all_in_integral_sequence_impl.
   * Only used when the provided integral sequence (T) does not match to a valid
   * integral sequence template signature
   *
   * \tparam T arbitrary integral that does not match to a valid integral
   * sequence signature
   */
  template< class T, template< class U, U, class... > class, class... >
    struct find_all_in_integral_sequence_impl
    {
      static_assert( warp::meta_sequence_traits< T >::is_integral_sequence,
                     "Invalid type used. Only integral sequence types are "
                     "allowed." );
    };

  /**
   * \brief Specialized version working with empty integral sequence specified.
   * A check is made only on the provided integral sequence.
   *
   * \tparam S the empty integral sequence
   * \tparam U integral type used in the sequence
   * \tparam VS empty integral pack of the sequence
   * \tparam P predicate template
   * \tparam TS integral pack used as argument of the predicate template
   * \tparam Q placeholder integral type in the integral sequence provided
   * \tparam WS integral pack corresponding to all integral that are matching
   * the predicate before the S< U, VS... > sequence was empty
   */
  template
    <
      template< class T, T... > class S, class U, U... VS,
      template< class V, V, class... > class P, class... TS,
      class Q, Q... WS
    >
    struct find_all_in_integral_sequence_impl
    <
      S< U, VS... >, P,
      warp::type_sequence< TS... >,
      warp::integral_sequence< Q, WS... >
    >
    {
      static_assert( warp::meta_sequence_traits< S< U, VS... > >::
                       is_integral_sequence,
                     "Invalid type used. Only integral sequence types are "
                     "allowed." );

      /**
       * \brief Exposes the sequence made of integral inside the variadic pump
       * as S< U, VS... > is empty
       */
      using type = S< U, WS... >;
    };

  /**
   * \brief Specialization working on a integral sequence that contains at least
   * one element. Checks are performed on both integral sequence and the
   * predicate template instance that will be used to ensure the 2 are valid
   *
   * \tparam S the integral sequence template
   * \tparam U the integral type used in the sequence
   * \tparam V the first value in the sequence
   * \tparam VS the remaining values inside the integral sequence
   * \tparam P predicate template
   * \tparam Q placeholder integral type in the integral type embedded in the
   * warp::type
   * \tparam US integral pack used as parameter for the predicate
   */
  template
    <
      template< class T, T... > class S, class U, U V, U... VS,
      template< class R, R, class... > class P, class... TS,
      class Q, Q... WS
    >
    struct find_all_in_integral_sequence_impl
    <
      S< U, V, VS... >, P,
      warp::type_sequence< TS... >,
      warp::integral_sequence< Q, WS... >
    >
    {
      static_assert( warp::meta_sequence_traits< S< U, V, VS... > >::
                       is_integral_sequence,
                     "Invalid type used. Only integral sequence types are "
                     "allowed." );

      static_assert( warp::meta_predicate_traits< P< U, V, TS... > >::
                       is_integral_sequence_predicate,
                     "Invalid type used. Only integral sequence predicates are "
                     "allowed." );

      /**
       * \brief Using a predicate template instance and conditional integral
       * deduction. Recursive search until the original sequence observed is
       * empty. If V matches the predicate, add it to the integral list pump
       */
      using type =
        std::conditional_t
          <
            P< U, V, TS... >::value,
            // predicate matched
            // recursive search, adding V into the pump
            typename find_all_in_integral_sequence_impl
              <
                S< U, VS... >, P,
                warp::type_sequence< TS... >,
                warp::integral_sequence< U, WS..., V >
              >::type,
            // predicate unmatched
            // recursive search leaving pump untouched
            typename find_all_in_integral_sequence_impl
              <
                S< U, VS... >, P,
                warp::type_sequence< TS... >,
                warp::integral_sequence< U, WS... >
              >::type
          >;
    };

  /**
   * \brief Non specialized version used on types that don't have a valid
   * template signature for integral sequence or type sequence. Display explicit
   * error message
   *
   * \tparam T invalid type
   */
  template< class T >
    struct is_empty_sequence_impl
    {
      static_assert( warp::meta_sequence_traits< T >::is_meta_sequence,
                     "Invalid type used. Only integral sequence types are "
                     "allowed." );

    };

  /**
   * \brief Specialization working with a valid type sequence template
   * signature. A check is made through inheritance for traits.
   *
   * \tparam S type sequence template
   * \tparam TS type pack contained in the sequence template
   */
  template< template< class... > class S, class... TS >
    struct is_empty_sequence_impl< S< TS... > >
    {
      static_assert( warp::meta_sequence_traits< S< TS... > >::is_type_sequence,
                     "Invalid type used. Only type sequence types are "
                     "allowed." );

      /**
       * \brief Uses this wonderful operator
       */
      static constexpr auto value = ( sizeof...( TS ) == 0 );
    };

  /**
   * \brief Specialization working with valid integral sequence template
   * signature. A check is made through inheritance for traits
   *
   * \tparam S the integral sequence template
   * \tparam U integral type used in the integral sequence
   * \tparam VS value pack contained in the integral sequence
   */
  template< template< class T, T... > class S, class U, U... VS >
    struct is_empty_sequence_impl< S< U, VS... > >
    {
      static_assert( warp::meta_sequence_traits< S< U, VS... > >::
                       is_integral_sequence,
                     "Invalid type used. Only integral sequence types are "
                     "allowed." );

      /**
       * \brief Uses this wonderfull operator
       */
      static constexpr auto value = ( sizeof...( VS ) == 0 );
    };

  /**
   * \brief Non specialized template for remove_first_in_type_sequence_impl.
   * Only used when the provided type sequence (T) does not match to a valid
   * type sequence template signature
   *
   * \tparam T arbitrary type that does not match to a valid type sequence
   * signature
   */
  template< class T, template< class, class... > class, class... >
    struct remove_first_in_type_sequence_impl
    {
      static_assert( warp::meta_sequence_traits< T >::is_type_sequence,
                     "Invalid type used. Only type sequence types are "
                     "allowed." );
    };

  /**
   * \brief Specialized version working with empty type sequence specified.
   * A check is made only on the provided type sequence.
   *
   * \tparam S the empty type sequence
   * \tparam TS empty type pack of the sequence
   * \tparam P predicate template
   * \tparam US type pack used as argument of the predicate template
   */
  template
    <
      template< class... > class S, class... TS,
      template< class, class... > class P, class... US,
      class... VS
    >
    struct remove_first_in_type_sequence_impl
    < 
      S< TS... >, P,
      warp::type_sequence< US... >, warp::type_sequence< VS... >
    >
    {
      static_assert( warp::meta_sequence_traits< S< TS... > >::is_type_sequence,
                     "Invalid type used. Only type sequence types are "
                     "allowed." );

      /**
       * \brief Exposes the sequence as is as it is empty
       */
      using type = S< TS... >;
    };

  /**
   * \brief Specialization working on a type sequence that contains at least one
   * element. Checks are performed on both type sequence and the predicate
   * template instance that will be used to ensure the 2 are valid
   *
   * \tparam S the type sequence template
   * \tparam T the first type inside the type sequence
   * \tparam TS remaining types in the type sequence
   * \tparam P predicate template
   * \tparam US type pack used as parameter for the predicate, embedded in a
   * type sequence.
   * \tparam VS type pack that are pumped out in previous recursive calls,
   * embedded in type sequence
   */
  template
    <
      template< class... > class S, class T, class... TS,
      template< class, class... > class P, class... US,
      class... VS
    >
    struct remove_first_in_type_sequence_impl
      <
        S< T, TS... >, P,
        warp::type_sequence< US... >, warp::type_sequence< VS... >
      >
    {
      static_assert( warp::meta_sequence_traits< S< T, TS... > >::
                       is_type_sequence,
                     "Invalid type used. Only type sequence types are "
                     "allowed." );

      static_assert( warp::meta_predicate_traits< P< T, US... > >::
                       is_type_sequence_predicate,
                     "Invalid type used. Only type sequence predicates are "
                     "allowed." );

      /**
       * \brief Using a predicate template instance and conditional type
       * deduction. Recursive search if T doesn't match the predicate value
       */
      using type =
        std::conditional_t
          <
            P< T, US... >::value,
            S< VS..., TS... >,
            typename remove_first_in_type_sequence_impl
            <
              S< TS... >, P,
              warp::type_sequence< US... >, warp::type_sequence< VS..., T >
            >::type
          >;
    };

  /**
   * \brief Non specialized template for remove_first_in_integral_sequence_impl.
   * Only used when the provided integral sequence (T) does not match to a valid
   * integral sequence template signature
   *
   * \tparam T arbitrary integral that does not match to a valid integral
   * sequence signature
   */
  template< class T, template< class U, U, class... > class, class... >
    struct remove_first_in_integral_sequence_impl
    {
      static_assert( warp::meta_sequence_traits< T >::
                       is_integral_sequence,
                     "Invalid type used. Only integral sequence types are "
                     "allowed." );
    };

  /**
   * \brief Specialized version working with empty integral sequence specified.
   * A check is made only on the provided integral sequence.
   *
   * \tparam S the empty integral sequence
   * \tparam U integral type used in the sequence
   * \tparam VS empty integral pack of the sequence
   * \tparam P predicate template
   * \tparam US integral pack used as argument of the predicate template
   * \tparam Q integral type used in the pumped out values integral sequence
   * \tparam WS pumped out value pack
   */
  template
    <
      template< class T, T... > class S, class U, U... VS,
      template< class V, V, class... > class P, class... US,
      class Q, Q... WS
    >
    struct remove_first_in_integral_sequence_impl
    <
      S< U, VS... >, P,
      warp::type_sequence< US... >, warp::integral_sequence< Q, WS... >
    >
    {
      static_assert( warp::meta_sequence_traits< S< U, VS... > >::
                       is_integral_sequence,
                     "Invalid type used. Only integral sequence types are "
                     "allowed." );

      /**
       * \brief Exposes the sequence as is as it is empty
       */
      using type = S< U, VS... >;
    };

  /**
   * \brief Specialization working on a integral sequence that contains at least
   * one element. Checks are performed on both integral sequence and the
   * predicate template instance that will be used to ensure the 2 are valid
   *
   * \tparam S the integral sequence template
   * \tparam T the first integral inside the integral sequence
   * \tparam TS remaining integrals in the integral sequence
   * \tparam P predicate template
   * \tparam US integral pack used as parameter for the predicate
   * \tparam Q integral type used in the pumped out values integral sequence
   * \tparam WS pumped out value pack
   */
  template
    <
      template< class T, T... > class S, class U, U V, U... VS,
      template< class W, W, class... > class P, class... US,
      class Q, Q... WS
    >
    struct remove_first_in_integral_sequence_impl
    <
      S< U, V, VS... >, P,
      warp::type_sequence< US... >, warp::integral_sequence< Q, WS... >
    >
    {
      static_assert( warp::meta_sequence_traits< S< U, V, VS... > >::
                       is_integral_sequence,
                     "Invalid type used. Only integral sequence types are "
                     "allowed." );

      static_assert( warp::meta_predicate_traits< P< U, V, US... > >::
                       is_integral_sequence_predicate,
                     "Invalid type used. Only integral sequence predicates are "
                     "allowed." );

      /**
       * \brief Using a predicate template instance and conditional type
       * deduction. Recursive search if V doesn't match the predicate value
       */
      using type =
        std::conditional_t
        <
          P< U, V, US... >::value,
          S< U, WS..., VS... >,
          typename remove_first_in_integral_sequence_impl
          <
            S< U, VS... >, P,
            warp::type_sequence< US... >, warp::integral_sequence< U, WS..., V >
          >::type
        >;
    };

  /**
   * \brief Non specialized template for remove_all_in_type_sequence_impl. Only
   * used when the provided type sequence (T) does not match to a valid type
   * sequence template signature
   *
   * \tparam T arbitrary type that does not match to a valid type sequence
   * signature
   */
  template< class T, template< class, class... > class, class... >
    struct remove_all_in_type_sequence_impl
    {
      static_assert( warp::meta_sequence_traits< T >::is_type_sequence,
                     "Invalid type used. Only type sequence types are "
                     "allowed." );
    };

  /**
   * \brief Specialized version working with empty type sequence specified.
   * A check is made only on the provided type sequence.
   *
   * \tparam S the empty type sequence
   * \tparam TS empty type pack of the sequence
   * \tparam P predicate template
   * \tparam US type pack used as argument of the predicate template
   * \tparam WS type pack corresponding to all type that are matching the
   * predicate before the S< TS... > sequence was empty
   */
  template
    <
      template< class... > class S, class... TS,
      template< class, class... > class P, class... US,
      class... WS
    >
    struct remove_all_in_type_sequence_impl
    <
      S< TS... >, P,
      warp::type_sequence< US... >, warp::type_sequence< WS... >
    >
    {
      static_assert( warp::meta_sequence_traits< S< TS... > >::is_type_sequence,
                     "Invalid type used. Only type sequence types are "
                     "allowed." );

      /**
       * \brief Exposes the sequence made of type inside the variadic pump as
       * S< TS... > is empty
       */
      using type = S< WS... >;
    };

  /**
   * \brief Specialization working on a type sequence that contains at least one
   * element. Checks are performed on both type sequence and the predicate
   * template instance that will be used to ensure the 2 are valid
   *
   * \tparam S the type sequence template
   * \tparam T the all type inside the type sequence
   * \tparam TS remaining types in the type sequence
   * \tparam P predicate template
   * \tparam US type pack used as parameter for the predicate
   * \tparam WS type pack corresponding to all type that are matching the
   * predicate before the S< TS... > sequence was empty
   */
  template
    <
      template< class... > class S, class T, class... TS,
      template< class, class... > class P, class... US,
      class... WS
    >
    struct remove_all_in_type_sequence_impl
    <
      S< T, TS... >, P,
      warp::type_sequence< US... >,
      warp::type_sequence< WS... >
    >
    {
      static_assert( warp::meta_sequence_traits< S< T, TS... > >::
                       is_type_sequence,
                     "Invalid type used. Only type sequence types are "
                     "allowed." );

      static_assert( warp::meta_predicate_traits< P< T, US... > >::
                       is_type_sequence_predicate,
                     "Invalid type used. Only type sequence predicates are "
                     "allowed." );

      /**
       * \brief Using a predicate template instance and conditional type
       * deduction. Recursive search until the original sequence observed is
       * empty. If T matches the predicate, add it to the type list pump
       */
      using type =
        std::conditional_t
        <
          // predicate matched
          P< T, US... >::value,
          // recursive search, leaving pump untouched
          typename remove_all_in_type_sequence_impl
            <
              S< TS... >, P,
              warp::type_sequence< US... >, warp::type_sequence< WS... >
            >::type,
          // else, recursive search adding type in pumped
          typename remove_all_in_type_sequence_impl
            <
              S< TS... >, P,
              warp::type_sequence< US... >, warp::type_sequence< WS..., T >
            >::type
        >;
    };

  /**
   * \brief Non specialized template for remove_all_in_integral_sequence_impl.
   * Only used when the provided integral sequence (T) does not match to a valid
   * integral sequence template signature
   *
   * \tparam T arbitrary integral that does not match to a valid integral
   * sequence signature
   */
  template< class T, template< class U, U, class... > class, class... >
    struct remove_all_in_integral_sequence_impl
    {
      static_assert( warp::meta_sequence_traits< T >::
                       is_integral_sequence,
                     "Invalid type used. Only integral sequence types are "
                     "allowed." );
    };

  /**
   * \brief Specialized version working with empty integral sequence specified.
   * A check is made only on the provided integral sequence.
   *
   * \tparam S the empty integral sequence
   * \tparam U integral type used in the sequence
   * \tparam VS empty integral pack of the sequence
   * \tparam P predicate template
   * \tparam TS integral pack used as argument of the predicate template
   * \tparam Q placeholder integral type in the integral sequence provided
   * \tparam WS integral pack corresponding to all integral that are matching
   * the predicate before the S< U, VS... > sequence was empty
   */
  template
    <
      template< class T, T... > class S, class U, U... VS,
      template< class V, V, class... > class P, class... TS,
      class Q, Q... WS
    >
    struct remove_all_in_integral_sequence_impl
    <
      S< U, VS... >, P,
      warp::type_sequence< TS... >, warp::integral_sequence< Q, WS... >
    >
    {
      static_assert( warp::meta_sequence_traits< S< U, VS... > >::
                       is_integral_sequence,
                     "Invalid type used. Only integral sequence types are "
                     "allowed." );

      /**
       * \brief Exposes the sequence made of integral inside the variadic pump
       * as S< U, VS... > is empty
       */
      using type = S< U, WS... >;
    };

  /**
   * \brief Specialization working on a integral sequence that contains at least
   * one element. Checks are performed on both integral sequence and the
   * predicate template instance that will be used to ensure the 2 are valid
   *
   * \tparam S the integral sequence template
   * \tparam U the integral type used in the sequence
   * \tparam V the first value in the sequence
   * \tparam VS the remaining values inside the integral sequence
   * \tparam P predicate template
   * \tparam Q placeholder integral type in the integral type embedded in the
   * warp::type
   * \tparam US integral pack used as parameter for the predicate
   */
  template
    <
      template< class T, T... > class S, class U, U V, U... VS,
      template< class R, R, class... > class P, class... TS,
      class Q, Q... WS
    >
    struct remove_all_in_integral_sequence_impl
    <
      S< U, V, VS... >, P,
      warp::type_sequence< TS... >, warp::integral_sequence< Q, WS... >
    >
    {
      static_assert( warp::meta_sequence_traits< S< U, V, VS... > >::
                       is_integral_sequence,
                     "Invalid type used. Only integral sequence types are "
                     "allowed." );

      static_assert( warp::meta_predicate_traits< P< U, V, TS... > >::
                       is_integral_sequence_predicate,
                     "Invalid type used. Only integral sequence predicates are "
                     "allowed." );

      /**
       * \brief Using a predicate template instance and conditional integral
       * deduction. Recursive search until the original sequence observed is
       * empty. If V matches the predicate, add it to the integral list pump
       */
      using type =
        std::conditional_t
        <
          P< U, V, TS... >::value,
          // predicate matched
          // recursive search, don't add V inside the pump
          typename remove_all_in_integral_sequence_impl
            <
              S< U, VS... >, P,
              warp::type_sequence< TS... >,
              warp::integral_sequence< U, WS... >
            >::type,
          // predicate unmatched
          // recursive search, adding V inside the pump
          typename remove_all_in_integral_sequence_impl
            <
              S< U, VS... >, P,
              warp::type_sequence< TS... >,
              warp::integral_sequence< U, WS..., V >
            >::type
        >;
    };

  /**
   * \brief Non specialized version of the hidden implementation of the sort
   * feature on a type sequence. This version is used if the T type is all but a
   * type sequence template instance. Triggers an understandable error message.
   *
   * \tparam T not a type sequence
   */
  template
    < class T, template< class, class... > class, class... >
    struct sort_type_sequence_impl
    {
      static_assert( warp::meta_sequence_traits< T >::is_type_sequence,
                     "Invalid type used. Only type sequence types are "
                     "allowed." );
    };

  /**
   * \brief Specialization working with an empty type sequence. Just test traits
   * of the sequence and exposes it as is, nothing to sort.
   *
   * \tparam S type sequence template
   * \tparam TS empty type pack (for the type sequence template)
   * \tparam P the predicate template (not verified here as not used)
   * \tparam US type pack used in the predicate as arguments
   */
  template
    <
      template< class... > class S,
      template< class, class... > class P, class... TS
    >
    struct sort_type_sequence_impl< S<>, P, TS... >
    {
      static_assert( warp::meta_sequence_traits< S<> >::is_type_sequence,
                     "Invalid type used. Only type sequence types are "
                     "allowed." );

      /**
       * \brief Exposes the empty sequence as is
       */
      using type = S<>;
    };

  /**
   * \brief Specialization working with a type sequence that contains only one
   * element. There is nothing to sort in a one element type sequence
   *
   * \tparam S type sequence template
   * \tparam T the unique element in the type sequence
   * \tparam P the predicate template (not verified here as not used)
   * \tparam US type pack used in the predicate as arguments
   */
  template
    <
      template< class... > class S, class T,
      template< class, class... > class P, class... TS
    >
    struct sort_type_sequence_impl< S< T >, P, TS... >
    {
      static_assert( warp::meta_sequence_traits< S< T > >::is_type_sequence,
                     "Invalid type used. Only type sequence types are "
                     "allowed." );

      /**
       * \brief Nothing to do there is only one element in the sequence.
       */
      using type = S< T >;
    };

  /**
   * \brief Specialization working with a type sequence containing 2 or more
   * elements within. This is the really functionnal specialization, testing
   * traits of the type sequence and the predicate as it'll be used.
   *
   * \tparam S type sequence template
   * \tparam T the first element in the type sequence
   * \tparam U the second element in the type sequence
   * \tparam TS remaining types in the sequence
   * \tparam P the predicate template (not verified here as not used)
   * \tparam US type pack used in the predicate as arguments
   */
  template
    <
      template< class... > class S, class T, class U, class... TS,
      template< class, class... > class P, class... US
    >
    struct sort_type_sequence_impl< S< T, U, TS... >, P, US... >
    {
      static_assert( warp::meta_sequence_traits< S< T, U, TS... > >::
                       is_type_sequence,
                     "Invalid type used. Only type sequence types are "
                     "allowed." );

      static_assert( warp::meta_predicate_traits< P< T, U, US... > >::
                       is_type_sequence_predicate,
                     "Invalid type used. Only type sequence predicates are "
                     "allowed." );

      /**
       * \brief The sorter template is the one that will perform the sort
       * operation several times. It will sort using the bubble sort algorithm.
       *
       * \tparam C_ the number of sort operation to perform, will decrease by
       * one each time the full sequence has been sorted. When reaches 0, the
       * sort is terminated.
       * \tparam S_ the sequence to sort
       * \tparam P_ the predicate used to sort
       * \tparam T_ a type sequence that contains the predicate arguments
       * \tparam U_ a type sequence that contains the in-progress sorted values
       */
      template
        <
          std::size_t C_,
          class S_,
          template< class, class... > class P_,
          class T_, class U_
        >
        struct sorter;

      /**
       * \brief Specialization of the sorter, working with a provided type
       * sequence currently in-sorting and containing more than 2 values.
       *
       * \tparam C_ the number of sort operation to perform, will decrease by
       * one each time the full sequence has been sorted. When reaches 0, the
       * sort is terminated.
       * \tparam S_ the sequence template to sort
       * \tparam T_ the first element of the sequence
       * \tparam U_ the second element of the sequence
       * \tparam TS_ remaining element in the sequence to sort
       * \tparam P_ the predicate used to sort
       * \tparam US_ a type pack used in the type sequence containing predicate
       * arguments
       * \tparam VS_ a type pack used in the sequence containing sorted elements
       */
      template
        <
          std::size_t C_,
          template< class... > class S_, class T_, class U_, class... TS_,
          template< class, class... > class P_,
          class... US_, class... VS_
        >
        struct sorter
        <
          C_,
          S_< T_, U_, TS_... >,
          P_,
          warp::type_sequence< US_... >, warp::type_sequence< VS_... >
        >
        {
          /**
           * \brief Use the predicate and build the next input sequence to be
           * sorted, keeping only the type that doesn't match the predicate and
           * the next ones
           */
          using popped_input_sequence =
            std::conditional_t
            <
              P_< T_, U_, US_... >::value,
              S_< U_, TS_... >,
              S_< T_, TS_... >
            >;

          /**
           * \brief Consolidate the output type sequence by adding at last the
           * type that matches the predicate
           */
          using sorted_out_sequence =
            std::conditional_t
            <
              P_< T_, U_, US_... >::value,
              warp::type_sequence< VS_..., T_ >,
              warp::type_sequence< VS_..., U_ >
            >;

          /**
           * \brief Recursive usage of the sorter, using calculated above
           * sequences as input and output
           */
          using type =
            typename sorter
            <
              // keep the same counter value
              C_,
              // input sequence with the matching type popped out
              popped_input_sequence,
              P_,
              warp::type_sequence< US_... >,
              // output sequence appended with the type matching the predicate
              sorted_out_sequence
            >::type;
        };

      /**
       * \brief Specialization used when the sequence to sort contains exactly 2
       * elements. It means that a sort iteration has finished and that the
       * counter will be decreased. Note that if the counter reach 0, the sort
       * is done
       *
       * \tparam C_ the number of sort operation to perform, will decrease by
       * one each time the full sequence has been sorted. When reaches 0, the
       * sort is terminated.
       * \tparam S_ the sequence template to sort
       * \tparam T_ the first element of the sequence
       * \tparam U_ the second element of the sequence
       * \tparam P_ the predicate used to sort
       * \tparam US_ a type pack used in the type sequence containing predicate
       * arguments
       * \tparam VS_ a type pack used in the sequence containing sorted elements
       */
      template
        <
          std::size_t C_,
          template< class... > class S_, class T_, class U_,
          template< class, class... > class P_,
          class... US_, class... VS_
        >
        struct sorter
        <
          C_,
          S_< T_, U_ >,
          P_,
          warp::type_sequence< US_... >, warp::type_sequence< VS_... >
        >
        {
          /**
           * \brief First, sort the 2 element and add them to the sorted
           * sequence according to the predicate. Uses the sequence template
           * provided by the user
           */
          using sorted_sequence =
            std::conditional_t
            <
              P< T_, U_, US_... >::value,
              S_< VS_..., T_, U_ >,
              S_< VS_..., U_, T_ >
            >;

          /**
           * \brief Recursive use of sorter, decreasing counter value by one,
           * switching the sorted sequence content to be used as input with the
           * provided sequence template
           */
          using type =
            typename sorter
            <
              // one sort iteration terminated
              C_ - 1,
              // sorted sequence is used here
              sorted_sequence,
              P_,
              warp::type_sequence< US_... >,
              // the variadic pump is now empty, ready for the next iteration
              warp::type_sequence<>
            >::type;
        };

      /**
       * \brief Specialization of the sorter when the counter reaches 0.Sort is
       * considered as done here, ends all recursion, don't use the predicate
       * anymore and exposes a type sequence that is fully sorted
       *
       * \tparam S_ the sequence template to sort
       * \tparam T_ first type in the sequence
       * \tparam T_ second type in the sequence
       * \tparam TS_ type pack used in the sequence template above, completely
       * sorted here
       * \tparam P_ the predicate used to sort
       * \tparam T_ unused type but it was a type sequence containing predicate
       * variadic arguments
       */
      template
        <
          template< class... > class S_, class T_, class U_, class... TS_,
          template< class, class... > class P_,
          class... US_
        >
        struct sorter
        <
          0,
          S_< T_, U_, TS_... >,
          P_,
          warp::type_sequence< US_... >, warp::type_sequence<>
        >
        {
          /**
           * \brief Exposes the sorted sequence, using the sequence template
           * provided by the user that has been switched with the variadic pump
           * when the counter has been decreased (see above specialization)
           */
          using type = S< T_, U_, TS_... >;
        };

      /**
       * \brief Uses the sorter type, it will perform a bubble sort
       */
      using type =
        typename sorter
        <
          // serves as counter for sorts operation, length of sequence - 1
          sizeof...( TS ) + 1,
          // forward template arguments
          S< T, U, TS... >, P,
          // embbeds predicate arguments in a sequence to...
          warp::type_sequence< US... >,
          // ...allow usage of a variadic pump for sorted types
          warp::type_sequence<>
        >::type;
    };

  /**
   * \brief Non specialized version of the hidden implementation of the sort
   * feature on an integral sequence. This version is used if the T type is all
   * but an integral sequence template instance. Triggers an understandable
   * error message.
   *
   * \tparam T not an integral sequence
   */
  template
    < class T, template< class U, U, class... > class, class... >
    struct sort_integral_sequence_impl
    {
      static_assert( warp::meta_sequence_traits< T >::
                       is_integral_sequence,
                     "Invalid type used. Only integral sequence types are "
                     "allowed." );
    };

  /**
   * \brief Specialization working with an empty integral sequence. Just test
   * traits of the sequence and exposes it as is, nothing to sort.
   *
   * \tparam S integral sequence template
   * \tparam U integral type used in the integral sequence
   * \tparam VS empty integral pack (for the integral sequence template)
   * \tparam P the predicate template (not verified here as not used)
   * \tparam TS type pack used in the predicate as arguments
   */
  template
    <
      template< class T, T... > class S, class U, U... VS,
      template< class V, V, class... > class P, class... TS
    >
    struct sort_integral_sequence_impl< S< U, VS... >, P, TS... >
    {
      static_assert( warp::meta_sequence_traits< S< U, VS... > >::
                       is_integral_sequence,
                     "Invalid type used. Only integral sequence types are "
                     "allowed." );

      /**
       * \brief Exposes the empty sequence as is
       */
      using type = S< U, VS... >;
    };

  /**
   * \brief Specialization working with a integral sequence that contains only
   * one element. There is nothing to sort in a one element integral sequence
   *
   * \tparam S integral sequence template
   * \tparam T the integral type used in the integral sequence
   * \tparam V the unique element in the integral sequence
   * \tparam P the predicate template (not verified here as not used)
   * \tparam TS type pack used in the predicate as arguments
   */
  template
    <
      template< class T, T... > class S, class U, U V,
      template< class W, W, class... > class P, class... TS
    >
    struct sort_integral_sequence_impl< S< U, V >, P, TS... >
    {
      static_assert( warp::meta_sequence_traits< S< U, V > >::
                       is_integral_sequence,
                     "Invalid type used. Only integral sequence types are "
                     "allowed." );

      /**
       * \brief Nothing to do there is only one element in the sequence.
       */
      using type = S< U, V >;
    };

  /**
   * \brief Specialization working with a integral sequence containing 2 or more
   * elements within. This is the really functionnal specialization, testing
   * traits of the integral sequence and the predicate as it'll be used.
   *
   * \tparam S integral sequence template
   * \tparam U the integral type used in the sequence
   * \tparam V the first element in the integral sequence
   * \tparam W the second element in the integral sequence
   * \tparam VS remaining integrals in the sequence
   * \tparam P the predicate template (not verified here as not used)
   * \tparam TS type pack used in the predicate as arguments
   */
  template
    <
      template< class T, T... > class S, class U, U V, U W, U... VS,
      template< class X, X, class... > class P, class... TS
    >
    struct sort_integral_sequence_impl< S< U, V, W, VS... >, P, TS... >
    {
      static_assert( warp::meta_sequence_traits< S< U, V, W, VS... > >::
                       is_integral_sequence,
                     "Invalid type used. Only integral sequence types are "
                     "allowed." );

      static_assert( warp::meta_predicate_traits< P< U, V, TS... > >::
                       is_integral_sequence_predicate,
                     "Invalid type used. Only integral sequence predicates are "
                     "allowed." );

      /**
       * \brief The sorter template is the one that will perform the sort
       * operation several times. It will sort using the bubble sort algorithm.
       *
       * \tparam C_ the number of sort operation to perform, will decrease by
       * one each time the full sequence has been sorted. When reaches 0, the
       * sort is terminated.
       * \tparam S_ the sequence to sort
       * \tparam P_ the predicate used to sort
       * \tparam T_ a type sequence that contains the predicate arguments
       * \tparam U_ an integral sequence that contains the in-progress sorted
       * values
       */
      template
        <
          std::size_t C_,
          class S_,
          template< class T, T, class... > class P_,
          class T_, class U_
        >
        struct sorter;

      /**
       * \brief Specialization of the sorter, working with a provided integral
       * sequence currently in-sorting and containing more than 2 values.
       *
       * \tparam C_ the number of sort operation to perform, will decrease by
       * one each time the full sequence has been sorted. When reaches 0, the
       * sort is terminated.
       * \tparam S_ the sequence template to sort
       * \tparam U_ the integral type used in the integral sequence
       * \tparam V_ the first element of the sequence
       * \tparam W_ the second element of the sequence
       * \tparam VS_ remaining element in the sequence to sort
       * \tparam P_ the predicate used to sort
       * \tparam US_ a type pack used in the integral sequence containing
       * predicate arguments
       * \tparam WS_ a integral pack used in the sequence containing sorted
       * elements
       */
      template
        <
          std::size_t C_,
          template< class T_, T_... > class S_,
          class U_, U_ V_, U_ W_, U_... VS_,
          template< class X_, X_, class... > class P_,
          class... US_, U_... WS_
        >
        struct sorter
        <
          C_,
          S_< U_, V_, W_, VS_... >,
          P_,
          warp::type_sequence< US_... >, warp::integral_sequence< U_, WS_... >
        >
        {
          /**
           * \brief Create a pure value type as it is a standard way to act for
           * warp. This pure value type exposes a static constexpr method
           * names value returning a constant expression value
           */
          struct W_value{ static constexpr auto value() { return W_; } };

          /**
           * \brief Use the predicate and build the next input sequence to be
           * sorted, keeping only the integral that doesn't match the predicate
           * and the next ones
           */
          using popped_input_sequence =
            std::conditional_t
            <
              P_< U_, V_, W_value, US_... >::value,
              S_< U_, W_, VS_... >,
              S_< U_, V_, VS_... >
            >;

          /**
           * \brief Consolidate the output integral sequence by adding at last
           * the integral that matches the predicate
           */
          using sorted_out_sequence =
            std::conditional_t
            <
              P_< U_, V_, W_value, US_... >::value,
              warp::integral_sequence< U_, WS_..., V_ >,
              warp::integral_sequence< U_, WS_..., W_ >
            >;

          /**
           * \brief Recursive usage of the sorter, using calculated above
           * sequences as input and output
           */
          using type =
            typename sorter
            <
              // keep the same counter value
              C_,
              // input sequence with the matching integral popped out
              popped_input_sequence,
              P_,
              warp::type_sequence< US_... >,
              // output sequence appended with the integral matching the
              // predicate
              sorted_out_sequence
            >::type;
        };

      /**
       * \brief Specialization used when the sequence to sort contains exactly 2
       * elements. It means that a sort iteration has finished and that the
       * counter will be decreased. Note that if the counter reach 0, the sort
       * is done
       *
       * \tparam C_ the number of sort operation to perform, will decrease by
       * one each time the full sequence has been sorted. When reaches 0, the
       * sort is terminated.
       * \tparam S_ the sequence template to sort
       * \tparam U_ the integral type used in the sequence
       * \tparam V_ the first element of the sequence
       * \tparam W_ the second element of the sequence
       * \tparam P_ the predicate used to sort
       * \tparam TS_ a type pack used in the integral sequence containing
       * predicate arguments
       * \tparam VS_ a integral pack used in the sequence containing sorted
       * elements
       */
      template
        <
          std::size_t C_,
          template< class T_, T_... > class S_, class U_, U_ V_, U_ W_,
          template< class X_, X_, class... > class P_,
          class... TS_, U_... VS_
        >
        struct sorter
        <
          C_,
          S_< U_, V_, W_ >,
          P_,
          warp::type_sequence< TS_... >, warp::integral_sequence< U_, VS_... >
        >
        {
          /**
           * \brief Create a pure value type as it is a standard way to act for
           * warp. This pure value type exposes a static constexpr method
           * names value returning a constant expression value
           */
          struct W_value{ static constexpr auto value() { return W_; } };

          /**
           * \brief First, sort the 2 elements and add them to the sorted
           * sequence according to the predicate. Uses the sequence template
           * provided by the user
           */
          using sorted_sequence =
            std::conditional_t
            <
              P< U_, V_, W_value, TS_... >::value,
              S_< U_, VS_..., V_, W_ >,
              S_< U_, VS_..., W_, V_ >
            >;

          /**
           * \brief Recursive use of sorter, decreasing counter value by one,
           * switching the sorted sequence content to be used as input with the
           * provided sequence template
           */
          using type =
            typename sorter
            <
              // one sort iteration terminated
              C_ - 1,
              // sorted sequence is used here
              sorted_sequence,
              P_,
              warp::type_sequence< TS_... >,
              // the variadic pump is now empty, ready for the next iteration
              warp::integral_sequence< U_ >
            >::type;
        };

      /**
       * \brief Specialization of the sorter when the counter reaches 0.Sort is
       * considered as done here, ends all recursion, don't use the predicate
       * anymore and exposes a integral sequence that is fully sorted
       *
       * \tparam S_ the sequence template to sort
       * \tparam U_ integral type used in the integral sequence
       * \tparam V_ first integral in the sequence
       * \tparam W_ second integral in the sequence
       * \tparam VS_ integral pack used in the sequence template above,
       * completely sorted here
       * \tparam P_ the predicate used to sort
       * \tparam TS_ type pack, arguments of the predicate
       */
      template
        <
          template< class T, T... > class S_, class U_, U_ V_, U_ W_, U_... VS_,
          template< class X, X, class... > class P_,
          class... TS_
        >
        struct sorter
        <
          0,
          S_< U_, V_, W_, VS_... >,
          P_,
          warp::type_sequence< TS_... >, warp::integral_sequence< U_ >
        >
        {
          /**
           * \brief Exposes the sorted sequence, using the sequence template
           * provided by the user that has been switched with the variadic pump
           * when the counter has been decreased (see above specialization)
           */
          using type = S< U_, V_, W_, VS_... >;
        };

      /**
       * \brief Uses the sorter integral, it will perform a bubble sort
       */
      using type =
        typename sorter
        <
          // serves as counter for sorts operation, length of sequence - 1
          sizeof...( VS ) + 1,
          // forward template arguments
          S< U, V, W, VS... >, P,
          // embbeds predicate arguments in a sequence to...
          warp::type_sequence< TS... >,
          // ...allow usage of a variadic pump for sorted integrals
          warp::integral_sequence< U >
        >::type;
    };

  /**
   * \brief Hidden implementation of the partion feature for a type sequence.
   * Unspecialized here, instantiated when T is not a valid type sequence type.
   *
   * \tparam S Any type but a valid type sequence
   */
  template< class S, template< class, class... > class, class, class, class >
    struct partition_type_sequence_impl
    {
      static_assert( warp::meta_sequence_traits< S >::is_type_sequence,
                     "Invalid type used. Only type sequence types are "
                     "allowed." );
    };

  /**
   * \brief Specialization used with a valid type sequence that is empty. Check
   * the type sequence type.
   *
   * \tparam S type sequence template
   * \tparam TS type pack used in the type sequence, empty here
   * \tparam P predicate template
   * \tparam US type pack used as argument of the predicate template
   * \tparam VS type pack containing types matching the predicate
   * \tparam WS type pack containing types that don't match the predicate
   */
  template
    <
      template< class... > class S, class... TS,
      template< class, class... > class P, class... US,
      class... VS, class... WS
    >
    struct partition_type_sequence_impl
    <
      S< TS... >, P, warp::type_sequence< US... >,
      warp::type_sequence< VS... >, warp::type_sequence< WS... >
    >
    {
      static_assert( warp::meta_sequence_traits< S< TS... > >::is_type_sequence,
                     "Invalid type used. Only type sequence types are "
                     "allowed." );

      /**
       * \brief The type sequence is empty, either provided by the user or
       * emptied by a recursive process. Exposes a type sequence containing
       * types that match predicate first followed by type that don't match.
       * Relative order of type is preserved.
       */
      using type = S< VS..., WS... >;
    };

  /**
   * \brief Specialization used with a valid type sequence that contains at
   * least one type . Check the type sequence type and the predicate.
   *
   * \tparam S type sequence template
   * \tparam T the first type in the sequence
   * \tparam TS type pack used in the type sequence, empty here
   * \tparam P predicate template
   * \tparam US type pack used as argument of the predicate template
   * \tparam VS type pack containing types matching the predicate
   * \tparam WS type pack containing types that don't match the predicate
   */
  template
    <
      template< class... > class S, class T, class... TS,
      template< class, class... > class P, class... US,
      class... VS, class... WS
    >
    struct partition_type_sequence_impl
    <
      S< T, TS... >, P, warp::type_sequence< US... >,
      warp::type_sequence< VS... >, warp::type_sequence< WS... >
    >
    {
      static_assert( warp::meta_sequence_traits< S< T, TS... > >::
                       is_type_sequence,
                     "Invalid type used. Only type sequence types are "
                     "allowed." );

      static_assert( warp::meta_predicate_traits< P< T, US... > >::
                       is_type_sequence_predicate,
                     "Invalid type used. Only type sequence predicates are "
                     "allowed." );

      /**
       * \brief Exposes a type that is conditionally determined regarding the
       * predicate result with the first type of the sequence
       */
      using type =
        std::conditional_t
        <
          P< T, US... >::value,
          // predicate is verified, T is appended to the first type sequence
          typename partition_type_sequence_impl
            <
              S< TS... >, P, warp::type_sequence< US... >,
              warp::type_sequence< VS..., T >, warp::type_sequence< WS... >
            >::type,
          // predicate is not verified, T is appended to the last type sequence
          typename partition_type_sequence_impl
            <
              S< TS... >, P, warp::type_sequence< US... >,
              warp::type_sequence< VS... >, warp::type_sequence< WS..., T >
            >::type
        >;
    };

  /**
   * \brief Unspecialized version of the partition algorithm for integral
   * sequence. Used when any type but a valid integral sequence is specified.
   *
   * \tparam T any type but a valid integral sequence type
   */
  template
    < class T, template< class U, U, class... > class, class, class, class >
    struct partition_integral_sequence_impl
    {
      static_assert( warp::meta_sequence_traits< T >::
                       is_integral_sequence,
                     "Invalid type used. Only integral sequence types are "
                     "allowed." );
    };

  /**
   * \brief Specialized version working with an integral sequence that is empty.
   * A check is made on the provided integral sequence type.
   *
   * \tparam S integral sequence template
   * \tparam U integral type used in the integral sequence
   * \tparam VS empty value pack of the integral sequence
   * \tparam P predicate template
   * \tparam TS type pack used for the predicate and embedded inside a type
   * sequence
   * \tparam V integral type used in embedding sequence containing partitionned
   * values
   * \tparam WS value pack grouping values that match the predicate
   * \tparam XS value pack grouping value that don't match the predicate
   */
  template
    <
      template< class T, T... > class S, class U, U... VS,
      template< class V, V, class... > class P, class...TS,
      class V, V... WS, V... XS
    >
    struct partition_integral_sequence_impl
    <
      S< U, VS... >, P, warp::type_sequence< TS... >,
      warp::integral_sequence< V, WS... >, warp::integral_sequence< V, XS... >
    >
    {
      static_assert( warp::meta_sequence_traits< S< U, VS... > >::
                       is_integral_sequence,
                     "Invalid type used. Only integral sequence types are "
                     "allowed." );

      /**
       * \brief Empty sequence provided, concatenate partitionned values, first
       * those matching the predicate, then those that don't match; preserve
       * relative order of the initial sequence
       */
      using type = S< U, WS..., XS... >;
    };

  /**
   * \brief Specialized version working with an integral sequence that has at
   * least one element.  A check is made on the provided integral sequence type
   * and the predicate as well.
   *
   * \tparam S integral sequence template
   * \tparam U integral type used in the integral sequence
   * \tparam V the first value in the integral sequence
   * \tparam VS empty value pack of the integral sequence
   * \tparam P predicate template
   * \tparam TS type pack used for the predicate and embedded inside a type
   * sequence
   * \tparam X integral type used in embedding sequence containing partitionned
   * values
   * \tparam WS value pack grouping values that match the predicate
   * \tparam XS value pack grouping value that don't match the predicate
   */
  template
    <
      template< class T, T... > class S, class U, U V, U... VS,
      template< class W, W, class... > class P, class...TS,
      class X, X... WS, X... XS
    >
    struct partition_integral_sequence_impl
    <
      S< U, V, VS... >, P, warp::type_sequence< TS... >,
      warp::integral_sequence< X, WS... >, warp::integral_sequence< X, XS... >
    >
    {
      static_assert( warp::meta_sequence_traits< S< U, V, VS... > >::
                       is_integral_sequence,
                     "Invalid type used. Only integral sequence types are "
                     "allowed." );

      static_assert( warp::meta_predicate_traits< P< U, V, TS... > >::
                       is_integral_sequence_predicate,
                     "Invalid type used. Only integral sequence predicates are "
                     "allowed." );

      /**
       * \brief Recursively exposes the sequence, partially partitionned
       * regarding the predicate matching for V
       */
      using type =
        std::conditional_t
        <
          P< U, V, TS... >::value,
          // predicate matched -> V in the first sequence
          typename partition_integral_sequence_impl
            <
              S< U, VS... >, P, warp::type_sequence< TS... >,
              warp::integral_sequence< U, WS..., V >,
              warp::integral_sequence< U, XS... >
            >::type,
          // predicate not matched -> V in the last sequence
          typename partition_integral_sequence_impl
            <
              S< U, VS... >, P, warp::type_sequence< TS... >,
              warp::integral_sequence< U, WS... >,
              warp::integral_sequence< U, XS..., V >
            >::type
        >;
    };

  /**
   * \brief Feature removing duplicate inside a type sequence. Non defined
   * unspecialized version
   */
  template< class, class >
    struct unique_type_sequence;

  /**
   * \brief This specialized version removes duplicated elements inside an empty
   * type sequence, aka does nothing but expose the pump content
   *
   * \tparam S type sequence template
   * \tparam TS type pack (empty) of the type sequence
   * \tparam US type pack containing uniqued elements from the specified type
   * sequence
   */
  template< template< class... > class S, class... TS, class... US >
    struct unique_type_sequence< S< TS... >, warp::type_sequence< US... > >
    {
      /**
       * \brief Simply exposes the pump content, that doesn't contain any
       * duplicated element
       */
      using type = S< US... >;
    };

  /**
   * \brief Specialization working with a type sequence containing at least one
   * element
   *
   * \tparam S type sequence template
   * \tparam T the first type in the sequence
   * \tparam TS type pack of the type sequence representing remaining elements
   * \tparam US type pack containing uniqued elements from the specified type
   * sequence
   */
  template< template< class... > class S, class T, class... TS, class... US >
    struct unique_type_sequence< S< T, TS... >, warp::type_sequence< US... > >
    {
      /**
       * \brief Recursively push element after made sure that there is no
       * duplicate in the pump
       */
      using type =
        // recursively...
        typename unique_type_sequence
        <
          S< TS... >,
          // push the currently explore element...
          typename push_back_on_impl
            <
              // after have removed its potential presence in the pump
              typename remove_all_in_type_sequence_impl
                <
                  warp::type_sequence< US... >,
                  std::is_same,
                  warp::type_sequence< T >, warp::type_sequence<>
                >::type,
              T
            >::type
        >::type;
    };

  /**
   * \brief Declaration of the feature removing duplicates in an integral
   * sequence
   */
  template< class, class >
    struct unique_integral_sequence;

  /**
   * \brief This specialized version removes duplicated elements inside an empty
   * integral sequence, aka does nothing but expose the pump content
   *
   * \tparam S integral sequence template
   * \tparam U integral type used in the integral sequence
   * \tparam VS integral pack (empty) of the integral sequence
   * \tparam WS integral pack containing uniqued elements from the specified
   * integral sequence
   */
  template< template< class T, T... > class S, class U, U...VS, U... WS >
    struct unique_integral_sequence
    < S< U, VS... >, warp::integral_sequence< U, WS... > >
    {
      /**
       * \brief Simply exposes the pump content
       */
      using type = S< U, WS... >;
    };

  /**
   * \brief Specialization working with a integral sequence containing at least
   * one element
   *
   * \tparam S integral sequence template
   * \tparam U the integral type used in the sequence
   * \tparam V the first integral in the sequence
   * \tparam VS integral pack of the integral sequence representing remaining
   * elements
   * \tparam WS integral pack containing uniqued elements from the specified
   * integral sequence
   */
  template< template< class T, T... > class S, class U, U V, U...VS, U... WS >
    struct unique_integral_sequence
    < S< U, V, VS... >, warp::integral_sequence< U, WS... > >
    {
      /**
       * \brief Value-type simply returning V value, suits well for predicate
       * usage
       */
      struct V_value
      {
        /**
         * \brief The value method return a constant expression
         *
         * \return THe value of V
         */
        static constexpr auto value() { return V; } 
      };

      /**
       * \brief Predicate looking for an equality between 2 values in an
       * integral sequence
       *
       * \tparam T integral type used
       * \tparam W the currently explored value in the iterated integral
       * sequence
       * \tparam X value type exposing a value to compare with
       */
      template< class T, T W, class X >
        struct is_equal_to
        {
          /**
           * \brief Equality check
           */
          static constexpr auto value = ( W == X::value() );
        };

      /**
       * \brief Recursively push the current element after have removed
       * duplicated value inside the pump
       */
      using type =
        // recursively...
        typename unique_integral_sequence
        <
          S< U, VS... >,
          // push values...
          typename push_back_on_impl
            <
              // after have removed dulpicated values...
              typename remove_all_in_integral_sequence_impl
                <
                  // in the pump
                  warp::integral_sequence< U, WS... >,
                  is_equal_to,
                  warp::type_sequence< V_value >, warp::integral_sequence< U >
                >::type,
              U, V
            >::type
        >::type;
    };

  /**
   * \brief Hidden implementation of the unique feature. This unspecialized
   * version is used if an invalid meta sequence type is specified
   *
   * \tparam T any type but a valid meta sequence type
   */
  template< class T >
    struct unique_on_impl
    {
      static_assert( warp::meta_sequence_traits< T >::is_meta_sequence,
                     "Invalid type used. Only meta sequence types are "
                     "allowed." );
    };

  /**
   * \brief Specialization working with a type sequence. Forward to a more
   * specific featuer dealing exclusively with type sequences.
   *
   * \tparam S type sequence template
   * \tparam TS... type pack used in the type sequence
   */
  template< template< class... > class S, class... TS >
    struct unique_on_impl< S< TS... > >
    {
      static_assert( warp::meta_sequence_traits< S< TS... > >::is_type_sequence,
                     "Invalid type used. Only type sequence types are "
                     "allowed." );

      /**
       * \brief Relies on a more specific feature, passing an empty  variadic
       * pump
       */
      using type =
        typename unique_type_sequence
        < S< TS... >, warp::type_sequence<> >::type;
    };

  /**
   * \brief Specialization working with an integral sequence. Forward to a more
   * specific featuer dealing exclusively with integral sequences.
   *
   * \tparam S integral sequence template
   * \tparam U integral type used in the integral sequence
   * \tparam VS... integral pack used in the integral sequence
   */
  template< template< class T, T... > class S, class U, U... VS >
    struct unique_on_impl< S< U, VS... > >
    {
      static_assert( warp::meta_sequence_traits< S< U, VS... > >::
                       is_integral_sequence,
                     "Invalid type used. Only integral sequence types are "
                     "allowed." );

      /**
       * \brief Relies on a more specific feature, passing an empty  variadic
       * pump
       */
      using type =
        typename unique_integral_sequence
        < S< U, VS... >, warp::integral_sequence< U > >::type;
    };

  /**
   * \brief Declaration of the unspecialized hidden generate feature for an
   * integral sequence
   *
   * \tparam C the counter indicating how many time the generator has to be used
   * \tparam S the output integral sequence
   * \tparam the generator type
   */
  template< std::size_t C, class S, class G >
    struct generate_integral_sequence_impl;

  /**
   * \brief Specialization working when it remains one or more generation to be
   * performed. Makes use of the generator and push a generated value in hte
   * output sequence
   *
   * \tparam C the counter indicating how many time the generator has to be used
   * \tparam S integral sequence template
   * \tparam U integral type used in the output integral sequence
   * \tparam VS value pack used in the output integral sequence
   * \tparam G the generator template
   * \tparam TS type pack used as arguments in the generator template
   */
  template
    <
      std::size_t C, template< class T, T... > class S, class U, U... VS,
      template< class... > class G, class... TS
    >
    struct generate_integral_sequence_impl< C, S< U, VS... >, G< TS... > >
    {
      static_assert( warp::meta_generator_traits< G< TS... > >::
                       is_integral_sequence_generator,
                     "Invalid type used. Only integral sequence generators are "
                     "allowed." );

      /**
       * \brief Alias on the instantiation of the generator
       */
      using generator = G< TS... >;

      /**
       * \brief Extracts the generated value from the generator
       */
      static constexpr auto value = generator::value;

      /**
       * \brief Deduces the generated value integral type
       */
      using value_type = decltype( value );

      /**
       * \brief Get the next generator type for the next generation
       */
      using next_generator = typename generator::next;

      /**
       * \brief Recursively exposes the final output of generated values
       */
      using type =
        typename generate_integral_sequence_impl
        < C - 1, S< value_type, VS..., value >, next_generator >::type;
    };

  /**
   * \brief Specialization working when it doesn't remain any generation to be
   * performed. Only exposes the generated value sequence.
   *
   * \tparam S integral sequence template
   * \tparam U integral type used in the output integral sequence
   * \tparam VS value pack used in the output integral sequence
   * \tparam G the generator template
   * \tparam TS type pack used as arguments in the generator template
   */
  template
    <
      template< class T, T... > class S, class U, U... VS,
      template< class... > class G, class... TS
    >
    struct generate_integral_sequence_impl< 0, S< U, VS... >, G< TS... > >
    {
      static_assert( warp::meta_generator_traits< G< TS... > >::
                       is_integral_sequence_generator,
                     "Invalid type used. Only integral sequence generators are "
                     "allowed." );

      /**
       * \brief Siply exposes the sequence
       */
      using type = S< U, VS... >;
    };

  /**
   * \brief Unspecialized version chosen if S is not a valid integral sequence
   *
   * \tparam S any type but a valid integral sequence
   * \tparam B type containing a char buffer
   */
  template< class S, class B >
    struct append_char_buffer_in_impl
    {
      static_assert( warp::meta_sequence_traits< S >::
                       is_integral_sequence,
                     "Invalid type used. Only integral sequence types are "
                     "allowed." );
    };

  /**
   * \brief Dispatcher used after all checks have been made on the specified
   * buffer value-type. The corresponding specialization is used depending on
   * the type of B::value
   */
  template< class, class, class = warp::sfinae_type_t<> >
    struct dispatch_from_value_type;

  /**
   * \brief Utility used to unify how to access a char buffer from a type. The
   * purpose is to have in all case a static constexpr function to access a
   * buffer
   *
   * \tparam B a type containing a value char buffer member
   */
  template< class B >
    struct value_char_buffer
    {
      /**
       * \brief Function using B's member
       *
       * \return the buffer hold by B::value
       */
      static constexpr auto content() { return B::value; };
    };

  /**
   * \brief Utility used to unify how to access a char buffer from a type. The
   * purpose is to have in all case a static constexpr function to access a
   * buffer
   *
   * \tparam B a type containing a value char buffer returning method
   */
  template< class B >
    struct function_char_buffer
    {
      /**
       * \brief Function using B's method
       *
       * \return the buffer returned by a B::value() call
       */
      static constexpr auto content() { return B::value(); };
    };

  /**
   * \brief Utility function calculating a null-terminated buffer size.
   *
   * \tparam B either value_char_buffer or function_char_buffer type exposing a
   * static method name content, returning the char buffer
   *
   * \param current the current sized determined. Recursively calculated.
   *
   * \return the size of the buffer
   */
  template< class B >
    constexpr std::size_t char_buffer_size( std::size_t current = 0 )
    {
      // recursively seek for a terminating null-char
      return
        B::content()[ current ] == '\0' ?
        current :
        char_buffer_size< B >( current + 1 );
    }

  /**
   * \brief The appending feature real implementation.
   *
   * \tparam S the integral sequence in which append a char buffer
   * \tparam B a buffer type containing a value method to access the content of
   * the char buffer to append
   * \tparam N the size of the buffer to append
   */
  template< class S, class B, std::size_t N >
    struct dispatched_appending_in;

  /**
   * \brief Specialization used with an integral sequence and a buffer partially
   * explored
   *
   * \tparam S the sequence template
   * \tparam U the integral type used in the sequence
   * \tparam VS integral value pack in the sequence
   * \tparam B a buffer type containing a value method to access the content of
   * the char buffer to append
   * \tparam N the size of the buffer to explore
   */
  template
    <
      template< class T, T... > class S, class U, U... VS,
      class B, std::size_t N
    >
    struct dispatched_appending_in< S< U, VS... >, B, N >
    {
      /**
       * \brief Buffer is explored in reverse order, calculating the current
       * index here
       */
      static constexpr auto index = char_buffer_size< B >() - N;

      /**
       * \brief recursively use the feature, appending a char from the buffer
       */
      using type =
        typename dispatched_appending_in
        < S< U, VS..., B::content()[ index ] >, B, N - 1 >::type;
    };

  /**
   * \brief Specialization used with an integral sequence and a buffer totally
   * explored
   *
   * \tparam S the sequence template
   * \tparam U the integral type used in the sequence
   * \tparam VS integral value pack in the sequence
   * \tparam B a buffer type containing a value method to access the content of
   * the char buffer to append
   */
  template
    <
      template< class T, T... > class S, class U, U... VS,
      class B
    >
    struct dispatched_appending_in< S< U, VS... >, B, 0 >
    {
      /**
       * \brief appending is finished here
       */
      using type = S< U, VS... >;
    };

  /**
   * \brief Specialization used when B::value is a member which the type is a
   * char buffer.
   *
   * \tparam S the integral sequence template
   * \tparam U integral type used in the integral sequence
   * \tparam VS integral values used in the sequence
   * \tparam B a type containing a static char buffer name value
   */
  template< template< class T, T... > class S, class U, U... VS, class B >
    struct dispatch_from_value_type
    <
      S< U, VS... >, B,
      warp::sfinae_type_t
        <
          // B::value is valid in all case once it exists in B. Ensure
          // expression correctness thanks to enable_if usage. here I know there
          // is one of the 2 valid solution to check
          std::enable_if_t
            < warp::is_char_buffer< decltype( B::value ) >::value >
        >
    >
    {
      /**
       * \brief Transfer work to another type, indicating how to read the buffer
       * hold in B
       */
      using type =
        typename dispatched_appending_in
        <
          S< U, VS... >, value_char_buffer< B >,
          char_buffer_size< value_char_buffer< B > >()
        >::type;
    };

  /**
   * \brief Specialization used when B::value is a method which the returning
   * type is a char buffer.
   *
   * \tparam S the integral sequence template
   * \tparam U integral type used in the integral sequence
   * \tparam VS integral values used in the sequence
   * \tparam B a type containing a static method returning a char buffer
   */
  template< template< class T, T... > class S, class U, U... VS, class B >
    struct dispatch_from_value_type
    <
      S< U, VS... >, B,
      // this sfinae expression is correct if B::value is a function only
      warp::sfinae_type_t< decltype( B::value() ) >
    >
    {
      /**
       * \brief Transfer work to another type, indicating how to read the buffer
       * hold in B
       */
      using type = 
        typename dispatched_appending_in
        <
          S< U, VS... >, function_char_buffer< B >,
          char_buffer_size< function_char_buffer< B > >()
        >::type;
    };

  /**
   * \brief Specialization triggered when used with a type matching a valid
   * integral sequence predicate
   *
   * \tparam S integral sequence template
   * \tparam U integral type used in the integral sequence
   * \tparam VS integral value pack used in the integral sequence
   * \tparam B the char buffer embedded in a value-type
   */
  template
    <
      template< class T, T... > class S, class U, U... VS,
      class B
    >
    struct append_char_buffer_in_impl< S< U, VS... >, B >
    {
      static_assert( warp::meta_sequence_traits< S< U, VS... > >::
                       is_integral_sequence,
                     "Invalid type used. Only integral sequence types are "
                     "allowed." );

      static_assert( warp::meta_sequence_operands_traits< B >::
                       is_char_buffer_value_type,
                     "Invalid type used. Only char buffer value types are "
                     "allowed." );

      /**
       * \brief Using an internal feature, dispatching the work regarding the
       * type of value that could be a static member or a static method.
       */
      using type = typename dispatch_from_value_type< S< U, VS... >, B >::type;
    };

  /**
   * \brief Internal feature used by the hidden implementation of for each
   * algorithm for both integral and type sequence. Non specialized version only
   * declared.
   */
  template< class, class >
    struct apply_functor_on;

  /**
   * \brief Specialization used on a type sequence that is not empty
   *
   * \tparam S type sequence template
   * \tparam T the first type in the sequence
   * \tparam TS type pack, remaining types in sequence
   * \tparam F user-defined validated functor template
   * \tparam U a type used in functor instantiation, previsously contained in
   * the iterated type sequence
   * \tparam US type pack used as functor arguments
   */
  template
    <
      template< class... > class S, class T, class... TS,
      template< class, class... > class F, class U, class... US
    >
    struct apply_functor_on< S< T, TS... >, F< U, US... > >
    {
      /**
       * \brief Recursively apply functor on remaining types in the sequence,
       * using the 'next' type hold in the functor and passing the currently
       * explored type to it.
       */
      using type =
        typename apply_functor_on
        < S< TS... >, typename F< T, US... >::next >::type;
    };

  /**
   * \brief Specialization used on a type sequence that is empty
   *
   * \tparam S type sequence template
   * \tparam F user-defined validated functor template
   * \tparam U a type used in functor instantiation, previsously contained in
   * the iterated type sequence
   * \tparam US type pack used as functor arguments
   */
  template
    <
      template< class... > class S,
      template< class, class... > class F, class U, class... US
    >
    struct apply_functor_on< S<>, F< U, US... > >
    {
      /**
       * \brief Exposes the functor instantiation as is
       */
      using type = F< U, US... >;
    };

  /**
   * \brief Specialization used on an integral sequence that is not empty
   *
   * \tparam S type sequence template
   * \tparam U integral type used in the sequence
   * \tparam V the first value in the sequence
   * \tparam VS value pack, remaining values in sequence
   * \tparam F user-defined validated functor template
   * \tparam X a value used in functor instantiation, previsously contained in
   * the iterated integral sequence
   * \tparam TS type pack used as functor arguments
   */
  template
    <
      template< class T, T... > class S, class U, U V, U... VS,
      template< class W, W, class... > class F, U X, class... TS
    >
    struct apply_functor_on< S< U, V, VS... >, F< U, X, TS... > >
    {
      /**
       * \brief Recursively apply functor on remaining values in the sequence,
       * using the 'next' type hold in the functor and passing the currently
       * explored value to it.
       */
      using type =
        typename apply_functor_on
        < S< U, VS... >, typename F< U, V, TS... >::next >::type;
    };

  /**
   * \brief Specialization used on an integral sequence that is empty
   *
   * \tparam S type sequence template
   * \tparam U integral type used in that sequence
   * \tparam F user-defined validated functor template
   * \tparam V a value used in functor instantiation, previsously contained in
   * the iterated type sequence
   * \tparam TS type pack used as functor arguments
   */
  template
    <
      template< class T, T... > class S, class U,
      template< class W, W, class... > class F, U V, class... TS
    >
    struct apply_functor_on< S< U >, F< U, V, TS... > >
    {
      /**
       * \brief Exposes the functor instantiation as is
       */
      using type = F< U, V, TS... >;
    };

  /**
   * \brief Hidden feature used in the visible implementation of for each for
   * type sequences. This non specialized version is used if S if not a valid
   * type sequence and display an understandable error message
   *
   * \tparam S any type but a valid type sequence
   * \tparam F the functor template to apply on a valid type sequence
   * \tparam TS type pack used as functor arguments
   */
  template< class S, template< class, class... > class F, class... TS >
    struct for_each_type_in_impl
    {
      static_assert( warp::meta_sequence_traits< S >::is_type_sequence,
                     "Invalid type used. Only type sequence types are "
                     "allowed." );
    };

  /**
   * \brief Specialization of the for each feature for type sequence that is
   * empty. It is an invalid operation and display an understandable error
   * message at compile time. Indeed, it is impossible to instantiate the
   * functor template with an empty sequence
   *
   * \tparam S type sequence template
   * \tparam TS type pack (empty) hold by the type sequence
   * \tparam F functor used
   * \tparam US type pack used as functor arguments
   */
  template
    <
      template< class... > class S,
      template< class, class... > class F, class... US
    >
    struct for_each_type_in_impl< S<>, F, US... >
    {
      static_assert( warp::meta_sequence_traits< S<> >::is_type_sequence,
                     "Invalid type used. Only type sequence types are "
                     "allowed." );

      static_assert( ! warp::meta_sequence_traits< S<> >::is_empty,
                     "Invalid type used. Only non empty type sequence types "
                     "are allowed."
                     );
    };

  /**
   * \brief Specialization triggered when used with a type sequence containing
   * at least one type.
   *
   * \tparam S type sequence template
   * \tparam T the first type in the sequence
   * \tparam TS type pack (may be empty) hold by the type sequence after T
   * \tparam F functor used
   * \tparam US type pack used as functor arguments
   */
  template
    <
      template< class... > class S, class T, class... TS,
      template< class, class... > class F, class... US
    >
    struct for_each_type_in_impl< S< T, TS... >, F, US... >
    {
      static_assert( warp::meta_sequence_traits< S< T, TS... > >::
                       is_type_sequence,
                     "Invalid type used. Only type sequence types are "
                     "allowed." );

      static_assert( warp::meta_functor_traits< F< T, US... > >::
                       is_type_sequence_functor,
                     "Invalid type used. Only type sequence functors are "
                     "allowed." );

      /**
       * \brief instantiate the functor template with the currently explored
       * type.
       */
      using functor = F< T, US... >;

      /**
       * \brief Apply the instantiated functor on the currently explored type
       * and continue to unfold the entire sequence
       */
      using type = typename apply_functor_on< S< T, TS... >, functor >::type;
    };

  /**
   * \brief Hidden feature used in the visible implementation of for each for
   * integral sequences. This non specialized version is used if S if not a
   * valid integral sequence and display an understandable error message
   *
   * \tparam S any integral but a valid integral sequence
   * \tparam F the functor template to apply on a valid integral sequence
   * \tparam TS integral pack used as functor arguments
   */
  template< class S, template< class T, T V, class... > class F, class... TS >
    struct for_each_value_in_impl
    {
      static_assert( warp::meta_sequence_traits< S >::
                       is_integral_sequence,
                     "Invalid type used. Only integral sequence types are "
                     "allowed." );
    };

  /**
   * \brief Specialization of the for each feature for integral sequence that is
   * empty. It is invalid to use for each on an empty sequence because it's
   * impossible to isntantiate the functor template with no element to iterate
   * on.
   *
   * \tparam S integral sequence template
   * \tparam U the integral type used in the sequence template
   * \tparam VS integral pack (empty) hold by the integral sequence
   * \tparam F functor used
   * \tparam US type pack used as functor arguments
   */
  template
    <
      template< class T, T...VS > class S, class U,
      template< class V, V, class... > class F, class... TS
    >
    struct for_each_value_in_impl< S< U >, F, TS... >
    {
      static_assert( warp::meta_sequence_traits< S< U > >::
                       is_integral_sequence,
                     "Invalid type used. Only integral sequence types are "
                     "allowed." );

      static_assert( warp::meta_sequence_traits< S< U > >::
                       is_empty,
                     "Invalid type used. Only non empty integral sequence "
                     "types are allowed.");
    };

  /**
   * \brief Specialization triggered when used with an integral sequence
   * containing at least one type.
   *
   * \tparam S type sequence template
   * \tparam U integral type used in the integral sequence
   * \tparam V the first value in the sequence
   * \tparam VS value pack (may be empty) hold by the type sequence after V
   * \tparam F functor used
   * \tparam US type pack used as functor arguments
   */
  template
    <
      template< class T, T...VS > class S, class U, U V, U... VS,
      template< class W, W, class... > class F, class... TS
    >
    struct for_each_value_in_impl< S< U, V, VS... >, F, TS... >
    {
      static_assert( warp::meta_sequence_traits< S< U, V, VS... > >::
                       is_integral_sequence,
                     "Invalid type used. Only integral sequence types are "
                     "allowed." );

      static_assert( warp::meta_functor_traits< F< U, V, TS... > >::
                       is_integral_sequence_functor,
                     "Invalid type used. Only integral sequence functors are "
                     "allowed." );

      /**
       * \brief instantiate the functor template with the currently explored
       * value.
       */
      using functor = F< U, V, TS... >;

      /**
       * \brief Apply the instantiated functor on the currently explored value
       * and continue to unfold the entire sequence
       */
      using type = typename apply_functor_on< S< U, V, VS... >, functor >::type;
    };

  /**
   * \brief Non specialized version that deals with any type but a valid
   * integral sequence nor a valid type sequence
   *
   * \tparam T any type but a valid type or integral sequence
   * \tparam B optional type used only if T is a type sequence. Represents a
   * base class for all type in the type sequence. This base type should exposes
   * the common contract that is respected in each type contained in the type
   * sequence.
   */
template< class T, class... B >
    struct runtime_access_for_impl
    {
      static_assert( warp::meta_sequence_traits< T >::is_meta_sequence,
                     "Invalid type used. Only meta sequence types are "
                     "allowed." );
    };

  /**
   * \brief Specialization dealing with an integral sequence. It exposes an
   * embedded std::array constant instance that contains all the value inside
   * the used integral sequence.
   *
   * \tparam S the integral sequence template
   * \tparam U the integral type used in the integral sequence
   * \tparam VS the integral pack used in the integral sequence
   */
  template< template< class T, T... > class S, class U, U... VS >
    struct runtime_access_for_impl< S< U, VS... > >
    {
      static_assert( warp::meta_sequence_traits< S< U, VS... > >::
                       is_integral_sequence,
                     "Invalid type used. Only integral sequence types are "
                     "allowed." );

      /**
       * \brief this type embbeds a std::array constant instance containing all
       * values within the sequence at construction
       */
      class const_array
      {
      public :
        /**
         * \brief Allows range for loops. relies on std::array exposition
         *
         * \return address of the first element in the underlying array
         */
        constexpr auto begin() const { return array_.begin(); }

        /**
         * \brief Allows range for loops. relies on std::array exposition
         *
         * \return address of the first element in the underlying array
         */
        constexpr auto cbegin() const { return array_.cbegin(); }

        /**
         * \brief Allows range for loops. relies on std::array exposition
         *
         * \return address of the element after the end in the underlying array
         */
        constexpr auto end() const { return array_.end(); }

        /**
         * \brief Allows range for loops. relies on std::array exposition
         *
         * \return address of the element after the end in the underlying array
         */
        constexpr auto cend() const { return array_.cend(); }

      private :
        /**
         * \brief The underlying array, implicitly initialized with sequence's
         * values
         */
        const std::array< U, sizeof...( VS ) > array_ { { VS... } };
      };

      /**
       * \brief Type alias on the embedded array
       */
      using type = const_array;
    };

  /**
   * \brief An iterator type used on an empty const_runtime_type_sequence
   * container. Most of methods defined within are no-op and other lead to
   * runtime error if used (dereferencing). This is the unspecialized template
   * version of the iterator
   *
   * \tparam B the value type of the iterator
   */
  template< class B, class... >
    class const_runtime_type_sequence_const_iterator
    {
    public :
      /**
       * \brief Alias on the value type to fullfil iterator requirements
       */
      using value_type = const B;

      /**
       * \brief Type alias for iterator requirements
       */
      using pointer = value_type *;

      /**
       * \brief Type alias for iterator requirements
       */
      using reference = value_type &;

      /**
       * \brief Type alias for iterator requirements
       */
      using difference_type = std::ptrdiff_t;

      /**
       * \brief Type alias for iterator requirements
       */
      using iterator_category = std::random_access_iterator_tag;

      /**
       * \brief using this method will lead to a runtime error.
       *
       * \return nothing, will crash
       */
      constexpr reference operator * () const
      {
        // this is intentionnal; there is nothing to dereference when the source
        // container is empty
        pointer dummy{ nullptr };
        return *dummy;
      }

      /**
       * \brief Same logic as the operator *.
       *
       * \return nothin as the app will crash
       */
      constexpr reference operator [] ( std::size_t ) const
      { return this->operator * (); }

      /**
       * \brief Quasi no-op
       *
       * \return nullptr
       */
      constexpr pointer operator -> () const { return nullptr; }

      /**
       * \brief No-op operator
       *
       * \return default-initialized instance of iterator
       */
      constexpr const_runtime_type_sequence_const_iterator operator ++ () const
      { return const_runtime_type_sequence_const_iterator{}; }

      /**
       * \brief No-op operator
       *
       * \return default-initialized instance of iterator
       */
      constexpr const_runtime_type_sequence_const_iterator operator ++ ( int )
        const { return const_runtime_type_sequence_const_iterator{}; }

      /**
       * \brief No-op operator
       *
       * \return default-initialized instance of iterator
       */
      constexpr const_runtime_type_sequence_const_iterator operator -- () const
      { return const_runtime_type_sequence_const_iterator{}; }

      /**
       * \brief No-op operator
       *
       * \return default-initialized instance of iterator
       */
      constexpr const_runtime_type_sequence_const_iterator operator -- ( int )
        const { return const_runtime_type_sequence_const_iterator{}; }

      /**
       * \brief No-op operator
       *
       * \return default-initialized instance of iterator
       */
      constexpr const_runtime_type_sequence_const_iterator operator +
        ( difference_type ) const
      { return const_runtime_type_sequence_const_iterator{}; }

      /**
       * \brief No-op operator
       *
       * \return default-initialized instance of iterator
       */
      constexpr const_runtime_type_sequence_const_iterator operator -
        ( difference_type ) const
      { return const_runtime_type_sequence_const_iterator{}; }

      /**
       * \brief No-op operator, return the difference between 2 iterator
       * instances.
       *
       * \return always 0
       */
      constexpr difference_type operator -
        ( const const_runtime_type_sequence_const_iterator & ) const
      { return 0; }

      /**
       * \brief No-op operator
       *
       * \return default-initialized instance of iterator
       */
      constexpr const_runtime_type_sequence_const_iterator & operator +=
        ( difference_type ) const
      { return *this; }

      /**
       * \brief No-op operator
       *
       * \return default-initialized instance of iterator
       */
      constexpr const_runtime_type_sequence_const_iterator & operator -=
        ( difference_type ) const
      { return *this; }

      /**
       * \brief Comparison operator. For this iterator type, all instances are
       * equal.
       *
       * \return true
       */
      constexpr bool operator ==
        ( const_runtime_type_sequence_const_iterator && ) const
      { return true; }

      /**
       * \brief Comparison operator. For this iterator type, all instances are
       * equal.
       *
       * \return false
       */
      constexpr bool operator !=
        ( const_runtime_type_sequence_const_iterator && ) const
      { return false; }

      /**
       * \brief Comparison operator. For this iterator type, all instances are
       * equal.
       *
       * \return false
       */
      constexpr bool operator <
        ( const_runtime_type_sequence_const_iterator && ) const
      { return false; }

      /**
       * \brief Comparison operator. For this iterator type, all instances are
       * equal.
       *
       * \return false
       */
      constexpr bool operator >
        ( const_runtime_type_sequence_const_iterator && ) const
      { return false; }

      /**
       * \brief Comparison operator. For this iterator type, all instances are
       * equal.
       *
       * \return true
       */
      constexpr bool operator <=
        ( const_runtime_type_sequence_const_iterator && ) const
      { return true; }

      /**
       * \brief Comparison operator. For this iterator type, all instances are
       * equal.
       *
       * \return true
       */
      constexpr bool operator >=
        ( const_runtime_type_sequence_const_iterator && ) const
      { return true; }
    };

  // forward declare this type that will be used in iterator type below
  template< class, class... >
    class const_runtime_type_sequence;

  /**
   * \brief An iterator type used on a non empty const_runtime_type_sequence
   * container. 
   *
   * \tparam B the value type of the iterator
   * \tparam T first type of a non empty type sequence
   * \tparam TS type pack, remainings type of the type sequence
   */
  template< class B, class T, class... TS >
    class const_runtime_type_sequence_const_iterator< B, T, TS... >
    {
    public :
      /**
       * \brief Alias on the value type to fullfil iterator requirements
       */
      using value_type = const B;

      /**
       * \brief Type alias for iterator requirements
       */
      using pointer = value_type *;

      /**
       * \brief Type alias for iterator requirements
       */
      using reference = value_type &;

      /**
       * \brief Type alias for iterator requirements
       */
      using difference_type = std::ptrdiff_t;

      /**
       * \brief Type alias for iterator requirements
       */
      using iterator_category = std::random_access_iterator_tag;

      /**
       * \brief Alias on the container type associated with this iterator type
       */
      using container_type = const const_runtime_type_sequence< B, T, TS... >;

      /**
       * \brief Pointer alias on the container type. Used as member.
       */
      using container_pointer = container_type *;

      /**
       * \brief Explicit construction, taking a pointer on an associated
       * container
       *
       * \param container a pointer on a constant container instance
       */
      explicit const_runtime_type_sequence_const_iterator
        ( container_pointer container = nullptr ) :
        container_{ container },
        base_level_{ 0 } {}

      /**
       * \brief Defaulted copy constructor
       */
      constexpr const_runtime_type_sequence_const_iterator
        ( const const_runtime_type_sequence_const_iterator & ) = default;

      /**
       * \brief Defaulted move-constructor
       */
      constexpr const_runtime_type_sequence_const_iterator
        ( const_runtime_type_sequence_const_iterator && ) = default;

      /**
       * \brief Defaulted affectation operator
       *
       * \return reference of the copied iterator
       */
      constexpr const_runtime_type_sequence_const_iterator & operator =
        ( const const_runtime_type_sequence_const_iterator & ) = default;

      /**
       * \brief Defaulted move affectation operator
       *
       * \return reference of the copied iterator
       */
      constexpr const_runtime_type_sequence_const_iterator & operator =
        ( const_runtime_type_sequence_const_iterator && ) = default;

      /**
       * \brief Redirection operator, uses container method if container is
       * specified
       *
       * \return pointer on the base type, might be nullptr
       */
      constexpr pointer operator -> () const
      {
        return
          ( container_ != nullptr ) ?
          container_->get_instance_at( base_level_ ) :
          nullptr;
      }

      /**
       * \brief Dereferencing operator. If a container is available, relies on
       * one of its method, otherwise, cause a runtime error by dereferencing
       * nullptr
       *
       * \return a reference to a base type constant instance or cause a runtime
       * error by dereferencing nullptr if iterator is invalid
       */
      constexpr reference operator * () const
      {
        pointer instance_address = nullptr;

        // use the container's method if possible
        if( container_ != nullptr )
          instance_address = container_->get_instance_at( base_level_ );

        // this line may cause a runtime error, it is voluntary
        return *instance_address;
      }

      /**
       * \brief Allows access at random level, may cause a runtime error if
       * index is invalid, making this iterator in an invalid state.
       *
       * \param base_level level at which access the instance in the underlying
       * container.
       *
       * \param base_level index of the instance to access. May be invalid.
       *
       * \return a reference on a constant instance in the container, or cause a
       * runtime error if index is invalid
       */
      constexpr reference operator [] ( std::size_t base_level ) const
      {
        // make a copy and work on it for access
        const_runtime_type_sequence_const_iterator tmp{ *this };

        tmp.base_level_ = base_level;

        // trigger this iterator instance to be fixed if past the end is reached
        tmp.fix_if_invalid();

        return *tmp;
      }

      /**
       * \brief pre-increment
       *
       * \return fresh instance of iterator with incremented base level
       */
      constexpr const_runtime_type_sequence_const_iterator operator ++ ()
      {
        ++base_level_;

        // trigger this iterator instance to be fixed if past the end is reached
        fix_if_invalid();

        return const_runtime_type_sequence_const_iterator{ *this };
      }

      /**
       * \brief post-increment
       *
       * \return an instance of iterator before its incrementation
       */
      constexpr const_runtime_type_sequence_const_iterator operator ++ ( int )
      {
        const_runtime_type_sequence_const_iterator tmp{ *this };

        ++( *this );

        // trigger this iterator instance to be fixed if past the end is reached
        fix_if_invalid();

        return tmp;
      }

      /**
       * \brief pre-decrement this iterator
       *
       * \return iterator instance, decremented
       */
      constexpr const_runtime_type_sequence_const_iterator operator -- ()
      {
        --base_level_;

        // trigger this iterator instance to be fixed if past the end is reached
        fix_if_invalid();

        return const_runtime_type_sequence_const_iterator{ *this };
      }

      /**
       * \brief post decrement this iterator
       *
       * \return copy of this iterator, before decrementation occurs
       */
      constexpr const_runtime_type_sequence_const_iterator operator -- ( int )
      {
        const_runtime_type_sequence_const_iterator tmp{ *this };

        --( *this );

        // trigger this iterator instance to be fixed if past the end is reached
        fix_if_invalid();

        return tmp;
      }

      /**
       * \brief increment this iterator by a value
       *
       * \param value value to use for the increment
       *
       * \return incremented iterator
       */
      constexpr const_runtime_type_sequence_const_iterator operator +
        ( difference_type value ) const
      {
        const_runtime_type_sequence_const_iterator tmp
          { container_, base_level_ + value };

        // trigger this iterator instance to be fixed if past the end is reached
        tmp.fix_if_invalid();

        return const_runtime_type_sequence_const_iterator{ std::move( tmp ) };
      }

      /**
       * \brief decrement this iterator by a value
       *
       * \param value value to use for the decrement
       *
       * \return decremented iterator
       */
      constexpr const_runtime_type_sequence_const_iterator operator -
        ( difference_type value ) const
      {
        const_runtime_type_sequence_const_iterator tmp
          { container_, base_level_ - value };

        // trigger this iterator instance to be fixed if past the end is reached
        tmp.fix_if_invalid();

        return const_runtime_type_sequence_const_iterator{ std::move( tmp ) };
      }

      /**
       * \brief Get the distance between this iterator and another one. Take the
       * validity of the iterator into account
       *
       * \param it other iterator
       *
       * \return The distance between this iterator instance and the iterator
       * specified in parameter
       */
      constexpr difference_type operator -
        ( const const_runtime_type_sequence_const_iterator &it ) const
      {
        // initially, takes base level of iterators
        difference_type this_base_level = base_level_,
                        other_base_level = it.base_level_;

        // if an iterator is invalid, it is automatically considered as a
        // past-the-end one
        if( *( this ) == const_runtime_type_sequence_const_iterator{} )
          this_base_level = container_size_;

        if( it == const_runtime_type_sequence_const_iterator{} )
          other_base_level = container_size_;

        return this_base_level - other_base_level;
      }

      /**
       * \brief increment this iterator instance by a specific value
       *
       * \param value value of the increment
       *
       * \return this instance of iterator, incremented
       */
      constexpr const_runtime_type_sequence_const_iterator & operator +=
        ( difference_type value )
      {
        base_level_ += value;

        // trigger this iterator instance to be fixed if past the end is reached
        fix_if_invalid();

        return *this;
      }

      /**
       * \brief decrement this iterator instance by a specific value
       *
       * \param value value of the decrement
       *
       * \return this instance of iterator, decremented
       */
      constexpr const_runtime_type_sequence_const_iterator operator -=
        ( difference_type value )
      {
        base_level_ -= value;

        // trigger this iterator instance to be fixed if past the end is reached
        fix_if_invalid();

        return *this;
      }

      /**
       * \brief Comparison operator.
       *
       * \param it other iterator used for the comparison
       *
       * \return true if states are stricty equal, otherwise false
       */
      constexpr bool operator ==
        ( const const_runtime_type_sequence_const_iterator &it ) const
      {
        return
          ( container_ == it.container_ ) &&
          ( base_level_ == it.base_level_ );
      }

      /**
       * \brief non equality operator.
       *
       * \param it other iterator used for the comparison
       *
       * \return Not ==
       */
      constexpr bool operator !=
        ( const const_runtime_type_sequence_const_iterator &it ) const
      { return ! ( ( *this ) == it ); }

      /**
       * \brief Comparison operator. Less than.
       *
       * \param it iterator used for the comparison
       *
       * \return true if all states of this are lesser than states of the
       * iterator instance specified in parameter
       */
      constexpr bool operator <
        ( const const_runtime_type_sequence_const_iterator &it ) const
      {
        return
          // to be eligible for comparison, containers must be the same
          ( container_ == it.container_ ) &&
          ( base_level_ < it.base_level_ );
      }

      /**
       * \brief Comparison operator : a > b
       *
       * \param it iterator used for the comparison
       *
       * \return b < a
       */
      constexpr bool operator >
        ( const const_runtime_type_sequence_const_iterator &it ) const
      { return it < ( *this ); }

      /**
       * \brief Comparison operator : a <= b
       *
       * \param it iterator used for the comparison
       *
       * \return ! ( a > b )
       */
      constexpr bool operator <=
        ( const const_runtime_type_sequence_const_iterator &it ) const
      { return ! ( ( *this ) > it ); }

      /**
       * \brief Comparison operator : a >= b
       *
       * \param it iterator used for the comparison
       *
       * \return !( a < b )
       */
      constexpr bool operator >=
        ( const const_runtime_type_sequence_const_iterator &it ) const
      { return ! ( ( *this ) < it ); }

    private :
      /**
       * \brief The associated container of this iterator instance
       */
      container_pointer container_;

      /**
       * \brief The container size, TS... + T
       */
      static constexpr std::size_t container_size_ = sizeof...( TS ) + 1;

      /**
       * \brief Current level of the iterator. Represents which instance is
       * pointed in container_.
       */
      difference_type base_level_;

      /**
       * \brief Internal fixing state method, giving a default initialized
       * iterator once base_level is considered incorrect (negative or too much
       * big regarding the underlying container's size. As a result, a
       * past-the-end iterator could be compared to a default initialized
       * iterator
       */
      constexpr void fix_if_invalid()
      {
        // unsigned base level. in case of negative value, no matter, the next
        // test handles it well
        decltype( container_size_ ) unsigned_base_level = base_level_;

        if( ( base_level_ < 0 ) || ( unsigned_base_level >= container_size_ ) )
        {
          base_level_ = 0;
          container_ = nullptr;
        }
      }
    };

  /**
   * \brief This specialization of container only works on an empty type
   * sequence. There is nothing to store here
   *
   * \tparam B Represents a base class for all type in the type sequence. This
   * base type should exposes the common contract that is respected in each type
   * contained in the type sequence.
   */
  template< class B, class... >
    class const_runtime_type_sequence
    {
    public :
      /**
       * \brief Iterator method returning a default-initialized iterator
       * pointing on an empty sequence. Nothing to dereference.
       *
       * \return a default-initialized iterator that is not valid to dereference
       * anything
       */
      constexpr auto begin() const
      { return const_runtime_type_sequence_const_iterator< B >{}; }

      /*
       * \brief Iterator method returning a default-initialized iterator
       * pointing on an empty sequence. Nothing to dereference.
       *
       * \return a default-initialized iterator that is not valid to dereference
       * anything
       */
      constexpr auto end() const
      { return const_runtime_type_sequence_const_iterator< B >{}; }
    };

  /**
   * \brief Specialization working for a type sequence containing only one
   * element. It's store inside the class
   *
   * \tparam T the unique type of the sequence. Default-instanciated as member.
   * \tparam B Represents a base class for all type in the type sequence. This
   * base type should exposes the common contract that is respected in each type
   * contained in the type sequence.
   */
  template< class B, class T >
    class const_runtime_type_sequence< B, T > :
    test_base_specified_for< B, T >
    {
      /**
       * \brief This iteartor type need a privileged access to use a private
       * method here
       */
      friend const_runtime_type_sequence_const_iterator< B, T >;

    public :
      /**
       * \brief Practical type alias
       */
      using value_type = const T;

      /**
       * \brief The base type of all types contained in T, TS...
       * Constantified.
       */
      using base_type = const B;

      /**
       * \brief Pointer on a constant base type. used in the get_instance_at
       * method as return type.
       */
      using pointer_base = base_type *;

      /**
       * \brief Get an iterator on the beginning of the sequence
       *
       * \return an iterator ponting on the instance stored in this container
       */
      constexpr auto begin() const
      { return const_runtime_type_sequence_const_iterator< B, T >{ this }; }

      /**
       * \brief Return a default-initialized iterator on the past -the-end
       * sequence.
       *
       * \return an default initialized iterator, invalid for dereferencing
       */
      constexpr auto end() const
      { return const_runtime_type_sequence_const_iterator< B, T >{}; }

    private :
      /**
       * \brief The type of the sequence is default-initialized here
       */
      value_type instance_{};

    protected :
      /**
       * \brief This method address how to access to the instance in this
       * container.
       *
       * \param base_level the base level to access instance. must be 0 to
       * access a real instance.
       *
       * \return a pointer on a constant base type. If base_level is higher than
       * 0, return nullptr
       */
      pointer_base get_instance_at( std::size_t base_level ) const
      {
        return ( base_level == 0 ) ? &instance_ : nullptr;
      }
    };

  /**
   * \brief Specialization used when the type sequence contains more than one
   * element. The first element is default-instanciated inside the class and the
   * contained inherits from himself, parameterized with remaining type in the
   * type sequence
   *
   * \tparam T the first type of the sequence. This is the one that is directly
   * instantiated inside the class
   * \tparam TS type pack representing remaining type in the type sequence
   * \tparam B Represents a base class for all type in the type sequence. This
   * base type should exposes the common contract that is respected in each type
   * contained in the type sequence.
   */
  template< class B, class T, class... TS >
    class const_runtime_type_sequence< B, T, TS... > :
    public const_runtime_type_sequence< B, TS... >,
    test_base_specified_for< B, T, TS... >
    {
      /**
       * \brief This iteartor type need a privileged access to use a private
       * method here
       */
      friend const_runtime_type_sequence_const_iterator< B, T, TS... >;

    public :
      /**
       * \brief Practical type alias on the true value type of the instance
       * stored in thsi container. Constantified.
       */
      using value_type = const T;

      /**
       * \brief The base type of all types contained in T, TS...
       * Constantified.
       */
      using base_type = const B;

      /**
       * \brief Pointer on a constant base type. used in the get_instance_at
       * method as return type.
       */
      using pointer_base = base_type *;

      /**
       * \brief Alias on the base class. Represents the base container type
       * containing other instances of types in the type sequence.
       */
      using base_container = const_runtime_type_sequence< B, TS... >;

      /**
       * \brief Return an iterator on the beginning of the sequence.
       *
       * \return an iterator pointing on the first instance of types contained
       * in the type sequence
       */
      constexpr auto begin() const
      {
        return
          const_runtime_type_sequence_const_iterator< B, T, TS... >{ this };
      }

      /**
       * \brief Standard iterator end method.
       *
       * \return a default-initialized, past-the-end iterator
       */
      constexpr auto end() const
      {
        return
          const_runtime_type_sequence_const_iterator< B, T, TS... >{};
      }

    private :
      /**
       * \brief The type of the sequence is default-initialized here
       */
      value_type instance_{};

    protected :
      /**
       * \brief This method address how to access to an instance at higher
       * hierachy-level. Used in iterators.
       *
       * \param base_level the base level to access instance
       *
       * \return a pointer on a constant base type. If base_level is invalid,
       * return nullptr
       */
      pointer_base get_instance_at( std::size_t base_level ) const
      {
        return
          ( base_level == 0 ) ?
          &instance_ : base_container::get_instance_at( base_level - 1 );
      }
    };

  /**
   * \brief Hidden implementation of the feature to gain a runtime access on
   * default-instantiated types of a type sequence.
   *
   * \tparam S type sequence template
   * \tparam TS type pack used as arguments for the type sequence template
   * \tparam B Represents a base class for all type in the type sequence. This
   * base type should exposes the common contract that is respected in each type
   * contained in the type sequence.
   */
  template< template< class... > class S, class... TS, class B >
    struct runtime_access_for_impl< S< TS... >, B >
    {
      static_assert( warp::meta_sequence_traits< S< TS... > >::is_type_sequence,
                     "Invalid type used. Only type sequence types are "
                     "allowed." );

      /**
       * \brief Exposes the container type, containing a default instance for
       * each type in the sequence, specifying the base type to use
       */
      using type = const_runtime_type_sequence< B, TS... >;
    };

  /**
   * \brief Hidden implementation of the merge feature. Will be declined in a
   * specialization to be used with integral sequences and another
   * specialization to be used with type sequences
   */
  template< class, class >
    struct merge_sequence_impl;

  /**
   * \brief Specialization triggered when the merged feature is used with 2
   * integral sequences. Integral types used by the 2 sequences must be
   * identical.
   *
   * \tparam LS left sequence template
   * \tparam LU integral type used in the left sequence
   * \tparam LV value pack of the left sequence
   * \tparam RS right sequence template
   * \tparam RU integral type used in the right sequence
   * \tparam RV value pack of the right sequence
   */
  template
    <
      template< class LT, LT... > class LS, class LU, LU... LV,
      template< class RT, RT... > class RS, class RU, RU... RV
    >
    struct merge_sequence_impl< LS< LU, LV... >, RS< RU, RV... > >
    {
      static_assert( warp::meta_sequence_traits< LS< LU, LV... > >::
                       is_integral_sequence,
                     "Invalid type used. Only integral sequence types are "
                     "allowed." );

      static_assert( warp::meta_sequence_traits< RS< RU, RV... > >::
                       is_integral_sequence,
                     "Invalid type used. Only integral sequence types are "
                     "allowed." );

      static_assert( std::is_same< LU, RU >::value,
                     "Invalid integral sequences specified for a merge. "
                     "Integral type used must be the same." );

      /**
       * \brief Merging means take elements of the left sequence and add element
       * of the right sequence, then expose the resulting sequence using the
       * left sequence template
       */
      using type = LS< LU, LV..., RV... >;
    };

  /**
   * \brief Specialization triggered when the merged feature is used with 2
   * type sequences.
   *
   * \tparam LS left sequence template
   * \tparam LT left type pack containing types in the left sequence
   * \tparam RS right sequence template
   * \tparam LT right type pack containing types in the right sequence
   */
  template
    <
      template< class... > class LS, class... LT,
      template< class... > class RS, class... RT
    >
    struct merge_sequence_impl< LS< LT... >, RS< RT... > >
    {
      static_assert( warp::meta_sequence_traits< LS< LT... > >::
                       is_type_sequence,
                     "Invalid type used. Only type sequence types are "
                     "allowed." );

      static_assert( warp::meta_sequence_traits< RS< RT... > >::
                       is_type_sequence,
                     "Invalid type used. Only type sequence types are "
                     "allowed." );

      /**
       * \brief Merging means take elements of the left sequence and add element
       * of the right sequence, then expose the resulting sequence using the
       * left sequence template
       */
      using type = LS< LT..., RT... >;
    };
}

// holds some meta predicates usable with type sequences
namespace warp
{
  /**
   * \brief Predicate used to compare type sizes in a type sequence.
   *
   * \tparam T the currently explored type in the sequence
   * \tparam U the type with which compare the size
   */
  template< class T, class U >
    struct type_less_size
    {
      /**
       * \brief Result of the comparison is exposed by the value constant
       */
      static constexpr auto value = ( sizeof( T ) < sizeof( U ) );
    };

  /**
   * \brief Predicate used to compare type alignment value in a type sequence.
   *
   * \tparam T the currently explored type in the sequence
   * \tparam U the type with which compare the size
   */
  template< class T, class U >
    struct type_less_align
    {
      /**
       * \brief Result of the comparison is exposed by the value constant
       */
      static constexpr auto value = ( alignof( T ) < alignof( U ) );
    };

  /**
   * \brief meta predicate designed to be used on an integral sequence and which
   * matches any integral value that is lower than a specified integral
   * constant. This non specialized version expose a false value.
   *
   * \tparam T integral type used in the integral sequence
   * \tparam V the currently explore value in the sequence
   */
  template< class T, T V, class... >
    struct integral_less
    {
      /**
       * \brief Nothing to compare, it's false
       */
      static constexpr auto value = false;
    };

  /**
   * \brief The only valid specialization, working with a value embedded inside
   * an integral constant type
   *
   * \tparam T integral type used in the integral sequence
   * \tparam V the currently explore value in the sequence
   * \tparam U A value embedded in an arbitrary type. This type MUST expose a
   * static constexpr value function to be valid
   */
  template< class T, T V, class U >
    struct integral_less< T, V, U >
    {
      /**
       * \brief The comparison result is exposed as a constant, using a pure
       * value-type. A pure value type is used in some warp algorithms
       */
      static constexpr auto value = ( V < U::value() );
    };

  /**
   * \brief Simple generator aiming to provide an indices sequence :
   * 0, 1, 2, ..., n-2, n-1, n
   */
  template< class... >
    struct indices
    {
      /**
       * \brief Generated value
       */
      static constexpr auto value = 0;

      /**
       * \brief The next value to be generated, 1
       */
      struct one
      {
        /**
         * \brief The one value embedded in a type
         */
        static constexpr auto value = 1;
      };

      /**
       * \brief Next value generated is in this generator type
       */
      using next = indices< one >;
    };

  /**
   * \brief Generic specialization working with a value-type containing the
   * value to be generated
   *
   * \tparam T type containing a value constant that is the value to generate
   */
  template< class T >
    struct indices< T >
    {
      /**
       * \brief Extract the value to generate from the type
       */
      static constexpr auto value = T::value;

      /**
       * \brief Prepare the next value to be generated after this one
       */
      struct n
      {
        /**
         * \brief Embedds the next indice inside a type
         */
        static auto constexpr value = T::value + 1;
      };

      /**
       * \brief Exposes the next generator type, for the next value to generate
       */
      using next = indices< n >;
    };

  /**
   * \brief Generator of triangular number. A triangular number of order 'n' is
   * calculated with ( N * ( N + 1 ) ) / 2. this non specialized version give 1.
   */
  template< class... >
    struct triangular
    {
      /**
       * \brief First oreder number
       */
      static constexpr auto value = 1;

      /**
       * \brief Next value
       */
      struct two
      {
        /**
         * \brief This is 2
         */
        static constexpr auto value = 2;
      };

      /**
       * \brief Next generator type
       */
      using next = triangular< two >;
    };

  /**
   * \brief Specialization exposing the triangular number of the rank specified
   * in the T type.
   *
   * \tparam T value type containing the order of the triangular number
   */
  template< class T >
    struct triangular< T >
    {
      /**
       * \brief Order of the number to generate
       */
      static constexpr auto o = T::value;

      /**
       * \brief calculates the triangular number regarding the order
       */
      static constexpr auto value = ( o * ( o + 1 ) ) / 2;

      /**
       * \brief Next order
       */
      struct n
      {
        /**
         * \brief Next order value
         */
        static constexpr auto value = o + 1;
      };

      /**
       * \brief Next generator type
       */
      using next = triangular< n >;
    };

  /**
   * \brief Generator providing a fibonacci number. Non specialized version
   * generating the first number of the serie
   */
  template< class... >
    struct fibonacci
    {
      /**
       * \brief The first fibonacci's sequence value
       */
      static constexpr auto value = 0;

      /**
       * \brief Embedded value used in the next generator
       */
      struct zero
      {
        /**
         * \brief This is the zero, embedded in a type
         */
        static constexpr auto value = 0;
      };

      /**
       * \brief The next generator for the next fibonacci's sequence value
       */
      using next = fibonacci< zero >;
    };

  /**
   * \brief Specialized generator when the first fibonacci's sequence value has
   * been calculated
   *
   * \tparam the first value of the fibonacci's sequence, embedded in a
   * value-type
   */
  template< class ZERO >
    struct fibonacci< ZERO >
    {
      /**
       * \brief The next value of the Fibonacci's sequence
       */
      static constexpr auto value = 1;

      /**
       * \brief Embedds the n-1 value in this type
       */
      struct one
      {
        /**
         * \brief The one value embedded in a type
         */
        static constexpr auto value = 1;
      };

      /**
       * \brief The next generator will make use of the last 2 number of the
       * fibonacci's sequence
       */
      using next = fibonacci< ZERO, one >;
    };

  /**
   * \brief Last specialization of this generator making use of the last 2
   * number of the Fibonacci's sequence.
   *
   * \tparam N_MINUS_2 the n-2 value embedded in a value-type
   * \tparam N_MINUS_1 the n-1 value embedded in a value-type
   */
  template< class N_MINUS_2, class N_MINUS_1 >
    struct fibonacci< N_MINUS_2, N_MINUS_1 >
    {
      /**
       * \brief Extracts n-2 value
       */
      static constexpr auto a = N_MINUS_2::value;

      /**
       * \brief Extracts n-1 value
       */
      static constexpr auto b = N_MINUS_1::value;

      /**
       * \brief Calculates the value to be generated
       */
      static constexpr auto value = a + b;

      /**
       * \brief Embedds the generated value in a value-type
       */
      struct n
      {
        /**
         * \brief the sum, embedded in a type
         */
        static constexpr auto value = a + b;
      };

      /**
       * \brief Exposes the next generator shifting values and incorporating the
       * last one as n-1 value
       */
      using next = fibonacci< N_MINUS_1, n >;
    };

  /**
   * \brief Ever wanted to generate prime numbers at compile time? This non
   * specialized generator give you the first of the serie. Beware, this one is
   * greedy
   */
  template< class... >
    struct prime
    {
      /**
       * \brief The first prime number
       */
      static constexpr auto value = 2;

      /**
       * \brief the first prime embedded in a value-type
       */
      struct two
      {
        /**
         * \brief first prime member embedded in a type
         */
        static constexpr auto value = 2;
      };

      /**
       * \brief the next prime number embedded in a value-type
       */
      struct three
      {
        /**
         * \brief Another prime member embedded in a type
         */
        static constexpr auto value = 3;
      };

      /**
       * \brief The next generator
       */
      using next = prime< two, three >;
    };

  /**
   * \brief Prime number generator specialization knowing the first 2 prime
   * numbers
   *
   * \brief TWO 2
   * \brief THREE 3
   */
  template< class TWO, class THREE >
    struct prime< TWO, THREE >
    {
      /**
       * \brief Extracts the value of 2
       */
      static constexpr auto two = TWO::value;

      /**
       * \brief Extracts the value of 3
       */
      static constexpr auto three = THREE::value;

      /**
       * \brief The prime number to be generated
       */
      static constexpr auto value = three;

      /**
       * \brief Assumes the next prime is the next odd number
       */
      struct n
      {
        /**
         * \brief An oddd number
         */
        static constexpr auto value = three + 2;
      };

      /**
       * \brief the next generator, embedding previous primes in a sequence and
       * forwarding the next assumed prime in a valu-type
       */
      using next =
        prime< warp::integral_sequence< unsigned long long, two, three >, n >;
    };

  /**
   * \brief Prime number generator used when more than 2 prime have been
   * generated.
   *
   * \tparam S integral sequence containing prime numbers
   * \tparam U integral type of prime numbers
   * \tparam VS value pack representing prime numbers
   * \tparam N the next assumed prime number
   */
  template< class T, T... VS, class N >
    struct prime< integral_sequence< T, VS... >, N >
    {
      /**
       * \brief Internal implementation search for a prime number for an
       * embedded value in a value-type
       */
      template< class, class >
        struct prime_impl;

      /**
       * \brief Specialization working with a non empty integral sequence
       * containing primer numbers. Check for N_ divisibility with the first
       * integral in the sequence. Recursive.
       *
       * \tparam W_ the first prime number in the sequence
       * \tparam WS_ prime number pack, remaining values in the sequence
       * \tparam N_ the assumed prime number
       */
      template< T W_, T... WS_, class N_ >
        struct prime_impl< integral_sequence< T, W_, WS_... >, N_ >
        {
          /**
           * \brief Check for divisibility of N_ and W_
           */
          static constexpr auto multiple = ( ( N_::value % W_ ) == 0 );

          /**
           * \brief Next assumed prime number, embedded in a value-type
           */
          struct n
          {
            /**
             * \brief Assumed next prime number
             */
            static constexpr auto value = N_::value + 2;
          };

          /**
           * \brief Alias used to access both value and next member of
           * prime_impl specialization
           */
          using next_impl =
            std::conditional_t
            <
              multiple,
              // if W_ divides N_, restart check with next assumed prime number
              prime_impl< integral_sequence< T, VS... >, n  >,
              // otherwise unfold checking sequence to work with the next prime
              prime_impl< integral_sequence< T, WS_... >, N_ >
            >;

          /**
           * \brief Relies on an internal feature
           */
          static constexpr auto value = next_impl::value;

          /**
           * \brief Relies on an internal feature
           */
          using next = typename next_impl::next;
        };

      /**
       * \brief Specialization used when checking sequence has been completely
       * iterated, proving N_ is a prime number
       *
       * \tparam N_ value-type containing a prime number
       */
      template< class N_ >
        struct prime_impl< integral_sequence< T >, N_ >
        {
          /**
           * \brief The next assumed prime number
           */
          struct n
          {
            /**
             * \brief Next assumed prime number inside a type
             */
            static constexpr auto value = N_::value + 2;
          };

          /**
           * \brief Current found prime number
           */
          static constexpr auto value = N_::value;

          /**
           * \brief The next generator
           */
          using next = prime< integral_sequence< T, VS..., value >, n >;
        };

      /**
       * \brief Relies on an internal feature
       */
      static constexpr auto value =
        prime_impl< integral_sequence< T, VS... >, N >::value;

      /**
       * \brief Relies on an internal feature
       */
      using next =
        typename prime_impl< integral_sequence< T, VS... >, N >::next;
    };

  /**
   * \brief Functor usable in the for_each_type_in algorithm designed to find
   * the biggest type contained in the type sequence. It exposes the size value
   * as well as the type itself as a result. Non specialized declaration,
   * respects the template signature of functor types
   */
  template< class, class... >
    struct first_biggest_type;

  /**
   * \brief Specialization corresponding to the user's used form in for each
   * feature. Used for the first type iterated in the sequence.
   *
   * \tparam T currently explored type in the sequence
   */
  template< class T >
    struct first_biggest_type< T >
    {
      /**
       * \brief Resulting value, size of the currently explored type
       */
      static constexpr auto value = sizeof( T );

      /**
       * \brief Resulting type, the currently explored type
       */
      using type = T;

      /**
       * \brief Computes the next functor, specifying an ignorable placeholder
       * and type to compare with the next one in the sequence
       */
      using next = first_biggest_type< warp::ignore, T >;
    };

  /**
   * \brief Specialization used for the type after the first and remaining ones.
   *
   * \tparam T the currently explored type
   * \tparam U the previously biggest type found in the sequence
   */
  template< class T, class U >
    struct first_biggest_type< T, U >
    {
      /**
       * \brief Size of the previsously biggest type found
       */
      static constexpr auto value = sizeof( U );

      /**
       * \brief The previously biggest type found
       */
      using type = U;

      /**
       * \brief Computes the next functor, comparing the currently explored type
       * size with the size of the previously biggest type found
       */
      using next =
        first_biggest_type
        <
          // ignorable placeholder
          warp::ignore,
          std::conditional_t
            <
              // comparison by size
              ( sizeof( T ) > sizeof( U ) ),
              T, U
            >
        >;
    };

  /**
   * \brief This functor is designed to provide information on the type that has
   * the strictest alignment requirement in a type sequence.
   */
  template< class, class... >
    struct first_strictest_alignment;

  /**
   * \brief Specialization corresponding to the user's used form in for each
   * feature. Used for the first type iterated in the sequence.
   *
   * \tparam T currently explored type in the sequence
   */
  template< class T >
    struct first_strictest_alignment< T >
    {
      /**
       * \brief Resulting value, alignment of the currently explored type
       */
      static constexpr auto value = alignof( T );

      /**
       * \brief Resulting type, the currently explored type
       */
      using type = T;

      /**
       * \brief Computes the next functor, specifying an ignorable placeholder
       * and type to compare with the next one in the sequence
       */
      using next = first_strictest_alignment< warp::ignore, T >;
    };

  /**
   * \brief Specialization used for the type after the first and remaining ones.
   *
   * \tparam T the currently explored type
   * \tparam U the previously type that has te strictest alignment found in the
   * sequence
   */
  template< class T, class U >
    struct first_strictest_alignment< T, U >
    {
      /**
       * \brief Size of the previsously biggest type found
       */
      static constexpr auto value = alignof( U );

      /**
       * \brief The previously biggest type found
       */
      using type = U;

      /**
       * \brief Computes the next functor, comparing the currently explored type
       * size with the size of the previously biggest type found
       */
      using next =
        first_strictest_alignment
        <
          // ignorable placeholder
          warp::ignore,
          std::conditional_t
            <
              // comparison by size
              ( alignof( T ) > alignof( U ) ),
              T, U
            >
        >;
    };

  /**
   * \brief Functor designed to be used on an integral sequence and providing
   * informations on the minimal value in an integral sequence. only declared.
   *
   * \tparam T integral type used in the sequence
   */
  template< class T, T, class... >
    struct min;

  /**
   * \brief Specialization working when the first value of the integral sequence
   * is explored.
   *
   * \tparam T integral type used in the sequence
   * \tparam V the currently explored value
   */
  template< class T, T V >
    struct min< T, V >
    {
      /**
       * \brief The first value is the tiniest one
       */
      static constexpr auto value = V;
      
      /**
       * \brief Computes the next functor, embedding the minimal value in an
       * integral constant
       */
      using next = min< T, V, std::integral_constant< T, V > >;
    };

  /**
   * \brief Specialization used for the 2nd and remaining values explored in the
   * integral sequence
   *
   * \tparam T integral type used in the sequence
   * \tparam V the currently explored value
   * \tparam W the previous minimal value found before this functor execution
   */
  template< class T, T V, T W >
    struct min< T, V, std::integral_constant< T, W > >
    {
      /**
       * \brief Exposes the strictest value
       */
      static constexpr auto value = W;

      /**
       * \brief Computes the next functor, compring the currently explored value
       * with the previous minimal value found
       */
      using next =
        std::conditional_t
        <
          ( V < W ),
          min< T, V, std::integral_constant< T, V > >,
          min< T, V, std::integral_constant< T, W > >
        >;
    };

  /**
   * \brief Functor designed to be used on an integral sequence and providing
   * informations on the maximal value in an integral sequence. only declared.
   *
   * \tparam T integral type used in the sequence
   */
  template< class T, T, class... >
    struct max;

  /**
   * \brief Specialization working when the first value of the integral sequence
   * is explored.
   *
   * \tparam T integral type used in the sequence
   * \tparam V the currently explored value
   */
  template< class T, T V >
    struct max< T, V >
    {
      /**
       * \brief The first value is the biggest one
       */
      static constexpr auto value = V;
      
      /**
       * \brief Computes the next functor, embedding the maximal value in an
       * integral constant
       */
      using next = max< T, V, std::integral_constant< T, V > >;
    };

  /**
   * \brief Specialization used for the 2nd and remaining values explored in the
   * integral sequence
   *
   * \tparam T integral type used in the sequence
   * \tparam V the currently explored value
   * \tparam W the previous maximal value found before this functor execution
   */
  template< class T, T V, T W >
    struct max< T, V, std::integral_constant< T, W > >
    {
      /**
       * \brief Exposes the strictest value
       */
      static constexpr auto value = W;

      /**
       * \brief Computes the next functor, compring the currently explored value
       * with the previous maximal value found
       */
      using next =
        std::conditional_t
        <
          ( V > W ),
          max< T, V, std::integral_constant< T, V > >,
          max< T, V, std::integral_constant< T, W > >
        >;
    };

  /**
   * \brief Computes the sum of all values in an integral sequence
   *
   * \tparam T integral type used in the sequence
   */
  template< class T, T, class... >
    struct sum;

  /**
   * \brief Specialization working when the first value of the integral sequence
   * is explored.
   *
   * \tparam T integral type used in the sequence
   * \tparam V the currently explored value
   */
  template< class T, T V >
    struct sum< T, V >
    {
      /**
       * \brief The first value is the tiniest one
       */
      static constexpr auto value = V;
      
      /**
       * \brief Computes the next functor, embedding the sum result in an
       * integral constant
       */
      using next = sum< T, V, std::integral_constant< T, V > >;
    };

  /**
   * \brief Specialization used for the 2nd and remaining values explored in the
   * integral sequence
   *
   * \tparam T integral type used in the sequence
   * \tparam V the currently explored value
   * \tparam W the previous sum result found before this functor execution
   */
  template< class T, T V, T W >
    struct sum< T, V, std::integral_constant< T, W > >
    {
      /**
       * \brief Exposes the current sum result
       */
      static constexpr auto value = W;

      /**
       * \brief Computes the next functor, sums
       */
      using next = sum< T, V, std::integral_constant< T, V + W > >;
    };

  /**
   * \brief Functor giving an average of values stored in an integral sequence
   *
   * \tparam T integral type used in the sequence
   */
  template< class T, T, class... >
    struct average;

  /**
   * \brief Specialization used when the first value of the sequence is explored
   *
   * \tparam T integral type used in the integral sequence
   * \tparam V the currently explored value
   */
  template< class T, T V >
    struct average< T, V >
    {
      /**
       * \brief Function returning the average. Only one value found for now,
       * return it as is
       *
       * \return the average result
       */
      static constexpr auto value() { return V; }

      /**
       * \brief Computes the next functor, embedding the sum of all value and
       * the count of element explored. Here, V and 1 respectively.
       */
      using next =
        average
        <
          T, V,
          std::pair
            <
              std::integral_constant< T, V >,
              std::integral_constant< std::size_t, 1 >
            >
        >;
    };

  /**
   * \brief Specialization used when the second and remaining values are
   * explored.
   *
   * \tparam T integral type used in the integral sequence
   * \tparam V the currently explored value
   * \tparam S the current sum of all value exploredbut V
   * \tparam C the count of element explored
   */
  template< class T, T V, T S, std::size_t C >
    struct average
    <
      T, V,
      std::pair
        <
          std::integral_constant< T, S >,
          std::integral_constant< std::size_t, C >
        >
    >
    {
      /**
       * \brief Calculates the average, casting to double
       *
       * \return the average result
       */
      static constexpr auto value() { return 1. * S / C; }

      /**
       * \brief Computes the next functor, adding the currentl explored value to
       * sum and adding 1 to element counted
       */
      using next =
        average
        <
          T, V,
          std::pair
            <
              std::integral_constant< T, V + S >,
              std::integral_constant< std::size_t, C + 1 >
            >
        >;
    };

  /**
   * \brief Functor applying on an integral sequence and useable with the
   * for_each_value_in algorithm. Give the number of element inside the
   * sequence. This unspecialized version open the way for more specialized
   * ones.
   *
   * \tparam T integral type used in the sequence
   */
  template< class T, T, class... >
    struct count_integral;

  /**
   * \brief Specialization used when the first element of the sequence is
   * explored.
   *
   * \tparam T the integral type used in the sequence
   * \tparam V the first value of the sequence
   */
  template< class T, T V >
    struct count_integral< T, V >
    {
      /**
       * \brief Current size of the sequence being explored, no value has been
       * explored yet
       */
      static constexpr std::size_t value = 0;

      /**
       * \brief Mandatory type exposition, get the next result afeter the first
       * value has been explored
       */
      using next =
        count_integral< T, V, std::integral_constant< std::size_t, 1 > >;
    };

  /**
   * \brief Specialization after the first element of the sequence has been
   * explored
   *
   * \tparam T the integral type used in the sequence
   * \tparam V the current value of the sequence being explored
   * \tparam S the current calculated size of the sequence
   */
  template< class T, T V, std::size_t S >
    struct count_integral< T, V, std::integral_constant< std::size_t, S > >
    {
      /**
       * \brief Before next element, if any, expose this value as size of the
       * sequence
       */
      static constexpr auto value = S;

      /**
       * \brief Next calculation
       */
      using next =
        count_integral< T, V, std::integral_constant< std::size_t, S + 1 > >;
    };

  /**
   * \brief Functor applying on a type sequence and useable with the
   * for_each_type_in algorithm. Give the number of element inside the sequence.
   * This unspecialized version open the way for more specialized ones.
   */
  template< class, class... >
    struct count_type;

  /**
   * \brief Specialization used when the first element of the sequence is
   * explored.
   *
   * \tparam T the first type of the sequence
   */
  template< class T >
    struct count_type< T >
    {
      /**
       * \brief Current size of the sequence being explored, no type has been
       * explored yet
       */
      static constexpr std::size_t value = 0;

      /**
       * \brief Mandatory type exposition, get the next result afeter the first
       * value has been explored
       */
      using next =
        count_type< T, std::integral_constant< std::size_t, 1 > >;
    };

  /**
   * \brief Specialization after the first element of the sequence has been
   * explored
   *
   * \tparam V the current type of the sequence being explored
   * \tparam S the current calculated size of the sequence
   */
  template< class T, std::size_t S >
    struct count_type < T, std::integral_constant< std::size_t, S > >
    {
      /**
       * \brief Before next element, if any, expose this value as size of the
       * sequence
       */
      static constexpr auto value = S;

      /**
       * \brief Next calculation
       */
      using next =
        count_type< T, std::integral_constant< std::size_t, S + 1 > >;
    };

  /**
   * \brief General form of the push_back algorithm, working both on integral
   * and type sequence
   *
   * \tparam T the supposed sequence, that will be checked
   * \tparam U double meaning : the type to insert for a type sequence, or the
   * integral type of the value to insert if the algorithm is used on an
   * integral sequence
   * \tparam V an optionnal value that is used if the algorithm is used on an
   * integral sequence
   */
  template< class T, class U, U...V >
    struct push_back_on;

  /**
   * \brief Specialization working for an integral sequence
   *
   * \tparam T the integral sequence
   * \tparam U the integral type of the value to push
   * \tparam V the value to push
   */
  template< class T, class U, U V >
    struct push_back_on< T, U, V >
    {
      /**
       * \brief Exposed the result, computed in a hidden type
       */
      using type = typename push_back_on_impl< T, U, V >::type;
    };

  /**
   * \brief Specialization working for a type sequence
   *
   * \tparam T the type sequence
   * \tparam U the type to push
   */
  template< class T, class U >
    struct push_back_on< T, U >
    {
      /**
       * \brief Exposed the result, computed in a hidden type
       */
      using type = typename push_back_on_impl< T, U >::type;
    };

  /**
   * \brief Alias template that can be used for bot integral and type sequence
   */
  template< class T, class U, U... V >
    using push_back_on_t = typename push_back_on< T, U, V... >::type;

  /**
   * \brief General form of the push_front algorithm, working both on integral
   * and type sequence
   *
   * \tparam T the supposed sequence, that will be checked
   * \tparam U double meaning : the type to insert for a type sequence, or the
   * integral type of the value to insert if the algorithm is used on an
   * integral sequence
   * \tparam V an optionnal value that is used if the algorithm is used on an
   * integral sequence
   */
  template< class T, class U, U...V >
    struct push_front_on;

  /**
   * \brief Specialization working for an integral sequence
   *
   * \tparam T the integral sequence
   * \tparam U the integral type of the value to push
   * \tparam V the value to push
   */
  template< class T, class U, U V >
    struct push_front_on< T, U, V >
    {
      /**
       * \brief Exposed the result, computed in a hidden type
       */
      using type = typename push_front_on_impl< T, U, V >::type;
    };

  /**
   * \brief Specialization working for a type sequence
   *
   * \tparam T the type sequence
   * \tparam U the type to push
   */
  template< class T, class U >
    struct push_front_on< T, U >
    {
      /**
       * \brief Exposed the result, computed in a hidden type
       */
      using type = typename push_front_on_impl< T, U >::type;
    };

  /**
   * \brief Alias template that can be used for bot integral and type sequence
   */
  template< class T, class U, U... V >
    using push_front_on_t = typename push_front_on< T, U, V... >::type;

  /**
   * \brief General form of the algorithm, this one is defined to ensure the
   * type used is a t the very least a meta_sequence, that is required, but not
   * sufficient.
   *
   * \tparam T the type that must be a meta_sequence
   */
  template< class T >
    struct pop_front_on
    {
      static_assert( warp::meta_sequence_traits< T >::
                       is_meta_sequence,
                     "Invalid type used. Only meta sequence types are "
                     "allowed." );
    };

  /**
   * \brief Specialization working well with a type sequence. Calculations and
   * checks are made in a hidden implementation
   *
   * \tparam S type sequence template
   * \tparam TS type pack used in the type sequence
   */
  template< template< class... > class S, class... TS >
    struct pop_front_on< S< TS... > >
    {
      /**
       * \brief Rely on hidden implementation to get it
       */
      using type = typename pop_front_on_impl< S< TS... > >::type;

      /**
       * \brief Rely on hidden implementation to get it
       */
      using sequence = typename pop_front_on_impl< S< TS... > >::sequence;
    };

  /**
   * \brief Specialization working on type sequences that are compliant with the
   * warp integral sequence concept.
   *
   * \tparam S integral sequence template
   * \tparam U integral type used in the integral sequence
   * \tparam VS value pack used in the integral sequence
   */
  template< template< class T, T... > class S, class U, U... VS >
    struct pop_front_on< S< U, VS... > >
    {
      /**
       * \brief Rely on hidden implementation to get it
       */
      static constexpr auto value = pop_front_on_impl< S< U, VS... > >::value;

      /**
       * \brief Rely on hidden implementation to get it
       */
      using sequence = typename pop_front_on_impl< S< U, VS... > >::sequence;
    };

  /**
   * \brief Alias template for the popped type. Only applicable on a type
   * sequence
   *
   * \tparam T a type sequence
   */
  template< class T >
    using pop_front_on_t = typename pop_front_on< T >::type;

  /**
   * \brief Alias template to get the sequence popped of on value. Applicable on
   * both type and integral sequence
   *
   * \tparam a meta sequence (type or integral)
   */
  template< class T >
    using pop_front_on_s = typename pop_front_on< T >::sequence;

  /**
   * \brief General form of the algorithm, this one is defined to ensure the
   * type used is a t the very least a meta_sequence, that is required, but not
   * sufficient.
   *
   * \tparam T the type that must be a meta_sequence
   */
  template< class T >
    struct pop_back_on
    {
      static_assert( warp::meta_sequence_traits< T >::
                       is_meta_sequence,
                     "Invalid type used. Only meta sequence types are "
                     "allowed." );
    };

  /**
   * \brief Specialization working well with a type sequence. Calculations and
   * checks are made in a hidden implementation
   *
   * \tparam S type sequence template
   * \tparam TS type pack used in the type sequence
   */
  template< template< class... > class S, class... TS >
    struct pop_back_on< S< TS... > >
    {
      /**
       * \brief Rely on hidden implementation to get it
       */
      using type = typename pop_back_on_impl< S< TS... > >::type;

      /**
       * \brief Rely on hidden implementation to get it
       */
      using sequence = typename pop_back_on_impl< S< TS... > >::sequence;
    };

  /**
   * \brief Specialization working on type sequences that are compliant with the
   * warp integral sequence concept.
   *
   * \tparam S integral sequence template
   * \tparam U integral type used in the integral sequence
   * \tparam VS value pack used in the integral sequence
   */
  template< template< class T, T... > class S, class U, U... VS >
    struct pop_back_on< S< U, VS... > >
    {
      /**
       * \brief Rely on hidden implementation to get it
       */
      static constexpr auto value = pop_back_on_impl< S< U, VS... > >::value;

      /**
       * \brief Rely on hidden implementation to get it
       */
      using sequence = typename pop_back_on_impl< S< U, VS... > >::sequence;
    };

  /**
   * \brief Alias template for the popped type. Only applicable on a type
   * sequence
   *
   * \tparam T a type sequence
   */
  template< class T >
    using pop_back_on_t = typename pop_back_on< T >::type;

  /**
   * \brief Alias template to get the sequence popped of on value. Applicable on
   * both type and integral sequence
   *
   * \tparam a meta sequence (type or integral)
   */
  template< class T >
    using pop_back_on_s = typename pop_back_on< T >::sequence;

  /**
   * \brief General form of the algorithm, used to specialize it for integral or
   * type sequence.
   *
   * \tparam T the type that must be a meta_sequence
   */
  template< class T >
    struct reverse_on
    {
      /**
       * \brief Delegates calculation to a hidden implementation
       */
      using type = typename reverse_on_impl< T >::type;
    };

  /**
   * \brief Alias template for the reversed sequence.
   *
   * \tparam T a type sequence
   */
  template< class T >
    using reverse_on_t = typename reverse_on< T >::type;

  /**
   * \brief Allows the user to perform a search inside the specified type
   * sequence. A valid predicate must be provided with its otional arguments as
   * well.
   *
   * \tparam T the type sequence
   * \tparam P Predicate template
   * \tparam TS type pack used as argument for the predicate template
   */
  template< class T, template< class, class... > class P, class... TS >
    struct find_first_in_type_sequence
    {
      /**
       * \brief Relies on a hidden implementation to get a sequence starting by
       * the first type corresponding to the predicate. If no type is found, the
       * returned sequence is empty.
       */
      using type =
        typename find_first_in_type_sequence_impl< T, P, TS... >::type;
    };

  /**
   * \brief Alias template providing a direct access to the sequence member of
   * the algorithm
   */
  template< class T, template< class, class... > class P, class... TS >
    using find_first_in_type_sequence_t =
    typename find_first_in_type_sequence< T, P, TS... >::type;

  /**
   * \brief Allows the user to perform a search inside the specified integral
   * sequence. A valid predicate must be provided with its otional arguments as
   * well.
   *
   * \tparam T the integral sequence
   * \tparam P Predicate template
   * \tparam TS type pack used as argument for the predicate template
   */
  template< class T, template< class U, U, class... > class P, class... TS >
    struct find_first_in_integral_sequence
    {
      /**
       * \brief Relies on a hidden implementation to get a sequence starting by
       * the first value corresponding to the predicate. If no value is found,
       * the returned sequence is empty.
       */
      using type =
        typename find_first_in_integral_sequence_impl< T, P, TS... >::type;
    };

  /**
   * \brief Alias template providing a direct access to the sequence member of
   * the algorithm
   */
  template< class T, template< class U, U, class... > class P, class... TS >
    using find_first_in_integral_sequence_t =
    typename find_first_in_integral_sequence< T, P, TS... >::type;

  /**
   * \brief Allows the user to perform a search inside the specified type
   * sequence. A valid predicate must be provided with its otional arguments as
   * well.
   *
   * \tparam T the type sequence
   * \tparam P Predicate template
   * \tparam TS type pack used as argument for the predicate template
   */
  template< class T, template< class, class... > class P, class... TS >
    struct find_all_in_type_sequence
    {
      /**
       * \brief Relies on a hidden implementation to get a sequence full of
       * types matching the specified predicate. If no type is found, the
       * returned sequence is empty.
       * TS pack is embedded inside a type sequence and an empty type sequence
       * is passed to the hidden implementation to serve as 'variadic' pump and
       * will receive found types
       */
      using type =
        typename find_all_in_type_sequence_impl
        < T, P, type_sequence< TS... >, type_sequence<> >::type;
    };

  /**
   * \brief Alias template providing a direct access to the sequence member of
   * the algorithm
   */
  template< class T, template< class, class... > class P, class... TS >
    using find_all_in_type_sequence_t =
    typename find_all_in_type_sequence< T, P, TS... >::type;

  /**
   * \brief Allows the user to perform a search inside the specified integral
   * sequence. A valid predicate must be provided with its otional arguments as
   * well.
   *
   * \tparam T the integral sequence
   * \tparam P Predicate template
   * \tparam TS type pack used as argument for the predicate template
   */
  template< class T, template< class U, U, class... > class P, class... TS >
    struct find_all_in_integral_sequence
    {
      /**
       * \brief Relies on a hidden implementation to get a sequence filled with
       * values matching to the predicate. If no value is found, the returned
       * sequence is empty.  TS pack is embedded inside a type sequence and an
       * empty integral sequence is passed to the hidden implementation to serve
       * as placecholder for an integral sequence that will contain values that
       * are matching the predicate
       */
      using type =
        typename find_all_in_integral_sequence_impl
        <
          T, P,
          type_sequence< TS... >,
          integral_sequence< int >
        >::type;
    };

  /**
   * \brief Alias template providing a direct access to the sequence member of
   * the algorithm
   */
  template< class T, template< class U, U, class... > class P, class... TS >
    using find_all_in_integral_sequence_t =
    typename find_all_in_integral_sequence< T, P, TS... >::type;

  /**
   * \brief The is_empty_sequence algorithm check if the provided meta sequence
   * (integral or type) is empty, exposing a value for that
   *
   * \tparam T the sequence to check
   */
  template< class T >
    struct is_empty_sequence
    {
      /**
       * \brief Value exposed relies on an hidden implementation
       */
      static constexpr auto value = is_empty_sequence_impl< T >::value;
    };

  /**
   * \brief Allows the user to perform a deletion inside the specified type
   * sequence. A valid predicate must be provided with its otional arguments as
   * well.
   *
   * \tparam T the type sequence
   * \tparam P Predicate template
   * \tparam TS type pack used as argument for the predicate template
   */
  template< class T, template< class, class... > class P, class... TS >
    struct remove_first_in_type_sequence
    {
      /**
       * \brief Relies on a hidden implementation to get a sequence without the
       * first type corresponding to the predicate. If no type is found, the
       * returned sequence is untouched
       */
      using type =
        typename remove_first_in_type_sequence_impl
        < T, P, type_sequence< TS... >, type_sequence<> >::type;
    };

  /**
   * \brief Alias template providing a direct access to the sequence member of
   * the algorithm
   */
  template< class T, template< class, class... > class P, class... TS >
    using remove_first_in_type_sequence_t =
    typename remove_first_in_type_sequence< T, P, TS... >::type;

  /**
   * \brief Allows the user to perform a deletion inside the specified integral
   * sequence. A valid predicate must be provided with its otional arguments as
   * well.
   *
   * \tparam T the integral sequence
   * \tparam P Predicate template
   * \tparam TS type pack used as argument for the predicate template
   */
  template< class T, template< class U, U, class... > class P, class... TS >
    struct remove_first_in_integral_sequence
    {
      /**
       * \brief Relies on a hidden implementation to get a sequence without the
       * first value corresponding to the predicate. If no value is found, the
       * returned sequence is untouched
       */
      using type =
        typename remove_first_in_integral_sequence_impl
        < T, P, type_sequence< TS... >, integral_sequence< int > >::type;
    };

  /**
   * \brief Alias template providing a direct access to the sequence member of
   * the algorithm
   */
  template< class T, template< class U, U, class... > class P, class... TS >
    using remove_first_in_integral_sequence_t =
    typename remove_first_in_integral_sequence< T, P, TS... >::type;

  /**
   * \brief Allows the user to perform a deltion inside the specified type
   * sequence. A valid predicate must be provided with its otional arguments as
   * well.
   *
   * \tparam T the type sequence
   * \tparam P Predicate template
   * \tparam TS type pack used as argument for the predicate template
   */
  template< class T, template< class, class... > class P, class... TS >
    struct remove_all_in_type_sequence
    {
      /**
       * \brief Relies on a hidden implementation to get a sequence cleared of
       * types matching the specified predicate. If no type is found, the
       * returned sequence is untouched.
       * TS pack is embedded inside a type sequence and an empty type sequence
       * is passed to the hidden implementation to serve as 'variadic' pump and
       * will receive found types
       */
      using type =
        typename remove_all_in_type_sequence_impl
        < T, P, type_sequence< TS... >, type_sequence<> >::type;
    };

  /**
   * \brief Alias template providing a direct access to the sequence member of
   * the algorithm
   */
  template< class T, template< class, class... > class P, class... TS >
    using remove_all_in_type_sequence_t =
    typename remove_all_in_type_sequence< T, P, TS... >::type;

  /**
   * \brief Allows the user to perform a deltion inside the specified integral
   * sequence. A valid predicate must be provided with its otional arguments as
   * well.
   *
   * \tparam T the integral sequence
   * \tparam P Predicate template
   * \tparam TS type pack used as argument for the predicate template
   */
  template< class T, template< class U, U, class... > class P, class... TS >
    struct remove_all_in_integral_sequence
    {
      /**
       * \brief Relies on a hidden implementation to get a sequence cleared of
       * values matching to the predicate. If no value is found, the returned
       * sequence is untouched. TS pack is embedded inside a type sequence and
       * an empty integral sequence is passed to the hidden implementation to
       * serve as placecholder for an integral sequence that will contain values
       * that are matching the predicate
       */
      using type =
        typename remove_all_in_integral_sequence_impl
        < T, P, type_sequence< TS... >, integral_sequence< int > >::type;
    };

  /**
   * \brief Alias template providing a direct access to the sequence member of
   * the algorithm
   */
  template< class T, template< class U, U, class... > class P, class... TS >
    using remove_all_in_integral_sequence_t =
    typename remove_all_in_integral_sequence< T, P, TS... >::type;

  /**
   * \brief Sort algorithm for a type sequence. Need a sequence and a valid
   * template form of meta predicate. Rely on hidden implementation.
   *
   * \tparam T the supposed type sequence
   * \tparam P predicate template
   * \tparam TS type pack used in the predicate
   */
  template< class T, template< class, class... > class P, class... TS >
    struct sort_type_sequence
    {
      /**
       * \brief Uses the hidden implementation type exposition
       */
      using type =
        typename sort_type_sequence_impl< T, P, TS... >::type;
    };

  /**
   * \brief Alias template, c++14 flavor
   *
   * \tparam T the supposed type sequence
   * \tparam P predicate template
   */
  template< class T, template< class, class... > class P, class... TS >
    using sort_type_sequence_t =
    typename sort_type_sequence< T, P, TS... >::type;

  /**
   * \brief Sort algorithm for an integral sequence. need a sequence and a valid
   * template meta predicate in template parameter.
   *
   * \tparam T supposed integral sequence
   * \tparam P predicate template
   * \tparam TS type pack used in the predicate
   */
  template< class T, template< class U, U, class... > class P, class... TS >
    struct sort_integral_sequence
    {
      /**
       * \brief Relies on hidden implementation
       */
      using type =
        typename sort_integral_sequence_impl< T, P, TS... >::type;
    };

  /**
   * \brief Alias template allowing use of this algorithm with a c++14 flavor
   *
   * \tparam T the supposed type sequence
   * \tparam P predicate template
   */
  template< class T, template< class U, U, class... > class P, class... TS >
    using sort_integral_sequence_t =
    typename sort_integral_sequence< T, P, TS... >::type;

  /**
   * \brief Algorithm to partition a type sequence, order is preserved and type
   * matching the predicate are place before those that don't match
   *
   * \tparam T the supposed type sequence type
   * \tparam P the predicate template
   * \tparam TS type pack used as arguments in the predicate
   */
  template< class T, template< class, class... > class P, class... TS >
    struct partition_type_sequence
    {
      /**
       * \brief relies on a hidden implementation
       */
      using type =
        typename partition_type_sequence_impl
        <
          T, P, type_sequence< TS... >,
          // use type sequences to receive partitionned types, the left one is
          // for types matching the predicate, the right one for others.
          type_sequence<>, type_sequence<>
        >::type;
    };

  /**
   * \brief Convenient alias, providing access to a C++14 writing fashion
   *
   * \tparam T the supposed type sequence type
   * \tparam P the predicate template
   * \tparam TS type pack used as arguments in the predicate
   */
  template< class T, template< class, class... > class P, class... TS >
    using partition_type_sequence_t =
    typename partition_type_sequence< T, P, TS... >::type;

  /**
   * \brief Algorithm to partition an integral sequence, order is preserved and
   * type matching the predicate are place before those that don't match
   *
   * \tparam T the supposed integral sequence type
   * \tparam P the predicate template
   * \tparam TS type pack used as arguments in the predicate
   */
  template< class T, template< class U, U, class... > class P, class... TS >
    struct partition_integral_sequence
    {
      /**
       * \brief Recursively deduce the next partition iteration
       */
      using type =
        typename partition_integral_sequence_impl
        <
          T, P, type_sequence< TS... >,
          // use integral sequences to receive partitionned values, the left one
          // is for values matching the predicate, the right one for others.
          integral_sequence< int >, integral_sequence< int >
        >::type;
    };

  /**
   * \brief Convenient alias, providing access to a C++14 writing fashion
   *
   * \tparam T the supposed integral sequence type
   * \tparam P the predicate template
   * \tparam TS type pack used as arguments in the predicate
   */
  template< class T, template< class U, U, class... > class P, class... TS >
    using partition_integral_sequence_t =
    typename partition_integral_sequence< T, P, TS... >::type;

  /**
   * \brief Public exposure of the algorithm, entirely relies on a hidden
   * implementation
   *
   * \tparam T the supposed sequence in which remove duplicated elements
   */
  template< class T >
    struct unique_on
    {
      /**
       * \brief Uses hidden implementation
       */
      using type = typename unique_on_impl< T >::type;
    };

  /**
   * \brief Convenient c++14 kind alias template
   */
  template< class T >
    using unique_on_t = typename unique_on< T >::type;

  /**
   * \brief feature that can be used to generate a sequence of signed integral
   * values. Takes a generator template and its parameters as arguments. The
   * feature will use the generator an amount of time specified in template
   * parameter list
   *
   * \tparam C the number of time a generation must occur.
   * \tparam G generator template
   * \tparam TS type pack used as parameters for the generator template
   */
  template< std::size_t C, template< class... > class G, class... TS >
    struct generate_signed_integral_sequence
    {
      /**
       * \brief relies on the hidden implementation, instantiating the generator
       * template using its specified arguments. Forward an empty integral
       * sequence parameterized with the smallest signed integral type existing.
       */
      using type =
        typename generate_integral_sequence_impl
        < C, warp::integral_sequence< signed char >, G< TS... > >::type;
    };

  /**
   * \brief feature that can be used to generate a sequence of unsigned integral
   * values. Takes a generator template and its parameters as arguments. The
   * feature will use the generator an amount of time specified in template
   * parameter list
   *
   * \tparam C the number of time a generation must occur.
   * \tparam G generator template
   * \tparam TS type pack used as parameters for the generator template
   */
  template< std::size_t C, template< class... > class G, class... TS >
    struct generate_unsigned_integral_sequence
    {
      /**
       * \brief relies on the hidden implementation, instantiating the generator
       * template using its specified arguments. Forward an empty integral
       * sequence parameterized with the smallest unsigned integral type
       * existing.
       */
      using type =
        typename generate_integral_sequence_impl
        < C, warp::integral_sequence< unsigned char >, G< TS... > >::type;
    };

  /**
   * \brief Convenient alias for the generation of an integral sequence of
   * signed values
   *
   * \tparam C the number of time a generation must occur.
   * \tparam G generator template
   * \tparam TS type pack used as parameters for the generator template
   */
  template< std::size_t C, template< class... > class G, class... TS >
    using generate_signed_integral_sequence_t =
    typename generate_signed_integral_sequence< C, G, TS... >::type;

  /**
   * \brief Convenient alias for the generation of an integral sequence of
   * unsigned values
   *
   * \tparam C the number of time a generation must occur.
   * \tparam G generator template
   * \tparam TS type pack used as parameters for the generator template
   */
  template< std::size_t C, template< class... > class G, class... TS >
    using generate_unsigned_integral_sequence_t =
    typename generate_unsigned_integral_sequence< C, G, TS... >::type;

  /**
   * \brief This feature is designed to append a char buffer embedded in a
   * value-type inside an integral sequence.
   *
   * \tparam S the integral sequence in which append the char buffer
   * \tparam B the value-type containing the char buffer to append
   */
  template< class S, class B >
    struct append_char_buffer_in
    {
      /**
       * \brief Relies-on an hidden feature
       */
      using type = typename append_char_buffer_in_impl< S, B >::type;
    };

  /**
   * \brief Convenient alias to shorten the feature usage
   *
   * \tparam S the integral sequence in which append the char buffer
   * \tparam B the value-type containing the char buffer to append
   */
  template< class S, class B >
    using append_char_buffer_in_t =
    typename append_char_buffer_in< S, B >::type;

  /**
   * \brief This feature will iterate through a type sequence, applying an
   * user-made meta-functor one each explored type. The user-made functor must
   * respect a specific template signature and expose a 'next' type that is an
   * instantiation of this functor template signature.
   *
   * \tparam S the type sequence that will be iterated
   * \tparam F functor template
   * \tparam TS type pack used as functor arguments
   */
  template< class S, template< class, class... > class F, class... TS >
    struct for_each_type_in
    {
      /**
       * \brief Relies-on an internal hidden implementation for both check and
       * execution of the algorithm
       */
      using type = typename for_each_type_in_impl< S, F, TS... >::type;
    };

  /**
   * \brief This feature will iterate through an integral sequence, applying an
   * user-made meta-functor one each explored type. The user-made functor must
   * respect a specific template signature and expose a 'next' type that is an
   * instantiation of this functor template signature.
   *
   * \tparam S the integral sequence that will be iterated
   * \tparam F functor template
   * \tparam TS type pack used as functor arguments
   */
  template< class S, template< class T, T, class... > class F, class... TS >
    struct for_each_value_in
    {
      /**
       * \brief Relies-on an internal hidden implementation for both check and
       * execution of the algorithm
       */
      using type = typename for_each_value_in_impl< S, F, TS... >::type;
    };

  /**
   * \brief Convenient template alias for the for each feature on a type
   * sequence.
   *
   * \tparam S the type sequence that will be iterated
   * \tparam F functor template
   * \tparam TS type pack used as functor arguments
   */
  template< class S, template< class, class... > class F, class... TS >
    using for_each_type_in_t = typename for_each_type_in< S, F, TS... >::type;

  /**
   * \brief Convenient template alias for the for each feature on a type
   * sequence.
   *
   * \tparam S the integral sequence that will be iterated
   * \tparam F functor template
   * \tparam TS type pack used as functor arguments
   */
  template< class S, template< class T, T, class... > class F, class... TS >
    using for_each_value_in_t = typename for_each_value_in< S, F, TS... >::type;

  /**
   * \brief Features allowing the user to access the content of a meta sequence
   * at runtime. It exposes a type that is iteratable. In the case of T is a
   * type sequence, B must be specified and be a valid base class for all type
   * that are inside the type sequence.
   *
   * \tparam T the sequence to deal with
   * \tparam B optional type used only if T is a type sequence. Represents a
   * base class for all type in the type sequence. This base type should exposes
   * the common contract that is respected in each type contained in the type
   * sequence.
   */
  template< class T, class... B >
    struct runtime_access_for
    {
      /**
       * \brief Uses an hidden implementation of the feature.
       */
      using type = typename runtime_access_for_impl< T, B... >::type;
    };

  /**
   * \brief Template alias to gain a c++14 fashion write
   *
   * \tparam T the sequence to deal with
   * \tparam B optional type used only if T is a type sequence. Represents a
   * base class for all type in the type sequence. This base type should exposes
   * the common contract that is respected in each type contained in the type
   * sequence.
   */
  template< class T, class... B >
    using runtime_access_for_t = typename runtime_access_for< T, B... >::type;

  /**
   * \brief Merging feature. This algorithm will combine 2 sequences with each
   * other. The 2 sequences must be of the same type, either 2 type sequences or
   * 2 integral sequences. As a result, the given merged sequence will be LS.RS
   *
   * \tparam LS left sequence
   * \tparam RS right sequence
   */
  template< class LS, class RS >
    struct merge_sequence
    {
      /**
       * \brief Uses an hidden implementation of the feature.
       */
      using type = typename merge_sequence_impl< LS, RS >::type;
    };

  /**
   * \brief Template alias to gain a c++14 fashion write
   *
   * \tparam LS left sequence
   * \tparam RS right sequence
   */
  template< class LS, class RS >
    using merge_sequence_t = typename merge_sequence< LS, RS >::type;
}

#endif // _WARP_SEQUENCES_ALGORITHM_HPP_

// doxygen
/**
 * \file
 * \brief Contains various compile-time algorithms applicable on meta sequence
 * types of warp.
 */
