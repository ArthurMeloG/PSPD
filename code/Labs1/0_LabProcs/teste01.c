#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>

int main() {
	int i=0;
	int pid;
	int ini, fim;
	pid = fork();
	if (pid < 0 )
		return 1;
	else if (pid == 0) {
		ini = 0;
		fim = 500000;
	} else {
		ini = 500000;
		fim = 1000000;
	}
	while (ini<fim) {
		/* execute ação BoT */
	//	printf("Olá, mundo!\n");
		for (int j=0; j<2000; j++);
		ini++;
	} /* fim-while */
	printf("Kbo!\n");
	return 0;
} /* fim-main */
