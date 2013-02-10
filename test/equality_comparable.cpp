/**
 * Test suite for the `EqualityComparable` concept.
 */

#include <duck/equality_comparable.hpp>

#include <boost/mpl/assert.hpp>


#define ASSERT_EC(T) BOOST_MPL_ASSERT((duck::is_equality_comparable<T>))
#define ASSERT_NOT_EC(T) \
    BOOST_MPL_ASSERT_NOT((duck::is_equality_comparable<T>))

// Test for a primitive type.
ASSERT_EC(int);
ASSERT_EC(int const);
ASSERT_EC(int*);
ASSERT_EC(int const*);
ASSERT_EC(int&);
ASSERT_EC(int const&);
ASSERT_EC(int&&);
ASSERT_EC(int const&&);

// Test with a custom type not implementing operator==.
struct no_comp { };
ASSERT_NOT_EC(no_comp);

// Test with one of the two operators missing.
struct missing_comp {
    bool operator==(missing_comp const&);
};
ASSERT_NOT_EC(missing_comp);

// Test with an equality operator made private.
class private_comp {
    bool operator==(private_comp const&);
};
ASSERT_NOT_EC(private_comp);

// Test with comparison operators implemented as member functions.
struct member_comp {
    bool operator==(member_comp const&);
    bool operator!=(member_comp const&);
};
ASSERT_EC(member_comp);

// Test with comparison operators implemented as free function overloads.
struct free_comp { };
bool operator==(free_comp const&, free_comp const&);
bool operator!=(free_comp const&, free_comp const&);
ASSERT_EC(free_comp);

// Test with a template class using template free functions.
template <typename T>
struct free_comp_template { };
template <typename T>
bool operator==(free_comp_template<T> const&, free_comp_template<T> const&);
template <typename T>
bool operator!=(free_comp_template<T> const&, free_comp_template<T> const&);
ASSERT_EC(free_comp_template<int>);
