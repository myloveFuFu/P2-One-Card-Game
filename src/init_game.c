#include "init_game.h"

void cmd_help(void) {
	printf(
	    "-h|--help print this help message\n--log filename write the logs in filename (default: "
	    "onecard.log)\n");
	printf("-n n|--player-number=n n players, n must be larger than 2 (default: 4)\n");
	printf("-c c|--initial-cards=c deal c cards per player, c must be at least 2 (default: 5)\n");
	printf("-d d|--decks=d use d decks 52 cards each, d must be at least 2 (default: 2)\n");
	printf("-r r|--rounds=r play r rounds, r must be at least 1 (default: 1)\n");
	printf("-a|--auto run in demo mode\n");
	printf("-f|--figure use figure cards\n");  // add new function
}

game_p init_game(int argc, char *argv[]) {
	game_p g;
	g.players = 4;
	g.cards = 5;
	g.decks = 2;
	g.rounds = 1;
	g.if_demo = false;
	g.if_figure = false;
	g.log = NULL;
	char log_file[100] = "onecard.log";

	int option_index = 0, opt = 0;
	struct option long_options[] = {{"help", no_argument, NULL, 'h'},
	                                {"log", required_argument, NULL, 0},
	                                {"player-number", required_argument, NULL, 'n'},
	                                {"initial-cards", required_argument, NULL, 'c'},
	                                {"decks", required_argument, NULL, 'd'},
	                                {"rounds", required_argument, NULL, 'r'},
	                                {"auto", no_argument, NULL, 'a'},
	                                {"figure", no_argument, NULL, 'f'},  // add new function
	                                {NULL, 0, NULL, 0}};

	while ((opt = getopt_long(argc, argv, "hn:c:d:r:af", long_options, &option_index)) != -1) {
		switch (opt) {
			case 'h':
				cmd_help();
				exit(1);
			case 0:
				snprintf(log_file, 100, "%s", optarg);
				break;
			case 'n':
				g.players = atoi(optarg);
				if (g.players <= 2) {
					fprintf(stderr, "Error: player number must be larger than 2.\n");
					exit(-1);
				}
				break;
			case 'c':
				g.cards = atoi(optarg);
				if (g.cards < 2) {
					fprintf(stderr, "Error: initial cards must be at least 2.\n");
					exit(-1);
				}
				break;
			case 'd':
				g.decks = atoi(optarg);
				if (g.decks < 2) {
					fprintf(stderr, "Error: decks must be at least 2.\n");
					exit(-1);
				}
				break;
			case 'r':
				g.rounds = atoi(optarg);
				if (g.rounds < 1) {
					fprintf(stderr, "Error: rounds must be at least 1.\n");
					exit(-1);
				}
				break;
			case 'a':
				g.if_demo = true;
				break;
			case 'f':
				g.if_figure = true;
				break;
			default:
				printf("Unvalid input\n");
				cmd_help();
				exit(-1);
		}
	}

	printf("#######################\n");
	printf("#                     #\n");
	printf("# Wlecome to One card #\n");
	printf("#                     #\n");
	printf("#######################\n\n\n");
	printf("-----Initial setup-----\n");
	printf("Number of rounds: %d\n", g.rounds);
	printf("Number of players: %d\n", g.players);
	printf("Number of decks: %d\n\n", g.decks);

	g.log = fopen(log_file, "w");  // remember to close in main
	if (g.log == NULL) {
		fprintf(stderr, "Error: cannot open log file.\n");
		exit(-1);
	}
	fprintf(g.log, "#######################\n");
	fprintf(g.log, "#                     #\n");
	fprintf(g.log, "# Wlecome to One card #\n");
	fprintf(g.log, "#                     #\n");
	fprintf(g.log, "#######################\n\n\n");
	fprintf(g.log, "-----Initial setup-----\n");
	fprintf(g.log, "Number of rounds: %d\n", g.rounds);
	fprintf(g.log, "Number of players: %d\n", g.players);
	fprintf(g.log, "Number of decks: %d\n\n", g.decks);

	return g;
}
