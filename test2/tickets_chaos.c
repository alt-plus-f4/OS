#include <string.h>
#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>

pthread_mutex_t floor_mutex;
pthread_mutex_t lower_mutex;
pthread_mutex_t upper_mutex;

void* buy_ticket(int** data){
    int* floor_tickets = data[0];
    int* lower_tickers = data[1];
    int* upper_tickets = data[2];

    // srand(time(NULL));
    int ticket_category = (rand() % 3) + 1;
    // printf("Ticket category: %d\n", ticket_category);

    
    if(ticket_category == 1){
        pthread_mutex_lock(&floor_mutex);

        if(*floor_tickets > 0){
            (*floor_tickets) -= 1;
            pthread_mutex_unlock(&floor_mutex);
            printf("BOUGHT FLOOR: Left %d\n", *floor_tickets);
        }
        else printf("Tickes of type FLOOR have sold out\n");
    }
    else if(ticket_category == 2){
        pthread_mutex_lock(&lower_mutex);

        if(*lower_tickers > 0){
            (*lower_tickers) -= 1;
            pthread_mutex_unlock(&lower_mutex);
            printf("BOUGHT LOWER: Left %d\n", *lower_tickers);
        }

        else printf("Tickes of type LOWER have sold out\n");
    }
    else if(ticket_category == 3){
        pthread_mutex_lock(&upper_mutex);

        if(*upper_tickets > 0){
            (*upper_tickets) -= 1;
            pthread_mutex_unlock(&upper_mutex);
            printf("BOUGHT UPPER: Left %d\n", *upper_tickets);
        }

        else printf("Tickes of type UPPER have sold out\n");
    }
    else{
        printf("what??\n");
    }
}

int main(int argc, char* argv[]){
    if(argc != 2) {
        printf("Invalid Args: ONE EXTRA REQ!\n");
        return -1;
    }

    pthread_mutex_init(&floor_mutex, NULL);
    pthread_mutex_init(&lower_mutex, NULL);
    pthread_mutex_init(&upper_mutex, NULL);
    srand(time(NULL));

    int floor_tickets = 5000;
    int lower_tickers = 5000;
    int upper_tickets = 5000;

    int* data[] = {&floor_tickets, &lower_tickers, &upper_tickets};
    int buyers_count = atoi(argv[1]);
    pthread_t buyer;

    for(int i = 0; i < buyers_count; i++)
        pthread_create(&buyer, NULL, (void*) buy_ticket, (void*) data);

    pthread_join(buyer, NULL);

    printf("Floor tickets rn: %d\n", floor_tickets);
    printf("Lower tickets rn: %d\n", lower_tickers);
    printf("Upper tickets rn: %d\n", upper_tickets);

    return 0;
}