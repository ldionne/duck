/**
 * This file defines the `models` metafunction.
 */

#ifndef DUCK_MODELS_HPP
#define DUCK_MODELS_HPP

#include <boost/mpl/apply.hpp>


namespace duck {

//! Metafunction returning whether a `Type` is a model of a given `Concept`.
template <typename Concept, typename Type>
struct models
    : boost::mpl::apply<Concept, Type>
{ };

} // end namespace duck

#endif // !DUCK_MODELS_HPP
