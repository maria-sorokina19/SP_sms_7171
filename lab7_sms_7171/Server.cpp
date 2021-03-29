#include <sys/types.h>
#include <sys/socket.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/un.h>
#include <stdio.h>
#include <iostream>
#include <netinet/in.h>
#include <string.h>
#include <netdb.h>

using namespace std;
//Вывод сообщения об ошибке и выход из программы
void error(const char *msg)
{
	perror(msg);
	exit(0);
}

int main(int argc, char *argv[])
{
	//TCP сервер в UNIX домене
	cout<<"Передача TCP!"<<endl;
	int socket_inf, newsocket_inf,servlen, n;
	socklen_t clilen;
	char buffer[256];
	struct sockaddr_un cli_addr, serv_addr;
	//Создание сокета
	socket_inf = socket(AF_UNIX, SOCK_STREAM, 0);
	if (socket_inf<0) error("Ошибка создания сокета!");
	else cout<<"Сокет создан!"<<endl;
	bzero ((char *) &serv_addr, sizeof(serv_addr));
	serv_addr.sun_family = AF_UNIX;
	strcpy(serv_addr.sun_path, argv[1]);
	servlen = strlen(serv_addr.sun_path) + sizeof(serv_addr.sun_family);
	//Установление связи сокета с адресом
	if (bind(socket_inf, (struct sockaddr *)&serv_addr, servlen)<0) error("Ошибка связывания сокета сервера с адресом!");
	else cout<<"Сокет сервера связан с адресом успешно!"<<endl;
	//Ожидание соединения от клиента
	listen(socket_inf, 5);
	//Создание нового сокета, когда сервер готов принять запросы клиентов
	clilen = sizeof(cli_addr);
	newsocket_inf = accept(socket_inf, (struct sockaddr *)&cli_addr, &clilen);
	if (newsocket_inf < 0) error("Ошибка создания нового сокета!");
	else cout<<"Новый сокет создан успешно!"<<endl;
	//Очищаем буффер
	bzero(buffer, 256);
	//Чтение данных из нового сокета
	n=recv(newsocket_inf, buffer, 255, 0);
	if (n<0) error("Ошибка чтения!");
	else cout<<"Чтение!"<<endl;
	//Вывод собщения от клиента
	cout<<"Сообщение от клиента: "<<buffer<<endl;
	//Отправка сообщения клиенту
	n = send(newsocket_inf, "Сообщение клиента получено!", 255, 0);
	if (n<0) error("Ошибка отправки ответа клиенту!");
	else cout<<"Ответ клиенту успешно отправлен!"<<endl;
	//Закрываем созданные TCP сокеты 
	close(newsocket_inf);
	close(socket_inf);
	//UDP сервер в интернет домене
	cout<<"Передача UDP!"<<endl;
	int socket_, servlen_, n_;
	socklen_t clilen_;
	char buffer_[1024];
	struct sockaddr_in cli_addr_;
	struct sockaddr_in serv_addr_;
	//Проверка то, что введена информация о UDP порте
	if (argc < 2)
	{
		fprintf(stderr, "ERROR, no port provided\n");
		exit(0);
	}
	//Создание сокета
	socket_ = socket(AF_INET, SOCK_DGRAM, 0);
	if (socket_<0) error("Ошибка создания сокета!");
	else cout<<"Сокет создан!"<<endl;
	servlen_ = sizeof(serv_addr_);
	bzero (&serv_addr_, servlen_);
	serv_addr_.sin_family = AF_INET;
	serv_addr_.sin_addr.s_addr=INADDR_ANY;
	serv_addr_.sin_port=htons(atoi(argv[2]));
	//Установление связи сокета с адресом
	if (bind(socket_, (struct sockaddr *)&serv_addr_, servlen_)<0) error("Ошибка связывания сокета сервера с адресом!");
	else cout<<"Сокет сервера связан с адресом успешно!"<<endl;
	//Получение данных с клиента
	clilen_ = sizeof(struct sockaddr_in);
	n_=recvfrom(socket_, buffer_, 1024, 0, (struct sockaddr *)&cli_addr_, &clilen_);
	if (n<0) error("Ошибка получения данных!");
	else cout<<"Получение данных!"<<endl;
	//Вывод датаграммы, полученной от клиента
	cout<<"Датаграмма от клиента: "<<endl;
	write(1, buffer_, n_);
	//Отправка ответа клиенту от сервера
	n_ = sendto(socket_, "Сообщение получено", 40, 0, (struct sockaddr *)&cli_addr_, clilen_);
	if (n_<0) error("Ошибка отправки данных!");
	else cout<<"Отправка данных успешно осуществлена!"<<endl;
	//Закрытие созданного UDP сокета
	close(socket_);
	return 0;
}
