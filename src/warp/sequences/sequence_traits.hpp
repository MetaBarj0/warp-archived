#ifndef _WARP_SEQUENCES_SEQUENCE_TRAITS_HPP_
#define _WARP_SEQUENCES_SEQUENCE_TRAITS_HPP_

#include "sequence_types.hpp"
#include "../core/types.hpp"
#include "../core/type_traits.hpp"

#include <type_traits>

// holds hidden stuff
namespace
{
  /**
   * \brief Meta function indicating if a specified type has a specified static
   * member named value of a specified type within. Relies on SFINAE
   * availaibility in the compiler.
   * This non specialized version is used if the specified type doesn't have any
   * static value member found within T
   *
   * \tparam T the type to look for a static member named value within
   * \tparam U the type of the value member must have
   */
  template< class T, class U, class = typename warp::sfinae_type<>::type >
    struct has_static_value_member_of_type
    {
      /**
       * \brief Non specialized version, means the value static member does not
       * exist
       */
      static constexpr bool value = false;
    };

  /**
   * \brief Specialized version in which a static member named value exists in
   * T. Despite its existence, I must ensure this member has the right type.
   *
   * \tparam T the type to look for a static member named value within
   * \tparam U the type of the value member must have
   */
  template< class T, class U >
    struct has_static_value_member_of_type
    < T, U, typename warp::sfinae_type< decltype( T::value ) >::type >
    {
      /**
       * \brief The static member named value has been found, but this type must
       * be U
       */
      static constexpr bool value =
        std::is_same< U, decltype( T::value ) >::value;
    };

  /**
   * \brief Meta function indicating if a specified type has a specified static
   * member named value that is integral . Relies on SFINAE availaibility in the
   * compiler.
   * This non specialized version is used if the specified type doesn't have any
   * static value member found within T
   *
   * \tparam T the type to look for a static member named value within
   */
  template< class T, class = typename warp::sfinae_type<>::type >
    struct has_static_integral_value_member
    {
      /**
       * \brief Non specialized version, means the value static member does not
       * exist
       */
      static constexpr bool value = false;
    };

  /**
   * \brief Specialized version in which a static member named value exists in
   * T. Despite its existence, I must ensure this member has the right type.
   *
   * \tparam T the type to look for a static member named value within
   */
  template< class T >
    struct has_static_integral_value_member
    < T, typename warp::sfinae_type< decltype( T::value ) >::type >
    {
      /**
       * \brief The static member named value has been found, but this type must
       * be integral
       */
      static constexpr bool value =
        std::is_integral< decltype( T::value ) >::value;
    };

  /**
   * \brief Recognize a template signature through specialization. Usable to
   * check a generator template signature for integral sequence generations
   */
  template< class >
    struct is_valid_integral_sequence_generator_template_signature
    {
      /**
       * \brief Non specialized version means that is not a generator at all
       */
      static constexpr bool value = false;
    };

  /**
   * \brief Only valid specialization suiting for integral sequence generator
   * template signature
   *
   * \tparam G generator template
   * \tparam TS type pack used as argument in the generator template
   */
  template< template< class... > class G, class... TS >
    struct is_valid_integral_sequence_generator_template_signature< G< TS... > >
    {
      /**
       * \brief Specialization used, it's OK
       */
      static constexpr bool value = true;
    };

  /**
   * \brief Check for the existence of a 'next' type inside T. T must be an
   * integral sequence generator and the next type must be also an integral
   * sequence generator
   *
   * \tparam T any type but a valid integral sequence generator
   */
  template< class T, class = typename warp::sfinae_type<>::type >
    struct has_integral_sequence_generator_next_type
    {
      /**
       * \brief T doesn't have a 'next' type exposed
       */
      static constexpr bool value = false;
    };

  /**
   * \brief Specialization using an integral sequence generator and a SFINAE
   * expression for 'next'
   *
   * \tparam G generator template
   * \tparam TS type pack used as arguments in the generator
   */
  template< class T >
    struct has_integral_sequence_generator_next_type
    < T, typename warp::sfinae_type< typename T::next >::type >
    {
      /**
       * \brief 'next' type is exposed by T, check its type
       */
      static constexpr bool value =
        is_valid_integral_sequence_generator_template_signature
        < typename T::next >::value;
    };

