#undef UNICODE
#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#include <winsock2.h>
#include <ws2tcpip.h>
#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <string.h>
#include "message.h"
#include <vector>
#include "DatBase.h"

#pragma comment (lib, "Ws2_32.lib")
#define DEFAULT_BUFLEN 512
#define DEFAULT_PORT "27015"


WSADATA wsaData;
int iResult;

SOCKET ListenSocket = INVALID_SOCKET;
SOCKET ClientSocket = INVALID_SOCKET;

struct addrinfo* result = NULL;
struct addrinfo hints;

int iSendResult;
char recvbuf[DEFAULT_BUFLEN];
int recvbuflen = DEFAULT_BUFLEN;

std::string text, from;
std::vector<Message> messages;

DatBase* db = new(DatBase);


int main()
{
    vector<Message> messages = db->returnMesVector();
    iResult = WSAStartup(MAKEWORD(2, 2), &wsaData);
   
    ZeroMemory(&hints, sizeof(hints));
    hints.ai_family = AF_INET;
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_protocol = IPPROTO_TCP;
    hints.ai_flags = AI_PASSIVE;

    iResult = getaddrinfo(NULL, DEFAULT_PORT, &hints, &result);
    ListenSocket = socket(result->ai_family, result->ai_socktype, result->ai_protocol);
    iResult = bind(ListenSocket, result->ai_addr, (int)result->ai_addrlen);
    freeaddrinfo(result);
    iResult = listen(ListenSocket, SOMAXCONN);
    ClientSocket = accept(ListenSocket, NULL, NULL);
    closesocket(ListenSocket);

    while (1){
        memset(recvbuf, 0, recvbuflen);
        iResult = recv(ClientSocket, recvbuf, recvbuflen, 0);
        
        if (iResult > 0) {
            string unser(recvbuf);
            int pos = unser.find(" ");

            text = unser.substr(0, pos);
            from = unser.substr(pos + 1);

            Message* mmm = new Message(from, text);

            db->insertValue(from, text);            

            messages.push_back(*mmm);
            unser = "";
            for (auto& mess : messages) {
                unser.append("\nfrom:\n");
                unser.append(mess.GetFrom());
                unser.append("\ntext:\n");
                unser.append(mess.GetText());
                unser.append("\n========\n");
            }
            memset(recvbuf, 0, recvbuflen);
            strcpy(recvbuf, unser.c_str());
            

            iSendResult = send(ClientSocket, recvbuf, iResult, 0);
        }

    } ;


    iResult = shutdown(ClientSocket, SD_SEND);
    closesocket(ClientSocket);
    WSACleanup();
    return 0;
}