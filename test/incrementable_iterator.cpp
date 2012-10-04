/**
 * Test suite for the @em IncrementableIterator concept.
 */

#include <duck/incrementable_iterator.hpp>

#include "unit_test_helper.hpp"
#include <vector>


#define ASSERT_II(T) ASSERT_MODELS(duck::IncrementableIterator, T)
#define ASSERT_NOT_II(T) ASSERT_NOT_MODELS(duck::IncrementableIterator, T)

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
