/**
 * This file defines the `SwappableIterator` concept.
 */

#ifndef DUCK_SWAPPABLE_ITERATOR_HPP
#define DUCK_SWAPPABLE_ITERATOR_HPP

#include <duck/assignable.hpp>
#include <duck/copy_constructible.hpp>
#include <duck/detail/test_expression.hpp>

#include <algorithm>
#include <boost/mpl/and.hpp>
#include <boost/mpl/or.hpp>
#include <boost/utility/declval.hpp>


namespace duck {

/**
 * Metafunction returning whether an `Iterator` models the `SwappableIterator`
 * concept.
 */
template <typename Iterator>
class is_swappable_iterator {
    DUCK_I_TEST_EXPRESSION(iter_swap_adl,
                    iter_swap(boost::declval<I&>(), boost::declval<I&>()),
                    typename I);

    DUCK_I_TEST_EXPRESSION(std_iter_swap,
                std::iter_swap(boost::declval<I&>(), boost::declval<I&>()),
                typename I);

    // Because of the current implementation of `std::iter_swap`, compilation
    // will fail instead of triggering SFINAE if `Iterator` is not
    // dereferenceable or if the result of dereferencing it is not assignable.
    // Therefore, we will make sure that It fulfils these conditions on our
    // side.
    DUCK_I_TEST_EXPRESSION(swap_adl,
                    swap(boost::declval<I&>(), boost::declval<I&>()),
                    typename I);

    DUCK_I_TEST_EXPRESSION(dereference, *boost::declval<I&>(), typename I);

    template <typename I>
    struct std_iter_swap_is_valid {
        typedef typename dereference<I>::type Dereference;
        // dereferenceable && (has adl swap || is assignable)
        typedef typename boost::mpl::and_<
                    detail::is_valid<Dereference>,
                    boost::mpl::or_<
                        detail::is_valid<
                            typename swap_adl<Dereference>::type
                        >,
                        is_assignable<Dereference>
                    >
                >::type type;
    };

public:
    typedef typename boost::mpl::and_<
                is_copy_constructible<Iterator>,
                boost::mpl::or_<
                    detail::is_valid<typename iter_swap_adl<Iterator>::type>,
                    std_iter_swap_is_valid<Iterator>
                >
            >::type type;
    static bool const value = type::value;
};

//! `SwappableIterator` concept.
struct SwappableIterator {
    template <typename Iterator>
    struct apply
        : is_swappable_iterator<Iterator>
    { };
};

} // end namespace duck

#endif // !DUCK_SWAPPABLE_ITERATOR_HPP
