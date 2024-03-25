#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>
#include <sys/wait.h>
#include <math.h>

#define MAX_SIZE 20

int main(int argc, char * argv[]) {
	struct  sockaddr_in end_servidor;
	int     sd;
	int     n,k;
	double 	vet[MAX_SIZE];
	double  buf_rec[2];

  	if(argc<3)  {
    		printf("OBS - uso correto: %s <ip_do_servidor> <porta_do_servidor>\n", argv[0]);
    		exit(1);
	}
	memset((char *)&end_servidor,0,sizeof(end_servidor));
	memset((int *)&vet,0,sizeof(vet));
	end_servidor.sin_family      = AF_INET;
	end_servidor.sin_addr.s_addr = inet_addr(argv[1]);
	end_servidor.sin_port        = htons(atoi(argv[2]));

	/* Preparando vetor */
	double aux = 0;
	for (int i = 0; i < MAX_SIZE; i++){
		aux = pow ((i - (rand() % MAX_SIZE)/2), 2);
		vet[i] = sqrt(aux);
	} /* fim-for */

	printf("Vetor a ser enviado:\n");
	for (int i = 0; i < MAX_SIZE; i++)
		printf("%6.2f ", vet[i]);
	printf("\n");

	sd = socket(AF_INET, SOCK_STREAM, 0);
	if (sd < 0) {
		fprintf(stderr, " ERROR - Criacao do socket!\n");
		exit(1);
	}
	if (connect(sd, (struct sockaddr *)&end_servidor, sizeof(end_servidor)) < 0) {
		fprintf(stderr,"ERROR - Tentativa de conexao!\n");
		exit(1);
	}
	/* Enviando vetor inicializado para o servidor ...*/
	printf("Enviando vetor para o servidor remoto...\n");
	if (send(sd, &vet, MAX_SIZE * sizeof(double), 0) < 0) {
		fprintf(stderr, "ERROR - Envio de dados ao servidor!\n");
		exit(1);
	}
	/* Recebendo resultado do servidor ... */
	printf("Recebendo resultados...\n");
	if (recv(sd, &buf_rec, sizeof(buf_rec),0) < 0){
		fprintf(stderr, "ERROR - Recebimento de dados do servidor!\n");
		exit(1);
	} else {
		printf("Menor ->  %6.2f\n", buf_rec[0]);
		printf("Maior ->  %6.2f\n", buf_rec[1]);
	}
	printf("Encerrando conexão com o servidor...\n");
	close (sd);
	return (0);
} /* fim-main */
