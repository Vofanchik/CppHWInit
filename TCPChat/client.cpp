#include <iostream>
#include <unistd.h>
#include <string.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include "message.h"
 
using namespace std;
 
#define MESSAGE_LENGTH 1024 // Максимальный размер буфера для данных
#define PORT 7777 // Будем использовать этот номер порта
 
int socket_file_descriptor, connection;
struct sockaddr_in serveraddress, client;
char message[MESSAGE_LENGTH];
string text, from;

int main(){
    // Создадим сокет
    socket_file_descriptor = socket(AF_INET, SOCK_STREAM, 0);
    if(socket_file_descriptor == -1){
        cout << "Creation of Socket failed!" << endl;
        exit(1);
    }
 
    // Установим адрес сервера
    serveraddress.sin_addr.s_addr = inet_addr("127.0.0.1");
    // Зададим номер порта
    serveraddress.sin_port = htons(PORT);
    // Используем IPv4
    serveraddress.sin_family = AF_INET;
    // Установим соединение с сервером
    connection = connect(socket_file_descriptor, (struct sockaddr*)&serveraddress, sizeof(serveraddress));
    if(connection == -1){
        cout << "Connection with the server failed.!" << endl;
        exit(1);
    }
    // Взаимодействие с сервером
    while(1){
        bzero(message, sizeof(message));
        if(from.length()==0){
            cout << "Enter your login: " << endl;
            cin >> from;
        }

       
        cout << "Enter the message: " << endl;
        cin>>text;
        getline(cin, text);// почему режет первое слово
        
        Message *mmm = new Message(from, text);
        strcpy(message, mmm->serialize().c_str());
        

        // if ((strncmp(message, "end", 3)) == 0) {
        //     write(socket_file_descriptor, message, sizeof(message));
        //     cout << "Client Exit." << endl;
        //     break;
        // }
        ssize_t bytes = write(socket_file_descriptor, message, sizeof(message));
        // Если передали >= 0  байт, значит пересылка прошла успешно
        if(bytes >= 0){
        cout << "Data send to the server successfully.!" << endl;
    }
    bzero(message, sizeof(message));
    // Ждем ответа от сервера
    read(socket_file_descriptor, message, sizeof(message));
    cout << "Data received from server: " << message << endl;
    // cout<<serveraddress.sin_addr.s_addr<<endl;
    // cout<< socket_file_descriptor<<endl;

    }
    // закрываем сокет, завершаем соединение
    close(socket_file_descriptor);
    return 0;
}
