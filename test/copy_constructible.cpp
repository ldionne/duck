/**
 * Test suite for the `CopyConstructible` concept.
 */

#include <duck/copy_constructible.hpp>

#include <boost/mpl/assert.hpp>


#define ASSERT_CC(T) BOOST_MPL_ASSERT((duck::is_copy_constructible<T>))
#define ASSERT_NOT_CC(T) BOOST_MPL_ASSERT_NOT((duck::is_copy_constructible<T>))

// Test for a primitive type.
ASSERT_CC(int);
ASSERT_CC(int const);
ASSERT_CC(int*);
ASSERT_CC(int const*);
ASSERT_CC(int&);
ASSERT_CC(int const&);
ASSERT_NOT_CC(int&&);
ASSERT_NOT_CC(int const&&);

// Test with explicitly disabled copy constructor.
struct nocc {
    nocc(nocc const&) = delete;
};
ASSERT_NOT_CC(nocc);

// nocc should be inherited.
struct inherit_nocc : nocc { };
ASSERT_NOT_CC(inherit_nocc);

// Test with a copy constructor made private.
class private_cc {
    private_cc(private_cc const&);
};
ASSERT_NOT_CC(private_cc);

// Test with custom constructors and a copy constructor.
struct custom {
    custom(custom const&);
    custom(int);
};
ASSERT_CC(custom);
