

void leer_archivo(Cola *cola,char * direccion){
	FILE* fichero;



    fichero = fopen(direccion, "r");



	int burst;
	int prioridad;
	int c;
	int leer_busrt;
	int temporal;
	temporal = 0;
	leer_busrt=1;
	c = getc(fichero);
	while( c != 70){
		if(c == 10){
			insertar(cola,0,0,burst,prioridad);
			leer_busrt = 1;
			burst = 0;
		}


		if(c == 32){
			leer_busrt = 0;
		}

		if(leer_busrt){
			if(c !=10){
				temporal = burst * 10;
				burst  = c-48;
				burst = temporal + burst;
			}

		}else{
			if(c != 32){
				prioridad =  c-48;
			}
		}

		c = getc(fichero);
	}

	fclose(fichero);

}
