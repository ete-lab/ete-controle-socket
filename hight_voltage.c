#include <stdio.h>
#include <string.h>
#include <esone.h>
#include <conio.h>
#include "comum.h"

int subAdress = 0;
int qx =0;
int funcao = 0;
short shortData;

void hv_on(int banco){
	cdreg(&ext, &branch, &crate, &moduloRele219, &subAdress);
	shortData = 0x0883; //mantem hv off e desacopla os bancos
	
	funcao = 16; //f16 escreve no registro do módulo 219
	cssa(&funcao, &ext, &shortData, &qx);

	funcao = 25; //f25 carrega registrador e o executa
	cssa(&funcao, &ext, &shortData, &qx);
}

void hv_off(int banco){
	cdreg(&ext, &branch, &crate, &moduloRele219, &subAdress);
	shortData = 0x0883; //mantem hv off e desacopla os bancos
	
	funcao = 16; //f16 escreve no registro do módulo 219
	cssa(&funcao, &ext, &shortData, &qx);

	funcao = 25; //f25 carrega registrador e o executa
	cssa(&funcao, &ext, &shortData, &qx);
}

void hv_off_all(){

	cdreg(&ext, &branch, &crate, &moduloRele219, &subAdress);
	shortData = 0x1987; //mantem hv off e desacopla os bancos
	
	funcao = 16; //f16 escreve no registro do módulo 219
	cssa(&funcao, &ext, &shortData, &qx);

	funcao = 25; //f25 carrega registrador e o executa
	cssa(&funcao, &ext, &shortData, &qx);
}