#include "player.h"

void fprint_player(player* p, FILE* f, bool if_demo) {
	fprintf(f, "Player %d: ", p->player_id);
	fprint_pile(p->hand_card, f);
	if (if_demo) {
		printf("Player %d: ", p->player_id);
		prt_pile(p->hand_card);
	}
}

player* player_init(int player_num, int card_num, pile** draw_pile, FILE* f, bool if_demo) {
	player* head = (player*)calloc(1, sizeof(player));
	if (head == NULL) {
		fprintf(stderr, "Error: memory allocation failed\n");
		exit(-1);
	}
	player* first = head;
	head->player_id = 1;
	head->hand_card = initialise_pile(card_num);
	head->hand_card->num_of_cards = 0;
	move_card(&head->hand_card, draw_pile, card_num);
	fprintf(f, "Dealing cards ...\n");
	if (if_demo) {
		printf("Dealing cards ...\n");
	}
	fprint_player(head, f, if_demo);
	for (int i = 1; i < player_num; i++) {
		player* temp = (player*)calloc(1, sizeof(player));
		if (temp == NULL) {
			fprintf(stderr, "Error: memory allocation failed\n");
			exit(-1);
		}
		temp->player_id = i + 1;
		temp->hand_card = initialise_pile(card_num);
		temp->hand_card->num_of_cards = 0;
		move_card(&temp->hand_card, draw_pile, card_num);
		fprint_player(temp, f, if_demo);
		head->next = temp;
		temp->prev = head;
		head = temp;
	}
	fprintf(f, "\n");
	if (if_demo) {
		printf("\n");
	}
	head->next = first;
	first->prev = head;
	return first;
}

void free_player(player* p) {
	player* temp = p;
	player* next = p->next;
	while (next != p) {
		free_pile(temp->hand_card);
		free(temp);
		temp = next;
		next = next->next;
	}
	free_pile(temp->hand_card);
	free(temp);
}

player* first_player(player* head, pile* draw_pile, pile* store_pile, FILE* f, bool if_figure) {
	printf("Deciding the first player...\n");
	fprintf(f, "Deciding the first player...\n");
	card card[4] = {draw_pile->cards[0], draw_pile->cards[1], draw_pile->cards[2],
	                draw_pile->cards[3]};
	if (if_figure) {
		for (int i = 0; i < 4; i++) {
			printf("Player %d: \n", i + 1);
			print_one_card(card[i]);
		}
	} else {
		for (int i = 0; i < 4; i++) {
			printf("Player %d: ", i + 1);
			prt_one_card(card[i]);
			printf("\n");
		}
	}
	for (int i = 0; i < 4; i++) {
		fprintf(f, "Player %d: ", i + 1);
		fprint_one_card(card[i], f);
		fprintf(f, "\n");
	}
	int win = 0;
	for (int i = 0; i < 4; i++) {
		if (card[i].suit > card[win].suit) {
			win = i;
		} else if (card[i].suit == card[win].suit) {
			if (card[i].rank > card[win].rank) {
				win = i;
			}
		}
	}
	win = win + 1;
	printf("The game will start with player %d\n\n", win);
	fprintf(f, "The game will start with player %d\n\n", win);
	for (int i = 0; i < win - 1; i++) {
		head = head->next;
	}
	move_card(&store_pile, &draw_pile, 4);
	return head;
}

void play_card(player* p, pile** store_pile, int pos) {
	if (pos <= 0 || pos > p->hand_card->num_of_cards) {
		fprintf(stderr, "Error: the position of the card to be played is invalid\n");
		exit(-1);
	}
	p->hand_card = *(if_realloc(&p->hand_card, -1));
	store_pile = if_realloc(store_pile, 1);
	(*store_pile)->cards[(*store_pile)->num_of_cards] = p->hand_card->cards[pos - 1];
	(*store_pile)->num_of_cards++;
	if (pos != p->hand_card->num_of_cards) {
		for (int i = pos - 1; i < p->hand_card->num_of_cards - 1; i++) {
			p->hand_card->cards[i] = p->hand_card->cards[i + 1];
		}
	}
	p->hand_card->cards[p->hand_card->num_of_cards - 1].suit = -1;
	p->hand_card->cards[p->hand_card->num_of_cards - 1].rank = -1;
	p->hand_card->cards[p->hand_card->num_of_cards - 1].type = -1;
	p->hand_card->num_of_cards--;
}
