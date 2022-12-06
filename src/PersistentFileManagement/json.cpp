//
// Created by erikn on 29.11.2022.
//

#include "json.hpp"
#include <iostream>
#include <string>

using namespace std;
using json = nlohmann::json;

// Constructor
/// <BR><h3>Creates a new PersistentFileManagement object</h3>
/// \param path The path to the file <VAR>(optional)</VAR>
PersistentFileManagement::PersistentFileManagement(string name) {
	this->basePath = "data\\";
	this->name = name;
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
void PersistentFileManagement::save(string name){
	// Check if the directory exists
	if (!filesystem::exists( this->basePath)) {
		// Create the directory
		filesystem::create_directory(this->basePath);
	}else if(!filesystem::exists(filesystem::current_path().string() + "\\"
	+ this->basePath + name + ".json")){
		this->create(name);
	}
	ofstream file(this->basePath + name + ".json");
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
json PersistentFileManagement::load(const string name){
	// Check if the directory exists
	if (!filesystem::exists(basePath)) {
		// Create the directory
		std::filesystem::create_directory(basePath);
	}else if(!filesystem::exists(filesystem::current_path().string() + "\\"
	                             + basePath + name + ".json")){
		throw runtime_error("No data file found called " + name);
	}
	std::ifstream f(this->basePath + name + ".json");
	return json::parse(f);
}

/// <BR><h3>Gets a value from a json object</h3>
/// \param key The key of the value
json PersistentFileManagement::get(string key){
	if(this->data.contains(key)){
		return this->data[key];
	}else{
		cout<<"No value found with the key: "<<key<<endl;
	}
}

/// <BR><h3>Deletes a key from a json object</h3>
/// \param key The key to delete
void PersistentFileManagement::remove(string key){
	// Check if the key exists
	if (this->data.contains(key)) {
		this->data.erase(key);
	}else{
		throw runtime_error("Key does not exist");
	}
}

/// <BR><h3>Creates a new json file</h3>
/// \param name The name of the file
void PersistentFileManagement::create(string name){
	//Check if directory exists
	if (!filesystem::exists( this->basePath)) {
		//Directory does not exist
		//Create directory
		filesystem::create_directory(this->basePath);
	}
	//Create file
	ofstream _file( this->basePath + name + ".json");
	//Check if file exists
	if (!filesystem::exists(this->basePath +
	                        name + ".json")) {
		//File exists
		//Create file
		_file << "{}";
		//Close file
		_file.close();
		//Return path
		cout << "Created file " << PersistentFileManagement::basePath + name + ".json" << endl;
	} else {
		//File exists
		//Throw error
		throw invalid_argument("File already exists");
	}
}

/// <BR><h3>Creates a new json file</h3>
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
		throw invalid_argument("Name is empty. Please set a "
		                       "name with the setName() method");
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
			//Throw error
			throw invalid_argument("File already exists");
		}
	}
}


// Template functions
/// \todo Fix template functions

/// <BR><h3>Searches for a value in a json object</h3>
/// \param key The key of the value (string or regex)
/// \typeparam \b S The type of the value (string or regex)
template<typename S> void PersistentFileManagement::search(S search) {
	assert(typeid(search) == typeid(string) || typeid(search) == typeid(regex));

	int counter = 0;

	if(typeid(search) == typeid(string)){
		for (auto& element : this->data.items()) {
			if(element.value() == search){
				cout << "[Found] " << element.key() << " : " << element.value()
				<< endl;
				counter++;
			}
		}
	}else if(typeid(search) == typeid(regex)){
		for (auto& element : this->data.items()) {
			if(regex_search(element.value(), search)){
				cout << "[Found] " << element.key() << " : " << element.value()
				<< endl;
				counter++;
			}
		}
	}else{
		throw runtime_error("Invalid search type");
	}

	if(counter == 0){
		cout << "No results found" << endl;
	}
}

/// <BR><h3>Updates a value in a json object</h3>
/// \param key The key of the value
/// \param value The new value
/// \typeparam \b U The type of the value
template<typename U> void
PersistentFileManagement::update(string key, U value ) {
	// Check if the key exists
	if (this->data.contains(key)) {
		this->data[key] = value;
	}else{
		throw runtime_error("Key does not exist");
	}
}

/// <BR><h3>Adds a value to a json object</h3>
/// \param key The key of the value
/// \param value The value
/// \typeparam \b A The type of the value
template<typename A> void PersistentFileManagement::add(string key, A value) {
	// Check if the key already exists
	if(this->data.contains(key)){
		throw std::runtime_error("Key already exists. Use the update function to "
		                         "update the value.");
	}else{
		this->data[key] = value;
	}
}

//Getter
/// <BR><h3>Returns the json object of this instance.</h3>
json PersistentFileManagement::getData() {
	return this->data;
}

//Setter
/// <BR><h3>Sets the name of the file</h3>
void PersistentFileManagement::setName(string name ) {
	this->name = name;
	this->create();
}