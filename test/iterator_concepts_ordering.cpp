/**
 * Test suite for the iterator_concepts_ordering.hpp header.
 */

#include <duck/detail/iterator_concepts_ordering.hpp>

#include <boost/mpl/assert.hpp>


BOOST_MPL_ASSERT((duck::is_more_specific_than<
                    duck::BidirectionalIterator,
                    duck::RandomAccessIterator>));

BOOST_MPL_ASSERT((duck::is_more_specific_than<
                    duck::IncrementableIterator,
                    duck::RandomAccessIterator>));

BOOST_MPL_ASSERT((duck::is_more_specific_than<
                    duck::ForwardIterator,
                    duck::RandomAccessIterator>));


BOOST_MPL_ASSERT_NOT((duck::is_more_specific_than<
                        duck::RandomAccessIterator,
                        duck::BidirectionalIterator>));

BOOST_MPL_ASSERT_NOT((duck::is_more_specific_than<
                        duck::RandomAccessIterator,
                        duck::IncrementableIterator>));

BOOST_MPL_ASSERT_NOT((duck::is_more_specific_than<
                        duck::ForwardIterator,
                        duck::ForwardIterator>));

BOOST_MPL_ASSERT_NOT((duck::is_more_specific_than<
                        duck::RandomAccessIterator,
                        duck::ForwardIterator>));
