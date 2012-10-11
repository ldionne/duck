/**
 * Test suite for the @em Destructible concept.
 */

#include <duck/destructible.hpp>

#include "unit_test_helper.hpp"


#define ASSERT_D(T) ASSERT_MODELS(duck::Destructible, T)
#define ASSERT_NOT_D(T) ASSERT_NOT_MODELS(duck::Destructible, T)

// Test for a primitive type.
ASSERT_D(int);
ASSERT_D(int const);
ASSERT_D(int*);
ASSERT_D(int const*);
ASSERT_D(int&);
ASSERT_D(int const&);
ASSERT_D(int&&);
ASSERT_D(int const&&);

// test with explicitly deleted destructor.
struct nod {
    ~nod() = delete;
};
ASSERT_NOT_D(nod);

// nod should be inherited.
struct inherit_nod : nod { };
ASSERT_NOT_D(inherit_nod);

// Test with a destructor made private.
class private_d {
    ~private_d();
};
ASSERT_NOT_D(private_d);
