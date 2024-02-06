#include "DB.h"
#include <iomanip>

using namespace std;

//set the max limit
const int Id_size=5;
const int lName_size=12;
const int fName_size=16;
const int Age_size=5;
const int Ticket_size=17;
const int Fare_size=6;
const int Date_size=9;
const int recordSize = Id_size + lName_size + fName_size + Age_size + Ticket_size + Fare_size + Date_size;

// Replace Spaces with Underscores
void replaceSpaces(string &str) {
    for (int i = 0; i < str.length(); i++) {
        if (str[i] == ' ') {
            str[i] = '_';
        }
    }
}

// Replace Underscores with Spaces

void replaceUnderscores(string &str) {
    for (int i = 0; i < str.length(); i++) {
        if (str[i] == '_') {
            str[i] = ' ';
        }
    }
}





// Write a fixed length record to the file.  
void writeRecord(ofstream &Dout, const string &Id, const string lName, const string fName, const string Age, const string Ticket, const string Fare, const string Date) {
    // Write ID
    Dout << setw(Id_size) << left << Id.substr(0, Id_size);
    // Write Last Name
    Dout << setw(lName_size) << left << lName.substr(0, lName_size);
    // Write First Name
    Dout << setw(fName_size) << left << fName.substr(0, fName_size);
    // Write Age
    Dout << setw(Age_size) << left << Age.substr(0, Age_size);
    // Write Ticket
    Dout << setw(Ticket_size) << left << Ticket.substr(0, Ticket_size);
    // Write Fare
    Dout << setw(Fare_size) << left << Fare.substr(0, Fare_size);
    // Write Date
    Dout << setw(Date_size) << left << Date.substr(0, Date_size)<<endl;


    
    
}

void createDB(const string inFilename)
{
ifstream Din;   // the csv file
ofstream Dout;  // the data file
ofstream ConfigOut;  // the config file
string Id = "ID";
string lName = "LAST_NAME";
string fName = "FIRST_NAME";
string Age = "AGE";
string Ticket = "TICKET_NUM";
string Fare = "FARE";
string Date = "DATE_OF_PURCHASE";
int recordNum = 0;


   Din.open (inFilename+".csv");
   Dout.open (inFilename+".data");
   getline (Din, Id, ',');  // try to read an id
   while (!Din.eof())  
   {
      // read rest of the line
     
     getline (Din, lName, ',');
     getline (Din, fName, ',');
     getline (Din, Age, ',');
     getline (Din, Ticket, ',');
     getline (Din, Fare, ',');
     getline (Din, Date);

      // Replace spaces with underscores
      replaceSpaces(fName);
      replaceSpaces(Ticket);

      //write record
      writeRecord (Dout, Id, lName, fName, Age, Ticket, Fare, Date);
      recordNum++;

      //write an empty record
      writeRecord (Dout, "NA","NA","NA","NA","NA","NA","NA");

      getline (Din, Id, ',');  // Try to read the next line
   }
   Din.close();
   Dout.close();
   Din.open("config.data");
    ConfigOut.open("config.data");
    ConfigOut << recordNum << " " << recordSize;
    ConfigOut.close();
}
void menu(){

  cout << "1. Create Database" << endl;
  cout << "2. Open Database" << endl;
  cout << "3. Close Database" << endl;
  cout << "4. Display Record" << endl;
  cout << "5. Create Report" << endl;
  cout << "6. Update Record" << endl;
  cout << "7. Delete Record" << endl;
  cout << "8. Add Record" << endl;
  cout << "9. Exit" << endl;
  cout << "Enter Selection: ";

}




