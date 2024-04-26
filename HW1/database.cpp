#include <iomanip>
#include <iostream>
#include <algorithm>
#include "database.h"
using namespace std;

Database::Database()
{
	num_records = -1;
    record_size = -1;
}

Database::~Database()
{
}

bool Database::createDb(const string filename)
{
	/////////////////////////////////////possible strings might need to be set to an initial value
	string id, first_name, last_name, age, ticket_num, fare, purchase_date;

    // open csv file for reading
    f_csv.open(filename+".csv");
	if (!f_csv){
		cerr << "Failed to open csv file" << endl;
		return false;
    }

    // open data file for writing
	f_db.open(filename+".data", f_db.out);
    if (!f_db)
    {
		cerr << "Failed to open data file" << endl;
		return false;
    }

    // files are open
    num_records = 0;
	while(readCsv(id, first_name, last_name, age, ticket_num, fare, purchase_date))
	{
		writeRecord(id, first_name, last_name, age, ticket_num, fare, purchase_date);
        num_records++;
		writeRecord("_empty_", "None", "None", "None", "None", "None", "None");
        num_records++;
	}
	
	f_csv.close();
	f_db.close();
	
	//config file section
	ofstream f_cfg;
	f_cfg.open(filename+".config");
	if (!f_cfg)
		cerr << "Failed to create configuration file." << endl;
	else
	{
		f_cfg << num_records << " " << RECORD_SIZE << endl;
	}
	f_cfg.close();
	return true;
}

bool Database::openDb(const string filename)
{
bool Success = false;

    if (isOpen())
       cout << "There is a database open already.   Please close that first." << endl;
    else
    {
	   //read config file and set values
	   ifstream f_cfg;
   	
	   f_db.open(filename+".data");
	   f_cfg.open(filename+".config");
   	
	   if (!f_cfg || !f_db)
		   cerr << "Failed to open configuration file, openDb." << endl;
	   else
	   {
		  f_cfg >> num_records >> record_size;
	      f_cfg.close();
	      Success = true;
	   }
    }
    return Success;
}

void Database::closeDb()
{
	//does not say to update the config file here, might be a good idea to add it in
	if (isOpen()){
		f_db.close();
		num_records = -1;
		cout << "Database closed." << endl;
	}
	else{
		cout << "No database is open." << endl;
	}
}

bool Database::readCsv(string &id, string &firstName, string &lastName, string &age, string &ticketNum, string &fare, string &purchaseDate)
{
	if(getline(f_csv, id, ','))
	{
		getline(f_csv, firstName, ',');
		getline(f_csv, lastName, ',');
		getline(f_csv, age, ',');
		getline(f_csv, ticketNum, ',');
		getline(f_csv, fare, ',');
		getline(f_csv, purchaseDate);
		return true;
	}
	else
		return false;
}

void Database::writeRecord(string id, string first_name, string last_name, string age, 
						   string ticket_num, string fare, string purchase_date)
{

    // replace spaces with _
    replace(first_name.begin(), first_name.end(), ' ', '_');
    replace(last_name.begin(), last_name.end(), ' ', '_');
    replace(ticket_num.begin(), ticket_num.end(), ' ', '_');

	//do formatted writes
	f_db << setw(ID_SIZE) << left << id.substr(0, ID_SIZE) << " " 
         << setw(FIRST_SIZE) << left << first_name.substr(0, FIRST_SIZE) << " " 
         << setw(LAST_SIZE) << left << last_name.substr(0, LAST_SIZE) << " " 
         << setw(AGE_SIZE) << left << age.substr(0, AGE_SIZE) << " " 
         << setw(TICKET_NUM_SIZE) << left << ticket_num.substr(0, TICKET_NUM_SIZE) << " " 
         << setw(FARE_SIZE) << left << fare.substr(0, FARE_SIZE) << " " 
         << setw(DATE_SIZE) << left << purchase_date.substr(0, DATE_SIZE) << endl;
}


bool Database::readRecord(const int record_num, string &id, string &first_name, string &last_name, 
						 string &age, string &ticket_num, string &fare, string &purchase_date)
{
bool Success = false;

	if (!isOpen())
		cout <<"No Database open" << endl;
	else if ((record_num < 0) || (record_num >= num_records))
		cout << "value is out of range" << endl << endl;
    else
    {
	   f_db.seekg(((record_num) * record_size), ios::beg);
       f_db >> id >> first_name >> last_name >> age >> ticket_num >> fare >> purchase_date;
       Success = true;
    }
		
	return Success;
}

