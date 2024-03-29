#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
#include <time.h>

int buffer_size = 10; //tamanho do buffer
sem_t mutex, empty, full;
int ret0, ret1, count = 0;
pthread_t produtor, consumidor;

    
void produzir(){
    int i = 0;
    while(i < 100){
        sem_wait(&empty); //verifica os espaços vazios
        sem_wait(&mutex); //controle da região crítica
        count++; //posição para inserção de itens no buffer
        printf("Produtor: - %d \n", count);//abstração do produtor
        sleep(1);
        sem_post(&mutex);//saida da região crítica
        sem_post(&full);//representa o incremento de um item ao buffer

        i++;
    }
}

void consumir(){
    int i = 0;
    while(i < 100){
        sem_wait(&full);//verifica os espaços vazios
        sem_wait(&mutex);//controle da região crítica
        printf("Consumidor: - %d \n", count); //abstração do consumidor
        count--;//remove um item do buffer, liberando um espaço
        sleep(3);
        sem_post(&mutex);//saída da regiçao crítica
        sem_post(&empty);//representa a remoção de um item do buffer
        i++;
    }
}

int main(void) {
    
    //Semáforos
    sem_init(&mutex, 0, 1);
    sem_init(&empty, 0, buffer_size);
    sem_init(&full, 0, 0);
    
    ret0 = pthread_create(&produtor, NULL, produzir, NULL);//cria a thread para um produtor
    ret1 = pthread_create(&consumidor, NULL, consumir, NULL);//cria a thread para um consumidor
    
    pthread_join(produtor, NULL);//espera a execução da thread do produtor
    pthread_join(consumidor, NULL);//espera a execução da thread do produtor
    
	return 0;
}