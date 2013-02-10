/**
 * Test suite for the `WriteableIterator` concept.
 */

#include <duck/writeable_iterator.hpp>

#include <boost/mpl/assert.hpp>
#include <vector>


#define ASSERT_WI(It, T) \
    BOOST_MPL_ASSERT((duck::is_writeable_iterator<It, T>))

#define ASSERT_NOT_WI(It, T) \
    BOOST_MPL_ASSERT_NOT((duck::is_writeable_iterator<It, T>))

// Test with primitive types.
ASSERT_NOT_WI(int, int);
ASSERT_NOT_WI(int&, int);
ASSERT_WI(int*, int);
ASSERT_NOT_WI(int const*, int const);
ASSERT_NOT_WI(int const, int const);
ASSERT_NOT_WI(int const&, int const);
ASSERT_WI(int* const, int);
ASSERT_NOT_WI(int&&, int);
ASSERT_NOT_WI(int const&&, int const);

// Test with a sample iterator.
ASSERT_WI(std::vector<int>::iterator, int);
