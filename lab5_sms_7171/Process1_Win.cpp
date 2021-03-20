#include <iostream>
#include <conio.h>
#include <process.h>

using namespace std;

int main(int argc, char** argv[])
{
	setlocale(LC_ALL, "Russian");
	char* comand[3];
	comand[0] = (char*)"ping";
	string adress;
	if (argc > 1)
	{
		comand[1] = (char*)argv[1];
	}
	else
	{
		cout << "Введите адрес для проверки доступности: ";
		cin >> adress;
		comand[1] = (char*)adress.c_str();
	}
	comand[2] = 0;
	_execvp(comand[0], comand);
	return 0;
}
