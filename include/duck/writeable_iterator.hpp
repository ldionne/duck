/**
 * This file defines the `WriteableIterator` concept.
 */

#ifndef DUCK_WRITEABLE_ITERATOR_HPP
#define DUCK_WRITEABLE_ITERATOR_HPP

#include <duck/copy_constructible.hpp>
#include <duck/detail/test_expression.hpp>

#include <boost/mpl/and.hpp>
#include <boost/utility/declval.hpp>
#include <iterator>


namespace duck {

namespace writeable_detail {
    template <typename Iterator>
    struct default_value {
        typedef typename std::iterator_traits<Iterator>::value_type type;
    };
}

/**
 * Metafunction returning whether an `Iterator` models the
 * `WriteableIterator` concept.
 */
template <typename Iterator, typename Value =
                    typename writeable_detail::default_value<Iterator>::type>
class is_writeable_iterator {
    DUCK_I_TEST_EXPRESSION(assign_deref,
                           *boost::declval<I>() = boost::declval<V>(),
                           typename I, typename V);

public:
    typedef typename boost::mpl::and_<
                is_copy_constructible<Iterator>,
                detail::is_valid<typename assign_deref<Iterator, Value>::type>
            >::type type;
    static bool const value = type::value;
};

//! `WriteableIterator` concept.
struct WriteableIterator {
    template <typename Iterator, typename Value =
                    typename writeable_detail::default_value<Iterator>::type>
    struct apply
        : is_writeable_iterator<Iterator, Value>
    { };
};

} // end namespace duck

#endif // !DUCK_WRITEABLE_ITERATOR_HPP
