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
 
   // For debugging purposes:  Show the database before insert
   string builder = "";
   string query1 = "SELECT * from ITEM;";
   builder.append("<br><br><br> ITEM table before:" + myDB.query(query1) +"<br>");
 
   // Parse input string to get restaurant Name and Type and  City
   string name;
   string supplier_id;
   string quantity;
   string unit_price;

   // Read command line arguments
   // First arg, arg[0] is the name of the program
   // Next args are the parameters
   name = argv[1];
   supplier_id = argv[2];
   quantity = argv[3];
   unit_price = argv[4];

   // Get the next id
   string q = "select IFNULL(max(ID), 0) as max_id from ITEM";
   sql::ResultSet *result = myDB.rawQuery(q);
   int next_id = 1;
   if (result->next()) // get first row of result set
      next_id += result->getInt("max_id");

   // Insert the new restaurant
   string input = "'" + to_string(next_id) + "','" + name + "','" + supplier_id + "','" + quantity + "','" + unit_price + "'";

   // DEBUG:
   // printf("%s", input.c_str());
   myDB.insert("ITEM", input);    // insert new restaurant
 
   //For debugging purposes: Show the database after insert
   builder.append("<br><br><br> Table ITEM after:" + myDB.query(query1));
   cout << builder; 
       
   myDB.disConnect();//disconect Database

   return 0;
}


