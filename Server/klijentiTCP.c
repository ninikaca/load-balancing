#include "klijentiTCP.h"

unsigned int __stdcall PrihvatKlijentaTCP(void* parametri) {
    LoadBalancerParametri *params = (LoadBalancerParametri*)parametri;
    SOCKET clientSocket = *params->klijent;
    HANDLE* workers = params->workers;
    unsigned int* brojSkladistenihPodataka = params->brojSkladistenihPodatakaWorker;
    Red* red = params->red;

    char buffer[1024] = "", poruka[] = "Podatak je primljen od strane servisa!";
    char greska[] = "Greska prilikom prijema od strane servisa!";
    int bytesReceived = 0, broj = 0;

    do {
        int bytesReceived = recv(clientSocket, (char*)&broj, sizeof(broj), 0);
        if (bytesReceived <= 0) {
            if (bytesReceived == 0) {
                printf("Klijent je prekinuo vezu!\n");
                break;
            }
            else {
                printf("Greska pri prijemu podataka od klijenta!\n");
                break;
            }
            break;
        }
        else {
            if (bytesReceived < 1023) {
                buffer[bytesReceived] = '\0';
                sscanf_s(buffer, "%d", &broj);

                // Prijavi load balancer-u da odradi raspodelu podataka posto je primio novi zahtev
                int uspesno = IzvrsiSkladistenje(params, broj);

                if (uspesno == 0) {
                    //printf("Podatak uspesno skladisten!\n");
                    send(clientSocket, poruka, (int)strlen(poruka), 0);
                }
                else {
                    printf("Neocekivana greska prilikom skladistenja podatka!\n");
                    send(clientSocket, greska, (int)strlen(greska), 0);
                }
            }
            else {
                printf("Klijent je poslao previse podataka!\n");
                printf("Pritisnite bilo koji taster da zatvorite serversku aplikaciju...");
                char c = getchar();
                break;
            }
        }
    } while (1);

    // Zatvaranje soketa
    closesocket(clientSocket);
    _endthread();

    return 0;
}
