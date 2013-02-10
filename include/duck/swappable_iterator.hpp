/**
 * This file defines the @em SwappableIterator concept.
 */

#ifndef DUCK_SWAPPABLE_ITERATOR_HPP
#define DUCK_SWAPPABLE_ITERATOR_HPP

#include <duck/assignable.hpp>
#include <duck/copy_constructible.hpp>
#include <duck/detail/test_expression.hpp>

#include <algorithm>
#include <boost/mpl/and.hpp>
#include <boost/mpl/or.hpp>
#include <utility>


namespace duck {

/**
 * Metafunction returning whether @em It models the @em SwappableIterator
 * concept.
 */
template <typename It>
class SwappableIterator {
    DUCK_I_TEST_EXPRESSION(iter_swap_adl,
            iter_swap(std::declval<I&>(), std::declval<I&>()), typename I);
    DUCK_I_TEST_EXPRESSION(std_iter_swap,
        std::iter_swap(std::declval<I&>(), std::declval<I&>()), typename I);

    // Because of the current implementation of `std::iter_swap`, compilation
    // will fail instead of triggering SFINAE if It is not dereferenceable or
    // if the result of dereferencing it is not assignable. Therefore, we
    // will make sure that It fulfils these conditions on our side.
    DUCK_I_TEST_EXPRESSION(swap_adl,
                    swap(std::declval<I&>(), std::declval<I&>()), typename I);
    DUCK_I_TEST_EXPRESSION(dereference, *std::declval<I&>(), typename I);

    template <typename I>
    struct std_iter_swap_is_valid {
        using Dereference = typename dereference<I>::type;
        // dereferenceable && (has adl swap || is assignable)
        using type =
            typename boost::mpl::and_<
                detail::is_valid<Dereference>,
                boost::mpl::or_<
                    detail::is_valid<typename swap_adl<Dereference>::type>,
                    Assignable<Dereference>
                >
            >::type;
    };

public:
    using type =
        typename boost::mpl::and_<
            CopyConstructible<It>,
            boost::mpl::or_<
                detail::is_valid<typename iter_swap_adl<It>::type>,
                std_iter_swap_is_valid<It>
            >
        >::type;
    static bool const value = type::value;
};

} // end namespace duck

#endif // !DUCK_SWAPPABLE_ITERATOR_HPP
