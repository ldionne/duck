/**
 * Helper macros for unit tests.
 */

#include <type_traits>


#define DUCK_I_STRINGIZE_PRIMITIVE(...) #__VA_ARGS__
#define DUCK_I_STRINGIZE(...) DUCK_I_STRINGIZE_PRIMITIVE(__VA_ARGS__)

#define ASSERT_MODELS(Concept, ...)                                         \
    static_assert(::std::is_same<                                           \
                    Concept<__VA_ARGS__>::type,                             \
                    ::std::true_type                                        \
                  >::value,                                                 \
    DUCK_I_STRINGIZE(__VA_ARGS__ does not model the Concept concept.))      \
/**/

#define ASSERT_NOT_MODELS(Concept, ...)                                     \
    static_assert(::std::is_same<                                           \
                    Concept<__VA_ARGS__>::type,                             \
                    ::std::false_type                                       \
                  >::value,                                                 \
    DUCK_I_STRINGIZE(__VA_ARGS__ models the Concept concept.))              \
/**/
