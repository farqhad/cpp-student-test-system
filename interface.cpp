#include <iostream>
#include <conio.h>
#include <string>
#define WIN32_LEAN_AND_MEAN // to avoid syntax errors when including windows.h
#include <windows.h>
#include "interface.h"


bool isUsed(std::string login) {
	for (int i = 0; i < student::students.size(); ++i) {
		if (login == student::students[i].login) {
			return true;
		}
	}
	return false;
}

void interface::mainMenu() {
	system("cls");
	std::cout << "\t\tWelcome!\n";

	std::cout << "1. I'm a student (guest)\n";
	std::cout << "2. I'm a teacher (admin)\n";
	std::cout << "3. Exit\n";

	char userChoice = _getch();

	if (userChoice == '1') {
		studentMainMenu();
	}
	else if (userChoice == '2') {
		if (!teacher::flagFileCheck()) {
			teacherSignUp();
		}
		else {
			teacherSignIn();
		}
	}
	else if (userChoice == '3') {
		return;
	}
	else {
		mainMenu();
	}
}


void interface::studentMainMenu() {
	system("cls");
	std::cout << "\t\tWelcome!\n";

	std::cout << "1. Sign Up\n";
	std::cout << "2. Sign In\n";
	std::cout << "3. Back to Main Menu\n";
	std::cout << "4. Exit\n";

	char userChoice = _getch();

	if (userChoice == '1') {
		studentSignUp();
	}
	else if (userChoice == '2') {
		studentSignIn();
	}
	else if (userChoice == '3') {
		mainMenu();
	}
	else if (userChoice == '4') {
		return;
	}
	else {
		studentMainMenu();
	}
}

void interface::teacherSignUp() {
	while (true) {
		system("cls");

		std::string login;
		std::string password;
		std::string passwordVerification;

		std::cout << "\t\tRegistration:";
		std::cout << "\t\t(Enter 0 to exit to main menu)\n\n";

		std::cout << "Username: ";
		std::getline(std::cin, login);

		if (login == "0") {
			mainMenu();
			return;
		}

		HANDLE hStdin = GetStdHandle(STD_INPUT_HANDLE);       //
		DWORD mode = 0;                                       // to make the input
		GetConsoleMode(hStdin, &mode);                        // invisible (for the password)
		SetConsoleMode(hStdin, mode & (~ENABLE_ECHO_INPUT));  //

		std::cout << "Password(you won't see it): ";
		std::getline(std::cin, password);

		if (password == "0") {
			mainMenu();
			return;
		}
		else if (password.size() < 8) {
			std::cerr << "\n\nThe password is too weak! It must be 8 characters or more!\n\n";
			Sleep(3000);
			continue;
		}

		std::cout << '\n';

		std::cout << "Verify the password: ";
		std::getline(std::cin, passwordVerification);

		if (passwordVerification == "0") {
			mainMenu();
			return;
		}
		else if (password != passwordVerification) {
			std::cerr << "\n\nPasswords are not the same!\n\n";
			Sleep(2000);
			continue;
		}

		SetConsoleMode(hStdin, mode); // to make the input visible again
		std::cout << '\n';

		teacher newTeacher{ login, password };

		std::fstream flagFile(R"(teacherDataBase\flag.bin)", std::ios::out | std::ios::binary);

		teacherMenu(newTeacher);

		break;
	}
}

