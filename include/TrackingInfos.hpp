#ifndef TRACKINGINFOS_HPP
#define TRACKINGINFOS_HPP

#include <SGP4/CoordTopocentric.h>
#include <SGP4/CoordGeodetic.h>
#include <SGP4/Observer.h>
#include <SGP4/SGP4.h>

namespace sattrack
{
    namespace sgp4
    {
        // Give the Azimuth / Elevation / Altitude of an satellite using a TLE, observer location and eventually a DateTime
        class TrackingInfos
        {
            public:
                TrackingInfos(Tle *tle, Observer *obs);
                ~TrackingInfos();
                double getElevation(DateTime customDt) const;
                double getElevation() const;
                double getAzimuth(DateTime customDt) const;
                double getAzimuth() const;
                double getAltitude(DateTime customDt) const;
                double getAltitude() const;

            private:
                Tle *tle;
                Observer *obs;
                SGP4 *sgp4;
                double radToDeg(double rad) const;
        };
    }
}

#endif