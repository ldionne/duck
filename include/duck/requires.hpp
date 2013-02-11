/**
 * This file defines facilities to perform concept-based overloading.
 */

#ifndef DUCK_REQUIRES_HPP
#define DUCK_REQUIRES_HPP

#include <duck/detail/mpl_extensions.hpp>
#include <duck/models.hpp>

#include <boost/config.hpp>
#include <boost/mpl/and.hpp>
#include <boost/mpl/apply.hpp>
#include <boost/mpl/back.hpp>
#include <boost/mpl/bool.hpp>
#include <boost/mpl/contains.hpp>
#include <boost/mpl/copy_if.hpp>
#include <boost/mpl/deref.hpp>
#include <boost/mpl/find_if.hpp>
#include <boost/mpl/not.hpp>
#include <boost/mpl/placeholders.hpp>
#include <boost/mpl/pop_back.hpp>
#include <boost/mpl/push_front.hpp>
#include <boost/mpl/quote.hpp>
#include <boost/mpl/vector.hpp>
#include <boost/preprocessor/cat.hpp>
#include <boost/type_traits/is_same.hpp>
#include <boost/utility/enable_if.hpp>


namespace duck {

// Note to self: Storing the visited concepts in a list ordered by concept
//               specificity could make things much more efficient.

/**
 * Tag to signal the failure of a concept-based overload resolution.
 *
 * @note It is important that this stays an incomplete type.
 */
struct concept_based_overload_resolution_failed
#if defined(BOOST_NO_CXX11_DECLTYPE_N3276)
{
    // On GCC, incomplete types can't appear inside decltype.
    // Instead of failing on valid decltypes, we will trigger a link time
    // error when `concept_based_overload_resolution_failed` is used.
    ~concept_based_overload_resolution_failed();
}
#endif
;

/**
 * Trait that must be specialized by new concepts to specify a partial order
 * between concepts.
 *
 * @note It is only needed to specialize one side of the trait, i.e.
 *       `is_more_specific_than<A, B> : true` does not require the definition
 *       of `is_more_specific_than<B, A> : false` too.
 *
 * @note `is_more_specific_than<A, B>` is conceptually equivalent to `A < B`
 *       where the `<` operator is a partial order meaning `A` is less
 *       specific than `B`.
 */
template <typename A, typename B, typename Enable = void>
struct is_more_specific_than
    : boost::mpl::not_<is_more_specific_than<B, A, Enable> >
{ };

/**
 * Specialization of the `is_more_specific_than` trait for the trivial case
 * where both concepts are the same, i.e. `is_more_specific_than<A, A>`. In
 * this trivial case, the trait is obviously false.
 */
template <typename Concept, typename Enable>
struct is_more_specific_than<Concept, Concept, Enable>
    : boost::mpl::false_
{ };

/**
 * Metafunction class returning the result of calling the function overloaded
 * by `Family` at the current stage of the overload resolution.
 *
 * @note This metafunction class may be specialized by each family of
 *       overload, or the family may define a
 *       `perform_overload<OverloadResolution>` nested metafunction class
 *       accepting arguments to perform the overload.
 */
template <typename Family, typename OverloadResolution>
struct perform_overload {
    template <typename ...Args>
    struct apply
        : boost::mpl::apply<
            typename Family::template perform_overload<OverloadResolution>,
            Args...
        >
    { };
};

namespace requires_detail {
//! Compile-time data structure storing state during an overload resolution.
template <typename Family, typename VisitedConcepts = boost::mpl::vector<> >
struct overload_resolution {
    typedef VisitedConcepts visited_concepts;
    typedef Family family;

    typedef overload_resolution type; // to make it a metafunction
};

/**
 * Add a `Concept` to the list of concepts visited during the current
 * overload resolution.
 */
template <typename Concept, typename OverloadResolution>
struct mark_as_visited
    : overload_resolution<
        typename OverloadResolution::family,
        typename boost::mpl::push_front<
            typename OverloadResolution::visited_concepts, Concept
        >::type
    >
{ };

/**
 * Metafunction returning whether a `Concept` has already been visited during
 * the current overload resolution.
 */
template <typename Concept, typename OverloadResolution>
struct has_visited
    : boost::mpl::contains<
        typename OverloadResolution::visited_concepts, Concept
    >
{ };

/**
 * Metafunction returning whether a `Concept` is the most specific that was
 * visited so far during an overload resolution.
 */
template <typename Concept, typename OverloadResolution>
struct is_most_specific_so_far
    : boost::mpl::none_of<
        typename OverloadResolution::visited_concepts,
        is_more_specific_than<Concept, boost::mpl::_1>
    >
{ };

/**
 * Metafunction returning whether a `Concept` is the best match for a `Type`
 * so far during an overload resolution.
 */
template <typename Type, typename Concept, typename OverloadResolution>
struct is_best_match_so_far
    : boost::mpl::and_<
        boost::mpl::not_<has_visited<Concept, OverloadResolution> >,
        is_most_specific_so_far<Concept, OverloadResolution>,
        models<Concept, Type>
    >
{ };

/**
 * Metafunction class returning whether a `Concept` is the most specific
 * concept modeled by a `Type` for which an overload exists according to
 * the family present in `OverloadResolution`.
 */
template <typename Type, typename Concept, typename OverloadResolution>
class clause_passes {
    template <typename ...Args>
    struct result_of_calling_the_function_with
        : boost::mpl::apply<
            perform_overload<
                typename OverloadResolution::family,
                typename mark_as_visited<Concept, OverloadResolution>::type
            >,
            Args...
        >
    { };