  /**
   * \brief Recognize a template signature through specialization. Usable to
   * check a functor template signature for integral sequence generations
   */
  template< class >
    struct is_valid_integral_sequence_functor_template_signature
    {
      /**
       * \brief Non specialized version means that is not a generator at all
       */
      static constexpr bool value = false;
    };

  /**
   * \brief Only valid specialization suiting for integral sequence functor
   * template signature
   *
   * \tparam F functor template
   * \tparam TS type pack used as argument in the functor template
   */
  template
    < template< class T, T, class... > class F, class U, U V, class... TS >
    struct is_valid_integral_sequence_functor_template_signature
    < F< U, V, TS... > >
    {
      /**
       * \brief Specialization used, it's OK
       */
      static constexpr bool value = true;
    };

  /**
   * \brief Recognize a template signature through specialization. Usable to
   * check a functor template signature for type sequence generations
   */
  template< class >
    struct is_valid_type_sequence_functor_template_signature
    {
      /**
       * \brief Non specialized version means that is not a generator at all
       */
      static constexpr bool value = false;
    };

  /**
   * \brief Only valid specialization suiting for type sequence functor
   * template signature
   *
   * \tparam F functor template
   * \tparam TS type pack used as argument in the functor template
   */
  template< template< class, class... > class F, class T, class... TS >
    struct is_valid_type_sequence_functor_template_signature< F< T, TS... > >
    {
      /**
       * \brief Specialization used, it's OK
       */
      static constexpr bool value = true;
    };

  /**
   * \brief Check for the existence of a 'next' type inside T. T must be an
   * integral sequence functor and the next type must be also an integral
   * sequence functor
   *
   * \tparam T any type but a valid integral sequence functor
   */
  template< class T, class = typename warp::sfinae_type<>::type >
    struct has_integral_sequence_functor_next_type
    {
      /**
       * \brief T doesn't have a 'next' type exposed
       */
      static constexpr bool value = false;
    };

  /**
   * \brief Specialization using an integral sequence generator and a SFINAE
   * expression for 'next'
   *
   * \tparam F functor template
   * \tparam TS type pack used as arguments in the functor
   */
  template< class T >
    struct has_integral_sequence_functor_next_type
    < T, typename warp::sfinae_type< typename T::next >::type >
    {
      /**
       * \brief 'next' type is exposed by T, check its type
       */
      static constexpr bool value =
        is_valid_integral_sequence_functor_template_signature
        < typename T::next >::value;
    };

  /**
   * \brief Check for the existence of a 'next' type inside T. T must be an
   * type sequence functor and the next type must be also an type
   * sequence functor
   *
   * \tparam T any type but a valid type sequence functor
   */
  template< class T, class = typename warp::sfinae_type<>::type >
    struct has_type_sequence_functor_next_type
    {
      /**
       * \brief T doesn't have a 'next' type exposed
       */
      static constexpr bool value = false;
    };

  /**
   * \brief Specialization using an type sequence generator and a SFINAE
   * expression for 'next'
   *
   * \tparam F functor template
   * \tparam TS type pack used as arguments in the functor
   */
  template< class T >
    struct has_type_sequence_functor_next_type
    < T, typename warp::sfinae_type< typename T::next >::type >
    {
      /**
       * \brief 'next' type is exposed by T, check its type
       */
      static constexpr bool value =
        is_valid_type_sequence_functor_template_signature
        < typename T::next >::value;
    };
}

namespace warp
{
  /**
   * \brief This traits class provide all that is necessary to determine if the
   * specified type has some meta sequence traits. This template is not
   * specialized and workd for all type but meta sequences
   *
   * \tparam T an arbitrary type
   */
  template< class T >
    struct meta_sequence_traits
    {
      /**
       * \brief T is anything but meta sequence here
       */
      static constexpr bool is_meta_sequence = false;

      /**
       * \brief T is anything but meta sequence here
       */
      static constexpr bool is_type_sequence = false;

