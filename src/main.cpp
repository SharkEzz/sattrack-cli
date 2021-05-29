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

    std::vector<Tle> visibleSatellites = utils.getVisibleSatellites(tles, &location, 5);

    std::cout << "Visible satellites :\n\n";

    for (size_t i = 0; i < visibleSatellites.size(); i++)
    {
        std::cout << i << ". " << visibleSatellites.at(i).Name() << " - Elevation: " << utils.getSatelliteInfos(&visibleSatellites.at(i), &location).getElevation() << '\n';
    }

    std::string choiceStr;

    std::cout << "\nChoice: ";
    std::cin >> choiceStr;
    int choice = std::stoi(choiceStr); // Selected satellite number
    Tle trackedSatellite = visibleSatellites.at(choice); // Selected satellite
    
    return EXIT_SUCCESS;
}
