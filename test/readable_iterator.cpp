/**
 * Test suite for the `ReadableIterator` concept.
 */

#include <duck/readable_iterator.hpp>

#include <boost/mpl/assert.hpp>
#include <vector>


#define ASSERT_RI(T) BOOST_MPL_ASSERT((duck::is_readable_iterator<T>))
#define ASSERT_NOT_RI(T) BOOST_MPL_ASSERT_NOT((duck::is_readable_iterator<T>))

// Test with primitive types.
ASSERT_NOT_RI(int);
ASSERT_NOT_RI(int&);
ASSERT_RI(int*);
ASSERT_RI(int const*);
ASSERT_NOT_RI(int const);
ASSERT_NOT_RI(int const&);
ASSERT_NOT_RI(int* const);
ASSERT_NOT_RI(int&&);
ASSERT_NOT_RI(int const&&);

// Test with a sample iterator.
ASSERT_RI(std::vector<int>::iterator);
