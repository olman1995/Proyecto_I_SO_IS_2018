#include <stdio.h>
#include "Cola.h"
#include "Servidor.h"
#include  "Hilo.h"

int main(int argc, int *argv[])
{

	Cola *cola=(Cola*)malloc(sizeof(Cola));

	cola->estado=0;
	cola->tipo=strtol(argv[1], NULL, 10);
	if(strtol(argv[1], NULL, 10)==4){
		cola->quatun=strtol(argv[2], NULL, 10);
	}else{
		cola->quatun=0;
	}

	cola->tiempo=0;

	printf("\033[H\033[J");
	iniciar_hilo(cola);
	return 0;

}
