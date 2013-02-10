/**
 * This file defines the @em IncrementableIterator concept.
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
 * Metafunction returning whether @em It models the @em IncrementableIterator
 * concept.
 */
template <typename It>
class IncrementableIterator {
    DUCK_I_TEST_EXPRESSION(pre_increment, ++boost::declval<I&>(), typename I);
    DUCK_I_TEST_EXPRESSION(post_increment, boost::declval<I&>()++, typename I);

public:
    typedef typename boost::mpl::and_<
                Assignable<It>,
                CopyConstructible<It>,

                boost::is_convertible<
                    typename pre_increment<It>::type,
                    typename boost::add_lvalue_reference<It>::type
                >,

                boost::is_convertible<
                    typename post_increment<It>::type,
                    typename boost::remove_reference<It>::type
                >
            >::type type;
    static bool const value = type::value;
};

} // end namespace duck

#endif // !DUCK_INCREMENTABLE_ITERATOR_HPP
