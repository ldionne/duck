/**
 * This file defines the `IncrementableIterator` concept.
 */

#ifndef DUCK_INCREMENTABLE_ITERATOR_HPP
#define DUCK_INCREMENTABLE_ITERATOR_HPP

#include <duck/assignable.hpp>
#include <duck/copy_constructible.hpp>
#include <duck/detail/test_expression.hpp>

#include <boost/mpl/and.hpp>
#include <boost/type_traits/add_lvalue_reference.hpp>
#include <boost/type_traits/is_convertible.hpp>
#include <boost/type_traits/remove_reference.hpp>
#include <boost/utility/declval.hpp>


namespace duck {

/**
 * Metafunction returning whether an `Iterator` models the
 * `IncrementableIterator` concept.
 */
template <typename Iterator>
class is_incrementable_iterator {
    DUCK_I_TEST_EXPRESSION(pre_increment, ++boost::declval<I&>(), typename I);
    DUCK_I_TEST_EXPRESSION(post_increment, boost::declval<I&>()++, typename I);

public:
    typedef typename boost::mpl::and_<
                Assignable<Iterator>,
                CopyConstructible<Iterator>,

                boost::is_convertible<
                    typename pre_increment<Iterator>::type,
                    typename boost::add_lvalue_reference<Iterator>::type
                >,

                boost::is_convertible<
                    typename post_increment<Iterator>::type,
                    typename boost::remove_reference<Iterator>::type
                >
            >::type type;
    static bool const value = type::value;
};

//! `IncrementableIterator` concept.
struct IncrementableIterator {
    template <typename Iterator>
    struct apply
        : is_incrementable_iterator<Iterator>
    { };
};

} // end namespace duck

#endif // !DUCK_INCREMENTABLE_ITERATOR_HPP
