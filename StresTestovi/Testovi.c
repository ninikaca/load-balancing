#include "Testovi.h"

bool Test_Red(const unsigned long broj_podataka) {
    Red red;
    inicijalizujRed(&red);

    // Dodajemo podatke u red
    for (unsigned long i = 0; i < broj_podataka; ++i) {
        dodajURed(&red, i);
    }

    // Provera da li je red prazan
    if (jePrazan(&red)) {
        printf("GRESKA: Red je neocekivano prazan nakon dodavanja elemenata.\n");
        return false;
    }

    // Uklanjamo elemente iz reda
    for (unsigned long i = 0; i < broj_podataka; ++i) {
        int podatak = ukloniIzReda(&red);
        if (podatak != i) {
            printf("GRESKA: Neocekivani podatak %d umesto %lu\n", podatak, i);
            return false;
        }
    }

    // Provera da li je red prazan nakon uklanjanja svih elemenata
    if (!jePrazan(&red)) {
        printf("GRESKA: Red nije prazan nakon uklanjanja svih elemenata.\n");
        return false;
    }

    // Uni�tavanje reda i oslobadjanje resursa
    unistiRed(&red);

    return true;
}

bool Test_Propusnosti(const unsigned long broj_podataka, const unsigned short broj_workera) {
    if (broj_workera <= 0 || broj_workera > 10) {
        printf("GRESKA: Broj Worker-a mora biti u opsegu od 1 do 10.\n");
        return false;
    }

    Red red;
    unsigned int *brojSkladistenihPodatakaWorker = (unsigned int *)malloc(broj_workera * sizeof(unsigned int));
    HANDLE* workers = (HANDLE*)malloc(broj_workera * sizeof(HANDLE));
    LoadBalancerParametri parametri = { brojSkladistenihPodatakaWorker, NULL, &red, workers, broj_workera };

    // Inicijalizacija reda
    inicijalizujRed(&red);

    // Inicijalizacija kriticne sekcije
    InitializeCriticalSection(&parametri.cs);

    // Da li je uspesno alociranje memorije
    if (brojSkladistenihPodatakaWorker == NULL || workers == NULL) {
        printf("GRESKA: Neuspesno alocitanje memorije za worker-e.\n");
        return false;
    }

    // Generisanje podataka
    for (unsigned long i = 0; i < broj_podataka; ++i) {
        dodajURed(&red, i);
    }

    // Provera da li je red prazan
    if (jePrazan(&red)) {
        printf("GRESKA: Red je neocekivano prazan nakon dodavanja elemenata.\n");
        return false;
    }

    for (unsigned long i = 0; i < broj_podataka; i++) {
        int podatak = ukloniIzReda(&red);

        if (podatak != i) {
            printf("GRESKA: Neocekivani podatak %d umesto %lu\n", podatak, i);

            // Oslobadjanje resursa
            free(brojSkladistenihPodatakaWorker);
            free(workers);

            // Brisanje kriticne sekcije
            DeleteCriticalSection(&parametri.cs);

            // Brisanje reda
            unistiRed(&red);

            return false;
        }

        // Prijavi load balancer-u da odradi raspodelu podataka posto je primio novi zahtev
        int uspesno = IzvrsiSkladistenje_(&parametri, podatak);

        if (uspesno != 0) {
            return false;
        }
    }

    // Oslobadjanje resursa
    unistiRed(&red);
    free(brojSkladistenihPodatakaWorker);
    free(workers);

    // Brisanje kriticne sekcije
    DeleteCriticalSection(&parametri.cs);

    return true;
}