#include "DB.h"
#include <iomanip>

using namespace std;

//set the max limit
const int Id_size=10;
const int Experience_size=5;
const int Married_size=5;
const int Wage_size=20;
const int Industry_size=30;



// Write a fixed length record to the file.  
void writeRecord(ofstream &Dout, const string &Id, const string &Experience, 
                 const string &Married, const string &Wage, const string &Industry) {
    // Write ID
    Dout << setw(Id_size) << left << Id.substr(0, Id_size);
    
    // Write Experience
    Dout << setw(Experience_size) << left << Experience.substr(0, Experience_size);
    
    // Write Married
    Dout << setw(Married_size) << left << Married.substr(0, Married_size);
    
    // Write Wage
    Dout << setw(Wage_size) << left << Wage.substr(0, Wage_size);
    
    // Write Industry
    Dout << setw(Industry_size) << left << Industry.substr(0, Industry_size) << endl;

}

void createDB(const string inFilename)
{
ifstream Din;   // the csv file
ofstream Dout;  // the data file
ofstream ConfigOut;  // the config file
string Id = "ID";
string Experience = "EXPERIENCE";
string Married = "MARRIED";
string Wage = "WAGE";
string Industry = "INDUSTRY";

   Din.open (inFilename+".csv");
   Dout.open (inFilename+".data");
   getline (Din, Id, ',');  // try to read an id
   while (!Din.eof())  
   {
      // read rest of the line
      getline (Din, Experience, ',');  
      getline (Din, Married, ',');  
      getline (Din, Wage, ',');  
      getline (Din, Industry);   // this one is terminated with \n


      //write record
      writeRecord (Dout, Id, Experience, Married, Wage, Industry);

      //write an empty record
      writeRecord (Dout, "_empty_", "None", "None", "None", "None");

      getline (Din, Id, ',');  // Try to read the next line
   }
   Din.close();
   Dout.close();
}
void menu(){

    cout<<"1. Load"<<endl;
    cout<<"2. Search"<<endl;
    cout<<"3. Insert"<<endl;
    cout<<"4. Delete"<<endl;
    cout<<"5. Print"<<endl;
    cout<<"6. Exit"<<endl;

}




int main(int argc, char const *argv[])
{
  string Id = "ID";
  string Experience = "EXPERIENCE";
  string Married = "MARRIED";
  string Wage = "WAGE";
  string Industry = "INDUSTRY";
  int recordNum;


  //creates the database with empty records
  createDB("input");

  // calls constructor
  DB db;

  // opens "input.data"
  db.open("input.data");

  cout << "\n------------- Testing readRecord ------------\n";

  // Reads record 0
  // Then prints the values of the 5 fields to the screen with the name of the
  // field and the values read from the record, i.e.,
  // id: 00003 experience: 3 married: no wages: 1.344461678 industry:
  // Business_and_Repair_Service
  recordNum = 0;
  if (db.readRecord(recordNum, Id, Experience, Married, Wage, Industry))
    cout << "recordNum: " << recordNum << ", Id: " << Id
         << ", Experience: " << Experience << ", Married: " << Married
         << ", Wage: " << Wage << ", Industry:" << Industry << "\n\n";
  else
    cout << "Could not get record " << recordNum << ".\n\n";

  // Reads record 18 (last real (non-empty)record)
  recordNum = db.NUM_RECORDS - 2;
  if (db.readRecord(recordNum, Id, Experience, Married, Wage, Industry))
    cout << "recordNum: " << recordNum << ", Id: " << Id
         << ", Experience: " << Experience << ", Married: " << Married
         << ", Wage: " << Wage << ", Industry:" << Industry << "\n\n";
  else
    cout << "Could not get record " << recordNum << ".\n\n";

  // Reads record 19 (last(empty)record)
  recordNum = 19;
  if (db.readRecord(recordNum, Id, Experience, Married, Wage, Industry))
    cout << "recordNum: " << recordNum << ", Id: " << Id
         << ", Experience: " << Experience << ", Married: " << Married
         << ", Wage: " << Wage << ", Industry:" << Industry << "\n\n";
  else
    cout << "Could not get record " << recordNum << ".\n\n";

  cout << "\n------------- Testing binarySearch ------------\n";

  // Find record with id 42 (should not be found)
  Id = "00010";
  cout << "Looking for Id: " << Id << endl;
  bool found = db.binarySearch(Id,recordNum, Experience, Married, Wage, Industry);
  if (found)
    cout << "recordNum: " << recordNum << ", Id: " << Id
         << ", Experience: " << Experience << ", Married: " << Married
         << ", Wage: " << Wage << ", Industry:" << Industry << "\n\n";
  else
    cout << "Record " << Id << " not found."<<"Location for insert: "<<recordNum<<endl;

  // Find record with id 00000 (the first one in the file)
  Id = "00000";
  cout << "Looking for Id: " << Id << endl;
  // update the value of recordnum if found, populate the fields
  found = db.binarySearch(Id,recordNum, Experience, Married, Wage, Industry);
  if (found)
    cout << "recordNum: " << recordNum << ", Id: " << Id
         << ", Experience: " << Experience << ", Married: " << Married
         << ", Wage: " << Wage << ", Industry:" << Industry << "\n\n";
  else
    cout << "Record " << Id << " not found."<<"Location for insert: "<<recordNum<<endl;

  // Find record with id 00015 (the last one in the file)
  Id = "00015";
  cout << "Looking for Id: " << Id << endl;
  found = db.binarySearch(Id,recordNum, Experience, Married, Wage, Industry);
  if (found)
    cout << "recordNum: " << recordNum << ", Id: " << Id
         << ", Experience: " << Experience << ", Married: " << Married
         << ", Wage: " << Wage << ", Industry:" << Industry << "\n\n";
  else
    cout << "Record " << Id << " not found."<<"Location for insert: "<<recordNum<<endl;

  // Find record with id 00006 (somewhere in the middle)
  Id = "000006";
  cout << "Looking for Id: " << Id << endl;
  found = db.binarySearch(Id,recordNum, Experience, Married, Wage, Industry);
  if (found)
    cout << "recordNum: " << recordNum << ", Id: " << Id
         << ", Experience: " << Experience << ", Married: " << Married
         << ", Wage: " << Wage << ", Industry:" << Industry << "\n\n";
  else
    cout << "Record " << Id << " not found."<<"Location for insert: "<<recordNum<<endl;

  // Close database
  db.close();




  return 0;


}
