#ifndef TLEMANAGER_HPP
#define TLEMANAGER_HPP

#include "Database.hpp"
#include <vector>
#include <SGP4/Tle.h>
#include <SGP4/Observer.h>
#include <curl/curl.h>

namespace sattrack
{
    class TLEManager
    {
    public:
        TLEManager(Database* db);
        ~TLEManager();
        std::vector<Tle> getFromDB() const;
        Tle parseFromString(const char* name, const char* line1, const char* line2) const;
        bool updateTle(std::string currentName, std::string newName, std::string line1, std::string line2) const;
        void updateAll() const;

    private:
        Database* db;
        CURL* curl;
        std::string readBuffer;
    };
} // namespace sattrack


#endif
