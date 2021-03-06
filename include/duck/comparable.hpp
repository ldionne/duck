/**
 * This file defines the `Comparable` concept.
 */

#ifndef DUCK_COMPARABLE_HPP
#define DUCK_COMPARABLE_HPP

#include <duck/detail/test_expression.hpp>

#include <boost/mpl/and.hpp>
#include <boost/type_traits/is_convertible.hpp>
#include <boost/utility/declval.hpp>


namespace duck {

//! Metafunction returning whether `T` models the `Comparable` concept.
template <typename T>
class is_comparable {
    DUCK_I_TEST_EXPRESSION(lt, boost::declval<U>() < boost::declval<U>(),
                                                                typename U);
    DUCK_I_TEST_EXPRESSION(gt, boost::declval<U>() > boost::declval<U>(),
                                                                typename U);
    DUCK_I_TEST_EXPRESSION(le, boost::declval<U>() <= boost::declval<U>(),
                                                                typename U);
    DUCK_I_TEST_EXPRESSION(ge, boost::declval<U>() >= boost::declval<U>(),
                                                                typename U);

public:
    typedef typename boost::mpl::and_<
                boost::is_convertible<typename lt<T>::type, bool>,
                boost::is_convertible<typename gt<T>::type, bool>,
                boost::is_convertible<typename le<T>::type, bool>,
                boost::is_convertible<typename ge<T>::type, bool>
            >::type type;
    static bool const value = type::value;
};

//! `Comparable` concept.
struct Comparable {
    template <typename T>
    struct apply
        : is_comparable<T>
    { };
};

} // end namespace duck

#endif // !DUCK_COMPARABLE_HPP
