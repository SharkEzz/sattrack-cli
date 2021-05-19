#ifndef SATELLITEUTILS_HPP
#define SATELLITEUTILS_HPP

#include <SGP4/DateTime.h>
#include <SGP4/Tle.h>
#include <SGP4/Observer.h>
#include <vector>
#include "TrackingInfos.hpp"

namespace sattrack
{
    class SatelliteUtils
    {
    public:
        bool isVisible(Tle *tle, Observer *observer, double threshold);
        TrackingInfos getSatelliteInfos(Tle *tle, Observer *observer);
        std::vector<Tle> getVisibleSatellites(std::vector<Tle> tles, Observer *observer, double threshold);
    };
}

#endif