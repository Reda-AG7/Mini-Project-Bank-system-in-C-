#ifndef MY_BANK_CLASS
#define MY_BANK_CLASS
#include<fstream>
const int nameSize = 20;

using std::cout;
using std::cin;
using std::endl;
using std::ios;
using std::fstream;

class Account
{
private:
	char firstName[nameSize];
	char lastName[nameSize];
	int accountNumber;
	double balance;

public:

	void writeRecord();
	void readRecord() const;
	void addRecord();
	void searchRecord();
	void deleteRecord();
	void modifyRecord();
	void showAllRecord();
	void resetFile();
};


#endif
