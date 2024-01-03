#include "Testovi.h"

int main() {
	// Test I
	printf("[Test I]: Provera strukure podataka Red\n");
	int broj_podataka = 0;

	while (broj_podataka <= 0) {
		printf("[Test I]: Unesite broj podataka za dodavanje u red: ");
		scanf_s("%ld", &broj_podataka);
	}
	printf("[Test I]: Pokretanje testa strukure podataka Red\n");
	if (Test_Red(broj_podataka)) {
		printf("[Test I]: Test je uspesan!\n");
	}
	else {
		printf("[Test I]: Test nije uspesan!\n");
	}

	// Test II
	printf("\n---------------------------------------------------------------\n");
	printf("\n[Test II]: Provera propusnosti sistema\n");
	broj_podataka = 0;
	short broj_workera = 0;

	while (broj_podataka <= 0) {
		printf("[Test II]: Unesite broj podataka za dodavanje u red: ");
		scanf_s("%ld", &broj_podataka);
	}

	while (broj_workera <= 0) {
		printf("[Test II]: Unesite broj worker-a: ");
		scanf_s("%hd", &broj_workera);
	}

	printf("[Test II]: Pokretanje testa propusnosti sistema\n");
	if (Test_Propusnosti(broj_podataka, broj_workera)) {
		printf("[Test II]: Test je uspesan!\n");
	}
	else {
		printf("[Test II]: Test nije uspesan!\n");
	}
	printf("---------------------------------------------------------------\n");

	return 0;
}