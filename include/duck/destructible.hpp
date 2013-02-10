/**
 * This file defines the `Destructible` concept.
 */

#ifndef DUCK_DESTRUCTIBLE_HPP
#define DUCK_DESTRUCTIBLE_HPP

#include <type_traits>


namespace duck {

/**
 * Metafunction returning whether `T` models the `Destructible`
 * concept.
 */
template <typename T>
struct is_destructible
    : std::is_destructible<T>
{ };

//! `Destructible` concept.
struct Destructible {
    template <typename T>
    struct apply
        : is_destructible<T>
    { };
};

} // end namespace duck

#endif // !DUCK_DESTRUCTIBLE_HPP
