/**
 * Test suite for the @em BidirectionalIterator concept.
 */

#include <duck/bidirectional_iterator.hpp>

#include "unit_test_helper.hpp"
#include <vector>


#define ASSERT_BI(T) ASSERT_MODELS(duck::BidirectionalIterator, T)
#define ASSERT_NOT_BI(T) ASSERT_NOT_MODELS(duck::BidirectionalIterator, T)

// Test with primitive types.
ASSERT_NOT_BI(int);
ASSERT_NOT_BI(int&);
ASSERT_BI(int*);
ASSERT_BI(int const*);
ASSERT_NOT_BI(int const);
ASSERT_NOT_BI(int const&);
ASSERT_NOT_BI(int* const);
ASSERT_NOT_BI(int&&);
ASSERT_NOT_BI(int const&&);

// Test with a sample iterator.
ASSERT_BI(std::vector<int>::iterator);

// Test with a type that lacks only one of the decrement operator.
struct no_decrement : std::vector<int>::iterator {
    no_decrement& operator--() = delete;
};
ASSERT_NOT_BI(no_decrement);
