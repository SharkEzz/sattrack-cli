#include <iostream>
#include "JSONLoader.hpp"
#include "TleLoader.hpp"
#include "TrackingInfos.hpp"
#include <SGP4/Observer.h>

using namespace sattrack;

int main()
{
    TleLoader loader;
    std::vector<Tle> tles = loader.loadAll(JSONLoader::load("data/satdata/tle.json"));

    Json::Value location = JSONLoader::load("data/location.json");
    Observer observer = Observer(location["latitude"].asDouble(), location["longitude"].asDouble(), location["altitude"].asDouble());

    TrackingInfos ti = TrackingInfos(&tles.at(0), &observer);
    std::cout << "az : " << ti.getAzimuth(DateTime::Now()) << " el : " << ti.getElevation(DateTime::Now()) << " alt : " << ti.getAltitude(DateTime::Now()) << std::endl;

    return EXIT_SUCCESS;
}