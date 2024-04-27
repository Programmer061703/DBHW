#include "odbc_db.h"
#include <iostream>
#include <string>
using namespace std;

int main(int argc, char *argv[])
{
    string Username = "brw020";   // Change to your own username
    string mysqlPassword = "ar6Phis7";  // Change to your mysql password
    string SchemaName = "brw020"; // Change to your username

    odbc_db myDB;
    myDB.Connect(Username, mysqlPassword, SchemaName);
    myDB.initDatabase();

    // For debugging purposes: Show the Game table before insert
    string builder = "";
    string query1 = "SELECT * from PlayerStats;";
    builder.append("<br><br><br> Stats table before:" + myDB.query(query1) + "<br>");
    
    // Parse input string to get game details
    string playerId,gameId,touchdowns,passingYards,rushingYards,receptions,tackles,interceptions;

    // Read command line arguments
    // First arg, argv[0], is the name of the program
    // Next args are the parameters
    if (argc == 9) { // Ensure we have the correct number of parameters
        playerId = argv[1];
        gameId = argv[2];
        touchdowns = argv[3];
        passingYards = argv[4];
        rushingYards = argv[5];
        receptions = argv[6];
        tackles = argv[7];
        interceptions = argv[8];
    } else {
        cerr << "Invalid number of arguments. Expected 5 parameters." << endl;
        return 1;
    }
    string q = "select IFNULL(max(StatId), 0) as StatId from PlayerStats";
    sql::ResultSet *result = myDB.rawQuery(q);
        int next_id = 1;
        if (result->next()) // get first row of result set
            next_id += result->getInt("StatId");

    // Prepare to insert the new game
    string input = "'"+ to_string(next_id) + "','" + playerId + "','" + gameId + "','" + touchdowns + "','" + passingYards + "','" + rushingYards + "','" + receptions +"','"+ tackles + "','" + interceptions +"'";
   
    // Insert the new game
    myDB.insert("PlayerStats", input);    
    
    
    builder.append("<br><br><br> Stats table after:" + myDB.query(query1));
    cout << builder;
    
    myDB.disConnect(); // Disconnect from Database

    return 0;
}