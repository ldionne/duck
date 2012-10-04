/**
 * This file defines the @em DUCK_TEST_EXPRESSION helper macro.
 */

#ifndef DUCK_DETAIL_TEST_EXPRESSION_HPP
#define DUCK_DETAIL_TEST_EXPRESSION_HPP

#include <mpl11/eval_if.hpp>
#include <mpl11/identity.hpp>
#include <mpl11/not.hpp>
#include <type_traits>
#include <utility>


namespace duck {
    namespace detail {
        struct invalid { };

       /**
        * Metafunction returning whether its argument is valid, i.e.
        * if it is not the same as `duck::detail::invalid`.
        */
       template <typename T>
       struct is_valid : mpl11::not_<std::is_same<T, invalid>> { };
    }
}

#define DUCK_I_TEST_BASE(name, as_expression, as_type, ...)                 \
template <typename ...Args>                                                 \
class name {                                                                \
    template <__VA_ARGS__> static                                           \
    /* void() is used to make sure no user-defined comma operator is used */\
    decltype((as_expression, void(), ::std::true_type()))                   \
    test_validity(void*);                                                   \
                                                                            \
    template <__VA_ARGS__> static                                           \
    ::std::false_type test_validity(...);                                   \
                                                                            \
    template <__VA_ARGS__>                                                  \
    struct delayed_type {                                                   \
        using type = as_type;                                               \
    };                                                                      \
                                                                            \
    using is_valid = decltype(test_validity<Args...>(nullptr));             \
                                                                            \
public:                                                                     \
    using type =                                                            \
        typename ::mpl11::eval_if<is_valid,                                 \
            delayed_type<Args...>,                                          \
            ::mpl11::identity<::duck::detail::invalid>                      \
        >::type;                                                            \
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
    DUCK_I_TEST_BASE(name, ::std::declval<type>(), type, __VA_ARGS__)

#endif // !DUCK_DETAIL_TEST_EXPRESSION_HPP