bool Database::updateRecord(const string Id,int RecordNum ,string FIRST_NAME, string LAST_NAME, string AGE, string TICKET_NUM, string FARE, string DATE_OF_PURCHASE){
    

// First, use binarySearch to find the record by ID

bool Success = false;

if (!isOpen())
cout <<"No Database open" << endl;
else if ((RecordNum < 0) || (RecordNum >= num_records))
cout << "value is out of range" << endl << endl;
else
{
// Write the updated record to the file
f_db.seekg(((RecordNum) * record_size), ios::beg);
f_db << setw(ID_SIZE) << left << Id.substr(0, ID_SIZE) << " " 
<< setw(FIRST_SIZE) << left << FIRST_NAME.substr(0, FIRST_SIZE) << " " 
<< setw(LAST_SIZE) << left << LAST_NAME.substr(0, LAST_SIZE) << " " 
<< setw(AGE_SIZE) << left << AGE.substr(0, AGE_SIZE) << " " 
<< setw(TICKET_NUM_SIZE) << left << TICKET_NUM.substr(0, TICKET_NUM_SIZE) << " " 
<< setw(FARE_SIZE) << left << FARE.substr(0, FARE_SIZE) << " " 
<< setw(DATE_SIZE) << left << DATE_OF_PURCHASE.substr(0, DATE_SIZE) << endl;


// Optionally, print the updated record
cout << "Updated Record:" << endl;
cout << "ID: " << Id << ", First Name: " << FIRST_NAME << ", Last Name: " << LAST_NAME
<< ", Age: " << AGE << ", Ticket Number: " << TICKET_NUM << ", Fare: " << FARE
<< ", Purchase Date: " << DATE_OF_PURCHASE << endl;

Success = true;
}
return Success;

    
}
 
bool Database::isOpen()
{
   return f_db.is_open();
} 

bool Database::binarySearch(const string Id,int &RecordNum ,string &FIRST_NAME, string &LAST_NAME, string &AGE, string &TICKET_NUM, string &FARE, string &DATE_OF_PURCHASE)
{
    // Initialize low and high indices for binary search
    int Low = 0;
    int High = num_records - 1;
    bool Found = false;

    while (!Found && High >= Low)
    {
        // Calculate middle index for current search range
        int Middle = (Low + High) / 2;
        string MiddleId;

        // Update RecordNum to current middle index
        RecordNum = Middle;

        // Read record at middle index
        if (!readRecord(Middle,MiddleId,FIRST_NAME, LAST_NAME, AGE, TICKET_NUM, FARE, DATE_OF_PURCHASE)) {
            //cout << "RecordNum" << RecordNum << endl;
            return false; // Return false if reading record fails
        }

        // Check if the current record is empty
        if (MiddleId == "_empty_") {
            // Find the nearest non-empty record from current middle
            int nonEmptyRecord = findNearestNonEmpty(Middle, Low , High);
            if (nonEmptyRecord == -1) {
                // Return false if no non-empty record is found
                return false; 
            }

            // Update Middle to index of nearest non-empty record
            Middle = nonEmptyRecord;
            //cout << "RecordNum" << RecordNum << endl;
            if (!readRecord(Middle,MiddleId,FIRST_NAME, LAST_NAME, AGE, TICKET_NUM, FARE, DATE_OF_PURCHASE)) {
                return false; // Return false if reading record fails
            }
            //correct  the record num for nearest space to insert
            if (stoi(MiddleId)>stoi(Id)){
                RecordNum=Middle-1;
            }
            else{
                RecordNum=Middle+1;
            }
        }

        // Convert string IDs to integers and compare
        try {
            int middleIdInt = stoi(MiddleId);
            int targetIdInt = stoi(Id);

            // Check if the target ID is found
            if (middleIdInt == targetIdInt) {
                Found = true;
                RecordNum = Middle; // Store the found record number
            } else if (middleIdInt < targetIdInt) {
                Low = Middle + 1; // Narrow the search range to upper half
            } else {
                High = Middle - 1; // Narrow the search range to lower half
            }
        } catch (const std::invalid_argument&) {
            // Handle invalid or empty records
            High = Middle - 1; // Update the high index
        }
    }

    if (Found)
        return true; // Return true if ID is found
    else {
        cout << "Could not get record " << Id << endl;
        return false; // Return false if ID is not found
    }
}

int Database::findNearestNonEmpty(int start, int lowLimit, int highLimit) {
    // Initialize steps for backward and forward search
    int backStep = 1;
    int forwardStep = 1;

    while (true) {
        // Search for non-empty record in backward direction
        if (start - backStep >= lowLimit) {
            string RecordNum, FIRST_NAME, LAST_NAME, AGE, TICKET_NUM, FARE, DATE_OF_PURCHASE, PASSENGER_ID;
            if (readRecord(start - backStep, PASSENGER_ID, FIRST_NAME, LAST_NAME, AGE, TICKET_NUM, FARE, DATE_OF_PURCHASE) && PASSENGER_ID != "_empty_") {
                return start - backStep; // Return index of non-empty record
            }
            backStep += 1; // Increase step for backward search
        }

        // Search for non-empty record in forward direction
        if (start + forwardStep <= highLimit) {
            string RecordNum, FIRST_NAME, LAST_NAME, AGE, TICKET_NUM, FARE, DATE_OF_PURCHASE, PASSENGER_ID;
            if (readRecord(start + forwardStep, PASSENGER_ID, FIRST_NAME, LAST_NAME, AGE, TICKET_NUM, FARE, DATE_OF_PURCHASE) && PASSENGER_ID != "_empty_") {
                return start + forwardStep; // Return index of non-empty record
            }
            forwardStep += 1; // Increase step for forward search
        }

        // Terminate the search if limits are reached
        if (start - backStep < lowLimit && start + forwardStep > highLimit) {
            break;
        }
    }
    return -1; // Return -1 if no non-empty record is found
}

bool Database::MAX_RECORDS(const int recordNum){
    
    if(!isOpen()){
        cout << "No database is open." << endl;
        return false;
    } 
    
    if ((recordNum>=num_records)|| (recordNum < 0)){
        return true;
    }
    else{
        return false;
    }
}




