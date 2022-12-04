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
	/// Creates a new PersistentFileManagement object
	/// \param path The path to the file (optional)
	explicit PersistentFileManagement(const std::string& name);

	PersistentFileManagement();

	// Destructor
	~PersistentFileManagement();

	void save(const std::string& name);
	void save();
	nlohmann::json load(const std::string& path);
	nlohmann::json get(std::string
	key);

	template <typename T> void add(const std::string& key, const T& value);

	void remove(const std::string& key);

	template <typename T> void update(const std::string& key, const T& value);

	void create(const std::string& name);

	void create();

	template<typename T> void search(const T search);

	//Getter
	nlohmann::json getData();

	//Setter
	void setName(const std::string_view &name);

private:
	std::string name;
	std::string basePath;
	nlohmann::json data;
};

#endif //NP_SEMESTERPROJEKT_JSON_HPP
