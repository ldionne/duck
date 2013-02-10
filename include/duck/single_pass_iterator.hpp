/**
 * This file defines the `SinglePassIterator` concept.
 */

#ifndef DUCK_SINGLE_PASS_ITERATOR_HPP
#define DUCK_SINGLE_PASS_ITERATOR_HPP

#include <duck/equality_comparable.hpp>
#include <duck/incrementable_iterator.hpp>

#include <boost/mpl/and.hpp>


namespace duck {

/**
 * Metafunction returning whether an `Iterator` models the
 * `SinglePassIterator` concept.
 */
template <typename Iterator>
struct is_single_pass_iterator
    : boost::mpl::and_<
        EqualityComparable<Iterator>,
        IncrementableIterator<Iterator>
    >
{ };

//! `SinglePassIterator` concept.
struct SinglePassIterator {
    template <typename Iterator>
    struct apply
        : is_single_pass_iterator<Iterator>
    { };
};

} // end namespace duck

#endif // !DUCK_SINGLE_PASS_ITERATOR_HPP
