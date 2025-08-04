#ifndef FUNCTIONAL_SUPPORTED
    #if defined(__has_include) // Check if __has_include is supported
        #if __has_include(<functional>)
            #define FUNCTIONAL_SUPPORTED
        #endif
    #endif
#endif