#include "loadBalancer.h"

int IzvrsiSkladistenje_(LoadBalancerParametri* parametri, int podatak) {
    // Dereferenciranje parametara i raspakivanje u lokalne promenljive
    unsigned int* brojSkladistenihPodatakaWorker = parametri->brojSkladistenihPodatakaWorker;
    Red* red = parametri->red;
    CRITICAL_SECTION cs = parametri->cs;
    HANDLE* workers = parametri->workers;
    int maxWorker = parametri->maxBrojWorker;

    // Koji worker ima najmanje podataka, pamti se njegov indeks
    EnterCriticalSection(&cs);

    int minIndex = 0;
    for (int i = 1; i < maxWorker; i++) {
        if (brojSkladistenihPodatakaWorker[i] < brojSkladistenihPodatakaWorker[minIndex]) {
            minIndex = i;
        }
    }

    brojSkladistenihPodatakaWorker[minIndex] += 1;

    LeaveCriticalSection(&cs);

    // Slanje podatka na najmanje "opterecenog" workera
    WorkerParametri wp = { brojSkladistenihPodatakaWorker, red, podatak };
    workers[minIndex] = (HANDLE)_beginthreadex(NULL, 0, &Skladistenje, (void *)&wp, 0, NULL);
    
    if (workers[minIndex] != NULL) {
        WaitForSingleObject(workers[minIndex], 1000);
        CloseHandle(workers[minIndex]);
    }

    printf("[Skladiste ID = %d]: Podatak skladisten u skladiste.\n", minIndex);

    return 0;
}
