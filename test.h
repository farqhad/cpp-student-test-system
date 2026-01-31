#pragma once
#include <string>
#include <vector>
#include <fstream>
#include "ask.h"
#include "answer.h"

class test {
	friend class student;
	friend struct interface;

	std::string subject;
	std::string testName;
	int questionAmount;

	std::vector<ask> asks;

	static std::vector<test> tests;
	static std::fstream testsFile;

public:
	test();
	test(std::string subject, std::string testName, int questionAmount, std::vector<ask> asks);

	void addAnAsk(ask newAsk);

	void testSerialization(std::ostream& fileStream) const; // converts from std::string to cstring type and writes to a binary file
	void testDeserialization(std::istream& fileStream); // reads from a binary file and converts back from cstring type to std:string
	
	void askSerialization(std::ostream& fileStream, const ask& eachAsk) const; // converts from std::string to cstring type and writes to a binary file
	void askDeserialization(std::istream& fileStream, ask& eachAsk); // reads from a binary file and converts back from cstring type to std:string
	
	void answerSerialization(std::ostream& fileStream, const answer& eachAns) const; // converts from std::string to cstring type and writes to a binary file
	void answerDeserialization(std::istream& fileStream, answer& eachAns); // reads from a binary file and converts back from cstring type to std:string	
	
	static void saveData();
	static void loadData();
};