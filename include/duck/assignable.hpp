/**
 * This file defines the @em Assignable concept.
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

/**
 * Metafunction returning whether @em T models the @em Assignable concept.
 */
template <typename T>
class Assignable {
    DUCK_I_TEST_EXPRESSION(assignment,
                           boost::declval<Tgt>() = boost::declval<Src>(),
                           typename Tgt, typename Src);

    using Tgt = typename boost::add_lvalue_reference<T>::type;
    using Src = typename boost::add_lvalue_reference<
                    typename boost::add_const<
                        typename boost::remove_reference<T>::type
                    >::type
                >::type;

    template <typename Tgt, typename Src>
    struct continue_concept
        : std::is_convertible<
            decltype(boost::declval<Tgt>() = boost::declval<Src>()),
            typename boost::add_lvalue_reference<T>::type
        >
    { };

public:
    using type =
        typename boost::mpl::eval_if<
            detail::is_valid<typename assignment<Tgt, Src>::type>,
            continue_concept<Tgt, Src>,
            boost::mpl::false_
        >::type;
    static bool const value = type::value;
};

} // end namespace duck

#endif // !DUCK_ASSIGNABLE_HPP
