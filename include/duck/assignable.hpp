/**
 * This file defines the `Assignable` concept.
 */

#ifndef DUCK_ASSIGNABLE_HPP
#define DUCK_ASSIGNABLE_HPP

#include <duck/detail/test_expression.hpp>

#include <boost/mpl/bool.hpp>
#include <boost/mpl/eval_if.hpp>
#include <boost/type_traits/add_const.hpp>
#include <boost/type_traits/add_lvalue_reference.hpp>
#include <boost/type_traits/is_convertible.hpp>
#include <boost/type_traits/remove_reference.hpp>
#include <boost/utility/declval.hpp>


namespace duck {

//! Metafunction returning whether `T` models the `Assignable` concept.
template <typename T>
class is_assignable {
    DUCK_I_TEST_EXPRESSION(assignment,
                           boost::declval<Tgt>() = boost::declval<Src>(),
                           typename Tgt, typename Src);

    typedef typename boost::add_lvalue_reference<T>::type Tgt;
    typedef typename boost::add_lvalue_reference<
                typename boost::add_const<
                    typename boost::remove_reference<T>::type
                >::type
            >::type Src;

    template <typename Tgt, typename Src>
    struct continue_concept
        : boost::is_convertible<
            decltype(boost::declval<Tgt>() = boost::declval<Src>()),
            typename boost::add_lvalue_reference<T>::type
        >
    { };

public:
    typedef typename boost::mpl::eval_if<
                detail::is_valid<typename assignment<Tgt, Src>::type>,
                continue_concept<Tgt, Src>,
                boost::mpl::false_
            >::type type;
    static bool const value = type::value;
};

//! `Assignable` concept.
struct Assignable {
    template <typename T>
    struct apply
        : is_assignable<T>
    { };
};

} // end namespace duck

#endif // !DUCK_ASSIGNABLE_HPP
