#include<stdio.h>
#include<pthread.h>
#include<time.h>

#define MAX 4

int hashi[] = {1, 1, 1, 1};
pthread_t threads[MAX];

void pegaHashi(int arg) {
	while(1)
		if(hashi[arg - 1] == 1 && hashi[arg % MAX] == 1){
			hashi[arg - 1] = 0;
			hashi[arg % MAX] = 0;
			return;
		}
}

void largaHashi(int arg) {
	hashi[arg - 1] = 1;
	hashi[arg % MAX] = 1;
}

void * filosofo(void * args) {

	int i, arg = *(int *)args;

	for(i = 0; i < 2; i++) {
		pegaHashi(arg);

		printf("Filosofo %d comendo...3\n", arg);
		sleep(1);
		printf("Filosofo %d comendo...2\n", arg);
		sleep(1);
		printf("Filosofo %d comendo...1\n", arg);
		sleep(1);

		largaHashi(arg);

		printf("Filosofo %d pensando...\n", arg);
		sleep(1);
	}

}

int main() {

	int i, args[] = {1, 2, 3, 4};

	for(i = 0; i < MAX; i++)
		pthread_create(&(threads[i]), NULL, filosofo, args + i);

	for(i = 0; i < MAX; i++)
		pthread_join(threads[i], NULL);

	printf("Fim do jantar.");

	return 0;
}
