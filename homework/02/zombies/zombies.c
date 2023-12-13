#include "ui.h"
#include "config.h"
#include <unistd.h>
#include <pthread.h>

pthread_mutex_t mutex;

void* mine(int* gold){
	while(1){
		pthread_mutex_lock(&mutex);
		
		*gold += 10;

		pthread_mutex_unlock(&mutex);
		print_gold(*gold);

		sleep(1);
	}
}

void* spawn_soldier(unsigned int amount, int* soldiers){
	pthread_mutex_lock(&mutex);
		*soldiers += amount;
	pthread_mutex_unlock(&mutex);

	print_soldiers(*soldiers);
}

void* zombie_attack(int* soldiers){
	int zombies = STARTING_ZOMB;
	int health = HEALTH;

	while(1){
		for(int i = 5; i > 0; i--){
			print_zombies(i, zombies);
			sleep(1);
		}
		
		if(*soldiers > zombies) print_succ("Zombie attack DEFEATED!\n");

		else{
			print_fail("Zombie attack WAS NOT DEFEATED!\n");
			health -= zombies - *(soldiers);
			if(health < 1) game_end(zombies);
			print_health(health);
		}
		zombies *= ZOMBIE_CHANGE;
	}
}

int main() {
	init();
	pthread_mutex_init(&mutex, NULL);

	int gold = STARTING_GOLD;
	print_gold(STARTING_GOLD);
	int soldiers = STARTING_SOLD;
	print_soldiers(STARTING_SOLD);

	pthread_t zombie_thread;
	pthread_create(&zombie_thread, NULL, (void*)zombie_attack, (void*)&soldiers);

	while(1) {
		int ch = get_input();
		switch(ch) {
			case 'q':
				game_end(0);
				break;
			case 'm':
				if(gold < 100){
					print_fail("Not enough gold!\n");
					break;
				}

				pthread_mutex_lock(&mutex);
					gold-=100;
				pthread_mutex_unlock(&mutex);
				print_gold(gold);

				pthread_t miner;
				print_succ("Miner bought!\n");
				pthread_create(&miner, NULL, (void*)mine, (void*)&gold);

				break;
			case 's':
				if(gold < 10){
					print_fail("Not enough gold!\n");
					break;
				}

				pthread_mutex_lock(&mutex);
					gold-=10;
				pthread_mutex_unlock(&mutex);
				print_gold(gold);

				spawn_soldier(1, &soldiers);
				print_succ("Soldier bought!\n");

				break;
			case 'x':
				if(gold < 100){
					print_fail("Not enough gold!\n");
					break;
				}

				pthread_mutex_lock(&mutex);
					gold-=100;
				pthread_mutex_unlock(&mutex);
				print_gold(gold);

				spawn_soldier(10, &soldiers);
				print_succ("10 soldiers bought!\n");

				break;
		}
	}
	return 0;
}