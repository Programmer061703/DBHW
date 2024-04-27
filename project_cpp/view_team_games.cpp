#include "odbc_db.h"
#include <iostream>
#include <string>
#include <algorithm>

using namespace std;


int main(int argc, char *argv[])
{
    if (argc != 2) {
        cerr << "Usage: " << argv[0] << " <conference>" << endl;
        return 1;
    }

    string Username = "brw020";
    string mysqlPassword = "ar6Phis7";
    string SchemaName = "brw020";


    odbc_db myDB;
    myDB.Connect(Username, mysqlPassword, SchemaName);
    myDB.initDatabase();

   string TeamName;

   
   TeamName = argv[1];

    string input = "SELECT T1.Location AS Team1Location, T1.Nickname AS Team1Name, "
                   "T2.Location AS Team2Location, T2.Nickname AS Team2Name, G.Date, "
                   "CONCAT(G.Score1, '-', G.Score2) AS Score, "
                   "CASE WHEN (T1.Nickname = '" + TeamName + "' AND G.Score1 > G.Score2) OR "
                   "(T2.Nickname = '" + TeamName + "' AND G.Score2 > G.Score1) THEN 'Won' "
                   "WHEN (T1.Nickname = '" + TeamName + "' AND G.Score1 < G.Score2) OR "
                   "(T2.Nickname = '" + TeamName + "' AND G.Score2 < G.Score1) THEN 'Lost' "
                   "ELSE 'Draw' END AS Result "
                   "FROM Game G JOIN Team T1 ON G.TeamId1 = T1.TeamId "
                   "JOIN Team T2 ON G.TeamId2 = T2.TeamId "
                   "WHERE T1.Nickname = '" + TeamName + "' OR T2.Nickname = '" + TeamName + "';";


  string result = myDB.query(input);

    if (!result.empty()) {
        cout << result;
      
    } else {
        cout << "<p>No teams found for conference: " << input << "</p>";
    }

    myDB.disConnect();

    return 0;
}