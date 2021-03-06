/**
 * Test suite for the @em Destructible concept.
 */

#include <duck/destructible.hpp>

#include <boost/mpl/assert.hpp>


#define ASSERT_D(T) BOOST_MPL_ASSERT((duck::is_destructible<T>))
#define ASSERT_NOT_D(T) BOOST_MPL_ASSERT_NOT((duck::is_destructible<T>))

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
