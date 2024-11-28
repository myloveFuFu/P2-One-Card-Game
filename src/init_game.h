#ifndef INIT_GAME_H
#define INIT_GAME_H
#include <getopt.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
typedef struct ALL_parameters_for_game {
	int players;
	int cards;
	int decks;
	int rounds;
	bool if_demo;
	bool if_figure;  // if figure cards are used
	FILE* log;
} game_p;
void cmd_help(void);
game_p init_game(int argc, char* argv[]);
#endif
