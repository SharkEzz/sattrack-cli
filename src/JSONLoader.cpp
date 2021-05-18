#include "JSONLoader.hpp"

namespace sattrack
{
    Json::Value JSONLoader::load(const char* path)
    {
        std::ifstream is(path, std::fstream::binary);
        Json::Value json;

        is >> json;

        is.close();

        return json;
    }

    void JSONLoader::write(const char* path, Json::Value data)
    {
        std::ofstream os(path, std::fstream::trunc);
        os.write(data.asCString(), data.asString().length());
    }
}