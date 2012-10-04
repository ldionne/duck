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

#include <mpl11/and.hpp>
#include <mpl11/if.hpp>
#include <type_traits>
#include <utility>


namespace duck {

/**
 * Metafunction returning whether @em It models the @em RandomAccessIterator
 * concept.
 */
template <typename It>
class RandomAccessIterator {
    DUCK_I_TEST_EXPRESSION(iadd, std::declval<I&>() += std::declval<N>(),
                                                    typename I, typename N);
    DUCK_I_TEST_EXPRESSION(add, std::declval<A>() + std::declval<B>(),
                                                    typename A, typename B);
    DUCK_I_TEST_EXPRESSION(isub, std::declval<I&>() -= std::declval<N>(),
                                                    typename I, typename N);
    DUCK_I_TEST_EXPRESSION(sub, std::declval<A>() - std::declval<B>(),
                                                    typename A, typename B);
    // Only if ReadableIterator.
    DUCK_I_TEST_EXPRESSION(subscript, std::declval<I>()[std::declval<N>()],
                                                    typename I, typename N);
    // Only if WriteableIterator.
    DUCK_I_TEST_EXPRESSION(subscript_assign,
        std::declval<I>()[std::declval<N>()] = std::declval<V>(),
                                        typename I, typename N, typename V);
    DUCK_I_TEST_TYPE(value_type_,
                typename detail::iterator_traits<I>::value_type, typename I);
    DUCK_I_TEST_TYPE(difference_type_,
            typename detail::iterator_traits<I>::difference_type, typename I);

    using Value = typename value_type_<It>::type;
    using Difference = typename difference_type_<It>::type;

public:
    using type =
        typename mpl11::and_<
            BidirectionalIterator<It>,
            Comparable<It>,

            detail::is_valid<Value>,
            detail::is_valid<Difference>,

            std::is_convertible<
                typename iadd<It, Difference>::type,
                typename std::add_lvalue_reference<It>::type
            >,

            std::is_convertible<
                typename add<It, Difference>::type, It
            >,

            std::is_convertible<
                typename add<Difference, It>::type, It
            >,

            std::is_convertible<
                typename isub<It, Difference>::type,
                typename std::add_lvalue_reference<It>::type
            >,

            std::is_convertible<
                typename sub<It, Difference>::type, It
            >,

            std::is_convertible<
                typename sub<It, It>::type, Difference
            >,

            typename mpl11::if_<typename ReadableIterator<It>::type,
                std::is_convertible<
                    typename subscript<It, Difference>::type, Value
                >,
                std::true_type
            >::type,

            typename mpl11::if_<typename WriteableIterator<It, Value>::type,
                std::is_convertible<
                    typename subscript_assign<It, Difference, Value>::type,
                    Value
                >,
                std::true_type
            >::type
        >::type;
    static auto const value = type::value;
};

} // end namespace duck

#endif // !DUCK_RANDOM_ACCESS_ITERATOR_HPP
