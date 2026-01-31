#include "teacher.h"
#include <fstream>
#include <iostream>

std::hash<std::string> teacher::hashThePassword;
bool teacher::flag;
std::fstream teacher::adminFile;
teacher teacher::theAdmin;

teacher::teacher() = default;

teacher::teacher(std::string login, std::string password) {
	this->login = login;
	this->password = password;
	this->hashedPassword = hashThePassword(password);

	theAdmin = *this;

	saveData();
}

bool teacher::flagFileCheck() {
	std::fstream flagFile(R"(teacherDataBase\flag.bin)");
	
	return flagFile.is_open();
}

void teacher::serialization(std::ostream& fileStream) const { // converts from std::string to cstring type and writes to a binary file
	fileStream.write(login.c_str(), login.size() + 1);
	fileStream.write(reinterpret_cast<const char*>(&hashedPassword), sizeof(hashedPassword));	
}

void teacher::deserialization(std::istream& fileStream) {
	std::getline(fileStream, login, '\0');
	fileStream.read(reinterpret_cast<char*>(&hashedPassword), sizeof(hashedPassword));
}

void teacher::saveData() {
	adminFile.open(R"(teacherDataBase\teacher.bin)", std::ios::out | std::ios::binary);

	if (adminFile.is_open()) {
		theAdmin.serialization(adminFile);
	}
	else {
		std::cerr << "\n\n ERROR OPENING THE FILE! \n\n";
	}

	adminFile.close();
}

void teacher::loadData() {
	adminFile.open(R"(teacherDataBase\teacher.bin)", std::ios::in | std::ios::binary);

	if (adminFile.is_open()) {
		theAdmin.deserialization(adminFile);
	}
	else {
		std::cerr << "\n\n ERROR OPENING THE FILE! \n\n";
	}

	adminFile.close();
}