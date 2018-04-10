
void *administrador_procesos( void * cola ){


		 Cola *informacion;
	     informacion = (Cola *) cola;
	     iniciar(informacion);

}
int algoritmo(Cola *llegada){
	int pid;
	if(llegada->tipo==1){
			pid=fifo(llegada);
	}else if(llegada->tipo==2){
			pid=sjf(llegada);
	}else if(llegada->tipo==3){
			pid=hpf(llegada);
	}else{
			pid=fifo(llegada);
	}

	return pid;
}
void *administrador_cpu( void *cola ){

		 Cola * llegada;
		 Nodo * temporal = NULL;
		 Nodo * eliminado = NULL;
	     llegada = (Cola *) cola;
	     Cola * salida=(Cola*)malloc(sizeof(Cola));
	     int pid;
	     int contar=0;
	     int ocioso=0;
	     while(1){

	    	 if(llegada->estado==1){
	    		 llegada->tiempo=llegada->tiempo+1;
	    	 }

	    	 if(llegada->tipo==4){
	    		 if(llegada->inicio != NULL || temporal != NULL ){


	    			 if(temporal == NULL){
	    				 contar=0;
	    				 temporal= llegada->inicio;
	    			 }
	    			 temporal->ejecucion= temporal->ejecucion-1;

	    			 if(temporal->ejecucion <= 0){
						 pid=temporal->pid;


						 if(temporal->siguiente==NULL){
								 temporal = NULL;
						 }else{
							 contar=0;
							 temporal = temporal->siguiente;
						 }

						 eliminado = eliminar(llegada,pid);
						 eliminado->siguiente = NULL;
						 eliminado->tiempo_salida = llegada->tiempo;
						 eliminado->TAT= eliminado->tiempo_salida - eliminado->tiempo_llegada;
						 eliminado->WT=eliminado->TAT - eliminado->burst;
						 insertar_nodo(salida,eliminado);

					 }else{
						 contar=contar+1;
	    			 	 if(llegada->quatun == contar){
	    				 	 contar=0;
	    				 	 if(temporal->siguiente==NULL){
							 	 temporal = NULL;
						 	 }else{
							 	 temporal = temporal->siguiente;
						 	 }
	    			 	 }
					 }

	    		 }else{
	    	    	 if(llegada->estado==1){
	    	    		 ocioso=ocioso+1;
	    	    	 }

	    		 }
	    	 }else{

		    	 if(llegada->inicio != NULL || temporal != NULL){

			    	if(temporal==NULL){
			    		pid=algoritmo(llegada);
			    		temporal = eliminar(llegada,pid);

			    	}

			    	temporal->ejecucion=temporal->ejecucion-1;

			    	if(temporal->ejecucion <= 0){
			    		temporal->siguiente=NULL;
			    		temporal->tiempo_salida=llegada->tiempo;

						temporal->TAT= temporal->tiempo_salida - temporal->tiempo_llegada;
						temporal->WT=temporal->TAT - temporal->burst;

			    		insertar_nodo(salida,temporal);

			    		temporal=NULL;
			    	}
		    	 }else{
		    		 if(llegada->estado==1){
						 ocioso=ocioso+1;
		    		 }
		    	 }
	    	 }
			printf("************************************************************************************************\n");
			printf("*                                     SERVIDOR                                                 *\n");
			printf("************************************************************************************************\n");
	    	printf("------------------------------------  LLEGADA  ----------------------------------------------\n");
			imprimir(llegada);
			printf("------------------------------------  CPU      ----------------------------------------------\n");
			if(temporal != NULL){
				imprimir_nodo(temporal);
			}
			printf("------------------------------------  SALIDA   ----------------------------------------------\n");
			imprimir(salida);
			printf("------------------------------------  INFOMACION   ------------------------------------------\n");

			printf("Promedio WT:%.2f  Promedio TAT:%.2f  Ocioso:%d \n",
					promedio_wt(salida),promedio_tat(salida),ocioso);

			printf("\033[H\033[J");
	    	sleep(1);
		}

}



void iniciar_hilo(Cola *cola){
	int retorno;
	pthread_t hilo_1;
	pthread_t hilo_2;

	retorno = pthread_create(&hilo_1,NULL,&administrador_procesos,(void*)cola);
	if(retorno){
		fprintf(stderr,"Error - pthread_create() return code: %d\n",retorno);
	}

	retorno = pthread_create(&hilo_2,NULL,&administrador_cpu,(void*)cola);
	if(retorno){
		fprintf(stderr,"Error - pthread_create() return code: %d\n",retorno);
	}

	pthread_join( hilo_1, NULL);
	pthread_join( hilo_2, NULL);
}
