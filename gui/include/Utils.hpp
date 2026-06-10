#pragma once

#include <string>
#include <sstream>

namespace zappy {
    class Utils {
        public:
            template<typename T>
            static bool isOfType(std::string str)
            {
                std::stringstream ss(str);
                T value;

                if (ss.fail())
                    return false;

                ss >> value;

                if (ss.fail())
                    return false;

                return ss.eof();
            }
    };
}
