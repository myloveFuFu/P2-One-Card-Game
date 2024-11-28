#include "card.h"
void print_rank(card c) {
	switch (c.rank) {
		case 1:
			printf("#  A  #");
			break;
		case 11:
			printf("#  J  #");
			break;
		case 12:
			printf("#  Q  #");
			break;
		case 13:
			printf("#  K  #");
			break;
		case 10:
			printf("# 10  #");
			break;
		default:
			printf("#  %d  #", c.rank);
			break;
	}
}

void print_suit1(card c) {
	switch (c.suit) {
		case 0:
			printf("#\u2660    #");
			break;
		case 1:
			printf("#\u2665    #");
			break;
		case 2:
			printf("#\u2666    #");
			break;
		case 3:
			printf("#\u2663    #");
			break;
	}
}

void print_suit2(card c) {
	switch (c.suit) {
		case 0:
			printf("#    \u2660#");
			break;
		case 1:
			printf("#    \u2665#");
			break;
		case 2:
			printf("#    \u2666#");
			break;
		case 3:
			printf("#    \u2663#");
			break;
	}
}

void print_one_card(card c) {
	printf("#######\n");
	print_suit1(c);
	printf("\n");
	print_rank(c);
	printf("\n");
	print_suit2(c);
	printf("\n");
	printf("#######\n\n");
}

void print_hand_card(card* hand, int num_of_cards, int card_disp_aline) {
	int num = num_of_cards / card_disp_aline;
	int left = num_of_cards % card_disp_aline;
	int index1 = 0;
	int index2 = 0;
	int index3 = 0;
	for (int i = 0; i < num; i++) {
		for (int j = 0; j < card_disp_aline; j++) {
			printf("#######  ");
		}
		printf("\n");
		for (int j = 0; j < card_disp_aline; j++) {
			print_suit1(*(hand + index1));
			printf("  ");
			index1++;
		}
		printf("\n");
		for (int j = 0; j < card_disp_aline; j++) {
			print_rank(*(hand + index2));
			printf("  ");
			index2++;
		}
		printf("\n");
		for (int j = 0; j < card_disp_aline; j++) {
			print_suit2(*(hand + index3));
			printf("  ");
			index3++;
		}
		printf("\n");
		for (int j = 0; j < card_disp_aline; j++) {
			printf("#######  ");
		}
		printf("\n\n");
	}
	if (left != 0) {
		for (int i = 0; i < left; i++) {
			printf("#######  ");
		}
		printf("\n");
		for (int i = 0; i < left; i++) {
			print_suit1(*(hand + index1));
			printf("  ");
			index1++;
		}
		printf("\n");
		for (int i = 0; i < left; i++) {
			print_rank(*(hand + index2));
			printf("  ");
			index2++;
		}
		printf("\n");
		for (int i = 0; i < left; i++) {
			print_suit2(*(hand + index3));
			printf("  ");
			index3++;
		}
		printf("\n");
		for (int i = 0; i < left; i++) {
			printf("#######  ");
		}
		printf("\n\n");
	}
}

void print_one_pile(pile* p) { print_hand_card(p->cards, p->num_of_cards, 5); }
// default with 5 cards in a line
