#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#include "config.h"

pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

void* miner(int** data_for_miner){
    int id = *data_for_miner[0];
    int* player_minerals = data_for_miner[1];
    int* count_mineral_blocks = data_for_miner[2];
    int* mineral_blocks = data_for_miner[3];

    sleep(2);

    while(1){
        sleep(3);
        for(int i = 0; i < *count_mineral_blocks; i++){
            if(mineral_blocks[i] > 0){
                yellow();
                printf("SCV %d is mining from mineral block %d\n", id, i+1);
                reset();

                pthread_mutex_lock(&mutex);

                mineral_blocks[i] -= MINERALS_PER_MINE;
                *player_minerals += MINERALS_PER_MINE;
                
                printf("PLAYER MINERALS: %d\n", *player_minerals);
                pthread_mutex_unlock(&mutex);
                
                cyan();
                printf("SCV %d is transporting minerals\n", id);
                reset();

                sleep(2);
                
                yellow();
                printf("SCV %d delivered minerals to the Command Center\n", id);
                reset();
                
                break;
            }
            if(i == *count_mineral_blocks - 1){
                red();
                printf("SCV %d: I have no job here bye!\n", id);
                reset();
                return NULL;
            }
        }
    }
    
    return NULL;
}


int main(int argc, char* argv[]){
    int SCV = STARTING_SCV;
    int player_minerals = STARTING_MINERALS;
    int count_mineral_blocks = MINERAL_BLOCKS;
    int soldiers = 0, id = 1, left_minerals = 0;

    if(argc > 1) count_mineral_blocks = atoi(argv[1]);

    int mineral_blocks[count_mineral_blocks];
    for(int i = 0; i < count_mineral_blocks; i++) mineral_blocks[i] = MINERALS_PER_BLOCK;
    int* data[] = {&id, &player_minerals, &count_mineral_blocks, mineral_blocks};

    printf("Welcome to StarCraft!\n");
    printf("Game is Starting.");
    fflush(stdout);

    for(int i = 0; i < SCV; i++){
        pthread_t thread;
        pthread_create(&thread, NULL, (void * (*)(void *))miner, (void**)data); //!CHECK FOR ERRS

        printf(".");
        fflush(stdout);

        sleep(1);
        id++;
    }

    while(1){
        fflush(stdin);
        char input = getchar();

        switch(input){
            case 'm':
                if(SCV + soldiers >= MAX_PEOPLE){
                    red();
                    printf("Not enough population.\n");
                    reset();
                    break;
                }

                if(player_minerals >= 50){
                    pthread_mutex_lock(&mutex);
                    player_minerals -= SOLDIER_COST;
                    pthread_mutex_unlock(&mutex);
                    
                    sleep(1);
                    green();
                    printf("You wanna piece of me, boy?\n");
                    reset();
                    soldiers++;
                }
                else {red(); printf("Not enough minerals.\n"); reset();}
                break;
            case 's':
                if(SCV + soldiers >= MAX_PEOPLE){
                    red();
                    printf("Not enough population.\n");
                    reset();
                    break;
                }

                if(player_minerals >= 50){
                    pthread_mutex_lock(&mutex);
                    player_minerals -= SCV_COST;
                    pthread_mutex_unlock(&mutex);

                    sleep(4);
                    pthread_t thread;
                    pthread_create(&thread, NULL, (void * (*)(void *))miner, (void**)data); //!CHECK FOR ERRS
                    
                    green();
                    printf("SCV good to go, sir.\n");
                    reset();
                    SCV++;
                    id++;
                }
                else {red(); printf("Not enough minerals.\n"); reset();}
                break;
            case 'q':
                pthread_mutex_lock(&mutex);
                for(int i = 0; i < count_mineral_blocks; i++) left_minerals += mineral_blocks[i];
                green();
                printf("Map minerals %d, player minerals %d, SCVs %d, Marines %d\n", left_minerals, player_minerals, SCV, soldiers);
                reset();
                pthread_mutex_destroy(&mutex);
                exit(0);
                break;

            default:
                break;
        }
    }


    return 0;
}