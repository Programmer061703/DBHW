#include "odbc_db.h"
#include <iostream>
#include <string>
#include <algorithm>

using namespace std;


int main()
{
    

    string Username = "";
    string mysqlPassword = "";
    string SchemaName = "";


    odbc_db myDB;
    myDB.Connect(Username, mysqlPassword, SchemaName);
    myDB.initDatabase();

   

    string query = "SELECT T.Conference, T.Nickname, T.Location, "
                   "COUNT(CASE WHEN (G.TeamId1 = T.TeamId AND G.Score1 > G.Score2) OR "
                   "(G.TeamId2 = T.TeamId AND G.Score2 > G.Score1) THEN 1 ELSE NULL END) AS TotalWins, "
                   "COUNT(CASE WHEN ((G.TeamId1 = T.TeamId AND G.Score1 > G.Score2) OR "
                   "(G.TeamId2 = T.TeamId AND G.Score2 > G.Score1)) AND "
                   "T1.Conference = T2.Conference THEN 1 ELSE NULL END) AS ConferenceWins "
                   "FROM Team T "
                   "LEFT JOIN Game G ON T.TeamId = G.TeamId1 OR T.TeamId = G.TeamId2 "
                   "LEFT JOIN Team T1 ON G.TeamId1 = T1.TeamId "
                   "LEFT JOIN Team T2 ON G.TeamId2 = T2.TeamId "
                   "GROUP BY T.TeamId, T.Conference, T.Nickname, T.Location "
                   "ORDER BY T.Conference ASC, TotalWins DESC, ConferenceWins DESC;";

    string result = myDB.query(query);

    if (!result.empty()) {
        cout << result;
      
    } else {
        cout << "<p>No teams found for conference: "<<endl;
    }

    myDB.disConnect();

    return 0;
}
