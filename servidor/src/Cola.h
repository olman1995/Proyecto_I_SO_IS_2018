#include <stdio.h>
#include <stdlib.h>
#include <unistd.h> // necesaria para ejecutar fork()
#include <stdlib.h> // necesaria para ejecutar exit().
//#include <pthread.h>

typedef struct Nodo
{

  int pid;
  int burst;
  int prioridad;
  int ejecucion;
  int tiempo_llegada;
  int tiempo_salida;
  int TAT;
  int WT;
  struct Nodo *siguiente;
  struct Nodo *anterior;

}Nodo;

typedef struct Cola{
	int tipo;
	int quatun;
	  int tiempo;
	  int estado;
	struct Nodo *fin;
	struct Nodo *inicio;

}Cola;


void insertar(Cola *cola,int dato_pid,int dato_burst,int dato_prioridad
		,int tiempo)
{
  Nodo *dato;
  dato=(Nodo*)malloc(sizeof(Nodo));
  dato->pid=dato_pid;
  dato->burst=dato_burst;
  dato->prioridad= dato_prioridad;

  dato->ejecucion=dato_burst;
  dato->tiempo_llegada=tiempo;
  dato->tiempo_salida=0;
  dato->WT=0;
  dato->TAT=0;
  dato->siguiente=NULL;


  if(cola->fin==NULL){
	  cola->fin=dato;
	  cola->inicio=dato;

  }else{
	dato->anterior=cola->fin;
	cola->fin->siguiente=dato;
	cola->fin=dato;
  }
}


void insertar_nodo(Cola *cola, Nodo *dato)
{


  if(cola->fin==NULL){
	  cola->fin=dato;
	  cola->inicio=dato;

  }else{

	dato->anterior=cola->fin;
	cola->fin->siguiente=dato;
	cola->fin=dato;
  }
}

Nodo *eliminar(Cola *cola,int pid){
	Nodo *actual;
	actual = cola->inicio;

	while(actual != NULL){
		if(actual->pid == pid){
		    if(actual->anterior == NULL && actual->siguiente == NULL){
		    	cola->inicio=NULL;
		    	cola->fin=NULL;
		    }
		    else if(actual->anterior == NULL){
		    	cola->inicio=actual->siguiente;
		    	actual->siguiente->anterior = NULL;
		    }
		    else if(actual->siguiente == NULL){
		    	cola->fin = actual->anterior;
				actual->anterior->siguiente = NULL;
			}else{
				actual->siguiente->anterior = actual->anterior;
				actual->anterior->siguiente = actual->siguiente;

			}
			return actual;
		}
		actual = actual->siguiente;
	}
	return NULL;
}


int fifo(Cola *cola){
	Nodo *actual;
	Nodo *temporal;
	actual = cola->inicio;
	temporal = cola->inicio;
	while(actual != NULL){
		if(actual->pid < temporal->pid && actual->burst!=0){
			temporal = actual;
		}
		actual = actual->siguiente;
	}
	int pid =temporal->pid;
	return pid;
}

int sjf(Cola *cola){
	Nodo *actual;
	Nodo *temporal;
	actual = cola->inicio;
	temporal = cola->inicio;
	while(actual != NULL){
		if(actual->burst < temporal->burst){
			temporal = actual;
		}else if(actual->burst == temporal->burst){
			if(actual->pid < temporal->pid){
				temporal = actual;
			}
		}
		actual = actual->siguiente;
	}
	int id =temporal->pid;
	return id;
}
int hpf(Cola *cola){
	Nodo *actual;
	Nodo *temporal;
	actual = cola->inicio;
	temporal = cola->inicio;
	while(actual != NULL){
		if(actual->prioridad < temporal->prioridad){
			temporal = actual;
		}else if(actual->burst == temporal->burst){
			if(actual->pid < temporal->pid){
				temporal = actual;
			}
		}
		actual = actual->siguiente;
	}
	int pid =temporal->pid;
	return pid;
}
int rr(Cola *cola,int quantun){
	Nodo *actual;
	Nodo *temporal;
	actual = cola->inicio;
	temporal = cola->inicio;
	while(actual != NULL){
		if(actual->pid < temporal->pid){
			temporal = actual;
		}
		actual = actual->siguiente;
	}
	int pid =temporal->pid;
	return pid;
}
float promedio_wt(Cola *cola){
	float promedio = 0;
	float contar = 0;
	Nodo *actual;
	actual = cola->inicio;
	while(actual != NULL){
		promedio = promedio + actual->WT;
		contar = contar + 1;
		actual = actual->siguiente;
	}

	if(contar == 0){
		return promedio;
	}else{
		return promedio/contar;
	}

}
float promedio_tat(Cola *cola){
	float promedio = 0;
	float contar = 1;
	Nodo *actual;
	actual = cola->inicio;
	while(actual != NULL){
		promedio = promedio + actual->TAT;
		contar = contar + 1;
		actual = actual->siguiente;
	}
	if(contar == 0){
		return promedio;
	}else{
		return promedio/contar;
	}
}
void imprimir(Cola *cola){
	Nodo *actual;
	actual = cola->inicio;
	while(actual != NULL){
		printf(" PID: %d  \t B: %d \t P: %d \t E: %d \t T_L: %d \t T_S: %d \t TAT: %d \t WT: %d \n",
				actual->pid,actual->burst,actual->prioridad
				,actual->ejecucion,actual->tiempo_llegada
				,actual->tiempo_salida,actual->TAT,actual->WT);
		actual = actual->siguiente;
	}

}
void imprimir_nodo(Nodo *actual){
	printf(" PID: %d  \t B: %d \t P: %d \t E: %d \t T_L: %d \t T_S: %d \t TAT: %d \t WT: %d \n",
			actual->pid,actual->burst,actual->prioridad
			,actual->ejecucion,actual->tiempo_llegada
			,actual->tiempo_salida,actual->TAT,actual->WT);
}
