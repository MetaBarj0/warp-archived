#ifndef _WARP_SEQUENCES_SEQUENCE_TYPES_HPP_
#define _WARP_SEQUENCES_SEQUENCE_TYPES_HPP_

// core features needed here
#include "../core/types.hpp"

namespace warp
{
  /**
   * \brief An empty type, base of all meta-sequence types
   */
  struct meta_sequence {};

  /**
   * \brief Represents the integral sequence at compile time. Inherit from
   * empty_type for the emptiness representation and the meta_sequence type for
   * the meta-sequence concept representation
   *
   * \tparam T an integral type
   * \tparam VS template values pack
   */
  template< class T, T... VS >
    struct integral_sequence :
    meta_sequence, empty_type {};

  /**
   * \brief Represents a type sequence at compile time. Inherit from
   * empty_type for the emptiness representation and the meta_sequence type for
   * the meta-sequence concept representation
   *
   * \tparam TS template parameter pack containing each type of the sequence.
   */
  template< class... TS >
    struct type_sequence :
    meta_sequence, empty_type {};
}

#endif // _WARP_SEQUENCES_SEQUENCE_TYPES_HPP_
