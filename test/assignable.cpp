/**
 * Test suite for the `Assignable` concept.
 */

#include <duck/assignable.hpp>

#include <boost/mpl/assert.hpp>


#define ASSERT_A(T) BOOST_MPL_ASSERT((duck::is_assignable<T>))
#define ASSERT_NOT_A(T) BOOST_MPL_ASSERT_NOT((duck::is_assignable<T>))

// Test for a primitive type.
ASSERT_A(int);
ASSERT_NOT_A(int const);
ASSERT_A(int*);
ASSERT_NOT_A(int * const);
ASSERT_A(int&);
ASSERT_NOT_A(int const&);
ASSERT_A(int&&);
ASSERT_NOT_A(int const&&);

// Test with the void special case.
ASSERT_NOT_A(void);

// Test with an explicitely deleted operator=.
struct noassign {
    noassign& operator=(noassign const&) = delete;
};
ASSERT_NOT_A(noassign);

// The noassign should be inherited.
struct inherit_noassign : noassign { };
ASSERT_NOT_A(inherit_noassign);

// It should be assignable when inherited.
struct assign {
    assign& operator=(assign const&);
};
struct inherit_assign : assign { };
ASSERT_A(inherit_assign);

// It should not be assignable when operator= does not take a const ref.
struct takes_ref {
    takes_ref& operator=(takes_ref&);
};
ASSERT_NOT_A(takes_ref);
