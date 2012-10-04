/**
 * This file defines the @em WriteableIterator concept.
 */

#ifndef DUCK_WRITEABLE_ITERATOR_HPP
#define DUCK_WRITEABLE_ITERATOR_HPP

#include <duck/copy_constructible.hpp>
#include <duck/detail/config.hpp>
#include <duck/detail/test_expression.hpp>

#include <mpl11/and.hpp>
#include <utility>


namespace duck {

/**
 * Metafunction returning whether @em It models the @em WriteableIterator
 * concept.
 */
template <typename It,
          typename Value = typename detail::iterator_traits<It>::value_type>
class WriteableIterator {
    DUCK_I_TEST_EXPRESSION(assign_deref,
            *std::declval<I>() = std::declval<V>(), typename I, typename V);

public:
    using type =
        typename mpl11::and_<
            CopyConstructible<It>,
            detail::is_valid<typename assign_deref<It, Value>::type>
        >::type;
    static auto const value = type::value;
};

} // end namespace duck

#endif // !DUCK_WRITEABLE_ITERATOR_HPP
