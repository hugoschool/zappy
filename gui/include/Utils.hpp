#pragma once

#include <string>

namespace zappy {
    class Utils {
        public:
            static bool isInt(std::string str);
            static bool isSize_t(std::string str);
            static bool isFloat(std::string str);
    };
}
