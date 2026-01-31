#pragma once
#include <string>
#include <fstream>

class teacher {
	friend struct interface;

	std::string login;
	std::string password;
	size_t hashedPassword;

	static std::hash<std::string> hashThePassword;
	static bool flag;
	static std::fstream adminFile;

	static teacher theAdmin;

public:
	teacher();
	teacher(std::string login, std::string password);
	static bool flagFileCheck();
	void serialization(std::ostream& fileStream) const; // converts from std::string to cstring type and writes to a binary file
	void deserialization(std::istream& fileStream); // reads from a binary file and converts back from cstring type to std:string
	static void saveData();
	static void loadData();
};