//
// Created by erikn on 29.11.2022.
//

#ifndef NP_SEMESTERPROJEKT_PERSISTENTFILEMANAGEMENT_HPP
#define NP_SEMESTERPROJEKT_PERSISTENTFILEMANAGEMENT_HPP

#include <fstream>
#include <regex>
#include "../../_deps/json-src/single_include/nlohmann/json.hpp"

class PersistentFileManagement {
public:
	// Constructor
	explicit PersistentFileManagement(std::string name);

	PersistentFileManagement();

	// Destructor
	~PersistentFileManagement();

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

	template <typename A> void add(std::string key, A value);*/

	void search(const std::string& search, bool key);
	void search(const std::regex& search, bool key);

	void update(const std::string& key, const std::string& value);
	void update(const std::string& key, int value);
	void update(const std::string& key, double value);
	void update(const std::string& key, bool value);
	void update(const std::string& key, nlohmann::json value);

	void add(const std::string& key, std::string value);
	void add(const std::string& key, int value);
	void add(const std::string& key, double value);
	void add(const std::string& key, bool value);
	void add(const std::string& key, nlohmann::json value);

	//Getter
	nlohmann::json getData();

	//Setter
	void setName(const std::string& name);

	//Exceptions
	class KeyErrorException : public std::exception {
	private:
		char * message;

	public:
		explicit KeyErrorException(char * msg="Key does not exist"): message(msg){}
		char * what (){
			return message;
		}
	};

	class FileErrorException : public std::exception {
	private:
		char * message;

	public:
		explicit FileErrorException(char * msg="File already exists"): message(msg){}
		char * what(){
			return message;
		}
	};

	class NameErrorException : public std::exception {
	private:
		char * message;

	public:
		explicit NameErrorException(char * msg="Name is empty. Please set a name "
									  "with the setName() function."): message
									  (msg){}
		char * what(){
			return message;
		}
	};

private:
	std::string name;
	std::string basePath;
	nlohmann::json data;
};

#endif //NP_SEMESTERPROJEKT_PERSISTENTFILEMANAGEMENT_HPP
