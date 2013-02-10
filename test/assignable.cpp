/**
 * Test suite for the @em Assignable concept.
 */

#include <duck/assignable.hpp>

#include <boost/mpl/assert.hpp>


// Test for a primitive type.
BOOST_MPL_ASSERT((duck::Assignable<int>));
BOOST_MPL_ASSERT_NOT((duck::Assignable<int const>));
BOOST_MPL_ASSERT((duck::Assignable<int*>));
BOOST_MPL_ASSERT_NOT((duck::Assignable<int * const>));
BOOST_MPL_ASSERT((duck::Assignable<int&>));
BOOST_MPL_ASSERT_NOT((duck::Assignable<int const&>));
BOOST_MPL_ASSERT((duck::Assignable<int&&>));
BOOST_MPL_ASSERT_NOT((duck::Assignable<int const&&>));

// Test with the void special case.
BOOST_MPL_ASSERT_NOT((duck::Assignable<void>));

// Test with an explicitely deleted operator=.
struct noassign {
    noassign& operator=(noassign const&) = delete;
};
BOOST_MPL_ASSERT_NOT((duck::Assignable<noassign>));

// The noassign should be inherited.
struct inherit_noassign : noassign { };
BOOST_MPL_ASSERT_NOT((duck::Assignable<inherit_noassign>));

// It should be assignable when inherited.
struct assign {
    assign& operator=(assign const&);
};
struct inherit_assign : assign { };
BOOST_MPL_ASSERT((duck::Assignable<inherit_assign>));

// It should not be assignable when operator= does not take a const ref.
struct takes_ref {
    takes_ref& operator=(takes_ref&);
};
BOOST_MPL_ASSERT_NOT((duck::Assignable<takes_ref>));
