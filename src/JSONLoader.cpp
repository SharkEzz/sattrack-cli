#include "JSONLoader.hpp"

namespace sattrack
{
    Json::Value JSONLoader::load(const char* path)
    {
        std::ifstream is(path, std::fstream::binary);
        Json::Value json;

        is >> json;

        return json;
    }
}