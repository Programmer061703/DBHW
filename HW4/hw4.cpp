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
void findMenuItemsByRestaurantAndCity(const string& restaurantName, const string& city);
void menu();
int x = 0;
 

int main() 
{
 
    string Username = "brw020";             // Change to your own username
    string mysqlPassword = "ar6Phis7";   // Change to your own mysql password

    initDatabase(Username, mysqlPassword, Username); //init and testing - use it to enter your queries

    while (x != 1) {
        menu();
        while(!(cin >> selection)){
        cout << "Please enter a valid number" << endl; 
        cin.clear();
        cin.ignore(123,'\n');
        }
        switch (selection) {
            case 1: {
                string restaurantName, city;
                cout << "Enter restaurant name: ";
                cin >> restaurantName;
                cout << "Enter city: ";
                cin >> city;
                findMenuItemsByRestaurantAndCity(restaurantName, city);
                break;
            }
            case 2: {
                // Order an available menu item from a particular restaurant
                break;
            }
            case 3: {
                // List all food orders for a particular restaurant
                break;
            }
            case 4: {
                // Cancel a food order
                break;
            }
            case 5: {
                // Add a new dish for a restaurant
                break;
            }
            case 6: {
                x = 1;
                break;
            }
            default: {
                cout << "Invalid choice. Please try again." << endl;
                break;
            }
        }
    }
        

    disconnect();   
}   

void menu(){
    coud <<endl <<
        "1) Find menu items for a restaurant"
        "2) Order an available menu item from a particular restaurant"
        "3) List all food orders for a particular restaurant"
        "4) Cancel a food order"
        "5) Add a new dish for a restaurant"
        "6) Quit"
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

void findMenuItemsByRestaurantAndCity(const string& restaurantName, const string& city) {
    string q = "SELECT MI.itemNo, D.dishName, MI.price "
               "FROM MenuItem MI "
               "JOIN Dish D ON MI.dishNo = D.dishNo "
               "JOIN Restaurant R ON MI.restaurantNo = R.restaurantID "
               "WHERE R.restaurantName = '" + restaurantName + "' AND R.city = '" + city + "'";
    query(q);
}





