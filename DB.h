//-----------------------------------------------------
// Example code to read from fixed length records (random access file
// Author:  Susan Gauch
// Last updated:  Jan. 20, 2022
//-----------------------------------------------------

#include <iostream>
#include <fstream>
#include <string>

using namespace std;


//FORMAT OF THE DATA FILE
//PASSENGER_ID,FIRST_NAME,LAST_NAME,AGE,TICKET_NUM,FARE,DATE_OF_PURCHASE

class DB
{
private:
  std::fstream Din;
  int num_records;



public:
  //const static int RECORD_SIZE = 72;  // Windows record size
  const static int RECORD_SIZE = 71;    // linux record size
  const static int NUM_RECORDS = 20;
  bool openStatus = false;

  DB();
  ~DB();

  /**
   * Opens the file in read/write mode
   * 
   * @param filename (e.g., input.data)
   * @return status true if operation successful
   */
  void open(string filename);

  /**
   * Close the database file
   */
  void close();

  /**
   * Get record number n (Records numbered from 0 to NUM_RECORDS-1)
   * 
   * @param record_num
   * @return values of the fields with the name of the field and
   *         the values read from the record
   */
  bool readRecord(const int RecordNum, string PASSENGER_ID, string &FIRST_NAME, string &LAST_NAME, string &AGE, string &TICKET_NUM, string &FARE, string &DATE_OF_PURCHASE);

  /**
   * Binary Search by record id
   * 
   * @param id
   * @return Record number (which can then be used by read to
   *         get the fields) or -1 if id not found
   */
  bool binarySearch(const string Id,int &recordNum,
                   string PASSENGER_ID, string &FIRST_NAME, string &LAST_NAME, string &AGE, string &TICKET_NUM, string &FARE, string &DATE_OF_PURCHASE);

  
  int findNearestNonEmpty(int start, int lowLimit, int highLimit);

  
};
