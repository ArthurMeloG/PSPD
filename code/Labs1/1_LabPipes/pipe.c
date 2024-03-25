#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>

int main(void) {
        int     fd[2], nbytes;
        pid_t   pid;
        char    string[] = "Olá, mundo!";
        char    readbuffer[80];

        pipe(fd);
        if((pid = fork()) == -1) {
                perror("fork");
                exit(1);
        } /* fim-if */
        if(pid == 0) {
                /* Child process closes up input side of pipe */
                close(fd[0]);
                /* Send "string" through the output side of pipe */
		printf("Processo [%d] --> Enviando string pelo pipe...\n", getpid());
                write(fd[1], string, (strlen(string)+1));
                exit(0);
        } else {
                /* Parent process closes up output side of pipe */
                close(fd[1]);
                /* Read in a string from the pipe */
                nbytes = read(fd[0], readbuffer, sizeof(readbuffer));
                printf("Processo [%d] --> Recebendo string do pipe ...: %s\n", getpid(), readbuffer);
        } /* fim-if */
        return(0);
} /* fim-main */
