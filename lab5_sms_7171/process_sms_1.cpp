#include <iostream>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>

using namespace std;

int main (int argc, char *argv[], char *enpv[])
{
	char *comand[5];
	comand[0] = (char*) "ping";
        comand[1] = (char*) "-c"; //Параметр команды ping (количество отправленных пакетов)
	bool flag = false;
	string adress;
	if (argv[1]==NULL) //Если процесс создан не из второй программы
	{
		cout<<"Введите адрес для проверки доступности: ";
		cin>>adress;
		flag = true;
	}
	else comand[3] = argv[1]; //Если процесс вызван из второй программы, в качестве адреса принять переданный параметр
	if (flag == true) //Если процесс создан не из второй программы
	{
		string num_packets;
		cout<<"Введите количество пакетов для отправки: ";
		cin>>num_packets;
		comand[2] = (char*) num_packets.c_str();
		comand[3] = (char*) adress.c_str();
	}
	else comand[2] = argv[0]; //Если процесс вызван и второй программы,в качестве количества пакетов принять переданный параметр
	comand[4] = 0;
	execvp (comand[0], comand);
	return 0;
}
