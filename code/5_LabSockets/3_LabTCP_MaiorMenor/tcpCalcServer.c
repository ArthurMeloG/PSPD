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
#include <float.h>
#define QLEN 10
#define MAX_SIZE 20

int main(int argc, char *argv[]){
   	struct sockaddr_in endereco_servidor, endereco_cliente;
   	int    sd, novo_sd;
	int    pid,n;
    	socklen_t alen;

	if (argc < 3) {
		printf("Digite IP e Porta para este servidor\n");
		exit(1);
	}
	memset((char *)&endereco_servidor,0,sizeof(endereco_servidor));
	endereco_servidor.sin_family 		= AF_INET;
	endereco_servidor.sin_addr.s_addr 	= inet_addr(argv[1]);
	endereco_servidor.sin_port 		= htons(atoi(argv[2]));
	sd = socket(AF_INET, SOCK_STREAM, 0);
	if (sd < 0) {
		fprintf(stderr, "ERROR - Criacao do socket!\n");
		exit(1);
	}
	if (bind(sd, (struct sockaddr *)&endereco_servidor, sizeof(endereco_servidor)) < 0) {
		fprintf(stderr,"ERROR - Ligacao Falhou!\n");
		exit(1);
	}
	if (listen(sd, QLEN) < 0) {
		fprintf(stderr,"ERROR - Escuta da porta!\n");
		exit(1);
	}
	printf(">> Servidor Calcula Maior/Menor de um vetor de entrada (Ouvindo em %s/%s)<<\n\n", argv[1], argv[2]);
	alen = sizeof(endereco_cliente);
	if ( (novo_sd=accept(sd, (struct sockaddr *)&endereco_cliente, &alen)) < 0) {
		fprintf(stdout, "ERROR - Falha na conexao\n");
		exit(1);
	}
	fprintf(stdout, "Chegou requisição, cliente %u conectado.\n", ntohs(endereco_cliente.sin_port));

	double buf_rec[MAX_SIZE];
	double res[2];
	memset(&buf_rec, 0x0, MAX_SIZE * sizeof(double));

	/* Recebendo dados do cliente remoto ... */
	n = recv(novo_sd, &buf_rec, sizeof(buf_rec),0); 
	printf("Vetor recebido...\n");
	for(int i = 0; i < MAX_SIZE; i++){
		printf ("%6.2f ", buf_rec[i]);
	}
	printf("\n");
	/* Calculando maior e menor do vetor ...*/
	double maior = DBL_MIN;
	double menor = DBL_MAX;
	for (int i=0; i<MAX_SIZE; i++) {
		if (buf_rec[i] < menor) menor = buf_rec[i];
		if (buf_rec[i] > maior) maior = buf_rec[i];
	} /* fim-for */
	res[0]=menor; res[1]=maior;
	/* Enviando valores calculados de volta para o cliente ...*/
	n = send(novo_sd, &res, sizeof(res), 0);
	printf("Encerrando conexao...\n\n");
	close(novo_sd);
	return 0;
} /* fim-main */
