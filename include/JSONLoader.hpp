#ifndef JSONLOADER_HPP
#define JSONLOADER_HPP

#include <string>
#include <json/json.h>
#include <fstream>

namespace sattrack
{
    class JSONLoader
    {
    public:
        static Json::Value load(const char* path);
    };
}

#endif