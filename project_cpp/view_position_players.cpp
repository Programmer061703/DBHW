#include "odbc_db.h"
#include <iostream>
#include <string>
#include <algorithm> // For std::replace

using namespace std;



int main(int argc, char *argv[])
{
    if (argc != 2) {
        cerr << "Usage: " << argv[0] << " <position>" << endl;
        return 1;
    }

    string Username = "";   // Change to your own username
    string mysqlPassword = "";  // Change to your MySQL password
    string SchemaName = ""; // Change to your username

    string position;

    odbc_db myDB;
    myDB.Connect(Username, mysqlPassword, SchemaName);
    myDB.initDatabase();

    position = argv[1];
    

    // SQL query to find players by position, with basic escaping
   
    string query = "SELECT PlayerId, Name, TeamId FROM Player WHERE Position = '" + position + "';";

    // Execute the query and print the results
    string result = myDB.query(query);
    if (!result.empty()) {
        cout << result;
    } else {
        cout << "<p>No players found for position: " << position << "</p>";
    }

    myDB.disConnect();

    return 0;
}
