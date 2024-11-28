#include "card.h"
bool card_cmp(card former_card, card later_card) {  // the first parameter is the former card and
	                                                // the second parameter is the later card
	if ((former_card.type == 1 && later_card.type == 0) ||
	    (former_card.type == 0 && later_card.type == 2) ||
	    (former_card.type == 2 && later_card.type == 2) ||
	    (former_card.type == 3 && later_card.type == 2)) {
		return false;
	} else {
		return basic_cmp(former_card, later_card);
	}
}

bool basic_cmp(card former_card, card later_card) {
	if (former_card.suit == later_card.suit || former_card.rank == later_card.rank) {
		return true;
	} else {
		return false;
	}
}

int can_paly(card former_card, pile* p, bool if_formal_card_effect) {
	if (if_formal_card_effect) {
		for (int i = 0; i < p->num_of_cards; i++) {
			if (card_cmp(former_card, p->cards[i])) {
				return i;
			}
		}
	} else {
		for (int i = 0; i < p->num_of_cards; i++) {
			if (basic_cmp(former_card, p->cards[i])) {
				return i;
			}
		}
	}
	return -1;
}

pile* initialise_pile(int card_num) {
	int i = card_num / 64;
	pile* p = (pile*)calloc(1, sizeof(pile));
	// check_memory(p);
	if (p == NULL) {
		fprintf(stderr, "Error: memory allocation failed\n");
		exit(-1);
	}
	p->cards = (card*)calloc((size_t)(i + 1) * 64, sizeof(card));
	if (p->cards == NULL) {
		fprintf(stderr, "Error: memory allocation failed\n");
		exit(-1);
	}
	p->num_of_cards = card_num;
	return p;
}

void free_pile(pile* p) {
	free(p->cards);
	free(p);
}

pile* shuffle(pile* p) {
	srand((unsigned int)time(NULL));
	for (int i = 0; i < p->num_of_cards; i++) {
		int j = rand() % p->num_of_cards;
		card temp = p->cards[i];
		p->cards[i] = p->cards[j];
		p->cards[j] = temp;
	}
	return p;
}

pile** if_realloc(pile** p, int num) {
	if (num > 0 && ((*p)->num_of_cards % 64 == 0 || ((*p)->num_of_cards % 64 + num) >= 64)) {
		(*p)->cards =
		    (card*)realloc((*p)->cards, (size_t)((*p)->num_of_cards + num + 64) * sizeof(card));
		if ((*p)->cards == NULL) {
			fprintf(stderr, "Error: memory allocation failed\n");
			exit(-1);
		}
	}
	return p;
}  // num stands for the number of cards to be added or removed

void move_card(pile** add_pile, pile** remove_pile, int num) {
	if (num < 0 || num > (*remove_pile)->num_of_cards) {
		fprintf(stderr, "Error: the number of cards to be moved is invalid\n");
		exit(-1);
	}
	add_pile = if_realloc(add_pile, num);
	remove_pile = if_realloc(remove_pile, -num);
	for (int i = 0; i < num; i++) {
		(*add_pile)->cards[(*add_pile)->num_of_cards + i] = (*remove_pile)->cards[i];
	}
	for (int i = 0; i < (*remove_pile)->num_of_cards - num; i++) {
		(*remove_pile)->cards[i] = (*remove_pile)->cards[i + num];
	}
	for (int i = 0; i < num; i++) {
		(*remove_pile)->cards[(*remove_pile)->num_of_cards - i - 1].suit = -1;
		(*remove_pile)->cards[(*remove_pile)->num_of_cards - i - 1].rank = -1;
		(*remove_pile)->cards[(*remove_pile)->num_of_cards - i - 1].type = -1;
	}
	(*add_pile)->num_of_cards += num;
	(*remove_pile)->num_of_cards -= num;
}

pile* initialise_deck(int num) {
	pile* store_pile = initialise_pile(52 * num);
	for (int i = 0; i < 52 * num; i++) {
		int j = i % 52;
		store_pile->cards[i].suit = j / 13;
		store_pile->cards[i].rank = j % 13 + 1;
		if (store_pile->cards[i].rank == 2 || store_pile->cards[i].rank == 3) {
			store_pile->cards[i].type = 1;
		} else if (store_pile->cards[i].rank == 7) {
			store_pile->cards[i].type = 2;
		} else if (store_pile->cards[i].rank == 11 || store_pile->cards[i].rank == 12) {
			store_pile->cards[i].type = 3;
		} else {
			store_pile->cards[i].type = 0;
		}
	}
	return store_pile;
}
