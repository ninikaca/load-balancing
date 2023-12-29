﻿#define _WINSOCK_DEPRECATED_NO_WARNINGS

#include <stdio.h>
#include <winsock2.h> // Za Windows Sockets
#include <conio.h>
#include <time.h>

#pragma comment(lib, "ws2_32.lib") // Dodatak biblioteke za linker

int main() {
    WSADATA wsaData;
    SOCKET sockfd;
    struct sockaddr_in serverAddr;
    char buffer[1024];
    int bytesReceived = 0, lastGenNumber = 1;

    // Inicijalizacija Winsock
    if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) {
        printf("Neuspela inicijalizacija Winsock-a.\n");
        return 1;
    }

    // Kreiranje socket-a
    if ((sockfd = socket(AF_INET, SOCK_STREAM, 0)) == INVALID_SOCKET) {
        printf("Greska pri kreiranju socket-a.\n");
        WSACleanup();
        return 1;
    }

    // Postavljanje adrese servera i porta
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(5059);
    serverAddr.sin_addr.s_addr = inet_addr("127.0.0.1");

    // Spajanje na server
    if (connect(sockfd, (struct sockaddr*)&serverAddr, sizeof(serverAddr)) < 0) {
        printf("Greska pri povezivanju na server.\n");
        closesocket(sockfd);
        WSACleanup();
        return 1;
    }

    printf("Kreiranje i slanje podataka na Load Balancing servis...\n");
    printf("Pritisnite 'q' ili 'Q' za kraj rada klijenta.\n\n");


    // Zatvaranje socket-a i čišćenje Winsock-a
    closesocket(sockfd);
    WSACleanup();

    return 0;
}
