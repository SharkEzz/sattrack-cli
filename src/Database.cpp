#include "Database.hpp"

#include <iostream>
#include <fstream>
#include <exception>

static int queryCallback(void *db, int argc = 0, char** argv = {}, char** azColName = {})
{
    std::map<std::string, std::string> row;
    
    for(int i = 0; i < argc; i++)
    {
        row[azColName[i]] = argv[i];
    }

    sattrack::Database* dbRef = (sattrack::Database*) db;

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

    // Execute a SQL query and return an associative array for each line containing the column name and the value
    std::vector<std::map<std::string, std::string>> Database::query(const char* query)
    {
        this->queryRes.clear();
        int rc = sqlite3_exec(this->db, query, queryCallback, (void*)this, &this->errMsg);
        sqlite3_free(this->errMsg);

        if(rc != SQLITE_OK)
            std::__throw_logic_error("Query error");

        return this->queryRes;
    }

    // Execute a SQL statement without returning any values
    bool Database::exec(const char* sql)
    {
        int rc = sqlite3_exec(this->db, sql, nullptr, 0, &this->errMsg);
        sqlite3_free(this->errMsg);

        if(rc != SQLITE_OK)
        {
            std::cerr << sqlite3_errmsg(this->db) << '\n';
            return false;
        }
            
        else return true;
    }

    // Return true if the database is empty (no tables and data)
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

    // Initialize the database by creating the base tables
    void Database::init()
    {
        if(!this->isEmpty())
            return;

        const char* initTleTable = "CREATE TABLE tle(" \
                                "id INT PRIMARY KEY NOT NULL," \
                                "name VARCHAR(24) UNIQUE NOT NULL," \
                                "line1 VARCHAR(69) NOT NULL," \
                                "line2 VARCHAR(69) NOT NULL" \
                            ");";

        const char* initLocationTable = "CREATE TABLE location(" \
                                    "id INT PRIMARY KEY NOT NULL," \
                                    "latitude DECIMAL(10,6) NOT NULL," \
                                    "longitude DECIMAL(10,6) NOT NULL" \
                                ");";

        if(!this->exec(initTleTable) || !this->exec(initLocationTable))
            std::__throw_logic_error("Init error");
    }
} // namespace sattrack
