/**
 * This file defines the `CopyConstructible` concept.
 */

#ifndef DUCK_COPY_CONSTRUCTIBLE_HPP
#define DUCK_COPY_CONSTRUCTIBLE_HPP

#include <type_traits>


namespace duck {

/**
 * Metafunction returning whether `T` models the `CopyConstructible`
 * concept.
 */
template <typename T>
struct is_copy_constructible
    : std::is_copy_constructible<T>
{ };

//! `CopyConstructible` concept.
struct CopyConstructible {
    template <typename T>
    struct apply
        : is_copy_constructible<T>
    { };
};

} // end namespace duck

#endif // !DUCK_COPY_CONSTRUCTIBLE_HPP
