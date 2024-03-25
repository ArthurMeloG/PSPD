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
    /* Conectando-se a fila de mensagens */
    if( ( msqid = msgget( key, 0666 ) ) == -1 ) {
        fprintf( stderr, "Erro ao conectar a fila.\n" );
        exit(1);
    }
    printf( "Recebendo mensagens...\n" );
    buf.mtype = 1;
    for(;;) {
        if( msgrcv( msqid, (struct msgbuf *) &buf, sizeof(buf), 0, 0 ) == -1 ) {
            fprintf( stderr, "Erro ao receber mensagem.\n" );
            exit(1);
        }
        printf( "MENSAGEM: %s\n", buf.mtext );
    }
    return 0;
}