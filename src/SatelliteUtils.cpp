#include "SatelliteUtils.hpp"

namespace sattrack
{
    bool SatelliteUtils::isVisible(Tle *tle, Observer *observer, double threshold)
    {
        TrackingInfos ti = TrackingInfos(tle, observer);
        return ti.getElevation(DateTime::Now()) >= threshold;
    }
    
    TrackingInfos SatelliteUtils::getSatelliteInfos(Tle *tle, Observer *observer)
    {
        return TrackingInfos(tle, observer);
    }
    
    std::vector<Tle> SatelliteUtils::getVisibleSatellites(std::vector<Tle> tles, Observer *observer, double threshold)
    {
        std::vector<Tle> visibleSatellites;
        
        for(size_t i = 0; i < tles.size(); i++)
        {
            if(TrackingInfos(&tles.at(i), observer).getElevation(DateTime::Now()) > threshold)
                visibleSatellites.push_back(tles.at(i));
        }

        return visibleSatellites;
    }

} // namespace sattrack
