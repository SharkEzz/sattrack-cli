#include <iostream>
#include <string>
#include <unistd.h>
#include "Logger.hpp"
#include <SGP4/DateTime.h>
#include "JSONLoader.hpp"
#include "TleLoader.hpp"
#include "SatelliteUtils.hpp"
#include <SGP4/Observer.h>
#include "TrackingInfos.hpp"
#include "CLIDisplay.hpp"
#include <SGP4/Tle.h>

using namespace sattrack;

int main()
{
    // Load main data from files
    JSONLoader jsonLoader;
    TleLoader loader;
    std::vector<Tle> tles = loader.loadAll(jsonLoader.load("data/satdata/tle.json"));

    Json::Value location = jsonLoader.load("data/location.json");
    Observer observer(location["latitude"].asDouble(), location["longitude"].asDouble(), location["altitude"].asDouble());

    SatelliteUtils utils;
    std::vector<Tle> visibleSatellites = utils.getVisibleSatellites(tles, &observer, 5);

    if(visibleSatellites.size() == 0)
    {
        std::cout << "No currently visible satellites" << std::endl;
        return EXIT_SUCCESS;
    }

    std::cout << "Visible satellites:\n\n";

    for(size_t i = 0; i < visibleSatellites.size(); i++)
    {
        Tle tle = visibleSatellites.at(i);
        std::cout << i << " - " << tle.Name() << '\n';
    }

    std::cout << "\nChoice: ";
    unsigned int choice;
    std::cin >> choice;

    if(choice >= visibleSatellites.size())
    {
        Logger::danger("Invalid choice", 1);
        return EXIT_FAILURE;
    }

    Tle selectedSatellite = visibleSatellites.at(choice);

    TrackingInfos infos = utils.getSatelliteInfos(&selectedSatellite, &observer);

    CLIDisplay cliDisplay;

    while(utils.isVisible(&selectedSatellite, &observer, 5))
    {
        cliDisplay.Display(&infos, DateTime::Now());
        usleep(50 * 10000);
    }

    return EXIT_SUCCESS;
}
