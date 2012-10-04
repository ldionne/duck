/**
 * Test suite for the @em LvalueIterator concept.
 */

#include <duck/lvalue_iterator.hpp>

#include "unit_test_helper.hpp"
#include <vector>


#define ASSERT_LI(T) ASSERT_MODELS(duck::LvalueIterator, T)
#define ASSERT_NOT_LI(T) ASSERT_NOT_MODELS(duck::LvalueIterator, T)

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
