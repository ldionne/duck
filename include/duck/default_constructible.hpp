/**
 * This file defines the `DefaultConstructible` concept.
 */

#ifndef DUCK_DEFAULT_CONSTRUCTIBLE_HPP
#define DUCK_DEFAULT_CONSTRUCTIBLE_HPP

#include <type_traits>


namespace duck {

/**
 * Metafunction returning whether `T` models the `DefaultConstructible`
 * concept.
 */
template <typename T>
struct is_default_constructible
    : std::is_default_constructible<T>
{ };

//! `DefaultConstructible` concept.
struct DefaultConstructible {
    template <typename T>
    struct apply
        : is_default_constructible<T>
    { };
};

} // end namespace duck

#endif // !DUCK_DEFAULT_CONSTRUCTIBLE_HPP
