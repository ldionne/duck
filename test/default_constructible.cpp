/**
 * Test suite for the @em DefaultConstructible concept.
 */

#include <duck/default_constructible.hpp>

#include "unit_test_helper.hpp"


#define ASSERT_DC(T) ASSERT_MODELS(duck::DefaultConstructible, T)
#define ASSERT_NOT_DC(T) ASSERT_NOT_MODELS(duck::DefaultConstructible, T)

// Test for a primitive type.
ASSERT_DC(int);
ASSERT_DC(int const);
ASSERT_DC(int*);
ASSERT_DC(int* const);
ASSERT_NOT_DC(int&);
ASSERT_NOT_DC(int const&);
ASSERT_NOT_DC(int&&);
ASSERT_NOT_DC(int const&&);

// Test with explicitly disabled default constructor.
struct nodc {
    nodc() = delete;
};
ASSERT_NOT_DC(nodc);

// nodc should be inherited.
struct inherit_nodc : nodc { };
ASSERT_NOT_DC(inherit_nodc);

// Test with a non-default constructor hiding the default one.
struct hidden_dc {
    hidden_dc(int);
};
ASSERT_NOT_DC(hidden_dc);

// Test with a default constructor made private.
class private_dc {
    private_dc();
};
ASSERT_NOT_DC(private_dc);

// Test with custom constructors and a default constructor.
struct custom {
    custom();
    custom(int);
};
ASSERT_DC(custom);
