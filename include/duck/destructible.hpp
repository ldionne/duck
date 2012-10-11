/**
 * This file defines the @em Destructible concept.
 */

#ifndef DUCK_DESTRUCTIBLE_HPP
#define DUCK_DESTRUCTIBLE_HPP

#include <type_traits>


namespace duck {

/**
 * Metafunction returning whether @em T models the @em Destructible
 * concept.
 */
template <typename T>
struct Destructible : std::is_destructible<T> { };

} // end namespace duck

#endif // !DUCK_DESTRUCTIBLE_HPP
