//
// Created by erikn on 29.11.2022.
//

#include <nlohmann/json.hpp>
#include "json.hpp"
#include <fstream>
#include <iostream>
#include <utility>

using namespace std;
using json = nlohmann::json;


PersistentFileManagement::~PersistentFileManagement() {
	this->save(this->name);
}

PersistentFileManagement::PersistentFileManagement(const
std::string& name) {
	this->basePath = "data/";
	this->data = load( this->basePath + name + ".json");
	this->name = name;
}

PersistentFileManagement::PersistentFileManagement() {
	this->basePath = "data/";
	this->data = json::object();
}

/// Saves a json object to a file
/// \param path The path to the file
void PersistentFileManagement::save(const std::string&
name){
	// Check if the directory exists
	if (!filesystem::exists( this->basePath)) {
		// Create the directory
		std::filesystem::create_directory(this->basePath);
	}else if(!filesystem::exists(this->basePath + name + ".json")){
		throw std::runtime_error("File does not exist.\nFirst "
								 "create the file with the create function.");
	}
	ofstream file(this->basePath + name + ".json");
	file << this->data.dump(4);
	file.close();
}

/// Saves a json object to a file
void PersistentFileManagement::save() {
	if(this->name.empty()){
		throw std::runtime_error("No name was given.\nFirst set a name with the "
								 "constructor or the setName function.");
	}
	this->save(this->name);
}

void PersistentFileManagement::setName( const std::string &name ) {
	this->name = name;
}

/// Loads a json object from a file
/// \param name The name of the file
nlohmann::json PersistentFileManagement::load(const std::string&
name){
	// Check if the directory exists
	if (!filesystem::exists(basePath)) {
		// Create the directory
		std::filesystem::create_directory(basePath);
	}else if(!filesystem::exists(basePath + name + ".json")){
		throw runtime_error("No data file found called " + name);
	}
	std::ifstream f(PersistentFileManagement::basePath + name + ".json");
	this->data = json::parse(f);
}

/// Gets a value from a json object
/// \param key The key of the value
nlohmann::json PersistentFileManagement::get(std::string
key){
	return this->data[std::move(key)];
}

/// Adds a value to a json object
/// \param key The key of the value
/// \param value The value
template<typename T> void
PersistentFileManagement::add( const std::string& key, const T
&value ) {
	// Check if the key already exists
	if(this->data.contains(key)){
		throw std::runtime_error("Key already exists. Use the update function to "
								 "update the value.");
	}else{
		this->data[key] = value;
	}
}

/// Deletes a key from a json object
/// \param key The key to delete
void PersistentFileManagement::remove(const std::string& key){
	// Check if the key exists
	if (this->data.contains(key)) {
		this->data.erase(key);
	}else{
		throw runtime_error("Key does not exist");
	}
}

/// Updates a value in a json object
/// \param key The key of the value
/// \param value The new value
template<typename T> void
PersistentFileManagement::update( const std::string& key, const T &value ) {
	// Check if the key exists
	if (this->data.contains(key)) {
		this->data[key] = value;
	}else{
		throw runtime_error("Key does not exist");
	}
}


/// Creates a new json file
/// \param name The name of the file
/// \return The path to the file
void PersistentFileManagement::create(const string& name){
	//Check if directory exists
	if (!filesystem::exists( this->basePath)) {
		//Directory does not exist
		//Create directory
		filesystem::create_directory(this->basePath);
	}
	//Create file
	std::ofstream _file( this->basePath + name + ".json");
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
		throw std::invalid_argument("File already exists");
	}
}

void PersistentFileManagement::create(){
	//Check if directory exists
	if (!filesystem::exists( this->basePath)) {
		//Directory does not exist
		//Create directory
		filesystem::create_directory(this->basePath);
	}
	//Check if name is empty
	if (this->name.empty()) {
		//Name is empty
		//Throw error
		throw std::invalid_argument("Name is empty. Please set a "
									"name with the setName() method");
	}else{
		//Create file
		std::ofstream _file( this->basePath + this->name + ".json");
		//Check if file exists
		if (!filesystem::exists(this->basePath +
		this->name + ".json")) {
			//File exists
			//Create file
			_file << "{}";
			//Close file
			_file.close();
			//Return path
			cout << "Created file " << PersistentFileManagement::basePath + this->name + ".json" << endl;
		} else {
			//File exists
			//Throw error
			throw std::invalid_argument("File already exists");
		}
	}
}

nlohmann::json PersistentFileManagement::getData() {
	return this->data;
}


