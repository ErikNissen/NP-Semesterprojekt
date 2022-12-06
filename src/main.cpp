#include "PersistentFileManagement/json.hpp"

#include <iostream>
#include <string>

using namespace std;

int main() {
	cout << "Create JSON Object" << endl;
	auto pfm = PersistentFileManagement("test");

	//cout << "Add data to JSON Object" << endl;
	//pfm.add<string>("name", "Erik");
	//pfm.add<int>("age", 20);
	//pfm.add<float>("height", 1.80f);
	//pfm.add<bool>("isStudent", true);

	cout << "Save JSON Object to file" << endl;
	pfm.save();

	cout << "Load JSON Object from file" << endl;
	pfm.load("test");

	cout << "Get data from JSON Object" << endl;
	cout << pfm.get("name") << endl;
	//cout << pfm.get("age") << endl;
	//cout << pfm.get("height") << endl;
	//cout << pfm.get("isStudent") << endl;

	//cout << "Update data in JSON Object" << endl;
	//pfm.update<string>("name", "Erik Nissen");
	//pfm.update<int>("age", 21);
	//pfm.update<float>("height", 1.81f);
	//pfm.update<bool>("isStudent", false);

	//cout << "Search (String)" << endl;
	//pfm.search<string>("Erik");
	//pfm.search<string>("21");
	//pfm.search<string>("1.81");
	//pfm.search<string>("false");

	//cout << "Search (Regex)" << endl;
	// contains "E"
	//pfm.search<regex>(regex("E"));

	// contains not "a"
	//pfm.search<regex>(regex("[^a]"));

	//cout << "Delete data in JSON Object" << endl;
	//pfm.remove("name");
	//pfm.remove("age");
	//pfm.remove("height");
	//pfm.remove("isStudent");

	return 0;
}