#ifndef LOADBALANCER_PARAMETRI_H
#define LOADBALANCER_PARAMETRI_H

#include "../Common/Red.h"
#include <WinSock2.h>

/*
 * Struktura LoadBalancerParametri:
 * --------------------------------
 * Struktura koja sadrzi parametre koji se koriste za Load Balancer.
 *
 * Clanovi strukture:
 *  - brojSkladistenihPodatakaWorker: Niz broja skladistenih podataka radnika (workers).
 *  - klijent: Pokazivac na socket za klijenta.
 *  - red: Pokazivac na strukturu Red koja predstavlja red sa podrskom za sinhronizaciju pristupa.
 *  - workers: Pokazivac na niz handles za niti radnika (workers).
 *  - maxBrojWorker: Maksimalni broj radnika (workers).
 *  - cs: Kriticna sekcija za sinhronizaciju pristupa parametrima.
 */
typedef struct LoadBalancerParametri {
    unsigned int* brojSkladistenihPodatakaWorker;
    SOCKET* klijent;
    Red* red;
    HANDLE* workers;
    int maxBrojWorker;
    CRITICAL_SECTION cs;
} LoadBalancerParametri;

#endif /* LOADBALANCER_PARAMETRI_H */
