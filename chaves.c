#include <stdio.h>
#include <string.h>
#include <conio.h>
#include "comum.h"
#include "esone.h"

int subAdress = 0;
int qx =0;
int funcao = 0;
short shortData;
int branchAux = BRANCH;
int crateAux = CRATE;
int moduloRele219 = MODULO_RELE_219;

void levantarChave(int banco){
	cdreg(&ext, &branchAux, &crateAux, &moduloRele219, &subAdress);
	shortData = 0x0883; //mantem hv off e desacopla os bancos
	
	funcao = 16; 
	cssa(&funcao, &ext, &shortData, &qx);

	funcao = 25; //f25 carrega registrador e o executa
	cssa(&funcao, &ext, &shortData, &qx);
}

void baixarChave(int banco){
	cdreg(&ext, &branchAux, &crateAux, &moduloRele219, &subAdress);
	shortData = 0x0883; 
	
	funcao = 16; 
	cssa(&funcao, &ext, &shortData, &qx);

	funcao = 25; //f25 carrega registrador e o executa
	cssa(&funcao, &ext, &shortData, &qx);
}

