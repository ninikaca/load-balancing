#ifndef TESTOVI_H
#define TESTOVI_H

#include <stdio.h>
#include <stdlib.h>	
#include <WinSock2.h>
#include <stdbool.h>
#include "../Common/RadSaRedom.h"
#include "loadBalancer.h"

bool Test_Red(const unsigned long broj_podataka);

bool Test_Propusnosti(const unsigned long broj_podataka, const unsigned short broj_workera);

#endif // TESTOVI_H
