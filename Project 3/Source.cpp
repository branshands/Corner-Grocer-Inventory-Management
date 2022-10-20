// 7-1 Project Three
// Brandon Shands
// CS 210

#include <Python.h>
#include <iostream>
#include <Windows.h>
#include <cmath>
#include <string>
#include <fstream>
#include <vector>
#include <iomanip>

using namespace std;

// For changing text color
HANDLE color = GetStdHandle(STD_OUTPUT_HANDLE);

/*
Description:
	To call this function, simply pass the function name in Python that you wish to call.
Example:
	callProcedure("printsomething");
Output:
	Python will print on the screen: Hello from python!
Return:
	None
*/
void CallProcedure(string pName)
{
	char* procname = new char[pName.length() + 1];
	std::strcpy(procname, pName.c_str());

	Py_Initialize();
	PyObject* my_module = PyImport_ImportModule("PythonCode");
	PyErr_Print();
	PyObject* my_function = PyObject_GetAttrString(my_module, procname);
	PyObject* my_result = PyObject_CallObject(my_function, NULL);
	Py_Finalize();

	delete[] procname;
}

/*
Description:
	To call this function, pass the name of the Python functino you wish to call and the string parameter you want to send
Example:
	int x = callIntFunc("PrintMe","Test");
Output:
	Python will print on the screen:
		You sent me: Test
Return:
	100 is returned to the C++
*/
int callIntFunc(string proc, string param)
{
	char* procname = new char[proc.length() + 1];
	std::strcpy(procname, proc.c_str());

	char* paramval = new char[param.length() + 1];
	std::strcpy(paramval, param.c_str());


	PyObject* pName, * pModule, * pDict, * pFunc, * pValue = nullptr, * presult = nullptr;
	// Initialize the Python Interpreter
	Py_Initialize();
	// Build the name object
	pName = PyUnicode_FromString((char*)"PythonCode");
	// Load the module object
	pModule = PyImport_Import(pName);
	// pDict is a borrowed reference 
	pDict = PyModule_GetDict(pModule);
	// pFunc is also a borrowed reference 
	pFunc = PyDict_GetItemString(pDict, procname);
	if (PyCallable_Check(pFunc))
	{
		pValue = Py_BuildValue("(z)", paramval);
		PyErr_Print();
		presult = PyObject_CallObject(pFunc, pValue);
		PyErr_Print();
	}
	else
	{
		PyErr_Print();
	}
	//printf("Result is %d\n", _PyLong_AsInt(presult));
	Py_DECREF(pValue);
	// Clean up
	Py_DECREF(pModule);
	Py_DECREF(pName);
	// Finish the Python Interpreter
	Py_Finalize();

	// clean 
	delete[] procname;
	delete[] paramval;


	return _PyLong_AsInt(presult);
}

/*
Description:
	To call this function, pass the name of the Python functino you wish to call and the string parameter you want to send
Example:
	int x = callIntFunc("doublevalue",5);
Return:
	25 is returned to the C++
*/
int callIntFunc(string proc, int param)
{
	char* procname = new char[proc.length() + 1];
	std::strcpy(procname, proc.c_str());

	PyObject* pName, * pModule, * pDict, * pFunc, * pValue = nullptr, * presult = nullptr;
	// Initialize the Python Interpreter
	Py_Initialize();
	// Build the name object
	pName = PyUnicode_FromString((char*)"PythonCode");
	// Load the module object
	pModule = PyImport_Import(pName);
	// pDict is a borrowed reference 
	pDict = PyModule_GetDict(pModule);
	// pFunc is also a borrowed reference 
	pFunc = PyDict_GetItemString(pDict, procname);
	if (PyCallable_Check(pFunc))
	{
		pValue = Py_BuildValue("(i)", param);
		PyErr_Print();
		presult = PyObject_CallObject(pFunc, pValue);
		PyErr_Print();
	}
	else
	{
		PyErr_Print();
	}
	//printf("Result is %d\n", _PyLong_AsInt(presult));
	Py_DECREF(pValue);
	// Clean up
	Py_DECREF(pModule);
	Py_DECREF(pName);
	// Finish the Python Interpreter
	Py_Finalize();

	// clean 
	delete[] procname;

	return _PyLong_AsInt(presult);
}

