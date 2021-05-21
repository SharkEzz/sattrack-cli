#include "ObserverManager.hpp"

#include <vector>
#include <map>
#include <iostream>

namespace sattrack
{
    ObserverManager::ObserverManager(Database* db)
    {
        this->db = db;
    }

    Location ObserverManager::getFromDb() const
    {
        std::vector<std::map<std::string, std::string>> res = this->db->query("SELECT * FROM location WHERE id = 1");
        std::string::size_type sz;

        Location location = { std::stod(res.at(0)["latitude"], &sz), std::stod(res.at(0)["longitude"], &sz) };

        return location;
    }

    bool ObserverManager::setLocation(const double latitude, const double longitude) const
    {
        std::string lat = std::to_string(latitude);
        std::string lon = std::to_string(longitude);

        std::string query = "UPDATE location SET latitude=" + lat + ", longitude=" + lon + " WHERE id = 1";
        return this->db->exec(query.c_str());
    }
} // namespace sattrack
