//
// Created by erikn on 29.11.2022.
//

#ifndef NP_SEMESTERPROJEKT_JSON_HPP
#define NP_SEMESTERPROJEKT_JSON_HPP

#include <nlohmann/json.hpp>

class PersistentFileManagement {
public:
	static void save(nlohmann::json &json, const std::string& path);
	static nlohmann::json load(const std::string& path);
	static nlohmann::json get(nlohmann::json &dict, std::string
	key);
	static void add(nlohmann::json &dict, const std::string& key,
						const std::string& value);
	static void add(nlohmann::json &dict, const std::string& key,
						int value);
	static void add(nlohmann::json &dict, const std::string& key, bool
	value);
	static void add(nlohmann::json &dict, const std::string& key,
						double value);
	static void add(nlohmann::json &dict, const std::string& key,
						float value);
	static void add(nlohmann::json &dict, const std::string& key,
						char value);

	static void remove(nlohmann::json &dict, const std::string& key);

	static void update(nlohmann::json &dict, const std::string& key,
						const std::string& value);
	static void update(nlohmann::json &dict, const std::string& key,
						int value);
	static void update(nlohmann::json &dict, const std::string& key,
						bool value);
	static void update(nlohmann::json &dict, const std::string& key,
					   double value);
	static void update(nlohmann::json &dict, const std::string& key,
						float value);
	static void update(nlohmann::json &dict, const std::string&
	key,    char value);

	static std::string create(const std::string& path);

protected:
	nlohmann::json data;
	static const std::string basePath;
};

#endif //NP_SEMESTERPROJEKT_JSON_HPP
