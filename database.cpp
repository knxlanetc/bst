//--------------------------------------------------------------------
//
//  Laboratory 9, ProgrammingExercise 1                    database.cpp
//
//--------------------------------------------------------------------

#include <iostream>
#include <fstream>
#include "BSTree.cpp"

using namespace std;


const int nameLength      = 11;   // Maximum number of characters in a name
const long bytesPerRecord = 37;   // Number of bytes used to store each record in the accounts database file

// struct that holds account information
struct AccountRecord
{
    int acctID;                   // Account identifier
    char firstName[nameLength],   // Name of account holder
         lastName[nameLength];
    double balance;               // Account balance
};

// struct that holds na entry in the database index
struct IndexEntry
{
    int acctID;              // (Key) Account identifier
    long recNum;             // Record number

    int getKey () const
        { return acctID; }   // Return key field
};



int main ()
{
    ifstream acctFile ("accounts.dat");   // Accounts database file
    AccountRecord acctRec;                // Account record
    BSTree<IndexEntry,int> index;	      // Database index   // <---------------------- add a line of code here
    IndexEntry entry;                     // Index entry
    int searchID;                         // User input account ID
    long recNum;                          // Record number

	
    // Iterate through the database records. For each record, read the
    // account ID and add the (account ID, record number) pair to the index
    recNum = 0;
    while ( acctFile >> entry.acctID ) // puts the account ID into the entry
    {
        entry.recNum = recNum; 
        recNum++;  
		index.insert(entry);
		cout<<entry.acctID<<" ";// <-------------------------------------------------------------- add a line of code here
        acctFile.seekg(recNum*bytesPerRecord); // go to beginning of the line that contains the recNum record
    }

	
    // Output the account IDs in ascending order.
    cout << endl << "Account IDs : " << endl;
    index.writeKeys();     // <--------------------------------------------------------------- add a line of code here
//index.showStructure();
	
    // Clear the status flags for the database file.
    acctFile.clear();

	
    // Read an account ID from the keyboard and output the
    // corresponding record.
    cout << endl << "Enter account ID : ";
    while (cin >> searchID) {
        if (     index.retrieve(searchID, entry)   ) {  // <---------------------------------------------------- fill in the if condition here
            acctFile.seekg(entry.recNum*bytesPerRecord); // go to the beginning of the line that corresponds with the recNum record
            acctFile >> acctRec.acctID >> acctRec.firstName
                     >> acctRec.lastName >> acctRec.balance;
            cout << entry.recNum << " : " << acctRec.acctID << " "
                 << acctRec.firstName << " " << acctRec.lastName << " "
                 << acctRec.balance << endl;
         } else {
             cout << "No record with that account ID" << endl;
	 }

	 cout << "Enter account ID (EOF to quit): ";
    }

    cout << endl;
    return 0;
}
