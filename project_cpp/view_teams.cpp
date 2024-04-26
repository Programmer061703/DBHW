#include "odbc_db.h"
#include <iostream>
#include <string>
#include <algorithm>

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
        cerr << "Usage: " << argv[0] << " <conference>" << endl;
        return 1;
    }

    string Username = "brw020";
    string mysqlPassword = "ar6Phis7";
    string SchemaName = "brw020";

    string conference = argv[1];

    odbc_db myDB;
    myDB.Connect(Username, mysqlPassword, SchemaName);

    string query = "SELECT TeamId, Location, Nickname FROM Team WHERE Conference = '" + escapeSQL(conference) + "' ORDER BY Location;";
    string result = myDB.query(query);

    if (!result.empty()) {
        cout << "<table border='1'>";
        cout << "<tr><th>Team ID</th><th>Location</th><th>Nickname</th></tr>";
        cout << result;
        cout << "</table>";
    } else {
        cout << "<p>No teams found for conference: " << conference << "</p>";
    }

    myDB.disConnect();

    return 0;
}
