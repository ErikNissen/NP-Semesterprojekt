//
// Created by erikn on 29.11.2022.
//

#include "PersistentFileManagement.hpp"
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
void PersistentFileManagement::save(const string& name){
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
/// \return The json object
/// \throws PersistentFileManagement::FileErrorException if the file does not exist
json PersistentFileManagement::load(const string& name){
	// Check if the directory exists
	if (!filesystem::exists(basePath)) {
		// Create the directory
		std::filesystem::create_directory(basePath);
	}else if(!filesystem::exists(filesystem::current_path().string() + "\\"
	                             + basePath + name + ".json")){
		throw PersistentFileManagement::FileErrorException(const_cast<char*>(("No data file found called " + name).c_str()));
	}
	std::ifstream f(filesystem::current_path().string() + "\\"
	                + this->basePath + name + ".json");

	return json::parse(f);
}

/// <BR><h3>Gets a value from a json object</h3>
/// \param key The key of the value
json PersistentFileManagement::get(const string& key){
	if(this->data.contains(key)){
		return this->data[key];
	}else{
		cout<<"No value found with the key: "<<key<<endl;
	}
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
void PersistentFileManagement::create(const string& name){
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
		}
	}
}


// Template functions

/// <BR><h3>Searches for a value in a json object</h3>
/// \param key The key of the value (string or regex)
/// \typeparam \b S The type of the value (string or regex)
/*template<typename S> void PersistentFileManagement::search(S search) {
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
*/
/*/// <BR><h3>Adds a value to a json object</h3>
/// \param key The key of the value
/// \param value The value
/// \typeparam \b T The type of the value
template<typename T>
void PersistentFileManagement::add(const string& key, T value) {
	// Check if the key already exists
	if(this->data.contains(key)){
		throw std::runtime_error("Key already exists. Use the update function to "
		                         "update the value.");
	}else{
		this->data[key] = value;
	}
}*/

/// <BR><h3>Search for a value or key.</h3>
/// \param search The value or key to search for
/// \param type The type of search (true = key, false = value)
void PersistentFileManagement::search( const std::string& search , bool keySearch) {
	int counter = 0;

	if(keySearch){
		for (auto& element : this->data.items()) {
			if(element.key() == search){
				cout << "[Found] " << element.key() << " : " << element.value()
				     << endl;
				counter++;
			}
		}
	}else{
		for (auto& element : this->data.items()) {
			if(element.value() == search){
				cout << "[Found] " << element.key() << " : " << element.value()
				     << endl;
				counter++;
			}
		}
	}

	if(counter == 0){
		cout << "No results found" << endl;
	}
}

/// <BR><h3>Search for a value or key. (regex)</h3>
/// \param search The value or key to search for
/// \param type The type of search (true = key, false = value)
void PersistentFileManagement::search( const std::regex& search, bool keySearch) {
	int counter = 0;

	if(keySearch){
		for (auto& element : this->data.items()) {
			if(regex_search(element.key(), search)){
				cout << "[Found] " << element.key() << " : " << element.value()
				     << endl;
				counter++;
			}
		}
	}else{
		for (auto& element : this->data.items()) {
			if(regex_search(to_string(element.value()), search)){
				cout << "[Found] " << element.key() << " : " << element.value()
				     << endl;
				counter++;
			}
		}
	}

	if(counter == 0){
		cout << "No results found" << endl;
	}
}

/// <BR><h3>Updates a value in a json object</h3>
/// \param key The key of the value
/// \param value The new value
/// \throws PersistentFileManagement::KeyErrorException if the key does not exist
void PersistentFileManagement::update( const std::string& key, const std::string& value ) {
	// Check if the key exists
	if (this->data.contains(key)) {
		this->data[key] = value;
	}else{
		throw PersistentFileManagement::KeyErrorException();
	}
}

/// <BR><h3>Updates a value in a json object</h3>
/// \param key The key of the value
/// \param value The new value
/// \throws PersistentFileManagement::KeyErrorException if the key does not exist
void PersistentFileManagement::update( const std::string& key, int value ) {
	// Check if the key exists
	if (this->data.contains(key)) {
		this->data[key] = value;
	}else{
		throw PersistentFileManagement::KeyErrorException();
	}
}

