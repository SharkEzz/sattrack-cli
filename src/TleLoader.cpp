#include "TleLoader.hpp"

namespace sattrack
{
    std::vector<Tle> TleLoader::loadAll(Json::Value jsonContent)
    {
        std::vector<Tle> tles;

        for(int i = 0; i < (int)jsonContent.size(); i++)
        {
            std::vector<std::string> lines = this->parseTle(jsonContent[i]);
            tles.push_back(Tle(lines[0], lines[1], lines[2]));
        }

        // Store a copy of loaded TLE
        this->loadedTles = tles;
        return tles;
    }

    std::vector<std::string> TleLoader::parseTle(Json::Value tle)
    {
        std::vector<std::string> lines;

        lines.push_back(tle["name"].asString());
        lines.push_back(tle["line1"].asString());
        lines.push_back(tle["line2"].asString());

        return lines;
    }

    std::vector<Tle> TleLoader::getLoadedTles() const
    {
        return this->loadedTles;
    }

} // namespace sattrack
