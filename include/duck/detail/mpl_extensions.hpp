/**
 * This file defines some extensions for the Boost.MPL library.
 */

#ifndef DUCK_DETAIL_MPL_EXTENSIONS_HPP
#define DUCK_DETAIL_MPL_EXTENSIONS_HPP

#include <boost/mpl/apply.hpp>
#include <boost/mpl/contains.hpp>
#include <boost/mpl/end.hpp>
#include <boost/mpl/find_if.hpp>
#include <boost/mpl/not.hpp>
#include <boost/mpl/placeholders.hpp>
#include <boost/type_traits/is_same.hpp>


namespace boost {
namespace mpl {
    template <typename Sequence, typename Predicate>
    struct none_of
        : is_same<
            typename find_if<Sequence, Predicate>::type,
            typename end<Sequence>::type
        >
    { };

    template <typename Sequence, typename Predicate>
    struct any_of
        : not_<none_of<Sequence, Predicate> >
    { };

    namespace all_of_detail {
        template <typename Predicate>
        struct negate {
            template <typename Arg>
            struct apply
                : not_<typename ::boost::mpl::apply<Predicate, Arg>::type>
            { };
        };
    }

    template <typename Sequence, typename Predicate>
    struct all_of
        : none_of<Sequence, all_of_detail::negate<Predicate> >
    { };

    template <typename Sequence, typename Types>
    struct find_first_of
        : find_if<
            Sequence,
            contains<Types, _>
        >
    { };
} // end namespace mpl
} // end namespace boost

#endif // !DUCK_DETAIL_MPL_EXTENSIONS_HPP
