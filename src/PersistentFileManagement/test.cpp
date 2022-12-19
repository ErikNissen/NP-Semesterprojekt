#include "PersistentFileManagement.hpp"
#include <iostream>

using namespace std;

int main() {
	cout << "Create JSON Object" << endl;
	auto pfm = PersistentFileManagement("test");

	//cout << "Create JSON file" << endl;
	//pfm.create("test");

	cout << "Add data to JSON Object" << endl;
	string name = "Erik";
	pfm.add<string>("name", name);
	pfm.add<int>("age", 20);
	pfm.add<float>("height", 1.80);
	pfm.add<bool>("isStudent", true);

	cout << "Save JSON Object to file" << endl;
	pfm.save();

	cout << "Load JSON Object from file" << endl;
	pfm.load("test");

	cout << "Search (String)" << endl;
	pfm.search<string>("name");
	pfm.search<string>("age");
	pfm.search<string>("height");
	pfm.search<string>("isStudent");

	cout << "Get data from JSON Object" << endl;
	cout << pfm.get("name") << endl;
	cout << pfm.get("age") << endl;
	cout << pfm.get("height") << endl;
	cout << pfm.get("isStudent") << endl;

	cout << "Update data in JSON Object" << endl;
	name = "Erik Nissen";
	pfm.update<string>("name", name);
	pfm.update<int>("age", 21);
	pfm.update<float>("height", 1.81);
	pfm.update<bool>("isStudent", false);

	cout << "Delete data in JSON Object" << endl;
	pfm.remove("name");
	pfm.remove("age");
	pfm.remove("height");
	pfm.remove("isStudent");
}