#ifndef CLIDISPLAY_HPP
#define CLIDISPLAY_HPP

#include <SGP4/DateTime.h>
#include "TrackingInfos.hpp"
#include <iostream>

namespace sattrack
{
    class CLIDisplay
    {
    public:
        void Display(const TrackingInfos* infos, DateTime dt) const;
    };
} // namespace sattrack


#endif
