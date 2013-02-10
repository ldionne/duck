/**
 * This file defines the `LessThanComparable` concept.
 */

#ifndef DUCK_LESS_THAN_COMPARABLE_HPP
#define DUCK_LESS_THAN_COMPARABLE_HPP

#include <duck/detail/test_expression.hpp>

#include <boost/type_traits/is_convertible.hpp>
#include <boost/utility/declval.hpp>


namespace duck {

/**
 * Metafunction returning whether `T` models the `LessThanComparable`
 * concept.
 */
template <typename T>
class is_less_than_comparable {
    DUCK_I_TEST_EXPRESSION(less_than,
                    boost::declval<U>() < boost::declval<U>(), typename U);

public:
    typedef typename boost::is_convertible<
                typename less_than<T>::type, bool
            >::type type;
    static bool const value = type::value;
};

struct LessThanComparable {
    template <typename T>
    struct apply
        : is_less_than_comparable<T>
    { };
};

} // end namespace duck

#endif // !DUCK_LESS_THAN_COMPARABLE_HPP
