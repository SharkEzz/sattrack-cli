#ifndef TLEMANAGER_HPP
#define TLEMANAGER_HPP

#include "Database.hpp"
#include <vector>
#include <SGP4/Tle.h>
#include <SGP4/Observer.h>

namespace sattrack
{
    class TLEManager
    {
    public:
        TLEManager(Database* db);
        std::vector<Tle> getFromDB() const;
        Tle parseFromString(const char* name, const char* line1, const char* line2) const;
        bool updateTle(const char* currentName, const char* newName, const char* line1, const char* line2) const;

    private:
        Database* db;
    };
} // namespace sattrack


#endif
