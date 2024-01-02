#ifndef LOADBALANCER_H
#define LOADBALANCER_H

#include "../Common/parametriLoadBalancer.h"
#include <stdio.h>
#include <process.h>
#include "worker.h"
#include "../Common/parametriWorker.h"

/**
 * @file loadBalancer.h
 * @brief Deklaracije funkcija za rad sa load balancer-om.
 */

 /**
  * @brief Izvrsava skladistenje podataka.
  *
  * Funkcija za izvrsavanje skladistenja podataka prema odabranom load balancer-u.
  *
  * @param parametri Parametri koji se koriste za skladistenje podataka.
  * @param podatak Podatak koji se skladisti.
  * @return Vrednost 0 ako je skladistenje uspesno.
  */
int IzvrsiSkladistenje(LoadBalancerParametri* parametri, int podatak);

#endif /* LOADBALANCER_H */