void interface::studentSignUp() {
	while (true) {
		system("cls");

		std::string realName;
		std::string surname;
		std::string login;
		std::string password;
		std::string passwordVerification;
		std::string phoneNumber;


		std::cout << "\t\tRegistration:";
		std::cout << "\t\t(Enter 0 to exit to main menu)\n\n";

		std::cout << "First Name: ";
		std::getline(std::cin, realName);

		if (realName == "0") {
			studentMainMenu();
			return;
		}

		std::cout << "Last Name: ";
		std::getline(std::cin, surname);

		if (surname == "0") {
			studentMainMenu();
			return;
		}

		std::cout << "Username: ";
		std::getline(std::cin, login);

		if (login == "0") {
			studentMainMenu();
			return;
		}
		else if (isUsed(login)) {
			std::cerr << "\n\nUsername already taken!!!\n\n";
			Sleep(2000);
			continue;
		}

		HANDLE hStdin = GetStdHandle(STD_INPUT_HANDLE);       //
		DWORD mode = 0;                                       // to make the input
		GetConsoleMode(hStdin, &mode);                        // invisible (for the password)
		SetConsoleMode(hStdin, mode & (~ENABLE_ECHO_INPUT));  //

		std::cout << "Password(you won't see it): ";
		std::getline(std::cin, password);

		if (password == "0") {
			studentMainMenu();
			return;
		}
		else if (password.size() < 8) {
			std::cerr << "\n\nThe password is too weak! It must be 8 characters or more!\n\n";
			Sleep(3000);
			continue;
		}

		std::cout << '\n';

		std::cout << "Verify the password: ";
		std::getline(std::cin, passwordVerification);

		if (passwordVerification == "0") {
			studentMainMenu();
			return;
		}
		else if (password != passwordVerification) {
			std::cerr << "\n\nPasswords are not the same!\n\n";
			Sleep(2000);
			continue;
		}

		SetConsoleMode(hStdin, mode); // to make the input visible again
		std::cout << '\n';

		std::cout << "Phone Number(no spaces): ";
		std::getline(std::cin, phoneNumber);

		if (phoneNumber == "0") {
			studentMainMenu();
			return;
		}
		else if (phoneNumber.length() > 15) {
			std::cerr << "\n\nMaximum length of the phone number is 15 digits!!!\n";
			Sleep(2000);
			continue;
		}

		student newStudent{ realName, surname, login, password, phoneNumber };

		studentMenu(newStudent);

		break;
	}
}

void interface::teacherSignIn() {
	system("cls");

	std::string login;
	std::string password;

	std::cout << "\t\tLog In:";
	std::cout << "\t\t(Enter 0 to exit to main menu)\n\n";

	std::cout << "username: ";
	std::getline(std::cin, login);

	if (login == "0") {
		mainMenu();
		return;
	}

	std::cout << '\n';

	HANDLE hStdin = GetStdHandle(STD_INPUT_HANDLE);       //
	DWORD mode = 0;                                       // to make the input
	GetConsoleMode(hStdin, &mode);                        // invisible (for the password)
	SetConsoleMode(hStdin, mode & (~ENABLE_ECHO_INPUT));  //

	std::cout << "password(you won't see it): ";
	std::getline(std::cin, password);

	SetConsoleMode(hStdin, mode); // to make the input visible again

	if (password == "0") {
		mainMenu();
		return;
	}


	if (teacher::theAdmin.login == login && teacher::theAdmin.hashedPassword == teacher::hashThePassword(password)) {
		teacherMenu(teacher::theAdmin);
		return;
	}

	std::cerr << "\n\nWrong credentials!\n\n";
	Sleep(2000);
	mainMenu();
}

void interface::studentSignIn() {
	system("cls");

	std::string login;
	std::string password;

	std::cout << "\t\tLog In:";
	std::cout << "\t\t(Enter 0 to exit to main menu)\n\n";

	std::cout << "username: ";
	std::getline(std::cin, login);

	if (login == "0") {
		studentMainMenu();
		return;
	}

	std::cout << '\n';

	HANDLE hStdin = GetStdHandle(STD_INPUT_HANDLE);       //
	DWORD mode = 0;                                       // to make the input
	GetConsoleMode(hStdin, &mode);                        // invisible (for the password)
	SetConsoleMode(hStdin, mode & (~ENABLE_ECHO_INPUT));  //

	std::cout << "password(you won't see it): ";
	std::getline(std::cin, password);

	SetConsoleMode(hStdin, mode); // to make the input visible again

	if (password == "0") {
		studentMainMenu();
		return;
	}

	for (student stud : student::students) {
		if (stud.login == login && stud.hashedPassword == student::hashThePassword(password)) {
			studentMenu(stud);
			return;
		}
	}
	std::cerr << "\n\nUser not found!\n\n";
	Sleep(2000);
	studentMainMenu();
}

