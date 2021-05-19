#ifndef TLELOADER_HPP
#define TLELOADER_HPP

#include <SGP4/Tle.h>
#include <json/json.h>
#include <string>
#include <vector>

namespace sattrack
{
    // Load a set of TLE from a JSON file
    class TleLoader
    {
    public:
        std::vector<Tle> loadAll(Json::Value jsonContent);
        std::vector<Tle> getLoadedTles() const;

    private:
        std::vector<std::string> parseTle(Json::Value tle);
        std::vector<Tle> loadedTles;
    };
} // namespace sattrack

#endif
