

#ifndef GOODB_UTILS_H
#define GOODB_UTILS_H

#include <string>
#include <ctime>
#include "sha256.h"

namespace TMApp {
    namespace utils {
        std::string sha256(std::string input);

        std::string format_time(int time);

        int get_time(std::string date);
    }
}


#endif //GOODB_UTILS_H
