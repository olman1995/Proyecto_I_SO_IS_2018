
void generar(Cola *cola,int cantidad){
	int burst;
	int prioridad;
	srand(time(NULL));
	for(int i=1; i < cantidad+1; i++ ){
		burst  = (rand() % 5) +1;
		prioridad =  (rand() % 5) +1;
		insertar(cola,i,0,burst,prioridad);
	}

}

