/**
 * This file defines the @em LvalueIterator concept.
 */

#ifndef DUCK_LVALUE_ITERATOR_HPP
#define DUCK_LVALUE_ITERATOR_HPP

#include <duck/detail/config.hpp>
#include <duck/detail/test_expression.hpp>

#include <mpl11/and.hpp>
#include <type_traits>
#include <utility>


namespace duck {

/**
 * Metafunction returning whether @em It models the @em LvalueIterator
 * concept.
 */
template <typename It>
class LvalueIterator {
    DUCK_I_TEST_EXPRESSION(dereference, const_cast<V&>(*std::declval<I>()),
                                                    typename I, typename V);
    DUCK_I_TEST_TYPE(value_type_,
                typename detail::iterator_traits<I>::value_type, typename I);
    using Value = typename value_type_<It>::type;

public:
    using type =
        typename mpl11::and_<
            detail::is_valid<Value>,
            std::is_convertible<
                typename dereference<It, Value>::type,
                typename std::add_lvalue_reference<Value>::type
            >
        >::type;
    static auto const value = type::value;
};

} // end namespace duck

#endif // !DUCK_LVALUE_ITERATOR_HPP
