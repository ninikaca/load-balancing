#ifndef WORKER_PARAMS_H
#define WORKER_PARAMS_H

#include "Red.h"

/*
 * Struktura WorkerParametri:
 * --------------------------
 * Ova struktura sadrzi parametre potrebne radnoj niti (worker thread).
 *
 * Clanovi strukture:
 *  - workersSkladisteniPodaci: Pokazivac na niz koji sadrzi podatke koje su radnici skladistili.
 *  - red: Pokazivac na strukturu Red koja predstavlja red (queue).
 *  - podatak: Cela vrednost koja ce biti obradjena od strane radne niti.
 */
typedef struct WorkerParametri {
    unsigned int* workersSkladisteniPodaci;
    Red* red;
    int podatak;
} WorkerParametri;

#endif // WORKER_PARAMS_H
