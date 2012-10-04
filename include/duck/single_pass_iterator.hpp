/**
 * This file defines the @em SinglePassIterator concept.
 */

#ifndef DUCK_SINGLE_PASS_ITERATOR_HPP
#define DUCK_SINGLE_PASS_ITERATOR_HPP

#include <duck/equality_comparable.hpp>
#include <duck/incrementable_iterator.hpp>

#include <mpl11/and.hpp>


namespace duck {

/**
 * Metafunction returning whether @em It models the @em SinglePassIterator
 * concept.
 */
template <typename It>
struct SinglePassIterator
    : mpl11::and_<
        EqualityComparable<It>,
        IncrementableIterator<It>
    >
{ };

} // end namespace duck

#endif // !DUCK_SINGLE_PASS_ITERATOR_HPP
