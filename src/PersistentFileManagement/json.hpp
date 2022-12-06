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

	void create(std::string name);

	void create();

	// Template functions
	template<typename S> void search(S search);

	template <typename U> void update(std::string key, U value);

	template <typename A> void add(std::string key, A value);

	//Getter
	nlohmann::json getData();

	//Setter
	void setName(std::string name);

private:
	std::string name;
	std::string basePath;
	nlohmann::json data;
};

#endif //NP_SEMESTERPROJEKT_JSON_HPP
