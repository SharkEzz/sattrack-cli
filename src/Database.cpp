#include "Database.hpp"

#include <iostream>
#include <fstream>
#include <exception>

static int queryCallback(void *data, int argc, char** argv, char** azColName)
{
    std::map<std::string, std::string> row;
    
    for(int i = 0; i < argc; i++)
    {
        row[azColName[i]] = argv[i];
    }

    sattrack::Database* dbRef = (sattrack::Database*) data;

    dbRef->queryRes.push_back(row);

    return 0;
}

namespace sattrack
{
    Database::Database(const char* path)
    {
        int rc = sqlite3_open(path, &this->db);

        if(rc != SQLITE_OK)
            std::__throw_logic_error(sqlite3_errmsg(this->db));

        this->dbOpened = true;
        this->dbPath = path;
    }

    Database::~Database()
    {
        if(this->dbOpened)
            sqlite3_close(this->db);
    }

    std::vector<std::map<std::string, std::string>> Database::query(const char* query)
    {
        int rc = sqlite3_exec(this->db, query, queryCallback, (void*)this, &this->errMsg);
        sqlite3_free(this->errMsg);

        if(rc != SQLITE_OK)
            std::__throw_logic_error("Query error");

        return this->queryRes;
    }

    bool Database::exec(const char* sql)
    {
        int rc = sqlite3_exec(this->db, sql, nullptr, 0, &this->errMsg);
        sqlite3_free(this->errMsg);

        if(rc != SQLITE_OK)
            return false;
        else return true;
    }

    bool Database::isEmpty() const
    {
        std::ifstream is(this->dbPath, std::fstream::in);
        std::string content;
        is >> content;
        is.close();

        if(content == "")
            return true;
        else return false;
    }

    void Database::init()
    {
        if(!this->isEmpty())
            return;

        const char* initStr = "CREATE TABLE tle(" \
                                "id INT PRIMARY KEY NOT NULL," \
                                "name VARCHAR(24) NOT NULL," \
                                "line1 VARCHAR(69) NOT NULL," \
                                "line2 VARCHAR(69) NOT NULL" \
                            ");";

        if(!this->exec(initStr))
            std::__throw_logic_error("Init error");
    }
} // namespace sattrack
