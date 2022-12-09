#include "PersistentFileManagement/json.hpp"

#include <iostream>
#include <string>

using namespace std;

int main() {
	cout << "Create JSON Object" << endl;
	auto pfm = PersistentFileManagement("test");
	cout << endl;

	cout << "Press any key to continue..." << endl;
	cin.get();

	cout << "Add data to JSON Object" << endl;
	string name = "Max Mustermann";
	pfm.add("name", name);
	pfm.add("age", 20);
	pfm.add("height", 1.80f);
	pfm.add("isStudent", true);
	cout << endl;

	cout << "Press any key to continue..." << endl;
	cin.get();

	cout << "Save JSON Object to file" << endl;
	pfm.save();
	cout << endl;

	cout << "Press any key to continue..." << endl;
	cin.get();

	cout << "Load JSON Object from file" << endl;
	pfm.load("test");
	cout << endl;

	cout << "Press any key to continue..." << endl;
	cin.get();

	cout << "Get data from JSON Object" << endl;
	cout << pfm.get("name") << endl;
	cout << pfm.get("age") << endl;
	cout << pfm.get("height") << endl;
	cout << pfm.get("isStudent") << endl;
	cout << endl;

	cout << "Press any key to continue..." << endl;
	cin.get();

	cout << "Get all data containing in the JSON Object." << endl;
	cout << pfm.getData() << endl;
	cout << endl;

	cout << "Press any key to continue..." << endl;
	cin.get();

	cout << "Update data in JSON Object" << endl;
	string newName = "Maximilian Mustermann";
	pfm.update("name", newName);
	pfm.update("age", 21);
	pfm.update("height", 1.81f);
	pfm.update("isStudent", false);
	cout << endl;

	cout << "Press any key to continue..." << endl;
	cin.get();

	cout << "Search (String)" << endl;
	pfm.search("Erik");
	pfm.search("21");
	pfm.search("1.81");
	pfm.search("false");
	cout << endl;

	cout << "Press any key to continue..." << endl;
	cin.get();

	cout << "Search (Regex)" << endl;
	cout << "contains \"E\": " << endl;
	pfm.search(regex("E"));

	cout << "contains not \"a\": " << endl;
	pfm.search(regex("[^a]"));
	cout << endl;

	cout << "Press any key to continue..." << endl;
	cin.get();

	cout << "Delete data in JSON Object" << endl;
	pfm.remove("name");
	pfm.remove("age");
	pfm.remove("height");
	pfm.remove("isStudent");
	cout << endl;

	cout << "Press any key to continue..." << endl;
	cin.get();


	cout << "Purge JSON Object" << endl;
	pfm.purge();
	cout << endl;

	return 0;
}