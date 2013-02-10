/**
 * Test suite for the `LvalueIterator` concept.
 */

#include <duck/lvalue_iterator.hpp>

#include <boost/mpl/assert.hpp>
#include <vector>


#define ASSERT_LI(T) BOOST_MPL_ASSERT((duck::is_lvalue_iterator<T>))
#define ASSERT_NOT_LI(T) BOOST_MPL_ASSERT_NOT((duck::is_lvalue_iterator<T>))

// Test with primitive types.
ASSERT_NOT_LI(int);
ASSERT_NOT_LI(int&);
ASSERT_LI(int*);
ASSERT_LI(int const*);
ASSERT_NOT_LI(int const);
ASSERT_NOT_LI(int const&);
ASSERT_NOT_LI(int* const);
ASSERT_NOT_LI(int&&);
ASSERT_NOT_LI(int const&&);

// Test with a standard iterator.
ASSERT_LI(std::vector<int>::iterator);
