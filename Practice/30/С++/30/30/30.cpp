//ИГРАЛСЯ С 29 ЗАДАНИЕМ

#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <iomanip>

std::string exams_arr[] = { "math", "phys", "hist", "prog" };

struct Student
{
	std::string name;
	int group;

	std::map<std::string, int> exams;
	std::map<std::string, int>::iterator examsInit;
	int n;

	void init()
	{
		std::cout << "Enter student name: ";
		std::cin >> name;
		std::cout << "Enter student group: ";
		std::cin >> group;

		for (int i = 0; i < 4; i++)
		{
			std::cout << "Enter a " << exams_arr[i] << " grade: ";
			std::cin >> exams[exams_arr[i]];
		}
		std::cout << '\n';
	}

};
