#include <stdio.h>
#include <stdlib.h>
#include <unistd.h> // necesaria para ejecutar fork()
#include <stdlib.h> // necesaria para ejecutar exit().
//#include <pthread.h>

typedef struct Nodo
{
  int id;
  int pid;
  int burst;
  int prioridad;
  pthread_t hilo;
  struct Nodo *siguiente;
  struct Nodo *anterior;

}Nodo;

typedef struct Cola{
	struct Nodo *fin;
	struct Nodo *inicio;
}Cola;


void insertar(Cola *cola, int dato_id,int dato_pid,int dato_burst,int dato_prioridad)
{
  Nodo *dato;
  dato=(Nodo*)malloc(sizeof(Nodo));
  dato->id=dato_id;
  dato->pid=dato_pid;
  dato->burst=dato_burst;
  dato->prioridad= dato_prioridad;
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


Nodo *eliminar(Cola *cola,int id){
	Nodo *actual;
	actual = cola->inicio;

	while(actual != NULL){
		if(actual->id == id){
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
		if(actual->pid < temporal->pid){
			temporal = actual;
		}
		actual = actual->siguiente;
	}
	int id =temporal->id;
	return id;
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
	int id =temporal->id;
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
	int id =temporal->id;
	return id;
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
	int id =temporal->id;
	return id;
}

void imprimir(Cola *cola){
	Nodo *actual;
	actual = cola->inicio;

	while(actual != NULL){
		printf("PID: %d \t Burst: %d \t Prioridad: %d \n",actual->pid,actual->burst,actual->prioridad);
		actual = actual->siguiente;
	}

}
