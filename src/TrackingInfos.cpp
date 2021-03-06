#include "TrackingInfos.hpp"

#include <ctime>
#include <cmath>

namespace sattrack
{
    TrackingInfos::TrackingInfos(Tle *tle, Observer *obs)
    {
        this->tle = tle;
        this->obs = obs;
        this->sgp4 = new SGP4(*tle);
    }

    TrackingInfos::~TrackingInfos()
    {
        delete this->sgp4;
    }

    double TrackingInfos::getElevation(DateTime customDt) const
    {
        Eci eci = this->sgp4->FindPosition(customDt);
        return this->radToDeg(this->obs->GetLookAngle(eci).elevation);
    }

    double TrackingInfos::getAzimuth(DateTime customDt) const
    {
        Eci eci = this->sgp4->FindPosition(customDt);
        return this->radToDeg(this->obs->GetLookAngle(eci).azimuth);
    }

    double TrackingInfos::getAltitude(DateTime customDt) const
    {
        Eci eci = this->sgp4->FindPosition(customDt);
        return this->radToDeg(this->obs->GetLookAngle(eci).range);
    }

    double TrackingInfos::getElevation() const
    {
        Eci eci = this->sgp4->FindPosition(DateTime::Now());
        return this->radToDeg(this->obs->GetLookAngle(eci).elevation);
    }

    double TrackingInfos::getAzimuth() const
    {
        Eci eci = this->sgp4->FindPosition(DateTime::Now());
        return this->radToDeg(this->obs->GetLookAngle(eci).azimuth);
    }

    double TrackingInfos::getAltitude() const
    {
        Eci eci = this->sgp4->FindPosition(DateTime::Now());
        return this->radToDeg(this->obs->GetLookAngle(eci).range);
    }

    double TrackingInfos::radToDeg(double rad) const
    {
        return rad * (180 / M_PI);
    }

    Tle TrackingInfos::getTle() const
    {
        return *this->tle;
    }
} // namespace sattrack
