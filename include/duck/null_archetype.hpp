/**
 * This file defines the @em null_archetype class.
 */

#ifndef DUCK_NULL_ARCHETYPE_HPP
#define DUCK_NULL_ARCHETYPE_HPP

namespace duck {

/**
 * Archetype that models no concept.
 */
class null_archetype {
    null_archetype() /*= delete*/;
    null_archetype(null_archetype const&) /*= delete*/;
    null_archetype(null_archetype&&) /*= delete*/;
    null_archetype& operator=(null_archetype const&) /*= delete*/;
    ~null_archetype() /*= delete*/;
};

} // end namespace duck

#endif // !DUCK_NULL_ARCHETYPE_HPP
