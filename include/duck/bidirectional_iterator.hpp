/**
 * This file defines the @em BidirectionalIterator concept.
 */

#ifndef DUCK_BIDIRECTIONAL_ITERATOR_HPP
#define DUCK_BIDIRECTIONAL_ITERATOR_HPP

#include <duck/detail/test_expression.hpp>
#include <duck/forward_iterator.hpp>

#include <mpl11/and.hpp>
#include <type_traits>
#include <utility>


namespace duck {

/**
 * Metafunction returning whether @em It models the @em BidirectionalIterator
 * concept.
 */
template <typename It>
class BidirectionalIterator {
    DUCK_I_TEST_EXPRESSION(pre_decrement, --std::declval<I&>(), typename I);
    DUCK_I_TEST_EXPRESSION(post_decrement, std::declval<I&>()--, typename I);

public:
    using type =
        typename mpl11::and_<
            ForwardIterator<It>,

            std::is_convertible<
                typename pre_decrement<It>::type,
                typename std::add_lvalue_reference<It>::type
            >,

            std::is_convertible<
                typename post_decrement<It>::type, It
            >
        >::type;
    static auto const value = type::value;
};

} // end namespace duck

#endif // !DUCK_BIDIRECTIONAL_ITERATOR_HPP
