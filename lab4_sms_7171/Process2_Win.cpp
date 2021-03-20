#include <iostream>
#include <process.h>
#include <string>
#include <stdio.h>
#include <windows.h>
#include <conio.h>
#include <stdlib.h> 
using namespace std;

int main(int argc, char* argv[])
{
	setlocale(LC_ALL, "Russian");
	string adress;
	int first, second;
	cout << "Введите начало диапазона: ";
	cin >> first;
	cout << "Введите конец диапазона: ";
	cin >> second;
	second++;
	STARTUPINFO si;
	PROCESS_INFORMATION piCom;
	for (int i = first; i < second; i++)
	{
		ZeroMemory(&si, sizeof(si));
		si.cb = sizeof(si);
		// создаем новый процесс
		CreateProcess(L"E:\\старый диск\\Универ\\4 курс 2 семак\\СП\\лаба 4\\Новая папка\\Process1\\Debug\\Process1.exe", NULL, 
			NULL, NULL, FALSE, 0, NULL, NULL, &si, &piCom);
		Sleep(10000);
		_getch();
	}
	// закрываем дескрипторы этого процесса
	CloseHandle(piCom.hThread);
	CloseHandle(piCom.hProcess);
	cout << "Процесс завершен!" << endl;
	_getch();
	return 0;
}