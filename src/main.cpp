#include <iostream>

#include "Database.hpp"
#include "TLEManager.hpp"
#include "ObserverManager.hpp"
#include <vector>
#include <SGP4/Tle.h>

using namespace sattrack;

int main()
{
    Database db("data/database/db.sqlite");
    if(db.isEmpty())
        db.init();

    TLEManager manager(&db);
    std::vector<Tle> tles = manager.getFromDB();

    ObserverManager obsManager(&db);
    Location location = obsManager.getFromDb();

    std::cout << "lat: " << location.latitude << " longitude: " << location.longitude << std::endl;
 
    for (auto &&tle : tles)
    {
        std::cout << tle.Name() << std::endl;
    }
    
    return EXIT_SUCCESS;
}
