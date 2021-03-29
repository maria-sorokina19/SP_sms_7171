#include <sys/types.h>
#include <sys/socket.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/un.h>
#include <stdio.h>
#include <iostream>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <string.h>


using namespace std;
//Вывод сообщения об ошибке и выход из программы
void error(const char *msg)
{
        perror(msg);
        exit(0);
}

int main(int argc, char *argv[])
{
	//TCP клиент в UNIX домене
	cout<<"Передача TCP!"<<endl;
	int socket_inf, servlen, n;
	struct sockaddr_un serv_addr;
	char buffer[256];
	bzero((char *)&serv_addr, sizeof(serv_addr));
	serv_addr.sun_family = AF_UNIX;
	strcpy(serv_addr.sun_path, argv[1]);
	servlen = strlen(serv_addr.sun_path) + sizeof(serv_addr.sun_family);
	//Создание сокета
	socket_inf = socket(AF_UNIX, SOCK_STREAM, 0);
        if (socket_inf<0) error("Ошибка создания сокета!");
        else cout<<"Сокет создан!"<<endl;
        //Инициализация установки соединения со стороны клиента
	if (connect(socket_inf, (struct sockaddr *)&serv_addr, servlen)<0) error("Ошибка соединения!");
	else cout<<"Соединение установлено!"<<endl;
	cout<<"Введите свое сообщение: ";
	//Освобождаем буффер и заносим в него информацию, введенную со стороны клиента
	bzero(buffer, 256);
	fgets(buffer, 255, stdin);
	//Отправка данных
	n = send(socket_inf, buffer, 255, 0);
	if (n<0) error("Ошибка записи сообщения!");
	//Очищаем буффер
	bzero(buffer, 256);
	//Получаем ответ с сервера
	n=recv(socket_inf, buffer, 255, 0);
	if (n<0) error("Ошибка чтения сообщения!");
	else cout<<"Чтение осуществлено!"<<endl;
	//Выводим на экран содержимое буффера и закрываем TCP сокет 
	cout<<buffer<<endl;
	close(socket_inf);
	//UDP клиент в интернет домене
	cout<<"Передача UDP!"<<endl;
	int socket_, n_;
	unsigned int servlen_;
	struct sockaddr_in serv_addr_, cli_addr_;
	char buffer_[256];
	struct hostent *hp;
	//Создание сокета
	socket_ = socket(AF_INET, SOCK_DGRAM, 0);
        if (socket_<0) error("Ошибка создания сокета!");
        else cout<<"Сокет создан!"<<endl;
	serv_addr_.sin_family = AF_INET;
	hp = gethostbyname(argv[2]);
	if (hp==0) error("Неизвестный host");
	bcopy((char *)hp->h_addr,
		(char *)&serv_addr_.sin_addr,
		hp->h_length);
	serv_addr_.sin_port = htons(atoi(argv[3]));
	servlen_=sizeof(struct sockaddr_in);
	cout<<"Введите сообщение: ";
	//Освобождаем буффер и заносим в него информацию, введенную со стороны клиента
	bzero(buffer_, 256);
	fgets(buffer_, 255, stdin);
	//Отправка данных
	n_ = sendto(socket_, buffer_, strlen(buffer_), 0, (const struct sockaddr *)&serv_addr_, servlen_);
	if (n_<0) error("Ошибка отправки данных!");
	//Очищаем буффер
	bzero(buffer_, 256);
	//Получаем ответ с сервера
	n_=recvfrom(socket_, buffer_, 256, 0, (struct sockaddr *)&cli_addr_,&servlen_);
	if (n_<0) error("Ошибка получения данных!");
	else cout<<"Данные получены!"<<endl;
	//Выводим сообщение, полученное с сервера UDP, и закрываем сокет UDP
	write(1,buffer_,n_);
	cout<<endl;
	close(socket_);
	return 0;
}
