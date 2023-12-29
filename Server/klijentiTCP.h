#ifndef KLIJENTI_TCP_H
#define KLIJENTI_TCP_H

#include <stdio.h>
#include <WinSock2.h>
#include <process.h>
#include "../Common/parametriLoadBalancer.h"
#include "loadBalancer.h"

/**
 * @file klijentiTCP.h
 * @brief Definicije funkcija za rad sa TCP klijentima.
 */

 /**
  * @brief Prihvatanje klijenta preko TCP veze.
  *
  * Funkcija za prihvatanje dolaznog klijenta preko TCP veze.
  * Obradjuje dolazne podatke od klijenta, a zatim zatvara vezu.
  *
  * @param parametri Parametri za rad sa klijentom.
  * @return Vrednost 0 ako je sve uspesno izvrseno.
  */
unsigned int __stdcall PrihvatKlijentaTCP(void* parametri);

#endif /* KLIJENTI_TCP_H */
