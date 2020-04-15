#include "Translation.h"

namespace fs = std::filesystem;

Translation* Translation::currentTranslation = nullptr;
std::unordered_map<std::string, Translation> Translation::translations;

std::string Translation::translate(std::string input) {
	if (keys.count(input) > 0) {
		return keys[input];
	}
	return input;
}

std::string Translation::translateText(std::string input) {
	if (currentTranslation == nullptr) return input;
	setTranslation("");
	if (currentTranslation == nullptr) return input;
	return currentTranslation->translate(input);
}

void Translation::loadTranslations(std::string modid) {
	std::string path("assets/"+modid+"/translations/");
	if (!fs::exists(path)) fs::create_directories(path);

	for (const auto& entry : fs::directory_iterator(path))
	{
		Translation translation;
		std::ifstream t(entry.path());
		std::string str((std::istreambuf_iterator<char>(t)),
			std::istreambuf_iterator<char>());

		std::string s = "";
		for (size_t i = 0; i < str.length(); i++) {
			if (str[i] == '\n' || i == str.length() - 1) {
				std::vector<std::string> data = Utils::split(s, '=');

				if (data.size() == 2) {
					bool start = false;
					std::string a = "";
					std::string b = "";

					for (size_t j = 0; j < data[0].length(); j++) {
						char c = data[0][j];
						if (start && c == '"') break;
						if (start) a += c;
						if (c == '"') start = true;
					}

					start = false;

					for (size_t j = 0; j < data[0].length(); j++) {
						char c = data[0][j];
						if (start && c == '"') break;
						if (start) b += c;
						if (c == '"') start = true;
					}

					if (!a.empty() && !b.empty()) {
						std::pair<std::string, std::string> pair(a, b);
						translation.keys.insert(pair);
					}
				}

				s = "";
			}
			else {
				s += str[i];
			}
		}
		std::string name = entry.path().filename().string();
		Utils::replace(&name, ".txt", "");
		std::pair<std::string, Translation> pair(name, translation);
		translations.insert(pair);
	}
	setTranslation("english");
}

void Translation::setTranslation(std::string translation) {
	for (auto it : translations) {
		if (it.first == translation) {
			currentTranslation = &it.second;
			std::cout << "Translation set to " << it.first << std::endl;
			return;
		}
	}
	for (auto it : translations) {
		currentTranslation = &it.second;
		if (translation == "") {
			std::cout << "No translation loaded currently.  Setting translation to the first translation file found: " << it.first << std::endl;
		}
		else {
			std::cout << "Couldn't find translation " << translation << ". Setting to " << it.first << " instead." << std::endl;
		}
		return;
	}
}