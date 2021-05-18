#ifndef LOGGER_HPP
#define LOGGER_HPP

#include <iostream>

namespace sattrack
{
    class Logger
    {
        public:
            static void info(const char* str, bool nf);
            static void warning(const char* str, bool nf);
            static void danger(const char* str, bool nf);
            static void success(const char* str, bool nf);
    };
}

#endif