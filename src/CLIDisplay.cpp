#include "CLIDisplay.hpp"

#include <string>
#include <SGP4/Tle.h>

namespace sattrack
{
    void CLIDisplay::Display(const TrackingInfos* infos, DateTime dt) const
    {
        Tle* tle = infos->getTle();
        double az = infos->getAzimuth(dt);
        double el = infos->getElevation(dt);
        double alt = infos->getAltitude(dt);
        

        std::cout << "\033[H\033[2J"; // Clear the screen

        std::cout << "Tracking: " << tle->Name() << '\t' << "Current date/time: " << dt.Year() << '-' << dt.Month() << '-' << dt.Day() << ' ' << dt.Hour() << ':' << dt.Minute() << ':' << dt.Second() << "\n\n";
        std::cout << "Azimuth: " << az << "°\t";
        std::cout << "Elevation: " << el << "°\t";
        std::cout << "Altitude: " << alt / 100 << " km\t\n\n";
    }
} // namespace sattrack