/// <BR><h3>Updates a value in a json object</h3>
/// \param key The key of the value
/// \param value The new value
/// \throws PersistentFileManagement::KeyErrorException if the key does not exist
void PersistentFileManagement::update( const std::string& key, double value ) {
	// Check if the key exists
	if (this->data.contains(key)) {
		this->data[key] = value;
	}else{
		throw PersistentFileManagement::KeyErrorException();
	}
}

/// <BR><h3>Updates a value in a json object</h3>
/// \param key The key of the value
/// \param value The new value
/// \throws PersistentFileManagement::KeyErrorException if the key does not exist
void PersistentFileManagement::update( const std::string& key, bool value ) {
	// Check if the key exists
	if (this->data.contains(key)) {
		this->data[key] = value;
	}else{
		throw PersistentFileManagement::KeyErrorException();
	}
}

/// <BR><h3>Updates a value in a json object</h3>
/// \param key The key of the value
/// \param value The new value
/// \throws PersistentFileManagement::KeyErrorException if the key does not exist
void PersistentFileManagement::update( const std::string& key, json value ) {
	// Check if the key exists
	if (this->data.contains(key)) {
		this->data[key] = value;
	}else{
		throw PersistentFileManagement::KeyErrorException();
	}
}

/*
/// <BR><h3>Adds a value to a json object</h3>
/// \param key The key of the value
/// \param value The value
/// \throws PersistentFileManagement::KeyErrorException if the key exists
void PersistentFileManagement::add( const std::string& key, std::string value ) {
	// Check if the key already exists
	if(this->data.contains(key)){
		throw PersistentFileManagement::KeyErrorException("Key already exists. Use the update function to update the value.");
	}else{
		this->data[key] = value;
	}
}

/// <BR><h3>Adds a value to a json object</h3>
/// \param key The key of the value
/// \param value The value
/// \throws PersistentFileManagement::KeyErrorException if the key exists
void PersistentFileManagement::add( const std::string& key, int value ) {
	// Check if the key already exists
	if(this->data.contains(key)){
		throw PersistentFileManagement::KeyErrorException("Key already exists. Use the update function to update the value.");
	}else{
		this->data[key] = value;
	}
}

/// <BR><h3>Adds a value to a json object</h3>
/// \param key The key of the value
/// \param value The value
/// \throws PersistentFileManagement::KeyErrorException if the key exists
void PersistentFileManagement::add( const std::string& key, double value ) {
	// Check if the key already exists
	if(this->data.contains(key)){
		throw PersistentFileManagement::KeyErrorException("Key already exists. Use the update function to update the value.");
	}else{
		this->data[key] = value;
	}
}

/// <BR><h3>Adds a value to a json object</h3>
/// \param key The key of the value
/// \param value The value
/// \throws PersistentFileManagement::KeyErrorException if the key exists
void PersistentFileManagement::add( const std::string& key, bool value ) {
	// Check if the key already exists
	if(this->data.contains(key)){
		throw PersistentFileManagement::KeyErrorException("Key already exists. Use the update function to update the value.");
	}else{
		this->data[key] = value;
	}
}

/// <BR><h3>Adds a value to a json object</h3>
/// \param key The key of the value
/// \param value The value
/// \throws PersistentFileManagement::KeyErrorException if the key exists
void PersistentFileManagement::add( const std::string& key, json value ) {
	// Check if the key already exists
	if(this->data.contains(key)){
		throw PersistentFileManagement::KeyErrorException("Key already exists. Use the update function to update the value.");
	}else{
		this->data[key] = value;
	}
}
 */


//Getter
/// <BR><h3>Returns the json object of this instance.</h3>
json PersistentFileManagement::getData() {
	return this->data;
}

//Setter
/// <BR><h3>Sets the name of the file</h3>
void PersistentFileManagement::setName(const string& name ) {
	this->name = name;
	this->create();
}