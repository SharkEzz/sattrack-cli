#include "TLEManager.hpp"

#include <map>

namespace sattrack
{
    TLEManager::TLEManager(Database* db)
    {
        this->db = db;
    }

    std::vector<Tle> TLEManager::getFromDB() const
    {
        std::vector<std::map<std::string, std::string>> dbTles = this->db->query("SELECT * FROM tle");
        std::vector<Tle> tles;

        for(auto &&tle: dbTles)
        {
            tles.push_back(Tle(tle["name"], tle["line1"], tle["line2"]));
        }

        return tles;        
    }

    Tle TLEManager::parseFromString(const char* name, const char* line1, const char* line2) const
    {
        return Tle(name, line1, line2);
    }
} // namespace sattrack
