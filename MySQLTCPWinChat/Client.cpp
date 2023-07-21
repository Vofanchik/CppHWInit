#define WIN32_LEAN_AND_MEAN

#include <windows.h>
#include <winsock2.h>
#include <ws2tcpip.h>
#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <string>
#include "message.h"
#pragma comment (lib, "Ws2_32.lib")
#pragma comment (lib, "Mswsock.lib")
#pragma comment (lib, "AdvApi32.lib")


#define DEFAULT_BUFLEN 512
#define DEFAULT_PORT "27015"

WSADATA wsaData;
SOCKET ConnectSocket = INVALID_SOCKET;
struct addrinfo* result = NULL,
    * ptr = NULL,
    hints;

char recvbuf[DEFAULT_BUFLEN];
int iResult;
int recvbuflen = DEFAULT_BUFLEN;
std::string text, text_, from;

int main()
{
    iResult = WSAStartup(MAKEWORD(2, 2), &wsaData);

    ZeroMemory(&hints, sizeof(hints));
    hints.ai_family = AF_UNSPEC;
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_protocol = IPPROTO_TCP;

    iResult = getaddrinfo(NULL, DEFAULT_PORT, &hints, &result);

    for (ptr = result; ptr != NULL; ptr = ptr->ai_next) {
        ConnectSocket = socket(ptr->ai_family, ptr->ai_socktype, ptr->ai_protocol);
        if (ConnectSocket == INVALID_SOCKET) {
            printf("socket failed with error: %ld\n", WSAGetLastError());
            WSACleanup();
            return 1;
        }

        iResult = connect(ConnectSocket, ptr->ai_addr, (int)ptr->ai_addrlen);
        if (iResult == SOCKET_ERROR) {
            closesocket(ConnectSocket);
            ConnectSocket = INVALID_SOCKET;
            continue;
        }
        break;
    }

    freeaddrinfo(result);

    while (1){
        memset(recvbuf, 0, recvbuflen);
        if (from.length() == 0) {
            std::cout << "Enter your login: " << std::endl;
            std::cin >> from;
        }

        std::cout << "Enter the message: " << std::endl;
        std::cin >> text_;
        std::getline(std::cin, text);
        text = text_ + text;

        Message* mmm = new Message(from, text);
        strcpy(recvbuf, mmm->serialize().c_str());

        iResult = send(ConnectSocket, recvbuf, recvbuflen, 0);
        memset(recvbuf, 0, recvbuflen);


        iResult = recv(ConnectSocket, recvbuf, recvbuflen, 0);
        std::cout << recvbuf << std::endl;

    } ;

    closesocket(ConnectSocket);
    WSACleanup();

    return 0;
}