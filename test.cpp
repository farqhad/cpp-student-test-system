#include "test.h"
#include <fstream>
#include <iostream>

std::fstream test::testsFile;
std::vector<test> test::tests;

test::test() : questionAmount(0) {}

test::test(std::string subject, std::string testName, int questionAmount, std::vector<ask> asks) {
	this->subject = subject;
	this->testName = testName;
	this->questionAmount = questionAmount;
	this->asks = asks;

	tests.push_back(*this);

	saveData();
}

void test::addAnAsk(ask newAsk) {
	asks.push_back(newAsk);
}

void test::testSerialization(std::ostream& fileStream) const {
	// subject, testName, questionAmount
	
	fileStream.write(subject.c_str(), subject.size() + 1);
	fileStream.write(testName.c_str(), testName.size() + 1);
	fileStream.write(reinterpret_cast<const char*>(&questionAmount), sizeof(questionAmount));

	
	// number of asks

	size_t askAmount = asks.size();
	fileStream.write(reinterpret_cast<const char*>(&askAmount), sizeof(askAmount));


	// asks
	
	for (const auto& eachAsk : asks) {
		askSerialization(fileStream, eachAsk);
	}
}

void test::askSerialization(std::ostream& fileStream, const ask& eachAsk) const {
	// question, answerAmount

	fileStream.write(eachAsk.question.c_str(), eachAsk.question.size() + 1);
	fileStream.write(reinterpret_cast<const char*>(&eachAsk.answerAmount), sizeof(eachAsk.answerAmount));


	// number of answers
	
	size_t numAnswers = eachAsk.answers.size();
	fileStream.write(reinterpret_cast<const char*>(&numAnswers), sizeof(numAnswers));

	
	// answers

	for (const auto& eachAnswer : eachAsk.answers) {
		answerSerialization(fileStream, eachAnswer);
	}
}

void test::answerSerialization(std::ostream& fileStream, const answer& eachAns) const {
	// theAnswer, right, wrong

	fileStream.write(eachAns.theAnswer.c_str(), eachAns.theAnswer.size() + 1);
	fileStream.write(reinterpret_cast<const char*>(&eachAns.right), sizeof(eachAns.right));
	fileStream.write(reinterpret_cast<const char*>(&eachAns.wrong), sizeof(eachAns.wrong));
}

void test::testDeserialization(std::istream& fileStream) {
	// subject, testName, questionAmount

	std::getline(fileStream, subject, '\0');
	std::getline(fileStream, testName, '\0');
	fileStream.read(reinterpret_cast<char*>(&questionAmount), sizeof(questionAmount));


	// number of asks
	
	size_t askAmount;
	fileStream.read(reinterpret_cast<char*>(&askAmount), sizeof(askAmount));


	// asks

	asks.clear();
	for (size_t i = 0; i < askAmount; ++i) {
		if (askAmount < 100) { // for when askAmount is trash from memory like 89723894729324
			ask eachAsk;
			askDeserialization(fileStream, eachAsk);
			asks.push_back(eachAsk);
		}
		else {
			return;
		}
	}
}

void test::askDeserialization(std::istream& fileStream, ask& eachAsk) {
	// question, answerAmount
	
	std::getline(fileStream, eachAsk.question, '\0');
	fileStream.read(reinterpret_cast<char*>(&eachAsk.answerAmount), sizeof(eachAsk.answerAmount));


	// number of answers

	size_t answerAmount;
	fileStream.read(reinterpret_cast<char*>(&answerAmount), sizeof(answerAmount));


	// answers

	eachAsk.answers.clear();
	for (size_t i = 0; i < answerAmount; ++i) {
		if (answerAmount < 100) { // for when askAmount is trash from memory like 89723894729324
			answer ans;
			answerDeserialization(fileStream, ans);
			eachAsk.answers.push_back(ans);
		}
		else {
			return;
		}
	}
}

void test::answerDeserialization(std::istream& fileStream, answer& eachAns) {
	// theAnswer, right, wrong

	std::getline(fileStream, eachAns.theAnswer, '\0');
	fileStream.read(reinterpret_cast<char*>(&eachAns.right), sizeof(eachAns.right));
	fileStream.read(reinterpret_cast<char*>(&eachAns.wrong), sizeof(eachAns.wrong));
}


void test::saveData() {
	testsFile.open(R"(testDataBase\tests.bin)", std::ios::out | std::ios::binary);

	if (!testsFile.is_open()) {
		std::cerr << "Failed to open file!\n";
		return;
	}

	size_t testAmount = tests.size();
	testsFile.write(reinterpret_cast<const char*>(&testAmount), sizeof(testAmount));

	for (const test& t : tests) {
		t.testSerialization(testsFile);
	}

	testsFile.close();
}

void test::loadData() {
	testsFile.open(R"(testDataBase\tests.bin)", std::ios::in | std::ios::binary);
	
	if (!testsFile.is_open()) {
		std::cerr << "Failed to open file!\n";
		return;
	}

	size_t testAmount;
	testsFile.read(reinterpret_cast<char*>(&testAmount), sizeof(testAmount));

	tests.clear();
	for (size_t i = 0; i < testAmount; ++i) {
		if (testsFile.eof()) {
			break;
		}
		
		test t;
		t.testDeserialization(testsFile);
		tests.push_back(t);
	}

	testsFile.close();
}