/**
 * This file defines the @em WriteableIterator concept.
 */

#ifndef DUCK_WRITEABLE_ITERATOR_HPP
#define DUCK_WRITEABLE_ITERATOR_HPP

#include <duck/copy_constructible.hpp>
#include <duck/detail/config.hpp>
#include <duck/detail/test_expression.hpp>

#include <boost/mpl/and.hpp>
#include <boost/utility/declval.hpp>


namespace duck {

/**
 * Metafunction returning whether @em It models the @em WriteableIterator
 * concept.
 */
template <typename It,
          typename Value = typename detail::iterator_traits<It>::value_type>
class WriteableIterator {
    DUCK_I_TEST_EXPRESSION(assign_deref,
                           *boost::declval<I>() = boost::declval<V>(),
                           typename I, typename V);

public:
    typedef typename boost::mpl::and_<
                CopyConstructible<It>,
                detail::is_valid<typename assign_deref<It, Value>::type>
            >::type type;
    static bool const value = type::value;
};

} // end namespace duck

#endif // !DUCK_WRITEABLE_ITERATOR_HPP
