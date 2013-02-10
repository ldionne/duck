/**
 * This file defines the @em BidirectionalIterator concept.
 */

#ifndef DUCK_BIDIRECTIONAL_ITERATOR_HPP
#define DUCK_BIDIRECTIONAL_ITERATOR_HPP

#include <duck/detail/test_expression.hpp>
#include <duck/forward_iterator.hpp>

#include <boost/mpl/and.hpp>
#include <boost/type_traits/add_lvalue_reference.hpp>
#include <boost/type_traits/is_convertible.hpp>
#include <boost/utility/declval.hpp>


namespace duck {

/**
 * Metafunction returning whether @em It models the @em BidirectionalIterator
 * concept.
 */
template <typename It>
class BidirectionalIterator {
    DUCK_I_TEST_EXPRESSION(pre_decrement, --boost::declval<I&>(), typename I);
    DUCK_I_TEST_EXPRESSION(post_decrement, boost::declval<I&>()--, typename I);

public:
    typedef typename boost::mpl::and_<
                ForwardIterator<It>,

                boost::is_convertible<
                    typename pre_decrement<It>::type,
                    typename boost::add_lvalue_reference<It>::type
                >,

                boost::is_convertible<
                    typename post_decrement<It>::type, It
                >
            >::type type;
    static bool const value = type::value;
};

} // end namespace duck

#endif // !DUCK_BIDIRECTIONAL_ITERATOR_HPP
