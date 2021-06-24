#include <iostream>
#include <string>
#include <fstream>
#include "Matrix.h"

using namespace std;

bool check_lines(char* path);

int main(int argc, char** argv)
{
	setlocale(LC_ALL, "Russian");
	string op = argv[3];
	Matrix C;

	if (check_lines(argv[1]) && check_lines(argv[2]))
	{
		Matrix A(argv[1]);
		Matrix B(argv[2]);

		if (op == "*")
		{
			C = A * B;
		}
		else if (op == "+")
		{
			C = A + B;
		}
		else if (op == "-")
		{
			C = A - B;
		}
		else if (op == "trans")
		{
			C = A.transpose();
		}
	}
	else
	{
		return -1;
	}

	C.print();



	return 0;
}

/*!
\param [in] path - путь к входному файлу
*/
//! Функция проверки корректности входных данных файлов
bool check_lines(char* path)
{
	string line;
	bool is_ok = true;
	bool is_alpha = false;
	bool is_file_exist = true;
	int count_lines = 0;

	ifstream in(path);

	if (in.is_open())
	{
		while (getline(in, line))
		{
			++count_lines;

			for (int i = 0; i < line.length(); i++)
			{
				if (isalpha(line[i]))
				{
					is_alpha = true;
				}
			}
		}
	}
	else
	{
		cout << "File doesn't exist >> " << path;
		is_file_exist = false;
		is_ok = false;
	}

	in.close();

	if (is_alpha)
	{
		cout << "Error in data in file, expected only digits >> " << path;
		is_ok = false;
	}

	if (is_file_exist)
	{
		if (count_lines > 100)
		{
			cout << "Too much lines in file >> " << path;
			is_ok = false;
		}
		else if (count_lines == 0)
		{
			cout << "Zero lines in file is unexpected >> " << path;
			is_ok = false;
		}
	}

	return is_ok;
}
