#pragma once
#include "answer.h"
#include <vector>

struct ask {
	std::string question;
	int answerAmount;

	std::vector<answer> answers;

public:
	ask();
	ask(std::string question, int answerAmount);
	void addAnAnswer(answer ans);
};