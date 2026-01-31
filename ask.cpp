#include "ask.h"

ask::ask() : answerAmount(0) {}

ask::ask(std::string question, int answerAmount) {
	this->question = question;
	this->answerAmount = answerAmount;
}

void ask::addAnAnswer(answer ans) {
	answers.push_back(ans);
}