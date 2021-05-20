#include "utils.hpp"

#include <SGP4/DateTime.h>

namespace sattrack
{
    void display(const TrackingInfos infos)
    {
        Tle tle = infos.getTle();
        double az = infos.getAzimuth();
        double el = infos.getElevation();
        double alt = infos.getAltitude();
        
        std::cout << "\033[H\033[2J"; // Clear the screen

        std::cout << "Tracking: " << tle.Name() << '\t' << "Current date/time: " << DateTime::Now() << '\n';
        std::cout << "Azimuth: " << az << "°\t";
        std::cout << "Elevation: " << el << "°\t";
        std::cout << "Altitude: " << alt / 100 << " km\t\n\n";
    }
}
