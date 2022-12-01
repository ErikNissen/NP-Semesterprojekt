//
// Created by erikn on 29.11.2022.
//

#ifndef NP_SEMESTERPROJEKT_JSON_HPP
#define NP_SEMESTERPROJEKT_JSON_HPP

#include <nlohmann/json.hpp>
#include <fstream>

class PersistentFileManagement {
public:
	// Constructor
	/// Creates a new PersistentFileManagement object
	/// \param path The path to the file (optional)
	PersistentFileManagement(const std::string& name);

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

	//Getter
	nlohmann::json getData();

	//Setter
	void setName(const std::string& name);

protected:
	nlohmann::json data;
private:
	std::string name;
	std::string basePath;
};

#endif //NP_SEMESTERPROJEKT_JSON_HPP
