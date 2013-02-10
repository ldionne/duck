/**
 * Test suite for the @em BidirectionalIterator concept.
 */

#include <duck/bidirectional_iterator.hpp>

#include <boost/mpl/assert.hpp>
#include <vector>


#define ASSERT_NOT_MODELS(T) \
    BOOST_MPL_ASSERT_NOT((duck::is_bidirectional_iterator<T>))

#define ASSERT_MODELS(T) \
    BOOST_MPL_ASSERT((duck::is_bidirectional_iterator<T>))

// Test with primitive types.
ASSERT_NOT_MODELS(int);
ASSERT_NOT_MODELS(int&);
ASSERT_MODELS(int*);
ASSERT_MODELS(int const*);
ASSERT_NOT_MODELS(int const);
ASSERT_NOT_MODELS(int const&);
ASSERT_NOT_MODELS(int* const);
ASSERT_NOT_MODELS(int&&);
ASSERT_NOT_MODELS(int const&&);

// Test with a sample iterator.
ASSERT_MODELS(std::vector<int>::iterator);

// Test with a type that lacks only one of the decrement operator.
struct no_decrement : std::vector<int>::iterator {
    no_decrement& operator--() = delete;
};
ASSERT_NOT_MODELS(no_decrement);
