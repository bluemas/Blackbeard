//
// Created by lg on 11/12/17.
//

#ifndef AMSS_LOGGING_H
#define AMSS_LOGGING_H

#include <iostream>
#include <stdarg.h>

class Logging {
public:
    enum LogLevel { INFO, DEBUG, ERROR };
    static void logOutput(LogLevel level, const char *format, ...) {
        char msg[256] = { 0 };

        va_list marker;
        va_start(marker, format);
        vsprintf(msg, format, marker);
        va_end(marker);

        #ifdef Debug
        if (level == Logging::DEBUG) {
            std::cout << "[DEBUG] " << msg << std::endl;
        }
        else
        #endif
        {
            std::cout << (level == Logging::INFO ? "[INFO] " :
                          (level == ERROR ? "[ERROR] " : "[UNKNOW] ")) << msg
                      << std::endl;
        }
    }
};

#endif //AMSS_LOGGING_H
