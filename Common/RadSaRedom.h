#ifndef RED_FUNCTIONS_H
#define RED_FUNCTIONS_H

#include "Red.h"

/*
    @brief Funkcija za inicijalizaciju reda (queue).
    
    Inicijalizuje red postavljajuci pokazivace pocetka i kraja na NULL i 
    inicijalizuje kriticnu sekciju za sinhronizaciju pristupa redu.

    @param Red* red: Pokazivac na crvenu listu koju treba inicijalizovati.
*/
inline void inicijalizujRed(Red* red) {
    red->pocetak = red->kraj = NULL;
    InitializeCriticalSection(&red->kriticna_sekcija);
}

/*
    @brief Funkcija za proveru da li je red prazan.
    @param Red* red: Pokazivac na listu koju treba proveriti.
    @return bool: Vraca vrednost 'true' ako je red prazan, inace 'false'.
*/
inline bool jePrazan(Red* red) {
    return red->pocetak == NULL;
}

/**
    @brief Funkcija za dodavanje elementa u red.
    @param Red* red: Pokazivac na red u koji se dodaje element.
    @param int vrednost: Vrednost koja se dodaje u red.
**/
inline void dodajURed(Red* red, int vrednost) {
    RedCvor* noviCvor = (RedCvor*)malloc(sizeof(RedCvor));
    if (noviCvor == NULL) {
        // Obrada greske ako alokacija memorije nije uspela
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

/**
    @brief Funkcija za uklanjanje elementa iz reda.
    @param Red* red: Pokazivac na red iz koje se uklanja element.
    @return
        int: Vraca vrednost elementa koji je uklonjen iz reda.
             Ako je red prazan, vraca minimalnu vrednost za int kao indikator greske ili praznog reda.
**/
inline int ukloniIzReda(Red* red) {
    EnterCriticalSection(&red->kriticna_sekcija);

    if (jePrazan(red)) {
        LeaveCriticalSection(&red->kriticna_sekcija);
        return INT_MIN; // Vraca minimalnu vrednost za int kao indikator greske ili praznog reda
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

/**
    @brief Funkcija za unistavanje reda. Oslobadja resurse i red.
    @param Red* red: Pokazivac na red koji se unistava.
**/
inline void unistiRed(Red* red) {
    while (!jePrazan(red)) {
        ukloniIzReda(red);
    }
    DeleteCriticalSection(&red->kriticna_sekcija);
}

#endif /* RED_FUNCTIONS_H */
