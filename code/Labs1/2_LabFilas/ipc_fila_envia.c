#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>

/* Estrutura a ser enviada a fila de mensagens */
struct my_msgbuf {
    long mtype;
    char mtext[10];
};

int main(int argc, char **argv) {
    struct my_msgbuf buf;

    /* ID mantido pelo kernel */
    int msqid;
    /* Identificador unico da fila de mensagens */
    key_t key;
    /* Gerando o identificador unico da fila... */
    if( ( key = ftok( "ipc_fila_envia.c", 'B' ) ) == -1 ) {
        fprintf( stderr, "Erro na geracao do ID da fila.\n" );
       exit(1);
    }
    /* Criando a fila de mensagens */
    if( ( msqid = msgget( key, 0666 | IPC_CREAT ) ) == -1 ) {
        fprintf( stderr, "Erro na criacao da fila.\n" );
        exit(1);
    }
    /* Enviando mensagens */
    printf( "Digite mensagens de até 10 caracteres (Ctrl+D para sair):\n" );
    buf.mtype = 1;
    while( fgets( buf.mtext, 10, stdin ) /*&& !feof(stdin)*/ )  {
    if( msgsnd( msqid, (struct msgbuf *) &buf, sizeof(buf), 0 ) == -1 )
        fprintf( stderr, "Erro no envio da mensagem.\n" );
    }
//    if( msgctl( msqid, IPC_RMID, NULL ) == -1 ) {
//        fprintf( stderr, "Erro na remocao da fila.\n" );
//        exit(1);
//    }
    return 0;
}
