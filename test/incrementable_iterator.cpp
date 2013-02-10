/**
 * Test suite for the `IncrementableIterator` concept.
 */

#include <duck/incrementable_iterator.hpp>

#include <boost/mpl/assert.hpp>
#include <vector>


#define ASSERT_II(T) BOOST_MPL_ASSERT((duck::is_incrementable_iterator<T>))
#define ASSERT_NOT_II(T) \
    BOOST_MPL_ASSERT_NOT((duck::is_incrementable_iterator<T>))

// Test with primitive types.
ASSERT_II(int);
ASSERT_II(int&);
ASSERT_II(int*);
ASSERT_II(int const*);
ASSERT_NOT_II(int const);
ASSERT_NOT_II(int const&);
ASSERT_NOT_II(int* const);
ASSERT_NOT_II(int&&);
ASSERT_NOT_II(int const&&);

// Test with a sample iterator.
ASSERT_II(std::vector<int>::iterator);
