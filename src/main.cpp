#include <iostream>

#include "Database.hpp"
#include "TLEManager.hpp"
#include "ObserverManager.hpp"
#include "SatelliteUtils.hpp"
#include "TrackingInfos.hpp"
#include <vector>
#include <SGP4/Tle.h>
#include <SGP4/Observer.h>

using namespace sattrack;

int main()
{
    Database db("data/database/db.sqlite");
    if(db.isEmpty())
        db.init();

    TLEManager manager(&db);
    std::vector<Tle> tles = manager.getFromDB();

    ObserverManager obsManager(&db);
    Observer location = obsManager.getFromDb();

    SatelliteUtils utils;

    std::cout << utils.isVisible(&tles.at(1), &location, 5) << std::endl;
    
    return EXIT_SUCCESS;
}
