#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>

int main() {
	int i=0;
	while (i<1000000) {
		/* execute ação BoT */
		printf("Olá, mundo!\n");
		for (int j=0; j<2000; j++);
		i++;
	} /* fim-while */
	printf("Kbo!\n");
	return 0;
} /* fim-main */
