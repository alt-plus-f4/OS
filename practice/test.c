#include <unistd.h>
#include <pthread.h>
#include <stdio.h>

pthread_mutex_t mutex;

void* add_10(int* number){
    for(int i = 0; i < 10; i++){

        pthread_mutex_lock(&mutex);

            *number += 1;

        pthread_mutex_unlock(&mutex);
    }

}

int main() {
    int number = 0;
	pthread_mutex_init(&mutex, NULL);

    pthread_t add;
    pthread_create(&add, NULL, (void*)add_10, (void*)&number);
    pthread_create(&add, NULL, (void*)add_10, (void*)&number);

    pthread_join(add, NULL);

    printf("Final number: %d\n", number);

    return 0;
}