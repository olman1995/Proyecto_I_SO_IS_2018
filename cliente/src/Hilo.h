
void *print_message_function( void *nodo ){
		 Nodo *informacion;
	     informacion = (Nodo *) nodo;

	     iniciar(informacion);

}

void iniciar_hilo(Nodo *nodo){
	int retorno;

	retorno = pthread_create(&nodo->hilo,NULL,&print_message_function,(void*)nodo);
	if(retorno){
		fprintf(stderr,"Error - pthread_create() return code: %d\n",retorno);
	}

	pthread_join( nodo->hilo, NULL);
}
