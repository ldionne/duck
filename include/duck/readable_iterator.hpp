/**
 * This file defines the `ReadableIterator` concept.
 */

#ifndef DUCK_READABLE_ITERATOR_HPP
#define DUCK_READABLE_ITERATOR_HPP

#include <duck/assignable.hpp>
#include <duck/copy_constructible.hpp>
#include <duck/detail/config.hpp>
#include <duck/detail/test_expression.hpp>

#include <boost/mpl/and.hpp>
#include <boost/type_traits/is_convertible.hpp>
#include <boost/utility/declval.hpp>


namespace duck {

/**
 * Metafunction returning whether an `Iterator` models the `ReadableIterator`
 * concept.
 */
template <typename Iterator>
class is_readable_iterator {
    DUCK_I_TEST_EXPRESSION(dereference, *boost::declval<I>(), typename I);
    DUCK_I_TEST_TYPE(value_type_,
                typename detail::iterator_traits<I>::value_type, typename I);
    typedef typename value_type_<Iterator>::type Value;

public:
    typedef typename boost::mpl::and_<
                is_assignable<Iterator>,
                is_copy_constructible<Iterator>,

                detail::is_valid<Value>,
                boost::is_convertible<
                    typename dereference<Iterator>::type, Value
                >

                // We should also check whether it->m returns a reference to
                // the member inside its pointee, but that would require
                // asking a pointer to a member, which seems overly
                // restrictive. Also, non class-or-struct types don't care
                // about this.
            >::type type;
    static bool const value = type::value;
};

//! `ReadableIterator` concept.
struct ReadableIterator {
    template <typename Iterator>
    struct apply
        : is_readable_iterator<Iterator>
    { };
};

} // end namespace duck

#endif // !DUCK_READABLE_ITERATOR_HPP
