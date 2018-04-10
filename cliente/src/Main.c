#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include "Cola.h"
#include "Cliente.h"
#include "GenerarProceso.h"
#include "LeerArchivo.h"
#include  "Hilo.h"

//cd Escritorio/Progamacion_I_SO/git/Proyecto_I_SO_IS_2018/cliente/Debug/
int main(int argc, char *argv[])
{

	Cola *cola=(Cola*)malloc(sizeof(Cola));
	int tiempo;
	if (argc <= 1){
		generar(cola,1);
	}else{
		leer_archivo(cola,argv[1]);
	}

	Nodo *actual;
	actual = cola->inicio;


	printf("\033[H\033[J");

	while(actual != NULL){
		printf("*****************************************\n");
		printf("*                CLIENTE                *\n");
		printf("*****************************************\n");

		if (argc <= 1){
			generar(cola,1);
		}

		iniciar_hilo(actual);
		actual = actual->siguiente;
		imprimir(cola);
		tiempo = (rand() % 5) +3;
		//tiempo = 1;
		sleep(tiempo);
		printf("\033[H\033[J");
	}
	printf("*****************************************\n");
	printf("*                CLIENTE                *\n");
	printf("*****************************************\n");
	imprimir(cola);
	return 0;
}
