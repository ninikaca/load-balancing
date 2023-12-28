#ifndef RED_H
#define RED_H

#include <stdlib.h>
#include <stdbool.h>
#include <WinSock2.h>
#include "RedCvor.h"

/*
 * Struktura Red:
 * --------------
 * Struktura koja predstavlja red sa podrškom za sinhronizaciju pristupa (thread-safe queue).
 *
 * Clanovi strukture:
 *  - pocetak: Pokazivac na prvi element u redu.
 *  - kraj: Pokazivac na poslednji element u redu.
 *  - kriticna_sekcija: Kritična sekcija za sinhronizaciju pristupa redu.
 */
typedef struct {
    RedCvor* pocetak;
    RedCvor* kraj;
    CRITICAL_SECTION kriticna_sekcija; // Kritična sekcija za sinhronizaciju pristupa redu
} Red;

#endif /* RED_H */
