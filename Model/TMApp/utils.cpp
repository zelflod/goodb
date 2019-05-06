#include <utility>



#include "utils.h"

namespace TMApp {
    namespace utils {
        std::string sha256(std::string input){
            return SHA256_lib::sha256(std::move(input));
        }

        std::string format_time(int time)
        {
            std::time_t t_val = time;
            char out[100] = {0};
            if (std::strftime(out, sizeof(out), "%F %T", std::localtime(&t_val))) {
                return std::string(out);
            }
            return "";
        }

        int get_time(std::string date)
        {
            std::tm t;
            if (strptime(date.c_str(), "%Y-%m-%d %H:%M:%S", &t)) {
                return static_cast<int>(std::mktime(&t));
            }
            return -1;
        }
    }
}