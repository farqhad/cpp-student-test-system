#include <iostream>
#include "interface.h"
#include <vector>


int main() {
	teacher::loadData();
 	student::loadData();
	test::loadData();

	//student::getStudents();

	interface::mainMenu();

	student::saveData();

	return 0;
}