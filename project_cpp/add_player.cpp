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
 
    // For debugging purposes: Show the Player table before insert
    string builder = "";
    string query1 = "SELECT * from Player;";
    builder.append("<br><br><br> Player table before:" + myDB.query(query1) + "<br>");
 
    // Read command line arguments
    // First arg, arg[0], is the name of the program
    // Next args are the parameters
    if (argc != 5) {
        cerr << "Usage: " << argv[0] << " TeamId Name Position" << endl;
        return 1;
    }
    string playerId = argv[1];
    string teamId = argv[2];
    string name = argv[3];
    string position = argv[4];

    // Construct the input string for SQL INSERT statement
    string input = "'" + playerId + "','" + teamId + "','" + name + "','" + position + "'";
    cout << input<<endl;
    // Insert the new player
    myDB.insert("Player", input);
 
    // For debugging purposes: Show the Player table after insert
    builder.append("<br><br><br> Player table after:" + myDB.query(query1));
    cout << builder; 
       
    myDB.disConnect(); // Disconnect Database

    return 0;
}
