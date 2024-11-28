#include "one_play.h"
record* rec_init(int player_num) {
	record* rec = (record*)calloc((size_t)player_num, sizeof(record));
	if (rec == NULL) {
		fprintf(stderr, "Error: memory allocation failed\n");
		exit(-1);
	}
	for (int i = 0; i < player_num; i++) {
		rec[i].player_id = i + 1;
		rec[i].round_score = 0;
		rec[i].total_score = 0;
	}
	return rec;
}

record* one_play(player* current_player, r_params* r, pile** draw_pile, pile** store_pile, FILE* f,
                 bool if_figure, bool if_demo, record* rec, int player_num) {
	while (true) {
		printf("Former card: ");
		fprintf(f, "Former card: ");
		print_card(*(r->former_card), f, if_figure, if_demo);
		printf("Attack: %d\n", r->attack);
		fprintf(f, "Attack: %d\n", r->attack);
		printf("Player %d's turn\n", current_player->player_id);
		fprintf(f, "Player %d's turn\n", current_player->player_id);
		printf("Your hand cards: ");
		fprintf(f, "Your hand cards: ");
		print_pile(current_player->hand_card, f, if_figure, if_demo);
		int pos = valid_input(current_player, r->former_card, *r, f, if_demo);
		if (pos == -1) {
			// printf("Former card:(should be the same as the former card)\n");
			// fprintf(f, "Former card:(should be the same as the former card)\n");
			// print_card(*(r->former_card), f, if_figure, if_demo);
			if (r->attack == 0) {
				draw_cards(r, current_player, *draw_pile, 1, f, if_figure, if_demo, store_pile);
			} else {
				draw_cards(r, current_player, *draw_pile, r->attack, f, if_figure, if_demo,
				           store_pile);
			}
			r->is_former_card_effect = false;
		} else {
			// deal with the card effect
			if (current_player->hand_card->cards[pos].type == 1) {
				if (current_player->hand_card->cards[pos].rank == 2) {
					r->attack += 2;
				} else if (current_player->hand_card->cards[pos].rank == 3) {
					r->attack += 3;
				}
			} else if (current_player->hand_card->cards[pos].type == 2) {
				r->attack = 0;
			} else if (current_player->hand_card->cards[pos].type == 3) {
				if (current_player->hand_card->cards[pos].rank == 11) {
					r->direction = r->direction * 2;
				} else if (current_player->hand_card->cards[pos].rank == 12) {
					r->direction = -r->direction;
				}
			}
			r->is_former_card_effect = true;

			printf("Player %d plays: ", current_player->player_id);
			fprintf(f, "Player %d plays: ", current_player->player_id);
			print_card(current_player->hand_card->cards[pos], f, if_figure, if_demo);

			card temp = *(current_player->hand_card->cards + pos);
			(*r->former_card) = temp;
			play_card(current_player, store_pile, pos + 1);
			if (current_player->hand_card->num_of_cards == 0) {
				printf("Player %d wins the round!\n", current_player->player_id);
				fprintf(f, "Player %d wins the round!\n", current_player->player_id);
				player* temp1 = current_player;
				for (int i = 0; i < player_num; i++) {
					rec[temp1->player_id - 1].round_score -= temp1->hand_card->num_of_cards;
					rec[temp1->player_id - 1].total_score += rec[temp1->player_id - 1].round_score;
					temp1 = temp1->next;
				}
				return rec;
			}

			if (current_player->hand_card->num_of_cards == 1) {
				printf("Player %d has only one card left!\n", current_player->player_id);
				fprintf(f, "Player %d has only one card left!\n", current_player->player_id);
			}
		}
		printf("Player %d: ", current_player->player_id);
		fprintf(f, "Player %d: ", current_player->player_id);
		print_pile(current_player->hand_card, f, if_figure, if_demo);

		if (r->direction == 2) {
			current_player = current_player->next;
			current_player = current_player->next;
			r->direction = 1;
		} else if (r->direction == -2) {
			current_player = current_player->prev;
			current_player = current_player->prev;
			r->direction = -1;
		} else if (r->direction == 1) {
			current_player = current_player->next;
		} else {
			current_player = current_player->prev;
		}
		clean_screen(if_demo, f);
	}
}
