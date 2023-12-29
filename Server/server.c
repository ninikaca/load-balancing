#include <stdio.h>
#include <winsock2.h>
#include <process.h> // Za rad sa nitima
#include <conio.h>
#include "klijentiTCP.h"
#include "../Common/RadSaRedom.h"

#pragma comment(lib, "ws2_32.lib")

#define MAX_CLIENTS 10 // Maksimalan broj klijenata
#define MAX_WORKERS  10 // Maksimalan broj Wr

int main() {
    WSADATA wsaData;
    SOCKET sockfd, clientSocket;
    struct sockaddr_in serverAddr, clientAddr;
    int clientAddrLen = sizeof(clientAddr), receivedNumber = 0;
    char buffer[1024] = "";
    Red red;
    unsigned int brojSkladistenihPodatakaWorker[MAX_WORKERS] = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
    HANDLE workers[MAX_WORKERS] = { NULL };

    // Inicijalizacija reda
    inicijalizujRed(&red);

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
    serverAddr.sin_addr.s_addr = INADDR_ANY;

    // Povezivanje socket-a s adresom i portom
    if (bind(sockfd, (struct sockaddr*)&serverAddr, sizeof(serverAddr)) == SOCKET_ERROR) {
        printf("Greska pri povezivanju socket-a s adresom i portom.\n");
        closesocket(sockfd);
        WSACleanup();
        return 1;
    }

    // Slušanje dolaznih konekcija
    if (listen(sockfd, MAX_CLIENTS) == SOCKET_ERROR) {
        printf("Greska pri slušanju konekcija.\n");
        closesocket(sockfd);
        WSACleanup();
        return 1;
    }

    printf("Server je spreman i slusa konekcije...\n");
    printf("Pritisnite 'q' ili 'Q' za kraj rada klijenta.\n");

    // Cuvanje identifikatora niti za oslobađanje resursa
    HANDLE threadHandles[MAX_CLIENTS];
    int threadCount = 0;

    while (1) {
        if (_kbhit()) { // Check if a key has been pressed
            char ch = _getch(); // Get the pressed key
            if (ch == 'q' || ch == 'Q') {
                printf("Pritisnite bilo koji taster da zatvorite serversku aplikaciju...");
                char c = getchar();
                break;
            }
        }

        // Prihvatanje dolazne konekcije
        if ((clientSocket = accept(sockfd, (struct sockaddr*)&clientAddr, &clientAddrLen)) == INVALID_SOCKET) {
            printf("Greska pri prihvatanju konekcije.\n");
            closesocket(sockfd);
            WSACleanup();
            return 1;
        }

        printf("Klijent je povezan.\n");

        // Pokretanje nove niti za svakog klijenta
        uintptr_t threadID = -1;
        LoadBalancerParametri parametri = { brojSkladistenihPodatakaWorker, &clientSocket, &red, workers, MAX_WORKERS };
        InitializeCriticalSection(&parametri.cs); // Inicijalizacija kriticne sekcije za kasniju upotrebu

        threadHandles[threadCount] = (HANDLE)_beginthreadex(NULL, 0, &PrihvatKlijentaTCP, (void*)&parametri, 0, (unsigned int*)&threadID);

        if (threadHandles[threadCount] == NULL) {
            printf("Greska pri pokretanju niti za klijenta.\n");
            closesocket(clientSocket);
        }
        else {
            threadCount++;
        }

        //DeleteCriticalSection(&parametri.cs); // Brisanje kriticne sekcije
    }

    // Oslobađanje resursa niti
    for (int i = 0; i < threadCount; ++i) {
        CloseHandle(threadHandles[i]);
    }

    for (int i = 0; i < MAX_WORKERS; ++i) {
        if(workers[i] != NULL)
            CloseHandle(workers[i]);
    }

    // Zatvaranje socket-a i čišćenje Winsock-a, oslobadjanje reda
    unistiRed(&red);
    closesocket(sockfd);
    WSACleanup();

    return 0;
}
