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

const std::string PersistentFileManagement::basePath = "data/";

/// Saves a json object to a file
/// \param json The json object to save
/// \param path The path to the file
void PersistentFileManagement::save(json &json, const std::string& path){
	ofstream file(path);
	file << json.dump(4);
	file.close();
}

/// Loads a json object from a file
/// \param path The path to the file
nlohmann::json PersistentFileManagement::load(const std::string& path){
	std::ifstream f(path);
	json data = json::parse(f);
	return data;
}

/// Gets a value from a json object
/// \param dict The json object
/// \param key The key of the value
nlohmann::json PersistentFileManagement::get(json &dict, std::string
key){
	return dict[std::move(key)];
}

/// Adds a value to a json object
/// \param dict The json object
/// \param key The key of the value
/// \param value The value
void PersistentFileManagement::add(json &dict, const std::string& key,
                const std::string& value){
	//Check if key exists
	if (dict.find(key) != dict.end()) {
		//Key exists
		//Throw error
		throw std::invalid_argument("Key already exists");
	} else {
		//Key does not exist
		dict[key] = value;
	}
}

/// Adds a value to a json object
/// \param dict The json object
/// \param key The key of the value
/// \param value The value
void PersistentFileManagement::add(json &dict, const std::string& key,
                int value){
	//Check if key exists
	if (dict.find(key) != dict.end()) {
		//Key exists
		//Throw error
		throw std::invalid_argument("Key already exists");
	} else {
		//Key does not exist
		dict[key] = value;
	}
}

/// Adds a value to a json object
/// \param dict The json object
/// \param key The key of the value
/// \param value The value
void PersistentFileManagement::add(json &dict, const std::string& key,
								   bool value){
	//Check if key exists
	if (dict.find(key) != dict.end()) {
		//Key exists
		//Throw error
		throw std::invalid_argument("Key already exists");
	} else {
		//Key does not exist
		dict[key] = value;
	}
}

/// Adds a value to a json object
/// \param dict The json object
/// \param key The key of the value
/// \param value The value
void PersistentFileManagement::add(json &dict, const std::string& key,
                double value){
	//Check if key exists
	if (dict.find(key) != dict.end()) {
		//Key exists
		//Throw error
		throw std::invalid_argument("Key already exists");
	} else {
		//Key does not exist
		dict[key] = value;
	}
}

/// Adds a value to a json object
/// \param dict The json object
/// \param key The key of the value
/// \param value The value
void PersistentFileManagement::add(json &dict, const std::string& key,
                float value){
	//Check if key exists
	if (dict.find(key) != dict.end()) {
		//Key exists
		//Throw error
		throw std::invalid_argument("Key already exists");
	} else {
		//Key does not exist
		dict[key] = value;
	}
}

/// Adds a value to a json object
/// \param dict The json object
/// \param key The key of the value
/// \param value The value
void PersistentFileManagement::add(json &dict, const std::string& key,
                char value){
	//Check if key exists
	if (dict.find(key) != dict.end()) {
		//Key exists
		//Throw error
		throw std::invalid_argument("Key already exists");
	} else {
		//Key does not exist
		dict[key] = value;
	}
}

/// Deletes a key from a json object
/// \param dict The json object
/// \param key The key to delete
void PersistentFileManagement::remove(json &dict, const std::string& key){
	//Check if key exists
	if (dict.find(key) != dict.end()) {
		//Key exists
		//Remove key
		dict.erase(key);
	} else {
		//Key does not exist
		//Throw error
		throw std::invalid_argument("Key does not exist");
	}
}

/// Updates a value in a json object
/// \param dict The json object
/// \param key The key of the value
/// \param value The new value
void PersistentFileManagement::update(json &dict, const std::string& key,
                   const std::string& value){
	//Check if key exists
	if (dict.find(key) != dict.end()) {
		//Key exists
		//Update key
		dict[key] = value;
	} else {
		//Key does not exist
		//Throw error
		throw std::invalid_argument("Key does not exist");
	}
}

/// Updates a value in a json object
/// \param dict The json object
/// \param key The key of the value
/// \param value The new value
void PersistentFileManagement::update(json &dict, const std::string& key,
                   int value){
	//Check if key exists
	if (dict.find(key) != dict.end()) {
		//Key exists
		//Update key
		dict[key] = value;
	} else {
		//Key does not exist
		//Throw error
		throw std::invalid_argument("Key does not exist");
	}
}

/// Updates a value in a json object
/// \param dict The json object
/// \param key The key of the value
/// \param value The new value
void PersistentFileManagement::update(json &dict, const std::string& key,
                   bool value){
	//Check if key exists
	if (dict.find(key) != dict.end()) {
		//Key exists
		//Update key
		dict[key] = value;
	} else {
		//Key does not exist
		//Throw error
		throw std::invalid_argument("Key does not exist");
	}
}

/// Updates a value in a json object
/// \param dict The json object
/// \param key The key of the value
/// \param value The new value
void PersistentFileManagement::update(json &dict, const std::string& key,
				   double value){
	//Check if key exists
	if (dict.find(key) != dict.end()) {
		//Key exists
		//Update key
		dict[key] = value;
	} else {
		//Key does not exist
		//Throw error
		throw std::invalid_argument("Key does not exist");
	}
}

/// Updates a value in a json object
/// \param dict The json object
/// \param key The key of the value
/// \param value The new value
void PersistentFileManagement::update(json &dict, const std::string& key,
                   float value){
	//Check if key exists
	if (dict.find(key) != dict.end()) {
		//Key exists
		//Update key
		dict[key] = value;
	} else {
		//Key does not exist
		//Throw error
		throw std::invalid_argument("Key does not exist");
	}
}

/// Updates a value in a json object
/// \param dict The json object
/// \param key The key of the value
/// \param value The new value
void PersistentFileManagement::update(json &dict, const std::string&
key, char value){
	//Check if key exists
	if (dict.find(key) != dict.end()) {
		//Key exists
		//Update key
		dict[key] = value;
	} else {
		//Key does not exist
		//Throw error
		throw std::invalid_argument("Key does not exist");
	}
}

/// Creates a new json file
/// \param path The path to the file
/// \return The path to the file
string PersistentFileManagement::create(const string& name){
	//Check if directory exists
	if (!filesystem::exists(PersistentFileManagement::basePath)) {
		//Directory does not exist
		//Create directory
		filesystem::create_directory(PersistentFileManagement::basePath);
	}
	//Create file
	std::ofstream file(PersistentFileManagement::basePath + name + ".json");
	//Check if file exists
	if (file.is_open()) {
		//File exists
		//Create file
		file << "{}";
		//Close file
		file.close();
		//Return path
		cout << "Created file " << PersistentFileManagement::basePath + name + ".json" << endl;
		return PersistentFileManagement::basePath + name + ".json";
	} else {
		//File exists
		//Throw error
		throw std::invalid_argument("File already exists");
	}
}