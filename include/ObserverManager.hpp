#ifndef OBSERVERMANAGER_HPP
#define OBSERVERMANAGER_HPP

#include "Database.hpp"

namespace sattrack
{
    struct Location
    {
        const double latitude;
        const double longitude;
    };

    class ObserverManager
    {
    public:
        ObserverManager(Database* db);
        Location getFromDb() const;
        bool setLocation(const double latitude, const double longitude) const;

    private:
        Database* db;
    };
} // namespace sattrack


#endif
