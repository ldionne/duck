/**
 * This file defines the @em LvalueIterator concept.
 */

#ifndef DUCK_LVALUE_ITERATOR_HPP
#define DUCK_LVALUE_ITERATOR_HPP

#include <duck/detail/config.hpp>
#include <duck/detail/test_expression.hpp>

#include <boost/mpl/and.hpp>
#include <boost/utility/declval.hpp>
#include <boost/type_traits/add_lvalue_reference.hpp>
#include <boost/type_traits/is_convertible.hpp>


namespace duck {

/**
 * Metafunction returning whether @em It models the @em LvalueIterator
 * concept.
 */
template <typename It>
class LvalueIterator {
    DUCK_I_TEST_EXPRESSION(dereference, const_cast<V&>(*boost::declval<I>()),
                                                    typename I, typename V);
    DUCK_I_TEST_TYPE(value_type_,
                typename detail::iterator_traits<I>::value_type, typename I);
    typedef typename value_type_<It>::type Value;

public:
    typedef typename boost::mpl::and_<
                detail::is_valid<Value>,
                boost::is_convertible<
                    typename dereference<It, Value>::type,
                    typename boost::add_lvalue_reference<Value>::type
                >
            >::type type;
    static bool const value = type::value;
};

} // end namespace duck

#endif // !DUCK_LVALUE_ITERATOR_HPP
