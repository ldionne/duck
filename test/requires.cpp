/**
 * Test suite for the `requires` metafunction and related concept-based
 * overloading facilities.
 */

#include <duck/forward_iterator.hpp>
#include <duck/random_access_iterator.hpp>
#include <duck/requires.hpp>

#include <boost/mpl/apply.hpp>
#include <boost/mpl/assert.hpp>
#include <boost/mpl/bool.hpp>
#include <boost/mpl/vector.hpp>
#include <boost/type_traits/is_same.hpp>
#include <boost/utility/declval.hpp>


DUCK_ENABLE_CONCEPT_OVERLOADING(
    my_distance,
    my_distance(boost::declval<Iterator>(),
                boost::declval<Iterator>(), State()),
    typename Iterator
)


struct random_access_version_picked { };
template <typename Iterator, typename State = tag::my_distance>
typename duck::requires<
    duck::model_of<duck::RandomAccessIterator, Iterator>

  , duck::overload_resolution_state<State>
  , duck::template_parameters<Iterator>

, random_access_version_picked>::type
my_distance(Iterator, Iterator, State = State()) {
    return random_access_version_picked();
}

struct forward_version_picked { };
template <typename Iterator, typename State = tag::my_distance>
typename duck::requires<
    duck::model_of<duck::ForwardIterator, Iterator>

  , duck::overload_resolution_state<State>
  , duck::template_parameters<Iterator>

, forward_version_picked>::type
my_distance(Iterator, Iterator, State = State()) {
    return forward_version_picked();
}


struct my_custom_iterator { };
struct MyCustomConcept {
    template <typename Iterator>
    struct apply
        : boost::is_same<Iterator, my_custom_iterator>
    { };
};

namespace duck {
    template <typename T>
    struct is_more_specific_than<T, MyCustomConcept>
        : boost::mpl::true_
    { };
}

struct my_custom_iterator_picked { };
template <typename Iterator, typename State = tag::my_distance>
typename duck::requires<
    duck::model_of<MyCustomConcept, Iterator>
    // possibly other requirements

  , duck::overload_resolution_state<State>
  , duck::template_parameters<Iterator>

, my_custom_iterator_picked>::type
my_distance(Iterator, Iterator, State = State()) {
    return my_custom_iterator_picked();
}


typedef int* Iterator;
typedef tag::my_distance OverloadFamily;

template <typename Concept, typename ...Visited>
struct picks_overload
    : boost::mpl::apply<
        duck::requires_detail::clause_passes<
            Iterator, Concept,
            duck::requires_detail::overload_resolution<
                OverloadFamily, boost::mpl::vector<Visited...>
            >
        >,
        Iterator
    >
{ };

BOOST_MPL_ASSERT((picks_overload<duck::RandomAccessIterator>));
BOOST_MPL_ASSERT_NOT((picks_overload<duck::RandomAccessIterator, duck::RandomAccessIterator>));
BOOST_MPL_ASSERT((picks_overload<duck::RandomAccessIterator, duck::ForwardIterator>));
BOOST_MPL_ASSERT_NOT((picks_overload<duck::RandomAccessIterator, duck::RandomAccessIterator, duck::ForwardIterator>));

BOOST_MPL_ASSERT_NOT((picks_overload<duck::ForwardIterator>));
BOOST_MPL_ASSERT_NOT((picks_overload<duck::ForwardIterator, duck::RandomAccessIterator>));
BOOST_MPL_ASSERT_NOT((picks_overload<duck::ForwardIterator, duck::ForwardIterator>));
BOOST_MPL_ASSERT_NOT((picks_overload<duck::ForwardIterator, duck::RandomAccessIterator, duck::ForwardIterator>));

BOOST_MPL_ASSERT((
    boost::is_same<
        decltype(my_distance(boost::declval<Iterator>(),
                             boost::declval<Iterator>())),
        random_access_version_picked
    >
));

BOOST_MPL_ASSERT((
    boost::is_same<
        decltype(my_distance(boost::declval<my_custom_iterator>(),
                             boost::declval<my_custom_iterator>())),
        my_custom_iterator_picked
    >
));