void interface::teacherMenu(teacher newTeacher) {
	while (true) {
		system("cls");
		std::cout << "\t\tWelcome, " << newTeacher.login << "!\n";
		std::cout << "1. Create a test\n";
		std::cout << "2. Edit an existing test\n";
		std::cout << "3. Student control panel\n";
		std::cout << "4. Stats\n";
		std::cout << "5. Main menu\n";

		char teacherChoice = _getch();

		if (teacherChoice == '1') {
			system("cls");

			std::string testName;
			std::string subject;
			int questionAmount;
			std::vector<ask> asks;

			std::cout << "Enter a name for the test(enter 0 to go back): ";
			std::getline(std::cin, testName);

			if (testName == "0") {
				continue;
			}
			
			for (int i = 0; i < test::tests.size(); ++i) {
				if (testName == test::tests[i].testName) {
					std::cerr << "\n\n Test Name already taken! \n\n";
					continue;
				}
			}

			std::cout << "Enter the subject of it(enter 0 to go back): ";
			std::getline(std::cin, subject);

			if (subject == "0") {
				continue;
			}

			std::cout << "Enter the number of questions you want to add(enter 0 to go back): ";
			std::cin >> questionAmount;
			std::cin.ignore();

			if (questionAmount == 0) {
				continue;
			}

			std::cout << "\n\n";

			for (int i = 0; i < questionAmount; ++i) {
				std::string question;
				int answerAmount;

				std::cout << "Enter the question #" << i + 1 << ": ";
				std::getline(std::cin, question);

				std::cout << "Enter the number of answers for this question: ";
				std::cin >> answerAmount;
				std::cin.ignore();

				ask thisAsk{ question, answerAmount };

				for (int j = 0; j < answerAmount; ++j) {
					answer thisAsksAns;
					char isRight;

					std::cout << "Enter the answer #" << j + 1 << " to question #" << i + 1 << ": ";
					std::getline(std::cin, thisAsksAns.theAnswer);

					std::cout << "Is this one right?(Y/n): ";
					std::cin >> isRight;
					std::cin.ignore();

					if (isRight == 'y' || isRight == 'Y') {
						thisAsksAns.right = true;
					}
					else if (isRight == 'n' || isRight == 'N') {
						thisAsksAns.wrong = true;
					}
					else {
						std::cerr << "\n\n Enter either y/Y for \"Yes\" or n/N for \"No\"! \n\n";
					}

					thisAsk.addAnAnswer(thisAsksAns);
				}
				asks.push_back(thisAsk);
			}
			test newTest{ subject, testName, questionAmount, asks };

			test::saveData();

			continue;
		}
		else if (teacherChoice == '2') {
			if (test::tests.size() != 0) {
				while (true) {
					system("cls");
					std::cout << "1. Add a question\n";
					std::cout << "2. Delete a question\n";
					std::cout << "3. Modify a question\n";
					std::cout << "4. Back\n";

					char userChoice = _getch();

					if (userChoice == '1') {
						while (true) {
							system("cls");
							std::vector<std::string> subjects;
							std::cout << "Select a subject: \n\n";
							int userChoiceForSubject;

							for (int i = 0; i < test::tests.size(); ++i) {
								if (!std::count(subjects.begin(), subjects.end(), test::tests[i].subject)) {
									subjects.push_back(test::tests[i].subject);
								}

								std::cout << i + 1 << ". " << subjects[i] << "\n\n";
							}

							std::cout << "Enter your choice(enter 0 to go back): ";
							std::cin >> userChoiceForSubject;
							std::cin.ignore();

							if (userChoiceForSubject == 0) {
								break;
							}

							if (userChoiceForSubject <= test::tests.size()) {
								system("cls");
								std::cout << "Select a test: \n\n";

								while (true) {
									std::string subjectToWorkWith = subjects[userChoiceForSubject - 1];
									std::vector<test> testsToWorkWith;
									int userChoiceForTest;

									for (test& eachTest : test::tests) {
										if (eachTest.subject == subjectToWorkWith) {
											testsToWorkWith.push_back(eachTest);
										}
									}
									for (test& eachTestToWorkWith : testsToWorkWith) {
										int i = 1;

										std::cout << i << ". " << eachTestToWorkWith.testName << "\n\n";

										++i;
									}

									std::cout << "Enter your choice(enter 0 to go back): ";
									std::cin >> userChoiceForTest;
									std::cin.ignore();

									test testToWorkWith = testsToWorkWith[userChoiceForTest - 1];

									if (userChoiceForTest <= testsToWorkWith.size()) {
										system("cls");
										std::string newQuestion;
										int answerAmount;

										std::cout << "Enter the question #" << testToWorkWith.questionAmount + 1 << ": ";
										std::getline(std::cin, newQuestion);

										std::cout << "Enter the amount of answers for this question: ";
										std::cin >> answerAmount;
										std::cin.ignore();

										ask newAsk{ newQuestion, answerAmount };

										for (int j = 0; j < answerAmount; ++j) {
											answer newAsksAns;
											char isRight;

											std::cout << "Enter the answer #" << j + 1 << " to the question: ";
											std::getline(std::cin, newAsksAns.theAnswer);

											std::cout << "Is this one right?(Y/n): ";
											std::cin >> isRight;
											std::cin.ignore();

											if (isRight == 'y' || isRight == 'Y') {
												newAsksAns.right = true;
											}
											else if (isRight == 'n' || isRight == 'N') {
												newAsksAns.wrong = true;
											}
											else {
												std::cerr << "\n\n Enter either y/Y for \"Yes\" or n/N for \"No\"! \n\n";
											}

											newAsk.addAnAnswer(newAsksAns);
										}
										testToWorkWith.asks.push_back(newAsk);

										++testToWorkWith.questionAmount;

										for (int i = 0; i < test::tests.size(); ++i) {
											if (test::tests[i].testName == testToWorkWith.testName) {
												test::tests[i] = testToWorkWith;
											}
										}

										test::saveData();

										break;
									}
									else if (userChoiceForTest == 0) {
										break;
									}
									else {
										continue;
									}
								}
							}
							else if (userChoiceForSubject == 0) {
								break;
							}
							else {
								continue;
							}
						}
					}
					else if (userChoice == '2') {
						while (true) {
							system("cls");
							std::vector<std::string> subjects;
							std::cout << "Select a subject: \n\n";
							int userChoiceForSubject;

							for (int i = 0; i < test::tests.size(); ++i) {
								if (!std::count(subjects.begin(), subjects.end(), test::tests[i].subject)) {
									subjects.push_back(test::tests[i].subject);
								}

								std::cout << i + 1 << ". " << subjects[i] << "\n\n";
							}

							std::cout << "Enter your choice(enter 0 to go back): ";
							std::cin >> userChoiceForSubject;
							std::cin.ignore();

							if (userChoiceForSubject == 0) {
								break;
							}

							if (userChoiceForSubject <= test::tests.size()) {
								system("cls");
								std::cout << "Select a test: \n\n";

								while (true) {
									std::string subjectToWorkWith = subjects[userChoiceForSubject - 1];
									std::vector<test> testsToWorkWith;
									int userChoiceForTest;

									for (test& eachTest : test::tests) {
										if (eachTest.subject == subjectToWorkWith) {
											testsToWorkWith.push_back(eachTest);
										}
									}
									for (test& eachTestToWorkWith : testsToWorkWith) {
										int i = 1;

										std::cout << i << ". " << eachTestToWorkWith.testName << "\n\n";

										++i;
									}

									std::cout << "Enter your choice(enter 0 to go back): ";
									std::cin >> userChoiceForTest;
									std::cin.ignore();

									test testToWorkWith = testsToWorkWith[userChoiceForTest - 1];

									if (userChoiceForTest <= testsToWorkWith.size()) {
										system("cls");

										int userChoiceForQuestions;

										std::cout << "Choose a question to delete: \n\n";

										for (int i = 0; i < testToWorkWith.asks.size(); ++i) {
											std::cout << i + 1 << ". " << testToWorkWith.asks[i].question << "\n\n";
										}

										std::cout << "Enter your choice(enter 0 to go back): ";
										std::cin >> userChoiceForQuestions;
										std::cin.ignore();

										if (userChoiceForQuestions <= testToWorkWith.asks.size() && userChoiceForQuestions != 0) {
											testToWorkWith.asks.erase(testToWorkWith.asks.begin() + userChoiceForQuestions - 1);
											--testToWorkWith.questionAmount;

											for (int i = 0; i < test::tests.size(); ++i) {
												if (test::tests[i].testName == testToWorkWith.testName) {
													test::tests[i] = testToWorkWith;
												}
											}

											test::saveData();

											break;
										}
										else if (userChoiceForQuestions == 0) {
											break;
										}
										else {
											continue;
										}
									}
									else if (userChoiceForTest == 0) {
										break;
									}
									else {
										continue;
									}
								}
							}
							else if (userChoiceForSubject == 0) {
								break;
							}
							else {
								continue;
							}
						}
					}
					else if (userChoice == '3') {
						while (true) {
							system("cls");

							std::vector<std::string> subjects;
							std::cout << "Select a subject: \n\n";
							int userChoiceForSubject;

							for (int i = 0; i < test::tests.size(); ++i) {
								if (!std::count(subjects.begin(), subjects.end(), test::tests[i].subject)) {
									subjects.push_back(test::tests[i].subject);
								}

								std::cout << i + 1 << ". " << subjects[i] << "\n\n";
							}

							std::cout << "Enter your choice(enter 0 to go back): ";
							std::cin >> userChoiceForSubject;
							std::cin.ignore();

							if (userChoiceForSubject == 0) {
								break;
							}

							if (userChoiceForSubject <= test::tests.size()) {
								system("cls");
								std::cout << "Select a test: \n\n";

								while (true) {
									std::string subjectToWorkWith = subjects[userChoiceForSubject - 1];
									std::vector<test> testsToWorkWith;
									int userChoiceForTest;

									for (test& eachTest : test::tests) {
										if (eachTest.subject == subjectToWorkWith) {
											testsToWorkWith.push_back(eachTest);
										}
									}
									for (test& eachTestToWorkWith : testsToWorkWith) {
										int i = 1;

										std::cout << i << ". " << eachTestToWorkWith.testName << "\n\n";

										++i;
									}

									std::cout << "Enter your choice(enter 0 to go back): ";
									std::cin >> userChoiceForTest;
									std::cin.ignore();

									test testToWorkWith = testsToWorkWith[userChoiceForTest - 1];

									if (userChoiceForTest <= testsToWorkWith.size()) {
										system("cls");

										int userChoiceForQuestions;

										std::cout << "Choose a question to change: \n\n";

										for (int i = 0; i < testToWorkWith.asks.size(); ++i) {
											std::cout << i + 1 << ". " << testToWorkWith.asks[i].question << "\n\n";
										}

										std::cout << "Enter your choice(enter 0 to go back): ";
										std::cin >> userChoiceForQuestions;
										std::cin.ignore();

										if (userChoiceForQuestions <= testToWorkWith.asks.size() && userChoiceForQuestions != 0) {
											char isRight;
											
											std::cout << "Enter the new question: ";
											std::getline(std::cin, testToWorkWith.asks[userChoiceForQuestions - 1].question);

											for (int i = 0; i < testToWorkWith.asks[userChoiceForQuestions - 1].answers.size(); ++i) {
												std::cout << "Enter the new answer #" << i + 1 << ": ";
												std::getline(std::cin, testToWorkWith.asks[userChoiceForQuestions - 1].answers[i].theAnswer);

												std::cout << "Is this one right?(Y/n): ";
												std::cin >> isRight;
												std::cin.ignore();

												if (isRight == 'y' || isRight == 'Y') {
													testToWorkWith.asks[userChoiceForQuestions - 1].answers[i].right = true;
												}
												else if (isRight == 'n' || isRight == 'N') {
													testToWorkWith.asks[userChoiceForQuestions - 1].answers[i].wrong = true;
												}
												else {
													std::cerr << "\n\n Enter either y/Y for \"Yes\" or n/N for \"No\"! \n\n";
												}
											}

											for (int i = 0; i < test::tests.size(); ++i) {
												if (test::tests[i].testName == testToWorkWith.testName) {
													test::tests[i] = testToWorkWith;
												}
											}

											test::saveData();

											break;
										}
										else if (userChoiceForQuestions == 0) {
											break;
										}
										else {
											continue;
										}
									}
									else if (userChoiceForTest == 0) {
										break;
									}
									else {
										continue;
									}
								}
							}
							else if (userChoiceForSubject == 0) {
								break;
							}
							else {
								continue;
							}
						}
					}
					else if (userChoice == '4') {
						break;
					}
					else {
						continue;
					}
				}
			}
			else {
				std::cerr << "\n\n No tests yet! \n\n";
				Sleep(2000);
				continue;
			}
		}
		else if (teacherChoice == '3') {
			while (true) {
				system("cls");

				std::cout << "1. Add a Student\n";
				std::cout << "2. Delete a Student\n";
				std::cout << "3. Modify a Student\n";
				std::cout << "4. Back\n";

				char teacherChoiceForStudents = _getch();

				if (teacherChoiceForStudents == '1') {
					while (true) {
						system("cls");

						std::string realName;
						std::string surname;
						std::string login;
						std::string password;
						std::string passwordVerification;
						std::string phoneNumber;


						std::cout << "\t\tAdd a Student:";
						std::cout << "\t\t(Enter 0 to go back)\n\n";

						std::cout << "First Name: ";
						std::getline(std::cin, realName);

						if (realName == "0") {
							break;
						}

						std::cout << "Last Name: ";
						std::getline(std::cin, surname);

						if (surname == "0") {
							break;
						}

						std::cout << "Username: ";
						std::getline(std::cin, login);

						if (login == "0") {
							break;
						}
						else if (isUsed(login)) {
							std::cerr << "\n\nUsername already taken!!!\n\n";
							Sleep(2000);
							continue;
						}

						HANDLE hStdin = GetStdHandle(STD_INPUT_HANDLE);       //
						DWORD mode = 0;                                       // to make the input
						GetConsoleMode(hStdin, &mode);                        // invisible (for the password)
						SetConsoleMode(hStdin, mode & (~ENABLE_ECHO_INPUT));  //

						std::cout << "Password(you won't see it): ";
						std::getline(std::cin, password);

						if (password == "0") {
							break;
						}
						else if (password.size() < 8) {
							std::cerr << "\n\nThe password is too weak! It must be 8 characters or more!\n\n";
							Sleep(3000);
							continue;
						}

						std::cout << '\n';

						std::cout << "Verify the password: ";
						std::getline(std::cin, passwordVerification);

						if (passwordVerification == "0") {
							break;
						}
						else if (password != passwordVerification) {
							std::cerr << "\n\nPasswords are not the same!\n\n";
							Sleep(2000);
							continue;
						}

						SetConsoleMode(hStdin, mode); // to make the input visible again
						std::cout << '\n';

						std::cout << "Phone Number(no spaces): ";
						std::getline(std::cin, phoneNumber);

						if (phoneNumber == "0") {
							studentMainMenu();
							return;
						}
						else if (phoneNumber.length() > 15) {
							std::cerr << "\n\nMaximum length of the phone number is 15 digits!!!\n";
							Sleep(2000);
							continue;
						}

						student newStudent{ realName, surname, login, password, phoneNumber };

						break;
					}
				}
				else if (teacherChoiceForStudents == '2') {
					int teacherChoiceToDeleteAStudent;

					std::cout << "Choose a student:\n\n";

					for (int i = 0; i < student::students.size(); ++i) {
						std::cout << i + 1 << ". " << student::students[i].name << '\n';
					}

					std::cout << "Your choice(enter 0 to go back): ";
					std::cin >> teacherChoiceToDeleteAStudent;
					std::cin.ignore();

					if (teacherChoiceToDeleteAStudent <= student::students.size() && teacherChoiceToDeleteAStudent != 0) {
						student::students.erase(student::students.begin() + teacherChoiceToDeleteAStudent - 1);

						student::saveData();

						break;
					}
					else if (teacherChoiceToDeleteAStudent == 0) {
						break;
					}
					else {
						continue;
					}
				}
				else if (teacherChoiceForStudents == '3') {
					while (true) {
						system("cls");

						std::cout << "Select a student: \n\n";
						int userChoiceForStudent;

						for (int i = 0; i < student::students.size(); ++i) {
							std::cout << i + 1 << ". " << student::students[i].name << "\n\n";
						}

						std::cout << "Enter your choice(enter 0 to go back): ";
						std::cin >> userChoiceForStudent;
						std::cin.ignore();

						if (userChoiceForStudent == 0) {
							break;
						}
						else if (userChoiceForStudent <= student::students.size()) {
							std::string passVerification;

							std::cout << "Enter a new name for the student: ";
							std::getline(std::cin, student::students[userChoiceForStudent - 1].name);

							std::cout << "Enter a new surname for the student: ";
							std::getline(std::cin, student::students[userChoiceForStudent - 1].surname);

							std::cout << "Enter a new username for the student: ";
							std::getline(std::cin, student::students[userChoiceForStudent - 1].login);

							std::cout << "Enter a new password for the student: ";
							std::getline(std::cin, student::students[userChoiceForStudent - 1].password);

							student::students[userChoiceForStudent - 1].hashedPassword = student::hashThePassword(student::students[userChoiceForStudent - 1].password);

							std::cout << "Verify the password: ";
							std::getline(std::cin, passVerification);

							if (student::students[userChoiceForStudent - 1].password != passVerification) {
								continue;
							}

							std::cout << "Enter a new phone number for the student: ";
							std::getline(std::cin, student::students[userChoiceForStudent - 1].phoneNum);

							student::saveData();
						}
						else {
							continue;
						}
					}
				}
				else if (teacherChoiceForStudents == '4') {
					break;
				}
			}
		}
		else if (teacherChoice == '4') {
			system("cls");
			if (student::students.size() != 0) {
				for (student eachStud : student::students) {
					std::cout << eachStud.name << ": \n\n";

					if (eachStud.takenTestResults.size() != 0) {
						for (int i = 0; i < eachStud.takenTests.size(); ++i) {
							std::cout << eachStud.takenTests[i].testName << ": " << eachStud.takenTestResults[i] << "/12\n";
						}
					}
					else {
						std::cout << "Didn't take any tests\n";
					}
				}
			}
			else {
				std::cout << "\n\n No students yet! \n\n";
			}

			std::cout << "\n\n Press any key to continue...\n\n ";

			char anyKey = _getch();
		}
		else if (teacherChoice == '5') {
			teacher::saveData();
			mainMenu();
			return;
		}
		else {
			continue;
		}
	}
}

