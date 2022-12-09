//
// Created by erikn on 29.11.2022.
//

#ifndef NP_SEMESTERPROJEKT_JSON_HPP
#define NP_SEMESTERPROJEKT_JSON_HPP

#include <nlohmann/json.hpp>
#include <fstream>
#include <regex>

class PersistentFileManagement {
public:
	// Constructor
	explicit PersistentFileManagement(std::string name);

	PersistentFileManagement();

	// Destructor
	~PersistentFileManagement();

	void save(std::string name);

	void save();

	nlohmann::json load(std::string path);

	nlohmann::json get(std::string key);

	void remove(std::string key);

	void purge();

	void create(std::string name);

	void create();

	// Template functions
	/*
	template<typename S> void search(S search);

	template <typename U> void update(std::string key, U value);

	template <typename A> void add(std::string key, A value);*/

	void search(std::string search, bool key);
	void search(std::regex search, bool key);

	void update(std::string key, std::string value);
	void update(std::string key, int value);
	void update(std::string key, double value);
	void update(std::string key, bool value);
	void update(std::string key, nlohmann::json value);

	void add(std::string key, std::string value);
	void add(std::string key, int value);
	void add(std::string key, double value);
	void add(std::string key, bool value);
	void add(std::string key, nlohmann::json value);

	//Getter
	nlohmann::json getData();

	//Setter
	void setName(std::string name);

	//Exceptions
	class KeyErrorException : public std::exception {
	private:
		char * message;

	public:
		KeyErrorException(char * msg="Key does not exist"): message(msg){}
		char * what (){
			return message;
		}
	};

	class FileErrorException : public std::exception {
	private:
		char * message;

	public:
		FileErrorException(char * msg="File already exists"): message(msg){}
		char * what(){
			return message;
		}
	};

	class NameErrorException : public std::exception {
	private:
		char * message;

	public:
		NameErrorException(char * msg="Name is empty. Please set a name "
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

#endif //NP_SEMESTERPROJEKT_JSON_HPP
