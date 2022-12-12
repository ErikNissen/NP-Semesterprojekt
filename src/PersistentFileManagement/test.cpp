#include "json.hpp"
#include <iostream>

using namespace std;

int main() {
	cout << "Create JSON Object" << endl;
	PersistentFileManagement pfm = PersistentFileManagement("test");

	cout << "Create JSON file" << endl;
	pfm.create("test");

	cout << "Add data to JSON Object" << endl;
	pfm.add("name", "Erik");
	pfm.add("age", 20);
	pfm.add("height", 1.80);
	pfm.add("isStudent", true);

	cout << "Save JSON Object to file" << endl;
	pfm.save();

	cout << "Load JSON Object from file" << endl;
	pfm.load("test");

	cout << "Get data from JSON Object" << endl;
	cout << pfm.get("name") << endl;
	cout << pfm.get("age") << endl;
	cout << pfm.get("height") << endl;
	cout << pfm.get("isStudent") << endl;

	cout << "Update data in JSON Object" << endl;
	pfm.update("name", "Erik Nissen");
	pfm.update("age", 21);
	pfm.update("height", 1.81);
	pfm.update("isStudent", false);

	cout << "Search (String)" << endl;
	pfm.search("Erik");
	pfm.search(21);
	pfm.search(1.81);
	pfm.search(false);

	cout << "Search (Regex)" << endl;
	// contains "E"
	pfm.search(regex("E"));

	// contains not "a"
	pfm.search(regex("[^a]"));

	cout << "Delete data in JSON Object" << endl;
	pfm.remove("name");
	pfm.remove("age");
	pfm.remove("height");
	pfm.remove("isStudent");

}