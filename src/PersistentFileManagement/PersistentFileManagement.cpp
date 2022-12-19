//
// Created by erikn on 29.11.2022.
//

#include "PersistentFileManagement.hpp"

using namespace std;
using json = nlohmann::json;

// Constructor
/// <BR><h3>Creates a new PersistentFileManagement object</h3>
/// \param path The path to the file <VAR>(optional)</VAR>
PersistentFileManagement::PersistentFileManagement(const string& newName) {
	this->basePath = "data\\";
	this->name = newName;
	this->logPath = "log\\";
	if(filesystem::exists(filesystem::current_path().string() + "\\" +
	this->basePath +
	this->name + ".json")) {
		this->data = load(this->name);
	}else{
		this->create();
		this->data = load(this->name);
	}
}

PersistentFileManagement::PersistentFileManagement() {
	this->basePath = "data\\";
	this->logPath = "log\\";
	this->data = json::object();
}

// Destructor
PersistentFileManagement::~PersistentFileManagement() {
	if(this->name.empty()){
		cout << "Please set name to save the file: " << endl;
		cin >> this->name;
	}
	this->save(this->name);
}

/// <BR><h3>Saves a json object to a file</h3>
/// \param path The path to the file
void PersistentFileManagement::save(const string& newName){
	// Check if the directory exists
	if (!filesystem::exists( this->basePath)) {
		// Create the directory
		filesystem::create_directory(this->basePath);
	}else if(!filesystem::exists(filesystem::current_path().string() + "\\"
	+ this->basePath + newName + ".json")){
		this->create(newName);
	}
	ofstream file(this->basePath + newName + ".json");
	file << this->data.dump(4);
	file.close();
}

/// <BR><h3>Saves a json object to a file</h3>
void PersistentFileManagement::save() {
	if(this->name.empty()){
		cout<<"No name was given.\nFirst set a name with the constructor or "
			  "the setName function." << endl;
	}
	this->save(this->name);
}

/// <BR><h3>Loads a json object from a file</h3>
/// \param name The name of the file
/// \return The json object
/// \throws PersistentFileManagement::FileErrorException if the file does not exist
json PersistentFileManagement::load(const string& newValue){
	// Check if the directory exists
	if (!filesystem::exists(basePath)) {
		// Create the directory
		std::filesystem::create_directory(basePath);
	}else if(!filesystem::exists(filesystem::current_path().string() + "\\"
	                             + basePath + newValue + ".json")){
		throw PersistentFileManagement::FileErrorException(("No data file found called " + newValue));
	}
	std::ifstream f(filesystem::current_path().string() + "\\"
	                + this->basePath + newValue + ".json");

	return json::parse(f);
}

/// <BR><h3>Gets a value from a json object</h3>
/// \param key The key of the value
json PersistentFileManagement::get(const string& key){
	if(!this->data.contains(key)){
		cout<<"No value found with the key: "<<key<<endl;
		return 0;
	}
	return this->data[key];
}

/// <BR><h3>Deletes a key from a json object</h3>
/// \param key The key to delete
/// \throws PersistentFileManagement::KeyErrorException if the key does not exist
void PersistentFileManagement::remove(const string& key){
	// Check if the key exists
	if (this->data.contains(key)) {
		this->data.erase(key);
	}else{
		throw PersistentFileManagement::KeyErrorException();
	}
}

/// <BR><h3>Purges all data from json object</h3>
void PersistentFileManagement::purge(){
	this->data = json::object();
}

/// <BR><h3>Creates a new json file</h3>
/// \param name The name of the file
/// \throws PersistentFileManagement::FileErrorException if the file already exists
void PersistentFileManagement::create(const string& newName){
	//Check if directory exists
	if (!filesystem::exists( this->basePath)) {
		//Directory does not exist
		//Create directory
		filesystem::create_directory(this->basePath);
	}
	//Create file
	ofstream _file( this->basePath + newName + ".json");
	//Check if file exists
	if (!filesystem::exists(this->basePath +
                                    newName + ".json")) {
		//File exists
		//Create file
		_file << "{}";
		//Close file
		_file.close();
		//Return path
		cout << "Created file " << PersistentFileManagement::basePath + newName + ".json" << endl;
	} else {
		//File exists
		//Throw error
		throw PersistentFileManagement::FileErrorException();
	}
}

/// <BR><h3>Creates a new json file</h3>
/// \throws PersistentFileManagement::FileErrorException if the file already exists
/// \throws PersistentFileManagement::NameErrorException if no name was given
void PersistentFileManagement::create(){
	//Check if directory exists
	if (!filesystem::exists( filesystem::current_path().string() + "\\" +
	                         this->basePath)) {
		//Directory does not exist
		//Create directory
		filesystem::create_directory(filesystem::current_path().string() +
		                             "\\" + this->basePath);
	}
	//Check if name is empty
	if (this->name.empty()) {
		//Name is empty
		//Throw error
		throw PersistentFileManagement::NameErrorException();
	}else{
		//Check if file exists
		if (!filesystem::exists(filesystem::current_path().string() + "\\" +
		                        this->basePath +
		                        this->name + ".json")) {
			//Create file
			ofstream datafile( filesystem::current_path().string() + "\\" +
			                   this->basePath + this->name + ".json");
			datafile << "{}";
			//Close file
			datafile.close();
			//Return path
			cout << "Created file " << this->basePath + this->name + ".json" <<
			     endl;
		} else {
			//File exists
			// Open file
			ifstream datafile( filesystem::current_path().string() + "\\" +
			                   this->basePath + this->name + ".json");
			this->data = json::parse(datafile);
			datafile.close();
		}
	}
}

