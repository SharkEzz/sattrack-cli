#ifndef DATABASE_HPP
#define DATABASE_HPP

#include <sqlite3.h>
#include <vector>
#include <string>
#include <map>

namespace sattrack
{
    class Database
    {
    public:
        Database(const char* path);
        ~Database();
        std::vector<std::map<std::string, std::string>> query(const char* query);
        bool exec(const char* sql);
        bool isEmpty() const;
        void init();
        std::vector<std::map<std::string, std::string>> queryRes;

    private:
        const char* dbPath;
        sqlite3* db;
        char* errMsg = 0;
        bool dbOpened = false;
    };
} // namespace sattrack


#endif
