/**
 * This file defines the `RandomAccessIterator` concept.
 */

#ifndef DUCK_RANDOM_ACCESS_ITERATOR_HPP
#define DUCK_RANDOM_ACCESS_ITERATOR_HPP

#include <duck/bidirectional_iterator.hpp>
#include <duck/comparable.hpp>
#include <duck/detail/test_expression.hpp>
#include <duck/models.hpp>
#include <duck/readable_iterator.hpp>
#include <duck/writeable_iterator.hpp>

#include <boost/mpl/and.hpp>
#include <boost/mpl/bool.hpp>
#include <boost/mpl/if.hpp>
#include <boost/type_traits/add_lvalue_reference.hpp>
#include <boost/type_traits/is_convertible.hpp>
#include <boost/utility/declval.hpp>
#include <iterator>


namespace duck {

namespace random_access_detail {
template <typename Iterator>
class is_random_access_iterator_impl {
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
                typename std::iterator_traits<I>::value_type, typename I);
    DUCK_I_TEST_TYPE(difference_type_,
            typename std::iterator_traits<I>::difference_type, typename I);

    typedef typename value_type_<Iterator>::type Value;
    typedef typename difference_type_<Iterator>::type Difference;

public:
    typedef typename boost::mpl::and_<
                is_bidirectional_iterator<Iterator>,
                is_comparable<Iterator>,

                detail::is_valid<Value>,
                detail::is_valid<Difference>,

                boost::mpl::and_<

                boost::is_convertible<
                    typename iadd<Iterator, Difference>::type,
                    typename boost::add_lvalue_reference<Iterator>::type
                >,

                boost::is_convertible<
                    typename add<Iterator, Difference>::type, Iterator
                >,

                boost::is_convertible<
                    typename add<Difference, Iterator>::type, Iterator
                >,

                boost::is_convertible<
                    typename isub<Iterator, Difference>::type,
                    typename boost::add_lvalue_reference<Iterator>::type
                >,

                boost::mpl::and_<

                boost::is_convertible<
                    typename sub<Iterator, Difference>::type, Iterator
                >,

                boost::is_convertible<
                    typename sub<Iterator, Iterator>::type, Difference
                >,

                typename boost::mpl::if_<
                    is_readable_iterator<Iterator>,
                    boost::is_convertible<
                        typename subscript<Iterator, Difference>::type, Value
                    >,
                    boost::mpl::true_
                >::type,

                typename boost::mpl::if_<
                    is_writeable_iterator<Iterator, Value>,
                    boost::is_convertible<
                        typename subscript_assign<
                            Iterator, Difference, Value
                        >::type,
                        Value
                    >,
                    boost::mpl::true_
                >::type

                > // boost::mpl::and_
                > // boost::mpl::and_
            >::type type;
    static bool const value = type::value;
};
} // end namespace random_access_detail

//! `RandomAccessIterator` concept.
struct RandomAccessIterator {
    template <typename Iterator>
    struct apply
        : random_access_detail::is_random_access_iterator_impl<Iterator>
    { };
};

/**
 * Metafunction returning whether an `Iterator` models the
 * `RandomAccessIterator` concept.
 */
template <typename Iterator>
struct is_random_access_iterator
    : models<RandomAccessIterator, Iterator>
{ };

} // end namespace duck

#endif // !DUCK_RANDOM_ACCESS_ITERATOR_HPP
