#include <string.h>
#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>

pthread_mutex_t mutex;

void* buy_shares(int* shares){
    pthread_mutex_lock(&mutex);
    if(*shares > 0){
        (*shares) -= 1;
        printf("Shares bought! Shares left after transaction: %d\n", *shares);
    }
    else printf("Shares cannot be bought rn!\n");
    
    pthread_mutex_unlock(&mutex);
}

void* sell_shares(int* shares){
    pthread_mutex_lock(&mutex);
        (*shares) += 1;
        printf("Shares sold! Shares left after transaction: %d\n", *shares);
    pthread_mutex_unlock(&mutex);

}


int main(int argc, char* argv[]){
    if(argc != 3){
        printf("Invalid args! TWO ARGS EXTRA REQ\n");
        return -1;
    } 

    int shares = 1000;
    
    pthread_mutex_init(&mutex, NULL);
    pthread_t buyer;
    pthread_t seller;

    for(int i = 0; i < atoi(argv[1]); i++)
        pthread_create(&buyer, NULL, (void*) buy_shares, &shares);

    for(int i = 0; i < atoi(argv[1]); i++)
        pthread_create(&seller, NULL, (void*) sell_shares, &shares);
    

    pthread_join(buyer, NULL);
    pthread_join(seller, NULL);

    return 0;
}