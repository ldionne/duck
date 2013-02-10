/**
 * This file defines facilities to perform concept-based overloading.
 */

#ifndef DUCK_SANDBOX_CONCEPT_OVERLOAD_HPP
#define DUCK_SANDBOX_CONCEPT_OVERLOAD_HPP

#include <duck/detail/mpl_extensions.hpp>

#include <boost/mpl/and.hpp>
#include <boost/mpl/apply.hpp>
#include <boost/mpl/bool.hpp>
#include <boost/mpl/contains.hpp>
#include <boost/mpl/not.hpp>
#include <boost/mpl/placeholders.hpp>
#include <boost/mpl/push_front.hpp>
#include <boost/mpl/vector.hpp>
#include <boost/type_traits/is_same.hpp>


namespace duck {

// Note to self: Storing the visited concepts in a list ordered by concept
//               specificity could make things much more efficient.

/**
 * Tag to signal the failure of a concept-based overload resolution.
 *
 * @note It is important that this stays an incomplete type.
 */
struct concept_based_overload_resolution_failed;

//! Metafunction returning whether a `Type` is a model of a given `Concept`.
template <typename Concept, typename Type>
struct models
    : boost::mpl::apply<Concept, Type>
{ };

/**
 * Add a `Concept` to a list of concepts visited during the overload
 * resolution.
 */
template <typename Concept, typename VisitedConcepts>
struct mark_as_visited
    : boost::mpl::push_front<VisitedConcepts, Concept>
{ };

/**
 * Metafunction returning whether a `Concept` has already been visited during
 * the overload resolution.
 */
template <typename Concept, typename VisitedConcepts>
struct has_visited
    : boost::mpl::contains<VisitedConcepts, Concept>
{ };

/**
 * Trait that must be specialized by new concepts to specify a partial order
 * between concepts.
 *
 * @note `is_more_specific_than<A, B>` is conceptually equivalent to `A < B`
 *       where the `<` operator is a partial order meaning `A` is less
 *       specific than `B`.
 */
template <typename A, typename B>
struct is_more_specific_than;

/**
 * Specialization of the `is_more_specific_than` trait for the trivial case
 * where both concepts are the same, i.e. `is_more_specific_than<A, A>`. In
 * this trivial case, the trait is obviously false.
 */
template <typename Concept>
struct is_more_specific_than<Concept, Concept>
    : boost::mpl::false_
{ };

/**
 * Metafunction returning whether a `Concept` is the most specific in a list
 * of visited concepts.
 */
template <typename Concept, typename VisitedConcepts>
struct is_most_specific
    : boost::mpl::none_of<
        VisitedConcepts, is_more_specific_than<Concept, boost::mpl::_1>
    >
{ };

/**
 * Metafunction returning whether a `Concept` is the best match for a `Type`
 * so far according to a list of visited concepts.
 */
template <typename Type, typename Concept, typename VisitedConcepts>
struct is_best_so_far
    : boost::mpl::and_<
        boost::mpl::not_<has_visited<Concept, VisitedConcepts> >,
        is_most_specific<Concept, VisitedConcepts>,
        models<Concept, Type>
    >
{ };

/**
 * Metafunction class returning the result of calling the function overloaded
 * by `Family` after having visited a list of `VisitedConcepts`.
 *
 * @note This metafunction class must be specialized by each family of
 *       overloads.
 */
template <typename Family, typename VisitedConcepts>
struct result_of_call;

/**
 * Metafunction class returning whether a `Family` of overloads has no
 * overload that can be selected after a `Concept` was visited.
 */
template <typename Family, typename Concept, typename VisitedConcepts>
struct has_no_better_overload {
    template <typename ...Args>
    struct apply
        : boost::is_same<
            typename boost::mpl::apply<
                result_of_call<
                    Family,
                    typename mark_as_visited<Concept, VisitedConcepts>::type
                >,
                Args...
            >::type,
            concept_based_overload_resolution_failed
        >
    { };
};

/**
 * Metafunction class returning whether this is the best overload available
 * with respect to a `Type` modeling a `Concept`.
 *
 * Specifically, this metafunction class is true iff `Concept` is the most
 * specific concept modeled by `Type` for which an overload in a `Family` of
 * overloads exists.
 */
template <typename Type, typename Family,
          typename Concept, typename VisitedConcepts>
struct should_pick_this_overload_for {
    template <typename ...Args>
    struct apply
        : boost::mpl::and_<
            is_best_so_far<Type, Concept, VisitedConcepts>,
            boost::mpl::apply<
                has_no_better_overload<Family, Concept, VisitedConcepts>,
                Args...
            >
        >
    { };
};

//! Type representing an empty list of visited concepts.
typedef boost::mpl::vector<> no_concepts;

//! Requires a `Type` to be a model of a `Concept` in a `require` clause.
template <typename Concept, typename Type> struct model_of;

//! Provides the `Family` of overloads to a `require` clause.
template <typename Family> struct overload_family;

/**
 * Provides the list of visited concepts during the current overload
 * resolution to a `require` clause.
 */
template <typename VisitedConcepts> struct visited_concepts;

template <typename Family, typename VisitedConcepts = boost::mpl::vector<> >
struct overload_information {
    typedef VisitedConcepts visited_concepts;
    typedef Family family;
};

/**
 *
 */
template <typename ...Args>
struct requires {

};

} // end namespace duck

#endif // !DUCK_SANDBOX_CONCEPT_OVERLOAD_HPP
