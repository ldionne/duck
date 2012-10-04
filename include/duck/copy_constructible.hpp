/**
 * This file defines the @em CopyConstructible concept.
 */

#ifndef DUCK_COPY_CONSTRUCTIBLE_HPP
#define DUCK_COPY_CONSTRUCTIBLE_HPP

#include <type_traits>


namespace duck {

/**
 * Metafunction returning whether @em T models the @em CopyConstructible
 * concept.
 */
template <typename T>
struct CopyConstructible : std::is_copy_constructible<T> { };

} // end namespace duck

#endif // !DUCK_COPY_CONSTRUCTIBLE_HPP
