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

    bool TLEManager::updateTle(const char* currentName, const char* newName, const char* line1, const char* line2) const
    {
        std::string query = "UPDATE tle SET name='" + std::string(newName) + "', line1='" + std::string(line1) + "', line2='" + std::string(line2) + "' WHERE name='" + std::string(currentName) + "';";

        bool ret = this->db->exec(query.c_str());

        return ret;
    }
} // namespace sattrack
