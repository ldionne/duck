/**
 * This file defines the @em RandomAccessIterator concept.
 */

#ifndef DUCK_RANDOM_ACCESS_ITERATOR_HPP
#define DUCK_RANDOM_ACCESS_ITERATOR_HPP

#include <duck/bidirectional_iterator.hpp>
#include <duck/comparable.hpp>
#include <duck/detail/config.hpp>
#include <duck/detail/test_expression.hpp>
#include <duck/readable_iterator.hpp>
#include <duck/writeable_iterator.hpp>

#include <boost/mpl/and.hpp>
#include <boost/mpl/bool.hpp>
#include <boost/mpl/if.hpp>
#include <boost/type_traits/add_lvalue_reference.hpp>
#include <boost/type_traits/is_convertible.hpp>
#include <boost/utility/declval.hpp>


namespace duck {

/**
 * Metafunction returning whether @em It models the @em RandomAccessIterator
 * concept.
 */
template <typename It>
class RandomAccessIterator {
    DUCK_I_TEST_EXPRESSION(iadd, boost::declval<I&>() += boost::declval<N>(),
                                                    typename I, typename N);
    DUCK_I_TEST_EXPRESSION(add, boost::declval<A>() + boost::declval<B>(),
                                                    typename A, typename B);
    DUCK_I_TEST_EXPRESSION(isub, boost::declval<I&>() -= boost::declval<N>(),
                                                    typename I, typename N);
    DUCK_I_TEST_EXPRESSION(sub, boost::declval<A>() - boost::declval<B>(),
                                                    typename A, typename B);
    // Only if ReadableIterator.
    DUCK_I_TEST_EXPRESSION(subscript, boost::declval<I>()[boost::declval<N>()],
                                                    typename I, typename N);
    // Only if WriteableIterator.
    DUCK_I_TEST_EXPRESSION(subscript_assign,
        boost::declval<I>()[boost::declval<N>()] = boost::declval<V>(),
                                        typename I, typename N, typename V);
    DUCK_I_TEST_TYPE(value_type_,
                typename detail::iterator_traits<I>::value_type, typename I);
    DUCK_I_TEST_TYPE(difference_type_,
            typename detail::iterator_traits<I>::difference_type, typename I);

    typedef typename value_type_<It>::type Value;
    typedef typename difference_type_<It>::type Difference;

public:
    typedef typename boost::mpl::and_<
                BidirectionalIterator<It>,
                Comparable<It>,

                detail::is_valid<Value>,
                detail::is_valid<Difference>,

                boost::mpl::and_<

                boost::is_convertible<
                    typename iadd<It, Difference>::type,
                    typename boost::add_lvalue_reference<It>::type
                >,

                boost::is_convertible<
                    typename add<It, Difference>::type, It
                >,

                boost::is_convertible<
                    typename add<Difference, It>::type, It
                >,

                boost::is_convertible<
                    typename isub<It, Difference>::type,
                    typename boost::add_lvalue_reference<It>::type
                >,

                boost::mpl::and_<

                boost::is_convertible<
                    typename sub<It, Difference>::type, It
                >,

                boost::is_convertible<
                    typename sub<It, It>::type, Difference
                >,

                typename boost::mpl::if_<typename ReadableIterator<It>::type,
                    boost::is_convertible<
                        typename subscript<It, Difference>::type, Value
                    >,
                    boost::mpl::true_
                >::type,

                typename boost::mpl::if_<
                    typename WriteableIterator<It, Value>::type,
                    boost::is_convertible<
                        typename subscript_assign<It, Difference, Value>::type,
                        Value
                    >,
                    boost::mpl::true_
                >::type

                > // boost::mpl::and_
                > // boost::mpl::and_
            >::type type;
    static bool const value = type::value;
};

} // end namespace duck

#endif // !DUCK_RANDOM_ACCESS_ITERATOR_HPP
