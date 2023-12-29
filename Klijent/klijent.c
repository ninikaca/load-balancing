#define _WINSOCK_DEPRECATED_NO_WARNINGS

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

    do {
        if (_kbhit()) { // Check if a key has been pressed
            char ch = _getch(); // Get the pressed key
            if (ch == 'q' || ch == 'Q') {
                printf("\nPritisnite bilo koji taster da zatvorite klijensku aplikaciju...");
                char c = getchar();
                break;
            }
        }

        srand((unsigned int)time(NULL));
        srand(rand() % lastGenNumber);
        int broj = lastGenNumber = rand() % 300 + 1; // brojevi u opsegu od 1 do 300

        // Slanje broja serveru
        send(sockfd, (char*)&broj, sizeof(broj), 0);

        // Ispis poruke o slanju
        printf("Broj poslat na servis: %3d\n", broj);

        bytesReceived = recv(sockfd, buffer, sizeof(buffer), 0);
        if (bytesReceived <= 0) {
            if (bytesReceived == 0) {
                printf("Server je prekinuo vezu!\n");
                printf("Pritisnite bilo koji taster da zatvorite klijensku aplikaciju...");
                char c = getchar();
                break;
            }
            else {
                printf("Server je zatvorio vezu!\n");
                printf("Pritisnite bilo koji taster da zatvorite klijensku aplikaciju...");
                char c = getchar();
                break;
            }
        }
        else {
            if (bytesReceived > 0 && bytesReceived < 1023) {
                buffer[bytesReceived] = '\0';
                //printf("Server: %s\n", buffer);
            }
            else {
                printf("Pritisnite bilo koji taster da zatvorite klijensku aplikaciju...");
                char c = getchar();
                break;
            }
        }

        Sleep(500); // pauza do sledeceg slanja
    } while (bytesReceived > 0);

    // Zatvaranje socket-a i čišćenje Winsock-a
    closesocket(sockfd);
    WSACleanup();

    return 0;
}
