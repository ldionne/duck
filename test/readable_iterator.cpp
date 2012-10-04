/**
 * Test suite for the @em ReadableIterator concept.
 */

#include <duck/readable_iterator.hpp>

#include "unit_test_helper.hpp"
#include <vector>


#define ASSERT_RI(T) ASSERT_MODELS(duck::ReadableIterator, T)
#define ASSERT_NOT_RI(T) ASSERT_NOT_MODELS(duck::ReadableIterator, T)

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
