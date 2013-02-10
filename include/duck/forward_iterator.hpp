/**
 * This file defines the @em ForwardIterator concept.
 */

#ifndef DUCK_FORWARD_ITERATOR_HPP
#define DUCK_FORWARD_ITERATOR_HPP

#include <duck/default_constructible.hpp>
#include <duck/detail/config.hpp>
#include <duck/detail/test_expression.hpp>
#include <duck/single_pass_iterator.hpp>

#include <boost/mpl/and.hpp>
#include <boost/type_traits/is_integral.hpp>
#include <boost/type_traits/is_signed.hpp>


namespace duck {

/**
 * Metafunction returning whether @em It models the @em ForwardIterator
 * concept.
 */
template <typename It>
class ForwardIterator {
    DUCK_I_TEST_TYPE(difference_type_,
            typename detail::iterator_traits<I>::difference_type, typename I);
    typedef typename difference_type_<It>::type Difference;

public:
    typedef typename boost::mpl::and_<
                DefaultConstructible<It>,
                SinglePassIterator<It>,
                detail::is_valid<Difference>,
                boost::is_integral<Difference>,
                boost::is_signed<Difference>
            >::type type;
    static bool const value = type::value;
};

} // end namespace duck

#endif // !DUCK_FORWARD_ITERATOR_HPP
