/**
 * This file defines the @em Comparable concept.
 */

#ifndef DUCK_COMPARABLE_HPP
#define DUCK_COMPARABLE_HPP

#include <duck/detail/test_expression.hpp>

#include <mpl11/and.hpp>
#include <type_traits>
#include <utility>


namespace duck {

/**
 * Metafunction returning whether @em T models the @em Comparable concept.
 */
template <typename T>
class Comparable {
    DUCK_I_TEST_EXPRESSION(lt, std::declval<U>() < std::declval<U>(),
                                                                typename U);
    DUCK_I_TEST_EXPRESSION(gt, std::declval<U>() > std::declval<U>(),
                                                                typename U);
    DUCK_I_TEST_EXPRESSION(le, std::declval<U>() <= std::declval<U>(),
                                                                typename U);
    DUCK_I_TEST_EXPRESSION(ge, std::declval<U>() >= std::declval<U>(),
                                                                typename U);

public:
    using type =
        typename mpl11::and_<
            std::is_convertible<typename lt<T>::type, bool>,
            std::is_convertible<typename gt<T>::type, bool>,
            std::is_convertible<typename le<T>::type, bool>,
            std::is_convertible<typename ge<T>::type, bool>
        >::type;
    static auto const value = type::value;
};

} // end namespace duck

#endif // !DUCK_COMPARABLE_HPP
