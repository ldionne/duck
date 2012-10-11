/**
 * Test suite for the @em null_archetype class.
 */

#include <duck/null_archetype.hpp>
#include <duck/assignable.hpp>
#include <duck/copy_constructible.hpp>
#include <duck/default_constructible.hpp>
#include <duck/destructible.hpp>

#include "unit_test_helper.hpp"


ASSERT_NOT_MODELS(duck::Assignable, duck::null_archetype);
ASSERT_NOT_MODELS(duck::CopyConstructible, duck::null_archetype);
ASSERT_NOT_MODELS(duck::DefaultConstructible, duck::null_archetype);
ASSERT_NOT_MODELS(duck::Destructible, duck::null_archetype);
