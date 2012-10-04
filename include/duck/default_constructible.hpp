/**
 * This file defines the @em DefaultConstructible concept.
 */

#ifndef DUCK_DEFAULT_CONSTRUCTIBLE_HPP
#define DUCK_DEFAULT_CONSTRUCTIBLE_HPP

#include <type_traits>


namespace duck {

/**
 * Metafunction returning whether @em T models the @em DefaultConstructible
 * concept.
 */
template <typename T>
struct DefaultConstructible : std::is_default_constructible<T> { };

} // end namespace duck

#endif // !DUCK_DEFAULT_CONSTRUCTIBLE_HPP
