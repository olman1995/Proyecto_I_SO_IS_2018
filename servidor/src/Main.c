#include <stdio.h>
#include "Cola.h"
#include "Servidor.h"
#include  "Hilo.h"

int main()
{
	Cola *cola=(Cola*)malloc(sizeof(Cola));
	iniciar(cola);
	return 0;

}
