/**
 * This file defines the specialization of `is_more_specific_than` for
 * iterator concepts.
 */

#ifndef DUCK_DETAIL_ITERATOR_CONCEPTS_ORDERING_HPP
#define DUCK_DETAIL_ITERATOR_CONCEPTS_ORDERING_HPP

#include <duck/detail/mpl_extensions.hpp>
#include <duck/requires.hpp>

#include <boost/mpl/and.hpp>
#include <boost/mpl/contains.hpp>
#include <boost/mpl/deref.hpp>
#include <boost/mpl/not.hpp>
#include <boost/mpl/vector.hpp>
#include <boost/type_traits/is_same.hpp>
#include <boost/utility/enable_if.hpp>


namespace duck {

struct RandomAccessIterator;
struct BidirectionalIterator;
struct ForwardIterator;
struct SinglePassIterator;
struct IncrementableIterator;

namespace iter_concepts_detail {
typedef boost::mpl::vector<
            RandomAccessIterator,
            BidirectionalIterator,
            ForwardIterator,
            SinglePassIterator,
            IncrementableIterator
        > traversal_concepts;
} // end namespace iter_concepts_detail

template <typename A, typename B>
struct is_more_specific_than<A, B,
    typename boost::enable_if<
        boost::mpl::and_<
            boost::mpl::not_<boost::is_same<A, B> >,
            boost::mpl::contains<iter_concepts_detail::traversal_concepts, A>,
            boost::mpl::contains<iter_concepts_detail::traversal_concepts, B>
        >
    >::type
>
    // B must appear before A in the traversal_concepts
    : boost::is_same<
        B,
        typename boost::mpl::deref<
            typename boost::mpl::find_first_of<
                iter_concepts_detail::traversal_concepts,
                boost::mpl::vector<B, A>
            >::type
        >::type
    >
{ };

} // end namespace duck

#endif // !DUCK_DETAIL_ITERATOR_CONCEPTS_ORDERING_HPP
