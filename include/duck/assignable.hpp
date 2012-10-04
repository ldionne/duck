/**
 * This file defines the @em Assignable concept.
 */

#ifndef DUCK_ASSIGNABLE_HPP
#define DUCK_ASSIGNABLE_HPP

#include <mpl11/eval_if.hpp>
#include <type_traits>
#include <utility>


namespace duck {

/**
 * Metafunction returning whether @em T models the @em Assignable concept.
 */
template <typename T>
class Assignable {
    using Tgt = typename std::add_lvalue_reference<T>::type;
    using Src = typename std::add_lvalue_reference<
                    typename std::add_const<
                        typename std::remove_reference<T>::type>::type>::type;

    template <typename ...>
    struct continue_concept
        : std::is_convertible<
            decltype(std::declval<Tgt>() = std::declval<Src>()),
            typename std::add_lvalue_reference<T>::type
        >
    { };

public:
    using type =
        typename mpl11::eval_if<
            typename std::is_assignable<Tgt, Src>::type,
            continue_concept<>,
            std::false_type
        >::type;
    static auto const value = type::value;
};

} // end namespace duck

#endif // !DUCK_ASSIGNABLE_HPP