    template <typename ...Args>
    struct there_are_no_better_overloads
        : boost::is_same<
            typename result_of_calling_the_function_with<Args...>::type,
            concept_based_overload_resolution_failed
        >
    { };

public:
    template <typename ...Args>
    struct apply
        : boost::mpl::and_<
            is_best_match_so_far<Type, Concept, OverloadResolution>,
            there_are_no_better_overloads<Args...>
        >
    { };
};


//! Requires a `Type` to be a model of a `Concept` in a `require` clause.
template <typename Concept, typename Type> struct model_of {
    typedef Concept concept;
    typedef Type model;
};

template <typename T>
struct is_model_of_clause
    : boost::mpl::false_
{ };

template <typename Concept, typename Type>
struct is_model_of_clause<model_of<Concept, Type> >
    : boost::mpl::true_
{ };

//! Provides the current `OverloadResolution` state to a `require` clause.
template <typename Family>
struct overload_resolution_state {
    typedef overload_resolution<Family> type;
};

template <typename ...Args>
struct overload_resolution_state<overload_resolution<Args...> > {
    typedef overload_resolution<Args...> type;
};

template <typename T>
struct is_overload_resolution_state
    : boost::mpl::false_
{ };

template <typename OverloadResolution>
struct is_overload_resolution_state<
                            overload_resolution_state<OverloadResolution> >
    : boost::mpl::true_
{ };

/**
 * Provides the template parameters to pass to the next function that will be
 * tried in the same overload family.
 *
 * @note The overload information is handled by the library and must not be
 *       passed here.
 */
template <typename ...Params> struct template_parameters;

template <typename T>
struct is_template_parameters
    : boost::mpl::false_
{ };

template <typename ...Params>
struct is_template_parameters<template_parameters<Params...> >
    : boost::mpl::true_
{ };

template <typename ...Blob>
struct requires_impl {
    template <typename F, typename Pack> struct apply_pack;
    template <typename F, template <typename ...> class Pack, typename ...Args>
    struct apply_pack<F, Pack<Args...> >
        : boost::mpl::apply<F, Args...>
    { };

    typedef typename boost::mpl::back<
                boost::mpl::vector<Blob...>
            >::type return_type;

    typedef typename boost::mpl::pop_back<
                boost::mpl::vector<Blob...>
            >::type arguments;

    // Gather all the model_of clauses
    typedef typename boost::mpl::copy_if<
                arguments, boost::mpl::quote1<is_model_of_clause>
            >::type clauses;

    // Gather the template parameters to be passed to subsequent overloads
    typedef typename boost::mpl::deref<typename boost::mpl::find_if<
                arguments, boost::mpl::quote1<is_template_parameters>
            >::type>::type template_parameters;

    // Fetch the current overload resolution state
    typedef typename boost::mpl::deref<typename boost::mpl::find_if<
                arguments, boost::mpl::quote1<is_overload_resolution_state>
            >::type>::type::type current_state;

    struct clause_is_respected {
        template <typename Clause>
        struct apply
            : apply_pack<
                clause_passes<
                    typename Clause::model,
                    typename Clause::concept,
                    current_state
                >,
                template_parameters
            >
        { };
    };

    typedef typename boost::mpl::all_of<
                clauses, clause_is_respected
            >::type type;
    static bool const value = type::value;
};
} // end namespace requires_detail

// Named parameters for `requires`
using requires_detail::model_of;
using requires_detail::overload_resolution_state;
using requires_detail::template_parameters;

/**
 * Metafunction to perform concept-based overloading.
 *
 * Examples of usage:
 *
 *      typename requires<
 *                  model_of<SomeConcept, SomeType>,
 *                  model_of<SomeOtherConcept, SomeOtherType>,
 *
 *                  overload_resolution_state<State>,
 *                  template_parameters<SomeType, SomeOtherType>,
 *                  return_type
 *      >::type
 */
template <typename ...Args>
struct requires
    : boost::enable_if<
        requires_detail::requires_impl<Args...>,
        typename requires_detail::requires_impl<Args...>::return_type
    >
{ };

/**
 * Macro to enable concept overloading on a family of overloads.
 *
 * @param FUNCTION The name of the function that is overloaded using concepts.
 * @param CALL An expression calling the function. This expression can use
 *        the templates parameters provided in `__VA_ARGS__`.
 * @param ... A list of `typename T` template parameters that will be usable
 *            within the `CALL` expression. The `State` parameter is always
 *            available within the `CALL` expression and it represents the
 *            current state of the overload resolution.
 *
 * Once instantiated, this macro will create a type named `FUNCTION` inside a
 * `tag` namespace. This type should be used as the default overload
 * resolution state for overloads within this family.
 */
#define DUCK_ENABLE_CONCEPT_OVERLOADING(FUNCTION, CALL, .../*typenames*/)   \
    ::duck::concept_based_overload_resolution_failed FUNCTION(...);         \
    /* This MUST be defined in the same namespace as the FUNCTION in */     \
    /* order for FUNCTION to be found via ADL later on.              */     \
    struct BOOST_PP_CAT(FUNCTION, __LINE__) {                               \
        template <typename State>                                           \
        struct perform_overload {                                           \
            template <__VA_ARGS__>                                          \
            struct apply {                                                  \
                typedef decltype(CALL) type;                                \
            };                                                              \
        };                                                                  \
    };                                                                      \
    namespace tag {                                                         \
        typedef BOOST_PP_CAT(FUNCTION, __LINE__) FUNCTION;                  \
    }                                                                       \
/**/

} // end namespace duck

#endif // !DUCK_REQUIRES_HPP
