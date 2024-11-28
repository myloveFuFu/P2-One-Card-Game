#include "one_play.h"
r_params* round_init(pile** draw_pile, pile** store_pile) {
	r_params* r = (r_params*)calloc(1, sizeof(r_params));
	if (r == NULL) {
		fprintf(stderr, "Error: memory allocation failed\n");
		exit(-1);
	}
	r->attack = 0;
	r->direction = 1;
	r->former_card = (card*)calloc(1, sizeof(card));
	if (r->former_card == NULL) {
		fprintf(stderr, "Error: memory allocation failed\n");
		exit(-1);
	}
	card c = (*draw_pile)->cards[0];
	(*r->former_card) = c;
	r->is_former_card_effect = false;
	move_card(store_pile, draw_pile, 1);
	return r;
}

void free_r(r_params* r) {
	free(r->former_card);
	free(r);
}

void if_exhausted(pile** draw_pile, pile** store_pile, int num, FILE* f, bool if_demo) {
	if (num >= (*draw_pile)->num_of_cards) {
		if (if_demo) {
			printf("The draw pile will be exhausted\n");
			printf("Shuffling the discard pile and restore the stock pile\n");
			move_card(draw_pile, store_pile, (*store_pile)->num_of_cards);
			*draw_pile = shuffle(*draw_pile);
			printf("Shuffle result:\n");
			prt_pile(*draw_pile);
		}
		fprintf(f, "The draw pile will be exhausted\n");
		fprintf(f, "Shuffling the discard pile and restore the stock pile\n");
		fprint_pile(*draw_pile, f);
	}
}

void draw_cards(r_params* r, player* current_player, pile* draw_pile, int num, FILE* f,
                bool if_figure, bool if_demo, pile** store_pile) {
	if_exhausted(&draw_pile, store_pile, num, f, if_demo);
	printf("Player %d draws %d cards\n", current_player->player_id, num);
	fprintf(f, "Player %d draws %d cards\n", current_player->player_id, num);
	printf("Player %d draws: ", current_player->player_id);
	fprintf(f, "Player %d draws: ", current_player->player_id);
	if (if_figure) {
		printf("\n");
		print_hand_card(draw_pile->cards, num, 5);
	} else {
		prt_one_card(draw_pile->cards[0]);
		for (int i = 1; i < num; i++) {
			printf(", ");
			prt_one_card(draw_pile->cards[i]);
		}
		printf("\n");
	}
	fprint_one_card(draw_pile->cards[0], f);
	for (int i = 1; i < num; i++) {
		fprintf(f, ", ");
		fprint_one_card(draw_pile->cards[i], f);
	}
	fprintf(f, "\n");
	move_card(&current_player->hand_card, &draw_pile, num);
	r->attack = 0;
}

int valid_input(player* player1, card* former_card, r_params r, FILE* f, bool if_demo) {
	int pos = can_paly(*former_card, player1->hand_card, r.is_former_card_effect);
	if (pos == -1) {
		return -1;
	} else if (if_demo) {
		printf("Player %d plays (input the position of the card): ", player1->player_id);
		fprintf(f, "Player %d plays (input the position of the card): ", player1->player_id);
		printf("%d\n", pos + 1);
		fprintf(f, "%d\n", pos + 1);
		return pos;
	} else {
		printf("Player %d plays (input the position of the card, type 0 to skip): ",
		       player1->player_id);
		fprintf(f, "Player %d plays (input the position of the card, type 0 to skip): ",
		        player1->player_id);
		if (scanf("%d", &pos) != 1) {
			fprintf(stderr, "Error: invalid input\n");
			exit(-1);
		}
		fprintf(f, "%d\n", pos);
		if (pos == 0) {
			return -1;
		} else {
			if (r.is_former_card_effect) {
				while (pos < 1 || pos > player1->hand_card->num_of_cards ||
				       !card_cmp(*former_card, player1->hand_card->cards[pos - 1])) {
					printf("Invalid input, please input again: ");
					fprintf(f, "Invalid input, please input again: ");
					if (scanf("%d", &pos) != 1) {
						fprintf(stderr, "Error: invalid input\n");
						exit(-1);
					}
					fprintf(f, "%d\n", pos);
				}
			} else {
				while (pos < 1 || pos > player1->hand_card->num_of_cards ||
				       !basic_cmp(*former_card, player1->hand_card->cards[pos - 1])) {
					printf("Invalid input, please input again: ");
					fprintf(f, "Invalid input, please input again: ");
					if (scanf("%d", &pos) != 1) {
						fprintf(stderr, "Error: invalid input\n");
						exit(-1);
					}
					fprintf(f, "%d\n", pos);
				}
			}
			return pos - 1;
		}
	}
}
