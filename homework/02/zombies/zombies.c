#include "ui.h"
#include "config.h"

int main() {
	init();
	
	print_gold(STARTING_GOLD);
	print_soldiers(STARTING_SOLD);
	print_zombies(ZOMBIE_START_POS, STARTING_ZOMB);
	print_health(HEALTH);

	while(1) {
		int ch = get_input();
		switch(ch) {
			case 'q':
				game_end(0);
				break;
			case 'm':
				spawn_miner();
				break;
			case 's':
				spawn_soldier(1);
				break;
			case 'x':
				spawn_soldier(10);
				break;
		}
	}

	return 0;
}