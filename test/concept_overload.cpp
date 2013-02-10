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


template <typename Iterator, typename State = duck::overload_resolution<distance_tag> >
typename duck::requires<
    duck::model_of<RandomAccessTraversal, Iterator>
    // possibly other requirements

  , duck::overload_resolution_state<State>
  , duck::template_parameters<Iterator>

, std::size_t>::type
distance(Iterator first, Iterator last, State = State()) {
    std::cout << "random_access\n";
    return last - first;
}

template <typename Iterator, typename State = duck::overload_resolution<distance_tag> >
typename duck::requires<
    duck::model_of<ForwardTraversal, Iterator>
    // possibly other requirements

  , duck::overload_resolution_state<State>
  , duck::template_parameters<Iterator>

, std::size_t>::type
distance(Iterator first, Iterator last, State = State()) {
    std::cout << "forward_traversal\n";
    std::size_t dist = 0;
    while (first != last)
        ++first, ++dist;
    return dist;
}


struct my_zero_dist_iterator { };
namespace boost {
    template <>
    struct iterator_traversal<my_zero_dist_iterator> {
        typedef void type;
    };
}

struct ZeroDistIterator {
    template <typename Iterator>
    struct apply
        : boost::is_same<
            Iterator,
            my_zero_dist_iterator
        >
    { };
};

namespace duck {
    template <typename T>
    struct is_more_specific_than<ZeroDistIterator, T>
        : boost::mpl::false_
    { };

    template <typename T>
    struct is_more_specific_than<T, ZeroDistIterator>
        : boost::mpl::true_
    { };
}

template <typename Iterator, typename State = duck::overload_resolution<distance_tag> >
typename duck::requires<
    duck::model_of<ZeroDistIterator, Iterator>
    // possibly other requirements

  , duck::overload_resolution_state<State>
  , duck::template_parameters<Iterator>

, std::size_t>::type
distance(Iterator first, Iterator last, State = State()) {
    std::cout << "zero_dist\n";
    return 0;
}

static void foo() {
    int* i = 0;
    int* j = 0;
    std::size_t dist = distance(i, j);

    my_zero_dist_iterator first, last;
    std::size_t zero = distance(first, last);
}
