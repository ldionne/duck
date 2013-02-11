/**
 * Test suite for the `ForwardIterator` concept.
 */

#include <duck/forward_iterator.hpp>

#include <boost/mpl/assert.hpp>
#include <iterator>
#include <vector>


#define ASSERT_FI(T) BOOST_MPL_ASSERT((duck::is_forward_iterator<T>))
#define ASSERT_NOT_FI(T) BOOST_MPL_ASSERT_NOT((duck::is_forward_iterator<T>))

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

namespace std {
    template <>
    struct iterator_traits<with_difference_type> {
        typedef long difference_type;
    };
}
ASSERT_FI(with_difference_type);
