/**
 * Test suite for the @em null_archetype class.
 */

#include <duck/null_archetype.hpp>
#include <duck/assignable.hpp>
#include <duck/copy_constructible.hpp>
#include <duck/default_constructible.hpp>
#include <duck/destructible.hpp>

#include <boost/mpl/assert.hpp>


BOOST_MPL_ASSERT_NOT((duck::is_assignable<duck::null_archetype>));
BOOST_MPL_ASSERT_NOT((duck::is_copy_constructible<duck::null_archetype>));
BOOST_MPL_ASSERT_NOT((duck::is_default_constructible<duck::null_archetype>));
BOOST_MPL_ASSERT_NOT((duck::is_destructible<duck::null_archetype>));
