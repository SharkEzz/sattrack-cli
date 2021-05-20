#include <iostream>

#include "Database.hpp"
#include "TLEManager.hpp"
#include <vector>
#include <SGP4/Tle.h>

using namespace sattrack;

int main()
{
    Database db("data/database/db.sqlite");
    if(db.isEmpty())
        db.init();

    TLEManager manager(&db);
    std::vector<Tle> tles = manager.getFromDB();

    for (auto &&tle : tles)
    {
        std::cout << tle.Name() << std::endl;
    }
    
    
    return EXIT_SUCCESS;
}
