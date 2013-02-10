/**
 * Test suite for the concept-based overloading experiment.
 */

#include <duck/sandbox/concept_overload.hpp>

#include <boost/iterator/iterator_categories.hpp>
#include <boost/mpl/bool.hpp>
#include <boost/type_traits/is_convertible.hpp>
#include <boost/utility/declval.hpp>
#include <boost/utility/enable_if.hpp>
#include <iostream>


//////////////////////////////////////////////////////////////////////////////
template <typename Traversal>
struct iterator_traversal_at_least {
    template <typename Iterator>
    struct apply
        : boost::is_convertible<
            typename boost::iterator_traversal<Iterator>::type,
            Traversal
        >
    { };
};

struct RandomAccessTraversal {
    template <typename Iterator, typename Dummy = void>
    struct apply
        : boost::is_convertible<
            typename boost::iterator_traversal<Iterator>::type,
            boost::random_access_traversal_tag
        >
    { };

    template <typename T>
    struct apply<T*, void>
        : boost::mpl::true_
    { };
};

struct BidirectionalTraversal
    : iterator_traversal_at_least<boost::bidirectional_traversal_tag>
{ };

struct ForwardTraversal
    : iterator_traversal_at_least<boost::forward_traversal_tag>
{ };

struct SinglePassTraversal
    : iterator_traversal_at_least<boost::single_pass_traversal_tag>
{ };

struct IncrementableTraversal
    : iterator_traversal_at_least<boost::incrementable_traversal_tag>
{ };

namespace duck {
    template <>
    struct is_more_specific_than<RandomAccessTraversal, ForwardTraversal>
        : boost::mpl::false_
    { };

    template <>
    struct is_more_specific_than<ForwardTraversal, RandomAccessTraversal>
        : boost::mpl::true_
    { };
}
//////////////////////////////////////////////////////////////////////////////


struct distance_tag;
namespace duck {
    template <typename VisitedConcepts>
    struct result_of_call<distance_tag, VisitedConcepts> {
        template <typename Iterator>
        struct apply {
            typedef decltype(
                        distance(boost::declval<Iterator>(),
                                 boost::declval<Iterator>(),
                                 VisitedConcepts())
                    ) type;
        };
    };
}
duck::concept_based_overload_resolution_failed distance(...);


// Possibilité d'avoir un OverloadInfo qui default à la family?
// Ça pourrait faciliter l'utilisation.

template <typename Iterator, typename VisitedConcepts = duck::no_concepts>
typename duck::requires<
    duck::model_of<RandomAccessTraversal, Iterator>
    // possibly other requirements

  , duck::visited_concepts<VisitedConcepts>
  , duck::overload_family<distance_tag>
, std::size_t>::type
distance(Iterator first, Iterator last, VisitedConcepts = VisitedConcepts()) {

}


template <typename Concept, typename Model, typename Family, typename VisitedConcepts>
struct requires
    : boost::enable_if<
        duck::should_pick_this_overload_for<
            Model,
        >
    >
{ };

template <typename Iterator, typename VisitedConcepts = duck::no_concepts>
typename boost::enable_if<
    boost::mpl::apply<
        duck::should_pick_this_overload_for<
            Iterator, distance_tag, RandomAccessTraversal, VisitedConcepts
        >,
        Iterator
    >,
std::size_t>::type distance(Iterator first, Iterator last, VisitedConcepts = VisitedConcepts()) {
    std::cout << "random_access\n";
    return last - first;
}

template <typename Iterator, typename VisitedConcepts = duck::no_concepts>
typename boost::enable_if<
    boost::mpl::apply<
        duck::should_pick_this_overload_for<
            Iterator, distance_tag, ForwardTraversal, VisitedConcepts
        >,
        Iterator
    >,
std::size_t>::type distance(Iterator first, Iterator last, VisitedConcepts = VisitedConcepts()) {
    std::cout << "forward_traversal\n";
    std::size_t dist = 0;
    while (first != last)
        ++first, ++dist;
    return dist;
}

static void foo() {
    int* i = 0;
    int* j = 0;
    std::size_t dist = distance(i, j);
    distance(0, 1);
}



// struct my_zero_dist_iterator { };
// namespace boost {
//     template <>
//     struct iterator_traversal<my_zero_dist_iterator> {
//         typedef void type;
//     };
// }

// struct ZeroDistIterator {
//     template <typename Iterator>
//     struct apply
//         : boost::is_same<
//             Iterator,
//             my_zero_dist_iterator
//         >
//     { };
// };

// template <typename T>
// struct is_more_specific_than<ZeroDistIterator, T>
//     : boost::mpl::false_
// { };

// template <typename T>
// struct is_more_specific_than<T, ZeroDistIterator>
//     : boost::mpl::true_
// { };

// template <typename Iterator, typename VisitedConcepts = no_concepts>
// typename boost::enable_if<
//     boost::mpl::and_<
//         is_best_so_far<Iterator, ZeroDistIterator, VisitedConcepts>,
//         distance_has_no_better_overload<Iterator, ZeroDistIterator, VisitedConcepts>
//     >,
// std::size_t>::type distance(Iterator first, Iterator last, VisitedConcepts = VisitedConcepts()) {
//     std::cout << "zero_dist\n";
//     return 0;
// }
