/**
 * Test suite for the @em BidirectionalIterator concept.
 */

#include <duck/bidirectional_iterator.hpp>

#include <boost/mpl/assert.hpp>
#include <vector>


// Test with primitive types.
BOOST_MPL_ASSERT_NOT((duck::BidirectionalIterator<int>));
BOOST_MPL_ASSERT_NOT((duck::BidirectionalIterator<int&>));
BOOST_MPL_ASSERT((duck::BidirectionalIterator<int*>));
BOOST_MPL_ASSERT((duck::BidirectionalIterator<int const*>));
BOOST_MPL_ASSERT_NOT((duck::BidirectionalIterator<int const>));
BOOST_MPL_ASSERT_NOT((duck::BidirectionalIterator<int const&>));
BOOST_MPL_ASSERT_NOT((duck::BidirectionalIterator<int* const>));
BOOST_MPL_ASSERT_NOT((duck::BidirectionalIterator<int&&>));
BOOST_MPL_ASSERT_NOT((duck::BidirectionalIterator<int const&&>));

// Test with a sample iterator.
BOOST_MPL_ASSERT((duck::BidirectionalIterator<std::vector<int>::iterator>));

// Test with a type that lacks only one of the decrement operator.
struct no_decrement : std::vector<int>::iterator {
    no_decrement& operator--() = delete;
};
BOOST_MPL_ASSERT_NOT((duck::BidirectionalIterator<no_decrement>));
