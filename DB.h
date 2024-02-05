//-----------------------------------------------------
// Example code to read from fixed length records (random access file
// Author:  Susan Gauch
// Last updated:  Jan. 20, 2022
//-----------------------------------------------------

#include <iostream>
#include <fstream>

using namespace std;

class DB
{
private:
  std::fstream Din;
  int num_records;



public:
  //const static int RECORD_SIZE = 72;  // Windows record size
  const static int RECORD_SIZE = 71;    // linux record size
  const static int NUM_RECORDS = 20;

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
  bool readRecord(const int RecordNum,
                  string &Id, string &Experience, string &Married, string &Wage, string &Industry);

  /**
   * Binary Search by record id
   * 
   * @param id
   * @return Record number (which can then be used by read to
   *         get the fields) or -1 if id not found
   */
  bool binarySearch(const string Id,int &recordNum,
                   string &Experience, string &Married, string &Wage, string &Industry);
  
  int findNearestNonEmpty(int start, int lowLimit, int highLimit);
};
