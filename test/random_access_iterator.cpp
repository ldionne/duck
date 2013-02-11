/**
 * Test suite for the `RandomAccessIterator` concept.
 */

#include <duck/random_access_iterator.hpp>

#include <boost/mpl/assert.hpp>
#include <vector>


// Test with primitive types.
BOOST_MPL_ASSERT_NOT((duck::is_random_access_iterator<int>));
BOOST_MPL_ASSERT_NOT((duck::is_random_access_iterator<int&>));
BOOST_MPL_ASSERT((duck::is_random_access_iterator<int*>));
BOOST_MPL_ASSERT((duck::is_random_access_iterator<int const*>));
BOOST_MPL_ASSERT_NOT((duck::is_random_access_iterator<int const>));
BOOST_MPL_ASSERT_NOT((duck::is_random_access_iterator<int const&>));
BOOST_MPL_ASSERT_NOT((duck::is_random_access_iterator<int* const>));
BOOST_MPL_ASSERT_NOT((duck::is_random_access_iterator<int&&>));
BOOST_MPL_ASSERT_NOT((duck::is_random_access_iterator<int const&&>));

// Test with a sample iterator.
BOOST_MPL_ASSERT((duck::is_random_access_iterator<
                    std::vector<int>::iterator>));
