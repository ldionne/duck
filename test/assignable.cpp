/**
 * Test suite for the @em Assignable concept.
 */

#include <duck/assignable.hpp>

#include "unit_test_helper.hpp"


#define ASSERT_ASSIGNABLE(T) ASSERT_MODELS(duck::Assignable, T)
#define ASSERT_NOT_ASSIGNABLE(T) ASSERT_NOT_MODELS(duck::Assignable, T)

// Test for a primitive type.
ASSERT_ASSIGNABLE(int);
ASSERT_NOT_ASSIGNABLE(int const);
ASSERT_ASSIGNABLE(int*);
ASSERT_NOT_ASSIGNABLE(int * const);
ASSERT_ASSIGNABLE(int&);
ASSERT_NOT_ASSIGNABLE(int const&);
ASSERT_ASSIGNABLE(int&&);
ASSERT_NOT_ASSIGNABLE(int const&&);

// Test with the void special case.
ASSERT_NOT_ASSIGNABLE(void);

// Test with an explicitely deleted operator=.
struct noassign {
    noassign& operator=(noassign const&) = delete;
};
ASSERT_NOT_ASSIGNABLE(noassign);

// The noassign should be inherited.
struct inherit_noassign : noassign { };
ASSERT_NOT_ASSIGNABLE(inherit_noassign);

// It should be assignable when inherited.
struct assign {
    assign& operator=(assign const&);
};
struct inherit_assign : assign { };
ASSERT_ASSIGNABLE(inherit_assign);

// It should not be assignable when operator= does not take a const ref.
struct takes_ref {
    takes_ref& operator=(takes_ref&);
};
ASSERT_NOT_ASSIGNABLE(takes_ref);
