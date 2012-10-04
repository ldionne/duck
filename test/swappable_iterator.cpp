/**
 * Test suite for the @em SwappableIterator concept.
 */

#include <duck/swappable_iterator.hpp>

#include "unit_test_helper.hpp"
#include <vector>


#define ASSERT_SI(T) ASSERT_MODELS(duck::SwappableIterator, T)
#define ASSERT_NOT_SI(T) ASSERT_NOT_MODELS(duck::SwappableIterator, T)

// Test with primitive types.
ASSERT_NOT_SI(int);
ASSERT_NOT_SI(int&);
ASSERT_SI(int*);
ASSERT_NOT_SI(int const*);
ASSERT_NOT_SI(int const);
ASSERT_NOT_SI(int const&);
ASSERT_SI(int* const);
ASSERT_NOT_SI(int&&);
ASSERT_NOT_SI(int const&&);

// Test with a type defining iter_swap.
struct iter_swappable { };
void iter_swap(iter_swappable&, iter_swappable&);
ASSERT_SI(iter_swappable);

// Test with a type whose pointee defines swap.
struct pointee_swappable {
    struct pointee {
        pointee& operator=(pointee const&) = delete;
    };
    pointee& operator*();
};
void swap(pointee_swappable::pointee&, pointee_swappable::pointee&);
ASSERT_SI(pointee_swappable);

// Test with a type whose pointee is assignable.
struct pointee_assignable {
    struct pointee { };
    pointee& operator*();
};
ASSERT_SI(pointee_assignable);

// Test with a standard iterator.
ASSERT_SI(std::vector<int>::iterator);
