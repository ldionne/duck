/**
 * Test suite for the @em null_archetype class.
 */

#include <duck/null_archetype.hpp>
#include <duck/assignable.hpp>
#include <duck/copy_constructible.hpp>
#include <duck/default_constructible.hpp>
#include <duck/destructible.hpp>

#include <boost/mpl/assert.hpp>


BOOST_MPL_ASSERT_NOT((duck::Assignable<duck::null_archetype>));
BOOST_MPL_ASSERT_NOT((duck::CopyConstructible<duck::null_archetype>));
BOOST_MPL_ASSERT_NOT((duck::DefaultConstructible<duck::null_archetype>));
BOOST_MPL_ASSERT_NOT((duck::Destructible<duck::null_archetype>));
