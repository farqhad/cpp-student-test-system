#include "student.h"
#include <iostream>
#include <functional>

std::fstream student::studentsFile;

std::vector<student> student::students;

std::hash<std::string> student::hashThePassword;

student::student() = default;

student::student(std::string& name, std::string& surname, std::string& login, std::string& password, std::string& phoneNum) {	
	this->name = name;
	this->surname = surname;
	this->login = login;
	this->password = password;
	this->hashedPassword = hashThePassword(password);
	this->phoneNum = phoneNum;

	students.push_back(*this);

	saveData();
}

void student::getStudents() {
		for (int i = 0; i < students.size(); ++i) {
			std::cout << '\n' << students[i].hashedPassword << '\n';
		}
}

void student::serialization(std::ostream& fileStream) const { // converts from std::string to cstring type and writes to a binary file	
	size_t takenTestsAmount = takenTests.size();
	fileStream.write(reinterpret_cast<const char*>(&takenTestsAmount), sizeof(takenTestsAmount));
	
	for (test eachTest : takenTests) {
		eachTest.testSerialization(fileStream);
	}

	size_t takenTestResultsAmount = takenTestResults.size();
	fileStream.write(reinterpret_cast<const char*>(&takenTestResultsAmount), sizeof(takenTestResultsAmount));


	for (int result : takenTestResults) {
		fileStream.write(reinterpret_cast<const char*>(&result), sizeof(result));
	}

	fileStream.write(name.c_str(), name.size() + 1);
	fileStream.write(surname.c_str(), surname.size() + 1);
	fileStream.write(login.c_str(), login.size() + 1);
	fileStream.write(phoneNum.c_str(), phoneNum.size() + 1);
	fileStream.write(reinterpret_cast<const char*>(&hashedPassword), sizeof(hashedPassword));
}

void student::deserialization(std::istream& fileStream) {
	size_t takenTestsAmount;
	fileStream.read(reinterpret_cast<char*>(&takenTestsAmount), sizeof(takenTestsAmount));

	for (int i = 0; i < takenTestsAmount; ++i) {
		if (takenTestsAmount < 100) {
			test eachTest;
			eachTest.testDeserialization(fileStream);
			takenTests.push_back(eachTest);
		}
		else {
			return;
		}
	}

	size_t takenTestResultsAmount;
	fileStream.read(reinterpret_cast<char*>(&takenTestResultsAmount), sizeof(takenTestResultsAmount));
	
	for (int i = 0; i < takenTestResultsAmount; ++i) {
		if (takenTestResultsAmount < 100) {
			int result;
			fileStream.read(reinterpret_cast<char*>(&result), sizeof(result));
			takenTestResults.push_back(result);
		}
		else {
			return;
		}
	}

	std::getline(fileStream, name, '\0');
	std::getline(fileStream, surname, '\0');
	std::getline(fileStream, login, '\0');
	std::getline(fileStream, phoneNum, '\0');
	fileStream.read(reinterpret_cast<char*>(&hashedPassword), sizeof(hashedPassword));
}

void student::saveData() {
	studentsFile.open(R"(studentDataBase\students.bin)", std::ios::out | std::ios::binary);

	for (const student& temp : students) {
		if (studentsFile.is_open()) {
			temp.serialization(studentsFile);
		}
		else {
			std::cerr << "\n\n ERROR OPENING THE FILE! \n\n";
		}
	}

	studentsFile.close();
}

void student::loadData() {
	studentsFile.open(R"(studentDataBase\students.bin)", std::ios::in | std::ios::binary);

	if (studentsFile.tellg() == 0) {
		if (!studentsFile.is_open()) {
			std::cerr << "\n\n ERROR OPENING THE FILE \n\n";
		}

		studentsFile.seekg(0);

		while (!studentsFile.eof()) {
			student temp;
			temp.deserialization(studentsFile);
			students.push_back(temp);
		}

		studentsFile.close();
	}
}