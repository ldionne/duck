/**
 * This file defines the @em LessThanComparable concept.
 */

#ifndef DUCK_LESS_THAN_COMPARABLE_HPP
#define DUCK_LESS_THAN_COMPARABLE_HPP

#include <duck/detail/test_expression.hpp>

#include <type_traits>
#include <utility>


namespace duck {

/**
 * Metafunction returning whether @em T models the @em LessThanComparable
 * concept.
 */
template <typename T>
class LessThanComparable {
    DUCK_I_TEST_EXPRESSION(less_than, std::declval<U>() < std::declval<U>(),
                                                                typename U);

public:
    using type = typename std::is_convertible<
                    typename less_than<T>::type, bool
                >::type;
    static auto const value = type::value;
};

} // end namespace duck

#endif // !DUCK_LESS_THAN_COMPARABLE_HPP
