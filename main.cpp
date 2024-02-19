
#include <iostream>
#include "database.h"
using namespace std;

void printData(string id, string first_name, string last_name, string age, 
			   string ticket_num, string fare, string purchase_date)
{
	cout << "ID: " << id << " first Name: " << first_name << " Last Name: " << last_name
		 << " Age: " << age << " Ticket Num: " << ticket_num << " Fare: " << fare 
		 << " Purchase Date: " << purchase_date << endl;
}

void menu()
{
  
   cout << endl << endl
        << "1) Create new database\n"
        << "2) Open database\n"
        << "3) Close database\n"
        << "4) Read record\n"
        << "5) Display record\n"
        << "6) Update record\n"
        << "7) Create report\n"
        << "8) Add record\n"
        << "9) Delete record\n"
        << "10) Quit\n";
}

void updateMenu(){
    cout << "1) First Name\n"
         << "2) Last Name\n"
         << "3) Age\n"
         << "4) Ticket Number\n"
         << "5) Fare\n"
         << "6) Purchase Date\n";
  
  }



int main(int argc, char **argv)
{
	string id, first_name, last_name, age, ticket_num, fare, purchase_date;
	int selection = -1;
    Database db;
    string filename;
    int recordNum;
    string recordID;
    int updateSelection;
    int count = 0;
  
	
	cout << endl << "Welcome to the database part 1" << endl;
		 
    bool Done = false;
	while (!Done) {
        menu();
		cout  << "Please make your selection: ";
        cin >> selection;
        switch (selection) {
            case 1: // Create new database
                cout << "Enter database name: ";
                cin >> filename;
                if(db.createDb(filename)){
                	cout << "Database created." << endl;
                }
                break;
            case 2: // Open database
                cout << "Enter database name to open: ";
                cin >> filename;
                if(db.openDb(filename)) {
                    cout << "Database opened successfully." << endl;
                } else {
                    cout << "Failed to open database." << endl;
                }
                break;
            case 3: // Close database
                db.closeDb();
     
                break;
            case 4: // Read record
                cout << "Enter record number to display: ";
                cin >> recordNum;
                if(db.readRecord(recordNum, id, first_name, last_name, age, ticket_num, fare, purchase_date) == 1) {
                    printData(id, first_name, last_name, age, ticket_num, fare, purchase_date);
                } else {
                    cout << "Failed to read record or record does not exist." << endl;
                }
                break;
            case 5: // Display record

                cout << "Enter passenger ID to display: ";
                cin >> recordID;
                if(db.binarySearch(recordID, recordNum ,first_name, last_name, age, ticket_num, fare, purchase_date) == 1) {
                    printData(recordID, first_name, last_name, age, ticket_num, fare, purchase_date);
                } else {
                    cout << "Failed to read record or record does not exist." << endl;
                }
                
                

                break; 
            case 6: // Update record
                cout<<"Enter record number to update: ";
                cin>>recordID;
                if(db.binarySearch(recordID, recordNum ,first_name, last_name, age, ticket_num, fare, purchase_date) == 1) {
                    printData(recordID, first_name, last_name, age, ticket_num, fare, purchase_date);
                } else {
                    cout << "Failed to read record or record does not exist." << endl;
                }
                
                cout << "Which Field would you like to update?" << endl;
                updateMenu();
                cin >> updateSelection;
                
                switch(updateSelection){
                    case 1: 
                        cout <<"Enter new First Name: ";
                        cin >> first_name;
                        db.updateRecord(recordID, recordNum, first_name, last_name, age, ticket_num, fare, purchase_date);
                        break;
                    case 2:
                        cout <<"Enter new Last Name: ";
                        cin >> last_name;
                        db.updateRecord(recordID, recordNum, first_name, last_name, age, ticket_num, fare, purchase_date);
                        break;
                    case 3:
                        cout <<"Enter new Age: ";
                        cin >> age;
                        db.updateRecord(recordID, recordNum, first_name, last_name, age, ticket_num, fare, purchase_date);
                        break;
                    case 4:
                        cout <<"Enter new Ticket Number: ";
                        cin >> ticket_num;
                        db.updateRecord(recordID, recordNum, first_name, last_name, age, ticket_num, fare, purchase_date);
                        break;
                    case 5:
                        cout <<"Enter new Fare: ";
                        cin >> fare;
                        db.updateRecord(recordID, recordNum, first_name, last_name, age, ticket_num, fare, purchase_date);
                        break;
                    case 6:
                        cout <<"Enter new Purchase Date: ";
                        cin >> purchase_date;
                        db.updateRecord(recordID, recordNum, first_name, last_name, age, ticket_num, fare, purchase_date);
                        break;
                    default:
                        cout << "Invalid selection, please try again." << endl;
                        break;
                }


            
                break;
            case 7: // Create report
                count = 0;
                    for (recordNum = 0; count < 10; recordNum++)
                    {
                        if (db.readRecord(recordNum, id, first_name, last_name, age, ticket_num, fare, purchase_date) == 1)
                        {
                            if (id != "_empty_")
                            {
                                printData(id, first_name, last_name, age, ticket_num, fare, purchase_date);
                                count++;
                            }
                        }
                        else
                        {
                            cout << "Failed to read record or record does not exist." << endl;
                            break;
                        }
                    }
                    break;

            case 8: // Add record
                // Gather input from the user and use writeRecord or another method to add
                break;
            case 9: // Delete record
                cout<<"Enter record number to delete: ";
                cin>>recordID;
                if(db.binarySearch(recordID, recordNum ,first_name, last_name, age, ticket_num, fare, purchase_date) == 1) {
                    printData(recordID, first_name, last_name, age, ticket_num, fare, purchase_date);
                } else {
                    cout << "Failed to read record or record does not exist." << endl;
                }
                // Implementation depends on how the Database class handles deletion
                db.updateRecord("_empty_", recordNum, "None", "None", "None", "None", "None","None");

                break;
            case 10: // Quit
                if (!db.isOpen())
                {
                   cout << "Exiting program." << endl;
                   Done = true;
                }
                else
                   cout << "Please close the database before exiting." << endl;
                break;
            default:
                cout << "Invalid selection, please try again." << endl;
                break;
        }
    }

    return 0;

}

