/**
 * Test suite for the @em WriteableIterator concept.
 */

#include <duck/writeable_iterator.hpp>

#include "unit_test_helper.hpp"
#include <vector>


#define ASSERT_WI(It, T) ASSERT_MODELS(duck::WriteableIterator, It, T)
#define ASSERT_NOT_WI(It, T) ASSERT_NOT_MODELS(duck::WriteableIterator, It, T)

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
