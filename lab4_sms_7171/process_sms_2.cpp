#include <iostream>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <stdio.h>
using namespace std;

int main()
{
	string adress;
	cout<<"Введите диапазон адресов: ";
	cin>>adress;
	int first, second;
	cout<<"Введите начало диапазона: ";
	cin>>first;
	cout<<"Введите конец диапазона: ";
	cin>>second;
	second++;
	string packets;
	cout << "Введите количество пакетов для отправки по каждому адресу: ";
	cin>>packets;
	int num;
	int status;
	for (int i = first; i<second; i++)
	{
		string temp_ = adress; // Заносим диапазон адресов в строку
		string temp = ".";
		temp = temp+=to_string(i); // Формируем адрес в диапазоне
		temp_ = temp_+=temp; // Адрес для опроса
		num = fork(); // Порождаем новый процесс
		switch(num)
		{
		case -1: cout<<"Невозможно породить процесс!"<<endl;
			 exit(-1);
		case 0: //Если порождение процесса удалось, то заменяем контекст дочерного процесса и запускаем первую программу
			cout<<"Процесс порожден!"<<endl;
			execl("process1",(char*) packets.c_str(), (char*) temp_.c_str(), NULL);
		default:
			cout<<"Процесс не порожден. Ожидаем завершения дочернего процесса!"<<endl;
			wait(&status);
		}
	}
	return 0;
}
