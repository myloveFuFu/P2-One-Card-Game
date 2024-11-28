#include "card.h"

void prt_one_card(card c) {
	switch (c.suit) {
		case 0:
			printf("Spade ");
			break;
		case 1:
			printf("Heart ");
			break;
		case 2:
			printf("Diamond ");
			break;
		case 3:
			printf("Club ");
			break;
	}
	switch (c.rank) {
		case 1:
			printf("Ace");
			break;
		case 11:
			printf("Jack");
			break;
		case 12:
			printf("Queen");
			break;
		case 13:
			printf("King");
			break;
		default:
			printf("%d", c.rank);
			break;
	}
}

void prt_pile(pile* p) {
	for (int i = 0; i < p->num_of_cards - 1; i++) {
		prt_one_card(p->cards[i]);
		printf(", ");
	}
	prt_one_card(p->cards[p->num_of_cards - 1]);
	printf("\n");
}

void fprint_one_card(card c, FILE* f) {
	switch (c.suit) {
		case 0:
			fprintf(f, "Spade ");
			break;
		case 1:
			fprintf(f, "Heart ");
			break;
		case 2:
			fprintf(f, "Diamond ");
			break;
		case 3:
			fprintf(f, "Club ");
			break;
	}
	switch (c.rank) {
		case 1:
			fprintf(f, "Ace");
			break;
		case 11:
			fprintf(f, "Jack");
			break;
		case 12:
			fprintf(f, "Queen");
			break;
		case 13:
			fprintf(f, "King");
			break;
		default:
			fprintf(f, "%d", c.rank);
			break;
	}
}

void fprint_pile(pile* p, FILE* f) {
	for (int i = 0; i < p->num_of_cards - 1; i++) {
		fprint_one_card(p->cards[i], f);
		fprintf(f, ", ");
	}
	fprint_one_card(p->cards[p->num_of_cards - 1], f);
	fprintf(f, "\n");
}

void print_card(card c, FILE* f, bool if_figure, bool if_demo) {
	fprint_one_card(c, f);
	fprintf(f, "\n");
	if (if_figure && !if_demo) {
		printf("\n");
		print_one_card(c);
	} else {
		prt_one_card(c);
		printf("\n");
	}
}

void print_pile(pile* p, FILE* f, bool if_figure, bool if_demo) {
	fprint_pile(p, f);
	if (if_figure && !if_demo) {
		printf("\n");
		print_one_pile(p);
	} else {
		prt_pile(p);
	}
}