      /**
       * \brief T is anything but meta sequence here
       */
      static constexpr bool is_integral_sequence = false;

      /**
       * \brief Indicates if the sequence is empty, not a sequence here
       */
      static constexpr bool is_empty = false;
    };

  /**
   * \brief This specialization works well with a type sequence template
   * signature provided type
   *
   * \tparam S a type sequence template
   * \tparam TS type pack contained in the type sequence
   */
  template< template< class... > class S, class... TS >
    struct meta_sequence_traits< S< TS... > >
    {
      /**
       * \brief OK, a type sequence is a meta sequence
       */
      static constexpr bool is_meta_sequence = true;

      /**
       * \brief here it is a type sequence
       */
      static constexpr bool is_type_sequence = true;

      /**
       * \brief A type sequence is not an integral sequence
       */
      static constexpr bool is_integral_sequence = false;

      /**
       * \brief Indicates if the sequence is empty, examining the size of the
       * type parameter pack
       */
      static constexpr bool is_empty = ( sizeof...( TS ) == 0 );
    };

  /**
   * \brief Specialization working with integral sequence signature type.
   * Although the signature matches, I must ensure U is an integral type and not
   * another valid type for used non-type parameter in the sequence such as
   * pointers (function/static member), references or nullptr
   *
   * \tparam S valid integran sequence template (in term of signature)
   * \tparam U supposed integral type used in the sequence
   * \tparam VS value pack used in the sequence
   */
  template< template< class T, T... > class S, class U, U... VS >
    struct meta_sequence_traits< S< U, VS... > >
    {
      /**
       * \brief OK, an integral sequence is a meta sequence
       */
      static constexpr bool is_meta_sequence = true;

      /**
       * \brief An integral sequence is not a type sequence
       */
      static constexpr bool is_type_sequence = false;

      /**
       * \brief Ensures that U is an integral type
       */
      static constexpr bool is_integral_sequence = std::is_integral< U >::value;

      /**
       * \brief Indicates if the sequence is empty, examining the size of the
       * type parameter pack
       */
      static constexpr bool is_empty = ( sizeof...( VS ) == 0 );
    };

  /**
   * \brief Traits class related to meta predicate. Exposes all that is
   * necessary to get meta predicate tratis. This unspecialized version is used
   * when T is not a meta predicate
   *
   * \tparam T a non meta predicate type
   */
  template< class T >
    struct meta_predicate_traits
    {
      /**
       * \brief this is not a meta predicate
       */
      static constexpr bool is_type_sequence_predicate = false;

      /**
       * \brief this is not a meta predicate
       */
      static constexpr bool is_integral_sequence_predicate = false;
    };

  /**
   * \brief This specialization triggers when used with meta predicate designed
   * for type sequences.
   *
   * \tparam P meta predicate for type sequence template
   * \tparam T a type used in the meta predicate
   * \tparam TS a type pack used in the meta predicate
   */
  template< template< class, class... > class P, class T, class... TS >
    struct meta_predicate_traits< P< T, TS... > >
    {
      /**
       * \brief Template signature matched for this meta predicate. SFINAE check
       * now
       */
      static constexpr bool is_type_sequence_predicate =
        has_static_value_member_of_type< P< T, TS... >, const bool >::value;

      /**
       * \brief This meta predicate applies only on type sequences
       */
      static constexpr bool is_integral_sequence_predicate = false;
    };

  /**
   * \brief Specialization triggerring on meta predicate that are designed to be
   * used on integral sequences.
   *
   * \tparam P meta predicate template signature
   * \tparam U type used in the meta predicate. must be integral type
   * \tparam V integral value sued in the meta predicate
   * \tparam TS type pack used in the meta predicate
   */
  template
    < template< class T, T, class... > class P, class U, U V, class... TS >
    struct meta_predicate_traits< P< U, V, TS... > >
    {
      /**
       * \brief The current meta predicate is designed to be used on integral
       * sequence only
       */
      static constexpr bool is_type_sequence_predicate = false;

