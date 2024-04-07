// DO:  more ~username/.my.cnf to see your password
// CHANGE:  MYUSERNAME and MYMYSQLPASSWORD in the main function to your username and mysql password
// COMPILE AND RUN:      ./compileandruncpp.sh
#include "mysql_connection.h"
#include <cppconn/driver.h>
#include <cppconn/exception.h>
#include <cppconn/resultset.h>
#include <cppconn/metadata.h>
#include <cppconn/resultset_metadata.h>
#include <cppconn/statement.h>
#include <cppconn/prepared_statement.h>
 
using namespace std;
 
sql::Driver *driver;
sql::Connection *con;
sql::Statement *statement;
sql::ResultSet *resultSet;
sql::ResultSetMetaData *metaData;
sql::Connection* Connect(string, string);
 
void insert(string table, string values );
void initDatabase(const string Username, const string Password, const string SchemaName);
void query (string q);
void print (sql::ResultSet *resultSet);
void disconnect();
void printRecords(sql::ResultSet *resultSet, int numColumns);
void printHeader(sql::ResultSetMetaData *metaData, int numColumns);
 

int main() 
{
 
    string Username = "MYUSERNAME";             // Change to your own username
    string mysqlPassword = "MYMYSQLPASSWORD";   // Change to your own mysql password

    initDatabase(Username, mysqlPassword, Username); //init and testing - use it to enter your queries

    cout << "\nTesting select:\n";
    query("SELECT * FROM DEPT");

    cout << "\nTesting insert of dept MATH:\n";
    insert ("DEPT", "'MATH', 'Mathematics', 309, 'SCEN'"); 
    query("SELECT * FROM DEPT WHERE DEPT_CODE = 'MATH';");

    cout << "\nTesting delete of dept MATH:";
    statement->executeUpdate("DELETE FROM DEPT WHERE DEPT_CODE = 'MATH';");
    query("SELECT * FROM DEPT WHERE DEPT_CODE = 'MATH';");

    cout << "\nTesting update of professor name:";
    query("SELECT * FROM PROFESSOR WHERE PROF_ID = 123456;");
    statement->executeUpdate("Update PROFESSOR set PROF_NAME = 'Susan Dyer' WHERE PROF_ID = 123456;");
    query("SELECT * FROM PROFESSOR WHERE PROF_ID = 123456;");    

    disconnect();   
}   

// Connect to the database
sql::Connection* Connect(const string Username, const string Password)
 {
	 try{
	
		driver = get_driver_instance();
		con = driver->connect("tcp://127.0.0.1:3306", Username, Password);
		}
		 
	catch (sql::SQLException &e) {
        cout << "ERROR: SQLException in " << __FILE__;
        cout << " (" << __func__<< ") on line " << __LINE__ << endl;
        cout << "ERROR: " << e.what();
        cout << " (MySQL error code: " << e.getErrorCode();
        cout << ", SQLState: " << e.getSQLState() << ")" << endl;
        }
   return con;
}

// Disconnect from the database
void disconnect()
{
		delete resultSet;
		delete statement;
		con -> close();
		delete con;
} 

// Execute an SQL query passed in as a string parameter
// and print the resulting relation
void query (string q)
{
        try {
            resultSet = statement->executeQuery(q);
            cout<<("---------------------------------\n");
            cout<<("Query: \n" + q + "\n\nResult: \n");
            print(resultSet);
        }
        catch (sql::SQLException e) {
          
	    cout << "ERROR: SQLException in " << __FILE__;
        cout << " (" << __func__<< ") on line " << __LINE__ << endl;
        cout << "ERROR: " << e.what();
        cout << " (MySQL error code: " << e.getErrorCode();
        cout << ", SQLState: " << e.getSQLState() << ")" << endl;
        }
}
 
// Print the results of a query with attribute names on the first line
// Followed by the tuples, one per line
void print (sql::ResultSet *resultSet) 
{
    try{
		if (resultSet -> rowsCount() != 0)
		{
   		   sql::ResultSetMetaData *metaData = resultSet->getMetaData();
           int numColumns = metaData->getColumnCount();
		   printHeader( metaData, numColumns);
           printRecords( resultSet, numColumns);
		}
        else
			throw runtime_error("ResultSetMetaData FAILURE - no records in the result set");
    }
	catch (std::runtime_error &e) {
    }
    
}	

// Print the attribute names
void printHeader(sql::ResultSetMetaData *metaData, int numColumns)
{    
	/*Printing Column names*/  
    for (int i = 1; i <= numColumns; i++) {
            if (i > 1)
                cout<<",  ";
            cout<< metaData->getColumnLabel(i); //ColumnName
        }
        cout<<endl;
}		

// Print the attribute values for all tuples in the result
void printRecords(sql::ResultSet *resultSet, int numColumns)   
{ 
        while (resultSet->next()) {
            for (int i = 1; i <= numColumns; i++) {
                if (i > 1)
                    cout<<",  ";
                cout<< resultSet->getString(i);
               ;
            }
        cout<<endl;
        }
}
 
// Insert into any table, any values from data passed in as String parameters
void insert(const string table, const string values) 
{
    string query = "INSERT into " + table + " values (" + values + ")";
    statement->executeUpdate(query);
}
 

// init and  testing
// Assumes that the tables are already created
void initDatabase(const string Username, const string Password, const string SchemaName) 
{
        // Create a connection 
        con = Connect (Username, Password);
        driver = get_driver_instance();
        con = driver->connect("tcp://127.0.0.1:3306", Username, Password);

        // Connect to the MySQL test database 
        con->setSchema(SchemaName);
 
        // Create a MYSQL statement to hold queries
        statement = con->createStatement();
}
