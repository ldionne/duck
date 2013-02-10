/**
 * Helper macros for unit tests.
 */


#define DUCK_I_STRINGIZE_PRIMITIVE(...) #__VA_ARGS__
#define DUCK_I_STRINGIZE(...) DUCK_I_STRINGIZE_PRIMITIVE(__VA_ARGS__)

#define ASSERT_MODELS(Concept, ...)                                         \
    static_assert((Concept<__VA_ARGS__>::value),                            \
        DUCK_I_STRINGIZE(__VA_ARGS__ does not model the Concept concept.))  \
/**/

#define ASSERT_NOT_MODELS(Concept, ...)                                     \
    static_assert(!(Concept<__VA_ARGS__>::value),                           \
        DUCK_I_STRINGIZE(__VA_ARGS__ models the Concept concept.))          \
/**/