      /**
       * \brief Template signature of the predicate is matched. But I need that
       * U be an integral type and I need the meta predicate template instance
       * exposes a static const bool member name value
       */
      static constexpr bool is_integral_sequence_predicate =
        std::is_integral< U >::value &&
        has_static_value_member_of_type< P< U, V, TS... >, const bool >::value;
    };

  /**
   * \brief Holds trait specifications for generator. This non specialized
   * version indicates that traits for valid generators are not met.
   *
   * \tparam T any type but a valid generator
   */
  template< class T >
    struct meta_generator_traits
    {
      /**
       * \brief T is not a meta generator
       */
      static constexpr bool is_integral_sequence_generator = false;

      /**
       * \brief T is not a meta generator
       */
      static constexpr bool is_type_sequence_generator = false;
    };

  /**
   * \brief Specialization used when the specified type has this specific
   * template signature.
   *
   * \tparam G generator template correct in its former glory
   * \tparam TS type pack used as arguments in the generator and used to
   * validate its structure
   */
  template< template< class... > class G, class... TS >
    struct meta_generator_traits< G< TS... > >
    {
      /**
       * \brief Generator template signature matches. Need a supplementary
       * SFINAE check relative to the presence of a value integral static member
       */
      static constexpr bool is_integral_sequence_generator =
        has_static_integral_value_member< G< TS... > >::value &&
        has_integral_sequence_generator_next_type< G< TS... > >::value;

      /**
       * \brief not implemented yet
       */
      static constexpr bool is_type_sequence_generator = false;
    };

  /**
   * \brief Traits class containing all that is neccessary to determine the
   * validity of a static functor usable in some meta sequence iteration
   * features
   *
   * \tparam T any type but a valid functor for type or integral sequence
   */
  template< class T >
    struct meta_functor_traits
    {
      /**
       * \brief T is not a valid functor type
       */
      static constexpr bool is_type_sequence_functor = false;

      /**
       * \brief T is not a valid functor type
       */
      static constexpr bool is_integral_sequence_functor = false;
    };

  /**
   * \brief Specialization used when the functor is suitable to be used on a
   * type sequence
   *
   * \tparam F Functor template
   * \tparam T currently explored type in a type sequence
   * \tparam TS type pack used as functor arguments
   */
  template< template< class, class... > class F, class T, class... TS >
    struct meta_functor_traits< F< T, TS... > >
    {
      /**
       * \brief SFINAE check to look for a next type exposing a right functor
       * type
       */
      static constexpr bool is_type_sequence_functor =
        has_type_sequence_functor_next_type< F< T, TS... > >::value;

      /**
       * \brief not suitable for integral sequences
       */
      static constexpr bool is_integral_sequence_functor = false;
    };

  /**
   * \brief Specialization used when the functor is suitable to be used on an
   * integral sequence
   *
   * \tparam F Functor template
   * \tparam U integral type used in the integral sequence
   * \tparam V currently explored value in an integral sequence
   * \tparam TS type pack used as functor arguments
   */
  template
    < template< class T, T, class... > class F, class U, U V, class... TS >
    struct meta_functor_traits< F< U, V, TS... > >
    {
      /**
       * \brief SFINAE check to look for a next type exposing a right functor
       * type
       */
      static constexpr bool is_integral_sequence_functor =
        has_integral_sequence_functor_next_type< F< U, V, TS... > >::value;

      /**
       * \brief not suitable for type sequences
       */
      static constexpr bool is_type_sequence_functor = false;
    };

  /**
   * \brief Groups various traits related to operand  that could be used with
   * some meta sequence algorithms
   *
   * \tparam T an operand type
   */
  template< class T >
    struct meta_sequence_operands_traits
    {
      /**
       * \brief Indicates if this operand type is a value-type whose the value
       * is a char buffer. Check for both T::value xor T::value()
       */
      static constexpr bool is_char_buffer_value_type =
        (
          has_static_char_buffer_value_member< T >::value ^
          has_static_char_buffer_value_method< T >::value
        );
    };
}

#endif // _WARP_SEQUENCES_SEQUENCE_TRAITS_HPP_

// doxygen
/**
 * \file
 *
 * \brief Header containing some traits relative to meta sequence types exposed
 * by warp
 */
