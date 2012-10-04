/**
 * This file defines the @em IncrementableIterator concept.
 */

#ifndef DUCK_INCREMENTABLE_ITERATOR_HPP
#define DUCK_INCREMENTABLE_ITERATOR_HPP

#include <duck/assignable.hpp>
#include <duck/copy_constructible.hpp>
#include <duck/detail/test_expression.hpp>

#include <mpl11/and.hpp>
#include <type_traits>
#include <utility>


namespace duck {

/**
 * Metafunction returning whether @em It models the @em IncrementableIterator
 * concept.
 */
template <typename It>
class IncrementableIterator {
    DUCK_I_TEST_EXPRESSION(pre_increment, ++std::declval<I&>(), typename I);
    DUCK_I_TEST_EXPRESSION(post_increment, std::declval<I&>()++, typename I);

public:
    using type =
        typename mpl11::and_<
            Assignable<It>,
            CopyConstructible<It>,

            std::is_convertible<
                typename pre_increment<It>::type,
                typename std::add_lvalue_reference<It>::type
            >,

            std::is_convertible<
                typename post_increment<It>::type,
                typename std::remove_reference<It>::type
            >

        >::type;
    static auto const value = type::value;
};

} // end namespace duck

#endif // !DUCK_INCREMENTABLE_ITERATOR_HPP
