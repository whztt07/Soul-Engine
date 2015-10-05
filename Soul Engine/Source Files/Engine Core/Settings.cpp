#include "Settings.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <cstdio>
//takes an .ini filename
Settings::Settings(std::string file){
	fileName = file;
	std::ifstream infile(fileName);
	if (!infile.is_open()){
		std::ofstream outfile(fileName);
		outfile.close();
		infile.open(fileName);
	}

	std::string line;
	while (std::getline(infile, line))
	{
		std::istringstream iss(line);
		std::string a, b;
		if (!(iss >> a >> b)) { 
			std::cerr << "Couldn't read line in " + fileName << std::endl;
		} 

		values.insert(std::make_pair(a, b));
	}
	infile.close();
}
//Returns a string with the value at 'Setting'. If one does not exist, this 
//returns an empty string. Remember to have a default case for this instance!
std::string Settings::Retrieve(std::string setting){

	std::map<std::string, std::string>::const_iterator itr = values.find(setting);
	if (itr != values.end()){
		return itr->second;
	}
	else{
		return "";
	}
}
//Inserts the value at setting. If a setting already exists, value replaces it
void Settings::Set(std::string setting, std::string value){

	if (values.insert(std::make_pair(setting, value)).second==true){
	}
	else{
		values.find(setting)->second = value;
	}
	Update();
}
void Settings::Update(){

	remove(fileName.c_str());

	std::ofstream outfile(fileName);

	for (std::map<std::string, std::string>::iterator itr = values.begin();
		itr != values.end(); itr++) {
		outfile << itr->first << " " << itr->second << std::endl;
	}

	outfile.close();
}