//
// Created by erikn on 29.11.2022.
//

#ifndef NP_SEMESTERPROJEKT_PERSISTENTFILEMANAGEMENT_HPP
#define NP_SEMESTERPROJEKT_PERSISTENTFILEMANAGEMENT_HPP

#include <iostream>
#include <fstream>
#include <regex>
#include <utility>
#include "../../_deps/json-src/single_include/nlohmann/json.hpp"

class PersistentFileManagement {
public:
	// Constructor
	explicit PersistentFileManagement(const std::string& name);

	PersistentFileManagement();

	// Destructor
	~PersistentFileManagement();

	//Getter
	nlohmann::json getData();

	//Setter
	void setName(const std::string& name);

	//Exceptions
	class KeyErrorException : public std::exception {
	private:
		std::string message;

	public:
		explicit KeyErrorException(std::string msg="Key does not exist"): message(std::move(msg)){}
		std::string what (){
			return message;
		}
	};

	class FileErrorException : public std::exception {
	private:
		std::string message;

	public:
		explicit FileErrorException(std::string msg="File already exists"): message(std::move(msg)){}
		std::string what(){
			return message;
		}
	};

	class NameErrorException : public std::exception {
	private:
        std::string message;

	public:
		explicit NameErrorException(std::string msg = "Name is empty. Please set a name "
									  "with the setName() function."): message
									  (std::move(msg)){}
        std::string what(){
			return message;
		}
	};

private:
	std::string name;
	std::string basePath;
	nlohmann::json data;

// methods
public:


    void save(const std::string& name);

    void save();

    nlohmann::json load(const std::string& path);

    nlohmann::json get(const std::string& key);

    void remove(const std::string& key);

    void purge();

    void create(const std::string& name);

    void create();

    // Template functions
    /*
    template<typename S> void search(S search);

    template <typename U> void update(std::string key, U value);
*/
    //template <typename A> void add(const std::string& key, A value);


    /// <BR><h3>Adds a value to a json object or updates it if it already exists</h3>
/// \param key The key of the value
/// \param value The value
/// \typeparam \b T The type of the value
    template<typename T>
    void addOrIfExistentUpdate(const std::string& key, T value) {
        // Check if the key already exists
        if(this->data.contains(key)){
            update(key, value);
        }else{
            this->data[key] = value;
        }
    }


    //!!! https://stackoverflow.com/questions/495021/why-can-templates-only-be-implemented-in-the-header-file
    // template is easiest to use with header file declaration. Cpp-declaration does not work for template types.
    /// <BR><h3>Adds a value to a json object</h3>
/// \param key The key of the value
/// \param value The value
/// \typeparam \b T The type of the value
    template<typename T>
    void add(const std::string& key, T value) {
        // Check if the key already exists
        if(this->data.contains(key)){
            throw std::runtime_error("Key already exists. Use the update function to "
                                     "update the value.");
        }else{
            this->data[key] = value;
        }
    }

    /*
    void add(const std::string& key, std::string value);
    void add(const std::string& key, int value);
    void add(const std::string& key, double value);
    void add(const std::string& key, bool value);

    void add(const std::string& key, nlohmann::json value);
    */

    void search(const std::string& search, bool key);
    void search(const std::regex& search, bool key);



/// <BR><h3>Updates a value in a json object</h3>
/// \param key The key of the value
/// \param value The new value
/// \typeparam \b U The type of the value
    template<typename U> void
    update(std::string key, U value ) {
        // Check if the key exists
        if (this->data.contains(key)) {
            this->data[key] = value;
        }else{
            throw std::runtime_error("Key does not exist");
        }
    }

    /*
void update(const std::string& key, const std::string& value);
void update(const std::string& key, int value);
void update(const std::string& key, double value);
void update(const std::string& key, bool value);
void update(const std::string& key, const nlohmann::json& value);
*/


/// <BR><h3>Searches for a value in a json object</h3>
/// \param key The key of the value (string or regex)
/// \typeparam \b S The type of the value (string or regex)
template<typename S> void search(S search) {
	assert(typeid(search) == typeid(std::string) || typeid(search) == typeid(std::regex));

	int counter = 0;

	if(typeid(search) == typeid(std::string)){
		for (auto& element : this->data.items()) {
			if(element.value() == search){
                std::cout << "[Found] " << element.key() << " : " << element.value()
				<< std::endl;
				counter++;
			}
		}
	}else if(typeid(search) == typeid(std::regex)){
		for (auto& element : this->data.items()) {
			if(regex_search(element.value(), search)){
                std::cout << "[Found] " << element.key() << " : " << element.value()
				<< std::endl;
				counter++;
			}
		}
	}else{
		throw std::runtime_error("Invalid search type");
	}

	if(counter == 0){
		std::cout << "No results found" << std::endl;
	}
}

};

#endif //NP_SEMESTERPROJEKT_PERSISTENTFILEMANAGEMENT_HPP
