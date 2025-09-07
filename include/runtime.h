#ifndef runtimeHeader
    #define runtimeHeader
    #include <time.h>
    #define cStart(name) clock_t name##1 = clock()
    #define cEnd(name) clock_t name##2 = clock()
    #define printRuntime(name) (printf("runtime of %s: %.2fms\n", #name, (double)(name##2 - name##1) / CLOCKS_PER_SEC * 1000))
#endif
