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
    string teamId1, teamId2, score1, score2, gameDate,gameId;

    // Read command line arguments
    // First arg, argv[0], is the name of the program
    // Next args are the parameters
    if (argc == 7) { // Ensure we have the correct number of parameters
        gameId = argv[1];
        teamId1 = argv[2];
        teamId2 = argv[3];
        score1 = argv[4];
        score2 = argv[5];
        gameDate = argv[6];
        
    } else {
        cerr << "Invalid number of arguments. Expected 5 parameters." << endl;
        return 1;
    }

    // Prepare to insert the new game
    string input = "'"+ gameId + "','" + teamId1 + "','" + teamId2 + "','" + score1 + "','" + score2 + "','" + gameDate + "'";
   
    // Insert the new game
    myDB.insert("Game", input);    // insert new game
    
    // For debugging purposes: Show the Game table after insert
    builder.append("<br><br><br> Game table after:" + myDB.query(query1));
    cout << builder;
    
    myDB.disConnect(); // Disconnect from Database

    return 0;
}