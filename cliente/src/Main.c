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
int main()
{

	Cola *cola=(Cola*)malloc(sizeof(Cola));


	//leer_archivo(cola,10);
	generar(cola,1);
	Nodo *actual;
	actual = cola->inicio;


	printf("\033[H\033[J");
	while(actual != NULL){

		generar(cola,1);
		iniciar_hilo(actual);
		actual = actual->siguiente;
		imprimir(cola);
		sleep(2);
		printf("\033[H\033[J");
	}
	imprimir(cola);
	return 0;
}
