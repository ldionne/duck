/**
 * This file defines the `ForwardIterator` concept.
 */

#ifndef DUCK_FORWARD_ITERATOR_HPP
#define DUCK_FORWARD_ITERATOR_HPP

#include <duck/default_constructible.hpp>
#include <duck/detail/test_expression.hpp>
#include <duck/models.hpp>
#include <duck/single_pass_iterator.hpp>

#include <boost/mpl/and.hpp>
#include <boost/type_traits/is_integral.hpp>
#include <boost/type_traits/is_signed.hpp>
#include <iterator>


namespace duck {

namespace forward_detail {
template <typename Iterator>
class is_forward_iterator_impl {
    DUCK_I_TEST_TYPE(difference_type_,
            typename std::iterator_traits<I>::difference_type, typename I);
    typedef typename difference_type_<Iterator>::type Difference;

public:
    typedef typename boost::mpl::and_<
                is_default_constructible<Iterator>,
                is_single_pass_iterator<Iterator>,
                detail::is_valid<Difference>,
                boost::is_integral<Difference>,
                boost::is_signed<Difference>
            >::type type;
    static bool const value = type::value;
};
} // end namespace forward_detail

//! `ForwardIterator` concept.
struct ForwardIterator {
    template <typename Iterator>
    struct apply
        : forward_detail::is_forward_iterator_impl<Iterator>
    { };
};

/**
 * Metafunction returning whether an `Iterator` models the `ForwardIterator`
 * concept.
 */
template <typename Iterator>
struct is_forward_iterator
    : models<ForwardIterator, Iterator>
{ };

} // end namespace duck

#endif // !DUCK_FORWARD_ITERATOR_HPP
