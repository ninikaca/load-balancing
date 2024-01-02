#include "worker.h"

unsigned int _stdcall Skladistenje(void *parametri) {
	WorkerParametri* params = (WorkerParametri*)parametri;
	unsigned int* workersSkladisteniPodaci = params->workersSkladisteniPodaci;
	Red* red = params->red;
	int podatak = params->podatak;

	// Skladistiti podatak u red
	dodajURed(red, podatak);
	
	return 0;
}