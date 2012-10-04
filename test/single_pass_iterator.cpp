/**
 * Test suite for the @em SinglePassIterator concept.
 */

#include <duck/single_pass_iterator.hpp>

#include "unit_test_helper.hpp"
#include <vector>


#define ASSERT_SPI(T) ASSERT_MODELS(duck::SinglePassIterator, T)
#define ASSERT_NOT_SPI(T) ASSERT_NOT_MODELS(duck::SinglePassIterator, T)

// Test with primitive types.
ASSERT_SPI(int);
ASSERT_SPI(int&);
ASSERT_SPI(int*);
ASSERT_SPI(int const*);
ASSERT_NOT_SPI(int const);
ASSERT_NOT_SPI(int const&);
ASSERT_NOT_SPI(int* const);
ASSERT_NOT_SPI(int&&);
ASSERT_NOT_SPI(int const&&);

// Test with a sample iterator.
ASSERT_SPI(std::vector<int>::iterator);

// Test with a type that lacks only comparison.
struct no_compare : std::vector<int>::iterator {
    bool operator==(no_compare const&) = delete;
};
ASSERT_NOT_SPI(no_compare);

// Test with a type that lacks only a type of increment.
struct no_increment : std::vector<int>::iterator {
    no_increment& operator++(int) = delete;
};
ASSERT_NOT_SPI(no_increment);
