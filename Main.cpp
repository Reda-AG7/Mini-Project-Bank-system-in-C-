#include<iostream>
#include<fstream>
#include "bankClass.h"


int main() {
	Account A;
	char again;
	int choice;

	do {
		cout << "***** Account Information System **************" << endl;
		cout << "Select one option : " << endl;
		cout << "\t\t1) Add a Record        :" << endl;
		cout << "\t\t2) Search for a Record :" << endl;
		cout << "\t\t3) Modify a Record     :" << endl;
		cout << "\t\t4) Show All the Records:" << endl;
		cout << "\t\t5) Delete a Records    :" << endl;
		cout << "\t\t6) Reset the File      :" << endl;
		cout << "\t\t7) Quit the Program    :\n" << endl;
		cout << "Select your choice : ";
		cin >> choice;
		switch (choice) {
		case 1: A.addRecord();    break;
		case 2: A.searchRecord(); break;
		case 3: A.modifyRecord(); break;
		case 4: A.showAllRecord(); break;
		case 5: A.deleteRecord(); break;
		case 6: A.resetFile();    break;
		case 7: {cout << "Thank you for your visit." << endl;
			return 0; } break;
		default: cout << "The Number you have entered does not exist.";
		}
		cout << "Do you want to do another task ? press 'y' or 'n' : ";
		cin >> again;
	} while (again == 'y' || again == 'Y');



	cin.get();
}