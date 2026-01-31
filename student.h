#pragma once
#include <string>
#include <fstream>
#include <vector>
#include "test.h"

class student {
private:
	friend class test;
	friend struct interface;
	friend bool isUsed(std::string login);

	std::string name;
	std::string surname;
	std::string login;
	std::string password;
	size_t hashedPassword;
	std::string phoneNum;

	std::vector<test> takenTests;
	std::vector<int> takenTestResults;

	static std::hash<std::string> hashThePassword;

	static std::fstream studentsFile;

	static std::vector<student> students;
	

public:
	student();
	student(std::string& name, std::string& surname, std::string& login, std::string& password, std::string& phoneNum);
	
	static void getStudents();
	void serialization(std::ostream& fileStream) const; // converts from std::string to cstring type and writes to a binary file
	void deserialization(std::istream& fileStream); // reads from a binary file and converts back from cstring type to std:string
	static void saveData();
	static void loadData();
};