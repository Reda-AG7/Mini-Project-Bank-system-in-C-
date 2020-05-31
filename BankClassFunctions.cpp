#include<iostream>
#include<fstream>
#include<cstdlib> //for using remove() and rename()
#include "bankClass.h"



fstream fileObject;
const char* fileName = "Bank.dat";
int size = sizeof(Account);


int numberOfRecords() {
	fileObject.open(fileName, ios::in | ios::binary);
	fileObject.seekg(0L, ios::end);
	int nbr = (fileObject.tellg() / sizeof(Account));
	fileObject.close();
	return nbr;
}

bool checkOpeningW() {
	fileObject.open(fileName, ios::app | ios::binary);
	if (fileObject.is_open())
		return true;
	return false;
}
bool checkOpeningR() {
	fileObject.open(fileName, ios::in | ios::binary);
	if (fileObject.is_open())
		return true;
	return false;
}


void Account::writeRecord() {
	cout << "Enter Account number : ";
	cin >> accountNumber;
	cout << "Enter First Name : ";
	cin >> firstName;
	cout << "Enter Last Name : ";
	cin >> lastName;
	cout << "Enter The Balance : ";
	cin >> balance;

}
void Account::readRecord() const{
	cout << "Account number : " <<accountNumber << endl;
	cout << "First Name : " << firstName << endl;
	cout << "Last Name : " << lastName << endl;
	cout << "Balance : " << balance << endl;
}


void Account::addRecord() {

	bool (*open)() = checkOpeningW; // USING A FUNCTION POINTER
	open();
	
	if (open) {
		//cout << "The file is opened successfully.\n";
		this->writeRecord();
		fileObject.write(reinterpret_cast<char*>(this), sizeof(*this));
		fileObject.close();
	}
	else
		cout << "Error in opening the file.\n";
}

void Account::searchRecord() {
	//int nbRec = numberOfRecords();
	bool open = checkOpeningR();
	int accN;
	if (open) {
		//cout << "the file is opened successfully : " << endl;
		cout << "Enter the Account Number that you are looking for : ";
		cin >> accN;

		int i = 0;
		bool found = false;
		while (!fileObject.eof() && !found) {

			fileObject.seekg((i*size), ios::beg);
			fileObject.read(reinterpret_cast<char*>(this), sizeof(*this));
			if (this->accountNumber == accN) {
				cout << "The Account Number exist : \n";
				this->readRecord();
				found = true;
			}
			i++;
		}
		fileObject.close();

	}
	else
		cout << "Error in opening the file " << endl;

}

void Account::modifyRecord() {
	int recNb;
	bool found = false;
	int i = 0;
	cout << "There are " << numberOfRecords() << " records." << endl;
	showAllRecord();
	fileObject.open(fileName, ios::binary | ios::in | ios::out);
	if (!fileObject.fail()) {

		cout << "Enter the Account Number of the record you want to modify : ";
		cin >> recNb;

		while (!fileObject.eof() && !found) {
			fileObject.seekg(i*size, ios::beg);
			fileObject.read(reinterpret_cast<char*> (this), sizeof(*this));
			if (this->accountNumber == recNb) {
				cout << "this Account number Exist in our Database : \n" << endl;
				this->readRecord();
				cout << endl;
				fileObject.seekp((i * sizeof(*this)), ios::beg);
				cout << "Enter the new Data for this Record : \n" << endl;
				this->writeRecord();
				fileObject.write(reinterpret_cast<char*> (this), sizeof(*this));
				found = true;
			}
			else i++;
		}
		fileObject.close();
	}


}

void Account::showAllRecord()  {
	int recordNb = numberOfRecords(), count = 1;
	bool open = checkOpeningR();

	if (open) {

		//cout << "The file is opened successfully.\n" << endl;

		cout << "the Number of Records is : " << recordNb << endl;
		fileObject.seekg(0L, ios::beg);
		fileObject.read(reinterpret_cast<char*>(this), sizeof(*this));
		while (!fileObject.eof()) {

			cout << "Record " << count++ << " : \n" << endl;
			this->readRecord();
			fileObject.read(reinterpret_cast<char*>(this), sizeof(*this));
			cout << endl;
		}

		fileObject.close();
	}
	else {
		fileObject.open(fileName, ios::binary | ios::out);
		cout<<"the Number of Records is : " << recordNb << endl;
		fileObject.close();
	}
		
}

void Account::deleteRecord() {
	const char* fileName2 = "Bank2.dat";
	int accNb, i = 0;
	int recNb = numberOfRecords();
	bool openr = checkOpeningR();
	fstream fileObject2;
	if (openr) {
		//cout << "the file is ready to read from." << endl;
		cout << "Enter the Account Number you want to delete : ";
		cin >> accNb;
		fileObject2.open(fileName2, ios::binary | ios::out);
		//if (fileObject2) { cout << "the file is ready to write into." << endl; }
		//else cout << "Error" << endl;
		fileObject.read(reinterpret_cast<char*>(this), sizeof(*this));
		while (i < recNb) {
			if (this->accountNumber == accNb) {
				cout << "this account is deleted" << endl;
				i++;
				continue;
			}
			else {
				fileObject2.write(reinterpret_cast<char*>(this), sizeof(*this));
				i++;
				fileObject.seekg(i*size, ios::beg);
				fileObject.read(reinterpret_cast<char*>(this), sizeof(*this));
			}
		}
		fileObject2.close();
		fileObject.close();
		remove("Bank.dat");
		rename("Bank2.dat", "Bank.dat");
	}
	else cout << "Error in opening the file." << endl;
}

void Account::resetFile() {
	remove("Bank.dat");
	fstream fileObject2;
	const char* newFileName = "Bank.dat";
	fileObject2.open(newFileName, ios::binary | ios::in);
	fileObject2.close();
}
