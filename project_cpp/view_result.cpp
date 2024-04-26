/* Compile using:
g++ -Wall -I/usr/include/cppconn -o odbc odbc_insert_restaurant.cpp -L/usr/lib -lmysqlcppconn 
run: 
./odbc */
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
 
   string builder = "";
 
   // Parse input string to get restaurant Name and Type and  City
   string date;

   // Read command line arguments
   // First arg, arg[0] is the name of the program
   // Next args are the parameters
   date = argv[1];

   string q = "SELECT g.Location AS game_location, "
      "CASE "
      "    WHEN g.Score1 > g.Score2 THEN t1.Nickname "
      "    WHEN g.Score2 > g.Score1 THEN t2.Nickname "
      "    ELSE 'Tie' "
      "END AS winner_name, "
      "CASE "
      "    WHEN g.Score1 > g.Score2 THEN g.Score1 "
      "    WHEN g.Score2 > g.Score1 THEN g.Score2 "
      "    ELSE g.Score1 "
      "END AS winning_score, "
      "CASE "
      "    WHEN g.Score1 < g.Score2 THEN t1.Nickname "
      "    WHEN g.Score2 < g.Score1 THEN t2.Nickname "
      "    ELSE 'Tie' "
      "END AS loser_name, "
      "CASE "
      "    WHEN g.Score1 < g.Score2 THEN g.Score1 "
      "    WHEN g.Score2 < g.Score1 THEN g.Score2 "
      "    ELSE g.Score1 "
      "END AS losing_score "
      "FROM Game g "
      "INNER JOIN Team t1 ON g.TeamId1 = t1.TeamId "
      "INNER JOIN Team t2 ON g.TeamId2 = t2.TeamId "
      "WHERE g.Date = '" + date + "';";

 
   //For debugging purposes: Show the database after insert
   builder.append("<br><br><br> Table ITEM after:" + myDB.query(q));
   cout << builder; 
       
   myDB.disConnect();//disconect Database

   return 0;
}


