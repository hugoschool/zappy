#pragma once

#include "IEntity.hpp"
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

            static int getOrientation(int orientation) {
                switch (orientation) {
                    case 1: return 90;
                    case 2: return 180;
                    case 3: return 270;
                    case 4: return 0;
                    default: return 0;
                }
            };

            static tileCoordinates handleTileOverflow(tileCoordinates coords, std::pair<int, int> dimensions) {
                if (coords.first >= dimensions.first) {
                    coords.first = 0;
                }
                if (coords.second >= dimensions.second) {
                    coords.second = 0;
                }
                if (coords.first < 0) {
                    coords.first = dimensions.first - 1;
                }
                if (coords.second < 0) {
                    coords.second = dimensions.second - 1;
                }
                return coords;
            };
    };
}
