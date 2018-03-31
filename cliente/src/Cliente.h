#include <arpa/inet.h>
//#include <stdio.h>
//#include <string.h>
#include <sys/socket.h>
#include <unistd.h>

typedef struct _Cliente {

	const char* nombre_servidor ;
	int puerto ;
	struct sockaddr_in direccion_servidor;
	int socket;

}Cliente;



void iniciar(Nodo *nodo){
	const char* datos_enviados[10] ;
	Cliente cliente;
	cliente.nombre_servidor = "localhost";
	cliente.puerto = 8877;


	//datos_enviados=(char*)&burst;

	sprintf(datos_enviados, "%d %d",nodo->burst,nodo->prioridad);

	//cliente.datos_enviados="burst";


	memset(&cliente.direccion_servidor, 0, sizeof(cliente.direccion_servidor));
	cliente.direccion_servidor.sin_family = AF_INET;
	inet_pton(AF_INET, cliente.nombre_servidor , &cliente.direccion_servidor.sin_addr);
	cliente.direccion_servidor.sin_port = htons(cliente.puerto);



	if ((cliente.socket = socket(PF_INET, SOCK_STREAM, 0)) < 0) {
		printf("No se pudo crear un socket\n");
		return ;
	}

	if (connect(cliente.socket, (struct sockaddr*)&cliente.direccion_servidor,
	            sizeof(cliente.direccion_servidor)) < 0) {
		printf("No se pudo conectar al server\n");
		return ;
	}




	send(cliente.socket,datos_enviados, strlen(datos_enviados), 0);

	int n = 0;
	int len = 0, maxlen = 3;
	char buffer[maxlen];
	char* pbuffer = buffer;


	n = recv(cliente.socket, pbuffer, maxlen, 0);



	pbuffer += n;
	maxlen -= n;
	len += n;

	//buffer[len] = '\0';
	int pid = 0;
	int temporal= 1;
	int cambio = 1;


	for(int i = 0; i< len ; i++){
		if(buffer[i]==0){
			cambio=0;
		}
		if(cambio){
			temporal = pid * 10;
			pid  = buffer[i]-48;
			pid = temporal + pid;
		}

	}
	nodo->pid=pid;
	//

	close(cliente.socket);
}

