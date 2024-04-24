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
    string query1 = "SELECT * from Game;";
    builder.append("<br><br><br> Game table before:" + myDB.query(query1) + "<br>");
    
    // Parse input string to get game details
    string teamId1, teamId2, score1, score2, gameDate;

    // Read command line arguments
    // First arg, argv[0], is the name of the program
    // Next args are the parameters
    if (argc == 6) { // Ensure we have the correct number of parameters
        teamId1 = argv[1];
        teamId2 = argv[2];
        score1 = argv[3];
        score2 = argv[4];
        gameDate = argv[5];
    } else {
        cerr << "Invalid number of arguments. Expected 5 parameters." << endl;
        return 1;
    }

    // Prepare to insert the new game
    string input = "'" + teamId1 + "','" + teamId2 + "','" + score1 + "','" + score2 + "','" + gameDate + "'";

    // Insert the new game
    myDB.insert("Game", input);    // insert new game
    
    // For debugging purposes: Show the Game table after insert
    builder.append("<br><br><br> Game table after:" + myDB.query(query1));
    cout << builder;
    
    myDB.disConnect(); // Disconnect from Database

    return 0;
}



