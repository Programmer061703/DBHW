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

    string Username = "brw020";   // Change to your own username
    string mysqlPassword = "ar6Phis7";  // Change to your MySQL password
    string SchemaName = "brw020"; // Change to your username

    

    odbc_db myDB;
    myDB.Connect(Username, mysqlPassword, SchemaName);
    myDB.initDatabase();
    string teamName;
    teamName = argv[1];
    // SQL query to find players from the specified team, with basic escaping
    string query = "SELECT PlayerId, Name, Position FROM Player JOIN Team ON Player.TeamId = Team.TeamId ";
    query += "WHERE Team.Nickname = '" + teamName + "';";

    // Execute the query and print the results
    string result = myDB.query(query);
    if (!result.empty()) {
        // cout << "<table border='1'>";
        // cout << "<tr><th>Player ID</th><th>Name</th><th>Position</th></tr>";
         cout << result;
        // cout << "</table>";
    } else {
        cout << "<p>No players found for the team: " << teamName << "</p>";
    }

    myDB.disConnect();

    return 0;
}