template<typename T1, typename T2>
using mul = std::ratio_multiply<T1, T2>;

void PersistentFileManagement::log(
		std::chrono::duration<int> minTime,
		std::chrono::duration<int> maxTime,
		string inventory
) {
	// Calculate the median time
	auto medTime{minTime + (maxTime - minTime) / 2};

	auto minHrs = chrono::duration_cast<chrono::hours>(minTime);
	auto minMins = chrono::duration_cast<chrono::minutes>(minTime - minHrs);
	auto minSecs = chrono::duration_cast<chrono::seconds>(minTime - minHrs -
			minMins);
	auto minMs = chrono::duration_cast<chrono::milliseconds>(minTime -
			minHrs - minMins - minSecs);

	auto maxHrs = chrono::duration_cast<chrono::hours>(maxTime);
	auto maxMins = chrono::duration_cast<chrono::minutes>(maxTime - maxHrs);
	auto maxSecs = chrono::duration_cast<chrono::seconds>(maxTime - maxHrs -
	                                                      maxMins);
	auto maxMs = chrono::duration_cast<chrono::milliseconds>(maxTime -
	                                                         maxHrs - maxMins - maxSecs);

	auto medHrs = chrono::duration_cast<chrono::hours>(medTime);
	auto medMins = chrono::duration_cast<chrono::minutes>(medTime - medHrs);
	auto medSecs = chrono::duration_cast<chrono::seconds>(medTime - medHrs -
	                                                      medMins);
	auto medMs = chrono::duration_cast<chrono::milliseconds>(medTime -
	                                                         medHrs - medMins - medSecs);
	stringstream ss;

	// Open the file
	std::ofstream logfile;
	string filename{filesystem::current_path().string() + "\\" +
			this->logPath + this->name + ".log"};
	if(!filesystem::exists(filesystem::current_path().string() + "\\" +
	                      this->logPath)){
		filesystem::create_directory(filesystem::current_path().string() + "\\" +
		                             this->logPath);
	}

	// Check if the file exists
	if (filesystem::exists(filename)) {
		// Open the file in append mode
		logfile.open(filename, std::ios::app);
	}else{
		// Open the file in write mode
		logfile.open(filename);
	}

	json log, data;
	data = json::parse(inventory);
	//log["Inventory"] = data;
	ss << minHrs.count() << ":" << minMins.count() << ":" << minSecs.count()
	<< "." << minMs.count();
	log["minTime"] = ss.str();
	ss.str("");
	ss << maxHrs.count() << ":" << maxMins.count() << ":" << maxSecs.count()
	   << "." << maxMs.count();
	log["maxTime"] = ss.str();
	ss.str("");
	ss << medHrs.count() << ":" << medMins.count() << ":" << medSecs.count()
	   << "." << medMs.count();
	log["medianTime"] = ss.str();

	auto shelfPairs = data["shelfPairs"];
	for(auto shelf: shelfPairs.items()){
		using ull = unsigned long long;
		ull itemsLeft = 0, itemsRight = 0;
		auto shelfPairNumber = shelf.value()["shelfPairNumber"];
		auto shelfLeft = shelf.value()["shelfLeft"]["Matrix"];
		auto shelfRight = shelf.value()["shelfRight"]["Matrix"];
		for(auto i: shelfLeft.items()){
			//Matrix
			for ( auto j: i.value().items() ) {
				int c = j.value()
				["Container"]["currentAmountOfItem"];
				itemsLeft = itemsLeft + c;
				log["shelfPair"][to_string(shelfPairNumber)
				]["shelfLeft"]["Container"].push_back(j.value()["Container"]);
			}
		}
		for(auto i: shelfRight.items()){
			//Matrix
			for ( auto j: i.value().items() ) {
				int c = j.value()
				["Container"]["currentAmountOfItem"];
				itemsRight = itemsRight + c;
				log["shelfPair"][to_string(shelfPairNumber)
				]["shelfRight"]["Container"].push_back(j.value()["Container"]);
			}
		}

		log["shelfPair"][to_string(shelfPairNumber)]["AmountOfItems"] =
				itemsLeft + itemsRight;
		log["shelfPair"][to_string(shelfPairNumber)
		]["ShelfLeft"]["AmountOfItems"] = itemsLeft;
		log["shelfPair"][to_string(shelfPairNumber)
		]["ShelfRight"]["AmountOfItems"] = itemsRight;
	}

	logfile << "MinTime: " << log["minTime"].dump() << ", MaxTime: " <<
	log["maxTime"].dump() << ", MedianTime: " << log["medianTime"].dump() <<
	", Data: " << log["shelfPair"].dump();
	logfile.close();
}


//Getter
/// <BR><h3>Returns the json object of this instance.</h3>
json PersistentFileManagement::getData() {
	return this->data;
}

//Setter
/// <BR><h3>Sets the name of the file</h3>
void PersistentFileManagement::setName(const string& newName ) {
	this->name = newName;
}