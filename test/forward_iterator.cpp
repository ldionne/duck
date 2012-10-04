/**
 * Test suite for the @em ForwardIterator concept.
 */

#include <duck/forward_iterator.hpp>
#include <duck/detail/config.hpp>

#include "unit_test_helper.hpp"
#include <vector>


#define ASSERT_FI(T) ASSERT_MODELS(duck::ForwardIterator, T)
#define ASSERT_NOT_FI(T) ASSERT_NOT_MODELS(duck::ForwardIterator, T)

// Test with primitive types.
ASSERT_NOT_FI(int);
ASSERT_NOT_FI(int&);
ASSERT_FI(int*);
ASSERT_FI(int const*);
ASSERT_NOT_FI(int const);
ASSERT_NOT_FI(int const&);
ASSERT_NOT_FI(int* const);
ASSERT_NOT_FI(int&&);
ASSERT_NOT_FI(int const&&);

// Test with a sample iterator.
ASSERT_FI(std::vector<int>::iterator);

// Test with a type that lacks only the iterator_traits specialization.
struct no_difference_type {
    no_difference_type& operator++();
    no_difference_type operator++(int);
    bool operator==(no_difference_type const&) const;
    bool operator!=(no_difference_type const&) const;
};
ASSERT_NOT_FI(no_difference_type);

// Test with a pseudo-custom type specializing iterator_traits.
struct with_difference_type {
    with_difference_type& operator++();
    with_difference_type operator++(int);
    bool operator==(with_difference_type const&) const;
    bool operator!=(with_difference_type const&) const;
};
template <>
struct duck::detail::iterator_traits<with_difference_type> {
    using difference_type = long;
};
ASSERT_FI(with_difference_type);
