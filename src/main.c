#include "card.h"
#include "init_game.h"
#include "one_play.h"
#include "player.h"
#include "tool_box.h"

int main(int argc, char* argv[]) {
	game_p g = init_game(argc, argv);
	pile* draw_pile = initialise_deck(g.decks);
	pile* store_pile = initialise_pile(0);
	draw_pile = shuffle(draw_pile);
	fprintf(g.log, "Shuffling the cards...\n");
	fprintf(g.log, "Shuffle result:\n");
	fprint_pile(draw_pile, g.log);
	fprintf(g.log, "\n");
	if (g.if_demo) {
		printf("Shuffling the caeds...\n");
		printf("Shuffle result:\n");
		prt_pile(draw_pile);
		printf("\n");
	}
	player* head = player_init(g.players, g.cards, &draw_pile, g.log, g.if_demo);
	player* first = first_player(head, draw_pile, store_pile, g.log, g.if_figure);
	// fprint_player(first, g.log, g.if_demo);
	// play_card(first, &store_pile, 3);
	// fprint_player(first, g.log, g.if_demo);
	// fprint_pile(store_pile, g.log);
	game_start(g.if_demo, g.log);

	r_params* r = round_init(&draw_pile, &store_pile);
	// fprint_pile(draw_pile, g.log);
	// fprint_pile(store_pile, g.log);
	record* rec = rec_init(g.players);
	for (int i = 0; i < g.rounds; i++) {
		rec = one_play(first, r, &draw_pile, &store_pile, g.log, g.if_figure, g.if_demo, rec,
		               g.players);
		printf("-----Status-----\nRound %d result: \n", i + 1);
		int winround = 0;
		fprintf(g.log, "-----Status-----\nRound %d result: \n", i + 1);
		for (int j = 0; j < g.players; j++) {
			printf("Player %d: %d, total: %d\n", rec[j].player_id, rec[j].round_score,
			       rec[j].total_score);
			if (rec[j].round_score == 0) {
				winround = j;
			}
			fprintf(g.log, "Player %d: %d, total: %d\n", rec[j].player_id, rec[j].round_score,
			        rec[j].total_score);
			(rec + j)->round_score = 0;
		}
		printf("\n");
		fprintf(g.log, "\n");

		if (i != g.rounds - 1) {
			free_player(head);
			free_pile(draw_pile);
			free_pile(store_pile);
			draw_pile = initialise_deck(g.decks);
			store_pile = initialise_pile(0);
			draw_pile = shuffle(draw_pile);
			fprintf(g.log, "Shuffling the cards...\n");
			fprintf(g.log, "Shuffle result:\n");
			fprint_pile(draw_pile, g.log);
			fprintf(g.log, "\n");
			if (g.if_demo) {
				printf("Shuffling the caeds...\n");
				printf("Shuffle result:\n");
				prt_pile(draw_pile);
				printf("\n");
			}
			head = player_init(g.players, g.cards, &draw_pile, g.log, g.if_demo);
			for (int j = 0; j < winround; j++) {
				head = head->next;
			}
			first = head;
		}
	}

	int winner = 0;
	for (int i = 0; i < g.players; i++) {
		if (rec[i].total_score > rec[winner].total_score) {
			winner = i;
		}
	}
	printf("Final winner is player %d ", rec[winner].player_id);
	for (int i = 0; i < g.players; i++) {
		if (rec[i].total_score == rec[winner].total_score && i != winner) {
			printf("and %d ", rec[i].player_id);
		}
	}
	printf("\n");
	fprintf(g.log, "Final winner is player %d\n", rec[winner].player_id);
	for (int i = 0; i < g.players; i++) {
		if (rec[i].total_score == rec[winner].total_score && i != winner) {
			fprintf(g.log, "and %d ", rec[i].player_id);
		}
	}
	fprintf(g.log, "\n");
	free(rec);
	free_r(r);
	free_player(head);
	free_pile(draw_pile);
	free_pile(store_pile);
	fclose(g.log);
	return 0;
}
