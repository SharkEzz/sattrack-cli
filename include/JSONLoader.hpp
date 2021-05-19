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
        Json::Value load(const char* path);
        void write(const char* path, Json::Value data);
    };
} // namespace sattrack

#endif
