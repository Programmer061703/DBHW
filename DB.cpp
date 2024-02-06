//-----------------------------------------------------
// Example code to read from fixed length records (random access file
// Author:  Susan Gauch
// Last updated:  Jan. 20, 2022
//-----------------------------------------------------

//FORMAT OF THE DATA FILE
//PASSENGER_ID,FIRST_NAME,LAST_NAME,AGE,TICKET_NUM,FARE,DATE_OF_PURCHASE

#include "DB.h"

DB::DB()
{
  num_records = 0;
}

DB::~DB() {}

/**
   * Opens the file in read/write mode
   * 
   * @param filename (e.g., input.data)
   * @return status true if operation successful
   */
void DB::open(string filename)
{
  // Set the number of records
  num_records = NUM_RECORDS;

  // Open file in read/write mode
  if (openStatus == true)
  {
    cout << "File is already open. Close before trying again.\n";
  }
  else
  { Din.open(filename.c_str(), fstream::in | fstream::out | fstream::app);
     openStatus = true; }
}

void DB::close()
{
  Din.close();
    openStatus = false;
}

/**
   * Get record number n (Records numbered from 0 to NUM_RECORDS-1)
   * 
   * @param record_num
   * @return values of the fields with the name of the field and
   *         the values read from the record
   */
bool DB::readRecord(const int RecordNum, string PASSENGER_ID, string &FIRST_NAME, string &LAST_NAME, string &AGE, string &TICKET_NUM, string &FARE, string &DATE_OF_PURCHASE)
{
  bool status = false;

  if ((0 <= RecordNum) && (RecordNum < NUM_RECORDS))
  {
    Din.seekg(RecordNum * RECORD_SIZE, ios::beg);
    Din >> PASSENGER_ID >> FIRST_NAME >> LAST_NAME >> AGE >> TICKET_NUM >> FARE >> DATE_OF_PURCHASE;
    status = true;
  }
  else
    cout << "Record " << PASSENGER_ID << " out of range.\n";

  return status;
}

/**
   * Binary Search by id with possible empty records
   * returns true if the id is found, false otherwise
   * sets RecordNum to the record number of the id (if found)
   * else, sets RecordNum to the RecordNumber of record after where the id was expected
   * @param id
   */
bool DB::binarySearch(const string Id,int &RecordNum, string PASSENGER_ID, string &FIRST_NAME, string &LAST_NAME, string &AGE, string &TICKET_NUM, string &FARE, string &DATE_OF_PURCHASE)
{
    // Initialize low and high indices for binary search
    int Low = 0;
    int High = NUM_RECORDS - 1;
    bool Found = false;

    while (!Found && High >= Low)
    {
        // Calculate middle index for current search range
        int Middle = (Low + High) / 2;
        string MiddleId;

        // Update RecordNum to current middle index
        RecordNum = Middle;

        // Read record at middle index
        if (!readRecord(RecordNum, PASSENGER_ID, FIRST_NAME, LAST_NAME, AGE, TICKET_NUM, FARE, DATE_OF_PURCHASE)) {
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
            if (!readRecord(RecordNum, PASSENGER_ID, FIRST_NAME, LAST_NAME, AGE, TICKET_NUM, FARE, DATE_OF_PURCHASE)) {
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

int DB::findNearestNonEmpty(int start, int lowLimit, int highLimit) {
    // Initialize steps for backward and forward search
    int backStep = 1;
    int forwardStep = 1;

    while (true) {
        // Search for non-empty record in backward direction
        if (start - backStep >= lowLimit) {
            string RecordNum, FIRST_NAME, LAST_NAME, AGE, TICKET_NUM, FARE, DATE_OF_PURCHASE, PASSENGER_ID;
            if (readRecord(start - backStep, PASSENGER_ID, FIRST_NAME, LAST_NAME, AGE, TICKET_NUM, FARE, DATE_OF_PURCHASE) && PASSENGER_ID != NULL) {
                return start - backStep; // Return index of non-empty record
            }
            backStep += 1; // Increase step for backward search
        }

        // Search for non-empty record in forward direction
        if (start + forwardStep <= highLimit) {
            string RecordNum, FIRST_NAME, LAST_NAME, AGE, TICKET_NUM, FARE, DATE_OF_PURCHASE, PASSENGER_ID;
            if (readRecord(start + forwardStep, PASSENGER_ID, FIRST_NAME, LAST_NAME, AGE, TICKET_NUM, FARE, DATE_OF_PURCHASE) && PASSENGER_ID != NULL) {
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