void interface::studentMenu(student newStudent) {
	system("cls");
	std::cout << "\t\tWelcome, " << newStudent.name << "!\n";
	std::cout << "1. Take a test\n";
	std::cout << "2. Previous test results\n";
	std::cout << "3. Main menu\n";

	char studentChoice = _getch();

	if (studentChoice == '1') {
		while (true) {
			system("cls");
			std::vector<std::string> subjects;
			std::cout << "Select a subject: \n\n";
			int userChoiceForSubject;

			for (int i = 0; i < test::tests.size(); ++i) {
				if (!std::count(subjects.begin(), subjects.end(), test::tests[i].subject)) {
					subjects.push_back(test::tests[i].subject);
				}

				std::cout << i + 1 << ". " << subjects[i] << "\n\n";
			}

			std::cout << "Enter your choice(enter 0 to go back): ";
			std::cin >> userChoiceForSubject;
			std::cin.ignore();

			if (userChoiceForSubject == 0) {
				studentMenu(newStudent);
				return;
			}

			if (userChoiceForSubject <= test::tests.size()) {
				while (true) {
					system("cls");
					std::cout << "Select a test: \n\n";

					std::string subjectToWorkWith = subjects[userChoiceForSubject - 1];
					std::vector<test> testsToWorkWith;
					int userChoiceForTest;

					for (test& eachTest : test::tests) {
						if (eachTest.subject == subjectToWorkWith) {
							testsToWorkWith.push_back(eachTest);
						}
					}
					for (test& eachTestToWorkWith : testsToWorkWith) {
						int i = 1;

						std::cout << i << ". " << eachTestToWorkWith.testName << "\n\n";

						++i;
					}

					std::cout << "Enter your choice(enter 0 to go back): ";
					std::cin >> userChoiceForTest;
					std::cin.ignore();

					if (userChoiceForTest == 0) {
						break;
					}

					test testToWorkWith = testsToWorkWith[userChoiceForTest - 1];

					int rightAnswerAmount = 0;

					for (int i = 0; i < testToWorkWith.asks.size(); ++i) {
						system("cls");
						
						std::cout << i + 1 << ". " << testToWorkWith.asks[i].question << "\n\n";
						
						for (int j = 0; j < testToWorkWith.asks[i].answers.size(); ++j) {
							if (j == 0 || j % 2 == 0) {
								std::cout << j + 1 << ". " << testToWorkWith.asks[i].answers[j].theAnswer << '\t';
							}
							else {
								std::cout << j + 1 << ". " << testToWorkWith.asks[i].answers[j].theAnswer << '\n';
							}
						}

						int answerChoice;

						std::cout << "\n\nEnter your answer(enter 0 to go back): ";
						std::cin >> answerChoice;
						std::cin.ignore();

						if (answerChoice <= testToWorkWith.asks[i].answerAmount && answerChoice != 0) {
							if (testToWorkWith.asks[i].answers[answerChoice - 1].right == true) {
								std::cout << "\n\n That's Right! \n";

								++rightAnswerAmount;

								Sleep(1000);
							}
							else {
								std::cout << "\n\n Wrong! \n";

								Sleep(1000);
							}
						}
						else if (answerChoice == 0) {
							studentMenu(newStudent);
							return;
						}
						else {
							continue;
						}
					}
					newStudent.takenTests.push_back(testToWorkWith);
					
					int rightAnswerPercent = rightAnswerAmount * 100 / testToWorkWith.questionAmount;
					
					newStudent.takenTestResults.push_back(rightAnswerPercent * 12 / 100);
					
					for (int i = 0; i < student::students.size(); ++i) {
						if (student::students[i].login == newStudent.login) {
							student::students[i] = newStudent;
						}
					}

					student::saveData();
				}
			}
			else {
				continue;
			}
		}
	}
	else if (studentChoice == '2') {
		while (true) {
			system("cls");
			if (newStudent.takenTestResults.size() != 0) {
				for (int i = 0; i < newStudent.takenTests.size(); ++i) {
					std::cout << newStudent.takenTests[i].testName << ": " << newStudent.takenTestResults[i] << "/12\n";
				}
			}
			else {
				std::cout << "You didn't take any tests\n";
			}

			std::cout << "\nPress anything to continue...\n";

			char anythingToContinue = _getch();

			studentMenu(newStudent);
			return;
		}
	}
	else if (studentChoice == '3') {
		student::saveData();
		studentMainMenu();
	}
	else {
		studentMenu(newStudent);
	}
}