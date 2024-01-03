#ifndef WORKER_H
#define WORKER_H

#include <stdio.h>
#include <time.h>
#include "../Common/Red.h"
#include "../Common/parametriWorker.h"
#include "../Common/RadSaRedom.h"

/**
 * @file worker.h
 * @brief Deklaracije funkcija za rad sa worker-om.
 */

 /**
  * @brief Funkcija za skladistenje podataka.
  *
  * Funkcija za skladistenje podataka u red koji se koristi od strane worker-a.
  *
  * @param parametri Parametri koji se koriste za skladistenje podataka.
  * @return Vrednost 0 kao indikator uspesnog skladistenja podataka.
  */
unsigned int _stdcall Skladistenje(void* parametri);

#endif // WORKER_H
