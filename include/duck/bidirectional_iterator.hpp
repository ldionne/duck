/**
 * This file defines the `BidirectionalIterator` concept.
 */

#ifndef DUCK_BIDIRECTIONAL_ITERATOR_HPP
#define DUCK_BIDIRECTIONAL_ITERATOR_HPP

#include <duck/detail/test_expression.hpp>
#include <duck/forward_iterator.hpp>
#include <duck/models.hpp>

#include <boost/mpl/and.hpp>
#include <boost/type_traits/add_lvalue_reference.hpp>
#include <boost/type_traits/is_convertible.hpp>
#include <boost/utility/declval.hpp>


namespace duck {

namespace bidirectional_detail {
template <typename Iterator>
class is_bidirectional_iterator_impl {
    DUCK_I_TEST_EXPRESSION(pre_decrement, --boost::declval<I&>(), typename I);
    DUCK_I_TEST_EXPRESSION(post_decrement, boost::declval<I&>()--, typename I);

public:
    typedef typename boost::mpl::and_<
                is_forward_iterator<Iterator>,

                boost::is_convertible<
                    typename pre_decrement<Iterator>::type,
                    typename boost::add_lvalue_reference<Iterator>::type
                >,

                boost::is_convertible<
                    typename post_decrement<Iterator>::type, Iterator
                >
            >::type type;
    static bool const value = type::value;
};
} // end namespace bidirectional_detail

//! `BidirectionalIterator` concept.
struct BidirectionalIterator {
    template <typename Iterator>
    struct apply
        : bidirectional_detail::is_bidirectional_iterator_impl<Iterator>
    { };
};

/**
 * Metafunction returning whether an `Iterator` models the
 * `BidirectionalIterator` concept.
 */
template <typename Iterator>
struct is_bidirectional_iterator
    : models<BidirectionalIterator, Iterator>
{ };

} // end namespace duck

#endif // !DUCK_BIDIRECTIONAL_ITERATOR_HPP
