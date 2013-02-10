/**
 * This file defines the `EqualityComparable` concept.
 */

#ifndef DUCK_EQUALITY_COMPARABLE_HPP
#define DUCK_EQUALITY_COMPARABLE_HPP

#include <duck/detail/test_expression.hpp>

#include <boost/mpl/and.hpp>
#include <boost/type_traits/is_convertible.hpp>
#include <boost/utility/declval.hpp>


namespace duck {

/**
 * Metafunction returning whether `T` models the `EqualityComparable`
 * concept.
 */
template <typename T>
class is_equality_comparable {
    DUCK_I_TEST_EXPRESSION(equal, boost::declval<U>() == boost::declval<V>(),
                                                    typename U, typename V);
    DUCK_I_TEST_EXPRESSION(not_equal,
        boost::declval<U>() != boost::declval<V>(), typename U, typename V);

public:
    typedef typename boost::mpl::and_<
                boost::is_convertible<typename equal<T, T>::type, bool>,
                boost::is_convertible<typename not_equal<T, T>::type, bool>
            >::type type;
    static bool const value = type::value;
};

//! `EqualityComparable` concept.
struct EqualityComparable {
    template <typename T>
    struct apply
        : is_equality_comparable<T>
    { };
};

} // end namespace duck

#endif // !DUCK_EQUALITY_COMPARABLE_HPP
