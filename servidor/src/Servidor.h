#include <arpa/inet.h>
#include <netinet/in.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

typedef struct _Servidor{
	int puerto ;
	struct sockaddr_in direccion_servidor;
	int socket_escucha;
	struct sockaddr_in direccion_cliente;
	int largo_direccion_cliente ;

}Servidor;

void iniciar(Cola *cola){
		Servidor servidor;
		servidor.puerto = 8877;
		servidor.direccion_servidor;
		servidor.largo_direccion_cliente = 0;

		memset(&servidor.direccion_servidor, 0, sizeof(servidor.direccion_servidor));
		servidor.direccion_servidor.sin_family = AF_INET;
		servidor.direccion_servidor.sin_port = htons(servidor.puerto);
		servidor.direccion_servidor.sin_addr.s_addr = htonl(INADDR_ANY);



		if ((servidor.socket_escucha = socket(PF_INET, SOCK_STREAM, 0)) < 0) {
			printf("No se pudo crear el socket de escucha\n");
			return ;
		}

		if ((bind(servidor.socket_escucha, (struct sockaddr *)&servidor.direccion_servidor,
		          sizeof(servidor.direccion_servidor))) < 0) {
			printf("No se pudo enlazar el soket\n");
			return ;
		}

		int wait_size = 16;
		if (listen(servidor.socket_escucha, wait_size) < 0) {
			printf("No se pudo abri el socket para escuchar\n");
			return ;
		}

		int burst;
		int prioridad;
		int temporal;
		int contar = 0;
		int cambio = 0;
		while (true) {
			int sock;
			if ((sock =
			         accept(servidor.socket_escucha, (struct sockaddr *)&servidor.direccion_cliente,
			                &servidor.largo_direccion_cliente)) < 0) {
				printf("No se pudo abrir el soxket para acpetar datos\n");
				return ;
			}

			int n = 0;
			int len = 0, maxlen = 10;
			char buffer[maxlen];
			char *pbuffer = buffer;
			/*
			printf("client connected with ip address: %s\n",
			       inet_ntoa(client_address.sin_addr));
			*/
			inet_ntoa(servidor.direccion_cliente.sin_addr);

			while ((n = recv(sock, pbuffer, maxlen, 0)) > 0) {
				pbuffer += n;
				maxlen -= n;
				len += n;
				contar = contar +1;

				burst=0;
				prioridad=0;
				temporal=1;
				cambio=1;
				for(int i = 0; i< len ; i++){
					//	printf("value: %d \n",buffer[i]);
					if(buffer[i] == 32){
						cambio=0;
					}else{
						if(cambio){
							temporal = burst * 10;
							burst  = buffer[i]-48;
							burst = temporal + burst;
						}else{
							prioridad =  buffer[i]-48;
						}
					}

				}
				insertar(cola,contar,contar,burst,prioridad);
				imprimir(cola);
				printf("\033[H\033[J");

				sprintf(buffer, "%d",contar);
				send(sock, buffer, len, 0);
			}

			close(sock);
		}

	close(servidor.socket_escucha);
}
