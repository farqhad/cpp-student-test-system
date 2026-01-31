#pragma once
#include "student.h"
#include "teacher.h"
#include "test.h"
#include "ask.h"
#include "answer.h"

struct interface {
	friend class test;
	friend struct answer;
	friend struct ask;

	static void mainMenu();
	static void studentMainMenu();
	static void studentSignUp();
	static void studentSignIn();
	static void studentMenu(student);
	static void teacherSignUp();
	static void teacherSignIn();
	static void teacherMenu(teacher);
};