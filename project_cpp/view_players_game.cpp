#include "odbc_db.h"
#include <iostream>
#include <string>
#include <algorithm> // For std::replace

using namespace std;



int main(int argc, char *argv[])
{
    if (argc != 2) {
        cerr << "Usage: " << argv[0] << " <teamName>" << endl;
        return 1;
    }

    string Username = "";   // Change to your own username
    string mysqlPassword = "";  // Change to your MySQL password
    string SchemaName = ""; // Change to your username

    

    odbc_db myDB;
    myDB.Connect(Username, mysqlPassword, SchemaName);
    myDB.initDatabase();
    string playerId;
    playerId = argv[1];
    // SQL query to find players from the specified team, with basic escaping
    string query = "SELECT g.GameId, g.TeamId1, g.TeamId2, ps.Touchdowns, ps.PassingYards, "
                   "ps.RushingYards, ps.Receptions, ps.Tackles, ps.Interceptions, "
                   "IF(g.Score1 > g.Score2, 'Win', 'Loss') AS Result "
                   "FROM Game g "
                   "JOIN PlayerStats ps ON g.GameId = ps.GameId "
                   "WHERE ps.PlayerId = " + playerId;

    // Execute the query and print the results
    string result = myDB.query(query);
    if (!result.empty()) {
         cout << result;
    } else {
        cout << "<p>No players found for the team: " << playerId << "</p>";
    }

    myDB.disConnect();

    return 0;
}