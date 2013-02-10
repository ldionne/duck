/**
 * This file defines the @em EqualityComparable concept.
 */

#ifndef DUCK_EQUALITY_COMPARABLE_HPP
#define DUCK_EQUALITY_COMPARABLE_HPP

#include <duck/detail/test_expression.hpp>

#include <boost/mpl/and.hpp>
#include <type_traits>
#include <utility>


namespace duck {

/**
 * Metafunction returning whether @em T models the @em EqualityComparable
 * concept.
 */
template <typename T>
class EqualityComparable {
    DUCK_I_TEST_EXPRESSION(equal, std::declval<U>() == std::declval<V>(),
                                                    typename U, typename V);
    DUCK_I_TEST_EXPRESSION(not_equal, std::declval<U>() != std::declval<V>(),
                                                    typename U, typename V);

public:
    using type =
        typename boost::mpl::and_<
            std::is_convertible<typename equal<T, T>::type, bool>,
            std::is_convertible<typename not_equal<T, T>::type, bool>
        >::type;
    static bool const value = type::value;
};

} // end namespace duck

#endif // !DUCK_EQUALITY_COMPARABLE_HPP
