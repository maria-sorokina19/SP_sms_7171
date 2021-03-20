#include <iostream>
#include <process.h>
#include <string>
#include <stdio.h>
#include <windows.h>
#include <conio.h>
#include <stdlib.h> 

using namespace std;
//Семафор, значение семафора
HANDLE hSemaphore;
LONG cMax = 1;
string cLine;

//Формирование ip-адреса 
void num_adress(string adress, int i)
{
	string temp_ = adress; // Заносим диапазон адресов в строку
	string temp = ".";
	temp = temp += to_string(i); // Формируем адрес в диапазоне
	temp_ = temp_ += temp; // Адрес для опроса
	string cLine_ = "code ";
	cLine_ = cLine_ += temp_;
	cLine = cLine_;
}

DWORD WINAPI ThreadFunc(PVOID pvParam)
{
		DWORD dwWaitResult;
		BOOL bContinue = TRUE;
		//Номер потока
		int i = (*((int*)pvParam));
		//Путь exe файла первой программы
		string appName = "E:\\старый диск\\Универ\\4 курс 2 семак\\СП\\лаба 4\\Новая папка\\Process1\\Debug\\Process1.exe";
		while (bContinue)
		{
				//Определяем значение семафора
				dwWaitResult = WaitForSingleObject(hSemaphore, 0L);           
				switch (dwWaitResult) 
				{
					//Семафор свободен
					case WAIT_OBJECT_0:
					cout << endl;
					cout << "Поток "<< GetCurrentThreadId() <<": запущен" << endl;
					bContinue = FALSE;
					Sleep(5);
					cout << "Порядковый номер потока: ";
					cout << (*((int*)pvParam))+1 << endl;
					STARTUPINFOA si;
					PROCESS_INFORMATION piCom;
					ZeroMemory(&si, sizeof(si));
					si.cb = sizeof(si);
					//Создаем новый процесс
					CreateProcessA(appName.c_str(), (char*)cLine.c_str(), NULL, NULL, FALSE, 0, NULL, NULL, &si, &piCom);
					//Ожидаем завершения процесса
					WaitForSingleObject(CreateProcessA, INFINITE);
					Sleep(20000);
					//Закрываем все потоки и процесс
					CloseHandle(piCom.hThread);
					CloseHandle(piCom.hProcess);
					//Освобождаем семафор, когда закончил работу процесс. Если освободить не получилось, вывести сообщение об ошибке
					if (!ReleaseSemaphore(hSemaphore, 1, NULL))       
					{
						cout<<"Ошибка работы с семафором: " << GetLastError()<<endl;
					}
					break;
					//Семафор занят, поток ждет
					case WAIT_TIMEOUT:
					cout << "Поток " << GetCurrentThreadId() << ": ждет!" << endl;
					break;
			}
		}
	return TRUE;
}

int main(int argc, char* argv[])
{
	setlocale(LC_ALL, "Russian");
	string adress;
	cout << "Введите диапазон адресов: ";
	cin >> adress;
	int first, second;
	cout << "Введите начало диапазона: ";
	cin >> first;
	//const int n = 10;
	const int n = 4;
	second = first + n;
	DWORD dwThreadId[n], dw;
	HANDLE hThread[n];
	//Создаем семафор, если не получилось, вывести сообщение об ошибке
	hSemaphore = CreateSemaphore(NULL, cMax, cMax, NULL);
	if (hSemaphore == NULL)
	{
		cout << "Ошибка создания семафора: " << GetLastError() << endl;
		return 1;
	}
	//Заносим в массив значения адресов текущего диапазона
	int a[n];
	int k = 0;
	for (int i = first; i < second; i++)
	{
		a[k] = i;
		k++;
	}
	//Создание n дочерних потоков
	for (int j = 0; j < n; j++)
	{
			//Вызываем функцию, которая формирует ip-адрес
			num_adress(adress, a[j]);
			//Создаем поток j
			hThread[j] = CreateThread(NULL, 0, ThreadFunc, (PVOID)&j, 0, &dwThreadId[j]);
			//Если не получилось создать поток, вывести сообщение об ошибке
			if (!hThread) cout << "Поток " << j << " не создан!" << endl; 
			//Ждем завершения текущего потока и закрываем 
			dw = WaitForMultipleObjects(1, hThread, TRUE, INFINITE);
			CloseHandle(hThread[j]);
	}
	//Ожидание завершения n потоков
	dw = WaitForMultipleObjects(n, hThread, TRUE, INFINITE);
	//Закрываем семафор
	CloseHandle(hSemaphore);
	return 0;
}