int main(int argc, char const *argv[])
{
  
  
  int x = 0;
  string filename;
  DB db; 



    while(x != 1){
        int selection;
        menu();
        while(!(cin >> selection)){
    cout << "Please enter a valid number" << endl; 
    cin.clear();
    cin.ignore(123,'\n');
        }

        switch(selection){
            case 1:
                cout << "Create Database" << endl;
                cout << "Input File Name"<< endl;
                cin >> filename;
                createDB(filename);
                break;
            case 2:
                cout << "Open Database" << endl;
                cout << "Input File Name"<< endl;
                cin >> filename;
                db.open(filename);
                break;
            case 3:
                cout << "Close Database" << endl;
                db.close();
                break;
            case 4:
                cout << "Display Record" << endl;
                break;
            case 5:
                cout << "Create Report" << endl;
                break;
            case 6:
                cout << "Update Record" << endl;
                break;
            case 7:
                cout << "Delete Record" << endl;
                break;
            case 8:
                cout << "Add Record" << endl;
                break;
            case 9:
                cout << "Exit" << endl;
                x = 1;
                break;
            default:
                cout << "Invalid Selection" << endl;
                break;
        }
  
  
  
  
    }
    return 0;
    }
  
  
  
  // string Id = "ID";
  // string Experience = "EXPERIENCE";
  // string Married = "MARRIED";
  // string Wage = "WAGE";
  // string Industry = "INDUSTRY";
  // int recordNum;


  // //creates the database with empty records
  // createDB("input");

  // // calls constructor
  // DB db;

  // // opens "input.data"
  // db.open("input.data");

  // cout << "\n------------- Testing readRecord ------------\n";

  // // Reads record 0
  // // Then prints the values of the 5 fields to the screen with the name of the
  // // field and the values read from the record, i.e.,
  // // id: 00003 experience: 3 married: no wages: 1.344461678 industry:
  // // Business_and_Repair_Service
  // recordNum = 0;
  // if (db.readRecord(recordNum, Id, Experience, Married, Wage, Industry))
  //   cout << "recordNum: " << recordNum << ", Id: " << Id
  //        << ", Experience: " << Experience << ", Married: " << Married
  //        << ", Wage: " << Wage << ", Industry:" << Industry << "\n\n";
  // else
  //   cout << "Could not get record " << recordNum << ".\n\n";

  // // Reads record 18 (last real (non-empty)record)
  // recordNum = db.NUM_RECORDS - 2;
  // if (db.readRecord(recordNum, Id, Experience, Married, Wage, Industry))
  //   cout << "recordNum: " << recordNum << ", Id: " << Id
  //        << ", Experience: " << Experience << ", Married: " << Married
  //        << ", Wage: " << Wage << ", Industry:" << Industry << "\n\n";
  // else
  //   cout << "Could not get record " << recordNum << ".\n\n";

  // // Reads record 19 (last(empty)record)
  // recordNum = 19;
  // if (db.readRecord(recordNum, Id, Experience, Married, Wage, Industry))
  //   cout << "recordNum: " << recordNum << ", Id: " << Id
  //        << ", Experience: " << Experience << ", Married: " << Married
  //        << ", Wage: " << Wage << ", Industry:" << Industry << "\n\n";
  // else
  //   cout << "Could not get record " << recordNum << ".\n\n";

  // cout << "\n------------- Testing binarySearch ------------\n";

  // // Find record with id 42 (should not be found)
  // Id = "00010";
  // cout << "Looking for Id: " << Id << endl;
  // bool found = db.binarySearch(Id,recordNum, Experience, Married, Wage, Industry);
  // if (found)
  //   cout << "recordNum: " << recordNum << ", Id: " << Id
  //        << ", Experience: " << Experience << ", Married: " << Married
  //        << ", Wage: " << Wage << ", Industry:" << Industry << "\n\n";
  // else
  //   cout << "Record " << Id << " not found."<<"Location for insert: "<<recordNum<<endl;

  // // Find record with id 00000 (the first one in the file)
  // Id = "00000";
  // cout << "Looking for Id: " << Id << endl;
  // // update the value of recordnum if found, populate the fields
  // found = db.binarySearch(Id,recordNum, Experience, Married, Wage, Industry);
  // if (found)
  //   cout << "recordNum: " << recordNum << ", Id: " << Id
  //        << ", Experience: " << Experience << ", Married: " << Married
  //        << ", Wage: " << Wage << ", Industry:" << Industry << "\n\n";
  // else
  //   cout << "Record " << Id << " not found."<<"Location for insert: "<<recordNum<<endl;

  // // Find record with id 00015 (the last one in the file)
  // Id = "00015";
  // cout << "Looking for Id: " << Id << endl;
  // found = db.binarySearch(Id,recordNum, Experience, Married, Wage, Industry);
  // if (found)
  //   cout << "recordNum: " << recordNum << ", Id: " << Id
  //        << ", Experience: " << Experience << ", Married: " << Married
  //        << ", Wage: " << Wage << ", Industry:" << Industry << "\n\n";
  // else
  //   cout << "Record " << Id << " not found."<<"Location for insert: "<<recordNum<<endl;

  // // Find record with id 00006 (somewhere in the middle)
  // Id = "000006";
  // cout << "Looking for Id: " << Id << endl;
  // found = db.binarySearch(Id,recordNum, Experience, Married, Wage, Industry);
  // if (found)
  //   cout << "recordNum: " << recordNum << ", Id: " << Id
  //        << ", Experience: " << Experience << ", Married: " << Married
  //        << ", Wage: " << Wage << ", Industry:" << Industry << "\n\n";
  // else
  //   cout << "Record " << Id << " not found."<<"Location for insert: "<<recordNum<<endl;

  // // Close database
  // db.close();




  // return 0;



