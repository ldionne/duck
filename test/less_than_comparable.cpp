/**
 * Test suite for the `LessThanComparable` concept.
 */

#include <duck/less_than_comparable.hpp>

#include <boost/mpl/assert.hpp>


#define ASSERT_LTC(T) BOOST_MPL_ASSERT((duck::is_less_than_comparable<T>))
#define ASSERT_NOT_LTC(T) \
    BOOST_MPL_ASSERT_NOT((duck::is_less_than_comparable<T>))

// Test for a primitive type.
ASSERT_LTC(int);
ASSERT_LTC(int const);
ASSERT_LTC(int*);
ASSERT_LTC(int const*);
ASSERT_LTC(int&);
ASSERT_LTC(int const&);
ASSERT_LTC(int&&);
ASSERT_LTC(int const&&);

// Test with a custom type not implementing operator<.
struct no_comp { };
ASSERT_NOT_LTC(no_comp);

// Test with an operator< made private.
class private_comp {
    bool operator<(private_comp const&);
};
ASSERT_NOT_LTC(private_comp);

// Test with operator< implemented as a member function.
struct member_comp {
    bool operator<(member_comp const&);
};
ASSERT_LTC(member_comp);

// Test with operator < implemented as a free function overload.
struct free_comp { };
bool operator<(free_comp const&, free_comp const&);
ASSERT_LTC(free_comp);

// Test with a template class using a template free function.
template <typename T>
struct free_comp_template { };
template <typename T>
bool operator<(free_comp_template<T> const&, free_comp_template<T> const&);
ASSERT_LTC(free_comp_template<int>);
