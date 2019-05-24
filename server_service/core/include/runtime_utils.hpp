
#pragma once

#include <execinfo.h>
#include <unistd.h>

namespace cfx {
    class RuntimeUtils {
    public:
        static void printStackTrace() {
            const int MAX_CALLSTACK = 100;
            void * callstack[MAX_CALLSTACK];
            int frames;
                        
            // получить void* для всех записей в стеке
            frames = backtrace(callstack, MAX_CALLSTACK);

            // распечатать все frame'ы в stderr
            backtrace_symbols_fd(callstack, frames, STDERR_FILENO);
        }
    };
}