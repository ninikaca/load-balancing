#ifndef RED_CVOR_H
#define RED_CVOR_H

/*
    Struktura koja predstavlja cvor u redu.

    Atributi:
        int podatak: Primer podataka koji se cuva u cvoru.
        struct RedCvor* sledeci: Pokazivac na sledeci cvor.
*/
typedef struct RedCvor {
    int podatak;
    struct RedCvor* sledeci;
} RedCvor;

#endif /* RED_CVOR_H */
