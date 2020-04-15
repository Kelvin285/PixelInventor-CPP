#pragma once
#include <unordered_map>
#include <string>
#include <fstream>
#include <filesystem>
#include <iostream>
#include <vector>
#include "Utils.h"

class Translation
{
public:
	static Translation* currentTranslation;
	static std::unordered_map<std::string, Translation> translations;
	
	std::string translate(std::string input);
	static std::string translateText(std::string input);

	static void loadTranslations(std::string modid);
	static void setTranslation(std::string translation);
private:
	std::unordered_map<std::string, std::string> keys;
};

