/**
 * This file defines the @em ReadableIterator concept.
 */

#ifndef DUCK_READABLE_ITERATOR_HPP
#define DUCK_READABLE_ITERATOR_HPP

#include <duck/assignable.hpp>
#include <duck/copy_constructible.hpp>
#include <duck/detail/config.hpp>
#include <duck/detail/test_expression.hpp>

#include <mpl11/and.hpp>
#include <type_traits>
#include <utility>


namespace duck {

/**
 * Metafunction returning whether @em It models the @em ReadableIterator
 * concept.
 */
template <typename It>
class ReadableIterator {
    DUCK_I_TEST_EXPRESSION(dereference, *std::declval<I>(), typename I);
    DUCK_I_TEST_TYPE(value_type_,
                typename detail::iterator_traits<I>::value_type, typename I);
    using Value = typename value_type_<It>::type;

public:
    using type =
        typename mpl11::and_<
            Assignable<It>,
            CopyConstructible<It>,

            detail::is_valid<Value>,
            std::is_convertible<typename dereference<It>::type, Value>

            // We should also check whether it->m returns a reference to the
            // member inside its pointee, but that would require asking a
            // pointer to a member, which seems overly restrictive. Also,
            // non class-or-struct types don't care about this.

        >::type;
    static auto const value = type::value;
};

} // end namespace duck

#endif // !DUCK_READABLE_ITERATOR_HPP
