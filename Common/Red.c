// Red.c

#include "Red.h"

// Funkcija za inicijalizaciju reda
void inicijalizujRed(Red* red) {
    red->pocetak = red->kraj = NULL;
    InitializeCriticalSection(&red->kriticna_sekcija);
}

// Funkcija za dodavanje elementa u red
void dodajURed(Red* red, int vrednost) {
    RedCvor* noviCvor = (RedCvor*)malloc(sizeof(RedCvor));
    if (noviCvor == NULL) {
        // Obrada greške ako alokacija memorije nije uspela
        return;
    }
    noviCvor->podatak = vrednost;
    noviCvor->sledeci = NULL;

    EnterCriticalSection(&red->kriticna_sekcija);

    if (red->kraj == NULL) {
        red->pocetak = red->kraj = noviCvor;
    }
    else {
        red->kraj->sledeci = noviCvor;
        red->kraj = noviCvor;
    }

    LeaveCriticalSection(&red->kriticna_sekcija);
}

// Funkcija za uklanjanje elementa iz reda
int ukloniIzReda(Red* red) {
    EnterCriticalSection(&red->kriticna_sekcija);

    if (jePrazan(red)) {
        LeaveCriticalSection(&red->kriticna_sekcija);
        return INT_MIN; // Vraća minimalnu vrednost za int kao indikator greške ili praznog reda
    }

    RedCvor* temp = red->pocetak;
    int podatak = temp->podatak;

    red->pocetak = red->pocetak->sledeci;

    if (red->pocetak == NULL) {
        red->kraj = NULL;
    }

    free(temp);

    LeaveCriticalSection(&red->kriticna_sekcija);

    return podatak;
}

// Funkcija za proveru da li je red prazan
bool jePrazan(Red* red) {
    return red->pocetak == NULL;
}

// Funkcija za uništavanje reda
void unistiRed(Red* red) {
    while (!jePrazan(red)) {
        ukloniIzReda(red);
    }
    DeleteCriticalSection(&red->kriticna_sekcija);
}
