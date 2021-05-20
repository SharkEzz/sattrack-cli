#include <iostream>

#include "Database.hpp"
#include <map>

using namespace sattrack;

int main()
{
    Database db("data/database/db.sqlite");
    if(db.isEmpty())
        db.init();

    std::vector<std::map<std::string, std::string>> res = db.query("SELECT * FROM tle");

    for (auto &&resRow : res)
    {
        std::cout << resRow["id"] << " - " << resRow["name"] << '\n';
    }
    
    
    return EXIT_SUCCESS;
}
