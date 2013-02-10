/**
 * Test suite for the `Comparable` concept.
 */

#include <duck/comparable.hpp>

#include <boost/mpl/assert.hpp>


#define ASSERT_C(T) BOOST_MPL_ASSERT((duck::is_comparable<T>))
#define ASSERT_NOT_C(T) BOOST_MPL_ASSERT_NOT((duck::is_comparable<T>))

// Test for a primitive type.
ASSERT_C(int);
ASSERT_C(int const);
ASSERT_C(int*);
ASSERT_C(int const*);
ASSERT_C(int&);
ASSERT_C(int const&);
ASSERT_C(int&&);
ASSERT_C(int const&&);

// Test with one of the operators missing.
struct missing_comp {
    bool operator<(missing_comp const&);
    bool operator<=(missing_comp const&);
    bool operator>(missing_comp const&);
    bool operator>=(missing_comp const&) = delete;
};
ASSERT_NOT_C(missing_comp);

// Test with a comparison operator made private.
struct private_comp {
    bool operator<(missing_comp const&);
    bool operator<=(missing_comp const&);
    bool operator>(missing_comp const&);
    private: bool operator>=(missing_comp const&);
};
ASSERT_NOT_C(private_comp);

// Test with comparison operators implemented as member functions.
struct member_comp {
    bool operator<(member_comp const&);
    bool operator<=(member_comp const&);
    bool operator>(member_comp const&);
    bool operator>=(member_comp const&);
};
ASSERT_C(member_comp);

// Test with comparison operators implemented as free function overloads.
struct free_comp { };
bool operator>(free_comp const&, free_comp const&);
bool operator<(free_comp const&, free_comp const&);
bool operator<=(free_comp const&, free_comp const&);
bool operator>=(free_comp const&, free_comp const&);
ASSERT_C(free_comp);

// Test with a template class using template free functions.
template <typename T>
struct free_comp_template { };
template <typename T>
bool operator>(free_comp_template<T> const&, free_comp_template<T> const&);
template <typename T>
bool operator<(free_comp_template<T> const&, free_comp_template<T> const&);
template <typename T>
bool operator<=(free_comp_template<T> const&, free_comp_template<T> const&);
template <typename T>
bool operator>=(free_comp_template<T> const&, free_comp_template<T> const&);
ASSERT_C(free_comp_template<int>);
