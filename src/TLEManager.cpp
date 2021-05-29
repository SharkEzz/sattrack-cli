#include "TLEManager.hpp"

#include <spdlog/spdlog.h>
#include <map>

static size_t WriteCallback(void *contents, size_t size, size_t nmemb, void *userp)
{
    ((std::string*)userp)->assign((char*)contents);
    return size * nmemb;
}

namespace sattrack
{
    TLEManager::TLEManager(Database* db)
    {
        this->db = db;
        curl_global_init(CURL_GLOBAL_DEFAULT);
        this->curl = curl_easy_init();
        if(!this->curl)
            std::__throw_logic_error("CURL init error");
        curl_easy_setopt(this->curl, CURLOPT_WRITEFUNCTION, WriteCallback);
        curl_easy_setopt(this->curl, CURLOPT_WRITEDATA, &this->readBuffer);
    }

    TLEManager::~TLEManager()
    {
        curl_easy_cleanup(this->curl);
        curl_global_cleanup();
    }

    std::vector<Tle> TLEManager::getFromDB() const
    {
        std::vector<std::map<std::string, std::string>> dbTles = this->db->query("SELECT * FROM tle");
        std::vector<Tle> tles;

        for(auto &&tle: dbTles)
        {
            tles.push_back(Tle(tle["name"], tle["line1"], tle["line2"]));
        }

        return tles;        
    }

    Tle TLEManager::parseFromString(const char* name, const char* line1, const char* line2) const
    {
        return Tle(name, line1, line2);
    }

    bool TLEManager::updateTle(std::string currentName, std::string newName, std::string line1, std::string line2) const
    {
        std::string query = "UPDATE tle SET name='" + newName + "', line1='" + line1 + "', line2='" + line2 + "' WHERE name='" + currentName + "';";

        bool ret = this->db->exec(query.c_str());

        return ret;
    }

    void TLEManager::updateAll() const
    {
        spdlog::info("Starting TLE updater...");
        std::vector<Tle> tles = this->getFromDB();
        CURLcode res;
        
        for (auto &&tle : tles)
        {
            spdlog::info("Updating {}", tle.Name());
            int catnr = tle.NoradNumber();
            std::string url = "https://celestrak.com/NORAD/elements/gp.php?CATNR=" + std::to_string(catnr) + "&FORMAT=TLE";

            curl_easy_setopt(this->curl, CURLOPT_URL, url.c_str());
            res = curl_easy_perform(this->curl);
            if(res != CURLE_OK)
                std::__throw_logic_error("curl_easy_perform failed");

            std::stringstream ss(this->readBuffer);
            std::string temp;
            std::vector<std::string> lines;

            for(uint i = 0; i < 3; i++)
            {
                std::getline(ss, temp, '\n');
                temp.pop_back(); // Remove \n

                lines.push_back(temp);
            }
            
            this->updateTle(tle.Name(), lines.at(0), lines.at(1), lines.at(2));
        }
        
    }
} // namespace sattrack