// Displays the menu options
void displayMenu() {

	// Temporarily changes text color in function
	SetConsoleTextAttribute(color, FOREGROUND_GREEN);

	cout << "\n ________________________________________________ " << endl;
	cout << "|    MAIN MENU                                   |" << endl;
	cout << "|                                                |" << endl;
	cout << "| 1: View All Daily Purchases                    |" << endl;
	cout << "| 2: Search for Specific Item                    |" << endl;
	cout << "| 3: View Histogram For All Daily Purchases      |" << endl;
	cout << "| 4. Exit                                        |" << endl;
	cout << "|________________________________________________|" << endl;
	
	SetConsoleTextAttribute(color, 0x07);
}

// Gets user's menu selection and validates that it is an int
int validateInput() {
	
	int selection;
	
	// Temporarily changes text color in function
	SetConsoleTextAttribute(color, FOREGROUND_BLUE);
	
	cout << "\nEnter your selection as a number 1, 2, 3 or 4:" << endl;
	cin >> selection;

	// Request new input if user does not enter int value
	while (!cin) {
		cout << "\nNo letters or punctionation allowed. Enter your selection as a number 1, 2, 3 or 4:" << endl;
		cin.clear();
		cin.ignore();
		cin >> selection;
	}
	
	SetConsoleTextAttribute(color, 0x07);
	return selection;
}

// Requests input if menu selection 2 is selected and displays results
void searchInventory() {

	string userInput;

	cout << "\nEnter Item to Look Up:" << endl;
	cin >> userInput;
	cout << endl;

	// Temporarily changes text color in function
	SetConsoleTextAttribute(color, FOREGROUND_RED | BACKGROUND_BLUE | BACKGROUND_GREEN | BACKGROUND_RED);

	cout << userInput << " were purchased " << callIntFunc("determineFrequency", userInput) << " time(s).";

	// Gives suggestion if no result is found
	if (callIntFunc("determineFrequency", userInput) == 0) {
		cout << " Consider trying the singular or plural form.";
	}
	
	SetConsoleTextAttribute(color, 0x07);
}

// Reads in frequency.dat and outputs a histogram of items sold
void displayHistogram() {
	// Vectors to store product name and amount sold
	vector<string> productVec;
	vector<int> amountVec;

	// Calls Python function to create frequency.dat file
	CallProcedure("output");

	// Creates input stream and opens the file created in Python's output() function
	ifstream inStream;
	inStream.open("frequency.dat");

	// Outputs error if file does not open properly
	if (!inStream.is_open()) { 
		cout << "Could not open file." << endl;
	}
	else {
		string productName;
		int amountSold;
		
		// Converts file contents into variables 
		inStream >> productName >> amountSold;

		cout << left << setw(15) << "\nProduct" << " Number Sold" << endl;
		cout << "-------------------------------" << endl;
		
		// Adds all items to vector and then displays a * for every time it sold
		while (!inStream.fail()) {
			cout << left << setw(15) << productName << " ";
			for (int i = 0; i < amountSold; i++) {
				cout << "*";
			}
			cout << endl;

			// Add next item to front of vectors 
			productVec.push_back(productName);
			amountVec.push_back(amountSold);
			inStream >> productName >> amountSold;
		}
	}
	// Closes input stream
	inStream.close(); 
}

void main()
{
	int menuInput = 0;

	// Loops program until user selects exit
	do {
		// Display the menu and recieve user selection 
		displayMenu();
		menuInput = validateInput();

		// Validate menu input and perform the selected task
		switch (menuInput) {
		case 1:
			// Calls Python function to print the output of items.txt
			cout << "\nTotal Inventory" << endl;
			cout << "-------------------------------" << endl;
			
			CallProcedure("determineInventory");
			break;

		case 2:
			// Calls Python function to determine how many of a given item have sold and outputs the result
			searchInventory();
			break;

		case 3:
			// Creates frequency.dat using Python and then uses C++ to create and display a histogram 
			displayHistogram();
			break;
			
		case 4:
			// Output confirmation and end
			cout << "\nExiting program" << endl;
			break;

		// Outputs error message and requests new input if an invalid input is entered
		default:
			cout << "Not a valid selection. Try again." << endl;
		}
	// Exits menu loop if 4 is selected
	} while (menuInput != 4);
}
