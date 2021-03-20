#include <iostream>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>

using namespace std;
//Глобальные переменные для передачи параметров вызываемому процессу
string temp_ = "";
string packets = "";
//Объявление семафора или мьютекса
//sem_t sem;
pthread_mutex_t m;

//Функция для формирования отдельного ip-адреса
void num_adress(string adress, int i)
{
	temp_ = adress; // Заносим диапазон адресов в строку
	string temp = ".";
	temp = temp+=to_string(i); // Формируем адрес в диапазоне
	temp_ = temp_+=temp; // Адрес для опроса
}


void *thread_func (void *in) {
	//Остановка выполнения потока до тех пор, пока значение семафора не станет больше нуля
//	sem_wait(&sem);
	//Захватить мьютекс
	pthread_mutex_lock(&m);
	cout<<" запущен!"<<endl;
	pid_t num;
        int status;
	num = fork();
	switch(num)
      	{
		case -1:
			cout<<"Невозможно породить процесс!"<<endl;
                        exit(-1);
		case 0: //Если порождение процесса не удалось, то заменяем контекст дочернего процесса и запускаем первую программу
			cout<<"Процесс порожден!"<<endl;
                        execl("process1",(char*) packets.c_str(), (char*) temp_.c_str(), NULL);
		default: //Если дочерний процесс еще не завершен, ждем его окончания
                        wait(&status);
	}
	//Увеличить значение семафора на единицу
//	sem_post(&sem);
	//Освободить мьютекс
	pthread_mutex_unlock(&m);
	return 0;
}


int main()
{
	//Инициализация семафора или мьютекса
//	sem_init(&sem, 0, 1);
	pthread_mutex_init(&m, NULL);
	string adress;
	cout<<"Введите диапазон адресов: ";
	cin>>adress;
	int first, second;
	cout<<"Введите начало диапазона: ";
	cin>>first;
	const int n  = 4;
	second = first + n;
	cout << "Введите количество пакетов для отправки по каждому адресу: ";
	cin >> packets;
	//Заносим в массив значения адресов текущего диапазона
	int a[n];
	int k = 0;
	for (int i = first; i < second; i++)
	{
		a[k] = i;
		k++;
	}
	//Создание n потоков
	pthread_t thread[n];
	for (int j = 0; j < n; j++)
	{
		//Вызываем функцию, которая формирует ip-адрес
		num_adress(adress, a[j]);
		cout<<endl;
		cout <<"Поток с порядковым номером: "<<j+1;
		//Создаем поток j
		pthread_create(&thread[j], NULL, thread_func, NULL);
		//Ждем завершения текущего потока
		pthread_join(thread[j], NULL);
	}
	//Уничтожение семафора или мьютекса
//	sem_destroy(&sem);
	pthread_mutex_destroy(&m);
//	pthread_attr_destroy(&attr);
	return 0;
}











