/**
 * Test suite for the @em RandomAccessIterator concept.
 */

#include <duck/random_access_iterator.hpp>

#include "unit_test_helper.hpp"
#include <vector>


#define ASSERT_RAI(T) ASSERT_MODELS(duck::RandomAccessIterator, T)
#define ASSERT_NOT_RAI(T) ASSERT_NOT_MODELS(duck::RandomAccessIterator, T)

// Test with primitive types.
ASSERT_NOT_RAI(int);
ASSERT_NOT_RAI(int&);
ASSERT_RAI(int*);
ASSERT_RAI(int const*);
ASSERT_NOT_RAI(int const);
ASSERT_NOT_RAI(int const&);
ASSERT_NOT_RAI(int* const);
ASSERT_NOT_RAI(int&&);
ASSERT_NOT_RAI(int const&&);

// Test with a sample iterator.
ASSERT_RAI(std::vector<int>::iterator);
