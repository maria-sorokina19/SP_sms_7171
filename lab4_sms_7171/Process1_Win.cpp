#include <iostream>
#include <conio.h>
#include <process.h>

using namespace std;

int main(int argc, char* argv[], char* enpv[])
{
	setlocale(LC_ALL, "Russian");
	char* comand[5];
	comand[0] = (char*)"ping";
	bool flag = false;
	string adress;
	cout << "Введите адрес для проверки доступности: ";
	cin >> adress;
	comand[1] = (char*)adress.c_str();
	comand[2] = 0;
	_execvp(comand[0], comand);
	return 0;
}
