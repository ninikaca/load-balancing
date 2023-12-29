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

   

    // Zatvaranje soketa
    closesocket(clientSocket);
    _endthread();

    return 0;
}
