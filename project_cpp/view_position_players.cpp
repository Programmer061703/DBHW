#include "odbc_db.h"
#include <iostream>
#include <string>
#include <algorithm> // For std::replace

using namespace std;

// Simple function to escape single quotes in user input for SQL queries
string escapeSQL(const string& input) {
    string output = input;
    // Replace single quotes with two single quotes for SQL escaping
    size_t pos = 0;
    while ((pos = output.find("'", pos)) != string::npos) {
        output.replace(pos, 1, "''");
        pos += 2; // Move past the inserted characters
    }
    return output;
}

int main(int argc, char *argv[])
{
    if (argc != 2) {
        cerr << "Usage: " << argv[0] << " <position>" << endl;
        return 1;
    }

    string Username = "brw020";   // Change to your own username
    string mysqlPassword = "ar6Phis7";  // Change to your MySQL password
    string SchemaName = "brw020"; // Change to your username

    string position = argv[1];

    odbc_db myDB;
    myDB.Connect(Username, mysqlPassword, SchemaName);

    // SQL query to find players by position, with basic escaping
    string safePosition = escapeSQL(position);
    string query = "SELECT PlayerId, Name, TeamId FROM Player WHERE Position = '" + safePosition + "';";

    // Execute the query and print the results
    string result = myDB.query(query);
    if (!result.empty()) {
        cout << "<table border='1'>";
        cout << "<tr><th>Player ID</th><th>Name</th><th>Team ID</th></tr>";
        cout << result;
        cout << "</table>";
    } else {
        cout << "<p>No players found for position: " << position << "</p>";
    }

    myDB.disConnect();

    return 0;
}
