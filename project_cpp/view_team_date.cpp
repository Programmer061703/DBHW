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
 
   
   string date;

   // Read command line arguments
   // First arg, arg[0] is the name of the program
   // Next args are the parameters
   date = argv[1];


        string query = "SELECT T1.Location AS Team1Location, T1.Nickname AS Team1Name, "
                   "T2.Location AS Team2Location, T2.Nickname AS Team2Name, G.Date, "
                   "CONCAT(G.Score1, '-', G.Score2) AS Score, "
                   "CASE "
                   "WHEN G.Score1 > G.Score2 THEN CONCAT(T1.Nickname, ' Wins') "
                   "WHEN G.Score1 < G.Score2 THEN CONCAT(T2.Nickname, ' Wins') "
                   "ELSE 'Draw' "
                   "END AS Result "
                   "FROM Game G "
                   "JOIN Team T1 ON G.TeamId1 = T1.TeamId "
                   "JOIN Team T2 ON G.TeamId2 = T2.TeamId "
                   "WHERE G.Date = '" + date + "';";


 
    string result = myDB.query(query);

    if (!result.empty()) {
        cout << result;
      
    } else {
        cout << "<p>No teams found for conference: " << query << "</p>";
    }
       
   myDB.disConnect();//disconect Database

   return 0;
}


