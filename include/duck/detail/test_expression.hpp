/**
 * This file defines the @em DUCK_I_TEST_EXPRESSION helper macro.
 */

#ifndef DUCK_DETAIL_TEST_EXPRESSION_HPP
#define DUCK_DETAIL_TEST_EXPRESSION_HPP

#include <boost/mpl/bool.hpp>
#include <boost/mpl/eval_if.hpp>
#include <boost/mpl/identity.hpp>
#include <boost/mpl/not.hpp>
#include <boost/type_traits/is_same.hpp>
#include <boost/utility/declval.hpp>


namespace duck {
    namespace detail {
        struct invalid { };

       /**
        * Metafunction returning whether its argument is valid, i.e.
        * if it is not the same as `duck::detail::invalid`.
        */
        template <typename T>
        struct is_valid
            : boost::mpl::not_<
                boost::is_same<T, invalid>
            >
        { };
    }
}

/**
 * Macro to make a name unique by mangling it with the line number.
 */
#define DUCK_I_UNIQUE(name) DUCK_I_CONCAT(name, __LINE__)
#define DUCK_I_CONCAT(a, b) DUCK_I_CONCAT_PRIMITIVE(a, b)
#define DUCK_I_CONCAT_PRIMITIVE(a, b) a ## b

#define DUCK_I_TEST_BASE(name, as_expression, as_type, ...)                 \
template <typename ...DUCK_I_UNIQUE(Args)>                                  \
class name {                                                                \
    template <__VA_ARGS__> static                                           \
    /* void() is used to make sure no user-defined comma operator is used */\
    decltype((as_expression), void(), ::boost::mpl::true_())                \
    test_validity(int);                                                     \
                                                                            \
    template <__VA_ARGS__> static                                           \
    ::boost::mpl::false_ test_validity(...);                                \
                                                                            \
    template <__VA_ARGS__>                                                  \
    struct delayed_type {                                                   \
        typedef as_type type;                                               \
    };                                                                      \
                                                                            \
    typedef decltype(test_validity<DUCK_I_UNIQUE(Args)...>(0)) is_valid;    \
                                                                            \
public:                                                                     \
    typedef typename ::boost::mpl::eval_if<is_valid,                        \
                delayed_type<DUCK_I_UNIQUE(Args)...>,                       \
                ::boost::mpl::identity<::duck::detail::invalid>             \
            >::type type;                                                   \
}                                                                           \
/**/

/**
 * This macro defines a metafunction that can be used to test for an
 * expression's validity depending of the types used inside it.
 *
 * Usage:
 *  DUCK_I_TEST_EXPRESSION(name of the metafunction to generate,
 *                         expression to test,
 *                         'typename' template parameters of the class...);
 *
 * `class_name<types_to_test_expression_with...>::type` is the type of the
 * expression if it is valid or `duck::detail::invalid` otherwise.
 *
 * Note: Providing at least one template parameter is required, although it
 *       can be left unused.
 */
#define DUCK_I_TEST_EXPRESSION(name, expression, ...) \
     DUCK_I_TEST_BASE(name, expression, decltype(expression), __VA_ARGS__)

/**
 * Same as above, but test for types instead of expressions.
 */
#define DUCK_I_TEST_TYPE(name, type, ...) \
    DUCK_I_TEST_BASE(name, ::boost::declval<type>(), type, __VA_ARGS__)

#endif // !DUCK_DETAIL_TEST_EXPRESSION_HPP
